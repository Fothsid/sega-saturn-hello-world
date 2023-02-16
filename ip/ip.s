.open "ip/IP_BASE.BIN", BUILD_DIR + "/IP.BIN", 0

EntryPoint equ 0x06004000

.db "SEGA SEGASATURN "
.db "Homebrew, eh?   "
.db "999999999 V1.000"
.db "20221017CD-1/1  "
.db "JEU             "
.db "J               "
.db "HELLO WORLD     "
.db "                "
.db "                "
.db "                "
.db "                "
.db "                "
.db "                "
.dd 0x00000000,0x00000000,0x00000000,0x00000000
.dd 0x00001800,0x00000000,0x00000000,0x00000000
.dd EntryPoint,0x00000000,0x00000000,0x00000000

.close