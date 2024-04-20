#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nome[16];
	char telefone[16];
	char curso[16];
	float nota1, nota2;
} Aluno;

//Função para organizar as informações de cada linha para uma struct chamada 'Aluno'.
Aluno aluno_organiza (char frases[][16]) {
	Aluno aluno;

	strcpy (aluno.nome, frases[0]);
	strcpy (aluno.telefone, frases[1]);
	strcpy (aluno.curso, frases[2]);

	//'strtof()' converte strings em valores tipo float.
	aluno.nota1 = strtof(frases[3], NULL);
	aluno.nota2 = strtof(frases[4], NULL);
	
	return aluno;
}

int main () {

	FILE *arquivo;
	arquivo = fopen("DadosEntrada.csv", "r");

	if (arquivo == NULL) {
		printf("Arquivo nao encontrado.");
		exit(1);
	}

	char linha[64];
	char corte[5][16];

	//Este loop é temporario, ele primeiro ler a primeira linha do arquivo, e enquanto ela não for nula ira continuar repetindo.
	while (fgets(linha, sizeof(linha), arquivo) != NULL) { //PARA FAZER! TRANSFORMAR ESTE LOOP INTEIRO EM UMA FUNÇÃO!
		strtok(linha, "\n"); //remove o fim da linha.

		char *memoria = linha;
		for (int i = 0; i < 5; i++) {
			//'strok_r()' usa um ponteiro da linha e quando chega em uma ',' retorna as informações anterior a ela.
			strcpy(corte[i], strtok_r(memoria, ",", &memoria)); 
		}

		Aluno aluno = aluno_organiza (corte);
		printf ("[Aluno: %s | Nota: %.2f | Nota2: %.2f]\n", aluno.nome, aluno.nota1, aluno.nota2);
	}

	fclose (arquivo);

	return 0;
}