section .text
bits 64
align 8
global _TrueAtom
global _FalseAtom
global _NullAtom

_TrueAtom:
    mov rax, 0
    cmp byte [rdi], 't'
    jne cmp_end
    cmp byte [rdi+1], 'r'
    jne cmp_end
    cmp byte [rdi+2], 'u'
    jne cmp_end
    cmp byte [rdi+3], 'e'
    jne cmp_end

    mov rax, 1
    ret

_FalseAtom:
    mov rax, 0
    cmp byte [rdi], 'f'
    jne cmp_end
    cmp byte [rdi+1], 'a'
    jne cmp_end
    cmp byte [rdi+2], 'l'
    jne cmp_end
    cmp byte [rdi+3], 's'
    jne cmp_end
    cmp byte [rdi+4], 'e'
    jne cmp_end

    mov rax, 1
    ret

_NullAtom:
    mov rax, 0
    cmp byte [rdi], 'n'
    jne cmp_end
    cmp byte [rdi+1], 'u'
    jne cmp_end
    cmp byte [rdi+2], 'l'
    jne cmp_end
    cmp byte [rdi+3], 'l'
    jne cmp_end

    mov rax, 1
    ret

cmp_end:
    ret