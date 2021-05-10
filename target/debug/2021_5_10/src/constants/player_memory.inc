

struc PlayerData {
	.spriteTexture	Texture2D
	.spriteRect		Rectangle
}

virtual at 0
	PlayerData	PlayerData
	sizeof.PlayerData = $ - PlayerData
end virtual