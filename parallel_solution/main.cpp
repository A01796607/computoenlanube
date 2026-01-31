#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000

int main() {

	int A[N], B[N], C[N];

	// Inicializar semilla para números aleatorios
	srand(time(NULL));

	// Llenar arreglos A y B con valores aleatorios
	for(int i = 0; i < N; i++) {
		A[i] = rand() % 100;   // valores entre 0 y 99
		B[i] = rand() % 100;
	}

	/*
	 * #pragma omp parallel for
	 *
	 * Esta directiva de OpenMP:
	 *
	 * 1 - Crea automáticamente un equipo de hilos (threads).
	 * 2 - Divide las iteraciones del ciclo for entre los hilos disponibles.
	 * 3 - Cada hilo ejecuta una parte distinta del ciclo.
	 * 4 - Al finalizar todas las iteraciones, los hilos se sincronizan implicitamente.
	 *
	 * En este caso:
	 * - Cada iteración calcula C[i] = A[i] + B[i]
	 * - No hay condición de carrera (race condition),
	 *   porque cada hilo escribe en una posición distinta del arreglo C.
	 *
	 * OpenMP maneja automáticamente:
	 * - Creación y destrucción de hilos
	 * - Distribución de carga
	 * - Sincronización final
	*/
	#pragma omp parallel for
	for(int i = 0; i < N; i++) {
		C[i] = A[i] + B[i];
	}

	// Imprimir los elementos para comprobar
	printf("Resultado de la suma de arreglos:\n");
	for(int i = 0; i < 100; i++) {
		printf("A[%d]=%d + B[%d]=%d = C[%d]=%d\n",
		       i, A[i], i, B[i], i, C[i]);
	}

	return 0;
}