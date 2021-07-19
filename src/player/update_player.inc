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
	je		.menu_control

;;----------------------;;
;;  Overworld Movement	;;
;;----------------------;;
.overworld_control:
	call	movement_controls
	cmp		rax,0
	je		.player_movement
	jne		.no_controls_pressed

;;----------------------;;
;;     Menu Movement    ;;
;;----------------------;;
.menu_control:
	call	ui_controls
	jmp		.no_controls_pressed

;;----------------------;;
;;    Menu Selection    ;;
;;----------------------;;
.menu_selection:
	
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
include 'overworld_controls/movement_controls.inc'
include 'overworld_controls/ui_controls.inc'