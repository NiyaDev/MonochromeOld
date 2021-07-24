;*/
;* @Date:		7/24/21
;* @Author:		Szyfr
;*/



;;+	Types of files
;;+		- Sprites
;;+		- Animations
;;+		- Map files
;;+		- 

;;=  Loads all files
;;=		Input:		N/A
;;=		Output:		N/A
load_files:
	sub		rsp,	28h



.exit:
	add		rsp,	28h
	ret