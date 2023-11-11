 org $8000
 ldab #$02
p0 
 ldy 0,x
 bsr p2
p1 
 nop
p2
 ldy 0,x 
 jmp $8007

    