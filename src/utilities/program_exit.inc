;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Closes all systems and memory spaces
program_exit:
	pop rcx

.free_memory_allocations:
	;;MemFree(&general_memory)
	mov rcx,[general_memory]
	call [MemFree]
	;;MemFree(&player_memory)
	mov rcx,[player_memory]
	call [MemFree]
	;;MemFree(&animation_memory)
	mov rcx,[animation_memory]
	call [MemFree]
	
	;;CloseWindowRL()
	call [CloseWindowRL]

	;;ExitProcess(0)
;	mov rcx,0
;	call [ExitProcess]
