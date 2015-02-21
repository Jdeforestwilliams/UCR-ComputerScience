;=================================================
; 
; Name: <DeForest-Williams, Joshua>
; Login id:Jdefo002
; 
; Assignment name: <Lab 2 Exercise 5>
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0,MSG_LOC
PUTS
HALT
MSG_LOC .fill x4000
.orig x4000
MSG .STRINGZ "High"
.END


