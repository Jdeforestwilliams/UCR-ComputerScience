;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: <assn 5>
; Lab section: <021>
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000 
LD R6, input_to_decimal
JSRR R6
ADD R2, R1, R2
AND R1, R1, #0
LD R6, input_to_decimal
JSRR R6
LD R6, check_bigger
JSRR R6
HALT
;;;;data
input_to_decimal .FILL x3200
check_bigger .FILL x3400
;; subroutine, input to chracter
.orig x3200 
ST R1, BACKUP_R1_3200
ST R7, BACKUP_R7_3200
ST R2, BACKUP_R2_3200
LD R5, enter_character ;used to check for when input is over 
;; big loop to start over if error input 
Invalid 
LD R3, input_counter
LD R6, input_arr
ADD R1, R1, #0
BRnp switch_array
LD R6, input_second_arr
AND R1, R1, #0
switch_array
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
LD R2, BACKUP_R1_3200
BRnp SKIP_ARRAY_SWITCH
LD R6, input_second_arr
SKIP_ARRAY_SWITCH
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
LD R2, BACKUP_R2_3200
LD R7, BACKUP_R7_3200
RET              ; terminates program execution
;;;Data Fields;;;   
BACKUP_R7_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
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
input_second_arr .FILL x5100

;;;powers of ten
one .FILL #1
ten .FILL #10
hundred .FILL #100
thousand .FILL #1000
ten_thousand .FILL #10000
powers_of_ten_counter .FILL #10

;;;;;;subroutine to check which one is bigger 
.orig x3400 
ST R7, BACKUP_R7_3400
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
AND R0, R0, #0
AND R3, R3, #0
AND R4, R4, #0
AND R5, R5, #0
AND R6, R6, #0
LD R5, neg_sign_1
LD R4, pos_sign_1
LD R6, check_bigger_sign
ADD R1, R1, #0
BRzp not_neg_sign
ST R6, neg_sign_1
ADD R3, R3, #-1
BRnzp sign_complete
not_neg_sign 
ADD R2, R2, #0
BRzp also_not_neg_sign
ST R6, neg_sign_1 
ADD R0, R0, #1
BRnzp sign_complete
also_not_neg_sign
ST R6, pos_sign_1
AND R3, R3, #0
sign_complete
AND R4, R4, #0
AND R5, R5, #0
AND R6, R6, #0
ADD R3, R3, #0
BRz both_positive
NOT R1, R1
ADD R1, R1, #1
ADD R4, R1, R2
BRzp reg_1_sm_both_pos
AND R3, R3, #0
ADD R3, R3, #1
reg_1_sm_both_pos

BRnzp END_ALL
END_ALL
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R7, BACKUP_R7_3400
RET
;;;;;;data 
BACKUP_R7_3400 .BLKW #1
BACKUP_R1_3400 .BLKW #1
BACKUP_R2_3400 .BLKW #1
check_bigger_sign .FILL x5200
neg_sign_1 .FILL #45
pos_sign_1 .FILL #43


.orig x5000 
input_storage .BLKW #6 
.orig x5100 
input_second_storage .BLKW #6
.orig x5200 
sign_arr .BLKW#1 
.orig x6000
orig_message   .STRINGZ "Plese input a decimal number (max 5 digits), preceded with +/‐, followed by ENTER \n"
