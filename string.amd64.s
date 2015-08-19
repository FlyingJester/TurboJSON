
section .text
align 8
global _find_quote
global _compare_strings

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

 ; uint64_t compare_strings(const char *in, const char *to, uint64_t to_length);

_compare_strings:
    mov rax, 1
compare_begin:    
    cmp rdx, 0
    jz compare_end
    mov cx, word [rdi]
    cmp cx, word [rdx]
    jne compare_fail
    inc rdi
    inc rsi
    dec rdx
    jmp compare_begin
compare_fail:
    mov rax, 0
compare_end:
    ret
