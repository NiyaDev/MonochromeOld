;*/
;* @Date:		5/25/21
;* @Author:		Szyfr
;*/


;;=  Updates overworld player's movement and sprite
;;=		INPUT:		N/A
;;=		Output:		N/A
UOP_control			equ		rcx
UOP_pollResult		equ		al

UOP_playerMem		equ		r8
UOP_playerIsMoving	equ		r8+PlayerData.entity.isMoving
UOP_playerDirection	equ		r8+PlayerData.entity.direction
UOP_playerTilePos	equ		r8+PlayerData.entity.tilePos
UOP_playerWorldPos	equ		r8+PlayerData.entity.worldPos
UOP_playerSprite	equ		r8+PlayerData.entity.sprite

UOP_isMoving		equ		al
UOP_currentTile		equ		rcx
UOP_moveDirOut		equ		rax
UOP_changeSprite	equ		rcx

;;TODO: Fix this?
UOP_animation		equ		r10
UOP_playAnimation	equ		rdx
update_player:
	sub		rsp,	28h

	xor		rdx,rdx

.set_controls:
	call	set_controls

.poll_up:
	mov		UOP_control,			0
	call	poll_controls
	cmp		UOP_pollResult,			1
	je		.tap_up

	cmp		UOP_pollResult,			2
	je		.hold_up
.poll_down:
	mov		UOP_control,			1
	call	poll_controls
	cmp		UOP_pollResult,			1
	je		.tap_down

	cmp		UOP_pollResult,			2
	je		.hold_down
.poll_left:
	mov		UOP_control,			2
	call	poll_controls
	cmp		UOP_pollResult,			1
	je		.tap_left

	cmp		UOP_pollResult,			2
	je		.hold_left
.poll_right:
	mov		UOP_control,			3
	call	poll_controls
	cmp		UOP_pollResult,			1
	je		.tap_right

	cmp		UOP_pollResult,			2
	je		.hold_right
.no_controls_pressed:
	jmp		.exit


.hold_up:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerIsMoving],	1
	mov		[UOP_playerDirection],	1
	mov		UOP_animation,			5
	jmp		.player_movement
.tap_up:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerDirection],	1
	mov		UOP_animation,			1
	jmp		.player_movement

.hold_down:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerIsMoving],	1
	mov		[UOP_playerDirection],	0
	mov		UOP_animation,			4
	jmp		.player_movement
.tap_down:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerDirection],	0
	mov		UOP_animation,			0
	jmp		.player_movement

.hold_left:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerIsMoving],	1
	mov		[UOP_playerDirection],	2
	mov		UOP_animation,			6
	jmp		.player_movement
.tap_left:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerDirection],	2
	mov		UOP_animation,			2
	jmp		.player_movement

.hold_right:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerIsMoving],	1
	mov		[UOP_playerDirection],	3
	mov		UOP_animation,			7
	jmp		.player_movement
.tap_right:
	mov		UOP_playerMem,			[player_memory]
	mov		[UOP_playerDirection],	3
	mov		UOP_animation,			3
	jmp		.player_movement


.player_movement:
	mov		UOP_playerMem,			[player_memory]		;;? Might not need
	cmp		[UOP_playerIsMoving],	0
	je		.animation

	mov		UOP_currentTile,		[UOP_playerTilePos]
	cmp		[UOP_playerWorldPos],	UOP_currentTile
	jne		.exit

	mov		UOP_playAnimation,		UOP_animation
	sub		UOP_playAnimation,		4
	call	move_direction
	mov		[UOP_playerTilePos],	UOP_moveDirOut

.animation:
	lea		UOP_changeSprite,		[UOP_playerSprite]
	mov		UOP_playAnimation,		UOP_animation
	call	change_animated_sprite

.exit:
	add		rsp,28h
	ret


;;=  Gathers currently pressed keys and stores them
;;=		INPUT:		N/A
;;=		Output:		N/A
;;TODO:	set up keybindings
SCN_playerMemory	equ		r8

SCN_playerDir		equ		cx
SCN_playerDirKeys	equ		r8+PlayerData.ctrData.direction
SCN_playerActKeys	equ		r8+PlayerData.ctrData.action
SCN_keycode			equ		rcx
SCN_keyOutput		equ		al
set_controls:
	sub		rsp,	28h

	push	rcx
	push	r8

.initialize:
	xor		rax,rax
	mov		SCN_playerMemory,		[player_memory]
.shift_last_bits:
	mov		SCN_playerDir,			[SCN_playerDirKeys]
	shl		SCN_playerDir,			4
	mov		[SCN_playerDirKeys],	SCN_playerDir

.check_up:
	mov		SCN_keycode,			KEY_W
	call	IsKeyDown
	cmp		SCN_keyOutput,			1
	jne		.check_down
	bts		[SCN_playerDirKeys],	0
.check_down:
	mov		SCN_keycode,			KEY_S
	call	IsKeyDown
	cmp		SCN_keyOutput,			1
	jne		.check_left
	bts		[SCN_playerDirKeys],	1
.check_left:
	mov		SCN_keycode,			KEY_A
	call	IsKeyDown
	cmp		SCN_keyOutput,			1
	jne		.check_right
	bts		[SCN_playerDirKeys],	2
.check_right:
	mov		SCN_keycode,			KEY_D
	call	IsKeyDown
	cmp		SCN_keyOutput,			1
	jne		.exit
	bts		[SCN_playerDirKeys],	3

;;TODO: Scan for action keys as well

.exit:
	pop		rcx
	pop		r8

	add		rsp,	28h
	ret


;;=  Polls currently stored controls
;;=		INPUT:		RCX = control
;;=						0:Up		1:Down		2:Left		3:Right
;;=						4:Confirm	5:Cancel	6:Start		7:Select
;;=		Output:		RAX = buttonData
;;=						0:None		1:Tap		2:Hold
PCN_control			equ		rcx
PCN_output			equ		rax
PCN_outputDword		equ		ax

PCN_controlHigh		equ		ch
PCN_controlDword	equ		cx
PCN_playerMemory	equ		r8
PCN_playerDirKeys	equ		r8+PlayerData.ctrData.direction
PCN_playerActKeys	equ		r8+PlayerData.ctrData.action
poll_controls:
	sub		rsp,	28h

.initialize:
	xor		PCN_output,				PCN_output
	xor		PCN_controlHigh,		PCN_controlHigh
	mov		PCN_playerMemory,		[player_memory]

;;TODO: Test if the control byte is greater than 3,
;;TODO: If so, poll in action, rather than direction

.poll:
	bt		[PCN_playerDirKeys],	PCN_controlDword
	jnc		.exit

	add		PCN_outputDword,		1
	add		PCN_controlDword,		12
	bt		[PCN_playerDirKeys],	PCN_controlDword
	jnc		.exit

	add		PCN_outputDword,		1

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