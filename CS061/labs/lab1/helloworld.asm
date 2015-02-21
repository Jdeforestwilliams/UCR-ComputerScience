;; This buffer is for notes you don't want to save, and for Lisp evaluation.
;; If you want to create a file, visit that file with C-x C-f,
;; then enter the text in that file's own buffer.

          ;; hello world program

          .ORIG x3000

          LEA R0, message ; stores address of start of message R0
          PUTS            ; invokes BIOS routine to output string
          HALT            ; terminates program execution


          ;; end of code

          ;; data block
message   .STRINGZ "Hello World!!\n"
                         ; store 'H' in address labelled "message"
                         ; and then one character per memory address

          .END           ; tells assembler to stop reading and start assembling