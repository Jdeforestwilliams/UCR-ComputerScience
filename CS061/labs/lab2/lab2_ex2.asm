;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 2 Exercise 2>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LDI R3, DEC_65
LDI R4, HEX_41
ADD R3, R3, #1
ADD R4, R4, #1
STI R3, DEC_65
STI R4, HEX_41
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
