    .section .text
    .globl printone

printone:
    addi a7, x0, 2      # syscall write
    addi a0, x0, 1       # fd = stdout
    mv   a1, t0          # buffer = t0
    addi a2, x0, 1       # count = 1
    ecall
    ret
