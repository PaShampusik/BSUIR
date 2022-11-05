; multi-segment executable file template.

data segment
    ; add your data here!
    enter_input_string db "Enter string to manipulate: $"
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
    mov ax, @DATA
    mov ds, ax
    mov dx, offset enter_input_string
    mov ah, 9
    int 21h 
    mov ah, 0Ah
    int 21h
    int 20h
    
ends

end start ; set entry point and stop the assembler.
