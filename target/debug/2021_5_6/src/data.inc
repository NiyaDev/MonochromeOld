
section '.data' readable writeable
	title				db		'Monochrome', 10, 0
	text_onscreen		db		'X', 10, 0
	example_variable	dq		0
	home				dq		0

	two					dd		2

	general_memory		dq		0

	tile_memory			dq		0
	tile_sprite			dq		0
	tile_texture		dq		0
	tile_dim			dq		16

	text_position_x		dq		10
	text_position_y		dq		30

	camera				Camera2D