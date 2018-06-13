.intel_syntax noprefix

mov rax, 1
mov rdi, 1
lea rsi, [rip + 0xa]

mov rdx, 17
syscall
ret
.string "Hello, Man Parvesh Singh Randhawa!!!!!!"
