;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002
; 
; Assignment name: <assn 3>
; Lab section: <021>
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000  
LD R5, counter ; to count up to the power of 2^n needed
LD R4, counter ; to set up a second counter 
LD R6, two_n ; to add to itsself to get up to 2^n
LD R1, input ; to load number into R1    
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
HALT
;;;;Data;;;;;
input .FILL #-20 ;number to output in binary
pos .FILL #0  ; used to output 0
neg .FILL #1  ; used to output  1
counter .FILL #16
two_n .FILL #1
convert .FILL#48

