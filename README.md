<div align="center">
  <h1>cppjit</h1>

  <a href="https://travis-ci.org/manparvesh/cppjit/builds" target="_blank"><img src="https://img.shields.io/travis-ci/manparvesh/cppjit.svg?style=for-the-badge" alt="Build Status"></a> 
  <a href="https://manparvesh.mit-license.org/" target="_blank"><img src="https://img.shields.io/badge/license-MIT-blue.svg?longCache=true&style=for-the-badge" alt="License"></a> 
  <p>A minimal JIT compiler for X86-64 written in C++</p>
</div>

## Building

### Requirements
- C++ 17
- cmake
- Preferably a UNIX environment, since it's not tested in Windows (only tested in Ubuntu with `g++ 7.3.0`).

### Compilation
- Clone this repository
- Navigate to the cloned repo on your system and run: `mkdir build && cd build`
- `cmake ..`
- `make`

---

## References
- [Writing a minimal x86-64 JIT compiler in C++](https://solarianprogrammer.com/2018/01/10/writing-minimal-x86-64-jit-compiler-cpp/)