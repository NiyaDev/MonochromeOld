;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Polls currently stored controls
;;=		INPUT:		RCX = control
;;=						0:Down		1:Up		2:Left		3:Right
;;=						4:Confirm	5:Cancel	6:Start		7:Select
;;=		Output:		RAX = buttonData
;;=						0:None		1:Tap		2:Hold
output				equ		rax		;Output

outputWord			equ		ax
selectionHigh		equ		ch
selectionWord		equ		cx

playerMemory		equ		r8
playerDirection		equ		r8+PlayerData.ctrData.direction
poll_controls:
	sub		rsp,	28h

.initialize:
	xor		output,					output
	xor		selectionHigh,			selectionHigh
	mov		playerMemory,			[player_memory]

;;TODO: Test if the control byte is greater than 3,
;;TODO: If so, poll in action, rather than direction

.poll:
	bt		[playerDirection],		selectionWord
	jnc		.exit

	add		outputWord,				1
	add		selectionWord,			12
	bt		[playerDirection],		selectionWord
	jnc		.exit

	add		outputWord,				1

.exit:
	add		rsp,28h
	ret