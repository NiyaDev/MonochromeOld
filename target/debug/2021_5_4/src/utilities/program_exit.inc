;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Closes all systems and memory spaces
program_exit:
	pop [home]

	;;MemFree(&general_memory)
	mov rcx,[general_memory]
	call [MemFree]
	
	;;CloseWindowRL()
	call [CloseWindowRL]

	;;ExitProcess(0)
	mov rcx,0
	call [ExitProcess]

	push [home]
	ret