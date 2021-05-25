;*/
;* @Date:		5/18/21
;* @Author:		Szyfr
;*/


;;=  
load_animations:
	sub		rsp,28h

.load_raw_data:
	;;animation_memory = LoadFileData(&animations_text,&qword);
	mov		rax,[general_memory]
	lea		rcx,[animations_text]
	lea		rdx,[rax+GeneralMemory.qword]
	call 	[LoadFileData]
	mov		[animation_memory],rax			;temp

.allocate_new_memory:
	mov		rax,[general_memory]
	mov		rcx,[rax+GeneralMemory.qword]
	imul	rcx,2
	call	[MemAlloc]

.copy_file_data:
	mov		rdx,[general_memory]			;Copy pointer to general_memory into rdx
	mov		rcx,[rdx+GeneralMemory.qword]	;Copy the file size into rcx
	mov		r8,[animation_memory]			;Copy pointer to animation_memory into r8
	mov		r9,rax							;Copy pointer to future animation_memory into r9
	add		r9,rcx							;Offset new animation_memory by the file size
.copy_loop:
	mov		r10d,[r8]
	mov		[r9],r10d
	add		r8,4
	add		r9,4
	sub		rcx,4
	jnz		.copy_loop

.fix_addresses:
	mov		rcx,[animation_memory]
	mov		[animation_memory],rax
	call	[UnloadFileData]


.parse_data_create_pointers:
	mov		rax,[general_memory]
	mov		rcx,[rax+GeneralMemory.qword]
	mov		r8,[animation_memory]
	mov		r9,[animation_memory]
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
	add		rsp,28h
	ret