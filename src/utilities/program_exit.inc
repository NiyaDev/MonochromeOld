;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/

;;=  Closes all systems and memory spaces
program_exit:
	sub		rsp,28h

.free_memory_allocations:
	;;MemFree(&general_memory)
	mov		rcx,[general_memory]
	call	[MemFree]
	;;MemFree(&player_memory)
	mov		rcx,[player_memory]
	call	[MemFree]
	;;MemFree(&animation_memory)
	mov		rcx,[animation_memory]
	call	[MemFree]
	
	;;CloseWindowRL()
	call [CloseWindowRL]

	add		rsp,28h
	ret
