#include <stdio.h>

extern void printone(void);

static void print_str(const char *s) {
    for (; *s; ++s) {
        // Colocar el puntero del carácter actual en t0
        asm volatile("mv t0, %0" :: "r"(s));
        printone();  // imprime un carácter
    }
}

int main(void) {
    print_str("Hola RISC-V!\n");
    return 0;
}
