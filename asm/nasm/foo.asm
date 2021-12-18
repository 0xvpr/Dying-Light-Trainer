segment .text

global foo

foo:
    xor     rax, rax
    mov     rax, 0x45
    ret
