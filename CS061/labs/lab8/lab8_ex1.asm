
;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:Jdefo002
; 
; Assignment name: lab 8 ex 1
; Lab section: 021
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0, SUB_TO_UPPER
JSRR R0
HALT
;;; data
SUB_TO_UPPER .FILL x3200

.orig x3200
ST R7, BACKUP_R7_3200
LD R6, string_array
LD R1, conversion  
AND R5, R5, #0   ;;;; to be used for counter
input_loop
LD R4, enter_check
Getc
ADD R4, R0, R4
BRz break_out_of_input
LD R2, lower_a
LD R3, lower_z
ADD R2, R0, R2
BRn SKIP
ADD R3, R0, R3
BRp SKIP
ADD R0, R1, R0
SKIP
STR R0, R6, #0
ADD R6, R6, #1
ADD R5, R5, #1
BRnzp input_loop
break_out_of_input
LD R0, string_array
PUTS
LD R0, newline
OUT
AND R4, R4, #0 ;; to set it back to 0 for future use
LD R7, BACKUP_R7_3200
RET

;;;data
BACKUP_R7_3200 .BLKW #1
string_array .FILL x5000
enter_check .FILL #-10 
conversion.FILL #-32
lower_a .FILL #-97
lower_z .FILL #-122
newline .fill x0a
