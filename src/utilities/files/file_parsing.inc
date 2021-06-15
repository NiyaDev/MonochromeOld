;*/
;* @Date:		6/15/21
;* @Author:		Szyfr
;*/



;;=  Parses file data and creates a table of contents
;;=		Input:		RCX = &data
;;=					RDX	= dataSize
;;=					R8	= endBuffer
;;=		Output:		N/A
;;?  Move this to a seperate file?
PRS_dataPtr			equ		rcx
PRS_dataSize		equ		rdx

PRS_tablePtr		equ		r10
PRS_contentsPtr		equ		r11
PRS_dataCounter		equ		rcx

PRS_buffer_8		equ		r8b
PRS_buffer_16		equ		r8w
PRS_buffer_32		equ		r8d
PRS_buffer_64		equ		r8

PRS_content_8		equ		al
PRS_content_16		equ		ax
PRS_content_32		equ		eax
PRS_content_64		equ		rax
parse_file_data:
	sub		rsp,	28h

	push	r10
	push	r11

.parse_initialize:
	mov		PRS_tablePtr,		PRS_dataPtr
	mov		PRS_contentsPtr,	PRS_dataPtr

	mov		PRS_dataCounter,	[PRS_tablePtr]
	add		PRS_contentsPtr,	PRS_dataCounter

	mov		[PRS_tablePtr],		PRS_contentsPtr
	add		PRS_tablePtr,		8

.parse_table:
	cmp		PRS_dataSize,		1
	je		.parse_loop_8

	cmp		PRS_dataSize,		2
	je		.parse_loop_16

	cmp		PRS_dataSize,		4
	je		.parse_loop_32

	cmp		PRS_dataSize,		8
	je		.parse_loop_64
	

	jmp		.exit

.parse_loop_8:
	mov		PRS_content_8,		[PRS_contentsPtr]
	cmp		PRS_content_8,		PRS_buffer_8
	je		.parse_loop_8_pointer

	add		PRS_contentsPtr,	PRS_dataSize
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_8

	jmp		.exit
.parse_loop_8_pointer:
	add		PRS_contentsPtr,	PRS_dataSize
	mov		[PRS_tablePtr],		PRS_contentsPtr
	add		PRS_tablePtr,		8
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_8

	jmp		.exit
.parse_loop_16:
	mov		PRS_content_16,		[PRS_contentsPtr]
	cmp		PRS_content_16,		PRS_buffer_16
	je		.parse_loop_16_pointer

	add		PRS_contentsPtr,	PRS_dataSize
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_16

	jmp		.exit
.parse_loop_16_pointer:
	add		PRS_contentsPtr,	PRS_dataSize
	mov		[PRS_tablePtr],		PRS_contentsPtr
	add		PRS_tablePtr,		8
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_16

	jmp		.exit
.parse_loop_32:
	mov		PRS_content_32,		[PRS_contentsPtr]
	cmp		PRS_content_32,		PRS_buffer_32
	je		.parse_loop_32_pointer

	add		PRS_contentsPtr,	PRS_dataSize
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_32

	jmp		.exit
.parse_loop_32_pointer:
	add		PRS_contentsPtr,	PRS_dataSize
	mov		[PRS_tablePtr],		PRS_contentsPtr
	add		PRS_tablePtr,		8
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_32

	jmp		.exit
.parse_loop_64:
	mov		PRS_content_64,		[PRS_contentsPtr]
	cmp		PRS_content_64,		PRS_buffer_64
	je		.parse_loop_64_pointer

	add		PRS_contentsPtr,	PRS_dataSize
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_64

	jmp		.exit
.parse_loop_64_pointer:
	add		PRS_contentsPtr,	PRS_dataSize
	mov		[PRS_tablePtr],		PRS_contentsPtr
	add		PRS_tablePtr,		8
	sub		PRS_dataCounter,	PRS_dataSize
	jnz		.parse_loop_64

	jmp		.exit

.exit:
	pop		r11
	pop		r10

	add		rsp,28h
	ret