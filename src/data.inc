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
	animation_memory	dq		0

	;;=  FileNames
	;;TODO: create a file manifest
	icon_text					db		'data/Icon.png',0
	animations_text				db		'data/sprites/animations.bin',0
	player_overworld_m_text		db		'data/sprites/characters/spr_player_overworld_m.png',0
	player_overworld_f_text		db		'data/sprites/characters/spr_player_overworld_f.png',0
	map_pallet					db		'data/maps/Temp.png',0
	font_text					db		'data/fonts/default_1.ttf',0
;	font_text					db		'data/fonts/alagard.png',0
	pause_menu_bg				db		'data/sprites/UI/pause_menu.png',0
	cursor_spr					db		'data/sprites/UI/cursor.png',0

	temp_text					db		'WIKI',10,'MONs',10,'ITEMS',10,'PLAYER',10,'SAVE',10,'OPTIONS',10,'QUIT',0


;;=  Windows
;section '.rsrc' resource data readable
;;=  Linux
;segment readable
;	directory RT_ICON, icons, RT_GROUP_ICON, group_icons
;	resource icons, 1, LANG_NEUTRAL, icon_data
;	resource group_icons, 5, LANG_NEUTRAL, main_icon
;	icon main_icon, icon_data, 'data/icon.ico'