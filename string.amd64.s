
section .text
align 8
global _find_quote

_find_quote:
    xor rax, rax
not_quote:
    cmp byte [rdi], 0x22
    je maybe_quote
    inc rax
    cmp rax, rsi
    je quote_end
    inc rdi
    jmp not_quote
    
maybe_quote:
    cmp byte [rdi-1], 0x5C
    je not_quote

quote_end:
    ret
