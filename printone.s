.section .text
.globl printone

printone:
addi a7, x0, 64      # syscall: write (RISC-V)
addi a0, x0, 1       # fd = 1 (stdout)
mv   a1, t0          # buffer = *(t0) (puntero a 1 char)
addi a2, x0, 1       # count = 1
ecall
ret                  # volver a C