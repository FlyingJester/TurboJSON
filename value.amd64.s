
section .text
bits 64
align 8
global Turbo_Value
extern Turbo_String
extern Turbo_Number
extern Turbo_Object
extern Turbo_Array
extern Turbo_ValueUtil

; const char *Turbo_Value(struct Turbo_Value *to, const char *in, const char *const end){

_Turbo_Value:
Turbo_Value:
    cmp byte [rsi], '"'
    je Turbo_String
    cmp byte [rsi], '['
    je Turbo_Array
    cmp byte [rsi], '{'
    je Turbo_Object
    cmp byte [rsi], '-'
    je Turbo_Number
    cmp byte [rsi], '0'
    jl Turbo_ValueUtil
    cmp byte [rsi], '9'
    jg Turbo_ValueUtil
    jmp Turbo_Number
