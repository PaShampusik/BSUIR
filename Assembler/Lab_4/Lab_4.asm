 org $8000
 ldx #$8000
 ldy #$8301
 ldab #9 ;<------
;count of bites -1|
 
fill:
 ldaa $0,x
 staa $0,y
 inx
 iny
 decb
 bne fill


 ldx #$8301
 ldab #5


loop:
 pshb
 ldaa $0,x
 ldab $0,y
 staa $8311
 stab $8312
 ldab #8
loop2:
 rol $8311
 ror $8312
 decb
 bne loop2
 rol $8311
 ldaa $8311
 ldab $8312
 staa $0,x
 stab $0,y
 inx
 dey
 pulb
 decb
 bne loop
 


 