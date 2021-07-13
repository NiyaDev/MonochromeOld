;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Polls currently stored controls
;;=		Input:		RCX = control
;;=						0:Down		1:Up		2:Left		3:Right
;;=						4:Confirm	5:Cancel	6:Start		7:Select
;;=		Output:		RAX = buttonData
;;=						0:None		1:Tap		2:Hold
controlNumber		equ		rcx		;Input
output				equ		rax		;Output

playerMemory		equ		r8
playerInput			equ		r8+PlayerData.ctrData.input
playerTap			equ		r8+PlayerData.ctrData.tap
poll_controls:
	sub		rsp,	28h
	push	rbx

.initialize:
	xor		output,					output
	mov		playerMemory,			[player_memory]
	mov		rbx,					[playerInput]

.poll:
	bt		rbx,					controlNumber
	jnc		.exit
	inc		output
;	shl		controlNumber,			64

	add		rbx,					64
	bt		rbx,					controlNumber
	jnc		.exit
	inc		output

.exit:
	pop		rbx
	add		rsp,	28h
	ret