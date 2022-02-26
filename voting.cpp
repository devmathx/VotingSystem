#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> 
#include <locale.h>

int turno, senha;
int maria=0, joao=0, pedro=0, nulo=0; 
FILE *db;

void lendoDB(){	// L� os dados do arquivo .txt
	db = fopen("votos.txt", "r");
	fscanf(db, "%d %d %d %d", &maria, &joao, &pedro, &nulo);
}

void alert(const char titulo[], const char frase[], const char tipo[]){	// Alertas
	system("cls");
	if(tipo == "AVISO"){
		system("color E0");
	} else {
		system("color 4F"); 
	}
	printf("\n\n\t\t\t%s", titulo);
	printf("\n\n\n\t\t%s \n\n\tPressione qualquer tecla para prosseguir... ", frase);
	getch();
	system("cls");
}

void config(){	// Configura��o inicial
	alert("Aviso!","Digite somente numerais inteiros!", "AVISO");
	system("color 8F");
	printf("Configura��es\n\n");
	printf("Defina o n�mero de turnos: ");
	scanf("%d", &turno);
	printf("\nDefina uma senha para finalizar a vota��o: ");
	scanf("%d", &senha);
	system("cls");
}

int main() {
	
	setlocale(LC_ALL, "Portuguese");	
	lendoDB();
	config();
	
	int finalizar;
	while(finalizar != senha){ 
	
		// Sistema de vota��o
		int x=0, voto=0;
		while(x != turno){ 
			
			system("cls");
			system("color 0F"); 
			x++;
			printf("Turno %d", x);
			printf("\n\n1 Para Maria \n");
			printf("2 Para Jo�o \n");
			printf("3 Para Pedro \n");
			printf("0 Para nenhum dos candidatos");	
			printf("\n-----------------------------");
			printf("\nSeu voto: ");
			scanf("%d", &voto);
			system("cls");	
					
			// Guardando votos
			if(voto == 0){
				nulo++;
			}
			else if(voto == 1){
				maria++;
			} 
			else if(voto == 2){
				joao++;
			} 
			else if(voto == 3){
				pedro++;
			} else {
				x--;
				alert("Voto invalido!", "Seu voto deve ser de 0 a 3.", "ERRO");
			}
		} 
		// Finalizando vota��o
		char sn = 0;
		system("color AF"); 
		printf("\n\t\t\tVotos salvos!\n");
		printf("\nDeseja finalizar a vota��o? S/N ");
		scanf("%s", &sn);
		
		if(sn == 's' || sn == 'S'){	
			system("cls");
			system("color F0"); 
			printf("Digite a senha para finalizar: ");
			scanf("%d", &finalizar);
			
			if(finalizar == senha){						
				// Salvando votos
				db = fopen("votos.txt", "w");
				fprintf(db, "%d %d %d %d", maria, joao, pedro, nulo); 
				fclose(db);		
				
				// Exibindo votos
				system("cls");
				system("color B0"); 
				printf("Resultados da vota��o: \n");
				printf("\nMaria: %d", maria);
				printf("\nJo�o: %d", joao);
				printf("\nPedro: %d", pedro);
				int tvotos = maria + joao + pedro + nulo;
				printf("\n\nTotal de votos: %d", tvotos);
				
				printf("\n\nAperte qualquer tecla para fechar...");
				getch();
				
			} else {
				alert("Senha incorreta!", "A vota��o n�o pode ser finalizada.", "ERRO");
				lendoDB();
			} 
		} else {
			lendoDB();
			alert("Aviso!", "A vota��o ser� reiniciada.", "AVISO");
		}
	} // Ciclo de verifica��o de senha
}
