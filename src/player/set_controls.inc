;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Gathers currently pressed keys and stores them
;;=		Input:		N/A
;;=		Output:		N/A
result				equ		rax
outputByte			equ		al
counter				equ		rbx
keyInputFull		equ		rcx
keyInput			equ		cx

playerMemory		equ		r8
playerInput			equ		r8+PlayerData.ctrData.input
playerDirection		equ		r8+PlayerData.ctrData.direction
playerAction		equ		r8+PlayerData.ctrData.action
playerKeys			equ		r8+PlayerData.keyBindings

keybindingsPtr		equ		r9
inputPtr			equ		r10
set_controls:
	sub		rsp,	28h
	push	rbx
	push	r8
	push	r9

.setup:
	xor		result,					result
	xor		keyInputFull,			keyInputFull
	mov		playerMemory,			[player_memory]
	shl		[playerInput],			8

	lea		keybindingsPtr,			[playerKeys]
	lea		inputPtr,				[playerInput]
	mov		counter,				0

.loop:
	mov		keyInput,				[keybindingsPtr]
	call	IsKeyDown
	cmp		outputByte,				1
	jne		.loop_end
	bts		[inputPtr],				counter
.loop_end:
	add		keybindingsPtr,			2
	inc		counter
	cmp		counter,				8
	jne		.loop

.exit:
	pop		r9
	pop		r8
	pop		rbx
	add		rsp,	28h
	ret