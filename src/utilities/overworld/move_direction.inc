;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Calculates the new world position based on the current position and the direction
;;=		INPUT:		RCX = tilePosition
;;=					RDX = direction
;;=		Output:		RAX = newPosition
tilePosition		equ		rcx		;Input
direction			equ		rdx		;Input
newPosition			equ		rax		;Output

generalMemory		equ		r9
generalDword		equ		r9+GeneralDword
generalVector2		equ		r9+GeneralVector2
generalVector2X		equ		r9+GeneralVector2X
generalVector2Y		equ		r9+GeneralVector2Y
move_direction:
	sub		rsp,28h

	mov		generalMemory,			[general_memory]
	mov		[generalVector2],		tilePosition
	mov		dword[generalDword],	64f

	cmp		direction,				dirDown
	jz		.move_down
	cmp		direction,				dirUp
	jz		.move_up
	cmp		direction,				dirLeft
	jz		.move_left
	cmp		direction,				dirRight
	jz		.move_right
	jmp		.exit

.move_down:
	fld		dword[generalVector2Y]
	fadd	dword[generalDword]
	fstp	dword[generalVector2Y]
	jmp		.exit
.move_up:
	fld		dword[generalVector2Y]
	fsub	dword[generalDword]
	fstp	dword[generalVector2Y]
	jmp		.exit
.move_left:
	fld		dword[generalVector2X]
	fsub	dword[generalDword]
	fstp	dword[generalVector2X]
	jmp		.exit
.move_right:
	fld		dword[generalVector2X]
	fadd	dword[generalDword]
	fstp	dword[generalVector2X]
	jmp		.exit

.exit:
	mov		newPosition,			[generalVector2]

	add		rsp,28h
	ret