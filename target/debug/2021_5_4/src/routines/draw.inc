;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Standard Draw call
;;=  void Draw(void)
draw:
	pop [home]

.begin_draw:	;;BeginDrawing()
	call [BeginDrawing]

.bg:		;;ClearBackground(RAYWHITE)
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
	mov dword [rsp+0x20],BLACK
	call [DrawRectangle]

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

.ecit:
	push [home]
	ret

;drawTiles:
;	pop r12
;
;	mov rcx,[tile_memory]
;	xor rdx,rdx
;.loop:
;	;mov 


;	push r12
;	ret

	;Ready the variables for DrawTexture()
;	lea rcx,[tile_texture]
;	mov rdx,0
;	mov r8,0
;	mov r9,WHITE
;
;	mov r10,[tile_memory]
;	xor r11,r11
;.drawTiles:
	;;DrawTexture(&tile_texture,rdx,r8,WHITE);
;	call [DrawTexture]

	;Increment
;	add r10,TILE_SIZE
;	inc r11

	;calculates x and y for each tile
;	xor rdx,rdx	;rdx  = 0
;	mov rax,r11	;rax  = r11 (i)
;	mov rbx,10	;rbx  = 10
;	div rbx		;rdx  = rax % rbx
				;rax /= rbx
;	shl rdx,5	;rdx *= 16
;	mov r8,rax	;r8   = rax
;	shl r8,5	;r8  *= 16

	;Iterate 100 times
;	cmp r11,100
;	jle .drawTiles