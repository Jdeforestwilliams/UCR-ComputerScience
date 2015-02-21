;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 3 Exercise 3>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R1, ARR
LD R2, ARR
LD R5, End_character

Input
Getc
STR R0, R1, #0 
ADD R1, R1, #1
ADD R0, R0, R5
BRnp Input
INPUT_END

OUTPUT_LOOP
LDR R0, R2, #0
OUT
ADD R2, R2, #1
BRnp OUTPUT_LOOP
HALT
ARR .FILL x4000
End_character .fill #-10
