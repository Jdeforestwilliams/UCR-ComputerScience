;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:Jdefo002 
; 
; Assignment name: Lab 4 Ex2
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R6, Counter
LD R0, Store
LD R1, Zero
Loop:
    STR R1, R0, #0
    ADD R1, R1, #1
    ADD R0, R0, #1
    ADD R3, R1, #-6
    BRnp Seventh 
        ADD R2, R1, #0
        Seventh
    ADD R6, R6, #-1
BRp Loop
LD R6, Counter 
LD R3, Store  
LD R4, Convert
Output: 
    STR R3, R1, #0
    ADD R1, R1, R4
    STR R1, R0, #0
    OUT
    ADD R6, R6, #-1
BRp Output
HALT
Counter .FILL #10
Zero .FILL #0 
Store .FILL x4000
Convert .FILL #48
.orig x4000
ARR .BLKW #10
