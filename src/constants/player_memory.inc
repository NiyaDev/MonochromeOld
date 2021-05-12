struc ControlData {
	.direction		dw		0
	.action			dw		0
}


struc PlayerData {
	.spriteTexture	Texture2D
	.spriteRect		Rectangle
	.camera			Camera2D
	.control		ControlData
}

virtual at 0
	PlayerData	PlayerData
	sizeof.PlayerData = $ - PlayerData
end virtual