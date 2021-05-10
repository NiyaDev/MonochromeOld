
section '.idata' import data readable writeable
library kernel32,	'KERNEL32.DLL',\
		user32,		'USER32.DLL',\
		msvcrt,		'MSVCRT.DLL',\
		raylib,		'RAYLIB.DLL'
include 'include/api/kernel32.inc'
include 'include/api/user32.inc'
import	msvcrt, printf,				'printf'
import	raylib, InitWindow,			'InitWindow',\
				SetTargetFPS,		'SetTargetFPS',\
				WindowShouldClose,	'WindowShouldClose',\
				CloseWindowRL,		'CloseWindow',\
				BeginDrawing,		'BeginDrawing',\
				EndDrawing,			'EndDrawing',\
				ClearBackground,	'ClearBackground',\
				MemAlloc,			'MemAlloc',\
				MemFree,			'MemFree',\
				DrawTextRL,			'DrawText',\
				LoadFileData,		'LoadFileData',\
				UnloadFileData,		'UnloadFileData',\
				IsKeyPressed,		'IsKeyPressed',\
				IsKeyDown,			'IsKeyDown',\
				GenImageColor,		'GenImageColor',\
				GenImageGradientV,	'GenImageGradientV',\
				DrawTexture,		'DrawTexture',\
				LoadTextureFromImage,'LoadTextureFromImage',\
				UnloadTexture,		'UnloadTexture',\
				UpdateCamera,		'UpdateCamera',\
				BeginMode2D,		'BeginMode2D',\
				EndMode2D,			'EndMode2D',\
				DrawRectangle,		'DrawRectangle'