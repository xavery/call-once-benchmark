section .text
extern actually_do_stuff
global selfmod_bench

align 4096
selfmod_bench:
  mov al, 90h
  mov rdi, selfmod_bench
  mov ecx, (.do_stuff - selfmod_bench)
  rep stosb
.do_stuff:
  call actually_do_stuff
  ret
