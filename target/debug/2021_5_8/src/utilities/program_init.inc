;*/
;* @Date:		4/25/21
;* @Author:		Szyfr
;*/

;;=  Initializes all necessary systems and memory spaces
program_init:
	pop [home]

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

.setup_camera:
	;Setting target
	mov dword [camera.target.x],0f
	mov dword [camera.target.y],0f
	;Setting offset
	mov dword [camera.offset.x],CONST_windowWidthHalf
	mov dword [camera.offset.y],CONST_windowHeightHalf
	;Setting zoom
	mov dword [camera.zoom],1f

.grab_sprites:
;;TODO: Make the process of Loading an image, resizing it, then making it a texture into a function
	;;LoadTexture(&player_overworld)
	mov rcx,[general_memory]
	add rcx,CONST_image
	lea rdx,[player_overworld_text]
	call [LoadImageRL]

	mov rcx,[general_memory]
	add rcx,CONST_image
	mov edx,[rcx+8]
	shl rdx,2
	mov r8,[rcx+12]
	shl r8,2
	call [ImageResizeNN]

	mov rcx,[player_memory]
	add rcx,CONST_playerSprite
	mov rdx,[general_memory]
	add rdx,CONST_image
	call [LoadTextureFromImage]

	mov rax,[player_memory]
	add rax,CONST_playerRect
	mov dword [rax],0f
	mov dword [rax+4],0f
	mov dword [rax+8],64f
	mov dword [rax+12],64f

	push [home]
	ret


include 'clean_memory.inc'
include '../sprites/sprite_initializing.inc'