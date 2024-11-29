#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCalendar.h>
#include <Wt/WTime.h>
#include <Wt/WDate.h>
#include <Wt/WLogger.h>
#include <cstdlib>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/SqlTraits.h>
#include <Wt/Dbo/WtSqlTraits.h> // WOW
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using std::vector;
using std::string;
using std::map;
using namespace Wt;
using namespace Wt::Dbo;

namespace dbo = Wt::Dbo;
enum class Role {
    Visitor = 0,
    User = 1,
    Admin = 2,
};


class Spot {
    public:
        WString name;
        WDate day;
        WTime start;
        WTime end;
        template <class Action>
        void persist(Action& a) {
            dbo::field( a, name,  "name"  );
            dbo::field( a, day,   "day"   );
            dbo::field( a, start, "start" );
            dbo::field( a, end,   "end"   );
        }
};

// class Schedule {
//     public:
//         dbo::collection<Spot> times = {};
//         template <class Action>
//         void persist(Action& a) {
//             for (auto i : times) {
//                 i.persist(a);
//             }
//         }
// };


class User {
    public:
        string username;
        string password;
        Role role;
        template <class Action>
        void persist(Action& a) {
            dbo::field( a, this->username,  "username"  );
            dbo::field( a, this->password,  "password"  );
            dbo::field( a, this->role,      "role"      );
        }
};
        



// Just testing out stuff at the moment.
// Working from PlannerCalendar example from Wt codebase.

class Cell : public WContainerWidget {
    private:
        WDate date_;
    public:
        WDate date() { return date_; }
        Cell() : WContainerWidget() {
            resize(100, 120);
        }
        void update(const WDate& date) {
            date_ = date;
            clear();
            WString day = std::to_string(date.day());
            auto header = std::make_unique<WText>(day);
            addWidget(std::move(header));
        }
};

class Calendar : public WCalendar {
    protected:
        virtual WWidget* renderCell(WWidget *widget, const WDate &date) override {
            if (!widget) {
                widget = new Cell;
            }
            Cell* g = (Cell*)widget;
            g->update(date);
            return g;
        }
};

class ScheduleApplication : public WApplication {
    public:
        dbo::Session session;
        ScheduleApplication(const WEnvironment& env);
        static ScheduleApplication* scheduleApplciation() {
            return (ScheduleApplication*)WApplication::instance();
        }
};

ScheduleApplication::ScheduleApplication(const WEnvironment& env)
    : WApplication(env)
{
    auto sqlite3 = std::make_unique<dbo::backend::Sqlite3>("schedule.db");
    sqlite3->setProperty("show-queries", "true");
    session.setConnection(std::move(sqlite3));

    session.mapClass<Spot>("Spot");

    dbo::Transaction transaction(session);
    try {
        session.createTables();
        log("info") << "Database created";
    } catch(...) {
        log("info") << "Using existing database";
    }
    root()->clear();
    root()->addWidget(std::make_unique<Calendar>());
}

/*----------------------------START----------------------*/
std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<ScheduleApplication>(env);
}

int main(int argc, char **argv)
{
    std::srand(std::time(0));
    return WRun(argc, argv, &createApplication);
}
