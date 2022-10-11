#include <stdio.h>
#include <math.h>

#define MAX 30
#define N 4
#define EPSILON 0.001

void calculaPorGaus(float matrizInicial[N][N], float matrizB[N], float vAproximacao[N]) {
	float resultados[MAX+1][N];
	int i = 0, j = 0, flag = 0;

	resultados[0][0] = vAproximacao[0];
	resultados[0][1] = vAproximacao[1];
	resultados[0][2] = vAproximacao[2];
	resultados[0][3] = vAproximacao[3];

	printf("Iteracao |      x1     |      x2     |      x3     |      x4     \n");
	printf("%8d | %011.6f | %011.6f | %011.6f | %011.6f\n", 0, resultados[0][0], resultados[0][1], resultados[0][2], resultados[0][3]);

	for (i = 1; i <= MAX; i++)
	{
		if (flag) {
			break;
		} 

		for (j = 0; j < N; j++)
		{
			resultados[i][j] = 1/matrizInicial[j][j] * (matrizB[j] - (matrizInicial[j][0] * resultados[i-1][0] + matrizInicial[j][1] * resultados[i-1][1] + matrizInicial[j][2] * resultados[i-1][2] + matrizInicial[j][3] * resultados[i-1][3]));
		}
		printf("%8d | %011.6f | %011.3f | %011.3f | %011.3f\n", i, resultados[i][0], resultados[i][1], resultados[i][2], resultados[i][3]);
		if (fabs(resultados[i][0] - resultados[i-1][0]) < EPSILON && fabs(resultados[i][1] - resultados[i-1][1]) < EPSILON && fabs(resultados[i][2] - resultados[i-1][2]) < EPSILON && fabs(resultados[i][3] - resultados[i-1][3]) < EPSILON)
		{
			flag = 1;
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
	calculaPorGaus(matrizInicial, matrizB, vAproximacao);
	printf("-----------------------\\\\-------------------------\n");

	return 0;
}
