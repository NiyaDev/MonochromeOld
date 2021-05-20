;*/
;* @Date:		5/20/21
;* @Author:		Szyfr
;*/



;;=  void UpdateMovement(Vector2:tilePosition, Vector2:currentPosition);
update_movement:
	sub		rsp,28h

	add		rsp,28h
	ret

;;=  Vector2 MoveDirection(Vector2:tilePosition, int:direction);
;;=  RCX = tilePosition		RDX = direction
move_direction:
	sub		rsp,28h

	mov		r8,[general_memory]
	mov		[r8+GeneralMemory.v2],rcx
	mov		[r8+GeneralMemory.dword],64f

	cmp		rdx,0			;down
	jz		.move_down
	cmp		rdx,1			;right
	jz		.move_right
	cmp		rdx,2			;up
	jz		.move_up
	cmp		rdx,3			;left
	jz		.move_left
	jmp		.exit

.move_down:					;down
	fld		dword[r8+GeneralMemory.v2.y]
	fadd	dword[r8+GeneralMemory.dword]
	fstp	dword[r8+GeneralMemory.v2.y]
	jmp		.exit
.move_right:				;right
	fld		dword[r8+GeneralMemory.v2.x]
	fadd	dword[r8+GeneralMemory.dword]
	fstp	dword[r8+GeneralMemory.v2.x]
	jmp		.exit
.move_up:					;up
	fld		dword[r8+GeneralMemory.v2.y]
	fsub	dword[r8+GeneralMemory.dword]
	fstp	dword[r8+GeneralMemory.v2.y]
	jmp		.exit
.move_left:					;left
	fld		dword[r8+GeneralMemory.v2.x]
	fsub	dword[r8+GeneralMemory.dword]
	fstp	dword[r8+GeneralMemory.v2.x]
	jmp		.exit

.exit:
	mov		rax,[r8+GeneralMemory.v2]
	add		rsp,28h
	ret