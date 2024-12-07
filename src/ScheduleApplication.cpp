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

    // Handle urls
    _content = 0;
    internalPathChanged().connect(this, &ScheduleApplication::onInternalPathChange);
    // Default Page
    navbar();
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
    if ( url_map.contains(internalPath()) ) {
        renderThis(internalPath());
    }
    else {
        renderThis("404");
    }
}
void ScheduleApplication::navbar() {
    auto button = root()->addWidget(make_unique<Wt::WPushButton>("Admin"));
    button->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/admin"));
}
void ScheduleApplication::calendar() {
    content()->addWidget(make_unique<Calendar>());
}
void ScheduleApplication::admin() {
    auto authWidget = std::make_unique<MyAuthWidget>(session_, "/login");
    
    if (session_.login().loggedIn()) {
        adminPage();
    }
    else {
        content()->addWidget(std::move(authWidget));
    }
}
void ScheduleApplication::e404() {
    content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
}

void ScheduleApplication::adminPage() {
}


