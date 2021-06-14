;*/
;* @Date:		5/13/21
;* @Author:		Szyfr
;*/



;;=  Constants
CONST_resizeFactor equ 2	;(ImageDimensions)*2^CONST_resizeFactor


;;=  Structures
struc AnimatedSprite {
	.texture	Texture2D		;20-bytes
	.rect		Rectangle		;16-bytes
	.curClip	dq		0		; 8-bytes
	.curFrame	db		0		; 1-byte
	.frameTime	db		0		; 1-byte
	.timer		dw		0		; 2-bytes
}	;46-bytes


;;=  Macro
virtual at 0
	AnimatedSprite	AnimatedSprite
	sizeof.AnimatedSprite = $ - AnimatedSprite
end virtual