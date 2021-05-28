;*/
;* @Date:		5/25/21
;* @Author:		Szyfr
;*/


;;=  void UpdatePlayer();
update_player:
	sub		rsp,28h

	xor		rdx,rdx

.set_controls:
	call	set_controls

.poll_up:
	mov		rcx,0
	call	poll_controls
	cmp		al,1
	je		.tap_up
	cmp		al,2
	je		.hold_up
.poll_down:
	mov		rcx,1
	call	poll_controls
	cmp		al,1
	je		.tap_down
	cmp		al,2
	je		.hold_down
.poll_left:
	mov		rcx,2
	call	poll_controls
	cmp		al,1
	je		.tap_left
	cmp		al,2
	je		.hold_left
.poll_right:
	mov		rcx,3
	call	poll_controls
	cmp		al,1
	je		.tap_right
	cmp		al,2
	je		.hold_right
.no_controls_pressed:
	jmp		.exit


.hold_up:
	mov		r8,[player_memory]
	mov		[r8+PlayerData.entity.isMoving],1
	mov		r10,0
.tap_up:
	mov		[r8+PlayerData.entity.direction],2
	add		r10,4
	jmp		.player_movement

.hold_down:
	mov		r8,[player_memory]
	mov		[r8+PlayerData.entity.isMoving],1
	mov		r10,1
.tap_down:
	mov		[r8+PlayerData.entity.direction],0
	add		r10,4
	jmp		.player_movement

.hold_left:
	mov		r8,[player_memory]
	mov		[r8+PlayerData.entity.isMoving],1
	mov		r10,2
.tap_left:
	mov		[r8+PlayerData.entity.direction],3
	add		r10,4
	jmp		.player_movement

.hold_right:
	mov		r8,[player_memory]
	mov		[r8+PlayerData.entity.isMoving],1
	mov		r10,3
.tap_right:
	mov		[r8+PlayerData.entity.direction],1
	add		r10,4
	jmp		.player_movement


.player_movement:
	mov		r8,[player_memory]
	mov		al,[r8+PlayerData.entity.isMoving]
	cmp		al,0
	jne		.animation

	mov		rcx,[r8+PlayerData.entity.tilePos]
	mov		rdx,r10
	sub		rdx,4
	call	move_direction
	mov		[r8+PlayerData.entity.tilePos],rax

.animation:
	lea		rcx,[r8+PlayerData.entity.sprite]
	mov		rdx,r10
	call	change_animated_sprite

.exit:
	add		rsp,28h
	ret


;;=  void SetControls();
set_controls:
	sub		rsp,28h

.initialize:
	xor		rax,rax
	mov		r8,[player_memory]
.shift_last_bits:
	mov		cx,[r8+PlayerData.ctrData.direction]
	shl		cx,4
	mov		[r8+PlayerData.ctrData.direction],cx

.check_up:
	mov		rcx,KEY_W
	call	IsKeyDown
	cmp		al,1
	jne		.check_down
	bts		[r8+PlayerData.ctrData.direction],0
.check_down:
	mov		rcx,KEY_S
	call	IsKeyDown
	cmp		al,1
	jne		.check_left
	bts		[r8+PlayerData.ctrData.direction],1
.check_left:
	mov		rcx,KEY_A
	call	IsKeyDown
	cmp		al,1
	jne		.check_right
	bts		[r8+PlayerData.ctrData.direction],2
.check_right:
	mov		rcx,KEY_D
	call	IsKeyDown
	cmp		al,1
	jne		.exit
	bts		[r8+PlayerData.ctrData.direction],3
	
.exit:
	add		rsp,28h
	ret


;;=  byte PollControls(byte:control);
;;=		RCX =	0:Up		1:Down		2:Left		3:Right
;;?				4:Confirm	5:Cancel	6:Start		7:Select
;;=		RAX = 0:None	1:Tap		2:Hold
poll_controls:
	sub		rsp,28h

.initialize:
	xor		rax,rax
	xor		ch,ch
	mov		r8,[player_memory]

.poll:
	bt		[r8+PlayerData.ctrData.direction],cx
	jnc		.exit
	add		ax,1
	add		cx,12
	bt		[r8+PlayerData.ctrData.direction],cx
	jnc		.exit
	add		ax,1

.exit:
	add		rsp,28h
	ret


;.tap_up:
;	mov		r10,1
;	jmp		.animation
;.hold_up:
;	mov		rdx,2
;	mov		r10,1
;	jmp		.player_movement
;.tap_down:
;	mov		r10,0
;	jmp		.animation
;.hold_down:
;	mov		rdx,0
;	mov		r10,0
;	jmp		.player_movement
;.tap_left:
;	mov		r10,2
;	jmp		.animation
;.hold_left:
;	mov		rdx,3
;	mov		r10,2
;	jmp		.player_movement
;.tap_right:
;	mov		r10,3
;	jmp		.animation
;.hold_right:
;	mov		rdx,1
;	mov		r10,3
;	jmp		.player_movement
;
;
;.player_movement:
;	mov		r8,[player_memory]
;	mov		al,[r8+PlayerData.entity.isMoving]
;	cmp		al,0
;;	jne		.exit_final
;	je		.move
;	jmp		.animation
;
;.move:
;	mov		rcx,[r8+PlayerData.entity.tilePos]
;	mov		[r8+PlayerData.entity.direction],r10b
;	call	move_direction
;	mov		r8,[player_memory]
;	mov		[r8+PlayerData.entity.tilePos],rax
;.animation:
;	lea		rcx,[r8+PlayerData.entity.sprite]
;	add		rdx,r10
;	cmp		[r8+PlayerData.entity.isMoving],1
;	jne		.animation_call
;	add		rdx,4
;.animation_call:
;	call	change_animated_sprite
;
;.exit:
;	mov		r8,[player_memory]
;	mov		al,[r8+Entity.isMoving]
;	cmp		al,1
;	je		.exit_final
;.exit_final: