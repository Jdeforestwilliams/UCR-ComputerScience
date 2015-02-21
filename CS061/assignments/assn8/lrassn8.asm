;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:JdeFo002
; 
; Assignment name: assn 8
; Lab section: 021
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R6, CONVERT_TO_BINARY
JSRR R6
;;;;to continue repeating the menu until option 7 is picked
menu_loop
LD R6, MENU
JSRR R6
;;;to pick the correct menu option 
LD R5, neg_one
ADD R5, R1, R5
BRz option_1
LD R5, neg_two
ADD R5, R1, R5
BRz option_2
LD R5, neg_three
ADD R5, R1, R5
BRz option_3
LD R5, neg_four
ADD R5, R1, R5
BRz option_4
LD R5, neg_five
ADD R5, R1, R5
BRz option_5
LD R5, neg_six
ADD R5, R1, R5
BRz option_6
LD R5, neg_seven
ADD R5, R1, R5
BRz option_7
BRnzp menu_loop

;; branches to select the correct option

option_1
LD R0, ALL_MACHINES_BUSY
JSRR R0
LD R0, print_option_1
JSRR R0
BRnzp menu_loop
option_2
LD R0, ALL_MACHINES_FREE
JSRR R0
LD R0, print_option_2
JSRR R0
BRnzp menu_loop
option_3
LD R0, NUM_BUSY_MACHINES
JSRR R0
LD R0, print_option_3
JSRR R0
BRnzp menu_loop
option_4
LD R0, NUM_FREE_MACHINES
JSRR R0
LD R0, print_option_4
JSRR R0
BRnzp menu_loop
option_5
LD R0, MACHINE_STATUS
JSRR R0
LD R0, print_option_5
JSRR R0
BRnzp menu_loop
option_6
LD R0, FIRST_FREE
JSRR R0
LD R0, print_option_6
JSRR R0
BRnzp menu_loop
option_7
LD R0, goodbye
PUTS
HALT
;;;;data
MENU .FILL x3200
ALL_MACHINES_BUSY .FILL x3300
ALL_MACHINES_FREE .FILL x3400
NUM_BUSY_MACHINES .FILL x3500
NUM_FREE_MACHINES .FILL x3600
MACHINE_STATUS .FILL x3700
FIRST_FREE .FILL x3800
CONVERT_TO_BINARY .fill x3900
print_option_1 .fill x4000
print_option_2 .fill x4100
print_option_3 .fill x4200
print_option_4 .fill x4300
print_option_5 .fill x4400
print_option_6 .fill x4500
neg_seven .FILL #-55
neg_six .FILL #-54
neg_five .FILL #-53
neg_four .FILL #-52
neg_three .FILL #-51
neg_two .FILL #-50
neg_one .FILL #-49
goodbye .fill x725A
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: MENU 
; Inputs: None 
; Postcondition: The subroutine has printed out a menu with numerical options, allowed the 
;                          user to select an option, and returned the selected option. 
; Return Value (R1): The option selected:  #1, #2, #3, #4, #5, #6 or #7 
; no other return value is possible 
.orig x3200
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3200
LD R0, star_1
PUTS
LD R0, menu_title
PUTS
LD R0, star_2
PUTS
LD R0, op_1
PUTS
LD R0, op_2
PUTS
LD R0, op_3
PUTS
LD R0, op_4
PUTS
LD R0, op_5
PUTS
LD R0, op_6
PUTS
LD R0, op_7
PUTS
LD R0, input_string
PUTS
GETC
OUT
ADD R1, R0, #0
LD R0, newline
OUT
LD R7, BACKUP_R7_3200
RET
BACKUP_R7_3200 .BLKW #1
star_1 .FILL x7000
menu_title .FILL x7019
star_2 .FILL x7032
op_1 .FILL x704C
op_2 .FILL x707B
op_3 .FILL x70AA
op_4 .FILL x70D1
op_5 .FILL x70F8
op_6 .FILL x711B
op_7 .FILL x7150
input_string .FILL x715A
newline .FILL x0a
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: ALL_MACHINES_BUSY 
; Inputs: None 
; Postcondition: The subroutine has returned a value indicating whether all machines are busy 
; Return value (R2): 1 if all machines are busy,    0 otherwise 
.orig x3300
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3300
LD R6, bit_vector_machines_busy
LD R5, machine_busy_counter
AND R1, R1, #0
machine_busy_loop
LDR R4, R6, #0
LD R3, machine_busy_neg_one
ADD R3, R3, R4
BRn machine_busy
ADD R1, R1, #1
machine_busy
ADD R6, R6, #1
ADD R5, R5, #-1
BRnp machine_busy_loop
ADD R1, R1, #0
BRp machines_are_busy
;;;to return R2 with the correct value
AND R2, R2, #0
ADD R2, R2, #1
BR machines_busy_anding
machines_are_busy
AND R2, R2, #0
;;;to and all registers for future use
machines_busy_anding 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LD R7, BACKUP_R7_3300
RET
BACKUP_R7_3300 .BLKW #1
bit_vector_machines_busy .FILL x5100
machine_busy_counter .fill #16
machine_busy_neg_one .fill #-1

;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: ALL_MACHINES_FREE 
; Inputs: None 
; Postcondition: The subroutine has returned a value indicating whether all machines are free 
; Return value (R2): 1 if all machines are free,    0 otherwise 
.orig x3400
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3400
LD R6, bit_vector_machines_free
LD R5, machine_free_counter
;;; to count for how many free machines there are
AND R1, R1, #0
AND R2, R2, #0
machine_free_loop
LDR R4, R6, #0
BRz machine_is_busy_free_machines
ADD R1, R1, #1
machine_is_busy_free_machines
ADD R6, R6, #1
ADD R5, R5, #-1
BRnp machine_free_loop
;;;;;to pick the right output
ADD R1, R1, #-15
ADD R1, R1, #-1
BRnp machines_are_not_free
ADD R2, R2, #1
machines_are_not_free
machines_free_anding 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LD R7, BACKUP_R7_3400
RET
BACKUP_R7_3400 .BLKW #1
bit_vector_machines_free .FILL x5100
machine_free_counter .fill #16
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: NUM_BUSY_MACHINES 
; Inputs: None 
; Postcondition: The subroutine has returned the number of busy machines. 
; Return Value (R2): The number of machines that are busy 
.orig x3500
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3500
LD R6, bit_vector_num_machines_busy
LD R5, num_machines_busy_counter 
LD R3, num_machines_busy_neg_ten
AND R2, R2, #0
AND R1, R1, #0
num_machines_busy_loop
LDR R4, R6, #0
BRp machine_is_busy
ADD R2, R2, #1
machine_is_busy
ADD R6, R6, #1
ADD R5, R5, #-1
BRnp num_machines_busy_loop

LD R7, BACKUP_R7_3500
RET
BACKUP_R7_3500 .BLKW #1
bit_vector_num_machines_busy .FILL x5100
num_machines_busy_counter .fill #16
num_machines_busy_conversion .fill #48
num_machines_busy_neg_ten .fill #-10
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: NUM_FREE_MACHINES 
; Inputs: None 
; Postcondition: The subroutine has returned the number of free machines 
; Return Value (R2): The number of machines that are free  
.orig x3600
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3600
LD R6, bit_vector_num_machines_free
LD R5, num_machines_free_counter 
LD R3, num_machines_free_neg_ten
AND R2, R2, #0
AND R1, R1, #0
num_machines_free_loop
LDR R4, R6, #0
BRz machine_is_free
ADD R2, R2, #1
machine_is_free
ADD R6, R6, #1
ADD R5, R5, #-1
BRnp num_machines_free_loop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LD R7, BACKUP_R7_3600
RET
BACKUP_R7_3600 .BLKW #1
bit_vector_num_machines_free .FILL x5100
num_machines_free_counter .fill #16
num_machines_free_conversion .fill #48
num_machines_free_neg_ten .fill #-10
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: MACHINE_STATUS 
; Input (R1): Which machine to check 
; Postcondition: The subroutine has returned a value indicating whether the machine indicated 
;                          by (R1) is busy or not. 
; Return Value (R2): 0 if machine (R1) is busy, 1 if it is free 
.orig x3700
;----------------------------------------------------------------------------------------------------------------- 
ST R7, BACKUP_R7_3700
LD R3, machine_status_dec_conversion
try_again
LD R0, which_machine_free
PUTS
LD R0, please_input
PUTS
GETC             ;; to input the number
OUT
ADD R5, R0, #0   ;; to store the number 
GETC             ;; to input the second number
OUT
ADD R6, R0, #0   ;; to store second number
LD R0, machine_number
PUTS 
ADD R0, R5, #0
OUT
ADD R0, R6, #0
OUT
NOT R4, R3       ;; to get the 1's complement of the conversion 
ADD R4, R4, #1   ;; to get the 2's complement of the conversion 
ADD R5, R4, R5   ;; to get the actual number for the first input
ADD R6, R4, R6   ;; to get the actual number for the second input
ADD R4, R5, #0
ADD R4, R4, #-1
BRp try_again
BRz one
Brn zero
one
ADD R4, R5, #9
ADD R4, R4, R6
BRnzp machine_status_finish
zero
ADD R4, R5, R6
machine_status_finish
ADD R1, R4, #0
BRz skip_to_end
LD R3, bit_vector_machine_status 
machine_status_loop
ADD R3, R3, #1
ADD R1, R1, #-1
BRp machine_status_loop
BRnz skip_skip_to_end
skip_to_end
LD R3, bit_vector_machine_status
skip_skip_to_end
LDR R2, R3, #0 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LD R7, BACKUP_R7_3700
RET
BACKUP_R7_3700 .BLKW #1
bit_vector_machine_status .fill x5100
which_machine_free .fill x7204
machine_number .FILL x7214
machine_status_counter .fill #16
please_input .fill x7263
machine_status_dec_conversion .FILL #48
machine_status_fifteen .fill #15
;----------------------------------------------------------------------------------------------------------------- 
; Subroutine: FIRST_FREE 
; Inputs: None 
; Postcondition:  
; The subroutine has returned a value indicating the lowest numbered free machine 
; Return Value (R2): the number of the free machine
.orig x3800
;-----------------------------------------------------------------------------------------------------------------
ST R7, BACKUP_R7_3800
LD R6, bit_vector_first_free
LD R3, final_counter
AND R1, R1, #0
AND R2, R2, #0
first_free_loop
ADD R1, R1, #1
LDR R5, R6, #0
BRp first_free_found
ADD R6, R6, #1
ADD R3, R3, #-1
BRp first_free_loop
ADD R2, R2, #-1
BR none_found
first_free_found
ADD R1, R1, #-1
ADD R2, R1, #0
none_found




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LD R7, BACKUP_R7_3800
RET
BACKUP_R7_3800 .BLKW #1
bit_vector_first_free .FILL x5100
first_free_conversion .FILL #48
new_line .fill x0A
final_counter .fill #16
;---------------------------------------------------------------------------------------------------------------
;changing input to bitvector here
;
;---------------------------------------------------------------------------------------------------------------
.orig x3900
ST R7, BACKUP_R7_3900
LD R3, bit_vector
LD R5, counter ; to count up to the power of 2^n needed
LD R4, counter ; to set up a second counter 
LD R6, two_n ; to add to itsself to get up to 2^n
LDI R1, input ; to load number into R1    
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
    ADD R0, R1, R6 ;to store/test the number of the input minus the 2^n number 
    
    BRzp NEGATIVE ; if statement to output a 1 if needed
        LD R0, pos  ; used to output a zero 
        STR R0, R3, #0
        BRnzp ELSE ;branch used to skip if output a 0
        NEGATIVE ; if statement to output a 1 if needed
            ADD R1, R1, R6 ; 
            LD R0, neg
            STR R0, R3, #0 
    ELSE
        LD R6, two_n
        ADD R3, R3, #1
        ADD R4, R4, #-1
        ADD R5, R4, #0
        ADD R4, R4, #0
    BRzp LOOP
    GO_TO_END
    AND R0, R0, #0
    AND R1, R1, #0
    AND R2, R2, #0
    AND R3, R3, #0
    AND R4, R4, #0
    AND R5, R5, #0
    AND R6, R6, #0
    AND R7, R7, #0
LD R7, BACKUP_R7_3900
RET
BACKUP_R7_3900 .BLKW #1
input .FILL x5000 ;number to output in binary
pos .FILL #0  ; used to output 0
neg .FILL #1  ; used to output  1
counter .FILL #16
two_n .FILL #1
convert .FILL#48
bit_vector .fill x5100

.orig x7000
.STRINGZ "\n**********************\n" 
.STRINGZ "* The Busyness Server *\n"
.STRINGZ "********************** \n\n"
.STRINGZ "1. Check to see whether all machines are busy\n" 
.STRINGZ "2. Check to see whether all machines are free\n" 
.STRINGZ "3. Report the number of busy machines\n"
.STRINGZ "4. Report the number of free machines\n"
.STRINGZ "5. Report the status of machine n\n"
.STRINGZ "6. Report the number of the first available machine\n"
.STRINGZ "7. Quit\n\n"
.STRINGZ "Your input is: "
.STRINGZ "All machines are busy\n"
.STRINGZ "All machines are not busy\n"
.STRINGZ "All machines are free\n"
.STRINGZ "All machines are not free\n"
.STRINGZ "There are "
.STRINGZ " busy machines\n"
.STRINGZ "There are "
.STRINGZ " free machines\n"
.STRINGZ "\nWhich machine?"
.STRINGZ "\nMachine "
.STRINGZ " is busy\n" 
.STRINGZ " is free \n" 
.STRINGZ "The first available machine is number "
.STRINGZ "Goodbye!"
.STRINGZ " Please enter a two digit number to specify which machine (from 00 at the left to 15 at the right): " 
.STRINGZ " There is no free machine\n" 


;;;;;;;to print the option for number 1
.orig x4000
ST R7, BACKUP_R7_4000
ADD R2, R2, #0
BRp option_1_positive
LD R0,  all_machines_not_busy
PUTS
BR option_1_break
option_1_positive
LD R0, all_machines_are_busy
PUTS
option_1_break
LD R7, BACKUP_R7_4000
RET
BACKUP_R7_4000 .BLKW #1
all_machines_are_busy .fill x716A
all_machines_not_busy .fill x7181


;;;;;;;to print the option for number 2
.orig x4100
ST R7, BACKUP_R7_4100
ADD R2, R2, #0
BRp option_2_positive
LD R0, all_machines_not_free
PUTS
BR option_2_break
option_2_positive
LD R0, all_machines_are_free
PUTS
option_2_break
LD R7, BACKUP_R7_4100
RET
BACKUP_R7_4100 .BLKW #1
all_machines_are_free .FILL x719C
all_machines_not_free .FILL x71B3


;;;;;;;to print the option for number 3
.orig x4200
ST R7, BACKUP_R7_4200
ST R1, BACKUP_R1_4200	
LD R0, there_are
PUTS
LD R3, option_3_neg_ten
ADD R3, R2, R3
Brn num_machines_busy_under_nine
AND R0, R0, #0
ADD R0, R0, #1
LD R3, option_3_neg_ten
ADD R1, R3, R2
LD R3, option_3_conversion
ADD R0, R0, R3
OUT
BR bigger_than_nine
num_machines_busy_under_nine
LD R3, option_3_conversion
ADD R1, R2, R3
BR finish_op_3
bigger_than_nine
LD R3, option_3_conversion
ADD R1, R1, R3
finish_op_3
ADD R0, R1, #0
OUT
LD R0, amount_busy_machines
PUTS
LD R1, BACKUP_R1_4200
LD R7, BACKUP_R7_4200
RET
BACKUP_R7_4200 .BLKW #1
BACKUP_R1_4200 .BLKW #1
there_are .FILL x71CE
amount_busy_machines .FILL  x71D9
option_3_conversion  .fill #48
option_3_neg_ten .fill #-10

;;;;;;;to print the option for number 4
.orig x4300
ST R7, BACKUP_R7_4300
ST R1, BACKUP_R1_4300
LD R0, num_free_machines_there_are
PUTS
ADD R3, R2, R3
Brn num_machines_free_under_nine
AND R0, R0, #0
ADD R0, R0, #1
LD R3, amount_machines_free_neg_ten
ADD R1, R2, #0
ADD R2, R3, R2
LD R3, option_4_conversion
ADD R0, R0, R3
OUT
num_machines_free_under_nine
LD R3, option_4_conversion
ADD R2, R2, R3

ADD R0, R2, #0
OUT
LD R3, amount_machines_free_counter
ADD R0, R3, R3
OUT
LD R0, amount_free_machines
PUTS
LD R1, BACKUP_R1_4300
LD R7, BACKUP_R7_4300
RET
BACKUP_R7_4300 .BLKW #1
BACKUP_R1_4300 .BLKW #1
num_free_machines_there_are .FILL x71E9
amount_free_machines .FILL x71F4
option_4_conversion .fill #48
amount_machines_free_neg_ten .fill #-10
amount_machines_free_counter .fill #16

;;;;;;;to print the option for number 5
.orig x4400
ST R7, BACKUP_R7_4400
ADD R2, R2, #0
BRp option_5_positive
LD R0, is_busy
PUTS
BR option_5_break
option_5_positive
LD R0, is_free
PUTS
option_5_break
LD R7, BACKUP_R7_4400
RET
BACKUP_R7_4400 .BLKW #1
is_busy .fill x721E
is_free .fill x7228


;;;;;;;to print the option for number 6
.orig x4500
ST R7, BACKUP_R7_4500
ADD R2, R2, #0
BRn nothing_found 
LD R0, first_free_machine
PUTS
ADD R3, R1, #-10
BRn lower_than_ten
AND R0, R0, #1
LD R4, first_free_conversion_number
ADD R0, R0, R4
OUT
ADD R1, R1, #-10
Brnzp second_digit
lower_than_ten
AND R0, R0, #0
LD R4, first_free_conversion_number
ADD R0, R0, R4
OUT
second_digit
ADD R0, R1, #0
LD R4, first_free_conversion_number
ADD R0, R0, R4
OUT
LD R0, new_line_character
OUT
BR ending
nothing_found
LD R0, no_free_machine_found
PUTS

ending
LD R7, BACKUP_R7_4500
RET
BACKUP_R7_4500 .BLKW #1
first_free_machine .fill x7233
first_free_conversion_number .fill #48
new_line_character .FILL x0a
no_free_machine_found .fill x72C8

;    AND R0, R0, #0
;    AND R1, R1, #0
;   AND R3, R3, #0
;    AND R4, R4, #0
;    AND R5, R5, #0
;    AND R6, R6, #0

.orig x5100
.BLKW #16
.orig x5000
BUSYNESS .FILL x0000
