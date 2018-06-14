# notes
Things that I thought are worth remembering while working on this project.

- JIT compilation is a technique through which a program generates machine code at runtime, based on the user input
- A C++ program is AOT (ahead of time) compiled, which typically means that once the original code was compiled for a particular machine it can’t be changed at runtime
  - This is desirable from the security point of view.
- A simple, useful application, of a C++ JIT compiler is on the fly compilation of a new function that is based on other functions already defined in the original code
- for copying to memory pages (executable memory), use `mmap` with the multiple of `sysconf(_SC_PAGE_SIZE)`

## Steps
- Overview for step 1:
```
generate machine code for a function at runtime,  copy this code in a 
part of memory, mark it as executable, call it from C++.
```
- Step 1:
  - Write a simple program in assembly (`src/hello.c`)
  - compile (`as hello.s -o hello.o`) 
  - disassemble (`objdump -M intel -D hello.o`)
  - take the hex integers from the output (machine code) and use in C++ program
  -  store the message size from index 24 to 27 in the machine code vector (`append_message_size` method)
  - append message body to end of vector
  - allocate required memory size for the message
  - copy generated code to executable memory
  - get a pointer to the beginning of our executable code and cast it to a function pointer, after which we can use the generated function

- Overview for step 2: 

```
in practice, we won't use a vector to store machine instructions and 
then copy code to executable memory. we would directly write to the 
executable memory
```
- Step 2:
  - we will be creating a struct/class which will contain methods like `push`, which will internally push the machine code to the machine memory.
  - 
