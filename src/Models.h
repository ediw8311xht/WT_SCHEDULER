#pragma once

#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

#include <Wt/Dbo/Dbo.h>


#include <Wt/WDate.h>
#include <Wt/WTime.h>

#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

class User;
using AuthInfo     = Wt::Auth::Dbo::AuthInfo<User>;
using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;


class User {
  public:

    // Allows different sql actions when calling persist.
    template <class Action>
    void persist(Action &a) {
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
        Wt::Auth::Login& login();
        const Wt::Auth::AuthService& auth();
        const Wt::Auth::PasswordService& passwordAuth();
};


