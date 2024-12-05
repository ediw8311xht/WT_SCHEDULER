#pragma once
#include <Wt/Dbo/Dbo.h>
#include <Wt/WDate.h>
#include <Wt/WTime.h>
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
    template <class Action>
    void persist(Action &a) {
        Wt::Dbo::field(a, this->username, "username");
        Wt::Dbo::field(a, this->password, "password");
        Wt::Dbo::field(a, this->role, "role");
    }
};

class Spot {
  public:
    // Information saved to db.
    Wt::WString name;
    Wt::WDate day;
    Wt::WTime start;
    Wt::WTime end;

    // Allows different sql actions when calling persist.
    template <class Action>
    void persist(Action &a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::field(a, day, "day");
        Wt::Dbo::field(a, start, "start");
        Wt::Dbo::field(a, end, "end");
    }
};
