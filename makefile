
make:
	yasm -f elf64 -o assign_0.o assign_0.asm
	gcc -static -o assign_0 assign_0.o
run:
	./assign_0
