;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:jdefo002
; 
; Assignment name: Lab 6 Ex2
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
AND R1, R1, #0
AND R5, R5, #0

LD R0, message
PUTS
GETC
ADD R1, R0, R1
LD R6, subroutine 
JSRR R6
LD R0, output
PUTS 
AND R0, R0, #0
ADD R0, R0, R5
LD R3, convert
ADD R0, R0, R3
OUT
HALT

;;;data
message .FILL x3100
output .FILL x3150
subroutine .FILL x3200
convert .FILL #48
.orig x3100
orig_message   .STRINGZ "Input a single character from the keyboard\n" 
.orig x3150
output_1 .STRINGZ "The number of 1's is: "
.orig x3200
ST R7, BACKUP_R7_3200
ST R6, BACKUP_R6_3200
ST R0, BACKUP_R0_3200
LD R3, two_n_counter
big_loop
AND R6, R6, #0
ADD R6, R1, R6
AND R2, R2, #0
ADD R2, R2, R3
LD R4, one
two_n_loop
ADD R4, R4, R4 
ADD R2, R2, #-1
BRp two_n_loop
NOT R4, R4
ADD R4, R4, #1
ADD R6, R4, R6
BRn Else
ADD R1, R1, R4
ADD R5, R5, #1
Else
ADD R3, R3, #-1
BRp big_loop
LD R6, BACKUP_R6_3200
LD R0, BACKUP_R0_3200
LD R7, BACKUP_R7_3200
RET
;;;;data;;;;
BACKUP_R7_3200 .BLKW #1
BACKUP_R0_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
two_n_counter .FILL # 15
one .FILL #1
zero .FILL #0

