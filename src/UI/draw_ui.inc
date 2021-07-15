;*/
;* @Date:		7/14/21
;* @Author:		Szyfr
;*/



;;=  Draws UI elements
;;=		Input:		N/A
;;=		Output:		N/A
playerMemory		equ		r8
playerMenu			equ		r8+PlayerData.ctrData.menu
draw_ui:
	sub		rsp,	28h

.init:
	mov		playerMemory,			[player_memory]
.check_menu:
	cmp		[playerMenu],			1
	jne		.exit

.exit:
	add		rsp,	28h
	ret