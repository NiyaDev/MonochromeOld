;format PE64 console 6.0		;; Windows w/  Console
format PE64 NX GUI 6.0		;; Windows w/o Console
;format ELF64 6.0			;; Linux
entry start


include 'include/win64a.inc'
include 'constants.inc'


section '.text' code readable executable
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
	call [WindowShouldClose]
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
include 'idata.inc'