;=================================================
; 
; Name: Deforest-Williams,Joshua	
; Login id:Jdefo002
; 
; Assignment name: Lab 1
; Lab section: <021>
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
;--------------------------------------------------
;REG VALUES      R0  R1  R2  R3  R4  R5  R6  R7
;-------------------------------------------------- 
;Pre-loop        0   6   12  0   0   0   0   1168
;Iteration 01    0   5   12  12  0   0   0   1168
;Iteration 02    0   4   12  24  0   0   0   1168 
;Iteration 03    0   3   12  36  0   0   0   1168
;Iteration 04    0   2   12  48  0   0   0   1168
;Iteration 05    0   1   12  60  0   0   0   1168
;End of program  0   0   12  72  0   0   0   DEC_0 
;-------------------------------------------------- 
.orig x3000
;--------------
;Instructions 
;--------------
LD R1, DEC_6        ; R1 <-- #6  (clear the "answer" register)
LD R2, DEC_12       ; R2 <-- #12 (the number to multiply by six)
LD R3, DEC_0        ; R3 <-- #0 (loop counter)

DO_WHILE_LOOP_1 
   ADD R3, R3, R2  ; R3 <-- R3 + R2
   ADD R1, R1, #-1  ; R1 <-- R1-1 (update loop counter. R6 is now the LMR)
   BRp DO_WHILE_LOOP_1   ; if (R1>0) {jump to DO_WHILE_LOOP_1 }
END_DO_WHILE_LOOP_1
HALT                ; Stop Execution of progarm

;----------
; Data
;----------
DEC_0    .fill #0
DEC_6    .fill   #6
DEC_12   .fill   #12
.end
