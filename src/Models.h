#pragma once

#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

#include <Wt/Dbo/Dbo.h>


#include <Wt/WDate.h>
#include <Wt/WTime.h>

#include <string.h>

using std::string;

class User;
using AuthInfo     = Wt::Auth::Dbo::AuthInfo<User>;
using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

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
    string username;
    string password;
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

class MySession : public Wt::Dbo::Session {
    private:
        std::unique_ptr<UserDatabase> users_;
        Wt::Auth::Login login_;
    public:
        static void configureAuth();

        MySession();
        Wt::Auth::AbstractUserDatabase& users();
        Wt::Auth::Login& login() { return login_; }
        static const Wt::Auth::AuthService& auth();
        static const Wt::Auth::PasswordService& passwordAuth();
};


