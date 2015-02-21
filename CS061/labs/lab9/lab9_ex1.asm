;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: lab 9 ex1
; Lab section: 021
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.ORIG x3000
LD R0, SUB_STACK_PUSH
JSRR R0
HALT
SUB_STACK_PUSH .fill x3200
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
LD R3, capacity
LD R2, top
LD R1, stack_addr
LD R6, numbers_to_add_to_stack
stack_push
LDR R0, R6, #0
ADD R0, R0, #0
BRnp check_capacity
BRz zero_check_capacity
capacity_okay
STR R0, R2, #0
ADD R6, R6, #1 
ADD R2, R2, #1
ADD R3, R3, #-1
BRnzp stack_push
check_capacity
ADD R3, R3, #0
BRp capacity_okay
overflow
LD R0, overflow_message
PUTS
BRnzp END
zero_check_capacity 
ADD R3, R3, #0
BRp input_over_still_room_in_capacity
BRnz great_job_put_in_right_amount_of_values
input_over_still_room_in_capacity
LD R0, input_over_still_room_in_capacity_stringz
PUTS
BRnzp END
great_job_put_in_right_amount_of_values
LD R0, great_job_put_in_right_amount_of_values_stringz 
PUTS
BRnzp END
END
LD R7, BACKUP_R7_3200
RET
BACKUP_R7_3200 .BLKW #1
stack_addr .FILL x4000
capacity .fill #10 
top .FILL x4000
numbers_to_add_to_stack .fill x8000
overflow_message .FILL x4050
input_over_still_room_in_capacity_stringz .FILL x4100
great_job_put_in_right_amount_of_values_stringz .FILL x4150

.orig x4000
.BLKW #10
.orig x4050
.STRINGZ "You have overflowed this stack, program terminating\n"
.orig x4100
.STRINGZ "Your input is over, you still have room in capacity, progam terminating\n" 
.orig x4150
.STRINGZ "Great Job, you ended your input with just the right amount of values, program terminating\n"
.orig x8000
.fill #5
.fill #9
.fill #6
.fill #22
.fill #12
.fill #5
.fill #15
.fill #21
.fill #6
.fill #7
.fill #15
.fill #21
.fill #6
.fill #7
