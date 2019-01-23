# Author: Frédéric Hamel
# Filename: os_getcwd.s
#
# Exemple d'implémentation de `wrapper`
# sur des appel système.
#
# Compile with:
#   > as os_getcwd.asm -o os_getcwd.o

.equ CWD_SIZE, 4096

.text

.global sys_getcwd
# size_t sys_getenv(char *buf, size_t size);
sys_getcwd:
  mov $79, %rax
  syscall
  ret

.global sys_fork
# pid_t sys_fork();
sys_fork:
  mov $57, %rax
  syscall
  ret

.global _getcwd
# char *_getenv(); //utilise un buffer interne.
_getcwd:
  mov $79, %rax
  leaq ___cwd_buf(%rip), %rdi
  mov $CWD_SIZE, %rsi
  syscall
  leaq ___cwd_buf(%rip), %rax
  ret

.data
___cwd_buf:
.fill CWD_SIZE, 0

