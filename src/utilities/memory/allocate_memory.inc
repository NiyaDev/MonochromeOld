;*/
;* @Date:		6/15/21
;* @Author:		Szyfr
;*/



;;=  Creates a memory heap and cleans it
;;=		Input:		RCX = size
;;=		Output:		RAX = &memoryAddress
memorySize			equ		rcx		;Input
memoryAddress		equ		rax
memoryPointer		equ		rcx
memorySizeAlt		equ		rdx
allocate_memory:
	sub		rsp,	28h
	push	rdx

.allocate:
	push	memorySize
	call	MemAlloc
.clean:
	pop		memorySizeAlt
	mov		memoryPointer,			memoryAddress
	call	clean_memory
.exit:
	pop		rdx
	add		rsp,	28h
	ret