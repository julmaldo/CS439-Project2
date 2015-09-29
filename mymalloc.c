#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include "mymalloc.h"

//struct for memory block with size, wether its empty or not and pointer to next block if there is one
struct memBlock
{
   size_t size;
   int isFree;
   struct memBlock *next;
};

static void *mem;
struct memBlock *memblock;

//combines empty memory bolcks together
void coalesce() {
   struct memBlock *current;
   current = memblock;
   while(current->next != NULL) {
      if (current->isFree && current->next->isFree) {
         current->size += (current->next->size);
         current->next = current->next->next;
      } else {
         current = current->next;
      }
      
   }
}

//cuts the excess space of current memory block and makes a new block
void split(struct memBlock *current, size_t size) {
   struct memBlock *newBlock = (struct memBlock*)((char*)current + size);
   
   newBlock->size = (current->size) - size;
   newBlock->isFree = 1;  
   newBlock->next = current->next;
   
   current->size = size;
   current->isFree = 0;
   current->next = newBlock;
}

void my_malloc_init(size_t size)
{
   mem = malloc(size);
   memblock = mem;
   memblock->next = NULL;
   memblock->size = size;
   memblock->isFree = 1;
  
}

//uses first fit search to allocate memory
void *my_malloc(size_t size)
{
   struct memBlock *current;
   void *result;
   current = memblock;
   

   //return empty memory blocks that can contain memory
   while ((current->size < size || current->isFree == 0) && (current->next != NULL)) {
      current = current->next;
   }

   //perfect fit
   if (current->size == size) {
      current->isFree = 0;
      result = (void*) (current);
      return result;
   } 
   //first
   else if (current->size > (size)) {
      split(current, size);
      result = (void*)(current);
      return result;
   } 
   else {
      return NULL;//no memory
   }




   /*
   i do{
       while ((cur->size < size || cur->is_free == 0)&&(cur->next != NULL)) {
         cur = cur->next;
      }
      if (cur->size == size){
         best_fit = cur;
         break;
      } else if ((best_fit->size > cur->size)){
         best_fit = cur;
      }
   }while(cur->next != NULL);

   if (best_fit->size == size){
      cur = best_fit;
      cur->is_free = 0;
      result = (void*)(++cur);
      return result;
   } else if(best_fit->size > size){
      cur = best_fit;
      split(cur, size);
      result = (void*)(++cur);
      return result;
   }else{
      return NU;
   }
   */
}


void my_free(void *ptr)
{
   struct memBlock *current = ptr;
   current->isFree = 1;
   coalesce();
}

static void draw_box(FILE *stream, int size, int empty, int last)
{
   int i;
   int pad = size / 2;

   fprintf(stream, "+---------------------+\n");

   if (!empty) fprintf(stream, "%c[%d;%dm", 0x1B, 7, 37);

   for (i=0; i<pad; i++)
   {
      fprintf(stream, "|                     |\n");
   }

   fprintf(stream, "|         %2d          |\n", size);

   for (i++; i<size; i++)
   {
      fprintf(stream, "|                     |\n");   
   }

   if (!empty) fprintf(stream, "%c[%dm", 0x1B, 0);

   if (last) fprintf(stream, "+---------------------+\n");
}

void my_dump_mem(FILE *stream)
{
   struct memBlock *current;
   current = memblock;
   while(current->next != NULL) {
      draw_box(stream, (int)(current->size/MiB), current->isFree, 0);
      current = current->next;      
   }
   draw_box(stream, current->size / MiB, current->isFree, 1);

}

uint64_t my_address(void *ptr)
{
   return ((((uint64_t) ptr) - ((uint64_t) mem)) / MiB);
}


