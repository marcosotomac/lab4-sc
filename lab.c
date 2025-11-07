//Proceso en C que muestre siempre el alfabeto, este proceso debe ser capaz de detectar una interrupción programada cada 5 segundos que dure dos segundos muestre números desde 0 a 9, gestione la interrupción en Linux x86 (4 ptos)

//Crear un temporizador kernel que simule una interrupción periódica. Listo
//Generar la temporización de la interrupción (2 segundos). Listo
//Generar un flag que indique qué imprimir (alfabeto o números).
//Generar el hilo de kernel que imprime continuamente.
//Describa cómo se programan los timers en el kernel.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

volatile sig_atomic_t interrupt_flag = 0;
void handle_interrupt(int sig) {
    interrupt_flag = 1;
}

void setup_timer() {
    struct itimerval timer;
    timer.it_value.tv_sec = 5; // primera interrupción en 5 segundos
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 5; // interrupciones subsiguientes cada 5 segundos
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handle_interrupt;
    sigaction(SIGALRM, &sa, NULL);

    setup_timer();

    while (1) {
        if (interrupt_flag) {
            // Mostrar números del 0 al 9 durante 2 segundos
            for (int i = 0; i < 10; i++) {
                printf("%d\n", i);
                fflush(stdout);
                usleep(200000); // 200 ms entre números
            }
            interrupt_flag = 0; // Resetear la bandera de interrupción
        } else {
            // Mostrar el alfabeto
            for (char c = 'A'; c <= 'Z'; c++) {
                printf("%c\n", c);
                fflush(stdout);
                usleep(200000); // 200 ms entre letras
            }
        }
    }

    return 0;
}