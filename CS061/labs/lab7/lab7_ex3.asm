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
LD R0, orig_message
PUTS
AND R0, R0, #0 
LD R6, SUB_GET_STRING
JSRR R6
LD R6, SUB_IS_A_PALINDROME
JSRR R6
ADD R4, R4, #0
BRp true_palindrome
LD R0, not_palindrome_message
PUTS
BRnzp exit
true_palindrome
LD R0, palindrome 
PUTS
exit
HALT

;;;data
SUB_GET_STRING .FILL x3200 
SUB_IS_A_PALINDROME .FILL x3400
orig_message .FILL x6000
palindrome .FILL x602A
not_palindrome_message .FILL x604A

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
;ADD R5, R5, #-1 ;; to skip the 0 at the end of the array
AND R4, R4, #0 ;; to set it back to 0 for future use
LD R7, BACKUP_R7_3200
RET

;;;data
BACKUP_R7_3200 .BLKW #1
string_array .FILL x5000
enter_check .FILL #-10 

.orig x3400
ST R7, BACKUP_R7_3400
LD R6, string_array_palindrome
ADD R2, R2, R6
ADD R2, R2, R5
LD R1, right_shift
JSRR R1
AND R4, R4, #0
ADD R4, R1, R4
ADD R4, R4, #1
is_palindrome
AND R0, R0, #0
LDR R3, R2, #0
LDR R1, R6, #0
LD R0, to_lower
JSRR R0
LD R0, is_other
JSRR R0

NOT R1, R1
ADD R1, R1, #1
AND R0, R0, #0
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
string_array_palindrome .FILl x5000
right_shift .fill x3600
to_lower .FILL x3800
is_other .FILL x4000

.orig x3600
ST R7, BACKUP_R7_3600
ST R2, BACKUP_R2_3600
ST R4, BACKUP_R4_3600
ST R3, BACKUP_R3_3600
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

;;; to lower
.orig x3800
ST R7, BACKUP_R7_3800
ST R2, BACKUP_R2_3800
ST R4, BACKUP_R4_3800 
ST R5, BACKUP_R5_3800 
ST R6, BACKUP_R6_3800 
LD R0, upper_a
ADD R0, R1, R0
BRn r1_not_upper
LD R0, upper_z
ADD R0, R1, R0
BRp r1_not_upper
LD R0, conversion
ADD R1, R0, R1
r1_not_upper

;;; test r3
LD R0, upper_a
ADD R0, R3, R0
BRn r3_not_upper
LD R0, upper_z
ADD R0, R3, R0
BRp r3_not_upper
LD R0, conversion
ADD R3, R0, R3
r3_not_upper

LD R2, BACKUP_R2_3800
LD R4, BACKUP_R4_3800 
LD R5, BACKUP_R5_3800 
LD R6, BACKUP_R6_3800 
LD R7, BACKUP_R7_3800
RET
;;;data
BACKUP_R7_3800 .BLKW #1
BACKUP_R2_3800 .BLKW #1
BACKUP_R4_3800 .BLKW #1
BACKUP_R5_3800 .BLKW #1
BACKUP_R6_3800 .BLKW #1
lower_a .FILL #-97
upper_a .FILL #-65
lower_Z .FILL #-122
upper_z .FILL #-90 
conversion  .FILL #32


;;is_other
.orig x4000
ST R7, BACKUP_R7_4000
ST R4, BACKUP_R4_4000 
ST R5, BACKUP_R5_4000 
loop_r1_r6_symbol
LD R0, dec_zero
ADD R0, R1, R0
BRn r1_r6_symbol
LD R0, nine
ADD R0, R1, R0
BRnz r1_clear
LD R0, upper_A
ADD R0, R1, R0
BRn r1_r6_symbol
LD R0, upper_Z
ADD R0, R1, R0
BRnz r1_clear
LD R0, Lower_a
ADD R0, R1, R0
BRn r1_r6_symbol
LD R0, Lower_z
ADD R0, R1,R0
BRnz r1_clear 

r1_r6_symbol
ADD R6, R6, #1  
LDR R1, R6, #0
LD R4, check_case_again
JSRR R4
BRnzp loop_r1_r6_symbol
r1_clear
loop_r3_r2_symbol
LD R0, dec_zero
ADD R0, R3, R0
BRn r3_r2_symbol
LD R0, nine
ADD R0, R3, R0
BRnz valid
LD R0, upper_A
ADD R0, R3, R0
BRn r3_r2_symbol
LD R0, upper_Z
ADD R0, R1, R0
BRnz valid
LD R0, Lower_a
ADD R0, R3, R0
BRn r3_r2_symbol
LD R0, Lower_z
ADD R0, R3,R0
BRnz valid

r3_r2_symbol
ADD R2, R2, #-1  
LDR R3, R2, #0
LD R4, check_case_again
JSRR R4
BRnzp loop_r3_r2_symbol
valid
LD R4, BACKUP_R4_4000 
LD R5, BACKUP_R5_4000 
LD R7, BACKUP_R7_4000
RET
;;;data
BACKUP_R7_4000 .BLKW #1
BACKUP_R4_4000 .BLKW #1
BACKUP_R5_4000 .BLKW #1
dec_zero .FILL #-48
nine .FILL #-57
upper_A .FILL #-65
upper_Z .FILL #-90
Lower_a .FILL #-97
Lower_z .FILL #-122
check_case_again .FILL x3800
.orig x6000
message .STRINGZ "Please type in a string to be tested\n" 

.orig x602A
is_palindrome_stringz .STRINGZ "Your input is a palindrome\n"

.orig x604A
is_not_palindrome .STRINGZ "Youre input is not a palindrome\n"
