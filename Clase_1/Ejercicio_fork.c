// Librería de entrada y salida estándar (printf, scanf, etc.)
#include <stdio.h>

// Proporciona acceso a llamadas al sistema POSIX (fork, getpid, sleep, etc.)
#include <unistd.h>

// Define tipos de datos utilizados por el sistema (pid_t, size_t, etc.)
#include <sys/types.h>

int main() {
    pid_t pid;
    int variable1 = 20;
    int variable2 = 10;
    int resultado = 0;

    printf("\n======== DEMOSTRACIÓN DE fork() ========\n");

    printf("Ingrese el primer número: ");
    scanf("%d", &variable1);

    printf("Ingrese el segundo número: ");
    scanf("%d", &variable2);

    // Crear proceso hijo
    pid = fork();

    if (pid < 0) {
        // Error al crear el proceso
        printf("Error: No se pudo crear el proceso hijo\n");
        return 1;

    } else if (pid == 0) {
        // Código del HIJO
        printf("\n=== PROCESO HIJO ===\n");
        printf("Mi PID: %d\n", getpid());
        printf("PID de mi padre: %d\n", getppid());

        // Suma
        resultado = variable1 + variable2;
        printf("Resultado de la Suma: %d\n", resultado);
        printf("HIJO: Terminando...\n\n");

    } else {
        // Código del PADRE
        sleep(1);

        printf("=== PROCESO PADRE ===\n");
        printf("Mi PID: %d\n", getpid());
        printf("PID de mi hijo: %d\n", pid);

        //Resta
        resultado = variable1 - variable2;
        printf("Resultado de la Suma: %d\n", resultado);
        printf("PADRE: Terminando...\n\n");
    }

    return 0;
}