class Cliente{
   private:
         char nome[50],cognome[30],nickname[20];
         char password[10];
         char cartaDiCredito[8];
   public:
        Cliente();
        Cliente(char*,char*,char*,char*,char*);
        ~Cliente();
        char* getNome()const;
        char* getPassword()const;
        char* getCarta()const;
		char* getNickname();
		char* getCognome()const;
        Cliente  operator = (Cliente&c);
};
