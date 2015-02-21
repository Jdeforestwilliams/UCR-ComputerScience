;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:jdefo002
; 
; Assignment name: Lab 6 Ex1
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;assn4;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.ORIG x3000

LD R5, enter_character ;used to check for when input is over 
;; big loop to start over if error input 
Invalid 
LD R3, input_counter
LD R6, input_arr
LD R4, pos_sign
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
    Getc
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
    BRnz ELSE
    ADD R0, R0, R5
    BRnp Input
INPUT_END  
ELSE: 
;; to reset the counter and the array position
LD R3, input_counter
LD R6, input_arr
AND R2, R2, #0
ADD R6, R6, #1
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
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
LD R5, one 
ADD R6, R6, #-1
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
LDR R2, R6, #0
BRz past_ten ;; if the value in the array is zero no need to add anything
ten_loop
    ADD R1, R1, R5 
    ADD R2, R2, #-1
BRp ten_loop
past_ten
;; loop for the number in the hundred's spot
LD R5, hundred 
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
ADD R1, R1, #1
LD R6, output
JSRR R6
HALT            ; terminates program execution
;;;Data Fields;;;   
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
output .fill x3200
;;;powers of ten
one .FILL #1
ten .FILL #10
hundred .FILL #100
thousand .FILL #1000
ten_thousand .FILL #10000
powers_of_ten_counter .FILL #10

.orig x3200 
ST R7, BACKUP_R7_3200
;;;;ten thousand
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
AND R6, R6, #0
ADD R3, R1, R3
BRp loops
LD R0, neg_sign_1
OUT
AND R0, R0, #0
NOT R1, R1
ADD R1, R1, #1
loops
LD R4, neg_ten_thousand
ten_thousand_loop_2
ADD R6, R6, #1
ADD R3, R3, R4
BRp ten_thousand_loop_2
ADD R6, R6, #-1
BRz skip_ten_thousand
LD R5, ten_thousand_2
output_ten_thousand_loop
ADD R0, R0, #1
ADD R2, R2, R5
ADD R6, R6, #-1
BRp output_ten_thousand_loop 
skip_ten_thousand
LD R4, convert
ADD R0, R0, R4
OUT
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;thousand
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
AND R6, R6, #0
ADD R3, R1, R3
BRz exit
LD R4, neg_thousand
thousand_loop_2
ADD R6, R6, #1
ADD R3, R3, R4
BRp thousand_loop_2
ADD R6, R6, #-1
BRz skip_thousand
LD R5, thousand_2
output_thousand_loop
ADD R0, R0, #1
ADD R2, R2, R5
ADD R6, R6, #-1
BRp output_thousand_loop 
skip_thousand
LD R4, convert
ADD R0, R0, R4
OUT
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;hundred
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
AND R6, R6, #0
ADD R3, R1, R3
BRz exit
LD R4, neg_hundred
hundred_loop_2
ADD R6, R6, #1
ADD R3, R3, R4
BRp hundred_loop_2
ADD R6, R6, #-1
BRz skip_hundred
LD R5, hundred_2
output_hundred_loop
ADD R0, R0, #1
ADD R2, R2, R5
ADD R6, R6, #-1
BRp output_hundred_loop 
skip_hundred
LD R4, convert
ADD R0, R0, R4
OUT
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;ten
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
AND R6, R6, #0
ADD R3, R1, R3
BRz exit
LD R4, neg_ten
ten_loop_2
ADD R6, R6, #1
ADD R3, R3, R4
BRp ten_loop_2
ADD R6, R6, #-1
BRz skip_ten
LD R5, ten_2
output_ten_loop
ADD R0, R0, #1
ADD R2, R2, R5
ADD R6, R6, #-1
BRp output_ten_loop 
skip_ten
LD R4, convert
ADD R0, R0, R4
OUT
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;one
AND R0, R0, #0
AND R2, R2, #0
AND R3, R3, #0
AND R6, R6, #0
ADD R3, R1, R3
BRz exit
LD R4, neg_one
one_loop_2
ADD R6, R6, #1
ADD R3, R3, R4
BRp one_loop_2

LD R5, one_2
output_one_loop
ADD R0, R0, #1
ADD R2, R2, R5
ADD R6, R6, #-1
BRp output_one_loop 
LD R4, convert
ADD R0, R0, R4
OUT
NOT R2, R2
ADD R2, R2, #1
ADD R1, R2, R1


exit
LD R7, BACKUP_R7_3200
RET
;;;;data for subroutine;;;;
BACKUP_R7_3200 .BLKW #1
output_counter .FILL #5
neg_one .FILL #-1
neg_ten .FILL #-10
neg_hundred .FILL #-100
neg_thousand .FILL #-1000
neg_ten_thousand .FILL #-10000
two_thousand .FILL #2768
seven_hundred .FILL #768
sixty .FILL #68
eight .FILL #8 
one_2 .FILL #1
ten_2 .FILL #10
hundred_2 .FILL #100
thousand_2 .FILL #1000
ten_thousand_2 .FILL #10000
convert .FILL #48
neg_sign_1 .FILL #45
.orig x5000 
input_storage .BLKW #6 
.orig x6000
orig_message   .STRINGZ "Input a 5-digit decimal number, padded with leading zeroes, preceded with +/-\n"
