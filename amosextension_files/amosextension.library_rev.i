VERSION		EQU	1
REVISION	EQU	4

DATE	MACRO
		dc.b '26.12.2017'
		ENDM

VERS	MACRO
		dc.b 'amosextension.library 1.4'
		ENDM

VSTRING	MACRO
		dc.b 'amosextension.library 1.4 (26.12.2017)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: amosextension.library 1.4 (26.12.2017)',0
		ENDM
