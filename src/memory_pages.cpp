/*********************************************************
*           Created by manparvesh on 14/6/18.
*********************************************************/

#include "memory_pages.h"

/*********************************************************
*           implementations of private methods
*********************************************************/

void MemoryPages::check_available_space(size_t data_size) {
    if (position + data_size > num_pages * page_size) {
        throw std::runtime_error("Not enough virtual memory allocated!");
    }
}

/*********************************************************
*           implementations of public methods
*********************************************************/

// constructor
MemoryPages::MemoryPages(size_t pages_requested) {
    page_size = sysconf(_SC_PAGE_SIZE); // Get the machine page size
    executable_memory = (uint8_t *) mmap(NULL, page_size * pages_requested, PROT_READ | PROT_WRITE | PROT_EXEC,
                                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (executable_memory == MAP_FAILED) {
        throw std::runtime_error("Can't allocate enough executable memory!");
    }
    num_pages = pages_requested;
}

// destructor
MemoryPages::~MemoryPages() {
    munmap(executable_memory, num_pages * page_size);
}

// push an uint8_t number to memory
void MemoryPages::push(uint8_t data) {
    check_available_space(sizeof data);
    executable_memory[position] = data;
    position++;
}

// Push a function pointer to the memory
void MemoryPages::push(void (*fn)()) {
    size_t function_address = reinterpret_cast<size_t>(fn);
    check_available_space(sizeof function_address);

    std::memcpy((executable_memory + position), &function_address, sizeof function_address);
    position += sizeof function_address;
}

// Push a vector of uint8_t numbers to the memory
void MemoryPages::push(const std::vector<uint8_t> &data) {
    check_available_space(data.size());

    std::memcpy((executable_memory + position), &data[0], data.size());
    position += data.size();
}

// Print the content of used memory
void MemoryPages::show_memory() {
    std::cout << endl << "Memory content: " << position << "/" << num_pages * page_size << " bytes used"
              << endl;
    std::cout << std::hex;
    for (size_t i = 0; i < position; ++i) {
        std::cout << "0x" << (int) executable_memory[i] << " ";
        if (i % 16 == 0 && i > 0) {
            std::cout << endl;
        }
    }
    std::cout << std::dec;
    std::cout << endl;
    std::cout << endl;
}
