;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 2 Exercise 3>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R5, DEC_65
LD R6, HEX_41
LDR R3, R5, #0
LDR R4, R6, #0
ADD R3, R3, #1
ADD R4, R4, #1
STR R3, R5, #0
STR R4, R6, #0
HALT
DEC_65    .fill   x4000
HEX_41    .fill   x4001
;; 
;; Remote data
;;
.orig x4000
.fill   #65
.fill   x41
.end
