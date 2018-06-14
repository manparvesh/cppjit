/*********************************************************
*           Created by manparvesh on 14/6/18.
*********************************************************/

#ifndef CPPJIT_MEMORY_PAGES_H
#define CPPJIT_MEMORY_PAGES_H


#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

#define endl '\n'

class MemoryPages {
private:
    size_t page_size; // OS defined memory page size (typically 4096 bytes)
    size_t num_pages = 0; // no of memory pages requested from the OS
    size_t position = 0; // current position to the unused memory space

    // Check if it there is enough available space to push some data to the memory
    void check_available_space(size_t data_size);

public:
    uint8_t *executable_memory; // pointer to start of executable memory

    MemoryPages(size_t pages_requested = 1);

    ~MemoryPages();

    // push an uint8_t number to memory
    void push(uint8_t data);

    // Push a function pointer to the memory
    void push(void (*fn)());

    // Push a vector of uint8_t numbers to the memory
    void push(const std::vector<uint8_t> &data);

    // Print the content of used memory
    void show_memory();
};

#endif //CPPJIT_MEMORY_PAGES_H
