#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password);
    std::string getType() const;
};

#endif
