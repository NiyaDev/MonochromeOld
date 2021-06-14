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
	mov		qword [rax+GeneralQword],rdx
	mov		rdx,rcx

	;;LoadTexture(&GeneralMemory.image,&filename);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralImage]
;	call [LoadImageRL]
	call	LoadImageRL

	;;ImageResizeNN(&GeneralMemory.image,GeneralMemory.image.width*4,GeneralMemory.image.height*4);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralImage]
	mov		edx,[rax+GeneralImageWidth]
	shl		rdx,CONST_resizeFactor
	mov		r8d,[rax+GeneralImageHeight]
	shl		r8,CONST_resizeFactor
	call	ImageResizeNN

	;;LoadTextureFromImage(&texture,&GeneralMemory.image);
	mov		rax,[general_memory]
	mov		rcx,qword[rax+GeneralQword]
	lea		rdx,[rax+GeneralImage]
	call	LoadTextureFromImage

	;;UnloadImage(&GeneralMemory.image);
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralImage]
	call	UnloadImage

	add		rsp,$28
	ret