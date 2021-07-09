;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Standard Draw call
begin2DInput		equ		rcx
drawTextureInputC	equ		rcx
drawAnimatedInputC	equ		rcx
clearBGInput		equ		ecx
drawTextureInputD	equ		rdx
drawAnimatedInputD	equ		rdx
drawTextureInput8	equ		r8
drawTextureInput9	equ		r9

playerMemory		equ		r8
playerCamera		equ		r8+PlayerData.camera
playerSprite		equ		r8+PlayerData.entity.sprite
playerWorldPos		equ		r8+PlayerData.entity.worldPos

generalMemory		equ		r8
generalPtr			equ		r8+100
draw:
	sub		rsp,	$28

.begin_draw:
	call	BeginDrawing

.clear_background:
	mov		clearBGInput,			RAYWHITE
	call	ClearBackground

.render_camera:
	mov		playerMemory,			[player_memory]
	lea		begin2DInput,			[playerCamera]
	call	BeginMode2D

.draw_test_texture:
	mov		generalMemory,			[general_memory]
	lea		drawTextureInputC,		[generalPtr]
	mov 	drawTextureInputD,		0
	mov 	drawTextureInput8,		16
	mov 	drawTextureInput9,		WHITE
	call	DrawTexture

.draw_player_sprite:
	mov		playerMemory,			[player_memory]
	lea		drawAnimatedInputC,		[playerSprite]
	mov		drawAnimatedInputD,		[playerWorldPos]
	call	draw_animated_sprite

.ender_render_camera:
	call	EndMode2D

.end_draw:
	call	EndDrawing

.exit:
	add		rsp,	$28
	ret


include '../sprites/sprite_rendering.inc'