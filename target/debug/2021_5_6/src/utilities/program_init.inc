;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Initializes all necessary systems and memory spaces
program_init:
	pop [home]

	;;InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,*title)
	mov ecx,WINDOW_WIDTH
	mov edx,WINDOW_HEIGHT
	lea r8,[title]
	call [InitWindow]

	;;SetTargetFPS(60)
	mov ecx,60
	call [SetTargetFPS]

	;;general_memory = MemAlloc(GENERAL_MEMORY_SIZE)
	mov rcx,GENERAL_MEMORY_SIZE
	call [MemAlloc]
	mov [general_memory],rax
	;;CleanMemory(&general_memory,GENERAL_MEMORY_SIZE)
	mov rcx,[general_memory]
	mov rdx,GENERAL_MEMORY_SIZE
	call CleanMemory

	;;Setup Camera
	;Getting address for DWRD_WORK
	mov rax,[general_memory]
	add rax,DWRD_WORK
	;Setting target
	mov dword [rax],0
	fild dword [rax]
	fst dword [camera.target.x]
	mov dword [rax],0
	fild dword [rax]
	fstp dword [camera.target.y]
	
	;Setting offset
	mov dword [rax],WINDOW_WIDTH/2
	fild dword [rax]
	fst dword [camera.offset.x]
	mov dword [rax],WINDOW_HEIGHT/2
	fild dword [rax]
	fstp dword [camera.offset.y]
	
	;Setting zoom
	mov dword [rax],1
	fild dword [rax]
	fstp dword [camera.zoom]


	push [home]
	ret


include 'clean_memory.inc'



	;;tile_sprite = GenImageGradientV(&tile_sprite,16,16,BLACK,RAYWHITE)
;	lea rcx,[tile_sprite]
;	mov edx,16
;	mov r8d,16
;	mov r9d,BLACK
;	mov dword [rsp+0x20],RAYWHITE
;	call [GenImageGradientV]

	;;tile_texture = LoadTextureFromImage(&tile_sprite)
;	lea rcx,[tile_texture]
;	lea rdx,[tile_sprite]
;	xor r8,r8
;	xor r9,r9
;	call [LoadTextureFromImage]

	;;tile_memory = MemAlloc(TILE_SIZE*100)
;	mov rcx,TILE_SIZE*100
;	call [MemAlloc]
;	mov [tile_memory],rax
	;;CleanMemory(&tile_memory,TILE_SIZE*100)
;	mov rcx,[tile_memory]
;	mov rdx,TILE_SIZE*100
;	call CleanMemory

;	mov rax,[tile_memory]
;	xor rbx,rbx
;.setBeginning: ;;Debug
;	mov [tileCitylevel],$1
;	add rax,TILE_SIZE
;	inc rbx

;	cmp rbx,100
;	jnz .setBeginning