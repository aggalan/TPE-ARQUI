GLOBAL call_sys_write
GLOBAL call_sys_read
GLOBAL call_reg_state
GLOBAL call_time_clock
GLOBAL call_size_up
GLOBAL call_size_down
GLOBAL call_clear
GLOBAL call_font
GLOBAL call_cursor_on
GLOBAL call_cursor_off
GLOBAL call_sound

section .text

%macro call_handler 1
    push rbp
    mov rbp, rsp

    ;;faltan los demas registros
    mov rax, %1
    int 80h

    mov rsp, rbp
    pop rbp
    ret
%endmacro


call_sys_write:
    call_handler 1
call_sys_read:
    call_handler 2
call_time_clock:
    call_handler 3
call_reg_state:
    call_handler 4
call_size_up:
    call_handler 5
call_size_down:
    call_handler 6
call_clear:
    call_handler 7
call_font:
    call_handler 8
call_cursor_on:
    call_handler 9
call_cursor_off:
    call_handler 10
call_sound:
    call_handler 11
