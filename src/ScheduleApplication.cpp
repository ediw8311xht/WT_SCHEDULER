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
    // Handle urls
    internalPathChanged().connect(this, &ScheduleApplication::onInternalPathChange);
    // Default Page
    init_navbar();
    renderThis("");
}
void ScheduleApplication::renderThis(string s) { invoke(url_map.at(s), this); }
WContainerWidget *ScheduleApplication::content() {
    if (_content == 0) {
        _content = root()->addNew<Wt::WContainerWidget>();
        _content->setId("content");
    }
    return _content;
}

ScheduleApplication *ScheduleApplication::scheduleApplication() {
    return (ScheduleApplication *)WApplication::instance();
}
void ScheduleApplication::onInternalPathChange() {
    content()->clear();
    std::string p = internalPathNextPart("/");

    // Just updated map instead whatever 
    // Handle weirdness with `internalPath` changes
    /*if (p == "/") { p = ""; }*/

    std::cout << "Path: '" << p << "'" << std::endl;
    if ( url_map.contains(p) ) {
        renderThis(p);
    }
    else {
        renderThis("404");
    }
}
void ScheduleApplication::init_navbar() {
    nav_container = root()->addWidget(make_unique<Wt::WContainerWidget>());
    for (auto& i : nav_buttons) {
        auto button = nav_container->addWidget(make_unique<Wt::WPushButton>(i.at(0)));
        button->setLink(Wt::WLink(Wt::LinkType::InternalPath, i.at(1)));
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
        login_button->hide();
        logout_button->show();
        edit_button->show();
    }
}
void ScheduleApplication::calendar() {
    content()->addWidget(make_unique<Calendar>(&session_));
}
void ScheduleApplication::login_page() {
    auto authWidget = std::make_unique<MyAuthWidget>(session_, "/login");
    content()->addWidget(std::move(authWidget));
}
void ScheduleApplication::e404() {
    content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
}

void ScheduleApplication::adminPage() {
    content()->addWidget(make_unique<WText>("<h1>HI</h1>"));
}
void ScheduleApplication::onAuthEvent() {
    if (session_.login().loggedIn()) {
        adminPage();
    }
    else {
        content()->clear();
        update_navbar();
        setInternalPath("");
    }
}


