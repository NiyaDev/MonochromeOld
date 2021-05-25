;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/


struc ControlData {
	.direction		dw		0
	.action			dw		0
}
struc KeyBindings {
	.up				db		0
	.down			db		0
	.right			db		0
	.left			db		0
	.confirm		db		0
	.cancel			db		0
	.start			db		0
	.select			db		0
}


struc PlayerData {
	.entity			Entity			;64-bytes
	.camera			Camera2D		;34-bytes
	.ctrData		ControlData		; 4-bytes
	.ctrBindings	KeyBindings		; 8-bytes
}	;110-bytes

virtual at 0
	PlayerData	PlayerData
	sizeof.PlayerData = $ - PlayerData
end virtual