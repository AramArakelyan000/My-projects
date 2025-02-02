#include <cstring>
#include <iostream>
#include "bank.hpp"

        int BankSystem::members = 0;
        double BankSystem::balanceusd = 0;
        double BankSystem::balanceamd = 0;
        double BankSystem::balancerub = 0;
        double BankSystem::balanceeuro = 0;

        BankSystem::BankSystem(){
            name = nullptr;
            surname = nullptr;
            passport = nullptr;
            id = nullptr;

            usd = 0.0;
            amd = 0.0;
            euro = 0.0;
            rub = 0.0;
        }
        BankSystem::BankSystem(char* name, char* surname, char* passport, char* id, double usd, double amd, double euro, double rub){
            this -> name = new char[strlen(name)];
            strcpy(name, this ->name);
            this -> surname = new char[strlen(surname)];
            strcpy(surname, this -> surname);
            this -> passport = new char[strlen(passport)];
            strcpy(passport, this -> passport);
            this -> id = new char[strlen(id)];
            strcpy(id, this -> id);
            this -> usd = usd;
            this -> amd = amd;
            this -> euro = euro;
            this -> rub = rub;
            BankSystem::incrementMembers();    
        }
       BankSystem::~BankSystem() {
            delete [] name;
            delete [] surname;
            delete [] passport;
            delete [] id;

            name = nullptr;
            surname = nullptr;
            passport = nullptr;
            id = nullptr;
            BankSystem::decrementMembers();
            BankSystem::subAmd(amd);
            BankSystem::subUsd(usd);
            BankSystem::subRub(rub);
            BankSystem::subEuro(euro);
        }
        bool BankSystem::setUsd(double x){
            if (x > 0){
                this -> usd = x;
                BankSystem::addUsd(x); 
                return true;
            }else{
                return false;
            }
        }
        bool BankSystem::setAmd(double x){
            if (x > 0){
                this -> amd = x;
                BankSystem::addAmd(x); 
                return true;
            }else{
                return false;
            }
        }
        bool BankSystem::setEuro(double x){
            if (x > 0){
                this -> euro = x;
                BankSystem::addEuro(x); 
                return true;
            }else{
                return false;
            }
        }
        bool BankSystem::setRub(double x){
            if (x > 0){
                this -> rub = x;
                BankSystem::addRub(x); 
                return true;
            }else{
                return false;
            }
        }
        bool BankSystem::setName(const char* x){
            for (int i = 0; x[i] != '\0'; ++i){
                if (!((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z'))){
                    return false;
                }
            }
            this -> name = x;
            return true;
        }
        bool BankSystem::setSurname(const char* x){
            for (int i= 0; x[i] != '\0'; ++i){
                if (!((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z'))){
                    return false;
                }
            }
            this -> surname = x;
            return true;
        }
        bool BankSystem::setId(const char* x){
            for (int i= 0; x[i] != '\0'; ++i){
                if (!((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z') || (x[i] >= 0))){
                    return false;
                }
            }
            this -> id = x;
            return true;
        }
        bool BankSystem::setPassport(const char* x){
            for (int i = 0; x[i] != '\0'; ++i){
                if (!((x[i] >= 'a' && x[i] <= 'z') || (x[i] >= 'A' && x[i] <= 'Z') || (x[i] >= 0))){
                    return false;
                }
            }
            this -> passport = x;
            return true;
        }
        const char* BankSystem::getName(){
            return name;
        }
        const char* BankSystem::getSurname(){
            return surname;
        }
        const char* BankSystem::getPassport(){
            return passport;
        }
        const char* BankSystem::getId(){
            return id;
        }
        double BankSystem::getUsd(){
            return usd;
        }
        double BankSystem::getAmd(){
            return amd;
        }
        double BankSystem::getEuro(){
            return euro;
        }
        double BankSystem::getRub(){
            return rub;
        }
        void BankSystem::Balance(){
            std::cout << "USD: " << usd << std::endl;
            std::cout << "AMD: " << amd << std::endl;
            std::cout << "EURO: " << euro << std::endl;
            std::cout << "RUB: " << rub << std::endl;
        }
        void BankSystem::incrementMembers() {
            BankSystem::members++;
        }
        void BankSystem::decrementMembers() {
            BankSystem::members--;
        }
        void BankSystem::addUsd(double x){
            BankSystem::balanceusd += x;
        }
        void BankSystem::addEuro(double x){
            BankSystem::balanceeuro += x;
        }
        void BankSystem::addAmd(double x){
            BankSystem::balanceamd += x;
        }
        void BankSystem::addRub(double x){
            BankSystem::balancerub += x;
        }
        void BankSystem::subUsd(double x){
            BankSystem::balanceusd -= x;
        }
        void BankSystem::subEuro(double x){
            BankSystem::balanceeuro -= x;
        }
        void BankSystem::subAmd(double x){
            BankSystem::balanceamd -= x;
        }
        void BankSystem::subRub(double x){
            BankSystem::balancerub -= x;
        }




    

