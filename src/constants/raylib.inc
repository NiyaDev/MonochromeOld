;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Color definitions
WHITE			equ	$ffffffff
RAYWHITE		equ	$fff5f5f5
BLACK			equ	$ff000000

;;=  Key definitions
KEY_A			equ 65
KEY_B			equ 66
KEY_C			equ 67
KEY_D			equ 68
KEY_E			equ 69
KEY_F			equ 70
KEY_G			equ 71
KEY_H			equ 72
KEY_I			equ 73
KEY_J			equ 74
KEY_K			equ 75
KEY_L			equ 76
KEY_M			equ 77
KEY_N			equ 78
KEY_O			equ 79
KEY_P			equ 80
KEY_Q			equ 81
KEY_R			equ 82
KEY_S			equ 83
KEY_T			equ 84
KEY_U			equ 85
KEY_V			equ 86
KEY_W			equ 87
KEY_X			equ 88
KEY_Y			equ 89
KEY_Z			equ 90

KEY_ENTER		equ 257
KEY_BACKSPACE	equ 259

MOUSE_LEFT		equ	0
MOUSE_RIGHT		equ	1
MOUSE_MIDDLE	equ	2

;;=  Structures
struc Color r,g,b,a {
	.r	db	r
	.g	db	g
	.b	db	b
	.a	db	a
}
COLOR_SIZE		equ 4

struc Vector2 x,y {
	.x	dd	x
	.y	dd	y
}
VECTOR2_SIZE	equ 8

struc Rectangle {
	.x		dd	?
	.y		dd	?
	.width	dd	?
	.height	dd	?
}
RECTANGLE_SIZE	equ 16

struc Camera2D {
	.offset		Vector2		0,0
	.target		Vector2		0,0
	.rotation	dd			0
	.zoom		dd			1
}
CAMERA2D_SIZE	equ 24

struc Image {
	.data		dq			?
	.width		dd			?
	.height		dd			?
	.mipmaps	dd			?
	.format		dd			?
}
IMAGE_SIZE		equ 24

struc Texture2D {
	.id			dd			?
	.width		dd			?
	.height		dd			?
	.mipmaps	dd			?
	.format		dd			?
}
TEXTURE2D_SIZE	equ 20

struc Font {
	.baseSize		dd			?
	.charsCount		dd			?
	.charsPadding	dd			?
	.texture		Texture2D
	.recs			dq			?
	.chars			dq			?
}