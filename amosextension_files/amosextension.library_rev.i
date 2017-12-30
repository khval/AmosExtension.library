VERSION		EQU	1
REVISION	EQU	5

DATE	MACRO
		dc.b '30.12.2017'
		ENDM

VERS	MACRO
		dc.b 'amosextension.library 1.5'
		ENDM

VSTRING	MACRO
		dc.b 'amosextension.library 1.5 (30.12.2017)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: amosextension.library 1.5 (30.12.2017)',0
		ENDM
