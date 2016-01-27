/*
------------------------------------------------------------------------------
| Instituicao    :    Faculdade de Tecnologia de Sao Paulo                   |
| Departamento   :    Tecnologia da Informacao                               |
| Curso          :    Analise e Desenvolvimento de Sistemas                  |
| Disciplina     :    ILP-010                                                |
| Turma          :    Tarde                                                  |
| Professor      :    Akamine                                                |
| Aux. Docente   :    Lucio                                                  | 
| Aluno          :    André Luiz Marques Torres Michelletti                  |
| Matricula      :    15101126                                               |
| Data           :    15/09/2015                                             |
------------------------------------------------------------------------------
| Programa       :    EP02.c - Corram que os zumbis vêm ai!                  |
| Compilador     :    Pelles C (7.00.355)                                    |
| Objetivo       :    O programa recebe uma planta de um edificio e          |
|                     devolve o percurso que irá salvar o maior número       |
|                     de pessoas.                                            |
|                                                                            |
| Descricao do programa:                                                     |
|                     O programa recebe como entrada uma planta definida     |
|                     por caracteres que simbolizam paredes (#), zumbis (Z), |
|                     sobrevientes (S), áreas livres ( ) e o ponto           |
|                     inicial (P). O programa então desenvolve um percurso   |
|                     salvando o maior número de pessoas, contabilizando os  |
|                     zumbis encontrados e marcando toda a área que pode ser |
|                     percorrida, evitando os zumbis.                        |
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>

void percorrePlanta(char *pplanta, int l, int c, int nC, int *pzumbis, int *psalvos);

int main(void)
{
	int i, j, m, n, l = -1, c = -1, zumbis = 0, salvos = 0;

	printf("Digite m n:");
	scanf("%d %d%*c", &m, &n);

	// m+2 e n+2 para a inserção da borda
	char planta[m+2][n+2];
	char str[n];

	printf("Digite cada linha da planta:\n");
	for (i = 0; i < m; i++)
	{
		// Recebe uma string
		gets(str);
		// Copia para a planta
		for (j = 0; j < n; j++)
		{
			// Copia no espaço reservado para a planta (pulando a borda)
			planta[i+1][j+1] = str[j];
			// Caso encontre o ponto inicial nessa linha
			if (str[j] == 'P')
			{ // Guarda
				l = i+1; c = j+1;
			}
		}
	}

	// Caso não exista ponto inicial
	if (l == -1 || c == -1)
	{
		printf("\nNão existe ponto inicial P\nSaindo...\n\n");
		return 0;
	}

	// Insere uma borda de '?'
	// Borda primeira linha
	for (i = 0; i < n+2; i++) 
		planta[0][i] = '?';

	// Borda ultima linha
	for (i = 0; i < n+2; i++) 
		planta[m+1][i] = '?';

	// Borda primeira coluna
	for (i = 0; i < m+2; i++) 
		planta[i][0] = '?';

	// Borda ultima coluna
	for (i = 0; i < m+2; i++) 
		planta[i][n+1] = '?';

	// Percorre a Planta
	percorrePlanta(&planta[0][0], l, c, n+2, &zumbis, &salvos);

	printf("\nA planta apos o percurso: \n\n");

	// Imprime somente a planta (ignorando a borda)
	for (i = 1; i < m+1; i++)
	{
		// Imprime a linha da planta
		for (j = 1; j < n+1; j++)
			printf("%c", planta[i][j]);

		// Pula de linha
		printf("\n");
	}

	printf("\nSobreviventes salvos: %d\nZumbis encontrados: %d\n\n", salvos, zumbis);

	return 0;

}

// # Procedimento para Percorrer a planta #
// *pplanta = endereco inicial da matriz
//        l = linha atual
//        c = coluna atual
//       nC = numero de colunas da matriz
// *pzumbis = ponteiro para a var zumbis do main
// *psalvos = ponteiro para a var salvos do main

void percorrePlanta(char *pplanta, int l, int c, int nC, int *pzumbis, int *psalvos)
{
	char *elemento = pplanta + l * nC + c;

	if (*elemento == '?' || *elemento == '#' || *elemento == '-' || *elemento == 'z')
		return;
	if (*elemento == 'Z')
	{
		*pzumbis += 1;
		*elemento = 'z';
		return;
	}
	if (*elemento == 'S')
		*psalvos += 1;

	if (*elemento != 'P')
		*elemento = '-';

	percorrePlanta(pplanta, l - 1, c, nC, pzumbis, psalvos);
	percorrePlanta(pplanta, l, c + 1, nC, pzumbis, psalvos);
	percorrePlanta(pplanta, l + 1, c, nC, pzumbis, psalvos);
	percorrePlanta(pplanta, l, c - 1, nC, pzumbis, psalvos);

}
