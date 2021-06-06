;*/
;* @Date:		5/18/21
;* @Author:		Szyfr
;*/



;;=  Loads animations from file and stores a pointer to them
;;=		Input:		N/A
;;=		Output:		N/A
LDA_output			equ		rax
load_animations:
	sub		rsp,	28h

	push	rax
	push	rcx
	push	rdx

.load_file:
	lea		LDF_filename,		[animations_text]
	mov		LDF_outputFormat,	1
	call	load_file_data
	mov		[animation_memory],	LDA_output
.create_toc:
	mov		PRS_dataPtr,		LDA_output
	mov		PRS_dataSize,		4
	mov		PRS_buffer_32,		0xFFFFFFFF
	call	parse_file_data

.exit:
	pop		rax
	pop		rcx
	pop		rdx

	add		rsp,	28h
	ret
