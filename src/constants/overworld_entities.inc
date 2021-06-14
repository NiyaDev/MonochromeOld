;*/
;* @Date:		6/14/21
;* @Author:		Szyfr
;*/



;;=  Structures
;* Overworld entity
struc Entity {
	.sprite		AnimatedSprite	;46-bytes
	.isMoving	db		0		; 1-byte
	.tilePos	Vector2	0,0		; 8-bytes
	.worldPos	Vector2	0,0		; 8-bytes
	.direction	db		0		; 1-byte
}	;64-bytes


;;=  Macro
virtual at 0
	Entity	Entity
	sizeof.Entity = $ - Entity
end virtual