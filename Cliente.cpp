#include "Cliente.h"
#include <string.h>

//costruttore cliente
Cliente::Cliente(){}
//costruttore cliente con parametri
Cliente::Cliente(char *_nome,char *_cognome, char *_nickname,char* _password,char* _carta)
{
    strcpy(nome,_nome);
    strcpy(cognome,_cognome);
    strcpy(nickname,_nickname);	
    strcpy(password,_password);
    strcpy(cartaDiCredito,_carta);
}
//distruttore cliente
Cliente::~Cliente(){}
//getNome restituisce un puntatore char con scritto il nome
char* Cliente::getNome()const
{
   char *nome1;
   nome1=new char[50];
   strcpy(nome1,nome);
   return nome1;
}
char* Cliente::getNickname()
{
   char *_nickname;
   _nickname=new char[40];
   strcpy(_nickname,nickname);
   return _nickname;
}
char* Cliente::getCognome()const
{
   char *cognome1;
   cognome1=new char[30];
   strcpy(cognome1,cognome);
   return cognome1;
}
//getPassword restituisce un puntatore char con scritta la password
char* Cliente::getPassword()const
{
    char *_password;
    _password=new char[10];
    strcpy(_password,password);
    return _password;
}
//getCarta restituisce un puntatore char con scritto il numero di carta
char* Cliente::getCarta()const
{
    char * ncarta;
    ncarta=new char[8];
    strcpy(ncarta,cartaDiCredito);
    return ncarta;
}

Cliente Cliente::operator=(Cliente &c){
   strcpy(nome,c.nome);
   strcpy(cognome,c.cognome);
   strcpy(nickname,c.nickname);
   strcpy(password,c.password);
   strcpy(cartaDiCredito,c.cartaDiCredito);
   return *this;
}
