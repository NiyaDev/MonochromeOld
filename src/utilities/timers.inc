;*/
;* @Date:		7/16/21
;* @Author:		Szyfr
;*/



;;=  Updates timers
;;=		Input:		RCX = timerPtr
;;=		Output:		N/A
timerPtr			equ		rcx
update_timer:
	sub		rsp,	28h

	cmp		byte[timerPtr],			0
	je		.exit

	sub		byte[timerPtr],			1

.exit:
	add		rsp,	28h
	ret