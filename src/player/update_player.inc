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
playerMenuTimer		equ		r8+PlayerData.ctrData.menuTimer
playerCursorLoc		equ		r8+PlayerData.ctrData.cursorLoc
animation			equ		r10
animationByte		equ		r10b
;;TODO: Clean up this code into multiple functions
;;TODO: This needs to be done BADLY
update_player:
	sub		rsp,	28h
	xor		rdx,rdx

.set_controls:
	call	set_controls

.init:
	xor		pollSelection,			pollSelection
	mov		playerMemory,			[player_memory]

;;----------------------;;
;;      Pause menu      ;;
;;----------------------;;
	call 	check_pause_menu

.pause_check:
	cmp		[playerMenu],			1
	je		.menu_move_init

;;----------------------;;
;;  Overworld Movement	;;
;;----------------------;;
.overworld_move_init:
	xor		pollLower,				pollLower
	mov		animation,				3
.overworld_move_loop:
	call	poll_controls

	inc		pollLower
	inc		animation

	cmp		controls,				1
	je		.tap
	cmp		controls,				2
	je		.hold

	cmp		animation,				7
	jg		.no_controls_pressed
	jle		.overworld_move_loop

.hold:
	mov		[playerDirection],		animationByte
	mov		[playerMoving],			1
	jmp		.player_movement
.tap:
	mov		[playerDirection],		animationByte
	sub		[playerDirection],		4
	jmp		.player_movement

.menu_move_init:
	cmp		[playerMenuTimer],		0
	jne		.no_controls_pressed

	xor		pollSelection,			pollSelection
.menu_move_loop:
	call	poll_controls

	cmp		controls,				1
	je		.menu_move

	inc		pollLower

	cmp		pollLower,				1
	jg		.exit
	jle		.menu_move_loop

.menu_move:
	cmp		pollLower,				20h
	je		.increase
	jne		.decrease

.increase:
	mov		[playerMenuTimer],		10
	cmp		[playerCursorLoc],		6
	je		.set_min
	inc		[playerCursorLoc]
	jmp		.no_controls_pressed
.decrease:
	mov		[playerMenuTimer],		10
	cmp		[playerCursorLoc],		0
	je		.set_max
	dec		[playerCursorLoc]
	jmp		.no_controls_pressed

.set_min:
	mov		[playerCursorLoc],		0
	jmp		.no_controls_pressed
.set_max:
	mov		[playerCursorLoc],		6
	jmp		.no_controls_pressed


.no_controls_pressed:
	cmp		[playerMoving],			1
	jne		.idle_animation
	jmp		.exit


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
	cmp		changeSpriteInputB,		4
	jl		.no_sub
	sub		changeSpriteInputB,		4
.no_sub:
	call	change_animated_sprite
	jmp		.exit


include 'overworld_controls/pause_menu.inc'