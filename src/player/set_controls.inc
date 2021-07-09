;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Gathers currently pressed keys and stores them
;;=		INPUT:		N/A
;;=		Output:		N/A
;;TODO:	set up keybindings
output				equ		rax
outputByte			equ		al
keyInput			equ		ecx

playerMemory		equ		r8
playerDirection		equ		r8+PlayerData.ctrData.direction
set_controls:
	sub		rsp,	28h

	push	rcx
	push	r8

.initialize:
	xor		output,					output
	mov		playerMemory,			[player_memory]
.shift_last_bits:
	shl		[playerDirection],		4

.check_down:
	mov		keyInput,				KEY_S
	call	IsKeyDown
	cmp		outputByte,				1
	jne		.check_up
	bts		[playerDirection],		dirDown
.check_up:
	mov		keyInput,				KEY_W
	call	IsKeyDown
	cmp		outputByte,				1
	jne		.check_left
	bts		[playerDirection],		dirUp
.check_left:
	mov		keyInput,				KEY_A
	call	IsKeyDown
	cmp		outputByte,				1
	jne		.check_right
	bts		[playerDirection],		dirLeft
.check_right:
	mov		keyInput,				KEY_D
	call	IsKeyDown
	cmp		outputByte,				1
	jne		.exit
	bts		[playerDirection],		dirRight

;;TODO: Scan for action keys as well

.exit:
	pop		rcx
	pop		r8

	add		rsp,	28h
	ret