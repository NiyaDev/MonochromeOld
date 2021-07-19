;*/
;* @Date:		7/17/21
;* @Author:		Szyfr
;*/



;;=  Checks for movement input
;;=		Input:		N/A
;;=		Output:		RAX = output
;;=						0 = Jump to .player_movement
;;=						1 = Jump to .no_controls_pressed
output				equ		rax
pollLower			equ		cl

playerMoving		equ		r8+PlayerData.entity.isMoving
playerDirection		equ		r8+PlayerData.entity.direction

animation			equ		r10
animationByte		equ		r10b
movement_controls:
	sub		rsp,	28h

.overworld_move_init:
	xor		pollLower,				pollLower
	mov		animation,				3
.overworld_move_loop:
	call	poll_controls

	inc		pollLower
	inc		animation

	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold

	cmp		animation,				7
	jg		.no_pressed
	jle		.overworld_move_loop

.hold:
	mov		[playerDirection],		animationByte
	mov		[playerMoving],			1
	jmp		.exit
.tap:
	mov		[playerDirection],		animationByte
	sub		[playerDirection],		4
	jmp		.exit

.exit:
	xor		output,					output
	add		rsp,	28h
	ret

.no_pressed:
	mov		output,					1
	add		rsp,	28h
	ret