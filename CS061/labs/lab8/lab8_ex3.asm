;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:Jdefo002
; 
; Assignment name: lab 8 ex 3
; Lab section: 021
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0, SUB_PRINT_OPCODES
JSRR R0
HALT
;;;;;data
SUB_PRINT_OPCODES .FILL x3200 

.orig x3200
ST R7, BACKUP_R7_3200
LD R6, input_array
LD R3, input_counter
Input
    LD R5, enter_character ;used to check for when input is over 
    Getc 
    ADD R5, R0, R5
    BRz INPUT_END
    STR R0, R6, #0 
    ADD R6, R6, #1
    OUT
    ADD R3, R3, #-1
    BRnp Input
INPUT_END  
LD R0, input_counter
NOT R3, R3
ADD R3, R3, #1
ADD R3, R0, R3
LD R5, opcode_pointer
AND R0, R0, #0
ADD R0, R3, #0 
LD R3, input_amount_counter
STR R0, R3, #0
AND R0, R0, #0
LD R4, opcode_string_amount_pointer
big_loop
LDI R3, input_amount_counter
LD R6, input_array
LD R1, check_r5
STR R5, R1, #0
check_same_loop
LDR R1, R5, #0
LD R2, neg1
ADD R1, R2, R1
BRz invalidness
LDR R2, R6, #0
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1
BRnp skip_x
ADD R5, R5, #1
ADD R6, R6, #1
ADD R3, R3, #-1
BRp check_same_loop
BRnz out_put_loop
skip_x
ADD R0, R0, #1
LDR R1, R4, #0
ADD R4, R4, #1
LDI R5, check_r5
ADD R5, R5, R1
;ADD R5, R5, #-1
LD R2, neg1
LDR R1, R5, #0
ADD R1, R2, R1
BRnp big_loop
invalidness 
LD R0, invalid_stringz
PUTS
BRnzp jump_out
out_put_loop
AND R1, R1, #0
ADD R1, R0, #0
LD R5, number_pointer
ADD R5, R0, R5
;ADD R5, R5, #-1
LDR R1, R5, #0

LD R0, equal_sign
OUT

LD R0, binary_output_subroutine
JSRR R0
LDR R0, R3, #0
ADD R5, R5, R0
ADD R6, R6, #1
ADD R3, R3, #1
ADD R2, R2, #-1
BRp out_put_loop

jump_out
LD R7, BACKUP_R7_3200
RET
BACKUP_R7_3200 .BLKW #1
number_pointer .fill x3300
opcode_pointer .FILL x3400 
opcode_string_amount_pointer .fill x3500
binary_output_subroutine .fill x3600
neg1 .fill #1
equal_sign .FILL #61
input_array .FILL x5000
enter_character .FILL #-10
input_counter .FILL #8
input_amount_counter .FILL x5100
 check_r5 .fill x5200
 invalid_stringz .fill x5300
 
.orig x3300
.fill #1
.fill #5
.fill #0
.fill #12
.fill #4
.fill #4
.fill #2
.fill #10
.fill #6
.fill #14
.fill #9
.fill #12
.fill #8
.fill #3
.fill #11
.fill #7
.fill #15
.fill #13


.orig x3400
.STRINGZ "ADD"
.STRINGZ "AND"
.STRINGZ "BR"
.STRINGZ "JMP"
.STRINGZ "JSR"
.STRINGZ "JSRR"
.STRINGZ "LD"
.STRINGZ "LDI"
.STRINGZ "LDR"
.STRINGZ "LEA"
.STRINGZ "NOT"
.STRINGZ "JMP"
.STRINGZ "RTI"
.STRINGZ "ST"
.STRINGZ "STI"
.STRINGZ "STR"
.STRINGZ "TRAP"
.STRINGZ "RESERVED"
.fill #-1

.orig x3500
.fill #4
.fill #4
.fill #3
.fill #4
.fill #4
.fill #5
.fill #3
.fill #4
.fill #4
.fill #4
.fill #4
.fill #4
.fill #4
.fill #3
.fill #4
.fill #4
.fill #5
.fill #8

.orig x3600
ST R7, BACKUP_R7_3600
ST R6, BACKUP_R6_3600
ST R5, BACKUP_R5_3600
ST R4, BACKUP_R4_3600
ST R3, BACKUP_R3_3600
ST R2, BACKUP_R2_3600
ST R0, BACKUP_R0_3600
LD R5, counter ; to count up to the power of 2^n needed
LD R4, counter ; to set up a second counter 
LD R6, two_n ; to add to itsself to get up to 2^n
LD R2, convert; used to convert number to character 
LOOP
    ADD R6, R6, #0 ; to get to 2^n of what what is needed 
    ADD R5, R5, #-1 ; to lower the counter to stop at zero  
    BRz SKIP
        two_to_the_n_loop: 
            ADD R6, R6, R6 ; to get to 2^n of what what is needed 
            ADD R5, R5, #-1 ; to lower the counter to stop at zero  
        BRp two_to_the_n_loop 
        BRn GO_TO_END  
    SKIP
    
    NOT R6, R6   ; to get the 1's complement 
    ADD R6, R6,  #1 ; to take the 2's complement
    ADD R3, R1, R6 ;to store/test the number of the input minus the 2^n number 
    
    BRzp NEGATIVE ; if statement to output a 1 if needed
        LD R0, pos  ; used to output a zero 
        ADD R0, R0, R2 ; used to output a zero
        OUT ; used to output a zero
        BRnzp ELSE ;branch used to skip if output a 0
        NEGATIVE ; if statement to output a 1 if needed
            ADD R1, R1, R6 ; 
            LD R0, neg
            ADD R0, R0, R2
            OUT 
    ELSE
        LD R6, two_n
        ADD R4, R4, #-1
        ADD R5, R4, #0
        ADD R4, R4, #0
    BRzp LOOP
    GO_TO_END
    LD R0, newline
    OUT
LD R7, BACKUP_R7_3600
LD R6, BACKUP_R6_3600
LD R5, BACKUP_R5_3600
LD R4, BACKUP_R4_3600
LD R3, BACKUP_R3_3600
LD R2, BACKUP_R2_3600
LD R0, BACKUP_R0_3600
RET
;;;;Data;;;;;
BACKUP_R7_3600 .BLKW #1
BACKUP_R6_3600 .BLKW #1
BACKUP_R5_3600 .BLKW #1
BACKUP_R4_3600 .BLKW #1
BACKUP_R3_3600 .BLKW #1
BACKUP_R2_3600 .BLKW #1
BACKUP_R0_3600 .BLKW #1

pos .FILL #0  ; used to output 0
neg .FILL #1  ; used to output  1
counter .FILL #4
two_n .FILL #1
convert .FILL#48
newline .FILL x0A


.orig x5000
input_array_storage .BLKW #8
.orig x5100 
.BLKW #1
.orig x5200
.BLKW #1
.orig x5300
.STRINGZ "Invalid Instruction"
