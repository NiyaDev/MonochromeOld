;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Standard Update call
update:
	sub		rsp,$28

	mov		rcx,[player_memory]
	call	update_movement

	mov		r8,[player_memory]
	mov		rax,[r8+PlayerData.entity.worldPos]
	mov		[r8+PlayerData.camera.target],rax
	
.controls:
	;;Checks each key, then shifts the response into position
	xor		rax,rax
	xor		rbx,rbx

.check_a:
	mov		rcx,KEY_A
	call	[IsKeyDown]
	or		bl,al
.check_d:
	mov		rcx,KEY_D
	call	[IsKeyDown]
	shl		al,1
	or		bl,al
.check_w:
	mov		rcx,KEY_W
	call	[IsKeyDown]
	shl		al,2
	or		bl,al
.check_s:
	mov		rcx,KEY_S
	call	[IsKeyDown]
	shl		al,3
	or		bl,al
.save_controls:
	mov		rax,[player_memory]
	mov		word[rax+PlayerData.ctrData.direction],bx
	
.test_controls:
;TODO: Create a function that polls for a specific control
	test	word[rax+PlayerData.ctrData.direction],1000b
	jnz		.move_down
	test	word[rax+PlayerData.ctrData.direction],0100b
	jnz		.move_up
	test	word[rax+PlayerData.ctrData.direction],0010b
	jnz		.move_right
	test	word[rax+PlayerData.ctrData.direction],0001b
	jnz		.move_left
	jmp		.exit

.move_down:
	mov		rdx,0
	mov		r10,0
	jmp		.player_movement
.move_right:
	mov		rdx,1
	mov		r10,3
	jmp		.player_movement
.move_up:
	mov		rdx,2
	mov		r10,1
	jmp		.player_movement
.move_left:
	mov		rdx,3
	mov		r10,2
	jmp		.player_movement

.player_movement:
	mov		r8,[player_memory]
	mov		al,[r8+PlayerData.entity.isMoving]
	cmp		al,0
	jne		.exit

;.idle:
;	lea		rcx,[r8+PlayerData.entity.sprite]
;	mov		rdx,r10
;	call	change_animated_sprite
;	jmp 	.exit

.move:
	mov		rcx,[r8+PlayerData.entity.tilePos]
	mov		[r8+PlayerData.entity.direction],r10b
	call	move_direction

	mov		r8,[player_memory]
	mov		[r8+PlayerData.entity.tilePos],rax

	lea		rcx,[r8+PlayerData.entity.sprite]
	mov		rdx,r10
	add		rdx,4
	call	change_animated_sprite

.exit:
	mov		r8,[player_memory]
	mov		al,[r8+Entity.isMoving]
	cmp		al,1
	je		.exit_final

;	xor		rdx,rdx
;	lea		rcx,[r8+Entity.sprite]
;	mov		dl,[r8+Entity.direction]
;	call	change_animated_sprite

.exit_final:
	add rsp,$28
	ret


include '../utilities/overworld/movement_overworld.inc'
