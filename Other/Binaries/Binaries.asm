%macro IncBin 2
    SECTION .rodata
    GLOBAL %1
%1:
    incbin %2
    db 0
    %1_size: dq %1_size - %1
%endmacro

IncBin SuccessAscii, "./Other/Binaries/successAscii.txt"
IncBin Licence, "./Other/Binaries/MIT-LICENCE.txt"