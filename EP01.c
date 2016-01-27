#include <stdio.h>
#include <string.h>

int tamString(char str[])
{
	int i = 0;
	while (str[i] != '\0') i++; 
	return i;
}

int main(void) 
{
	char mensagem[101], palavra[101];
	int operacao, i = 0, j = 1,k, palavra_size, found = 0;
	
	printf("Digite a mensagem:\n");
	gets(mensagem);
	printf("Digite a palavra chave:\n");
	gets(palavra);  
	palavra_size = tamString(palavra);


	printf("Digite a operação:\n 0 para criar sigilo\n 1 para quebrar sigilo\n ");
	scanf("%d%*c", &operacao);
	switch (operacao) 
	{
		// CRIAR SIGILO
		case 0:
			// Passa por cada elemento do vetor
			while (mensagem[i] != '\0') 
			{
				// Se achar a primeira letra da palavra
				if (mensagem[i] == palavra[0])
				{
					// Checa se é mesmo aquela palavra
					for (j = 1; j < palavra_size; j++)
					{
						if (mensagem[i+j] != palavra[j]) break;
						// Verifica um espaço após a palavra
						if (j + 1 >= palavra_size)
							if (mensagem[i+j+1] == ' ')
								found = 1; // A palavra é essa mesmo
					}
					if (found == 1) {
						// A palavra foi encontrada (i é o indice que ela começa)
						// Limpar a palavra e substituir * na primeira
						for (k = 0; k < palavra_size; k++)
							mensagem[i+k] = (k == 0 ? '*' : ' ');
						// Trazer o resto da palavra para trás
						k = 1;
						while (mensagem[i+k] != '\0')
						{
							mensagem[i+k] = mensagem[i+k+palavra_size-1];
							k++;
						}
						// Voltar o indice (pois a frase inteira foi empurrada para trás)
						i -= palavra_size;
					} else {

					}
				}
				i++;
				found = 0;
			}
			printf("%s \n\n\n", mensagem);
			break;

		// REMOVER SIGILO
		case 1:
			
			break;

		// BAD OPERATION
		default:
			printf("Operacao Invalida!\n\n");
			break;
	}
	
	return 0;
}	
