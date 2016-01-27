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
| Data           :    10/11/2015                                             |
------------------------------------------------------------------------------
| Programa       :    EP04.c -    Alocação Dinâmica - Lista Encadeada        |
| Compilador     :    Pelles C (7.00.355)                                    |
| Objetivo       :    O programa utiliza uma lista encadeada para o cadastro |
|                     de funcionarios, e oferece algumas funções.            |
|                                                                            |
| Descricao do programa:                                                     |
|                     O programa cadastra registro de funcionarios com       |
|                     alguns dados em uma estrutura de lista encadeada.      |
|                     Uma das vantagens dessa estrutura é quando temos       |
|                     inserção e remoção frequentemente. Além disso o        |
|                     programa possui funções utilitárias, como imprimir     |
|                     todos os funcionarios, imprimir o funcionario que      |
|                     possui maior salario e desalocar os registros.         |
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

struct Funcionario {
	int cod;
	char nome[31];
	char cargo[21];
	float salario;
	char departamento[21];
	char email[31];
	struct Funcionario *prox;
};

struct Funcionario *Insere(struct Funcionario *inicio, struct Funcionario *f);
void ImprimeTodos(struct Funcionario *f);
void ImprimeMaiorSalario(struct Funcionario *f);
int QuantidadeLista(struct Funcionario *f);
void LiberaLista(struct Funcionario *f);

int main(void)
{
	struct Funcionario *inicio, *novo;
	int tam, op = 0, x;
	float y;

	tam = sizeof(struct Funcionario);
	inicio = NULL;

	do {
		system("CLS");
		printf("-------------MENU------------\n");
		printf("   DIGITE A OPCAO\n");
		printf("1 - REGISTRAR\n");
		printf("2 - IMPRIMIR TODOS\n");
		printf("3 - IMPRIMIR MAIOR SALARIO\n");
		printf("4 - QUANTIDADE DA LISTA\n");
		printf("5 - LIBERAR LISTA\n");
		printf("0 - SAIR DO PROG.\n\n");
		scanf("%d%*c", &op);
		printf("\n");
		switch(op)
		{
			// SAIR
			case 0: break;
			// REGISTRAR
			case 1:
				// ALOCAÇÃO DE MEMORIA
				system("CLS");
				novo = malloc(tam);
				if (!novo) {
					printf("Nao foi possivel alocar memoria.\nSaindo do programa...\n\n");
					exit(-1);
				}
				// CADASTRO DO CLIENTE
				printf("----Cadastrando Funcionario----\n");
				printf("Digite o codigo (numerico): ");
				scanf("%d%*c", &x);
				novo->cod = x;
				printf("Digite o nome (30 caracteres): ");
				gets(novo->nome);
				printf("Digite o cargo (20 caracteres): ");
				gets(novo->cargo);
				printf("Digite o salário (formato real): ");
				scanf("%f%*c", &y);
				novo->salario = y;
				printf("Digite o departamento (20 caracteres): ");
				gets(novo->departamento);
				printf("Digite o email (30 caracteres): ");
				gets(novo->email);
				// CHAMA FUNCAO
				inicio = Insere(inicio, novo);
				printf("\nFUNCIONARIO CADASTRADO! \n\n");
				system("PAUSE");
				break;
			// IMPRIMIR TODOS
			case 2:
				system("CLS");
				ImprimeTodos(inicio);
				system("PAUSE");
				break;
			// IMPRIMIR MAIOR SALARIO
			case 3:
				ImprimeMaiorSalario(inicio);
				system("PAUSE");
				break;
			// IMPRIMIR QUANTIDADE DA LISTA
			case 4:
				printf("Quantidade de funcionarios na lista: %d\n\n", QuantidadeLista(inicio));
				system("PAUSE");
				break;
			// LIBERAR LISTA
			case 5:
				printf("Liberando lista...\n");
				LiberaLista(inicio);
				inicio = NULL;
				printf("Lista liberada com sucesso!\n\n");
				system("PAUSE");
				break;
			// OPCAO PADRAO
			default:
				printf("Opcao invalida! \n\n");
				system("PAUSE");
				break;
		}
	} while (op != 0);

	return 0;
}

struct Funcionario *Insere(struct Funcionario *inicio, struct Funcionario *f)
{
	f->prox = inicio;
	inicio = f;
	return inicio;
}

void ImprimeTodos(struct Funcionario *f)
{
	while (f != NULL)
	{
		printf("--------Registro de Funcionario--------\n\n");
		printf("     Codigo : %d\n", f->cod);
		printf("       Nome : %s\n", f->nome);
		printf("      Cargo : %s\n", f->cargo);
		printf("    Salario : %.2f\n", f->salario);
		printf("Departamento: %s\n", f->departamento);
		printf("      Email : %s\n", f->email);
		printf("---------------------------------------\n\n");
		f = f->prox;
	}
}
void ImprimeMaiorSalario(struct Funcionario *f)
{
	float maior = 0.0;
	while (f != NULL)
	{
		if (f->salario > maior)
			maior = f->salario;
		f = f->prox;
	}
	printf("O maior salario: %.2f\n\n", maior);
}
int QuantidadeLista(struct Funcionario *f)
{
	int i = 0;
	while (f != NULL)
	{
		i++;
		f = f->prox;
	}
	return i;
}
void LiberaLista(struct Funcionario *f)
{
	struct Funcionario *aux;
	aux = f;
	while (f != NULL)
	{
		f = aux->prox;
		free(aux);
		aux = f;
	}
}
