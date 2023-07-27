#include "user.h"

User::User(const std::string& username, const std::string& password) :
    username(username), password(password) {
}

User::~User() {
}

std::string User::getType() const {
    return "User";
}
