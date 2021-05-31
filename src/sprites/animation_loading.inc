;*/
;* @Date:		5/18/21
;* @Author:		Szyfr
;*/



;;=  Loads animations from file and stores a pointer to them
;;=		Input:		N/A
;;=		Output:		N/A
;;=		Destroys:	RAX,RCX,RDX
;;TODO:Finish cleaning this up
load_animations:
	sub		rsp,28h

	push	rax
	push	rcx
	push	rdx

	lea		rcx,[animations_text]
	mov		rdx,1
	call	load_file_data
	mov		[animation_memory],rax


.parse_data_create_pointers:
	mov		r8,[animation_memory]
	mov		r9,[animation_memory]
	mov		rcx,[r8]
	add		r9,rcx
	mov		[r8],r9
	add		r8,8
.parse_start:
	mov		eax,[r9]
	cmp		eax,0xFFFFFFFF
	je		.create_pointer
	add		r9,4
	sub		rcx,4
	jnz		.parse_start
	jmp		.exit

.create_pointer:
	add		r9,4
	mov		[r8],r9
	add		r8,8
	sub		rcx,4
	jnz		.parse_start

.exit:
	pop		rax
	pop		rcx
	pop		rdx

	add		rsp,28h
	ret


;load_animations:
;	sub		rsp,28h
;
;	push	rax
;	push	rcx
;	push	rdx
;
;.load_raw_data:
;	mov		rax,[general_memory]
;
;	lea		rcx,[animations_text]
;	lea		rdx,[rax+GeneralMemory.qword]
;	call 	LoadFileData
;	mov		[animation_memory],rax
;
;.allocate_new_memory:
;	mov		rax,[general_memory]
;
;	mov		rcx,[rax+GeneralMemory.qword]
;	imul	rcx,2
;	call	MemAlloc
;
;.copy_file_data:
;	mov		rdx,[general_memory]
;	mov		rcx,[rdx+GeneralMemory.qword]
;	mov		r8,[animation_memory]
;	mov		r9,rax
;	add		r9,rcx
;
;.copy_loop:
;	mov		r10d,[r8]
;	mov		[r9],r10d
;	add		r8,4
;	add		r9,4
;	sub		rcx,4
;	jnz		.copy_loop
;
;.fix_addresses:
;	mov		rcx,[animation_memory]
;	mov		[animation_memory],rax
;	call	UnloadFileData
;
;
;.parse_data_create_pointers:
;	mov		rax,[general_memory]
;	mov		rcx,[rax+GeneralMemory.qword]
;	mov		r8,[animation_memory]
;	mov		r9,[animation_memory]
;	add		r9,rcx
;	mov		[r8],r9
;	add		r8,8
;.parse_start:
;	mov		eax,[r9]
;	cmp		eax,0xFFFFFFFF
;	je		.create_pointer
;	add		r9,4
;	sub		rcx,4
;	jnz		.parse_start
;	jmp		.exit
;
;.create_pointer:
;	add		r9,4
;	mov		[r8],r9
;	add		r8,8
;	sub		rcx,4
;	jnz		.parse_start
;
;.exit:
;	pop		rax
;	pop		rcx
;	pop		rdx
;	
;	add		rsp,28h
;	ret