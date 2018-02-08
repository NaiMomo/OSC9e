; NASM 64
; Compile using: nasm -f elf64 swap.s
section .text
global acquire

; Acquire la ressource
acquire:
  ; Place la valeur de lock -> rdx
  mov ecx, 1
.while0:
  ; Echange lock <-> true
  lock xchg byte[rdi], cl
  ; set ZF=0
  test cl, cl
  ; boucle si ZF=1
  jne .while0
  ret
