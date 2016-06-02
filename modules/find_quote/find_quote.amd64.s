
section .text
align 8
global _FindQuote
global FindQuote
global _CompareStrings
global CompareStrings

FindQuote:
_FindQuote:
    xor rax, rax
    jmp quote_start
not_quote:
    cmp byte [rdi], 0x22
    je maybe_quote
quote_inc:
    add rax, 1
    add rdi, 1
quote_start:
    cmp byte [rdi], 0
    jne not_quote

quote_end:
    ret

maybe_quote:
    cmp byte [rdi-1], 0x5C
    je quote_inc
    ret

CompareStrings:
_CompareStrings:
    mov eax, 1
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
    mov eax, 0
compare_end:
    ret
