;*/
;* @Date:		6/14/21
;* @Author:		Szyfr
;*/



;;=  Constants
EntitySize			equ		64
dirDown				equ		0
dirUp				equ		1
dirLeft				equ		2
dirRight			equ		3

;;=  Structures
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