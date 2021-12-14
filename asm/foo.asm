segment .text

global _foo

_foo:
    xor     eax, eax
    mov     eax, 0x45
    ret
