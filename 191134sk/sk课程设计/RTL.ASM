.MODEL	SMALL

.8086
.stack
.code
;EXTRN _main
extern _main:near
.startup
        cli		       ; interrupt disable
	call  near ptr _main
endless:
	jmp   endless
.data
public	__acrtused		; trick to force in startup

__acrtused = 9876h	; funny value not easily matched ; ; in SYMDEB

END