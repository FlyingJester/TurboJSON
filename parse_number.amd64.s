
section .text
align 8

global _DecStrToNumber
global _OctStrToNumber
global _HexStrToNumber
global _BinStrToNumber

extern _IsDecDigit

; _ToNumber(const char *string, int64_t *dest);

%macro BEGIN 0
    xor rax, rax
    mov r9, rdi
%endmacro

%macro END 0
    sub rdi, r9
    mov rdi, [rsi]
    ret
%endmacro

%macro GET 1
    mov %1, [rdi]
    and %1, 0xFF
%endmacro

%macro GREATER_THAN_JUMP 3
    cmp %1, %2
    jg %3
%endmacro

%macro LESS_THAN_JUMP 3
    cmp %1, %2
    jl %3
%endmacro

_DecStrToNumber:
    BEGIN
dec_check:
    
    GET r8
    
    LESS_THAN_JUMP r8, '0', dec_done
    
    sub r8, '0'
    
    GREATER_THAN_JUMP r8, 9, dec_done
    
    imul rax, 10
    add rax, r8
    
    add rdi, 1
    jmp dec_check

dec_done:
    END

hex_to_lower_case:
    sub r8, 0x20
    jmp hex_handle_chars

hex_char_to_num:
    GREATER_THAN_JUMP r8, 'f', hex_done
    sub r8, 'a'
    jmp hex_numeric

_HexStrToNumber
    BEGIN
hex_check:
    GET r8

    LESS_THAN_JUMP r8, '0', hex_done

    GREATER_THAN_JUMP r8, 'A'-1, hex_to_lower_case

hex_handle_chars:

    GREATER_THAN_JUMP r8, 'a'-1, hex_char_to_num
    GREATER_THAN_JUMP r8, '9', hex_done
    
    sub r8, '0'

hex_numeric:
    shl rax, 4
    add rax, r8
    
    inc rdi
    
    jmp hex_check

hex_done:
    END
