;*/
;* @Date:		5/20/21
;* @Author:		Szyfr
;*/



;;=  void UpdateMovement(Enitity*:entity);
;;=		RCX = entity
update_movement:
	sub		rsp,28h

	mov		rax,[rcx+Entity.worldPos]
	cmp		rax,[rcx+Entity.tilePos]
	je		.equal_exit
	mov		[rcx+Entity.isMoving],1

.determine_direction:
	mov		ebx,[rcx+Entity.tilePos.y]
	cmp		ebx,[rcx+Entity.worldPos.y]
	jne		.move_y

.move_x:
	mov		ebx,[rcx+Entity.worldPos.x]
	cmp		ebx,[rcx+Entity.tilePos.x]
	jl		.move_positive
	jmp		.move_negative
.move_y:
	add		rcx,4
	mov		ebx,[rcx+Entity.worldPos.x]
	cmp		ebx,[rcx+Entity.tilePos.x]
	jl		.move_positive
	jmp		.move_negative
.move_positive:
	mov		r8,[general_memory]
	mov		[r8+GeneralDword],ebx
	fld		dword[r8+GeneralDword]
	mov		dword[r8+GeneralDword],walkSpeed
	fadd	dword[r8+GeneralDword]
	fstp	dword[r8+GeneralDword]
	mov		ebx,dword[r8+GeneralDword]
	mov		[rcx+Entity.worldPos.x],ebx
	jmp		.exit
.move_negative:
	mov		r8,[general_memory]
	mov		dword[r8+GeneralDword],ebx
	fld		dword[r8+GeneralDword]
	mov		dword[r8+GeneralDword],walkSpeed
	fsub	dword[r8+GeneralDword]
	fstp	dword[r8+GeneralDword]
	mov		ebx,dword[r8+GeneralDword]
	mov		[rcx+Entity.worldPos.x],ebx
	jmp		.exit

.equal_exit:
	mov		[rcx+Entity.isMoving],0

.exit:
	add		rsp,28h
	ret

;;=  Vector2 MoveDirection(Vector2:tilePosition, int:direction);
;;=  RCX = tilePosition		RDX = direction
move_direction:
	sub		rsp,28h

	mov		r9,[general_memory]
	mov		qword[r9+GeneralVector2],rcx
	mov		dword[r9+GeneralDword],64f

	cmp		rdx,0			;down
	jz		.move_down
	cmp		rdx,3			;right
	jz		.move_right
	cmp		rdx,1			;up
	jz		.move_up
	cmp		rdx,2			;left
	jz		.move_left
	jmp		.exit

.move_down:					;down
	fld		dword[r9+GeneralVector2Y]
	fadd	dword[r9+GeneralDword]
	fstp	dword[r9+GeneralVector2Y]
	jmp		.exit
.move_right:				;right
	fld		dword[r9+GeneralVector2X]
	fadd	dword[r9+GeneralDword]
	fstp	dword[r9+GeneralVector2X]
	jmp		.exit
.move_up:					;up
	fld		dword[r9+GeneralVector2Y]
	fsub	dword[r9+GeneralDword]
	fstp	dword[r9+GeneralVector2Y]
	jmp		.exit
.move_left:					;left
	fld		dword[r9+GeneralVector2X]
	fsub	dword[r9+GeneralDword]
	fstp	dword[r9+GeneralVector2X]
	jmp		.exit

.exit:
	mov		rax,[r9+GeneralVector2]
	add		rsp,28h
	ret