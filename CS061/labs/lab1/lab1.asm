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
.orig x3000
;--------------
;Instructions 
;--------------
LD R1, DEC_0        ; R1 <-- #0  (clear the "answer" register)
LD R2, DEC_12       ; R2 <-- #12 (the number to multiply by six)
LD R6, DEC_6        ; R6 <-- #6 (loop counter)

DO_WHILE_LOOP_1 
   ADD R1, R1, R2  ; R1 <-- R1 + R2
   ADD R6, R6, #-1  ; R6 <-- R6-1 (update loop counter. R6 is now the LMR)
   BRp DO_WHILE_LOOP_1   ; if (R6>0) {jump to DO_WHILE_LOOP_1 }
END_DO_WHILE_LOOP_1
HALT                ; Stop Execution of progarm

;----------
; Data
;----------
DEC_0    .fill #0
DEC_6    .fill   #6
DEC_12   .fill   #12
.end
