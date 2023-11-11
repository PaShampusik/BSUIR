 org $8000
 clra
 clrb
 ldx #0
 ORAA #%11111111
 ANDB #%00000000
 staa $10
 stab $11
 stx $12
 ldab #$4
loop: 
 rol $10
 rol $13
 rol $11
 rol $13
 decb
 bne loop
 ldab #$4
loop2: 
 rol $10
 rol $12
 rol $11
 rol $12
 decb
 bne loop2
 ldx $12 