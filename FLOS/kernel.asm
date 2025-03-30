org 0x7E00
bits 16

%include "print.inc"
%include "keyboard.inc"

start:
    ; Setup segments
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Init file table
    call init_file_table

    ; Welcome message
    mov si, welcome_msg
    call print_string

main_loop:
    ; Display prompt
    mov si, prompt
    call print_string

    ; Read input
    mov di, input_buffer
    call read_input

    ; Process command
    call process_command

    jmp main_loop

%include "file.inc"
%include "command.inc"

welcome_msg db "FLOS - Minimal OS", 0xD, 0xA, 0
prompt db "FLOS> ", 0
input_buffer times 64 db 0