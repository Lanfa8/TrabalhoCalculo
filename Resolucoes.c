#include <stdio.h>
#include <math.h>

#define MAX 30
#define N 4
#define EPSILON 0.001

float calculaSomatoriaGaussJacobi(float matrizInicial[N][N], float resultados[MAX + 1][N], int i, int j) {
	int k = 0;
	float soma = 0;

	for (int k = 0; k < N; k++)
	{
		if (j==k) {
			continue;
		}
		soma += matrizInicial[j][k] * resultados[i-1][k];
	}
	
	return soma;
}

float calculaSomatoriaGaussSeidel(float matrizInicial[N][N], float resultados[MAX + 1][N], int i, int j) {
	int k = 0;
	float soma = 0;
	int indexToUse = i - 1;

	for (int k = 0; k < N; k++)
	{
		indexToUse = i - 1;
		if (j==k) {
			continue;
		}

		if (k < j) {
			indexToUse = i;
		}

		soma += matrizInicial[j][k] * resultados[indexToUse][k];
	}

	return soma;
}

int possuiAproximacaoNecessaria(float resultados[MAX + 1][N], int i) {
	int j = 0;
	for (j = 0; j < N; j++)
	{
		if (fabs(resultados[i][j] - resultados[i-1][j]) > EPSILON) {
			return 0;
		}
	}
	return 1;
}

void calculaPorGaussJacobi(float matrizInicial[N][N], float matrizB[N], float vAproximacao[N]) {
	float resultados[MAX+1][N];
	int i = 0, j = 0;

	resultados[0][0] = vAproximacao[0];
	resultados[0][1] = vAproximacao[1];
	resultados[0][2] = vAproximacao[2];
	resultados[0][3] = vAproximacao[3];

	printf("Metodo de Gauss-Jacobi\n");

	printf("Iteracao |      x1     |      x2     |      x3     |      x4     \n");
	printf("%8d | %011.6f | %011.6f | %011.6f | %011.6f\n", 0, resultados[0][0], resultados[0][1], resultados[0][2], resultados[0][3]);

	for (i = 1; i <= MAX; i++)
	{
		for (j = 0; j < N; j++)
		{
			resultados[i][j] = 1/matrizInicial[j][j] * (matrizB[j] - (calculaSomatoriaGaussJacobi(matrizInicial, resultados, i, j)));
		}
		printf("%8d | %011.6f | %011.3f | %011.3f | %011.3f\n", i, resultados[i][0], resultados[i][1], resultados[i][2], resultados[i][3]);
		
		if (possuiAproximacaoNecessaria(resultados, i)) {
			break;
		}
	}
}

void calculaPorGaussSeidel(float matrizInicial[N][N], float matrizB[N], float vAproximacao[N]) {
	float resultados[MAX+1][N];
	int i = 0, j = 0;

	resultados[0][0] = vAproximacao[0];
	resultados[0][1] = vAproximacao[1];
	resultados[0][2] = vAproximacao[2];
	resultados[0][3] = vAproximacao[3];

	printf("Metodo de Gauss-Seidel\n");

	printf("Iteracao |      x1     |      x2     |      x3     |      x4     \n");
	printf("%8d | %011.6f | %011.6f | %011.6f | %011.6f\n", 0, resultados[0][0], resultados[0][1], resultados[0][2], resultados[0][3]);

	for (int i = 1; i <= MAX; i++)
	{
		for (j = 0; j < N; j++)
		{
			resultados[i][j] = 1/matrizInicial[j][j] * (matrizB[j] - (calculaSomatoriaGaussSeidel(matrizInicial, resultados, i, j)));
		}

		printf("%8d | %011.6f | %011.3f | %011.3f | %011.3f\n", i, resultados[i][0], resultados[i][1], resultados[i][2], resultados[i][3]);
		
		if (possuiAproximacaoNecessaria(resultados, i)) {
			break;
		}
	}
}

int main() {

	float matrizInicial[N][N] = {
		{9, 1, -2, 2},
		{1, 15, -3, 2},
		{1, -2, 8, 3},
		{2, 2, 1, 12}
	};

	float matrizB[N] = {10, 5, 14.6, 19.4};
	float vAproximacao[N] = {1,1,1,1};
	
	printf("QUESTAO A)\n");
	calculaPorGaussJacobi(matrizInicial, matrizB, vAproximacao);
	
	printf("\n\n");
	calculaPorGaussSeidel(matrizInicial, matrizB, vAproximacao);
	printf("-----------------------\\\\----------------\\\\----------------------------------\n");

	return 0;
}
