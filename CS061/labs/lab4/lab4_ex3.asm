;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:Jdefo002 
; 
; Assignment name: Lab 4 Ex3
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R6, Counter
LD R3, Store
LD R1, Zero
ADD R1, R1, #1
STR R1, R3, #0
Loop:
    ADD R1, R1, R1
    ADD R3, R3, #1
    STR R1, R3, #0
    ADD R4, R6, #-5
    BRnp Seventh 
        ADD R2, R1, #0
        Seventh
    ADD R6, R6, #-1
BRp Loop
HALT
Counter .FILL #10
Zero .FILL #0 
Store .FILL x4000
.orig x4000
ARR .BLKW #10

