#pragma once
#include <Wt/Dbo/Dbo.h>
#include <string.h>

// Currently only Admin role exists
// Might add different roles in future
enum class Role {
    // Visitor = 0,
    // User = 1,
    Admin = 2,
};

class User {
  public:
    // Information saved to db.
    std::string username;
    std::string password;
    Role role;

    // Allows different sql actions when calling persist.
    template <class Action> void persist(Action &a) {
        Wt::Dbo::field(a, this->username, "username");
        Wt::Dbo::field(a, this->password, "password");
        Wt::Dbo::field(a, this->role, "role");
    }
};
