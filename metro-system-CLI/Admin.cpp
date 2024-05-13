#include "Admin.h"

Admin::Admin(std::string email, std::string pass) :Account(email, pass) {

}

Admin::Admin(std::string email, std::string password, std::string name, int nationalId, int age) :Account(email, password, name, nationalId, age) {

}