
section .text
bits 64
align 8
global _skip_whitespace

%macro IS_WHITESPACE 2
    cmp byte %1, 0x20
    je %2
    cmp byte %1, 0xA
    je %2
    cmp byte %1, 0x9
    je %2
%endmacro

_skip_whitespace:
    ; r8 is the counter
    ; rsi is the len
    xor r8, r8
    
    ; We can't have 64-bit immediates except for in a mov?
    ; We use this later in the MMX comparisons
    mov r10, 0xFFFFFFFFFFFFFFFF

    ; We will need this later...
    movdqu xmm4, [eight_rnewlines wrt rip]
    movdqu xmm5, [eight_newlines wrt rip]
    movdqu xmm6, [eight_tabs wrt rip]
    movdqu xmm7, [eight_spaces wrt rip]
    
    cmp rsi, 16
    jge ws_sse_begin
    
    jmp ws_begin

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Perform an SEE whitespace test, testing 16 bytes at a time.           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ws_sse_init:

    mov r9, r8
    add r9, 16
    cmp r9, rsi
    jg ws_begin
    
    ; r9 already has the larger value because of the test
    mov r8, r9
    add rdi, 16

ws_sse_begin:
    
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
    
    pextrq rax, xmm0, 0
    pextrq r9, xmm0, 1
    and rax, r9
    cmp rax, r10
    je ws_sse_init

    ; Move to fine-grain testing...
    jmp ws_init

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test any remaining for whitespace when the string end is not aligned  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ws_begin:
    ; increment counter and string index
    inc rdi
    inc r8
ws_init:
    ; if counter == length, return
    cmp r8, rsi
    je ws_end

    IS_WHITESPACE [rdi], ws_begin

ws_end:
    mov rax, r8
    ret

%macro EIGHT_BYTES 1
    db %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1
%endmacro

section .data
    eight_newlines: EIGHT_BYTES '\n'
    eight_rnewlines: EIGHT_BYTES '\r'
    eight_tabs:     EIGHT_BYTES '\t'
    eight_spaces:   EIGHT_BYTES ' '
