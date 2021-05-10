
;;=  void CleanMemory(rcx:&memStart,rdx:size)
CleanMemory:
	xor rbx,rbx
.clearMem:
	mov byte [rcx],$0
	inc rcx
	inc rbx

	cmp rbx,rdx
	jnz .clearMem

	ret