#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

int turno = 0;
const int ITERACIONES_P0 = 3;
const int ITERACIONES_P1 = 5;

void *proceso_0(void *arg) {
    for (int i = 0; i < ITERACIONES_P0; i++) {
        printf("P0: Quiero entrar a la (iteración %d)...\n", i);

        while (turno != 0) {
            // Espera continua
        }

        printf("P0: Entra a la RC\n");
        printf("P0: Trabajando a la RC\n");
        sleep(1);
        printf("P0: Saliendo de la RC\n\n");
        turno = 1;
    }

    printf("===================================\n");
    printf("P0: ¡TERMINÉ TODAS MIS ITERACIONES!\n");
    printf("===================================\n\n");

    return NULL;
}

void *proceso_1(void *arg) {
    bool visto = false;

    for (int i = 0; i < ITERACIONES_P1; i++) {
        printf("P1: Quiero entrar (iteración %d)...\n", i);

        while (turno != 1) {

            if (i >= ITERACIONES_P0) {
                if (!visto) {
                    printf("\n¡BLOQUEADO!\n");
                    printf("P0 terminó y ya no puedo entrar\n\n");
                    visto = true;
                }
            }
        }

        printf("P1: Entra a la RC\n");
        printf("P1: Trabajando en RC\n");
        sleep(1);
        printf("P1: Saliendo de región crítica\n\n");
        turno = 0;
    }

    printf("===================================\n");
    printf("P1: ¡TERMINÉ TODAS MIS ITERACIONES!\n");
    printf("===================================\n\n");

    return NULL;
}

int main() {
    pthread_t hilo0, hilo1;

    printf("INICIANDO HILOS\n");

    pthread_create(&hilo0, NULL, proceso_0, NULL);
    pthread_create(&hilo1, NULL, proceso_1, NULL);

    pthread_join(hilo0, NULL);
    pthread_join(hilo1, NULL);

    return 0;
}
