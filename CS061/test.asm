.orig x3000
ADD R1, R2, #1
BRzp hi
ADD R6, R6, #1

HALT
hi .fill x4050

.orig x4050
ADD R3, R3, #1
RET
