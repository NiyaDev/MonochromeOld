;*/
;* @Date:		5/8/21
;* @Author:		Szyfr
;*/



;;=  Structures
struc PlayerData {
	.entity			Entity			;64-bytes
	.camera			Camera2D		;34-bytes
	.ctrData		ControlData		;24-bytes
	.keyBindings	KeyBindings		;16-bytes
}	;138-bytes
struc ControlData {
	.input			dq		0
	.tap			dq		0
	.menu			db		0
	.menuTimer		db		0
	.subStatus		dw		0
	.cursorLoc		dd		0
}	;24-bytes
;;TODO: Remove once settings is done
struc KeyBindings {
	.down			dw		0
	.up				dw		0
	.left			dw		0
	.right			dw		0
	.confirm		dw		0
	.cancel			dw		0
	.start			dw		0
	.select			dw		0
}	;16-bytes

;;=  Macros
virtual at 0
	PlayerData	PlayerData
	sizeof.PlayerData = $ - PlayerData
end virtual
