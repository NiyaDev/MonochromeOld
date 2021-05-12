;*/
;* @Date:		4/25/21
;* @Author:		Szyfr
;*/

;;=  Standard Draw call
;;=  void Draw(void)
draw:
	sub rsp,$28

.begin_draw:
	;;BeginDrawing()
	call [BeginDrawing]

.bg:
	;;ClearBackground(RAYWHITE)
	mov ecx,RAYWHITE
	call [ClearBackground]

.camera:
	;;BeginMode2D(&camera);
	mov rax,[player_memory]
	lea rcx,[rax+PlayerData.camera]
	call [BeginMode2D]

	;;DrawRectangle(-100,100,200,100,WHITE);
	mov rcx,-100
	mov rdx,100
	mov r8,200
	mov r9,100
	mov dword [rsp+0x20],WHITE
	call [DrawRectangle]

	;;DrawTexture(&PlayerData.spriteTexture,300,300,WHITE);
	mov rax,[player_memory]
	lea rcx,[rax+PlayerData.spriteTexture]
	mov rdx,300
	mov r8,300
	mov r9,WHITE
	call [DrawTexture]

	;;DrawTextureRec(&PlayerData.spriteTexture,&PlayerData.spriteRect,{PlayerData.camera.target.x-64f,PlayerData.camera.target.y-64f},WHITE);
	mov rax,[player_memory]
	lea rcx,[rax+PlayerData.spriteTexture]
	lea rdx,[rax+PlayerData.spriteRect]
	mov r8,qword[rax+PlayerData.camera.target]
	mov rax,[general_memory]
	mov qword[rax+GeneralMemory.qword],r8
	mov dword[rax+GeneralMemory.dword],64f
	fld dword[rax+GeneralMemory.qword]
	fsub dword[rax+GeneralMemory.dword]
	fstp dword[rax+GeneralMemory.qword]
	fld dword[rax+GeneralMemory.qword+4]
	fsub dword[rax+GeneralMemory.dword]
	fstp dword[rax+GeneralMemory.qword+4]
	mov r8,qword[rax+GeneralMemory.qword]
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
	add rsp,$28
	ret


include '../sprites/sprite_rendering.inc'