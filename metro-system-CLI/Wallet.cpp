#include "Wallet.h"

Wallet::Wallet(int chash):money(chash)
{
    
}

void Wallet::charge(int chash) 
{
    if (!vaidCharge(chash))return;
    /*std::cout << "chash = " << chash <<"   money"<<money <<"\n";
    std::cout << "asd"<<getMoney()<<money;*/
    money += chash;
    //std::cout << "asd" << getMoney() << money;

}

bool Wallet::vaidCharge(int chash)
{
    if (chash % 10 != 0) {
        std::cout << "Amount must be a multiple of 10." << std::endl;
        return false;
    }
    if (chash + money > 400) {
        std::cout << "Cannot exceed the maximum limit of 400 LE." << std::endl;
        return false;
    }
    return true;
}

void Wallet::checkIn(Stage& stage)
{
    if (!isValid(stage.getPrice())) {
        std::cout << "Not enough money in wallet." << std::endl;
        return;
    }
    money -= stage.getPrice();
}

float Wallet::getMoney()
{
    return money;
}

bool Wallet::isValid(float price)
{
    if (price > money)return false;;
    return true;
}
