#ifndef _SYSCALLS_H
#define _SYSCALLS_H

void sys_write(const char * buffer, int len, int fd);
void sys_read(const char * buff, int len, int fds);
void shift_active();
void shift_dropped();

#endif
