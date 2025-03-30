; Command buffer and pointers
cmd times 2 db 0
cmd_args dw 0

; Error/status messages
invalid_cmd_msg db "Invalid command", 0xD, 0xA, 0
file_created_msg db "File created", 0xD, 0xA, 0
file_removed_msg db "File removed", 0xD, 0xA, 0
no_space_msg db "No space for new file", 0xD, 0xA, 0
not_found_msg db "File not found", 0xD, 0xA, 0

parse_cmd:
    ; Skip leading spaces and get command
    mov si, input_buffer
    mov di, cmd
    ; Clear previous command
    mov word [cmd], 0
    ; Skip spaces
.skip_space:
    lodsb
    cmp al, ' '
    je .skip_space
    dec si  ; Back to first non-space char
    
    ; Copy first 2 chars of command
    mov cx, 2
.copy_command:
    cmp byte [si], 0
    je .done
    lodsb
    stosb
    loop .copy_command

    ; Find arguments after command
.find_args:
    cmp byte [si], ' '
    jne .no_args
    inc si  ; Skip space
    mov [cmd_args], si
    ret
.no_args:
    mov word [cmd_args], 0
.done:
    ret

process_command:
    call parse_cmd
    
    ; Commands use first 2 chars
    cmp word [cmd], 'ma'  ; make
    je .make
    cmp word [cmd], 'rm'  ; remove
    je .remove
    cmp word [cmd], 'mv'  ; rename
    je .rename
    cmp word [cmd], 'mk'  ; mkfile
    je .mkfile
    
    mov si, invalid_cmd_msg
    call print_string
    ret

.make:
    call find_free_entry
    test di, di
    jz .no_space
    mov si, [cmd_args]
    mov cx, FILENAME_LEN
    rep movsb
    mov byte [di], 1  ; Fixed line
    mov si, file_created_msg
    call print_string
    ret

.remove:
    mov si, [cmd_args]
    call find_entry
    test di, di
    jz .not_found
    mov byte [di + FileEntry.used], 0
    mov si, file_removed_msg
    call print_string
    ret

.rename:
    ; TODO: Implement rename functionality
    mov si, rename_not_implemented
    call print_string
    ret

.mkfile:
    jmp .make  ; Same as make for now

.no_space:
    mov si, no_space_msg
    call print_string
    ret

.not_found:
    mov si, not_found_msg
    call print_string
    ret

rename_not_implemented db "Rename not implemented yet", 0xD, 0xA, 0