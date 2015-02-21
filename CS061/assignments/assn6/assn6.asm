;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: assn 6
; Lab section: 021
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R0, input_to_decimal
JSRR R0
LD R6, hex_array
LD R0, positive
JSRR R0
LD R0, negative
JSRR R0
LD R0, dec_to_hex
JSRR R0
;;;if positive its second number
ADD R4, R4, #1
LD R0, positive
JSRR R0
LD R0, negative
JSRR R0
LD R0, dec_to_hex
JSRR R0
;;;if negative its third number
ADD R4, R4, #-2
LD R0, positive
JSRR R0
LD R0, negative
JSRR R0
LD R0, dec_to_hex
JSRR R0
AND R5, R5, #0
ADD R5, R1, #0
LD R0, dec_to_hex
JSRR R0
LD R0, output
JSRR R0
HALT
;;;;data
input_to_decimal .FILL x3200
positive .FILL x3400
negative .FILL x3600
dec_to_hex .FILL x3800
output .FILL x4000
hex_array .FILL x5200
;; subroutine, input to chracter

.orig x3200 
ST R7, BACKUP_R7_3200
ST R2, BACKUP_R2_3200
LD R5, enter_character ;used to check for when input is over 
;; big loop to start over if error input 
Invalid 
LD R3, input_counter
LD R6, input_arr
LD R4, num_sign
LD R0, message ; stores address of start of message R0
PUTS            ; invokes BIOS routine to output string
 ;; used to get sign from the user and store it in an array 
Getc    
AND R2, R2, #0
ADD R2, R2, R0 
ADD R4, R2, R4  
BRz  done_sign
LD R4, neg_sign
ADD R2, R2, R4
BRnp Invalid
done_sign:
OUT
STR R0, R6, #0
ADD R6, R6, #1
;;;  loop used to input the digits from the user into the array
Input
    LD R5, enter_character ;used to check for when input is over 
    Getc 
    ADD R5, R0, R5
    BRz ELSE
    LD R4, check_nine
    AND R2, R2, #0
    ADD R2, R2, R0 
    ADD R4, R2, R4  
    BRp Invalid
    LD R4, check_zero
    ADD R2, R2, R4
    BRn Invalid
    STR R0, R6, #0 
    ADD R6, R6, #1
    OUT
    ADD R3, R3, #-1
    BRnp Input
INPUT_END  
ELSE: 
;; to reset the counter and the array position
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, #5
LD R6, input_arr
AND R2, R2, #0
ADD R6, R6, #1
AND R0, R0, #0
ADD R0, R3, R0
;;; to change the characters to decimals
character_to_decimal
LDR R2, R6, #0
ADD R2, R2, R4
STR R2, R6, #0
ADD R6, R6, #1
ADD R3, R3, #-1
BRp character_to_decimal
;;; to reset all registers to zero, R6 to last value of array,
;;; setting R5 to correct value and loading R2 with the correct value
ADD R3, R0, R3
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R4, R4, #0
LD R5, one 
ADD R6, R6, #-1
ADD R3, R3, #0
BRnz past_one 
LDR R2, R6, #0
BRz past_one ;; if the value in the array is zero no need to add anything
;;;add numbers together
;; loop for the number in the one's spot
one_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp one_loop
past_one
;; loop for the number in the ten's spot
LD R5, ten 
ADD R6, R6, #-1
ADD R3, R3, #-1
BRnz past_ten
LDR R2, R6, #0
BRz past_ten ;; if the value in the array is zero no need to add anything
ten_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp ten_loop
past_ten
;; loop for the number in the hundred's spot
LD R5, hundred 
ADD R3, R3, #-1
BRnz past_hundred
ADD R6, R6, #-1
LDR R2, R6, #0
BRz past_hundred ;; if the value in the array is zero no need to add anything
hundred_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp hundred_loop
past_hundred
;; loop for the number in the thousand's spot
LD R5, thousand
ADD R3, R3, #-1
BRnz past_thousand
ADD R6, R6, #-1
LDR R2, R6, #0
BRz past_thousand ;; if the value in the array is zero no need to add anything
thousand_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp thousand_loop
past_thousand
;; loop for the number in the ten thousand's spot
LD R5, ten_thousand
ADD R3, R3, #-1
BRnz past_ten_thousand
ADD R6, R6, #-1
LDR R2, R6, #0
BRz past_ten_thousand ;; if the value in the array is zero no need to add anything
ten_thousand_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp ten_thousand_loop
past_ten_thousand
;; to check if negative to take twos complement 
ADD R6, R6, #-1
LDR R2, R6, #0
LD R3,neg_sign
ADD R3, R2, R3
BRn end
NOT R1, R1
ADD R1, R1, #1
end
LD R0, newline
OUT
AND R5, R5, #0
LD R2, BACKUP_R2_3200
LD R7, BACKUP_R7_3200
RET              ; terminates program execution
;;;Data Fields;;;   
BACKUP_R7_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
newline .FILL x0a 
input_counter .FILL #5      
pos_sign .FILL #-43
neg_sign .FILL #-45
check_nine .FILL #-57
check_zero .FILL #-48
enter_character .FILL #-10
message .FILL x6000
in_message .FILL x6053
input_arr .FILL x5000
num_sign .FILL #-35
;;;powers of ten
one .FILL #1
ten .FILL #10
hundred .FILL #100
thousand .FILL #1000
ten_thousand .FILL #10000
powers_of_ten_counter .FILL #10


.orig x3400 
ST R7, BACKUP_R7_3400
ST R4, BACKUP_R4_3400
ST R6, BACKUP_R6_3400
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
ADD R2, R1, #0
LD R3, three_sixteen
ADD R4, R4, #0
BRz first_number
BRp second_number
BRn third_number
second_number
LD R3, two_sixteen
BRnzp first_number
third_number
LD R3, one_sixteen
BRnzp first_number
first_number
ADD R2, R2, #0
BRn addition_loop
ADD R0, R2, R3
BRn skip_addition_loop
addition_loop
ADD R5, R5, #1
ADD R2, R2, R3
BRn addition_loop
skip_addition_loop
LD R4, BACKUP_R4_3400
LD R6, BACKUP_R6_3400
LD R7, BACKUP_R7_3400
RET
;;;;data
BACKUP_R7_3400 .BLKW #1
BACKUP_R4_3400 .BLKW #1
BACKUP_R6_3400 .BLKW #1
three_sixteen .FILL #-4096
two_sixteen .FILL #-256
one_sixteen .FILL #-16


.orig x3600
ST R7, BACKUP_R7_3600
ST R4, BACKUP_R4_3600
ST R6, BACKUP_R6_3600
AND R0, R0, #0
AND R3, R3, #0
LD R3, sixteen_cubed
ADD R4, R4, #0
BRz number_first
BRp number_second
BRn number_third
number_second
LD R3, sixteen_squared
BRnzp number_first
number_third
LD R3, sixteen_one
BRnzp number_first
number_first
ADD R2, R2, #0
BRzp positive_to_negative_minus_one_loop
ADD R0, R2, R3
BRn skip_positive_to_negative_minus_one_loop
positive_to_negative_minus_one_loop
ADD R5, R5, #1
ADD R2, R2, R3
BRzp positive_to_negative_minus_one_loop
NOT R3, R3
ADD R3, R3, #1
ADD R2, R2, R3
ADD R5, R5, #-1 
AND R1, R1, #0
ADD R1, R2, #0
skip_positive_to_negative_minus_one_loop
LD R4, BACKUP_R4_3600
LD R6, BACKUP_R6_3600
LD R7, BACKUP_R7_3600
RET
;;;DATA
BACKUP_R7_3600 .BLKW #1
BACKUP_R4_3600 .BLKW #1
BACKUP_R6_3600 .BLKW #1
sixteen_cubed .FILL #-4096
sixteen_squared .FILL #-256
sixteen_one .FILL #-16


.orig x3800
ST R7, BACKUP_R7_3800
ST R4, BACKUP_R4_3800
ST R0, BACKUP_R0_3800
ST R1, BACKUP_R1_3800
ST R2, BACKUP_R2_3800
ST R3, BACKUP_R3_3800
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
;;;to check for 15(F)
ADD R4, R5, #-15
BRnp NOT_F
LD R0, f
STR R0, R6, #0
BRnzp final
NOT_F
AND R4, R4, #0
ADD R4, R5, #-14
BRnp NOT_E
LD R0, e
STR R0, R6, #0
BRnzp final
NOT_E
AND R4, R4, #0
ADD R4, R5, #-13
BRnp NOT_D
LD R0, d
STR R0, R6, #0
BRnzp final
NOT_D
AND R4, R4, #0
ADD R4, R5, #-12
BRnp NOT_C
LD R0, c
STR R0, R6, #0
BRnzp final
NOT_C
AND R4, R4, #0
ADD R4, R5, #-11
BRnp NOT_B
LD R0, b
STR R0, R6, #0
BRnzp final
NOT_B
AND R4, R4, #0
ADD R4, R5, #-10
BRnp NOT_A
LD R0, a
STR R0, R6, #0
BRnzp final
NOT_A
AND R4, R4, #0
LD R4, conversion
ADD R5, R4, R5
STR R5, R6, #0
final
ADD R6, R6, #1
AND R5, R5, #0
LD R7, BACKUP_R7_3800
LD R4, BACKUP_R4_3800
LD R0, BACKUP_R0_3800
LD R1, BACKUP_R1_3800
LD R2, BACKUP_R2_3800
LD R3, BACKUP_R3_3800
RET
BACKUP_R7_3800 .BLKW #1
BACKUP_R4_3800 .BLKW #1
BACKUP_R0_3800 .BLKW #1
BACKUP_R1_3800 .BLKW #1
BACKUP_R2_3800 .BLKW #1
BACKUP_R3_3800 .BLKW #1
neg_ten .FILL #-10
a .FILL x41
neg_eleven .FILL #-11
b .FILL x42
neg_twelve .FILL #-12
c .FILL x43
neg_thirteen .FILL #-13
d .FILL x44
neg_fourteen .FILL #-14
e .FILL x45
neg_fifteen .FILL #-15
f .FILL x46
conversion .FILL #48
.orig x4000
ST R7, BACKUP_R7_4000
AND R1, R1, #0
ADD R1, R1, #4
LD R6, array
output_loop
LDR R0, R6, #0 
OUT
ADD R6, R6, #1
ADD R1, R1, #-1
BRp output_loop
LD R7, BACKUP_R7_4000
RET
BACKUP_R7_4000 .BLKW #1
array .FILL x5200
.orig x5000
input_storage .BLKW #6 
.orig x5200
hex_storage .BLKW #4
.orig x6000
orig_message   .STRINGZ "Plese input a decimal number (max 5 digits) between 0 and 65535, preceded with #, followed by ENTER \n"
