 org $8000
 ldx #generate
 stx $fff6
 ldab #$20
 ldx #$8200
 ldy #$8000
 swi
 ldx #solution
 stx $fff6
 ldx #$8200
 ldab #$20
 ldy #0
 swi
 org $100
generate:
 ldaa $0,y
 staa $0,x
 inx
 iny
 decb
 bne generate
 ldx #0
 ldab #$20
zero:
 ldaa #0
 staa $0,x
 inx
 decb
 bne zero
 rti
solution:
 brclr $0,x,#%00010000,copy
 jmp continue
copy:
 ldaa $0,x
 staa $0,y
continue:
 inx
 iny
 decb
 bne solution
 rti