;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  Draws the current frame in the pointed to AnimatedSprite at the input position
;;=  	Input:		RCX = &sprite
;;=					RDX = positon
DAS_sprite			equ		rcx
DAS_position		equ		rdx

DAS_generalMemPtr	equ		r8
DAS_spritePtr		equ		r9
DAS_spriteFrameTime	equ		r9+AnimatedSprite.frameTime
DAS_spriteTimer		equ		r9+AnimatedSprite.timer

DAS_timing			equ		r10
DAS_timingByte		equ		r10b
DAS_timingWord		equ		r10w
draw_animated_sprite:
	sub		rsp,	28h

	mov		DAS_generalMemPtr,		[general_memory]
	mov		DAS_spritePtr,			DAS_sprite
	xor		DAS_timing,				DAS_timing

	mov		DAS_timingByte,			[DAS_spriteFrameTime]

	inc		[DAS_spriteTimer]
	cmp		[DAS_spriteTimer],		DAS_timingWord
	jge		.change_sprite
	jmp		.display_sprite

.change_sprite:
	mov		[DAS_spriteTimer],		0
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
	call	DrawTextureRec

	add		rsp,28h
	ret


;;=  void ChangeAnimation(AnimatedSprite:&sprite, int:animation);
;;=  RCX = &sprite		RDX = animation
;;=  	Changes the current playing animation in the
;;=		pointed to AnimatedSprite to the animation input.
CAS_spritePtr		equ		rcx
CAS_animation		equ		rdx

CAS_spriteClip		equ		rcx+AnimatedSprite.curClip
CAS_spriteFrame		equ		rcx+AnimatedSprite.curFrame
CAS_spriteFrameTime	equ		rcx+AnimatedSprite.frameTime
CAS_spriteTimer		equ		rcx+AnimatedSprite.timer

CAS_animationMem	equ		r8
CAS_animationPtr	equ		rax
change_animated_sprite:
	sub 	rsp,	28h

.Init:
	mov		CAS_animationMem,		[animation_memory]
	imul	CAS_animation,			8
	add		CAS_animationMem,		CAS_animation
	mov		CAS_animationPtr,		[CAS_animationMem]
.check:
	cmp		CAS_animationPtr,		[CAS_spriteClip]
	je		.exit
.change:
	mov		[CAS_spriteClip],		CAS_animationPtr
	mov		[CAS_spriteFrame],		0
	mov		[CAS_spriteFrameTime],	16
	mov		[CAS_spriteTimer],		0
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