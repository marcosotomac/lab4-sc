/*
.section .text
.globl printone

printone:
addi a7, x0, 64      # syscall: write (RISC-V)
addi a0, x0, 1       # fd = 1 (stdout)
mv   a1, t0          # buffer = *(t0) (puntero a 1 char)
addi a2, x0, 1       # count = 1
ecall
ret                  # volver a C
`*/

// Declaramos la función ensamblada (no recibe args; usa t0 como canal)
extern void printone(void);

static void print_str(const char *s) {
    for (; *s; ++s) {
        // Colocamos el puntero al char actual en el registro t0
        register const char *p asm("t0") = s;
        (void)p;  // evita warning "unused variable"
        printone();  // imprime exactamente 1 carácter
    }
}

int main(void) {
    print_str("Hola RISC-V!\n");
    return 0;
}