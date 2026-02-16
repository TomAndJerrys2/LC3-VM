.ORIG x3000				; address in memory where the program will be
loaded 	
LEA R0, HELLO_STR 			; load the address of this string into R0
PUTs					; output the string in R0 to the console
HALT					; halt the program
HELLO_STR .STRINGZ "Hello, World!"	; store the string in the program
.END					; marks end of file
