
include 'include/win64a.inc'
include 'constants.inc'


;;=  Windows
format MS64 COFF
;;=  Linux
;format ELF64 executable 3

section '.text' code readable executable

;*
;*	Don't know if these are important yet
;*;entry start
;*;public Main
;*;public start as '_start'
;*
public start as 'WinMain'

extrn 'WindowShouldClose' as WindowShouldClose
extrn 'IsKeyDown' as IsKeyDown
extrn 'BeginDrawing' as BeginDrawing
extrn 'ClearBackground' as ClearBackground
extrn 'BeginMode2D' as BeginMode2D
extrn 'DrawRectangle' as DrawRectangle
extrn 'DrawTexture' as DrawTexture
extrn 'EndMode2D' as EndMode2D
extrn 'EndDrawing' as EndDrawing
extrn 'DrawTextureRec' as DrawTextureRec
extrn 'InitWindow' as InitWindow
extrn 'SetTargetFPS' as SetTargetFPS
extrn 'MemAlloc' as MemAlloc
extrn 'LoadImage' as LoadImageRL
extrn 'UnloadImage' as UnloadImage
extrn 'LoadTextureFromImage' as LoadTextureFromImage
extrn 'ImageResizeNN' as ImageResizeNN
extrn 'SetWindowIcon' as SetWindowIcon
extrn 'LoadFileData' as LoadFileData
extrn 'UnloadFileData' as UnloadFileData
extrn 'MemFree' as MemFree
extrn 'CloseWindow' as CloseWindowRL

start:
	; Make stack dqword aligned
	sub	rsp,8
	sub rsp,$100

.init:
	;;ProgramInit()
	call program_init

.loop:
	;;Update()
	call update
	;;Draw()
	call draw
	
	;;While (!WindowShouldClose())
	call qword WindowShouldClose
	cmp rax,1
	jnz .loop

.exit:
	;;ProgramExit()
	call program_exit
	
	ret



include 'routines/update.inc'
include 'routines/draw.inc'
include 'utilities/program_init.inc'
include 'utilities/program_exit.inc'


include 'data.inc'
;include 'idata.inc'