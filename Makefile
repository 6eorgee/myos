# $@ = target file
# $< = first dependency
# $^ = all dependencies

all: run

kernel.bin: kernel_entry.o kernel.o kbrd.o interrupt.o vga.o interrupts.o ports.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@

vga.o: vga.c
	gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@

ports.o: ports.c
	gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@

interrupts.o: interrupts.c
	gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@

kbrd.o: kbrd.c
	gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c $< -o $@

interrupt.o: interrupt.asm
	nasm $< -f elf -o $@

bootsector.bin: bootsector.asm
	nasm $< -f bin -o $@

os_image.img: bootsector.bin kernel.bin
	cat $^ > $@

run: os_image.img
	qemu-system-i386 -fda $<

clean:
	$(RM) *.bin *.o *.dis *.img