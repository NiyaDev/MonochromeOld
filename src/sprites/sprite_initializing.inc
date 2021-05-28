;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  Grabs a file from the input filename, outputs a resized texture, and frees the image
;;=  RCX = &filename		RDX = &texture
import_sprite:
	sub		rsp,$28
	
	;move filename to rdx and texture
	mov		rax,[general_memory]
	mov		qword [rax+GeneralMemory.qword],rdx
	mov		rdx,rcx

	;;LoadTexture(&GeneralMemory.image,&filename);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
;	call [LoadImageRL]
	call	qword LoadImageRL

	;;ImageResizeNN(&GeneralMemory.image,GeneralMemory.image.width*4,GeneralMemory.image.height*4);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
	mov		edx,[rax+GeneralMemory.image.width]
	shl		rdx,CONST_resizeFactor
	mov		r8d,[rax+GeneralMemory.image.height]
	shl		r8,CONST_resizeFactor
	call	qword ImageResizeNN

	;;LoadTextureFromImage(&texture,&GeneralMemory.image);
	mov		rax,[general_memory]
	mov		rcx,qword[rax+GeneralMemory.qword]
	lea		rdx,[rax+GeneralMemory.image]
	call	qword LoadTextureFromImage

	;;UnloadImage(&GeneralMemory.image);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
	call	qword UnloadImage

	add		rsp,$28
	ret