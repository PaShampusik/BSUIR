       .model tiny
       .code
start: mov ax,@DATA
       mov ds,ax
       mov dx,offset message       
       mov ah,9
       int 21h       
       int 20h
       ret                 
       .data
message db "Hello World!", 10,13, "Lab made by Pavel Shchirov, group 153503$" 
       end start
