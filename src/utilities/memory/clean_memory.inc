;*/
;* @Date:		6/15/21
;* @Author:		Szyfr
;*/



;;=  Zeros out all of the memory at address
;;=		Input:		RCX = &memoryLocation
;;=					RDX = size
;;=		Output:		N/A
memoryLocation		equ		rcx		;Input
heapSize			equ		rdx		;Input
counter				equ		rbx
clean_memory:
	sub		rsp,	28h
	push	rbx
	
	xor		counter,				counter
.loop:
	mov		byte[memoryLocation],	0
	inc		memoryLocation
	inc		counter

	cmp		counter,				heapSize
	jne		.loop

.exit:
	pop		rbx
	add		rsp,	28h
	ret