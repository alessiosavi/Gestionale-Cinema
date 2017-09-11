
class Spettacolo{
      private:
          char film[40];
          bool posti[10][20];
          int postiLiberi;
      public:
          Spettacolo();
          Spettacolo(char[40]);
          ~Spettacolo();
          Spettacolo& operator=(const Spettacolo);
          char* getFilm();
          int getPostiL();
          bool isFull();
          bool isLibero(int,int);
          void occupaPosto(int,int);
          void stampaSala();
          void confermaPosto(int , int);
};
