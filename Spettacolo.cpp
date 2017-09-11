#include "Spettacolo.h"
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

Spettacolo::Spettacolo(){
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<20;j++)posti[i][j]=false;
}
Spettacolo::Spettacolo(char titolo[40]){
    int i,j;
    strcpy(film,titolo);
    for(i=0;i<10;i++)
        for(j=0;j<20;j++)posti[i][j]=false;
    postiLiberi=200;
}
Spettacolo::~Spettacolo(){}
Spettacolo& Spettacolo::operator=(const Spettacolo nuovo){
    int i,j;
    strcpy(film,nuovo.film);
    for(i=0;i<10;i++)
        for(j=0;j<20;j++)posti[i][j]=nuovo.posti[i][j];
    postiLiberi=nuovo.postiLiberi;
    return *this;
}

char* Spettacolo::getFilm(){
    char *f;
    f=new char[40];
    strcpy(f,film);
    return f;
}
int Spettacolo::getPostiL(){
    return postiLiberi;
}
bool Spettacolo::isFull(){
    return postiLiberi==0;
}
bool Spettacolo::isLibero(int x, int y){
    system("pause");
    if(posti[x][y])return false;
    system("pause");
    return true;
}
void Spettacolo::occupaPosto(int x, int y){
     posti[x][y]=true;
}
void Spettacolo::stampaSala(){
     
     char c[2];
     int i,j,a, x,y;
     initwindow(480,300,film,0,0,false,false);
     setcolor(LIGHTBLUE);
     for(x=0;x<480;x++)line(x,0,x,300);
     bar(12,0,468,36);
     x=24;
     y=66;
     for(i=0;i<10;i++){
         for(j=0;j<20;j++){
             if(posti[i][j])setcolor(RED);
             else setcolor(GREEN);
             for(a=x;a<x+20;a++)line(a,y,a,y+14);
             x+=22;
         }
     y+=24;
     x=24;
     }
     setcolor(BLACK);
     setbkcolor(LIGHTBLUE);
     y=68;
     for(x=0;x<10;x++){
         itoa(x+1,c,10);
         outtextxy(6,y,c);
         y+=24;
     }
     x=28;
     for(y=0;y<20;y++){
         itoa(y+1,c,10);
         outtextxy(x,48,c);
         x+=22;
     }
     
}
void Spettacolo::confermaPosto(int x, int y){
     int i;
     system("pause");
     x=24+22*x;
     y=66+24*y;
     setcolor(YELLOW);
     for(i=x;i<x+20;i++)line(i,y,i,y+14);
}

