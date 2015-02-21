;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: assn 7
; Lab section: 021
; TA: Sean Allen 
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
;-----------------------------------------------------------------------------------------------------------------
; Main code block
; Description: Tests functionality of the system by calling the written subroutines
;-----------------------------------------------------------------------------------------------------------------
.ORIG x3000
; Instructions
; load parameters for INPUT_SENTENCE
LD R1, string_array
LD R0, INPUT_SENTENCE
; call INPUT_SENTENCE
JSRR R0
; load parameters for FIND_LONGEST WORD
LD R6, string_array
LD R0, FIND_LONGEST_WORD
; call FIND_LONGEST_WORD
JSRR R0
; load parameters for PRINT_ANALYSIS
LD R6, string_array
LD R0, PRINT_ANALYSIS  
; call PRINT_ANALYSIS
JSRR R0
HALT
; Local Data
; whatever local data you need
INPUT_SENTENCE .FILL x3200
FIND_LONGEST_WORD .FILL x3400
PRINT_ANALYSIS .FILL x3600
string_array .FILL x5000
;-----------------------------------------------------------------------------------------------------------------
; Subroutine: INPUT_SENTENCE
; Input (R1): The address of where to store the array of words
; Postcondition: The subroutine has collected an ENTER-terminated string of words from
; the user and stored them in consecutive memory locations, starting at (R6).
; Return Value: None
;-----------------------------------------------------------------------------------------------------------------
.orig x3200
ST R7, BACKUP_R7_3200
LD R0, prompt
PUTS

AND R5, R5, #0   ;;;; to be used for counter
input_loop
LD R4, enter_check
Getc
ADD R4, R0, R4 ;;; to check if the enter key has been hit 
BRnp keep_going
LD R4, enter_check 
OUT
ADD R0, R0, R4
STR R0, R1, #0 ;;; to store it in the array 
ADD R1, R1, #1
ADD R5, R5, #1
GETC
LD R4, enter_check
ADD R4, R0, R4 ;;; to check if the second one is zero to end the array
BRz break_out_of_input
keep_going
STR R0, R1, #0 ;; to store it in the array when its not a zero
OUT
ADD R1, R1, #1
ADD R5, R5, #1
BRnzp input_loop
break_out_of_input
LD R0, newline ;; to output a new line for the output later 
OUT
AND R4, R4, #0 ;; to set it back to 0 for future use
LD R7, BACKUP_R7_3200
RET

;;;data
BACKUP_R7_3200 .BLKW #1
enter_check .FILL #-10 
newline .fill x0a
prompt .FILL x7500

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: FIND_LONGEST_WORD
; Input (R6): The address of the array of words
; Postcondition: The subroutine has located and the longest word in the array of words
; Return value (R2): The address of the beginning of the longest word
;-----------------------------------------------------------------------------------------------------------------
.orig x3400
ST R7, BACKUP_R7_3400
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
AND R5, R5, #0
;;;R6 and r5 traverse the array, 
;;;r3 is counter for r5, r4 is counter for R6 
;;;r2 stores the address of the longest word
ADD R2, R6, #0
first_loop_counter
LDR R0, R6, #0
BRz break_out_first_loop_counter
ADD R6, R6, #1
ADD R4, R4, #1
BRnzp first_loop_counter
break_out_first_loop_counter
ADD R6, R6, #1
ADD R3, R4, #0
AND R4, R4, #0
reset_r5 ;;; to reset R5 for after R2 has the possibility of being set 
ADD R5, R6, #0
loop_counter
LDR R0, R6, #0
BRz break_out_loop_counter
ADD R6, R6, #1
ADD R4, R4, #1
BRnzp loop_counter
break_out_loop_counter
ADD R6, R6, #1
LDR R0, R6, #0
BRz END;;; to jump out if its a double zero
NOT R4, R4
ADD R4, R4, #1
AND R0, R0, #0
ADD R0, R3, R4
BRp clear_values_then_loop_counter
BRn new_is_bigger
BRz same
new_is_bigger;;; if the new word is bigger
ADD R2, R5, #0
AND R3, R3, #0
NOT R4, R4
ADD R4, R4, #1
ADD R3, R4, #0
AND R4, R4, #0
BRnzp reset_r5
same ;; if they are the same store it in R1 to be output later
ADD R1, R5, #0
AND R4, R4, #0
BRnzp reset_r5
clear_values_then_loop_counter ;;; to clear values since the word in R2 is bigger 
AND R4, R4, #0
BRnzp reset_r5
END ;; when the double zero is hit
NOT R4, R4 ;; used to check the last word
ADD R4, R4, #1
AND R0, R0, #0
ADD R0, R3, R4
BRn new_one_is_bigger ;;; still used to check the last word
BRz both_are_equal
BRp skip_keep_going
new_one_is_bigger
ADD R2, R5, #0
AND R3, R3, #0
NOT R4, R4
ADD R4, R4, #1
ADD R3, R4, #0
AND R4, R4, #0
BRnzp skip_keep_going
both_are_equal ;if the last word is equal to an earlier R1/r2 
ADD R1, R5, #0

skip_keep_going ;; used to check to see if last check of R2 
ADD R6, R1, #0  ;; is bigger than an earlier version of R1
AND R4, R4, #0  ;; or if they are the same
checkR1_loop_counter
LDR R0, R6, #0
BRz break_out_checkR1_loop_counter ;; to check out of the R1 checking loop 
ADD R6, R6, #1
ADD R4, R4, #1
BRnzp checkR1_loop_counter
break_out_checkR1_loop_counter
NOT R4, R4
ADD R4, R4, #1
AND R0, R0, #0
ADD R0, R3, R4
BRz R1_same
BRn R1_bigger
AND R1, R1, #0
BRnzp R1_same
R1_bigger
ADD R2, R1, #0
BRnzp R1_same
R1_same
LD R7, BACKUP_R7_3400
RET
BACKUP_R7_3400 .BLKW #1

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: PRINT_ANALYSIS
; Input (R6): The address of the beginning of the array of words
; Input (R2): The address of the longest word
; Postcondition: The subroutine has printed out a list of all the words entered as well as the
; longest word in the sentence.
; Return Value: None
;-----------------------------------------------------------------------------------------------------------------
.orig x3600
ST R7, BACKUP_R7_3600

LD R4, conversion 
output_loop ;; to output the entire sentence 
LDR R0, R6, #0 
BRnp output
ADD R6, R6, #1 
LDR R0, R6, #0
BRz done
ADD R6, R6, #-1
LDR R0, R6, #0
ADD R0, R0, R4
output
OUT
ADD R6, R6, #1
BRnp output_loop
done
LD R0, new_line
PUTS
LD R0, message
PUTS
ADD R0, R2, #0 ;; to output the longest word
PUTS
AND R0, R0, #0 ;; to output the other longest word (if applicable) 
ADD R0, R0, #15
ADD R0, R0, #15
ADD R0, R0, #2
OUT
ADD R0, R1, #0
PUTS
LD R0, new_line
OUT
OUT
LD R7, BACKUP_R7_3600
RET 
BACKUP_R7_3600 .BLKW #1
array .FILL  x5000
conversion .FILL #32
enter_check_3 .FILL #-10 
message .FILL x8000
new_line .FILL x0a

.orig x7500
.STRINGZ "Please enter a sentence with each word separated by ENTER, when done hit ENTER again\n"
.orig x8000
.STRINGZ "\nThe longest word(s) in your sentence is: "
