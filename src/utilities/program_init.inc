;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Initializes all necessary systems and memory spaces
allocateMemoryOut	equ		rax
offsetMover			equ		rbx
initWindowInputC	equ		ecx
targetFPSInput		equ		ecx
allocateMemoryInput	equ		rcx
loadImageInputC		equ		rcx
setIconInput		equ		rcx
unloadImageInput	equ		rcx
importSpriteInputC	equ		rcx
initWindowInputD	equ		edx
loadImageInputD		equ		rdx
importSpriteInputD	equ		rdx
initWindowInput8	equ		r8

playerRect			equ		rax
playerRectX			equ		rax+PlayerData.entity.sprite.rect.x
playerRectY			equ		rax+PlayerData.entity.sprite.rect.y
playerRectWidth		equ		rax+PlayerData.entity.sprite.rect.width
playerRectHeight	equ		rax+PlayerData.entity.sprite.rect.height

generalMemory		equ		r8
generalOffset		equ		r8+100
generalImage		equ		r8+GeneralImage

playerMemory		equ		r8
playerTexture		equ		r8+PlayerData.entity.sprite.texture
playerFrameTime		equ		r8+PlayerData.entity.sprite.frameTime
playerCurClip		equ		r8+PlayerData.entity.sprite.curClip
playerDirection		equ		r8+PlayerData.ctrData.direction
playerCameraTargetX	equ		r8+PlayerData.camera.target.x
playerCameraTargetY	equ		r8+PlayerData.camera.target.y
playerCameraOffsetX	equ		r8+PlayerData.camera.offset.x
playerCameraOffsetY	equ		r8+PlayerData.camera.offset.y
playerCameraZoom	equ		r8+PlayerData.camera.zoom

animationMemory		equ		r9
animationOffset		equ		r9+32
program_init:
	sub		rsp,	$28

.initialize_window:
	mov		initWindowInputC,		CONST_windowWidth
	mov		initWindowInputD,		CONST_windowHeight
	lea		initWindowInput8,		[title]
	call	InitWindow
.set_fps:
	mov		targetFPSInput,			60
	call	SetTargetFPS

.allocate_general_memory:
	mov		allocateMemoryInput,	CONST_memorySize
	call	allocate_memory
	mov		[general_memory],		allocateMemoryOut
.allocate_player_memory:
	mov		allocateMemoryInput,	CONST_memorySize
	call	allocate_memory
	mov		[player_memory],		allocateMemoryOut
.allocate_animation_memory:
	call	load_animations

.set_icon:
	mov		generalMemory,			[general_memory]
	lea		loadImageInputC,		[generalImage]
	lea		loadImageInputD,		[icon_text]
	call	LoadImageRL

	mov		generalMemory,			[general_memory]
	lea		setIconInput,			[generalImage]
	call	SetWindowIcon

	mov		generalMemory,			[general_memory]
	lea		unloadImageInput,		[generalImage]
	call	UnloadImage

.initialize_map_sprite:
	lea		importSpriteInputC,		[map_pallet]
	mov		generalMemory,			[general_memory]
	lea		importSpriteInputD,		[generalOffset]
	call	import_sprite

.initialize_player_sprites:
	lea		importSpriteInputC,		[player_overworld_m_text]
	mov		playerMemory,			[player_memory]
	lea		importSpriteInputD,		[playerTexture]
	call	import_sprite

.initialize_player_data:
;;TODO: Keep this up-to-date.
	mov		playerMemory,			[player_memory]
	mov		animationMemory,		[animation_memory]

.initialize_sprite_rectangle:
	mov		playerRect,				[player_memory]
	mov		[playerRectX],			0f
	mov		[playerRectY],			0f
	mov		[playerRectWidth],		64f
	mov		[playerRectHeight],		64f

.initialize_animation:
	mov		offsetMover,			[animationOffset]
	mov		[playerFrameTime],		8h
	mov		[playerCurClip],		offsetMover
	mov		[playerDirection],		0

.setup_camera:
	mov		playerMemory,			[player_memory]
	mov		[playerCameraTargetX],	0f
	mov		[playerCameraTargetY],	0f
	mov		[playerCameraOffsetX],	CONST_windowWidthHalf
	mov		[playerCameraOffsetY],	CONST_windowHeightHalf
	mov		[playerCameraZoom],		1f

.exit:
	add		rsp,	$28
	ret


include 'memory.inc'
include '../sprites/sprite_initializing.inc'
include '../sprites/animation_loading.inc'