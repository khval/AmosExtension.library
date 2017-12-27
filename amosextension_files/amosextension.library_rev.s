VERSION = 1
REVISION = 4

.macro DATE
.ascii "26.12.2017"
.endm

.macro VERS
.ascii "amosextension.library 1.4"
.endm

.macro VSTRING
.ascii "amosextension.library 1.4 (26.12.2017)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: amosextension.library 1.4 (26.12.2017)"
.byte 0
.endm
