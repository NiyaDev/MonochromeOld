;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  Grabs a file from the input filename, outputs a resized texture, and frees the image
;;=		Input:		RCX = &filename
;;=					RDX = &texture
;;=		Output:		N/A
filenamePtr			equ		rcx		;Input
texturePtr			equ		rdx		;Input

generalPtr			equ		rax
imagePtr			equ		rcx
imageWidth			equ		edx
imageWidthFull		equ		rdx
imageHeight			equ		r8d
imageHeightFull		equ		r8

memTexturePtr		equ		rax+GeneralQword
memImage			equ		rax+GeneralImage
memImageWidth		equ		rax+GeneralImageWidth
memImageHeight		equ		rax+GeneralImageHeight
import_sprite:
	sub		rsp,	$28
	
.load_image:
	mov		generalPtr,				[general_memory]
	mov		[memTexturePtr],		texturePtr
	mov		texturePtr,				filenamePtr

	lea		imagePtr,				[memImage]
	call	LoadImageRL

.resize_image:
	mov		generalPtr,				[general_memory]

	lea		imagePtr,				[memImage]
	mov		imageWidth,				[memImageWidth]
	shl		imageWidthFull,			CONST_resizeFactor
	mov		imageHeight,			[memImageHeight]
	shl		imageHeightFull,		CONST_resizeFactor
	call	ImageResizeNN

.convert_image_texture:
	mov		generalPtr,				[general_memory]
	mov		imagePtr,				[memTexturePtr]
	lea		texturePtr,				[memImage]
	call	LoadTextureFromImage

.unload_image:
	mov		generalPtr,				[general_memory]
	lea		imagePtr,				[memImage]
	call	UnloadImage

.exit:
	add		rsp,$28
	ret