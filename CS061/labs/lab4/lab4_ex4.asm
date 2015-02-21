;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id:Jdefo002 
; 
; Assignment name: Lab 4 Ex4
; Lab section: <021>
; TA:Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000  
LD R2, big_counter ;; to set a big loop counter
;;ex 3
LD R6, big_counter
LD R3, store
LD R1, pos
ADD R1, R1, #1
STR R1, R3, #0
Loop:
    ADD R1, R1, R1
    ADD R3, R3, #1
    STR R1, R3, #0
    ADD R4, R6, #-5
    ADD R6, R6, #-1
BRp Loop
;; assn3

 LD R3, store  
OUTER_LOOP
LD R5, counter ; to count up to the power of 2^n needed
LD R4, counter ; to set up a second counter 
LD R6, two_n ; to add to itsself to get up to 2^n
 

assn_LOOP
AND R1, R1, #0
LDR R0, R3, #0
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
    ADD R1, R0, R6 ;to store/test the number of the input minus the 2^n number 
    BRz NEGATIVE ; if statement to output a 1 if needed
        LD R0, ZERO  ; used to output a zero 
        OUT ; used to output a zero
        BRnzp ELSE ;branch used to skip if output a 0
        NEGATIVE ; if statement to output a 1 if needed
            ADD R0, R0, R6 
            LD R0, ONE
            OUT 
    ELSE
        
        LD R6, two_n
        ADD R4, R4, #-1
        ADD R5, R4, #0
        ADD R4, R4, #0
    BRzp assn_LOOP
    
    GO_TO_END
   
    ADD R3, R3, #1   ;to move the array
    LD R0, newline
    OUT

    ADD R2, R2, #-1
BRp OUTER_LOOP
HALT
;;;;Data;;;;;
pos .FILL #0
ZERO .FILL #48  ; used to output 0
ONE .FILL #49  ; used to output  1
big_counter .FILL #10
counter .FILL #16
two_n .FILL #1
store .FILL x5000
newline .FILL x0a
.orig x5000
ARR .BLKW #10
