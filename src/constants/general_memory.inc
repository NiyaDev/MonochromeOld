;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/



;;=  Constants
CONST_memorySize	equ 	10000	;Total of: 10,000 bytes


;;=  Memory locations
;;*  General use variables
GeneralByte			equ		10
GeneralWord			equ		0
GeneralDword		equ		11
GeneralQword		equ		2

GeneralVector2		equ		15
GeneralVector2X		equ		15
GeneralVector2Y		equ		19

GeneralImage		equ		23
GeneralImageData	equ		23
GeneralImageWidth	equ		31
GeneralImageHeight	equ		35
GeneralImageMipMap	equ		39
GeneralImageFormat	equ		43

Font				equ		  50
FontTexture			equ		  62
PauseMenuSprite		equ		 102
CursorSprite		equ		 122

TempMap				equ		1000