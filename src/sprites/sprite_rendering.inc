;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


;;=  Draws the current frame in the pointed to AnimatedSprite at the input position
;;=  	Input:		RCX = &sprite
;;=					RDX = position
;;=		Output:		N/A
spritePtr			equ		rcx		;Input
position			equ		rdx		;Input

frameIndex			equ		rax
frameIndexHalf		equ		eax
frameIndexLow		equ		al
clipPtr				equ		rbx
rectanglePtr		equ		rdx
generalPtr			equ		r8
currentSpritePtr	equ		r9
timer				equ		r10
timerWord			equ		r10w
timerByte			equ		r10b

aniTexture			equ		r9+AnimatedSprite.texture
aniRectangle		equ		r9+AnimatedSprite.rect
aniCurClip			equ		r9+AnimatedSprite.curClip
aniCurFrame			equ		r9+AnimatedSprite.curFrame
aniFrameTime		equ		r9+AnimatedSprite.frameTime
aniTimer			equ		r9+AnimatedSprite.timer

clipPtrOffset		equ		rbx+4

endFrame			equ		0xffffffff
draw_animated_sprite:
	sub		rsp,	28h

.init:
	mov		generalPtr,				[general_memory]
	mov		currentSpritePtr,		spritePtr
	xor		timer,					timer

	mov		timerByte,				[aniFrameTime]

	inc		[aniTimer]
	cmp		[aniTimer],				timerWord
	jl		.display_sprite

.change_sprite:
	mov		[aniTimer],				0
	xor		frameIndex,				frameIndex

	mov		frameIndexLow,			[aniCurFrame]
	imul	frameIndex,				4
	mov		clipPtr,				[aniCurClip]
	add		clipPtr,				frameIndex
	mov		frameIndexHalf,			[clipPtrOffset]
	cmp		frameIndexHalf,			endFrame
	je		.recall
.increase:
	inc		[aniCurFrame]
	jmp		.update_rect
.recall:
	mov		[aniCurFrame],			0
	jmp		.update_rect

.update_rect:
	mov		spritePtr,				currentSpritePtr
	call	update_rectangle

.display_sprite:
	lea		spritePtr,				[aniTexture]
	mov		r8,						rdx
	lea		rectanglePtr,			[aniRectangle]
	mov		r9d,					WHITE
	call	DrawTextureRec

	add		rsp,28h
	ret


;;=  Changes the current playing animation in the pointed to AnimatedSprite to the animation input.
;;=  	Input:		RCX = &sprite
;;=					RDX = animationNum
;;=		Output:		N/A
spritePtr			equ		rcx			;input
animationNum		equ		rdx			;input

newAnimationPtr		equ		rax
animationPtr		equ		r8

aniCurClip			equ		rcx+AnimatedSprite.curClip
aniCurFrame			equ		rcx+AnimatedSprite.curFrame
aniFrameTime		equ		rcx+AnimatedSprite.frameTime
aniTimer			equ		rcx+AnimatedSprite.timer
change_animated_sprite:
	sub 	rsp,	28h

.Init:
	mov		animationPtr,			[animation_memory]
	imul	animationNum,			8
	add		animationPtr,			animationNum
	mov		newAnimationPtr,		[animationPtr]
.check:
	cmp		newAnimationPtr,		[aniCurClip]
	je		.exit
.change:
	mov		[aniCurClip],			newAnimationPtr
	mov		[aniCurFrame],			0
	mov		[aniFrameTime],			8
	mov		[aniTimer],				0
	call	update_rectangle

.exit:
	add		rsp,28h
	ret


;;=  Updates the rectangle to the 
;;=  	Input:		RCX = &sprite
;;=		Output:		N/A
spritePtr			equ		rcx		;input

frameTotal			equ		rax
frameX				equ		eax
currentFrame		equ		al
animationPtr		equ		rbx

aniRectangleX		equ		rcx+AnimatedSprite.rect.x
aniCurClip			equ		rcx+AnimatedSprite.curClip
aniCurFrame			equ		rcx+AnimatedSprite.curFrame
update_rectangle:
	sub		rsp,	28h

	xor		frameTotal,				frameTotal

.update:
	mov		currentFrame,			[aniCurFrame]
	imul	frameX,					4
	mov		animationPtr,			[aniCurClip]
	add		animationPtr,			frameTotal
	mov		frameX,					[animationPtr]
	mov		[aniRectangleX],		frameX

.exit:
	add		rsp,	28h
	ret