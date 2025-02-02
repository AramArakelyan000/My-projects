#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H 

class BankSystem
{
  private:
        const char *name;
        const char *surname;
        const char *passport;
        const char *id;

        double usd;
        double amd;
        double euro;
        double rub;

        static int members;
        static double balanceusd;
        static double balanceamd;
        static double balanceeuro;
        static double balancerub;

    public:

        BankSystem();
        BankSystem(char* name, char* surname, char* passport, char* id, double usd, double amd, double euro, double rub);
            
        ~BankSystem();
        bool setUsd(double x);
            
        bool setAmd(double x);
        bool setEuro(double x);
        bool setRub(double x);
        bool setName(const char* x);
        bool setSurname(const char* x);
        bool setId(const char* x);
        bool setPassport(const char* x);
        const char* getName();
        const char* getSurname();
        const char* getPassport();
        const char* getId();
        double getUsd();
        double getAmd();
        double getEuro();
        double getRub();
        void Balance();
        static void incrementMembers();
        static void decrementMembers();
        static void addUsd(double x);
        static void addEuro(double x);
        static void addAmd(double x);
        static void addRub(double x);
        static void subUsd(double x);
        static void subEuro(double x);
        static void subAmd(double x);
        static void subRub(double x);

};
#endif
