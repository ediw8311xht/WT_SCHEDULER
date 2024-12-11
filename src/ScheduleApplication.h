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

/*--------------------------------------------------------------------------------------*/
/*------------------APPLICATION---------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
class ScheduleApplication : public WApplication {
  private:
    WContainerWidget *_content;
    WLogger logger;
    void renderThis(string s);

  public:
    MySession session_;

    map<string, void (ScheduleApplication::*)()> url_map = {
        {"",            &ScheduleApplication::calendar   },
        {"/",           &ScheduleApplication::calendar   },
        {"calendar",    &ScheduleApplication::calendar   },

        {"login",       &ScheduleApplication::login_page },
        {"404",         &ScheduleApplication::e404       },
    };
    vector<vector<string>> nav_buttons = {
        { "login",         "/login",  "nav_login"    },
        { "logout",        "/logout", "nav_logout"   },
        { "View Calendar", "/",       "nav_view"     },
        { "Edit Calendar", "/edit",   "nav_edit"     },
    };
    WContainerWidget *content();
    WContainerWidget *nav_container;

    ScheduleApplication(const WEnvironment &env);

    static ScheduleApplication *scheduleApplication();
    void onAuthEvent();
    void onInternalPathChange();
    void init_navbar();
    void update_navbar();
    void calendar();
    void login_page();
    void e404();
    void adminPage();
};
/*--------------------------------------------------------------------------------------*/
/*------------------START-POINT---------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/
