;*/
;* @Date:		7/17/21
;* @Author:		Szyfr
;*/



;;=  Checks for movement input
;;=		Input:		N/A
;;=		Output:		N/A
pollLower			equ		cl
animation			equ		r10
check_overworld_movement:
	sub		rsp,	28h

.init:
	xor		pollLower,				pollLower
	xor		animation,				animation
.loop:
	mov		pollLower,				dirDown
	call	poll_controls

.exit:
	add		rsp,	28h
	ret

.poll_down:
	mov		pollLower,				dirDown
	call	poll_controls

	mov		animation,				4
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_up:
	mov		pollLower,				dirUp
	call	poll_controls

	mov		animation,				5
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_left:
	mov		pollLower,				dirLeft
	call	poll_controls

	mov		animation,				6
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_right:
	mov		pollLower,				dirRight
	call	poll_controls

	mov		animation,				7
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold


.hold:
	mov		[playerDirection],		animationByte
	mov		[playerMoving],			1
	jmp		.player_movement
.tap:
	mov		[playerDirection],		animationByte
	sub		[playerDirection],		4
	jmp		.player_movement