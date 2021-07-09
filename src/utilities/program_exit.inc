;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/

;;=  Closes all systems and memory spaces
generalMemory		equ		rcx
playerMemory		equ		rcx
animationMemory		equ		rcx
program_exit:
	sub		rsp,	28h

.free_memory_allocations:
	mov		generalMemory,			[general_memory]
	call	MemFree
	mov		playerMemory,			[player_memory]
	call	MemFree
	mov		animationMemory,		[animation_memory]
	call	MemFree
	
	call	CloseWindowRL

	add		rsp,	28h
	ret
