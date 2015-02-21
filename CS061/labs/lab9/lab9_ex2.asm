;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: lab 9 ex2
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
prompt
LD R0, message
PUTS
GETC
OUT
LD R4, enter_check
ADD R4, R4, R0
BRz quit
LD R4, dec_48
ADD R0, R4, R0
BRz PUSH_STACK
BRp POP_STACK
PUSH_STACK
LD R0, SUB_STACK_PUSH
JSRR R0
BRnzp prompt
POP_STACK
LD R0, SUB_STACK_POP
JSRR R0
BRnzp prompt
quit
HALT
SUB_STACK_PUSH .fill x3200
SUB_STACK_POP   .fill x3400
message .fill x4150
enter_check .FILL #-10
dec_48 .FILL #-48
stack_addr .FILL x4000
capacity .fill #10 
top .FILL x4000
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
LD R0, newline_character 
OUT

LD R4, conversion_number
LD R0, input_message
PUTS
GETC
OUT
ADD R0, R0, R4
BRnp check_capacity
capacity_okay
STR R0, R2, #0
ADD R6, R6, #1 
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

numbers_to_add_to_stack .fill x8000
overflow_message .FILL x4050
input_message .FILL x4200
conversion_number .FILL #-48
newline_character .FILL x0a



.orig x3400
ST R7, BACKUP_R7_3400
ADD R5,R1,#0
NOT R5, R5
ADD R5, R5, #1
ADD R5, R2, R5
BRp underflow
LD R0, newline
OUT
LD R4, conversion
LDR R0, R2, #0
ADD R0, R0, #0
BRnp skip
ADD R2, R2, #1
LDR R0, R2, #0
skip
ADD R0, R0, R4
OUT
ADD R2, R2, #1
ADD R3, R3, #1
BRnzp finished
underflow
LD R0, underflow_message
PUTS
HALT
finished
LD R0, newline
OUT
LD R7, BACKUP_R7_3400
RET
BACKUP_R7_3400 .BLKW #1
conversion .FILL #48
newline .fill x0a
underflow_message .fill x4100
.orig x4000
.BLKW #10
.orig x4050
.STRINGZ "\nYou have overflowed this stack, program terminating\n"
.orig x4100
.STRINGZ "\nYou have underflowed this stack, program terminating\n" 
.ORIG x4150
.STRINGZ "Please enter 0 to push a number to the stack, enter 1 to pop a number from the stack and ENTER to quit (up to 10 numbers between 1 and 9)\n"
.orig x4200
.STRINGZ "Please input a number between 1 and 9\n"
