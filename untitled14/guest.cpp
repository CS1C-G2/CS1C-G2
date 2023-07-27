#include "guest.h"

Guest::Guest() : User("Guest", "") {
    // Set permissions for a guest
    setCanCreateShape(false);
}

std::string Guest::getType() const {
    return "Guest";
}
