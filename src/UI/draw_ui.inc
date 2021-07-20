;*/
;* @Date:		7/14/21
;* @Author:		Szyfr
;*/



;;=  Draws UI elements
;;=		Input:		N/A
;;=		Output:		N/A
;;TODO: Go through every external function and define variables
;;	void DrawTexture(Texture2D texture, int posX, int posY, Color tint);
;;	texture				equ		rcx
;;	posX				equ		rdx
;;	posY				equ		r8
;;	tint				equ		r9
drawTextureInputC	equ		rcx
drawTextureInputD	equ		rdx
drawTextureInput8	equ		r8
drawTextureInput9	equ		r9

drawTextExInputC	equ		rcx
drawTextExInputD	equ		rdx
drawTextExInput8	equ		r8
drawTextExInputX0	equ		xmm0
drawTextExInputX3	equ		xmm3
drawTextExInputSt	equ		dword [rsp+0x28]

playerMemory		equ		r8
playerMenu			equ		r8+PlayerData.ctrData.menu
playerCursorLoc		equ		r8+PlayerData.ctrData.cursorLoc
playerWorldPos		equ		r8+PlayerData.entity.worldPos
playerWorldPosX		equ		r8+PlayerData.entity.worldPos.x
playerWorldPosY		equ		r8+PlayerData.entity.worldPos.y

generalMemory		equ		r9
generalDword		equ		r9+GeneralDword
generalQword		equ		r9+GeneralQword
generalVector2		equ		r9+GeneralVector2
generalVector2X		equ		r9+GeneralVector2X
generalVector2Y		equ		r9+GeneralVector2Y
generalMenuSprite	equ		r9+PauseMenuSprite
generalCursorSprite	equ		r9+CursorSprite
generalFont			equ		r9+Font
draw_ui:
	sub		rsp,	48h

.init:
	mov		playerMemory,			[player_memory]
.check_menu:
	cmp		[playerMenu],			1
	jne		.exit

.grab_menu_sprite:
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
.draw_menu:
	mov 	drawTextureInput8,		WHITE
	call	DrawTextureV

.grab_cursor_sprite:
	mov		playerMemory,			[player_memory]
	mov		generalMemory,			[general_memory]
	lea		drawTextureInputC,		[generalCursorSprite]
.generate_cursor_x:
	mov		dword[generalDword],	32f
	fld		dword[generalVector2X]
	fadd	dword[generalDword]
	fstp	dword[generalVector2X]
.generate_cursor_y:
	mov		dword[generalDword],	64f
	fild	dword[playerCursorLoc]
	fmul	dword[generalDword]
	fadd	dword[generalDword]
	fadd	dword[generalVector2Y]
	fstp	dword[generalVector2Y]
.grab_cursor_vector2:
	mov 	drawTextureInputD,		[generalVector2]
.draw_cursor:
	mov 	drawTextureInput8,		WHITE
	call	DrawTextureV

.draw_test_text:
	mov		playerMemory,			[player_memory]
	mov		generalMemory,			[general_memory]

	lea		drawTextExInputC,		[generalFont]
	lea		drawTextExInputD,		[temp_text]
	
.generate_text_x:
	mov		dword[generalDword],	128f
	fld		dword[playerWorldPosX]
	fadd	dword[generalDword]
	fstp	dword[generalVector2X]
.generate_text_y:
	mov		dword[generalDword],	172f
	fld		dword[playerWorldPosY]
	fsub	dword[generalDword]
	fstp	dword[generalVector2Y]
.grab_text_vector2:
	mov 	drawTextExInput8,		[generalVector2]

	mov		dword[generalDword],	32f
	movss	drawTextExInputX3,		[generalDword]
	mov		dword[generalDword],	0f
	movss	drawTextExInputX0,		[generalDword]
	mov		drawTextExInputSt,		BLACK
	call	DrawTextEx

.exit:
	add		rsp,	48h
	ret