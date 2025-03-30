FILE_ENTRIES equ 16
FILENAME_LEN equ 16

struc FileEntry
    .name: resb FILENAME_LEN
    .used: resb 1
endstruc

file_table times FILE_ENTRIES * FileEntry_size db 0

init_file_table:
    mov di, file_table
    mov cx, FILE_ENTRIES * FileEntry_size
    xor al, al
    rep stosb
    ret

find_free_entry:
    mov cx, FILE_ENTRIES
    mov di, file_table
.loop:
    cmp byte [di + FileEntry.used], 0
    je .found
    add di, FileEntry_size
    loop .loop
    mov di, 0
.found:
    ret

find_entry:
    ; Input: SI = filename
    mov cx, FILE_ENTRIES
    mov di, file_table
.loop:
    push cx
    push di
    push si
    mov cx, FILENAME_LEN
    repe cmpsb
    pop si
    pop di
    pop cx
    je .found
    add di, FileEntry_size
    loop .loop
    mov di, 0
.found:
    ret