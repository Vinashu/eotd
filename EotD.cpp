#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

struct dado {
	int qtd = 0;
	int Ds[4] = {0,0,0,0};
} DP, DB, DC;

char tecla = ' ';
int Zs=1, Zk=0, B=10, C=0, Ds=0;

void desenharTela(void);
int lerTecla(int Ds);
void gamePlay(int Ds);
void clear(void);
void rolarDados(dado *DD);
void checarPortao(dado DP);
void checarBarricada(dado DB);
void checarCarro(dado DC);
void atualizarDados(dado DB, dado DC, dado DP);
void aumentarZs(int *Zs, int C);

int main(void){
  	setlocale(LC_ALL, "Portuguese");    
	srand (time(NULL));  	
	while(tecla != 'x'){
		desenharTela();
		Ds = lerTecla(Ds);	
		gamePlay(Ds);
		//checarEspecial();
		//checarVitoria();		
		clear();	
	}
	return(0);
}

void clear(void){
	system("cls");	
}

void desenharTela(void){
	printf("Zumbis no portão: %d\t",Zs);
	for(int i=0; i < Zs; i++){
		printf("#");
	}
	printf("\n\n");
	printf("Zumbis mortos: %d\t",Zk);
	for(int i=0; i < Zk; i++){
		printf("#");
	}
	printf("\n\n");	
	printf("Barricada: %d\t\t",B);
	for(int i=0; i < B; i++){
		printf("#");
	}
	printf("\n\n");	
	printf("Carro: %d\%\t\t",C);
	for(int i=0; i < C; i++){
		printf("#");
	}
	printf("\n\n");		
	return;
}

int lerTecla(int Ds){
	Ds = 0;
	printf("Quantos dados para o PORTÃO: ");
	scanf("%d",&DP.qtd);
	Ds += DP.qtd;
	printf("Quantos dados para o BARRICADA: ");
	scanf("%d",&DB.qtd);	
	Ds += DB.qtd;	
	printf("Quantos dados para o CARRO: ");
	scanf("%d",&DC.qtd);	
	Ds += DC.qtd;	
	return Ds;
}

void gamePlay(int Ds){
	if(Ds > 4){
		printf("\nO limite são 4 dados por turno!!!\n");
	} else {
		aumentarZs(&Zs, C);
		rolarDados(&DP);		
		rolarDados(&DB);
		rolarDados(&DC);				
		checarPortao(DP);
		checarBarricada(DB);
		checarCarro(DC);
	}
	system("pause");
}

void rolarDados(dado *DD){
	for (int i = 0; i < (*DD).qtd; i++){
		(*DD).Ds[i] = rand()%6 + 1;		
		printf("Dado %d = %d\n", i+1, (*DD).Ds[i] );
	}	
}

void checarPortao(dado DP){
	for(int i = 0; i < DP.qtd; i++){
		if(DP.Ds[i]>=3){
			Zs--;
			Zk++;
			DP.Ds[i]=0;
		}
	}	
	B -= Zs;
	return;
}

void checarBarricada(dado DB){
	for(int i = 0; i < DB.qtd; i++){
		if(DB.Ds[i]>=3){
			B++;
			DB.Ds[i]=0;
		}
	}
	if(B>10){B=10;}
	return;
}

void checarCarro(dado DC){
	for(int i = 0; i < DC.qtd; i++){
		if(DC.Ds[i]>=5){
			C++;
			DC.Ds[i]=0;
		}
	}
	return;
}

void aumentarZs(int *Zs, int C){
	if(C<=3){*Zs += 1;}
	if(C>3 && C<7){*Zs += 2;}
	if(C>=7 && C<=8){*Zs += 3;}		
	if(C>8){*Zs +=4;}	
}
