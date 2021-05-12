;*/
;* @Date:		4/25/21
;* @Author:		Szyfr
;*/

;;=  Initializes all necessary systems and memory spaces
program_init:
	sub rsp,$28

.initialize_window:
	;;InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,*title)
	mov ecx,CONST_windowWidth
	mov edx,CONST_windowHeight
	lea r8,[title]
	call [InitWindow]
	;;SetTargetFPS(60)
	mov ecx,60
	call [SetTargetFPS]

.allocate_general_memory:
	;;general_memory = MemAlloc(CONST_memorySize)
	mov rcx,CONST_memorySize
	call [MemAlloc]
	mov [general_memory],rax
	;;CleanMemory(&general_memory,CONST_memorySize)
	mov rcx,[general_memory]
	mov rdx,CONST_memorySize
	call CleanMemory
.allocate_player_memory:
	;;player_memory = MemAlloc(CONST_memorySize)
	mov rcx,CONST_memorySize
	call [MemAlloc]
	mov [player_memory],rax
	;;CleanMemory(&player_memory,CONST_memorySize)
	mov rcx,[player_memory]
	mov rdx,CONST_memorySize
	call CleanMemory

.initialize_player_sprites:
	;;import_sprite(&player_overworld_m_text,&PlayerData.spriteTexture)
	lea rcx,[player_overworld_m_text]
	mov rax,[player_memory]
	lea rdx,[rax+PlayerData.spriteTexture]
	call import_sprite

	;;PlayerData.spriteRect = {0,0,64f,64f};
	mov rax,[player_memory]
	mov dword [rax+PlayerData.spriteRect.x],0f
	mov dword [rax+PlayerData.spriteRect.y],0f
	mov dword [rax+PlayerData.spriteRect.width],64f
	mov dword [rax+PlayerData.spriteRect.height],64f

.setup_camera:
	;;camera = {0,0,CONST_windowWidthHalf,CONST_windowHeightHalf,1f};
	mov rax,[player_memory]
	mov dword [rax+PlayerData.camera.target.x],0f
	mov dword [rax+PlayerData.camera.target.y],0f
	mov dword [rax+PlayerData.camera.offset.x],CONST_windowWidthHalf
	mov dword [rax+PlayerData.camera.offset.y],CONST_windowHeightHalf
	mov dword [rax+PlayerData.camera.zoom],1f

;.setup_camera:
	;;camera = {0,0,CONST_windowWidthHalf,CONST_windowHeightHalf,1f};
;	mov dword [camera.target.x],0f
;	mov dword [camera.target.y],0f
;	mov dword [camera.offset.x],CONST_windowWidthHalf
;	mov dword [camera.offset.y],CONST_windowHeightHalf
;	mov dword [camera.zoom],1f

	add rsp,$28
	ret


include 'clean_memory.inc'
include '../sprites/sprite_initializing.inc'