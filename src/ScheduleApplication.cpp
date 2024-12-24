#include "ScheduleApplication.h"
#include "Calendar.h"
#include "MyAuthWidget.h"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

ScheduleApplication::ScheduleApplication(const WEnvironment &env)
    : WApplication(env) {
    session_.login().changed().connect(this, &ScheduleApplication::onAuthEvent);
    _content = 0;
    // Handle internalPathChanges. Note: This only handles when signal is sent from within application.
    // Users manually going to a specific suburl won't work. (as far as I know)
    internalPathChanged().connect(this, &ScheduleApplication::onInternalPathChange);
    // Create navbar.
    init_navbar();
    // Default Page
    renderThis("");
}
void ScheduleApplication::renderThis(string s) { invoke(url_map.at(s), this); }

// Method for getting and setting _content
WContainerWidget *ScheduleApplication::content() {
    if (_content == 0) {
        _content = root()->addNew<Wt::WContainerWidget>();
        _content->setId("content");
    }
    return _content;
}

/// Return current instance.
ScheduleApplication *ScheduleApplication::scheduleApplication() {
    return (ScheduleApplication *)WApplication::instance();
}
void ScheduleApplication::onInternalPathChange() {
    content()->clear();
    // Used to get correct internalPath
    std::string p = internalPathNextPart("/");

    // Just updated map instead whatever 
    // Handle weirdness with `internalPath` changes
    /*if (p == "/") { p = ""; }*/

    std::cout << "Path: '" << p << "'" << std::endl;
    // Specific callback dependent on matched string in url_map
    if ( url_map.contains(p) ) {
        renderThis(p);
    }
    else {
        // Render 404 if internalPath not found in url_map
        renderThis("404");
    }
}
void ScheduleApplication::init_navbar() {
    nav_container = root()->addWidget(make_unique<Wt::WContainerWidget>());
    for (auto& i : nav_buttons) {
        // create the button, pointer to button assigned to `button` var
        auto button = nav_container->addWidget(make_unique<Wt::WPushButton>(i.at(0)));
        // Sets redirection to
        button->setLink(Wt::WLink(Wt::LinkType::InternalPath, i.at(1)));
        // Setting object name, allows finding and referencing later from within application
        button->setObjectName(i.at(2));
    }
    update_navbar();
}
// Show/Hide correct buttons depending on login state.
void ScheduleApplication::update_navbar() {
    auto logout_button = nav_container->find("nav_logout");
    auto login_button  = nav_container->find("nav_login");
    auto edit_button   = nav_container->find("nav_edit");
    if (session_.login().loggedIn()) {
        login_button->hide();
        logout_button->show();
        edit_button->show();
    }
    else {
        login_button->show();
        logout_button->hide();
        edit_button->hide();
    }
}
// For Calendar page.
void ScheduleApplication::calendar() {
    content()->addWidget(make_unique<Calendar>(&session_));
}
void ScheduleApplication::edit_calendar() {
    auto g = make_unique<Calendar>(&session_);
    g->edit_on();
    content()->addWidget(std::move(g));
}
// For Login/Registration page.
void ScheduleApplication::login_page() {
    auto authWidget = std::make_unique<MyAuthWidget>(session_, "/login");
    content()->addWidget(std::move(authWidget));
}
// For Logout page.
// Uses same method as login (MyAuthWidget), but being explicit since I may want to modify later).
void ScheduleApplication::logout_page() {
    auto authWidget = std::make_unique<MyAuthWidget>(session_, "/logout");
    content()->addWidget(std::move(authWidget));
}
// 404 page, `e404` since can't start with number
void ScheduleApplication::e404() {
    content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
}
// Not implemented yet. Just for testing internal path.
void ScheduleApplication::adminPage() {
    content()->addWidget(make_unique<WText>("<h1>HI</h1>"));
}
// Called when user login changes. Refreshes page and updates content.
void ScheduleApplication::onAuthEvent() {
    // Clear content.
    content()->clear();
    // Update buttons
    update_navbar();
    // Reset internal path back to home.
    // setInternalPath takes 2nd argument (default false), to send signal on change.
    // setting to true so that content will be re-rendered (sent to my onInternalPathChanged handler).
    setInternalPath("", true);
}


