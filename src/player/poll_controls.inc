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
compared			equ		rbx

playerMemory		equ		r8
playerInput			equ		r8+PlayerData.ctrData.input
playerTap			equ		r8+PlayerData.ctrData.tap
poll_controls:
	sub		rsp,	28h
	push	rbx

.initialize:
	xor		output,					output
	mov		playerMemory,			[player_memory]
	mov		compared,				[playerInput]

.poll:
	bt		compared,				controlNumber
	jnc		.exit
	inc		output
	add		controlNumber,			32

	bt		compared,				controlNumber
	jnc		.exit
	inc		output

.exit:
	pop		rbx
	add		rsp,	28h
	ret