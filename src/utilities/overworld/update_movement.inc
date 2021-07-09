;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/



;;=  Updates movement of the input entity
;;=		INPUT:		RCX = entity
;;=		Output:		N/A
entityPtr			equ		rcx		;Input

positionCheck		equ		rax
directionCheck		equ		ebx
movementCompare		equ		ebx

entityMoving		equ		rcx+Entity.isMoving
entityTilePos		equ		rcx+Entity.tilePos
entityTilePosX		equ		rcx+Entity.tilePos.x
entityTilePosY		equ		rcx+Entity.tilePos.y
entityWorldPos		equ		rcx+Entity.worldPos
entityWorldPosX		equ		rcx+Entity.worldPos.x
entityWorldPosY		equ		rcx+Entity.worldPos.y

generalMemory		equ		r8
generalDword		equ		r8+GeneralDword
update_movement:
	sub		rsp,28h

	mov		positionCheck,			[entityWorldPos]
	cmp		positionCheck,			[entityTilePos]
	je		.equal_exit
	mov		[entityMoving],			1

.determine_direction:
	mov		directionCheck,			[entityTilePosY]
	cmp		directionCheck,			[entityWorldPosY]
	jne		.move_y

.move_x:
	mov		movementCompare,		[entityWorldPosX]
	cmp		movementCompare,		[entityTilePosX]
	jl		.move_positive
	jmp		.move_negative
.move_y:
	add		entityPtr,				4
	mov		movementCompare,		[entityWorldPosX]
	cmp		movementCompare,		[entityTilePosX]
	jl		.move_positive
	jmp		.move_negative

.move_positive:
	mov		generalMemory,			[general_memory]
	mov		[generalDword],			movementCompare
	fld		dword[generalDword]
	mov		dword[generalDword],	walkSpeed
	fadd	dword[generalDword]
	fstp	dword[generalDword]
	mov		movementCompare,		[generalDword]
	mov		[entityWorldPosX],		movementCompare
	jmp		.exit
.move_negative:
	mov		generalMemory,			[general_memory]
	mov		dword[generalDword],	movementCompare
	fld		dword[generalDword]
	mov		dword[generalDword],	walkSpeed
	fsub	dword[generalDword]
	fstp	dword[generalDword]
	mov		movementCompare,		[generalDword]
	mov		[entityWorldPosX],		movementCompare
	jmp		.exit

.equal_exit:
	mov		[entityMoving],			0

.exit:
	add		rsp,28h
	ret