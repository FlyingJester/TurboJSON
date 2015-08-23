
section .text
align 8
global _SkipWhitespace 
    
skip_whitespace_simple:
    cmp rax, rsi
    je ws_end2
    cmp byte [rdi], 0x20
    je ws_ok2
    cmp byte [rdi], 0x0A
    je ws_ok2
    cmp byte [rdi], 0x09
    je ws_ok2
    cmp byte [rdi], 0x0D
    jne ws_end2
    
    inc rax
    inc rdi
    
ws_start2:

    cmp byte [rdi], 0x20
    je ws_ok2
    cmp byte [rdi], 0x0A
    je ws_ok2
    cmp byte [rdi], 0x09
    je ws_ok2
    cmp byte [rdi], 0x0D
    jne ws_end2
    
ws_ok2:
    
    inc rax
    inc rdi
    
    cmp rax, rsi
    jl ws_start2

ws_end2:
    ret

; For our purposes, it's faster to check the first two bytes unrolled.
_SkipWhitespace:
    xor rax, rax
; Optimized for the first byte being not whitespace
    cmp byte [rdi], 0x20
    je skip_ws_second_byte
    cmp byte [rdi], 0x0A
    je skip_ws_second_byte
    cmp byte [rdi], 0x09
    je skip_ws_second_byte
    cmp byte [rdi], 0x0D
    je skip_ws_second_byte
    ret

skip_ws_second_byte:
    inc rdi
    inc rax
; Optimized for the second byte being not whitespace
    cmp byte [rdi], 0x20
    je skip_ws_real
    cmp byte [rdi], 0x0A
    je skip_ws_real
    cmp byte [rdi], 0x09
    je skip_ws_real
    cmp byte [rdi], 0x0D
    je skip_ws_real
    ret
    
skip_ws_real:
    ; Technically 16 is enough to work with, but this will be slightly slower for the overhead.
    ; We add two for the two unrolled bytes
    cmp rsi, 50
    jle skip_whitespace_simple

skip_whitespace_sse:
    ; We can't have 64-bit immediates except for in a mov?
    ; We use this later in the MMX comparisons
    mov r9, 0xFFFFFFFFFFFFFFFF    
    ; We will need this later...
    movdqu xmm4, [eight_rnewlines wrt rip]
    movdqu xmm5, [eight_newlines wrt rip]
    movdqu xmm6, [eight_tabs wrt rip]
    movdqu xmm7, [eight_spaces wrt rip]
    mov r8, rax
jmp sse_ws_cmp
sse_ws_inc:
    add rax, 16
    add rdi, 16
sse_ws_cmp:
    
    ; Check if we have 16 more bytes to go.
    add r8, 16
    cmp rsi, r8
    jle skip_whitespace_simple

    movdqu xmm0, [rdi]
    movdqu xmm1, xmm0
    movdqu xmm2, xmm0
    movdqu xmm3, xmm0
    
    pcmpeqb xmm0, xmm4
    pcmpeqb xmm1, xmm5
    pcmpeqb xmm2, xmm6
    pcmpeqb xmm3, xmm7
    
    por xmm0, xmm1
    por xmm0, xmm2
    por xmm0, xmm3
    
    pextrq r10, xmm0, 0
    pextrq r8, xmm0, 1
    and r10, r8
    cmp r10, r9
    je sse_ws_inc

    jmp skip_whitespace_simple

%macro SIXTEEN_BYTES 1
    db %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1
%endmacro

section .data
    eight_newlines:  SIXTEEN_BYTES 0x09
    eight_rnewlines: SIXTEEN_BYTES 0x0D
    eight_tabs:      SIXTEEN_BYTES 0x0A
    eight_spaces:    SIXTEEN_BYTES 0x20
