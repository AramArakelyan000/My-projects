#include <iostream>
#include "bank.hpp"

int main() {
    BankSystem obj = BankSystem();

    obj.Balance();

    bool name = obj.setName("Aram");
    bool surname = obj.setSurname("Arakelyan");
    bool id = obj.setId("484500234575");
    bool passport = obj.setPassport("AL0394735");
    bool usd = obj.setUsd(100);
    bool amd = obj.setAmd(8000);
    bool euro = obj.setEuro(80);
    bool rub = obj.setRub(2000);

    if (name) {
        std::cout << "Name: " << obj.getName() << std::endl;
    }
    if (surname) {
        std::cout << "Surname: " << obj.getSurname() << std::endl;
    }
    if (passport) {
        std::cout << "Passport: " << obj.getPassport() << std::endl;
    }
    if (id) {
        std::cout << "Id: " << obj.getId() << std::endl;
    }
    if (amd) {
        std::cout << "Amd: " << obj.getAmd() << std::endl;
    }
    if (usd) {
        std::cout << "USD: " << obj.getUsd() << std::endl;
    }
    if (rub) {
        std::cout << "Rub: " << obj.getRub() << std::endl;
    }
    if (euro) {
        std::cout << "Euro: " << obj.getEuro() << std::endl;
    }  

    return 0;
}