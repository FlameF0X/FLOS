org 0x7C00
bits 16

start:
    jmp main

%include "print.inc"

main:
    ; Setup segments
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Load stage2 (kernel) from disk
    mov ah, 0x02
    mov al, 10         ; Number of sectors to read
    mov ch, 0         ; Cylinder 0
    mov dh, 0         ; Head 0
    mov cl, 2         ; Sector 2 (1-based)
    mov bx, 0x7E00    ; Load to 0x7E00
    int 0x13
    jc disk_error

    ; Jump to stage2
    jmp 0x7E00

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt

disk_error_msg db "Disk error!", 0

times 510-($-$$) db 0
dw 0xAA55