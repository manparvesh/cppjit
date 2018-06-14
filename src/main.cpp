/*********************************************************
*           Created by manparvesh on 14/6/18.
 *********************************************************/

#include "memory_pages.h"

namespace AssemblyChunks {
    std::vector<uint8_t> function_prologue{
            0x55,               // push rbp
            0x48, 0x89, 0xe5,   // mov	rbp, rsp
    };

    std::vector<uint8_t> function_epilogue{
            0x5d,   // pop	rbp
            0xc3    // ret
    };
}

// Global vector that is modified by test()
std::vector<int> a{1, 2, 3};

// Function to be called from our generated machine code
void test() {
    printf("Ohhh, boy ...\n");
    for (auto &e : a) {
        e -= 5;
    }
}

int main() {
    // Instance of exec mem structure
    MemoryPages mp;

    // Push prologue
    mp.push(AssemblyChunks::function_prologue);

    // Push the call to the C++ function test (actually we push the address of the test function)
    mp.push(0x48);
    mp.push(0xb8);
    mp.push(test);    // movabs rax, <function_address>
    mp.push(0xff);
    mp.push(0xd0);                   // call rax

    // Push epilogue and print the generated code
    mp.push(AssemblyChunks::function_epilogue);
    mp.show_memory();

    std::cout << "Global data initial values:" << endl;
    std::cout << a[0] << "\t" << a[1] << "\t" << a[2] << endl;

    // Cast the address of our generated code to a function pointer and call the function
    void (*func)() = reinterpret_cast<void (*)()>(mp.executable_memory);
    func();

    std::cout << "Global data after test() was called from the generated code:" << endl;
    std::cout << a[0] << "\t" << a[1] << "\t" << a[2] << endl;
}
