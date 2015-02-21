;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 2 Exercise 4>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0, HEX_61
LD R1, HEX_1A
LOOP
OUT
ADD R0, R0, #1
ADD R1, R1, #-1
BRp LOOP

HALT
HEX_61    .fill   x61 ;;97
HEX_1A    .fill   x1A ;;26
.end
