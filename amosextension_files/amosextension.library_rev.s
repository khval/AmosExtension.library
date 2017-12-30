VERSION = 1
REVISION = 5

.macro DATE
.ascii "30.12.2017"
.endm

.macro VERS
.ascii "amosextension.library 1.5"
.endm

.macro VSTRING
.ascii "amosextension.library 1.5 (30.12.2017)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: amosextension.library 1.5 (30.12.2017)"
.byte 0
.endm
