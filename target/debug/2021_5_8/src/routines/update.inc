;/*/
; * @Date:		4/25/21
; * @Author:	Szyfr
;/*/

;;=  Standard Update call
update:
	pop [home]
	
	;;Checks each key, then shifts the response into position
	xor rax,rax
	xor rbx,rbx

	mov rcx,KEY_A
	call [IsKeyDown]
	or bl,al

	mov rcx,KEY_D
	call [IsKeyDown]
	shl al,1
	or bl,al

	mov rcx,KEY_W
	call [IsKeyDown]
	shl al,2
	or bl,al

	mov rcx,KEY_S
	call [IsKeyDown]
	shl al,3
	or bl,al

	;;Reads the bits
	mov rax,[general_memory]
	add rax,CONST_dword
	mov dword [rax],10
.horizontal_neg:
	bt rbx,0
	jnc .horizontal_pos
	fld dword [camera.target.x]
	fisub dword [rax]
	fstp dword [camera.target.x]
.horizontal_pos:
	bt rbx,1
	jnc .vertical_neg
	fld dword [camera.target.x]
	fiadd dword [rax]
	fstp dword [camera.target.x]

.vertical_neg:
	bt rbx,2
	jnc .vertical_pos
	fld dword [camera.target.y]
	fisub dword [rax]
	fstp dword [camera.target.y]
.vertical_pos:
	bt rbx,3
	jnc .exit
	fld dword [camera.target.y]
	fiadd dword [rax]
	fstp dword [camera.target.y]
	;call TestControlBit
	
.exit:
	push [home]
	ret