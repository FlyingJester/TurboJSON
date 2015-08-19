
section .text
align 8

global _IsDecDigit
global _IsHexDigit
global _IsOctDigit
global _IsBinDigit
global _IsHex
global _IsOct

_IsOct:
    xor rax, rax
    mov ax, word [rdi]
    sub ax, '0'
    ret

_IsHex:
    cmp word [rdi], 0x3078
    je is_digit
    cmp word [rdi], 0x3058
    je is_digit
    mov rax, 0
    ret

_IsBinDigit:
    cmp di, '0'
    je is_digit

    cmp di, '1'
    je is_digit

    mov rax, 0
    ret

_IsHexDigit:
    cmp di, 'f'
    jg not_digit

    cmp di, 'A'
    jl _IsDecDigit

    cmp di, 'G'
    jl is_digit

    cmp di, 'a'
    jge is_digit

 ; Fallthrough

not_digit:
    mov rax, 0
    ret


_IsOctDigit:
    cmp di, '7'
    jg not_digit

 ; Fallthrough

_IsDecDigit:
    cmp di, '0'
    jl not_digit
    
    cmp di, '9'
    jg not_digit
    
 ; Fallthrough

is_digit:
    mov rax, 1
    ret

