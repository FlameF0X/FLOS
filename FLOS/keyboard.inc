read_input:
    xor cx, cx

    cmp cx, 63
    jae .done

.loop:
    mov ah, 0
    int 0x16

    cmp al, 0x0D    ; Enter
    je .done

    cmp al, 0x08    ; Backspace
    je .backspace

    mov ah, 0x0E
    int 0x10

    stosb
    inc cx
    jmp .loop

.backspace:
    cmp cx, 0
    je .loop
    dec di
    dec cx
    mov ah, 0x0E
    mov al, 0x08
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 0x08
    int 0x10
    jmp .loop

.done:
    mov al, 0
    stosb
    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A
    int 0x10
    ret