;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:jdefo002
; 
; Assignment name: Lab 6 Ex3
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.ORIG x3000
LD R1, input
LD R6, subroutine
JSRR R6
HALT
;;;;data
input .FILL #-256
subroutine .FILL x3200

.orig x3200
ST R7, BACKUP_R7_3200
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
LD R7, BACKUP_R7_3200
RET
;;;;data
BACKUP_R7_3200 .BLKW #1
loop_counter .FILL #15
msb_mask .FILL x8000
