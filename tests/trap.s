; this is just an arbitrary example of the trap instructions
; that would get used by a regular LC3 machine

;; example of the operating systems entry point
;; which is usually at 0x0200
OS_START
	;; set the memory protection register
	LD R0, MPR_INIT
	STI R0, OS_MPR

	;; set timer interval on sys clock
	LD R0, TIM_INIT
	STI R0, OS_TMI

	;; start running the code
	LD R7, USER_CODE_ADDR
	JMPT	R7

;; Memory mapped registers - behind the scenes
OS_KBSR .FILL xFE00	; keyboard status MMR
OS_KBDR .FILL xFE02	; keyboard data register
OS_DSR  .FILL xFE04	; display status MMR
OS_DDR  .FILL xFE06	; display data MMR
OS_TR 	.FILL xFE08	; timer register
OS_TMI	.FILL xFE0A	; timer interval register
OS_MPR	.FILL xFE12	; MPR - memory protection register
OS_MCR  .FILL xFFFE	; machine control register

;; Save blocks of memory
;; this sets asside a number of sequential memory
;; locations for in the program, making it more 
;; efficient when it comes to eventually storing values
;; or even multiple values in a single operation
OS_SAVE_R0	.BLKW 1
OS_SAVE_R1	.BLKW 1
OS_SAVE_R2	.BLKW 1
OS_SAVE_R3      .BLKW 1
OS_SAVE_R4      .BLKW 1
OS_SAVE_R5	.BLKW 1
OS_SAVE_R6	.BLKW 1
OS_SAVE_R7	.BLKW 1

OS_OUT_SAVE_R1  .BLKW 1
OS_IN_SAVE_R1	.BLKW 1

;; 
MASK_HI		.FILL x7FFF
LOW_8_BITS	.FILL x00FF
