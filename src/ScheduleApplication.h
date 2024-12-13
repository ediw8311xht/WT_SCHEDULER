#pragma once
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/SqlTraits.h>
#include <Wt/Dbo/WtSqlTraits.h> // WOW
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "Models.h"

using namespace Wt;
using std::function;
using std::invoke;
using std::make_unique;
using std::map;
using std::string;
using std::vector;

class ScheduleApplication : public WApplication {
  private:
    // Content container.
    WContainerWidget *_content;
    // Navigation bar container.
    WContainerWidget *nav_container;
    WLogger logger;
    // Calls the function associated with string found in url_map.
    void renderThis(string s);
  public:
    MySession session_;

    // InternalPaths and the callback to run.
    map<string, void (ScheduleApplication::*)()> url_map = {
        {"",            &ScheduleApplication::calendar   },
        {"/",           &ScheduleApplication::calendar   },
        {"calendar",    &ScheduleApplication::calendar   },

        {"login",       &ScheduleApplication::login_page  },
        {"logout",      &ScheduleApplication::logout_page },
        {"404",         &ScheduleApplication::e404        },
    };
    // Nav button Text, InternalPath to redirect to, and name
    // Name is used for internally finding and referencing Widgets in Wt.
    vector<vector<string>> nav_buttons = {
        { "login",         "/login",  "nav_login"    },
        { "logout",        "/logout", "nav_logout"   },
        { "View Calendar", "/",       "nav_view"     },
        { "Edit Calendar", "/edit",   "nav_edit"     },
    };
    WContainerWidget *content();

    ScheduleApplication(const WEnvironment &env);

    static ScheduleApplication *scheduleApplication();
    void onAuthEvent();
    void onInternalPathChange();
    void init_navbar();
    void update_navbar();
    void calendar();
    void login_page();
    void logout_page();
    void e404();
    void adminPage();
};
