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
| Aluno          :    Kelvin Silva Alves de Souza                            |
| Matricula      :    15111507                                               |
| Data           :    15/09/2015                                             |
------------------------------------------------------------------------------
| Programa       :    EP01.c - Sigilo Absoluto                               |
| Compilador     :    Pelles C (7.00.355)                                    |
| Objetivo       :    O programa recebe uma mensagem e entao cria            |
|                     ou quebra o sigilo.                                    |
|                                                                            |
| Descricao do programa:                                                     |
|                     Apos receber uma mensagem e uma palavra, o programa    |
|                     oculta todas as ocorrencias dessa palvra na mensagem.  |
|                     Tambem e possivel fazer o processo inverso.            |
|                     - A palavra ocultada sera substituida por              |
|                     '*' para cada ocorrencia                               |
------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <string.h>

int tamString(char str[]);

int main(void) {
	
	char mensagem[101], palavra[101];
	int operacao, i = 0, j = 1, palavra_size, mensagem_size;
	
	printf("Digite a mensagem:\n");
	gets(mensagem);
	printf("Digite a palavra chave:\n");
	gets(palavra);  
	palavra_size = tamString(palavra);
	mensagem_size = tamString(mensagem);


	printf("Digite a operação:\n 0 para criar sigilo\n 1 para quebrar sigilo\n");
	scanf("%d%*c", &operacao);
	switch (operacao) {
		case 0:
			// Enquanto nao chegar ao fim da mensagem
			while (mensagem[i] != '\0')
			{
				// Verifica as possibilidades de encontrar a palavra
				if (mensagem[i] == palavra[0])
				{
					// Verifica todas as letras
					for (j = 1; j < palavra_size; j++)
						if (mensagem[i+j] != palavra[j]) break;

					// Verifica se é mesmo a palavra
					if (j == palavra_size)
					{
						// A palavra foi encontrada por inteiro
						// o indice i eh onde ela foi encontrada

						// Limpa a palavra e coloca * na primeira letra
						for (j = 0; j < palavra_size; j++)
							mensagem[i+j] = (j == 0 ? '*' : ' ');

						// Traz o resto da mensagem para trás
						j = 1;
						while(mensagem[i+j] != '\0')
						{
							mensagem[i+j] = mensagem[i+j+palavra_size-1];
							j++;
						}
					}
				}
				i++;
				j=0;
			}
			printf("\n%s\n", mensagem);
			break;
		case 1:
			// Enquanto no chegar ao fim da mensagem
			while (mensagem[i] != '\0') 
			{
				// Verifica as possibilidade de encontrar o '*'
				if(mensagem[i] == '*')
				{
					// Adiciona o tamanho da palavra ao tamanho da mensagem
					mensagem_size += palavra_size;
					// Move os caracteres para direita de acordo com o tamanho da palavra
					for(j = (mensagem_size -  1); j > i; j--) mensagem[j] = mensagem[j-(palavra_size-1)];
					// Adiciona a palavra a mensagem
					for(j = i; j < (i + palavra_size); j++) mensagem[j] = palavra[j - i];
				}
				i++;
			}
			printf("%s\n\n", &mensagem); 
			break;

		default:
			printf("Operacao Invalida!\n\n");
			break;
	}
	
	
	return 0;
}	

int tamString(char str[]) {
	int i = 0;
	while (str[i] != '\0') i++; 
	return i;
}
