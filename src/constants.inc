;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Program Constants
CONST_windowWidth		equ 1080
CONST_windowHeight		equ  720
;* For Raylib camera offset
CONST_windowWidthHalf	equ  508f	;476f	;540f
CONST_windowHeightHalf	equ  328f	;296f	;360f

;;=  Programming shortcuts
output					equ	rax
input_1					equ rcx
input_2					equ rdx
input_3					equ r8
input_4					equ r9
input_5					equ dword [rsp+0x20]


walk_speed	equ	4f
run_speed	equ	8f


include 'constants/raylib.inc'
include 'constants/sprite_data.inc'
include 'constants/general_memory.inc'
include 'constants/player_memory.inc'
