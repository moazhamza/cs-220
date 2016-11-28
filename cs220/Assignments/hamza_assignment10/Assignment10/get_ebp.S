.intel_syntax noprefix

.text
.global get_ebp_asm

get_ebp_asm:
  mov eax, ebp
  ret

