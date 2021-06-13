;*/
;* @Date:		5/4/21
;* @Author:		Szyfr
;*/


;;=  Initializes all necessary systems and memory spaces
program_init:
	sub		rsp,$28

.initialize_window:
	mov		ecx,CONST_windowWidth
	mov		edx,CONST_windowHeight
	lea		r8,[title]
	call	InitWindow
.set_fps:
	mov		ecx,60
	call	SetTargetFPS

.allocate_general_memory:
	mov		rcx,CONST_memorySize
	call	allocate_memory
	mov		[general_memory],rax
.allocate_player_memory:
	mov		rcx,CONST_memorySize
	call	allocate_memory
	mov		[player_memory],rax
.allocate_animation_memory:
	call	load_animations

.set_icon:
	;;SetWindowIcon(&image)
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
	lea		rdx,[icon_text]
;	call	qword[LoadImageRL]
	call	LoadImageRL
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
	call	SetWindowIcon
	mov		rax,[general_memory]
	lea		rcx,[rax+GeneralMemory.image]
	call	UnloadImage

.initialize_map_sprite:
	lea		rcx,[map_pallet]
	mov		rax,[general_memory]
	lea		rdx,[rax+100]
	call	import_sprite

.initialize_player_sprites:
	;;ImportSprite(&player_overworld_m_text,&PlayerData.spriteTexture)
	lea		rcx,[player_overworld_m_text]
	mov		rax,[player_memory]
	lea		rdx,[rax+PlayerData.entity.sprite.texture]
	call	import_sprite

.initialize_player_data:
;;TODO: Keep this up-to-date.
	mov		r8,[player_memory]
	mov		r9,[animation_memory]
;	mov		[r8+PlayerData.entity.sprite.]
.initialize_sprite_rectangle:
	;;PlayerData.spriteRect = {0,0,64f,64f};
	mov		rax,[player_memory]
	mov		dword [rax+PlayerData.entity.sprite.rect.x],0f
	mov		dword [rax+PlayerData.entity.sprite.rect.y],0f
	mov		dword [rax+PlayerData.entity.sprite.rect.width],64f
	mov		dword [rax+PlayerData.entity.sprite.rect.height],64f

.initialize_animation:
	mov		r8,[player_memory]
	mov		r9,[animation_memory]
	mov		rbx,[r9+32]
	mov		[r8+PlayerData.entity.sprite.frameTime],8h
	mov		[r8+PlayerData.entity.sprite.curClip],rbx

;.initialize_player_data:
	mov		[r8+PlayerData.ctrData.direction],0

.setup_camera:
	;;camera = {0,0,CONST_windowWidthHalf,CONST_windowHeightHalf,1f};
	mov		rax,[player_memory]
	mov		dword [rax+PlayerData.camera.target.x],0f
	mov		dword [rax+PlayerData.camera.target.y],0f
	mov		dword [rax+PlayerData.camera.offset.x],CONST_windowWidthHalf
	mov		dword [rax+PlayerData.camera.offset.y],CONST_windowHeightHalf
	mov		dword [rax+PlayerData.camera.zoom],1f

.exit:
	add		rsp,$28
	ret


include 'memory.inc'
include '../sprites/sprite_initializing.inc'
include '../sprites/animation_loading.inc'