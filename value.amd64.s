
section .text
bits 64
align 8
global _Turbo_Value
extern _Turbo_String
extern _Turbo_Number
extern _Turbo_Object
extern _Turbo_Array
extern _Turbo_ValueUtil

; const char *Turbo_Value(struct Turbo_Value *to, const char *in, const char *const end){

_Turbo_Value:
    cmp byte [rsi], '"'
    je _Turbo_String
    cmp byte [rsi], '['
    je _Turbo_Array
    cmp byte [rsi], '{'
    je _Turbo_Object
    cmp byte [rsi], '0'
    jl _Turbo_ValueUtil
    cmp byte [rsi], '9'
    jg _Turbo_ValueUtil
    jmp _Turbo_Number
