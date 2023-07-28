#include "admin.h"

Admin::Admin(const std::string& username, const std::string& password) :
    User(username, password) {
}

std::string Admin::getType() const {
    return "Admin";
}
