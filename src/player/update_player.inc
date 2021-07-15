;*/
;* @Date:		7/9/21
;* @Author:		Szyfr
;*/


;;=  Updates overworld player's movement and sprite
;;=		Input:		N/A
;;=		Output:		N/A
output				equ		rax
controls			equ		al
pollSelection		equ		rcx
tilePos				equ		rcx
playerSpritePtr		equ		rcx
pollLower			equ		cl
moveDirectionInput	equ		rdx
changeSpriteInput	equ		rdx
changeSpriteInputB	equ		dl

playerMemory		equ		r8
playerSprite		equ		r8+PlayerData.entity.sprite
playerMoving		equ		r8+PlayerData.entity.isMoving
playerTilePos		equ		r8+PlayerData.entity.tilePos
playerWorldPos		equ		r8+PlayerData.entity.worldPos
playerDirection		equ		r8+PlayerData.entity.direction
playerMenu			equ		r8+PlayerData.ctrData.menu
animation			equ		r10
animationByte		equ		r10b
update_player:
	sub		rsp,	28h
	xor		rdx,rdx

.set_controls:
	call	set_controls

.init:
	xor		pollSelection,			pollSelection
	mov		playerMemory,			[player_memory]

.check_start:
	mov		pollLower,				6
	call	poll_controls

	cmp		controls,				1
	jne		.poll_down
	;;Pause menu
	;;TODO: have pause menu stop player movement
	cmp		[playerMenu],			1
	jnz		.set
.reset:
	mov		[playerMenu],			0
	jmp		.leave
.set:
	mov		[playerMenu],			1
.leave:

.poll_down:
	mov		pollLower,				dirDown
	call	poll_controls

	mov		animation,				4
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_up:
	mov		pollLower,				dirUp
	call	poll_controls

	mov		animation,				5
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_left:
	mov		pollLower,				dirLeft
	call	poll_controls

	mov		animation,				6
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.poll_right:
	mov		pollLower,				dirRight
	call	poll_controls

	mov		animation,				7
	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold
.no_controls_pressed:
	jmp		.idle_animation


.hold:
	mov		[playerDirection],		animationByte
	sub		[playerDirection],		4
	mov		[playerMoving],			1
	jmp		.player_movement
.tap:
	mov		[playerDirection],		animationByte
	jmp		.player_movement


.player_movement:
	cmp		[playerMoving],			0
	je		.idle_animation

	mov		tilePos,				[playerTilePos]
	cmp		[playerWorldPos],		tilePos
	jne		.exit

	mov		moveDirectionInput,		animation
	sub		moveDirectionInput,		4
	call	move_direction
	mov		[playerTilePos],		output

.animation:
	lea		playerSpritePtr,		[playerSprite]
	mov		changeSpriteInput,		animation
	call	change_animated_sprite

.exit:
	add		rsp,28h
	ret

.idle_animation:
	lea		playerSpritePtr,		[playerSprite]
	mov		changeSpriteInputB,		[playerDirection]
	call	change_animated_sprite
	jmp		.exit