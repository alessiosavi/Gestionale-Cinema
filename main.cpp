#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Cliente.h"
#include "Spettacolo.h"
#include <graphics.h>

bool logIn(Cliente &u);
int registrazione();
void admin();
void prenotaBiglietto();
bool logOut();
char orari[3][6];
void stampaBiglietto(Cliente c,int sala,int orario, char* s, int x, int y);

Cliente utente;
Spettacolo **scaletta;

int main(int argc, char **argv)
{
    
    FILE *f;
    
	unsigned int scelta,i,j;
	char s;
	bool log=true;
	strcpy(orari[0],"14:30");
	strcpy(orari[1],"16:30");
	strcpy(orari[2],"18:30");
	do{
    do{
	system("CLS");
	printf("\n   ---Benvenuto alla Biglietteria automatica del Pi-Sa MULTISALA---");	
	printf("\n\n\n\t1)LogIn\t\t\t\t\t2)Registrazione\n\n\t\t\t  3)Amministratore");
	printf("\n\n----Spettacoli Disponibili:");
	printf("\n\nSala\tOrario\tTitolo\n");
	f=fopen("Scaletta.bin","rb");
    scaletta= new Spettacolo *[3];
    for(i=0;i<3;i++)scaletta[i]= new Spettacolo [3];
    for(i=0;i<3;i++)fread(scaletta[i],1,sizeof(Spettacolo[3]),f);
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(j==1)printf("\nSala %d\t%s\t%s",i+1,orari[j], scaletta[i][j].getFilm());
            else printf("\n\t%s\t%s",orari[j], scaletta[i][j].getFilm());
        }
        printf("\n");
    }
	do{
       s=getche();
	}while(!(s=='1'||s=='2'||s=='3'));
	switch(s)
	{
		case '1':
			log=logIn(utente);
			break;
		case '2':
			registrazione();
			break;
		case '3':
             admin();
             break;
	}
    }while(log);
    do{
    system("CLS");
    printf("\nBenvenuto %s (%s %s)",utente.getNickname(),utente.getCognome(),utente.getNome());

    fclose(f);
    printf("\n\n1) Prenota Biglietto\n\n2) Logout");
    do{
    s=getche();
    }while(!(s=='2'||s=='1'));
    if(s=='1')prenotaBiglietto();
    else log=logOut();
    }while(log);
	}while(1);
	return 0;
}


bool logIn(Cliente &u){
	FILE *f;
	int i,j=-1;
	bool controllo=false;
	char nickname[50], password[10];
	f=fopen("Utenti.bin","rb");
	fseek(f,0,SEEK_END);
	i=ftell(f)/sizeof(Cliente);
	Cliente *utenti= new Cliente[i];
	//Cliente *utenti;
	//utenti=(Cliente*)malloc(i*sizeof(Cliente));
	fseek(f,0,SEEK_SET);
	fread(utenti,sizeof(Cliente),i,f);
	system("cls");
	printf("\nInserisci il tuo nickname: \n\t");
	scanf("%s",&nickname);
	for(j=0;j<i;j++){
		if(!strcmp(nickname,utenti[j].getNickname())){
			controllo=true;
			break;
		}
    }
    if(!controllo){
        printf("\n!!Nickname errato!!\n");
        getche();
	    return true;
    }
	printf("\nInserisci la tua password: \n\t");
	scanf("%s",&password);
	for(j=0;j<i;j++){
		if(!strcmp(password,utenti[j].getPassword())){
			controllo=false;
			break;
		}
    }
    if(controllo){
        printf("\n!!Passwod Errata!!\n");
        getche();
	    return true;
    }
	u=utenti[j];
	printf("\n\tLogin avvenuto con successo!");
	return false;	
	
}

int registrazione()
{
	FILE *f;
	char nome[50],cognome[30],nickname[20],password[20],carta[11],_password[20];
	//system("cls");
	printf("\n---Registrazione---");
	printf("\nInserire Nome: ");
	scanf("%s",&nome);
	printf("\nInserire Cognome: ");
	scanf("%s",&cognome);
	printf("\nInserire Nickname: ");
	scanf("%s",&nickname);
	printf("\nInserire password: ");
	scanf("%s",&password);
	printf("\nInserisci numero carta: ");
	scanf("%s",&carta);
	printf("\nReinserire la password per confermare la registrazione: ");
	scanf("%s",&_password);
	if(strcmp(password,_password)==0)
		{
			Cliente cliente(nome,cognome,nickname,password,carta);
			f=fopen("Utenti.bin","ab");
			if(f==NULL){
				printf("\nErrore nell'apertura del file!!");
				return -1;
			}
			fseek(f,0,SEEK_END);
			fwrite(&cliente,sizeof(cliente),1,f);
			fclose(f);
			printf("\nRegistrazione avvenuta con successo !\n");
			return 0;
		}
	printf("\nLe password non corrispondono\nRegistrazione fallita!!!");
	return -2;
}

void admin(){
     FILE *f;
     char s;
     int i,j, x, movie,sala;
     char film[40];
     Spettacolo *aux;
     Cliente *clienti;
     bool uscita=false;
     
     f=fopen("Scaletta.bin","rb");
     scaletta= new Spettacolo *[3];
     for(i=0;i<3;i++)scaletta[i]= new Spettacolo [3];
     for(i=0;i<3;i++)fread(scaletta[i],1,sizeof(Spettacolo[3]),f);
     fclose(f);
     system("CLS");
     fclose(f);
     do{
        printf("\n1)Cambia Spettacolo singolo");
        printf("\n2)Cambia Intera programmazione");
        printf("\n3)Lista utenti registrati");
        printf("\n4)Torna al Menu");
        do{
           s=getche();
        }while(!(s=='1'||s=='2'||s=='3'||s=='4'));
	    switch(s){
            case '1':
                 do{
                    system("cls");
                    printf("\n\n----Spettacoli Disponibili:");
	                printf("\nSala\tOrario\tTitolo");
                    for(i=0;i<3;i++){
                        for(j=0;j<3;j++){
                            if(j==1)printf("\nSala %d\t%s\t%s",i+1,orari[j], scaletta[i][j].getFilm());
                            else printf("\n\t%s\t%s",orari[j], scaletta[i][j].getFilm());
                        }
                        printf("\n");
                    }
                    printf("Seleziona Sala: ");
                    s=getche();
                 }while(!(s=='1'||s=='2'||s=='3'));
	             sala=s-'0'-1;
                 do{
                    system("cls");
                    printf("\n\n----Film proiettati nella sala %d:",sala+1);
	                printf("\nOrario\tTitolo");
                    for(i=0;i<3;i++)printf("\n%s\t%s",orari[i], scaletta[sala][i].getFilm());
                    printf("\nSeleziona Film: ");
                    s=getche();
                 }while(!(s=='1'||s=='2'||s=='3'));
	             movie=(s-'0')-1;
                 system("cls");
                 printf("Inserisci il titolo del film delle %s nella sala %d:\n\t",orari[movie],sala);
                 gets(film);
                 aux=new Spettacolo(film);
                 scaletta[sala][movie]=*aux;
                 fopen("Scaletta.bin","wb");
                 for(i=0;i<3;i++)fwrite(scaletta[i],1,sizeof(Spettacolo[3]),f);
                 fclose(f);
                 break;
                 
            case '2':
                 for(i=0;i<3;i++){
                     system("CLS");
                     printf("\n\tSala %d (MASSIMO 39 CARATTERI!)",i+1);
                     for(j=0;j<3;j++){
                         printf("\n%s ) ",orari[j]);
                         gets(film);
                         aux= new Spettacolo(film);
                         scaletta[i][j]= *aux;   
                     }
                 }
                 fopen("Scaletta.bin","wb");
                 for(i=0;i<3;i++)fwrite(scaletta[i],1,sizeof(Spettacolo[3]),f);
                 fclose(f);
                 break;
            case '3':
                 f=fopen("Utenti.bin","rb");
			     if(f==NULL){
                    do{
                    system("CLS");
                    printf("\nErrore: Utenti.bin non trovato, creare ora? (S/N)");
                    s=getche();
                 }while(s!='s'||s!='S'||s!='n'||s!='N');
                 //fclose(f);
                 if(s=='s'||s=='S'){
                     f=fopen("Utenti.bin","wb");
                     fclose(f);
                 }
                 }
                 else{
                     fseek(f,0,SEEK_END);
                     x=ftell(f)/sizeof(Cliente);
                     if(x==0)printf("\nNessun Cliente Registrato!");
                     else{
                         fseek(f,0,SEEK_SET);
                         clienti=new Cliente[x];
                         fread(clienti,x,sizeof(Cliente),f);
                         system("CLS");
                         printf("Lista Clienti (in ordine di registrazione)\n");
                         for(i=0;i<x;i++)printf("\n----%s\nNome: %s\nCognome: %s\nPassword: %s\nNumero Di Carta: %s",clienti[i].getNickname(),clienti[i].getNome(),clienti[i].getCognome(),clienti[i].getPassword(),clienti[i].getCarta());
                         printf("\n\n");
                         system("PAUSE");
                     }
                 }
                 break;
            case '4':
                 system("cls");
                 do{
                    system("CLS");
                    printf("!!--Sei sicuro di voler tornare al menu?--!!");
                    printf("\n\t\tS/N\n");
                    s=getche();
                 }while(!(s=='s'||s=='S'||s=='n'||s=='N'));
                 if(s=='s'||s=='S')uscita=true;
                 break;
        }
        for(i=0;i<3;i++){
            for(j=0;j<3;j++)printf("\n--%d) %s",orari[j], scaletta[i][j].getFilm());
            printf("\n");
        }
     }while(!uscita);   
     //
     /*
     for(i=0;i<3;i++)
         for(j=0;j<3;j++){
             scanf("%s",&film);
             aux= new Spettacolo(j,film);
             scaletta[i][j]= *aux;
             delete(aux);
         }
     for(i=0;i<3;i++)fwrite(scaletta[i],1,sizeof(Spettacolo[3]),f);
     */
     
     
     /*switch(s){
         case '1':
              printf("\nSeleziona Sala:\n\t1)\t2)\t3)\n");
              s=getche();
              
     }
     */
}

void prenotaBiglietto(){
     
     int sala, film,i,j,x;
     char s;
     char movie[40];
     bool continua=true;
     system("cls");
     printf("\n\n----Spettacoli Disponibili:");
	 printf("\nSala\tOrario\tTitolo");
     for(i=0;i<3;i++){
         for(j=0;j<3;j++){
             if(j==1)printf("\nSala %d\t%s\t%s",i+1,orari[j], scaletta[i][j].getFilm());
             else printf("\n\t%s\t%s",orari[j], scaletta[i][j].getFilm());
         }
         printf("\n");
     }
     do{
       system("cls");
       printf("\n\n----Spettacoli Disponibili:");
	   printf("\nSala\tOrario\tTitolo");
       for(i=0;i<3;i++){
           for(j=0;j<3;j++){
               if(j==1)printf("\nSala %d\t%s\t%s",i+1,orari[j], scaletta[i][j].getFilm());
               else printf("\n\t%s\t%s",orari[j], scaletta[i][j].getFilm());
           }
           printf("\n");
       }
       printf("Seleziona Sala: ");
       s=getche();
	 }while(!(s=='1'||s=='2'||s=='3'));
	 sala=s-'0'-1;
     do{
       system("cls");
       printf("\n\n----Film proiettati nella sala %d:",sala+1);
	   printf("\nOrario\tTitolo");
       for(i=0;i<3;i++)printf("\n%s\t%s",orari[i], scaletta[sala][i].getFilm());
       printf("\nSeleziona Film: ");
       s=getche();
	 }while(!(s=='1'||s=='2'||s=='3'));
	 film=(s-'0')-1;
     system("cls");
	 printf("Verrà ora visualizzata la Platea della sala %d\n-I posti rossi sono occupati\n-Quelli verdi sono liberi",sala+1);
	 s='n';
	 while(s=='n'||s=='N'){
     scaletta[sala][film].stampaSala();
	 printf("\n\nDigita la posizione del posto che desideri (fila e posto separati da uno spazio es \"1 1\")\n");
	 continua=true;
	 while(continua){
        scanf("%d",&j);
        scanf("%d",&i);
        i--;
        j--;
	    if(i>10||j>20){
            if(scaletta[sala][film].isLibero(i,j))printf("!!IL POSTO SELEZIONATO E' OCCUPATO!!");
            else printf("!!SELEZIONE ERRATA!!");
            continua=true;
        }
        else continua=false;
     }
     system("pause");
     //scaletta[sala][film].confermaPosto(i,j);
     do{
        system("CLS");
        //printf("\nIl posto selezionato è stato evidenziato in giallo\nConfermi l'acquisto?");
        printf("------------------------------------------");
        printf("\n  %s\n  Ore %s\n  Sala %d\n  Fila %d Posto %d",scaletta[sala][film],orari[film+1],sala+1,j+1,i+1);
        printf("------------------------------------------");
        printf("\nConfermi l'acquisto di questo biglietto?");
        printf("\n\t\tS/N\n");
        s=getche();
     }while(!(s=='s'||s=='S'||s=='n'||s=='N'));
     }//while s diverso da n o N
     if(s=='s'||s=='S'){
         //scaletta[sala][film].occupaPosto(i,j);
         system("pause");
         closegraph();
         system("pause");
         strcpy(movie,scaletta[sala][film].getFilm());
         system("pause");
         stampaBiglietto(utente,sala,film,scaletta[sala][film].getFilm(),i,j);
         printf("Grazie Per Aver scelto il cinema Pi-Sa e Buona Visione!");
     }
     
}

bool logOut(){
     
     char s;
     do{
        system("CLS");
        printf("!!--Sei sicuro di voler uscire?--!!");
        printf("\n\t\tS/N\n");
        s=getche();
     }while(!(s=='s'||s=='S'||s=='n'||s=='N'));
     if(s=='s'||s=='S')return false;
     return true;
     
}

void stampaBiglietto(Cliente c,int sala,int orario, char* s, int x, int y){
     int i;
     char nome[103];
     char posto[18];
     char sa[7];
     char num[3];
     itoa(x,num,10);
     strcpy(nome,c.getNome());
     strcat(nome," ");
     strcat(nome,c.getCognome());
     strcat(nome," (");
     strcat(nome,c.getNickname());
     strcat(nome,")");
     strcpy(posto,"Fila ");
     strcat(posto,num);
     strcat(posto,"  Posto ");
     itoa(y,num,10);
     strcat(posto,num);
     strcpy(sa,"Sala ");
     itoa(sala,num,10);
     strcat(sa,num);
     initwindow(400,150,"Biglietto",0,0,false,false);
     bar(0,0,400,150);
     setcolor(MAGENTA);
     for(i=0;i<25;i++)line(0,i,400,i);
     setcolor(BLACK);
     setbkcolor(LIGHTRED);
     outtextxy(15,15,"Cinema Pi-Sa Multisala");
     setbkcolor(WHITE);
     outtextxy(10,35,nome);
     outtextxy(10,55,sa);
     outtextxy(20,70,posto);
     outtextxy(10,95,orari[orario]);
     outtextxy(20,110,s);
     setlinestyle(DASHED_LINE,0,2);
     line(300,0,300,150);
     outtextxy(305,40,c.getNickname());
     outtextxy(305,55,orari[orario]);
     outtextxy(330,70,sa);
     outtextxy(305,85,posto);
     srand(time(NULL));
     setlinestyle(SOLID_LINE,0,2);
     for(i=310;i<390;i+=5){
         x=120-(rand()%10);
         line(i,x,i,150);
         line(i+1,x,i+1,150);
         line(i+2,x,i+2,150);
         line(i-140,x-50,i-140,100);
         line(i-139,x-50,i-139,100);
         line(i-138,x-50,i-138,100);
     }
     system("pause");
     closegraph();
}
