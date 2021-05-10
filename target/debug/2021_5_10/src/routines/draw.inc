;*/
;* @Date:		4/25/21
;* @Author:		Szyfr
;*/

;;=  Standard Draw call
;;=  void Draw(void)
draw:
	pop [home]

.begin_draw:
	;;BeginDrawing()
	call [BeginDrawing]

.bg:
	;;ClearBackground(RAYWHITE)
	mov ecx,RAYWHITE
	call [ClearBackground]

.camera:
	;;BeginMode2D(&camera)
	lea rcx,[camera]
	call [BeginMode2D]

	mov rcx,-100
	mov rdx,100
	mov r8,200
	mov r9,100
	mov dword [rsp+0x20],WHITE
	call [DrawRectangle]

	mov rax,[player_memory]
	lea rcx,[rax+PlayerData.spriteTexture]
	mov rdx,300
	mov r8,300
	mov r9,WHITE
	call [DrawTexture]

	mov rax,[player_memory]
	lea rcx,[rax+PlayerData.spriteTexture]
	lea rdx,[rax+PlayerData.spriteRect]
	mov r8,$40a0000040a00000
	mov r9d,WHITE
	call [DrawTextureRec]

	;;EndMode2D()
	call [EndMode2D]

.DEBUG_text:
	;;DrawText(*text_onscreen,text_position_x,text_position_y,20,BLACK)
	lea rcx,[text_onscreen]
	mov rdx,10
	mov r8,10
	mov r9,20
	mov dword [rsp+0x20],BLACK
	call [DrawTextRL]

.end_draw::
	;;EndDrawing()
	call [EndDrawing]

.exit:
	push [home]
	ret


include '../sprites/sprite_rendering.inc'