;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: lab 9 ex3
; Lab section: 021
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.ORIG x3000
LD R3, capacity
LD R2, top
LD R1, stack_addr
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
AND R6, R6, #0
ADD R6, R6, #2
LD R0, SUB_STACK_PUSH
JSRR R0
AND R6, R6, #0
ADD R6, R6, #3
LD R0, SUB_STACK_PUSH
JSRR R0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
AND R6, R6, #0

LD R0, SUB_STACK_PUSH
JSRR R0
LD R0, SUB_STACK_PUSH
JSRR R0
LD R0, asterisk
PUTS
GETC
OUT
LD R0, RPN_MULTIPLY
JSRR R0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
AND R5, R5, #0
ADD R5, R6, #0
AND R6, R6, #0
ADD R6, R6, #4
LD R0, SUB_STACK_PUSH
JSRR R0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LD R0, PRINT_DECIMAL
JSRR R0
HALT
SUB_STACK_PUSH .fill x3200

RPN_MULTIPLY .fill x3600

enter_check .FILL #-10
dec_48 .FILL #-48
stack_addr .FILL x4100
capacity .fill #10 
top .FILL x4100
asterisk .fill x4300
PRINT_DECIMAL .fill x4000
;-----------------------------------------------------------------------------------------------
; Subroutine: SUB_STACK_PUSH
; Parameter (R0): The value to push onto the stack
; Parameter (R1): stack_addr: A pointer to the beginning of the stack
; Parameter (R2): top: A pointer to the next place to PUSH an item
; Parameter (R3): capacity: The number of additional items the stack can hold
; Postcondition: The subroutine has pushed (R0) onto the stack. If an overflow
; occurred, the subroutine has printed an overflow error message
; and terminated.
; Return Value: R2 <--updated top value
;               R3 <-- updated capacity value
;-----------------------------------------------------------------------------------------------
.orig x3200
ST R7, BACKUP_R7_3200
ADD R6, R6, #0
BRp already_have_number
LD R0, message
PUTS
GETC
OUT
ST R1, BACKUP_R1_3200
LD R1, conversion_number
ADD R0, R0, R1
LD R1, BACKUP_R1_3200
BRnzp got_number
already_have_number
AND R0, R0, #0
ADD R0, R6, #0
got_number
ADD R0, R0, #0
BRnzp check_capacity
capacity_okay
STR R0, R2, #0
ADD R2, R2, #-1
ADD R3, R3, #-1
BRnzp END
check_capacity
ADD R3, R3, #0
BRp capacity_okay
overflow
LD R0, overflow_message
PUTS
HALT
END
LD R0, newline_character
OUT
LD R7, BACKUP_R7_3200
RET
BACKUP_R7_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
numbers_to_add_to_stack .fill x8000
overflow_message .FILL x4150
conversion_number .FILL #-48
newline_character .FILL x0a
message .fill x4250

.orig x3400
ST R7, BACKUP_R7_3400
ADD R5,R1,#0
NOT R5, R5
ADD R5, R5, #1
ADD R5, R2, R5
BRp underflow
LDR R0, R2, #0
ADD R0, R0, #0
BRnp skip
ADD R2, R2, #1
LDR R0, R2, #0
skip
ADD R4, R4, #0
BRp store_in_R5
ADD R6, R0, #0
BRnzp finished
store_in_R5
AND R5, R5, #0
ADD R5, R0, #0
ADD R2, R2, #1
ADD R3, R3, #1
BRnzp finished
underflow
LD R0, underflow_message
PUTS
HALT
finished
LD R7, BACKUP_R7_3400
RET
BACKUP_R7_3400 .BLKW #1
conversion .FILL #48
newline .fill x0a
underflow_message .fill x4200

.orig x3600
ST R7, BACKUP_R7_3600
AND R4, R4, #0
LD R0, SUB_STACK_POP
JSRR R0
ADD R4, R4, #1
ADD R2, R2, #1
LD R0, SUB_STACK_POP
JSRR R0
LD R0, MULTIPLY
JSRR R0
ADD R2, R2, #-1
LD R0, SUB_STACK_PUSH_2
JSRR R0
LD R0, SUB_STACK_POP
JSRR R0
LD R7, BACKUP_R7_3600
RET
BACKUP_R7_3600 .BLKW #1
SUB_STACK_POP   .fill x3400
SUB_STACK_PUSH_2 .FILL x3200
MULTIPLY .FILL x3800

.orig x3800
ST R7, BACKUP_R7_3800
ST R1, BACKUP_R1_3800
AND R1, R1, #0
DO_WHILE_LOOP_1 
   ADD R1, R1, R5  ; R1 <-- R1 + R5
   ADD R6, R6, #-1  ; R6 <-- R6-1 (update loop counter. R6 is now the LMR)
   BRp DO_WHILE_LOOP_1   ; if (R6>0) {jump to DO_WHILE_LOOP_1 }
END_DO_WHILE_LOOP_1
AND R6, R6, #0
ADD R6, R1, #0
LD R1, BACKUP_R1_3800
LD R7, BACKUP_R7_3800
RET
BACKUP_R7_3800 .BLKW #1
BACKUP_R1_3800 .BLKW #1

.orig x4000
ST R7, BACKUP_R7_4000
ST R6, BACKUP_R6_4000
ST R4, BACKUP_R4_4000
ST R3, BACKUP_R3_4000
ST R2, BACKUP_R2_4000
ST R1, BACKUP_R1_4000
ST R0, BACKUP_R0_4000
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
AND R6, R6, #0
ADD R6, R5, #0
LD R1, ten
loop
ADD R2, R2, #1
ADD R6, R1, R6
BRzp loop
ADD R2, R2, #-1
LD R3, dec_48_2
ADD R0, R2, R3
OUT
NOT R1, R1
ADD R1, R1, #1
ADD R6, R6, R1
ADD R0, R6, R3
OUT

LD R7, BACKUP_R7_4000
LD R6, BACKUP_R6_4000
LD R4, BACKUP_R4_4000
LD R3, BACKUP_R3_4000
LD R2, BACKUP_R2_4000
LD R1, BACKUP_R1_4000
LD R0, BACKUP_R0_4000
RET
BACKUP_R7_4000 .BLKW #1
BACKUP_R6_4000 .BLKW #1
BACKUP_R4_4000 .BLKW #1
BACKUP_R3_4000 .BLKW #1
BACKUP_R2_4000 .BLKW #1
BACKUP_R1_4000 .BLKW #1
BACKUP_R0_4000 .BLKW #1
ten .FILL #-10
dec_48_2 .FILL #48
.orig x4100
.BLKW #10
.orig x4150
.STRINGZ "\nYou have overflowed this stack, program terminating\n"
.orig x4200
.STRINGZ "\nYou have underflowed this stack, program terminating\n" 
.ORIG x4250
.STRINGZ "\nPlease enter in a single digit number\n"
.orig x4300
.STRINGZ "\nPlease input an asterisk '*'\n"
.orig x4350
.STRINGZ " * "
