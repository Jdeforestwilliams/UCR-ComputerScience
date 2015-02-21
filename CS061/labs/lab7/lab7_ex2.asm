;=================================================
; 
; Name: DeForest-Williams
; Login id:Jdefo002
; 
; Assignment name: lab 7 ex 2
; Lab section: 021
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R6, SUB_GET_STRING
JSRR R6
LD R6, SUB_IS_A_PALINDROME
JSRR R6
HALT

;;;data
SUB_GET_STRING .FILL x3200 
SUB_IS_A_PALINDROME .FILL x3400
.orig x3200
ST R7, BACKUP_R7_3200
LD R6, string_array
AND R5, R5, #0   ;;;; to be used for counter
input_loop
LD R4, enter_check
Getc
ADD R4, R0, R4
BRz break_out_of_input
STR R0, R6, #0
ADD R6, R6, #1
ADD R5, R5, #1
BRnzp input_loop
break_out_of_input
LD R0, string_array
PUTS
ADD R5, R5, #-1 ;; to skip the 0 at the end of the array
AND R4, R4, #0 ;; to set it back to 0 for future use
LD R7, BACKUP_R7_3200
RET

;;;data
BACKUP_R7_3200 .BLKW #1
string_array .FILL x4000
enter_check .FILL #-10 

.orig x3400
ST R7, BACKUP_R7_3400
LD R6, string_array_palindrome
ADD R2, R2, R6
ADD R2, R2, R5
LD R1, right_shift
JSRR R1
ADD R4, R1, R4
is_palindrome
LDR R3, R2, #0
LDR R1, R6, #0
NOT R1, R1
ADD R1, R1, #1
ADD R0, R1, R3
BRnp not_palindrome
ADD R2, R2, #-1
ADD R6, R6, #1
ADD R4, R4, #-1
BRp is_palindrome
AND R4, R4, #0
ADD R4, R4, #1
BRnzp FINISH

not_palindrome 
AND R4, R4, #0
BRnzp FINISH

FINISH
LD R7, BACKUP_R7_3400
RET

;;data 
BACKUP_R7_3400 .BLKW #1
string_array_palindrome .FILl x4000
right_shift .fill x3600

input .FILL #-256

.orig x3600
ST R7, BACKUP_R7_3600
ST R2, BACKUP_R2_3600
ST R3, BACKUP_R3_3600
ST R4, BACKUP_R4_3600
ST R5, BACKUP_R5_3600
ST R6, BACKUP_R6_3600
AND R1, R1, #0
ADD R1, R1, R5
LD R4, loop_counter
LD R5, msb_mask
ADD R1, R1, #0
BRzp skip_negative
AND R3, R3, #0
ADD R3, R1, R3
NOT R1, R1
ADD R1, R1, #1
skip_negative
ADD R2, R1, #0
AND R2, R2, R5
BRz zero
ADD R1, R1, R1
ADD R1, R1, #1
BRnzp else
zero
ADD R1, R1, R1
else
big_loop
ADD R2, R1, #0
AND R2, R2, R5
BRz zero_1
ADD R1, R1, R1
ADD R1, R1, #1
BRnzp else_1
zero_1
ADD R1, R1, R1
else_1
ADD R4, R4, #-1
BRp big_loop
ADD R3, R3, #0
BRzp skip_negative_change_back
Not R1, R1
ADD R1, R1, #1
skip_negative_change_back
;NOT R5, R5
;ADD R5, R5, #1
;AND R1, R1, R5
LD R7, BACKUP_R7_3600
LD R2, BACKUP_R2_3600
LD R3, BACKUP_R3_3600
LD R4, BACKUP_R4_3600
LD R5, BACKUP_R5_3600
LD R6, BACKUP_R6_3600
RET
;;;;data
BACKUP_R7_3600 .BLKW #1
BACKUP_R2_3600 .BLKW #1
BACKUP_R3_3600 .BLKW #1
BACKUP_R4_3600 .BLKW #1
BACKUP_R5_3600 .BLKW #1
BACKUP_R6_3600 .BLKW #1
loop_counter .FILL #14
msb_mask .FILL x8000
