;;=  Windows
section '.data' readable writeable
;;=  Linux
;segment readable writeable
	;;=  Program information
	title				db		'Monochrome', 10, 0
	text_onscreen		db		'X', 10, 0
	home				dq		0
	home2				dq		0

	;;=  Memory heaps
	general_memory		dq		0
	player_memory		dq		0

	;;=  Game camera
	camera				Camera2D

	;;=  FileNames
	player_overworld_m_text		db		'data/sprites/characters/spr_player_overworld_m.png',0
	player_overworld_f_text		db		'data/sprites/characters/spr_player_overworld_f.png',0