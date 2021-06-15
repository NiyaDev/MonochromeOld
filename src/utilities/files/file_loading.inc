;*/
;* @Date:		6/15/21
;* @Author:		Szyfr
;*/



;;=  Loads contents of a file and stores a pointer to heap
;;=	 Also stores file length at the start of the heap
;;=		Input:		RCX = &filename
;;=					RDX = outputFormat
;;=						0:Regular	1:ToC
;;=		Output:		RAX = &data
;;TODO: This thing need another look over
;;TODO:	I swear... I lost 10 years because of this...
;filename			equ		rcx		;Input
;outputFormat		equ		rdx		;Input
;output				equ		rax		;Output
;
;newSize				equ		rcx
;allocationResult	equ		rax
;
;bytesToMove			equ		rcx
;oldFile				equ		r8
;newFile				equ		r9
;copyData			equ		r10d
;
;rawFilePtr			equ		rax
;;rawFileLocation		equ		general_memory+GeneralQword
;rawFileLocation		equ		r11+GeneralQword
;
;fileToFree			equ		rcx
;
;bytesReadPtr		equ		rdx		;FuncInput
;;bytesReadLocation	equ		general_memory+GeneralDword
;bytesReadLocation	equ		r11+GeneralDword
;load_file_data:
;	sub		rsp,	28h
;
;	push	filename
;	push	outputFormat
;.loading_file:
;	mov		r11,					general_memory
;	mov		bytesReadPtr,			[bytesReadLocation]
;;	lea		bytesReadPtr,			[bytesReadLocation]
;	call	LoadFileData
;
;.check_format:
;	pop		outputFormat
;	pop		filename
;	cmp		outputFormat,			0
;	je		.exit
;
;.allocate_new_memory:
;;	lea		rdx,					[bytesReadLocation]
;	mov		r11,					general_memory
;	mov		[rawFileLocation],		rawFilePtr
;	mov		newSize,				[bytesReadLocation]
;;	lea		newSize,				[bytesReadLocation]
;	imul	newSize,				2
;	call	MemAlloc
;
;.copy_init:
;;	mov		rdx,					[general_memory]
;	mov		r11,					general_memory
;	mov		bytesToMove,			[bytesReadLocation]
;	mov		oldFile,				[rawFileLocation]
;	mov		newFile,				allocationResult
;	add		newFile,				bytesToMove
;
;.copy_loop:
;	mov		copyData,				[oldFile]
;	mov		[newFile],				copyData
;	add		oldFile,				4
;	add		newFile,				4
;	sub		bytesToMove,			4
;	jnz		.copy_loop
;
;.remove_old_pointer: ;int3
;	mov		r11,					general_memory
;	mov		fileToFree,				[rawFileLocation]
;	mov		[rawFileLocation],		allocationResult
;	call	UnloadFileData
;
;;	mov		rdx,					[general_memory]
;	mov		r11,					general_memory
;	mov		newSize,				[bytesReadLocation]
;	mov		output,					[rawFileLocation]
;	mov		[output],				newSize
;
;.exit:
;	add		rsp,	28h
;	ret



filename			equ		rcx		;Input
outputFormat		equ		rdx		;Input
output				equ		rax		;Output
oldPtr				equ		rax

generalMemory		equ		rdx
firstAllocSize		equ		rdx
secondAllocSize		equ		rcx

fileDataPtr			equ		rdx+60

byteCounter			equ		rcx
oldPtrL				equ		r8
newPtrL				equ		r9
copiedDword			equ		r10d
load_file_data:
	sub		rsp,	28h

	push	filename
.loading_file:
	mov		firstAllocSize,			[general_memory]
	call	LoadFileData

.check_format:
	pop		filename
	cmp		filename,				0
	je		.exit

.allocate_new_memory:
	mov		generalMemory,			[general_memory]
	mov		[fileDataPtr],			output

	mov		secondAllocSize,		[generalMemory]
	imul	secondAllocSize,		2
	call	MemAlloc

.copy_init:
	mov		generalMemory,			[general_memory]
	mov		byteCounter,			[generalMemory]
	mov		oldPtrL,				[fileDataPtr]
	mov		newPtrL,				output
	add		newPtrL,				byteCounter

.copy_loop:
	mov		copiedDword,			[oldPtrL]
	mov		[newPtrL],				copiedDword
	add		oldPtrL,				4
	add		newPtrL,				4
	sub		byteCounter,			4
	jnz		.copy_loop

.remove_old_pointer:
	mov		rcx,					[fileDataPtr]
	mov		[fileDataPtr],			oldPtr
	call	UnloadFileData

	mov		generalMemory,			[general_memory]
	mov		rcx,					[generalMemory]
	mov		output,					[fileDataPtr]
	mov		[output],				rcx

.exit:
	add		rsp,	28h
	ret