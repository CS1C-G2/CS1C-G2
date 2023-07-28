#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(const std::string& username, const std::string& password);
    virtual ~User();

    virtual std::string getType() const = 0;

    void setCanCreateShape(bool canCreate) {
        this->canCreateShape = canCreate;
    }

    bool getCanCreateShape() const {
        return this->canCreateShape;
    }

protected:
    std::string username;
    std::string password;
    bool canCreateShape;
};

#endif
