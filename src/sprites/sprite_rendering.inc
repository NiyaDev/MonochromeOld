;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  DrawAnimatedSprite(AnimatedSprite:&sprite, Vector2:position);
;;=  RCX = &sprite		RDX = positon
;;=  	Draws the current frame in the pointed to AnimatedSprite
;;=		in the world at the input postion.
draw_animated_sprite:
	sub		rsp,28h

	mov		r8,[general_memory]
	mov		r9,rcx

	xor		r10,r10
	mov		r10b,[r9+AnimatedSprite.frameTime]

	inc		[r9+AnimatedSprite.timer]
	cmp		[r9+AnimatedSprite.timer],r10w
	jge		.change_sprite
	jmp		.display_sprite

.change_sprite:
	mov		[r9+AnimatedSprite.timer],0
	xor		rax,rax
	mov		al,byte[r9+AnimatedSprite.curFrame]
	imul	rax,4
	mov		rbx,[r9+AnimatedSprite.curClip]
	add		rbx,rax
	mov		eax,[rbx+4]
	cmp		eax,0xffffffff
	je		.recall
.increase:
	inc		[r9+AnimatedSprite.curFrame]
	jmp		.update_rect
.recall:
	mov		[r9+AnimatedSprite.curFrame],0
	jmp		.update_rect

.update_rect:
	mov		rcx,r9
	call	update_rectangle

.display_sprite:
	;;DrawTextureRec(&PlayerData.spriteTexture,&PlayerData.spriteRect,{PlayerData.camera.target.x-64f,PlayerData.camera.target.y-64f},WHITE);
	lea		rcx,[r9+AnimatedSprite.texture]
	mov		r8,rdx
	lea		rdx,[r9+AnimatedSprite.rect]
	mov		r9d,WHITE
	call	[DrawTextureRec]

	add		rsp,28h
	ret


;;=  void ChangeAnimation(AnimatedSprite:&sprite, int:animation);
;;=  RCX = &sprite		RDX = animation
;;=  	Changes the current playing animation in the
;;=		pointed to AnimatedSprite to the animation input.
change_animated_sprite:
	sub 	rsp,28h

.Init:
	mov		r8,[animation_memory]
	imul	rdx,8
	add		r8,rdx
	mov		rax,[r8]
.check:
	cmp		rax,[rcx+AnimatedSprite.curClip]
	je		.exit
.change:
	mov		[rcx+AnimatedSprite.curClip],rax
	mov		[rcx+AnimatedSprite.curFrame],0
	mov		[rcx+AnimatedSprite.frameTime],16
	mov		[rcx+AnimatedSprite.timer],0
	call	update_rectangle

.exit:
	add		rsp,28h
	ret


;;=  void UpdateRectangle(AnimatedSprite:&sprite);
;;=  RCX = &sprite		RDX = animation
;;=  	Changes the current playing animation in the
;;=		pointed to AnimatedSprite to the animation input.
update_rectangle:
	sub		rsp,28h

.update:
	xor		rax,rax
	mov		al,byte[rcx+AnimatedSprite.curFrame]
	imul	rax,4
	mov		rbx,[rcx+AnimatedSprite.curClip]
	add		rbx,rax
	mov		eax,[rbx]
	mov		[rcx+AnimatedSprite.rect.x],eax

.exit:
	add		rsp,28h
	ret