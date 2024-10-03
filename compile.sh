nasm "./Sector 1/bootloader.asm" -f bin -o ./tmps/bootloader.bin
nasm "./Sector 2+/ExtendedProgram.asm" -f elf64 -o ./tmps/ExtendedProgram.o
nasm "./Other/Binaries/Binaries.asm" -f elf64 -o ./tmps/Binarys.o

x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "./Other/Kernel/Kernel.cpp" -o "./tmps/Kernel.o"
x86_64-elf-ld -T"./link.ld"

cat ./tmps/bootloader.bin ./tmps/kernel.bin > SuperOS-v1.3-2024.flp

cp ./SuperOS-v1.3-2024.flp /media/sf_SharedFolder