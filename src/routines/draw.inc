;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Standard Draw call
;;=  void Draw(void)
draw:
	sub		rsp,$28

.begin_draw:
	;;BeginDrawing()
	call	qword[BeginDrawing]

.clear_background:
	;;ClearBackground(RAYWHITE)
	mov		ecx,RAYWHITE
	call	qword[ClearBackground]

.render_camera:
	;;BeginMode2D(&camera);
	mov		rax,[player_memory]
	lea		rcx,[rax+PlayerData.camera]
	call	qword[BeginMode2D]

	;;DrawRectangle(-100,100,200,100,WHITE);
	mov		rcx,-100
	mov		rdx,100
	mov		r8,200
	mov		r9,100
	mov		stack_variable_1,WHITE
	call	qword[DrawRectangle]

.draw_test_texture:
	;;DrawTexture(&PlayerData.spriteTexture,300,300,WHITE);
	mov		rax,[player_memory]
	lea		rcx,[rax+PlayerData.entity.sprite.texture]
	mov 	rdx,300
	mov 	r8,300
	mov 	r9,WHITE
	call	qword[DrawTexture]

.draw_player_sprite:
;	call draw_player
	mov		r8,[player_memory]
	lea		rcx,[r8+PlayerData.entity.sprite]
	mov		rdx,[r8+PlayerData.entity.worldPos] ;[r8+PlayerData.camera.target]
	call	draw_animated_sprite

.ender_render_camera:
	;;EndMode2D()
	call	qword[EndMode2D]

.end_draw::
	;;EndDrawing()
	call	qword[EndDrawing]

.exit:
	add		rsp,$28
	ret


include '../sprites/sprite_rendering.inc'


;.DEBUG_text:
;	;;DrawText(*text_onscreen,text_position_x,text_position_y,20,BLACK)
;	lea 	rcx,[text_onscreen]
;	mov 	rdx,10
;	mov 	r8,10
;	mov 	r9,20
;	mov 	dword [rsp+0x20],BLACK
;	call	[DrawTextRL]