#include <stdio.h>
#include <string.h>

typedef struct {
	char nome[64];
	char telefone[15];
	char curso[64];
	float nota1, nota2;
} Aluno;

void organiza (char frases[]) {

}

int main () {

	FILE *arquivo;

	arquivo = fopen("DadosEntrada.csv", "r");

	Aluno aluno;

	if (arquivo == NULL) {
		printf("Arquivo nao encontrado!");
	}

	int debug = 0;
	char linha[64];
	char corte[5][16];

	while (fgets(linha, sizeof(linha), arquivo) != NULL) {
		strtok(linha, "\n");
		char *save = linha;
		for (int i = 0; i < 5; i++) {
			strcpy(corte[i], strtok_r(save, ",", &save));
			printf ("[%s]", corte[i]);
		}
	}

	printf ("\nFUNCIONA!\n");

	return 0;
}