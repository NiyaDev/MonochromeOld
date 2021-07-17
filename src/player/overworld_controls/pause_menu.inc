;*/
;* @Date:		7/17/21
;* @Author:		Szyfr
;*/



;;=  Checks for pause menu
;;=		Input:		N/A
;;=		Output:		N/A
controls			equ		al
timerPtr			equ		rcx
pollLower			equ		cl

playerMemory		equ		r8
playerMenu			equ		r8+PlayerData.ctrData.menu
playerMenuTimer		equ		r8+PlayerData.ctrData.menuTimer
check_pause_menu:
	sub		rsp,	28h

.timers:
	mov		playerMemory,			[player_memory]
	lea		timerPtr,				[playerMenuTimer]
	call	update_timer

.check_start:
	mov		pollLower,				6
	call	poll_controls
	cmp		controls,				1
	jne		.exit
.check_timer:
	cmp		[playerMenuTimer],		0
	jne		.exit
	mov		[playerMenuTimer],		15
.check_open:
	cmp		[playerMenu],			1
	je		.reset
	jne		.set

.reset:
	mov		[playerMenu],			0
	jmp		.exit
.set:
	mov		[playerMenu],			1

.exit:
	add		rsp,	28h
	ret



;.pause_check:
;	cmp		[playerMenu],			1
;	je		.no_controls_pressed