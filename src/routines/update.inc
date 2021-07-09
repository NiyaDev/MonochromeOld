;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Standard Update call
updatedPosition		equ		rax

playerMemory		equ		rcx
playerCameraTarget	equ		rcx+PlayerData.camera.target
playerWorldPos		equ		rcx+PlayerData.entity.worldPos
update:
	sub		rsp,	$28

	mov		playerMemory,			[player_memory]
	call	update_movement

	mov		playerMemory,			[player_memory]
	mov		updatedPosition,		[playerWorldPos]
	mov		[playerCameraTarget],	updatedPosition
	call	update_player

.exit_final:
	add 	rsp,	$28
	ret


include '../utilities/overworld/move_direction.inc'
include '../utilities/overworld/update_movement.inc'

include '../player/poll_controls.inc'
include '../player/set_controls.inc'
include '../player/update_player.inc'
