#ifndef GUEST_H
#define GUEST_H

#include "user.h"

class Guest : public User {
public:
    Guest();
    std::string getType() const override;
};

#endif // GUEST_H
