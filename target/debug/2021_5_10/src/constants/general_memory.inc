
CONST_memorySize	equ 10000	;Total of: 10,000 bytes

;; Memory offsets
struc GeneralMemory {
	.home	dq	0
	.word	dw	0
	.qword	dq	0
	.byte	db	0
	.dword	dd	0
	.image	Image
}

virtual at 0
	GeneralMemory	GeneralMemory
	sizeof.GeneralMemory = $ - GeneralMemory
end virtual