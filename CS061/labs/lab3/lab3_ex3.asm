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
LD R0, MSG_LOC
PUTS
LD R6, Counter 
LD R4, Data_ptr
LD R5, Output_ptr
DO_WHILE_LOOP_1 
   GETC
   STR R0, R4, #0 
   ADD R4, R4, #1  
   ADD R6, R6, #-1  ; R6 <-- R6-1 (update loop counter. R6 is now the LMR)
   BRp DO_WHILE_LOOP_1   ; if (R6>0) {jump to DO_WHILE_LOOP_1 }
END_DO_WHILE_LOOP_1
LD R6, Second_count
LD R0,Newline
OUT
OUTPUT_LOOP
LDR R0, R5, #0
OUT
LD R0,Newline
OUT
ADD R5, R5, #1
ADD R6, R6, #-1  ; R6 <-- R6-1 (update loop counter. R6 is now the LMR)
BRp OUTPUT_LOOP
HALT
MSG_LOC .fill x400A
Data_ptr .fill x4000
Output_ptr .fill x4000
Counter .fill #10
Second_count .fill #10
Newline .fill x0a
;;Remote Data
.orig x4000
ARR1 .BLKW #10
MSG .STRINGZ "Please Input Exactly 10 Characters"
