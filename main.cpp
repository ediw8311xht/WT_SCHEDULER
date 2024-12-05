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
#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <Wt/WPushButton.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>


/*--------------------------------------------------------------------------------------*/
/*------------------TESTING-ONLY--------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
#include <iostream>
using std::cout;
using std::endl;
/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

using std::make_unique;
using std::invoke;
using std::function;
using std::vector;
using std::string;
using std::map;
using namespace Wt;


/*--------------------------------------------------------------------------------------*/
/*------------------DATABASE------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
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
/*--------------------------------------------------------------------------------------*/
/*------------------CALENDAR------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
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
            if (!widget) { widget = new Cell; }

            Cell* g = (Cell*)widget;
            g->update(date);
            return g;
        }
};
/*--------------------------------------------------------------------------------------*/
/*------------------APPLICATION---------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
class ScheduleApplication : public WApplication {
    private:
        WContainerWidget* _content;
        Wt::WLogger logger;
        void renderThis(string s) {
            invoke(url_map.at(s), this);
        }
    public:
        map <string, void(ScheduleApplication::*)()> url_map = {
            { "",            &ScheduleApplication::calendar },
            { "/admin",      &ScheduleApplication::admin    },
            { "calendar",    &ScheduleApplication::calendar },
            { "404",         &ScheduleApplication::e404     },
        };
        dbo::Session session;
        WContainerWidget* content() {
            if (_content == 0) {
                _content = root()->addNew<Wt::WContainerWidget>();
                _content->setId("content");
            }
            return _content;
        }

        ScheduleApplication(const WEnvironment& env);

        static ScheduleApplication* scheduleApplciation() {
            return (ScheduleApplication*)WApplication::instance();
        }
        void onInternalPathChange() {
            content()->clear();
            if ( url_map.contains(internalPath()) ) {
                renderThis(internalPath());
            }
            else {
                renderThis("404");
            }
        }
        void navbar() {
            auto button = root()->addWidget(make_unique<Wt::WPushButton>("Admin"));
            button->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/admin"));
        }
        void calendar() {
            content()->addWidget(make_unique<Calendar>());
        }
        void admin() {
            content()->addWidget(make_unique<WText>("<h1>Not implemented</h1>"));
        }
        void e404() {
            content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
        }
};
/*--------------------------------------------------------------------------------------*/
/*------------------START-POINT---------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
ScheduleApplication::ScheduleApplication(const WEnvironment& env) : WApplication(env) {

    //---------LOGGING---------//
    logger.addField("datetime", false);
    logger.addField("session", false);
    logger.addField("type", false);
    logger.addField("message", true);
    //-------------------------//

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
    // Handle urls
    _content = 0;
    internalPathChanged().connect(this, &ScheduleApplication::onInternalPathChange);
    // Default Page
    navbar();
    renderThis("");
}
/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
std::unique_ptr<WApplication> create(const WEnvironment& env) {
    return std::make_unique<ScheduleApplication>(env);
}

int main(int argc, char **argv) {
    std::srand(std::time(0));
    return WRun(argc, argv, &create);
}
