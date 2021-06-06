;*/
;* @Date:		5/22/21
;* @Author:		Szyfr
;*/


include 'constants.inc'

;;=  Windows
format MS64 COFF
;;=  Linux
;TODO: Still gotta work on getting linux support working
;format ELF64 executable 3

section '.text' code readable executable
public start as 'WinMain'


start:
	sub	rsp,	8
	sub rsp,	$100

.init:
	call	program_init

.loop:
	call	update
	call	draw
	
	call	WindowShouldClose
	cmp		rax,				1
	jnz		.loop

.exit:
	call	program_exit
	
	ret



include 'routines/update.inc'
include 'routines/draw.inc'
include 'utilities/program_init.inc'
include 'utilities/program_exit.inc'


include 'data.inc'
include 'imports.inc'


;*
;*	Don't know if these are important
;*;include 'include/win64a.inc'
;*;entry start
;*;public Main
;*;public start as '_start'
;*