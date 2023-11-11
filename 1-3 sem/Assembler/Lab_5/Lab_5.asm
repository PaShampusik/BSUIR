       .model small
       .stack 100h
       .code
start: mov ax,@DATA
       mov ds,ax
       mov dx,offset message       
       mov ah,9
       int 21h
       mov dx, offset message_1
       int 21h       
       int 20h                 
       .data
message db "Hello World!", 10, 13, "$"
message_1 db "Lab made by Pavel Shchirov, group 153503$" 
       end start