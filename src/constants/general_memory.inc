;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


CONST_memorySize	equ 10000	;Total of: 10,000 bytes

;; Memory offsets
struc GeneralMemory {
	.home	dq	0
	.word	dw	0
	.qword	dq	0
	.byte	db	0
	.dword	dd	0
	.v2		Vector2	0,0
	.image	Image
}

struc Entity {
	.sprite		AnimatedSprite	;46-bytes
	.isMoving	db		0		; 1-byte
	.tilePos	Vector2	0,0		; 8-bytes
	.worldPos	Vector2	0,0		; 8-bytes
	.direction	db		0		; 1-byte
}	;64-bytes


virtual at 0
	Entity	Entity
	sizeof.Entity = $ - Entity
end virtual

virtual at 0
	GeneralMemory	GeneralMemory
	sizeof.GeneralMemory = $ - GeneralMemory
end virtual