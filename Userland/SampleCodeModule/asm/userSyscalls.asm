GLOBAL call_sys_write
GLOBAL call_sys_read
GLOBAL call_reg_state
GLOBAL call_time_clock
GLOBAL call_change_size
GLOBAL call_clear

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
call_change_size:
    call_handler 5
call_clear:
    call_handler 6
