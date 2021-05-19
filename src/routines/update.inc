;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Standard Update call
update:
	sub rsp,$28

	mov		rcx,KEY_Z
	call	[IsKeyDown]
	cmp		al,0
	je		.controls

;	mov		r9,[player_memory]
;	lea		rcx,[r9+PlayerData.sprite]
;	mov		rdx,4
;	call	change_animated_sprite
	
.controls:
	;;Checks each key, then shifts the response into position
	xor rax,rax
	xor rbx,rbx

	mov rcx,KEY_A
	call [IsKeyDown]
	or bl,al

	mov rcx,KEY_D
	call [IsKeyDown]
	shl al,1
	or bl,al

	mov rcx,KEY_W
	call [IsKeyDown]
	shl al,2
	or bl,al

	mov rcx,KEY_S
	call [IsKeyDown]
	shl al,3
	or bl,al

	mov rax,[player_memory]
	mov word[rax+PlayerData.ctrData.direction],bx
	

	xor rax,rax
	xor rbx,rbx

	;;Reads the bits
	mov		r8,[general_memory]
	mov		r9,[player_memory]
	mov		dword [r8+GeneralMemory.dword],10
.horizontal_neg:
	bt		word[r9+PlayerData.ctrData.direction],0
	jnc		.horizontal_pos
	fld		dword [r9+PlayerData.camera.target.x]
	fisub	dword [r8+GeneralMemory.dword]
	fstp	dword [r9+PlayerData.camera.target.x]

	lea		rcx,[r9+PlayerData.sprite]
	mov		rdx,6
	call	change_animated_sprite
.horizontal_pos:
	bt		word[r9+PlayerData.ctrData.direction],1
	jnc		.vertical_neg
	fld		dword [r9+PlayerData.camera.target.x]
	fiadd	dword [r8+GeneralMemory.dword]
	fstp	dword [r9+PlayerData.camera.target.x]

	lea		rcx,[r9+PlayerData.sprite]
	mov		rdx,7
	call	change_animated_sprite

.vertical_neg:
	bt		word[r9+PlayerData.ctrData.direction],2
	jnc		.vertical_pos
	fld		dword [r9+PlayerData.camera.target.y]
	fisub	dword [r8+GeneralMemory.dword]
	fstp	dword [r9+PlayerData.camera.target.y]

	lea		rcx,[r9+PlayerData.sprite]
	mov		rdx,5
	call	change_animated_sprite
.vertical_pos:
	bt		word[r9+PlayerData.ctrData.direction],3
	jnc		.exit
	fld		dword [r9+PlayerData.camera.target.y]
	fiadd	dword [r8+GeneralMemory.dword]
	fstp	dword [r9+PlayerData.camera.target.y]

	lea		rcx,[r9+PlayerData.sprite]
	mov		rdx,4
	call	change_animated_sprite
	
.exit:
	add rsp,$28
	ret