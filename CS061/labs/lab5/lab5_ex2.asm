;=================================================
; 
; Name:DeForest-Williams, Joshua
; Login id:Jdefo002 
; 
; Assignment name: lab 5 ex2
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0, message
PUTS
LD R1, INPUT
JSRR R1 
HALT
;;;data;;;;
message .FILL x6000
INPUT .FILL x3200



;;subroutines
.orig x3200
ST R7, BACKUP_R7_3200
LD R3, input_counter
LD R5, dec_48
LD R6, input_storage_arr

input_loop
    GETC 
    STR R0, R6, #0 
    ADD R6, R6, #1
    ADD R3, R3, #-1
BRp input_loop

LD R1, character_to_decimal
JSRR R1
LD R7, BACKUP_R7_3200
RET
;;;data 
BACKUP_R7_3200 .BLKW #1
input_counter .FILL #17 
dec_one .FILL #1
input_storage_arr .FILL x5000
dec_48 .FILL #-48
character_to_decimal .FILL x3400
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;second subroutine 
.orig x3400
ST R7, BACKUP_R7_3400
LD R5, dec_48_2
LD R6, input_storage_arr_2
LD R3, input_counter_2
ADD R3, R3, #-1
ADD R6, R6, #1
character_to_decimal_loop
    LDR R4, R6, #0
    ADD R4, R4, R5
    STR R4, R6, #0
    ADD R6, R6, #1
    ADD R3, R3, #-1
BRp character_to_decimal_loop
LD R1, converter
JSRR R1
LD R7, BACKUP_R7_3400
RET
;;data
BACKUP_R7_3400 .BLKW #1
input_counter_2 .FILL #17 
input_storage_arr_2 .FILL x5000
dec_48_2 .FILL #-48
converter .FILL x3600
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;third subroutine 
.orig x3600
ST R7, BACKUP_R7_3600  
AND R1, R1, #0
AND R2, R2, #0
AND R4, R4, #0
LD R3, input_counter_3
ADD R3, R3, #-1
ADD R6, R6, #-1
LD R1, dec_one
loop
LDR R4, R6, #0
BRp ONE
BRz ZERO
ONE
ADD R2, R2, R1
ZERO 
ADD R1, R1, R1
ADD R6, R6, #-1
ADD R3, R3, #-1
BRp loop
LD R1, character_back_to_decimal
JSRR R1
LD R7, BACKUP_R7_3600
RET

;;;data
BACKUP_R7_3600 .BLKW #1
input_counter_3 .FILL #17 
dec_one .FILL #1
input_storage_arr_3 .FILL x5000
dec_48_3 .FILL #-48
character_back_to_decimal .FILL x3800
;;output
.orig x3800
ST R1, BACKUP_R1_3800 
ST R7, BACKUP_R7_3800 
LD R5, counter ; to count up to the power of 2^n needed
LD R4, counter ; to set up a second counter 
LD R3, dec_one_2 ; to add to itsself to get up to 2^n;;;;;;;;;
assn_LOOP
AND R1, R1, #0
AND R0, R0, #0
ADD R0, R2, #0
    ADD R3, R3, #0 ; to get to 2^n of what what is needed 
    ADD R5, R5, #-1 ; to lower the counter to stop at zero  
    BRz SKIP
        two_to_the_n_loop: 
            ADD R3, R3, R3 ; to get to 2^n of what what is needed 
            ADD R5, R5, #-1 ; to lower the counter to stop at zero  
        BRp two_to_the_n_loop 
        BRn GO_TO_END  
    SKIP
    NOT R3, R3   ; to get the 1's complement 
    ADD R3, R3,  #1 ; to take the 2's complement

ADD R1, R0, R3 ;to store/test the number of the input minus the 2^n number 
    BRz NEGATIVE ; if statement to output a 1 if needed
        LD R0, zero  ; used to output a zero 
        OUT ; used to output a zero
    BRnzp ELSE ;branch used to skip if output a 0
        NEGATIVE ; if statement to output a 1 if needed
            ADD R0, R0, R3 
            LD R0, one
            OUT 
    ELSE
        LD R3, dec_one_2
        ADD R4, R4, #-1
        ADD R5, R4, #0
        ADD R4, R4, #0
	 ADD R6, R6, #1   ;to move the array
BRzp assn_LOOP
      GO_TO_END
    ADD R6, R6, #1   ;to move the array
    LD R0, newline
    OUT
    ADD R2, R2, #-1

LD R1, BACKUP_R1_3800
LD R7, BACKUP_R7_3800
RET
;;;data for subroutine
BACKUP_R1_3800 .BLKW #1
BACKUP_R7_3800 .BLKW #1 
one .FILL #49
zero .FILL #48
dec_one_2 .FILL #1
newline .FILL x0a
counter .FILL #16
.orig x5000 
input_storage .BLKW #17 
.orig x6000
orig_message   .STRINGZ "Input the letter 'b' followed by sixteen 1's and 0's\n"
