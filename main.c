#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MIN 32
#define TAMANHO_MAX 64

typedef struct {
	char nome[TAMANHO_MIN];
	char telefone[TAMANHO_MIN];
	char curso[TAMANHO_MIN];
	float nota1, nota2;
} Aluno;

//Função para organizar as informações de cada linha para uma struct chamada 'Aluno'.
Aluno aluno_organiza (char frases[][TAMANHO_MIN]) {
	Aluno aluno;
	strcpy (aluno.nome, frases[0]);
	strcpy (aluno.telefone, frases[1]);
	strcpy (aluno.curso, frases[2]);

	//'strtof()' converte strings em valores tipo float.
	aluno.nota1 = strtof(frases[3], NULL);
	aluno.nota2 = strtof(frases[4], NULL);
	
	return aluno;
}

//Divide uma String em pedaços e inseri elas na array adjacente.
void separador (char linha[], char frases[][TAMANHO_MIN]) {
	char *memoria = linha;
	for (int i = 0; i < 5; i++) {
			//'strok_r()' usa um ponteiro da linha e quando chega em uma ',' retorna as informações anterior a ela.
			strcpy(frases[i], strtok_r(memoria, ",", &memoria));
	}
}

int main () {

	FILE *entrada, *saida;
	entrada = fopen("DadosEntrada.csv", "r");
	saida = fopen("SituacaoFinal.csv", "w");

	if (entrada == NULL) {
		printf("Arquivo nao encontrado.");
		exit(1);
	}

	char linha[TAMANHO_MAX];
	char frases[5][TAMANHO_MIN];

	//Este loop ira ler as linhas do arquivo uma de cada vez.
	while (fgets(linha, sizeof(linha), entrada) != NULL) {
		if (strcmp(linha, "Nome,Telefone,Curso,Nota1,Nota2\n") == 0) continue;
		strtok(linha, "\n"); //remove o fim da linha.

		separador (linha, frases);
		Aluno aluno = aluno_organiza (frases);

		//Calcula a media e gera o arquivo final.
		float media = (aluno.nota1 + aluno.nota2) / 2;
		if (media >= 7) fprintf (saida, "%s, %.2f, APROVADO\n", aluno.nome, media);
		else fprintf (saida, "%s, %.2f, REPROVADO\n", aluno.nome, media);
	}

	fclose (entrada);
	fclose (saida);

	return 0;
}