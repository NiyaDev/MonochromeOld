
;;=  Program Constants
CONST_windowWidth		equ 1080
CONST_windowHeight		equ  720
CONST_windowWidthHalf	equ  540f
CONST_windowHeightHalf	equ  360f

CONST_anim_0	equ	0f
CONST_anim_1	equ	64f
CONST_anim_2	equ	128f
CONST_anim_3	equ	192f
CONST_anim_4	equ	256f
CONST_anim_5	equ	320f
CONST_anim_6	equ	384f
CONST_anim_7	equ	448f


include 'constants/raylib.inc'
include 'constants/sprite_data.inc'
include 'constants/general_memory.inc'
include 'constants/player_memory.inc'


virtual at r10
	tileName		db	?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?
	tileCityname	db	?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?
	tileCitylevel	db	?
	tileTerrain		db	?
	tileBuildings	db	?,?,?,?,?,?,?,?,?,?
	tilePopulation	dq	?
end virtual

virtual at rdx
	srctileName			db	?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?
	srctileCityname		db	?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?
	srctileCitylevel	db	?
	srctileTerrain		db	?
	srctileBuildings	db	?,?,?,?,?,?,?,?,?,?
	srctilePopulation	dq	?
end virtual