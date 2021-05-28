
include 'include/win64a.inc'
include 'constants.inc'


;;=  Windows
format MS64 COFF
;;=  Linux
;format ELF64 executable 3

section '.text' code readable executable

;*
;*	Don't know if these are important yet
;*;entry start
;*;public Main
;*;public start as '_start'
;*
public start as 'WinMain'

start:
	; Make stack dqword aligned
	sub	rsp,8
	sub rsp,$100

.init:
	;;ProgramInit()
	call program_init

.loop:
	;;Update()
	call update
	;;Draw()
	call draw
	
	;;While (!WindowShouldClose())
	call WindowShouldClose
	cmp rax,1
	jnz .loop

.exit:
	;;ProgramExit()
	call program_exit
	
	ret



include 'routines/update.inc'
include 'routines/draw.inc'
include 'utilities/program_init.inc'
include 'utilities/program_exit.inc'


include 'data.inc'
include 'imports.inc'