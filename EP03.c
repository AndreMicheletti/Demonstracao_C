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
| Data           :    23/10/2015                                             |
------------------------------------------------------------------------------
| Programa       :    EP03.c -    Operadora Honesta                          |
| Compilador     :    Pelles C (7.00.355)                                    |
| Objetivo       :    O programa cadastra clientes e antenas e tem como      |
|                     objetivo realizar a mudança de serviço da operadora    |
|                     Telejusta para o serviço wireless                      |
|                                                                            |
| Descricao do programa:                                                     |
|                     O programa recebe os cadastros de Antenas e Clientes,  |
|                     e realiza uma busca por nome de um cliente que deseja  |
|                     fazer a mudança. A rotina escolhe a melhor antena      |
|                     disponivel para o cliente, levando em conta o limite   |
|                     de usuarios, alcance e preço da antena. E caso         |
|                     encontre, atualiza os cadastros, caso contrário,       |
|                     informa que não foi possivel realizar a mudança        |
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Data
{
	int dia;
	int mes;
	int ano;
};

struct Antena
{
	char nome[6];
	int alcance;
	float preco;
	int limite;
	int usuarios;
	int x;
	int y;
};

struct Cliente
{
	char nome[31];
	struct Data datacontrato;
	float mensalidade;
	int x;
	int y;
};

int buscaAntena(char busca[6], struct Antena *pantenas, int numA);

int buscaCliente(char busca[31], struct Cliente *pclientes, int numC);

int main(void)
{
	struct Antena *antenas[10];
	struct Cliente *clientes[30];
	int i, j, numC, numA, ind_cli, dx, dy, melhor_antena, sizeA, sizeC;
	float dist = 0.0;
	char n1[6], n2[31], busca[31], op;

	sizeA = sizeof(struct Antena);
	sizeC = sizeof(struct Cliente);

	// ANTENAS
	printf("Digite o numero de Antenas que deseja cadastrar: ");
	scanf("%d", &numA);
	if (numA > 10) numA = 10;

	// Cadastro de Antenas
	for(i = 0; i < numA; i++)
	{
		printf("\n## Cadastro de antena %d ##\n", i+1);
		antenas[i] = malloc(sizeA);
		// Recebe um nome e verifica
		do {
			fflush(stdin);
			printf("Digite o nome: ");
			//scanf("%s", n1);
			gets(n1);
			n1[5] = '\0';
		} while (buscaAntena(n1, *antenas, numA) != -1);
		// Guarda o nome
		for (j = 0; j < 6; j ++) antenas[i]->nome[j] = n1[j];

		printf("Digite o alcance: ");
		scanf("%d", &antenas[i]->alcance);
		printf("Digite o preco: ");
		scanf("%f", &antenas[i]->preco);
		printf("Digite o limite de usuarios: ");
		scanf("%d", &antenas[i]->limite);
		printf("Digite a qnt de usuarios atual: ");
		scanf("%d", &antenas[i]->usuarios);
		printf("Digite a coord. X: ");
		scanf("%d", &antenas[i]->x);
		printf("Digite a coord. Y: ");
		scanf("%d", &antenas[i]->y);
	}

	// CLIENTES
	printf("\n\nDigite o numero de clientes que deseja cadastrar: ");
	scanf("%d", &numC);
	if (numC > 30) numC = 30;
	
	// Cadastro de Clientes
	for(i = 0; i < numC; i++)
	{
		printf("\n## Cadastro de cliente %d ##\n", i+1);
		clientes[i] = malloc(sizeC);
		// Recebe um nome e verifica
		do {
			fflush(stdin);
			printf("Digite o nome: ");
			//scanf("%s", n2);
			gets(n2);
			n2[30] = '\0';
		} while (buscaCliente(n2, *clientes, numC) != -1);
		// Guarda o nome
		for (j = 0; j < 31; j ++) clientes[i]->nome[j] = n2[j];

		printf("Digite a data do contrato (dd/mm/aaaa): ");
		scanf("%d/%d/%d", 
			&clientes[i]->datacontrato.dia, 
			&clientes[i]->datacontrato.mes, 
			&clientes[i]->datacontrato.ano);
		printf("Digite a mensalidade atual: ");
		scanf("%f", &clientes[i]->mensalidade);
		printf("Digite a coord. X: ");
		scanf("%d", &clientes[i]->x);
		printf("Digite a coord. Y: ");
		scanf("%d", &clientes[i]->y);
	}

	// BUSCA
	do {
		fflush(stdin);
		printf("\n\nDigite o nome de um cliente para a busca: ");
		gets(busca);
		busca[30] = '\0';

		ind_cli = buscaCliente(busca, *clientes, numC);
		if (ind_cli != -1)
		{
			// Cliente esta cadastrado
			melhor_antena = -1;
			for (i = 0; i < numA; i++)
				if(antenas[i]->usuarios < antenas[i]->limite)
				{
					dx = clientes[ind_cli]->x - antenas[i]->x;
					dy = clientes[ind_cli]->y - antenas[i]->y;
					dist = sqrt((dx*dx)+(dy*dy));
					if (dist <= antenas[i]->alcance)
					{
						if (melhor_antena == -1)
							melhor_antena = i;
						else if (antenas[i]->preco < antenas[melhor_antena]->preco)
							melhor_antena = i;
					}
				}
			if (melhor_antena == -1)
				printf("\nServico wireless indisponivel.\n");
			else {
				clientes[ind_cli]->mensalidade = antenas[melhor_antena]->preco;
				antenas[melhor_antena]->usuarios += 1;
				printf("\nCliente encontrado!");

				printf("\n\n-- Dados do cliente --");
				printf("\nNome: %s", clientes[ind_cli]->nome);
				printf("\nData do contrato: %2d/%2d/%4d",
						clientes[ind_cli]->datacontrato.dia,
						clientes[ind_cli]->datacontrato.mes,
						clientes[ind_cli]->datacontrato.ano);
				printf("\nMensalidade: R$%.2f", clientes[ind_cli]->mensalidade);
				printf("\nLocalizacao: X(%d), Y(%d)", clientes[ind_cli]->x, clientes[ind_cli]->y);

				printf("\n\n-- Dados da antena usada --");
				printf("\nNome: %s", antenas[melhor_antena]->nome);
				printf("\nRaio de alcance: %d", antenas[melhor_antena]->alcance);
				printf("\nLimite de Usuarios: %d", antenas[melhor_antena]->limite);
				printf("\nUsuarios utilizando: %d", antenas[melhor_antena]->usuarios);
				printf("\nLocalizacao: X(%d), Y(%d)", antenas[melhor_antena]->x,antenas[melhor_antena]->y);
			}
		} else {
			// Cliente nao esta cadastrado
			printf("\nNao e cliente\n\n");
		}

		printf("\n\nDeseja procurar outro cliente? [S]im | [N]ao\n");
		scanf("%c", &op);

	} while ((op != 'N') && (op != 'n'));

	// Liberação
	for (i = 0; i < numA; i++)
		free(antenas[i]);
	for (i = 0; i < numC; i++)
		free(clientes[i]);


	return 0;
}

//        buscaAntena
// busca    : nome a ser procurado no vetor antenas
// pantenas : endereco do vetor antenas do main
// numA     : tamanho do vetor
// retorna  = o indice no vetor caso encontre
//          = -1 caso não encontre
int buscaAntena(char busca[6], struct Antena *pantenas, int numA)
{
	int i;
	for (i = 0; i < numA; i++)
		if (strcmp((pantenas + i)->nome, busca) == 0)
			return i;
	return -1;
}

//        buscaCliente
// busca     : nome a ser procurado no vetor clientes
// pclientes : endereco do vetor clientes do main
// numC      : tamanho do vetor
// retorna   = o indice no vetor caso encontre
//           = -1 caso não encontre
int buscaCliente(char busca[31], struct Cliente *pclientes, int numC)
{
	int i;
	for (i = 0; i < numC; i++)
		if (strcmp((pclientes + i)->nome, busca) == 0)
			return i;
	return -1;
}
