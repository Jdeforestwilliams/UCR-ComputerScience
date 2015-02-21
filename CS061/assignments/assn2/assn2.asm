;=================================================
; 
; Name: DeForest-Williams, Joshua
; Login id: Jdefo002    
; 
; Assignment name: <assn 2>
; Lab section: <021>
; TA: Sean Allen
; 
; I hereby certify that the contents of this file
; are ENTIRELY my own original work. 
;
;=================================================
.orig x3000
LD R2, NEGATIVE  ;; to put th negative sign in R2
GETC             ;; to input the number
ADD R5, R0, #0   ;; to store the number 
GETC             ;; to input the second number
ADD R6, R0, #0   ;; to store second number
LD R3, CONVERSION_NUMBER ;; to convert symbol number to actual number
NOT R4, R3       ;; to get the 1's complement of the conversion 
ADD R4, R4, #1   ;; to get the 2's complement of the conversion 
ADD R5, R4, R5   ;; to get the actual number for the first input
ADD R6, R4, R6   ;; to get the actual number for the second input
NOT R6, R6       ;; to get the 1's complement for the second input
ADD R6, R6, #1   ;; to get the 2's complement for the second input
ADD R1, R5, R6   ;; to subtract R6 (two's complement of original input) 
                 ;; from R5
BRn NEG          ;; to output the negative sign 
BRnzp END        ;; used to output the answer
NEG:      
ADD R0, R2, #0   ;; to put the negative sign in R0
OUT              ;; to output the negative sign 
NOT R1, R1       ;; to get the positive form of the number 
ADD R1, R1, #1   ;; to get the positive form of the number
END:
ADD R0, R1, R3   ;; to get the symbol number of the answer
OUT              ;; to output R0
HALT

;;data fields
CONVERSION_NUMBER .FILL #48
NEGATIVE .FILL 0x2d

