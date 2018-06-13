#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/mman.h>

// Add the message size
void append_message_size(std::vector<uint8_t> &machine_code, const std::string &hello_name);

void show_machine_code(const std::vector<uint8_t> &machine_code);

size_t estimate_memory_size(size_t machine_code_size);

int main() {
    std::string personName;
    // std::cout << "Please enter your name:" << std::endl;
    // std::getline(std::cin, personName);
    personName = "Man Parvesh";
    std::string greeting = "Welcome to C++, " + personName + "!!";


    // generating machine code
    std::vector<uint8_t> machine_code{
            0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00,           //Store the "write" system call number 0x01 for Linux
            0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,           //Store stdin file descriptor 0x01
            0x48, 0x8d, 0x35, 0x0a, 0x00, 0x00,
            0x00,           //Store the location of the string to write (3 instructions from the current instruction pointer)
            0x48, 0xc7, 0xc2, 0x00, 0x00, 0x00, 0x00,           //Store the length of the string (initially zero)
            0x0f, 0x05,                                         //Execute the system call
            0xc3                                                //return instruction
    };

    append_message_size(machine_code, greeting);

    for (auto c : greeting) {
        machine_code.push_back(c);
    }

    show_machine_code(machine_code);

    // allocate required memory size
    size_t required_size = estimate_memory_size(machine_code.size());
    uint8_t *mem = (uint8_t *) mmap(NULL, required_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        std::cerr << "Can't allocate memory ._.\n";
        std::exit(1);
    }

    // copy generated code to executable memory
    for (size_t i = 0; i < machine_code.size(); i++) {
        mem[i] = machine_code[i];
    }

    // get a pointer to the beginning of the our executable code and
    // cast it to a function pointer, after which we can use the generated function
    void (*func)();
    // cast address to function and call
    func = (void (*)()) mem;
    func();

    // Release the mapped memory
    munmap(mem, required_size);

    return 0;
}

void append_message_size(std::vector<uint8_t> &machine_code, const std::string &hello_name) {
    size_t message_size = hello_name.length();

    machine_code[24] = (message_size & 0xFF) >> 0;
    machine_code[25] = (message_size & 0xFF00) >> 8;
    machine_code[26] = (message_size & 0xFF0000) >> 16;
    machine_code[27] = (message_size & 0xFF000000) >> 24;
}

void show_machine_code(const std::vector<uint8_t> &machine_code) {
    int index = 0;
    std::cout << "Generated machine code: " << std::endl;

    // print hex
    std::cout << std::hex;
    for (int i = 0; i < machine_code.size(); i++) {
        auto e = (int) machine_code[i];
        std::cout << e << " ";
        if (i % 7 == 0) {
            std::cout << std::endl;
        }
    }

    // revert to decimal
    std::cout << std::dec;
    std::cout << std::endl;
    std::cout << std::endl;
}

size_t estimate_memory_size(size_t machine_code_size) {
    size_t page_size_multiple = sysconf(_SC_PAGESIZE); // machine page size
    size_t factor = 1;
    size_t required_memory_size;

    while (true) {
        required_memory_size = factor * page_size_multiple;
        if (machine_code_size <= required_memory_size) {
            break;
        }
        factor++;
    }

    return required_memory_size;
}
