;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Creates a memory heap and cleans it
;;=		Input:		RCX = size
;;=		Output:		RAX = &memoryAddress
allocate_memory:
	sub		rsp,28h
.allocate:
	push	rdx
	push	rcx
	call	MemAlloc
.clean:
	pop		rdx
	mov		rcx,rax
	call	clean_memory
.exit:
	pop		rdx
	add		rsp,28h
	ret


;;=  Zeros out all of the memory at address
;;=		Input:		RCX = &memoryLocation
;;=					RDX = size
;;=		Output:		N/A
clean_memory:
	push	rbx
	xor		rbx,rbx
.loop:
	mov		byte[rcx],$0
	inc		rcx
	inc		rbx

	cmp		rbx,rdx
	jnz		.loop

	pop		rbx
	ret


;;=  Loads contents of a file and stores a pointer to heap
;;=	 Also stores file length at the start of the heap
;;=		Input:		RCX = &filename
;;=					RDX = outputFormat
;;=						0:Regular	1:Double-sized and in later half
;;=		Output:		RAX = &data
MEM_fileDataPtr		equ		rdx+60
load_file_data:
	sub		rsp,28h
	push	rdx

.loading_file:
	mov		rdx,[general_memory]
	call	LoadFileData

.check_format:
	pop		rdx
	cmp		rdx,0
	je		.exit

.allocate_new_memory:
	mov		rdx,[general_memory]
	mov		[MEM_fileDataPtr],rax

	mov		rcx,[rdx]
	imul	rcx,2
	call	MemAlloc

.copy_init:
	mov		rdx,[general_memory]
	mov		rcx,[rdx]
	mov		r8,[MEM_fileDataPtr]
	mov		r9,rax
	add		r9,rcx

.copy_loop:
	mov		r10d,[r8]
	mov		[r9],r10d
	add		r8,4
	add		r9,4
	sub		rcx,4
	jnz		.copy_loop

.remove_old_pointer:
	mov		rcx,[MEM_fileDataPtr]
	mov		[MEM_fileDataPtr],rax
	call	UnloadFileData

	mov		rdx,[general_memory]
	mov		rcx,[rdx]
	mov		rax,[MEM_fileDataPtr]
	mov		[rax],rcx

.exit:
	add		rsp,28h
	ret