;*/
;* @Date:		7/14/21
;* @Author:		Szyfr
;*/



;;=  Draws UI elements
;;=		Input:		N/A
;;=		Output:		N/A
drawTextureInputC	equ		rcx
drawTextureInputD	equ		rdx
drawTextureInput8	equ		r8
drawTextureInput9	equ		r9

playerMemory		equ		r8
playerMenu			equ		r8+PlayerData.ctrData.menu
playerWorldPos		equ		r8+PlayerData.entity.worldPos
playerWorldPosX		equ		r8+PlayerData.entity.worldPos.x
playerWorldPosY		equ		r8+PlayerData.entity.worldPos.y

generalMemory		equ		r9
generalDword		equ		r9+GeneralDword
generalVector2		equ		r9+GeneralVector2
generalVector2X		equ		r9+GeneralVector2X
generalVector2Y		equ		r9+GeneralVector2Y
generalMenuSprite	equ		r9+PauseMenuSprite
draw_ui:
	sub		rsp,	28h

.init:
	mov		playerMemory,			[player_memory]
.check_menu:
	cmp		[playerMenu],			1
	jne		.exit

.grab_sprite:
	mov		generalMemory,			[general_memory]
	lea		drawTextureInputC,		[generalMenuSprite]
.generate_x:
	mov		dword[generalDword],	64f
	fld		dword[playerWorldPosX]
	fadd	dword[generalDword]
	fstp	dword[generalVector2X]
.generate_y:
	mov		dword[generalDword],	-240f
	fld		dword[playerWorldPosY]
	fadd	dword[generalDword]
	fstp	dword[generalVector2Y]
.grab_vector2:
	mov 	drawTextureInputD,		[generalVector2]
.draw_sprite:
	mov 	drawTextureInput8,		WHITE
	call	DrawTextureV

.exit:
	add		rsp,	28h
	ret