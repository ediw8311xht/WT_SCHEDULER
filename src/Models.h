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

// Forward declaration to allow reference between classes
class User;
class Day;
using AuthInfo     = Wt::Auth::Dbo::AuthInfo<User>;
using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;


class User {
  public:

    // template Allows different sql actions when calling persist.
    template <class Action>
    void persist(Action &a) {
    }
};

class Spot {
  public:
    // Information saved to db.
    // Wt::Dbo::ptr is used to reference database class
    // Smart pointer so no need to deallocate
    // https://webtoolkit.eu/wt/doc/reference/html/classWt_1_1Dbo_1_1ptr.html
    Wt::Dbo::ptr<Day> day;
    Wt::WString       name;
    Wt::WTime         start;
    Wt::WTime         end;

    /*static Wt::Dbo::collection<Spot> getOnDay(Wt::WDate) {*/
    /*}*/

    template <class Action>
    void persist(Action &a) {
        Wt::Dbo::belongsTo( a , day   , "day"   );
        Wt::Dbo::field(     a , name  , "name"  );
        Wt::Dbo::field(     a , start , "start" );
        Wt::Dbo::field(     a , end   , "end"   );
    }
};

// A collection of poiner to appointments (Spot)
typedef Wt::Dbo::collection<Wt::Dbo::ptr<Spot>> Spots;
// Used to contain information regarding Date, start_time, end_time, and
// appointments (Spot).
// start_time and end_time correspond to min and max time for that day 
// for appointments.
class Day {
  public:
      Wt::WDate date;
      Wt::WTime start_time;
      Wt::WTime end_time;
      Spots spots;

    template <class Action>
    void persist(Action &a) {
        Wt::Dbo::field(   a , date       , "date"             );    
        Wt::Dbo::field(   a , start_time , "start_time"       );    
        Wt::Dbo::field(   a , end_time   , "end_time"         );    
        Wt::Dbo::hasMany( a , spots      , Wt::Dbo::ManyToOne , "day" );
    }
};

// Session
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


