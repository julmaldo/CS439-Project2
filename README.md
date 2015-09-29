# CS439-Project2
Memory Allocator 

In this assignment I made my own malloc function that uses first fit to allocate memory and also a function to free up memory blocks. 

assignment discription:

1. Write Your Own Memory Allocator (40 Points)

  You will implement your own memory allocator in user space. The archive that you can download
  from the class web page contains a header file mymalloc.h with the API as well as a code skeleton
  in mymalloc.c.
  
  The API for mymalloc is the following:

  **
  * @brief Initializer, guaranteed to be called before any memory request
  *
  
  void my_malloc_init();
  
  **
  * @brief Allocate a block of memory of size size.
  * @param [in] size the requested size of the block.
  * @retval the pointer to the block or a negative value
  * if the request cannot be fulfilled.
  *
  
  void *my_malloc(size_t size);
  
  /**
  * @brief Free a previously allocated block so that it
  * becomes available again.
  * If possible, coalesc the block with adjacent free
  * blocks.
  * @param [in] ptr the pointer to the block.
  */
  
  void my_free(void *ptr);
  
  /**
  * @brief Dump a graphical representation of the state of the
  * mymalloc heap to the stream.
  * @param [in] stream the stream to write to.
  */
  
  void my_dump_mem(FILE *stream);
  
  /**
  * @brief Translate an absolute pointer address to the relative
  * address (in MiB) within the mymalloc heap.
  * @param [in] ptr the address to translate.
  * @retval The translated address in MiB.
  */
  
  uint64_t my_address(void *ptr);
  
  When my malloc init() is called, your memory allocator acquires a large chunk of memory from
  the operating system (through a traditional malloc) which it can then manage.
  You have the choice to implement any of the memory allocation strategies discussed in class (first
  fit, best fit, worst fit, buddy).
  
  Whenever a program requests a block of memory through my malloc, you need to update the
  internal data structures to reflect that the block that you picked is now used. When my free is
  called with a pointer to a previously allocated block, this block should become available again and
  potentially be coalesced with any adjacent free blocks.
  
  Finally, the my dump mem function prints a schematic representation of the current heap to a file
  descriptor. In order to simplify your task you can find a draw box function in the code skeleton
  that prints awesome ASCII-art boxes (either filled, or empty) and a mock-up example of how to use
  it. What you need to do is to iterate over the blocks in your heap (from the lowest to the highest
  address) and call the draw box function for every block (full or empty).
  The my address function is already implemented.


2 Test Your Memory Allocator
    The archive also contains a main.c file which uses mymalloc and can be used for testing. Using the
    provided make file, you can build a prog executable. Note that with the current mymalloc library
    the first assertion will already fail.
