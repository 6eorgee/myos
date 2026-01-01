;============================ print_ax ========================================
print_ax:
    pusha
    mov cx, 4
    mov dx, ax

loop:
    dec cx
    mov ax, dx
    push cx
    shl cx, 2
    shr ax, cl
    pop cx
    and ax, 0x000f
    cmp ax, 0x0009
    jle lessoreq9
    add ax, 0x0037
    jmp print
lessoreq9:
    add ax, 0x0030

print:
    mov ah, 0xe
    int 10h

    cmp cx, 0
    jne loop
    popa
    ret
;========================== end print_ax ======================================
