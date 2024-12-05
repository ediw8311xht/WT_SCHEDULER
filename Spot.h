#pragma once
#include <Wt/Dbo/Dbo.h>
#include <Wt/WDate.h>
#include <Wt/WTime.h>

class Spot {
  public:
    // Information saved to db.
    Wt::WString name;
    Wt::WDate day;
    Wt::WTime start;
    Wt::WTime end;

    // Allows different sql actions when calling persist.
    template <class Action> void persist(Action &a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::field(a, day, "day");
        Wt::Dbo::field(a, start, "start");
        Wt::Dbo::field(a, end, "end");
    }
};
