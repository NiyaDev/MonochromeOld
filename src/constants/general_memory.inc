
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
	.isMoving	db		0
	.tilePos	Vector2	0,0
	.worldPos	Vector2	0,0
}

virtual at 0
	GeneralMemory	GeneralMemory
	sizeof.GeneralMemory = $ - GeneralMemory
end virtual