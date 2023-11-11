 data segment
    enterance_msg db "This program find most common number in the array of n integers",10,13, "|||||FROM 10 TO 99|||||", 10, 13, "Now enter n integers : ", 10, 13, "$"
    array db 250 DUP(8) 
    count_msg db 10, 13, "Enter number of members n in array: $"    
    count_ db 3 DUP(0) 
    next_line db 10, 13, "$"
    buf db "   $"
    array_member_msg db 10, 13,"Enter array[$"  
    array_member db 49 
    end_of_array_member db "]: $" 
    buffer db 5 DUP(3), "$"
    msg_1 db 10, 13, "Most common number is: " 
    most_common_number db 4 DUP(0), "$" 
    msg db "Most common number was faced "      
    counter db 0
    msg_ db " times$"
    under_analys_msg db 10, 13, "Wait, your data is under analysis..$"
    smth_went_wrong_msg db 10, 13, "Something went wrong :($"
    input_error_msg db 13, 10, "Your input is not correct,", 13, 10, "Try again: $"
    succesful_validation_msg db 13,10, "Your data is correct! We started analisys of your data, it can take some time.. ", 10, 13, "$"
ends

stack segment
    dw   128  dup(0)
ends

print macro str
    mov ah, 9
    lea dx, str
    int 33 
endm
 
input macro str, count
    mov ah, 10
    lea dx, str
    mov bx, 0
    mov bx, dx
    mov [bx],count       
    int 33
    lea di, str
    mov bl, str[1]
    mov [di + bx  + 2], '$'
endm 

code segment
start:
;************ input and validation down here ***************
    mov ax, data
    mov ds, ax
    mov es, ax
    print enterance_msg
    mov cx, 0     
    print count_msg 
    input buf, 2    
    print next_line
    mov cl, buf[2]
    sub cx, 30h 
    mov bx, 0
    mov bl, 0
    cmp cl, bl
    jg next_validation__
    jmp symbol_error
    next_validation__:
    mov bl, 10 
    cmp bl, cl
    jg go_
    jmp symbol_error
go_:
    mov [count_], cl               
    lea di, array
    lea si, buffer[2]
filling:
    push di
    print array_member_msg
    print array_member
    input buffer, 3
    mov bx, 0
    mov bl, 48
    cmp buffer[2],bl
    jg next_validation
    jmp symbol_error
symbol_error:
    print input_error_msg
    mov array_member, 48
    jmp start 
next_validation:
    mov bl, 58 
    cmp bl, buffer[2]
    jg next_number
    jmp symbol_error 
next_number:
    mov bx, 0
    mov bl, 47
    cmp buffer[3],bl
    jg next_validation_1
    jmp symbol_error
next_validation_1:
    mov bl, 58 
    cmp bl, buffer[3]
    jg gogogo
    jmp symbol_error
gogogo:    
    print next_line
    pop di
    mov bx, 0
    mov bl, [si]
    mov [di], bl    
    inc di 
    mov bx, 0
    mov bl, [si+1]
    mov [di], bl
    inc di 
    inc array_member 
    mov al,[si+1]
    mov ah,[si]
    push ax
    mov ax, 0         ;pusing our numbers to stack 
    loop filling 
    
    print under_analys_msg
    
    mov dx, 0
    mov cl, count_
finding:        
    lea di, array     
    pop ax 
    push cx
    mov cx, 0
    mov cl, count_    
finding_1:   
    cmp ah, [di]
    jz next:
    inc di
    jmp go
  next:
    inc di
    cmp al, [di]
    jz find
    jmp go
find:
    inc dl         ;counter of finding times    
go: 
    inc di
    loopne finding_1 
    
    cmp dl, dh
    jge new_max
    jmp not_max
new_max:
    mov dh, 0
    mov dh, dl
    mov most_common_number[0], ah
    mov most_common_number[1], al
not_max:
    mov dl, 0
    mov ax, 0
    LAHF                      
    AND  AH, 10111111b    
    SAHF
    mov ax, 0
    pop cx
    loopne finding 
    
    lea di, counter
    add dh, 48
    mov [di], dh 
    
    print msg_1
    print next_line   
    print msg
    int 20h       ;end of the program
ends

end start ; set entry point and stop the assembler.
