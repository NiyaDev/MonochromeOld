;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  Draws the player's overworld sprite onto the screen
;;=  N/A
draw_player:
	sub rsp,28h

	;Grabs pointers to primary memory locations
	mov rax,[player_memory]
	mov rbx,[general_memory]
	;increments the animation timer
	inc [rax+PlayerData.sprite.timer]

	cmp [rax+PlayerData.sprite.timer],10h
	jle	.set_animation_0	;; If        timer <=  16
	cmp [rax+PlayerData.sprite.timer],20h
	jle	.set_animation_1	;; If  16 <= timer <=  32
	cmp [rax+PlayerData.sprite.timer],30h
	jle	.set_animation_2	;; If  32 <= timer <=  48
	cmp [rax+PlayerData.sprite.timer],40h
	jle	.set_animation_3	;; If  48 <= timer <=  64
	cmp [rax+PlayerData.sprite.timer],50h
	jle	.set_animation_4	;; If  64 <= timer <=  80
	cmp [rax+PlayerData.sprite.timer],60h
	jle	.set_animation_5	;; If  80 <= timer <=  96
	cmp [rax+PlayerData.sprite.timer],70h
	jle	.set_animation_6	;; If  96 <= timer <= 112
	cmp [rax+PlayerData.sprite.timer],80h
	jle	.set_animation_7	;; If 112 <= timer <= 128
	mov [rax+PlayerData.sprite.timer],0

.set_animation_0:	;display frame 0
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_1:	;display frame 1
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+4]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_2:	;display frame 2
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+8]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_3:	;display frame 3
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+12]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_4:	;display frame 4
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+16]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_5:	;display frame 5
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+20]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_6:	;display frame 6
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+24]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display
.set_animation_7:	;display frame 7
	mov rcx,[rax+PlayerData.sprite.curClip]
	mov edx,dword[rcx+28]
	mov [rax+PlayerData.sprite.rect.x],edx
	jmp .display


.display:
	;;DrawTextureRec(&PlayerData.spriteTexture,&PlayerData.spriteRect,{PlayerData.camera.target.x-64f,PlayerData.camera.target.y-64f},WHITE);
	lea rcx,[rax+PlayerData.sprite.texture]
	lea rdx,[rax+PlayerData.sprite.rect]
	mov r8,qword[rax+PlayerData.camera.target]
	mov qword[rbx+GeneralMemory.qword],r8
	mov dword[rbx+GeneralMemory.dword],64f
	fld dword[rbx+GeneralMemory.qword]
	fsub dword[rbx+GeneralMemory.dword]
	fstp dword[rbx+GeneralMemory.qword]
	fld dword[rbx+GeneralMemory.qword+4]
	fsub dword[rbx+GeneralMemory.dword]
	fstp dword[rbx+GeneralMemory.qword+4]
	mov r8,qword[rbx+GeneralMemory.qword]
	mov r9d,WHITE
	call [DrawTextureRec]

	add rsp,28h
	ret


;;=  Sets the current animation
;;=  RCX = *animationPointer	RDX = animation
set_animation:
	sub rsp,28h

	mov rax,32
	mul rdx
	lea rdx,[idle_down]
	add rax,rdx

	mov [rcx],rax

.exit:
	add rsp,28h
	ret