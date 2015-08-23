
section .text
bits 64
align 8
global _skip_whitespace

_skip_whitespace:
    ; rdi is the string, rsi is the length of the string
    ; rax is the counter
    xor r8, r8
    ; skip increment the first time
    jmp ws_init
is_whitespace:
    ; increment counter and string index
    inc rdi
    inc r8
ws_init:
    ; if counter == length, return
    cmp r8, rsi
    je ws_end

    ; Check against space, \t, and \n
    cmp byte [rdi], 0x20
    je is_whitespace
    cmp byte [rdi], 0xA
    je is_whitespace
    cmp byte [rdi], 0x9
    je is_whitespace
ws_end:
    mov rax, r8
    ret
