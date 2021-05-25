;*/
;* @Date:		5/13/21
;* @Author:		Szyfr
;*/


CONST_resizeFactor equ 2	;(ImageDimensions)*2^CONST_resizeFactor

CONST_sprite_0	equ	0f
CONST_sprite_1	equ	64f
CONST_sprite_2	equ	128f
CONST_sprite_3	equ	192f
CONST_sprite_4	equ	256f
CONST_sprite_5	equ	320f
CONST_sprite_6	equ	384f
CONST_sprite_7	equ	448f
CONST_sprite_8	equ	512f
CONST_sprite_9	equ	576f


struc AnimatedSprite {
	.texture	Texture2D		;20-bytes
	.rect		Rectangle		;16-bytes
	.curClip	dq		0		; 8-bytes
	.curFrame	db		0		; 1-byte
	.frameTime	db		0		; 1-byte
	.timer		dw		0		; 2-bytes
}	;46-bytes

virtual at 0
	AnimatedSprite	AnimatedSprite
	sizeof.AnimatedSprite = $ - AnimatedSprite
end virtual