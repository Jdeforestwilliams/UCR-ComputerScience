;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 3 Exercise 1>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R5, Data_ptr
LDR R3, R5, #0
LDR R4, R5, #1
ADD R3, R3, #1
ADD R4, R4, #1
STR R3, R5, #0
STR R4, R5, #1
HALT
Data_ptr  .fill   x4000
;; 
;; Remote data
;;
.orig x4000
.fill   #65
.fill   x42
.end
