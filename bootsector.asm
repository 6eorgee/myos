KERNEL_OFFSET equ 0x1000

[bits 16]
[org 0x7c00]

xor ax, ax
mov ds, ax
mov es, ax
mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit
jmp $

%include "diskutils.asm"
%include "gdt.asm"
%include "32bit.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; bx -> destination
    mov dh, 0x31          ; dh -> num sectors
    mov dl, [BOOT_DRIVE]  ; dl -> disk
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    call KERNEL_OFFSET ; give control to the kernel
    jmp $              ; loop in case kernel returns

BOOT_DRIVE db 0
times 510 - ($-$$) db 0
dw 0xaa55
