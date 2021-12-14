segment .text

global foo

foo:
    xor     eax, eax
    mov     eax, 0x45
    ret
