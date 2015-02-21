;=================================================
; 
; Name: DeForest-Williams
; Login id:Jdefo002
; 
; Assignment name: lab 7 ex 1
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
HALT

;;;data
SUB_GET_STRING .FILL x3200 

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
LD R7, BACKUP_R7_3200
RET

;;;data
BACKUP_R7_3200 .BLKW #1
string_array .FILL x4000
enter_check .FILL #-10 
