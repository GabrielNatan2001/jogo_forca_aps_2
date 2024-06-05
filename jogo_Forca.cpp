#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHANCES 6

void imprimirForca(int erros) {
    printf(" +---+\n");
    printf(" |   |\n");

    if (erros >= 1)
        printf(" O   |\n");
    else
        printf("     |\n");

    if (erros == 2)
        printf("/    |\n");
    else if (erros == 3)
        printf("/|   |\n");
    else if (erros >= 4)
        printf("/|\\  |\n");
    else
        printf("     |\n");

    if (erros == 5)
        printf("/    |\n");
    else if (erros >= 6)
        printf("/ \\  |\n");
    else
        printf("     |\n");

    printf("=========\n");
}

void informarLetrasErradas(char *letrasErradas){
	printf("\nLetras erradas: ");
    for (int i = 0; i < MAX_CHANCES; i++) {
        if (letrasErradas[i] != '\0')
            printf("%c ", letrasErradas[i]);
    }
}

void jogo(int *chances, char *menu, int *acertos, int tamPalavra, char *letrasCorretas, char *letrasErradas, char *palavra) {
    char letra;
    int i;

    while (*chances > 0 && *acertos < tamPalavra) {
        printf("\nPalavra: %s\n", letrasCorretas);
        printf("Chances restantes: %d\n", *chances);
        imprimirForca(MAX_CHANCES - *chances);

        informarLetrasErradas(letrasErradas);

        printf("\nDigite uma letra ou 1 para abrir o menu:\n");
        scanf(" %c", &letra);
        
        if (letra == '1') {
        	*menu = letra;
            break;
    	}

        int letraEncontrada = 0;
        for (i = 0; i < tamPalavra; i++) {
            if (letrasCorretas[i] == '_' && palavra[i] == letra) {
                letrasCorretas[i] = letra;
                (*acertos)++;
                letraEncontrada = 1;
            }
        }

        if (!letraEncontrada) {
            letrasErradas[MAX_CHANCES - *chances] = letra;
            (*chances)--;
        }

        system("cls");
    }
}

void limparVariaveis(int *chances, int *acertos, char *letrasCorretas, char *letrasErradas, int tamPalavra){
	*chances = MAX_CHANCES;
	*acertos = 0;
	for (int i = 0; i < tamPalavra; i++) {
	    letrasCorretas[i] = '_';
	}
	letrasCorretas[tamPalavra] = '\0';
	memset(letrasErradas, 0, sizeof(letrasErradas));
}

int main() {
    char palavra[20];
    char letrasErradas[MAX_CHANCES] = {'\0'};
    char letrasCorretas[20];
    char letra;
    int chances = MAX_CHANCES;
    int acertos = 0;
    char menu;
	int opcao = 0;
	int tamPalavra = 0;
	inicio:
		if(opcao != 1){
			printf("Digite a palavra secreta: ");
		    scanf("%s", palavra);

	    	tamPalavra = strlen(palavra);
	    
	    	for (int i = 0; i < tamPalavra; i++) {
			    letrasCorretas[i] = '_';
			}
			letrasCorretas[tamPalavra] = '\0';
	        system("cls");
		}
	    jogo(&chances, &menu, &acertos, tamPalavra, letrasCorretas, letrasErradas, palavra);
	    
		if(menu == '1' && acertos != tamPalavra){
	        system("cls");
	        printf("\n---------------Menu--------------");
	        printf("\nSelecione uma das seguintes opcoes");
	        printf("\n1 - Continuar");
	        printf("\n2 - Reiniciar");
	        printf("\n3 - Sair\n");
	        scanf("%d", &opcao);
	        
	        switch(opcao){
	        	case 1:
	        		system("cls");
	        		goto inicio;
	        		break;
	        	case 2:
	        		system("cls");
	                limparVariaveis(&chances, &acertos, letrasCorretas, letrasErradas, tamPalavra);
	        		goto inicio;
	        		break;
	        	default:
	        		printf("\nSaindo do jogo!");
	        		break;
			}
	        
		}else if(acertos == tamPalavra) {
	        printf("\nParabens, voce venceu! A palavra era: %s\n", palavra);
	        printf("\nJogar novamente?");
	        printf("\n1 - Sim");
	        printf("\n2 - Nao\n");
	        scanf("%d", &opcao);
	        switch(opcao){
	        	case 1:
	        		system("cls");
	                limparVariaveis(&chances, &acertos, letrasCorretas, letrasErradas, tamPalavra);
	                opcao = 2;
	        		goto inicio;
	        		break;
	        	default:
	        		printf("\nSaindo do jogo!");
	        		break;
			}
	    } else {
	        system("cls");
	        imprimirForca(MAX_CHANCES - chances);
	        printf("\nVoce perdeu! A palavra era: %s\n", palavra);
	    }

    return 0;
}
