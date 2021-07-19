;*/
;* @Date:		7/17/21
;* @Author:		Szyfr
;*/



;;=  Checks for menu input
;;=		Input:		N/A
;;=		Output:		N/A
ui_controls:
	sub		rsp,	28h

.menu_move_init:
	cmp		[playerMenuTimer],		0
	jne		.exit

	xor		pollSelection,			pollSelection
.menu_move_loop:
	call	poll_controls

	cmp		controls,				1
	je		.menu_move

	inc		pollLower

	cmp		pollLower,				1
	jg		.exit
	jle		.menu_move_loop

.menu_move:
	cmp		pollLower,				20h
	je		.increase
	jne		.decrease

.increase:
	mov		[playerMenuTimer],		10
	cmp		[playerCursorLoc],		6
	je		.set_min
	inc		[playerCursorLoc]
	jmp		.exit
.decrease:
	mov		[playerMenuTimer],		10
	cmp		[playerCursorLoc],		0
	je		.set_max
	dec		[playerCursorLoc]
	jmp		.exit

.set_min:
	mov		[playerCursorLoc],		0
	jmp		.exit
.set_max:
	mov		[playerCursorLoc],		6
	jmp		.exit

.exit:
	add		rsp,	28h
	ret