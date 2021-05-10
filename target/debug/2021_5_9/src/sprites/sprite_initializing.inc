;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/

import_sprite:
	pop rax
	mov rbx,[general_memory]
	mov qword[rbx],rax
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

	mov rbx,[general_memory]
	mov rax,qword[rbx]
	push rax
	ret