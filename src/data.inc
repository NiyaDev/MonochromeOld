;;=  Windows
section '.data' readable writeable
;;=  Linux
;segment readable writeable
	;;=  Program information
	title				db		'Monochrome', 10, 0
	text_onscreen		db		'X', 10, 0

	;;=  Memory heaps
	;;TODO: add animation memory heap
	general_memory		dq		0
	player_memory		dq		0

	;;=  FileNames
	;;TODO: create a file manifest
	icon_text					db		'data/Icon.png',0
	player_overworld_m_text		db		'data/sprites/characters/spr_player_overworld_m.png',0
	player_overworld_f_text		db		'data/sprites/characters/spr_player_overworld_f.png',0

	;;=  Defines
	;;TODO: move these to a file
	idle_down	dd	CONST_sprite_0,CONST_sprite_0,CONST_sprite_0,CONST_sprite_0,CONST_sprite_0,CONST_sprite_0,CONST_sprite_0,CONST_sprite_0
	idle_up		dd	CONST_sprite_3,CONST_sprite_3,CONST_sprite_3,CONST_sprite_3,CONST_sprite_3,CONST_sprite_3,CONST_sprite_3,CONST_sprite_3
	idle_left	dd	CONST_sprite_6,CONST_sprite_6,CONST_sprite_6,CONST_sprite_6,CONST_sprite_6,CONST_sprite_6,CONST_sprite_6,CONST_sprite_6
	idle_right	dd	CONST_sprite_8,CONST_sprite_8,CONST_sprite_8,CONST_sprite_8,CONST_sprite_8,CONST_sprite_8,CONST_sprite_8,CONST_sprite_8
	walk_down	dd	CONST_sprite_0,CONST_sprite_1,CONST_sprite_0,CONST_sprite_2,CONST_sprite_0,CONST_sprite_1,CONST_sprite_0,CONST_sprite_2
	walk_up		dd	CONST_sprite_3,CONST_sprite_4,CONST_sprite_3,CONST_sprite_5,CONST_sprite_3,CONST_sprite_4,CONST_sprite_3,CONST_sprite_5
	walk_left	dd	CONST_sprite_6,CONST_sprite_7,CONST_sprite_6,CONST_sprite_7,CONST_sprite_6,CONST_sprite_7,CONST_sprite_6,CONST_sprite_7
	walk_right	dd	CONST_sprite_8,CONST_sprite_9,CONST_sprite_8,CONST_sprite_9,CONST_sprite_8,CONST_sprite_9,CONST_sprite_8,CONST_sprite_9

section '.rsrc' resource data readable
	directory RT_ICON, icons, RT_GROUP_ICON, group_icons
	resource icons, 1, LANG_NEUTRAL, icon_data
	resource group_icons, 5, LANG_NEUTRAL, main_icon
	icon main_icon, icon_data, 'data/icon.ico'