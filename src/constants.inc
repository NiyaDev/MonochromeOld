;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Program Constants
;;TODO: Make into actual variables
CONST_windowWidth		equ 640;1080
CONST_windowHeight		equ 576; 720
CONST_windowWidthHalf	equ 256f;508f	;476f	;540f
CONST_windowHeightHalf	equ 240f;328f	;296f	;360f
walkSpeed				equ	4f
runSpeed				equ	8f

;;=  Programming shortcuts
StackVariableOne		equ dword [rsp+0x20]


include 'constants/raylib.inc'
include 'constants/sprite_data.inc'
include 'constants/overworld_entities.inc'
include 'constants/general_memory.inc'
include 'constants/player_memory.inc'
