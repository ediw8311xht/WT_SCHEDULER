#include "ScheduleApplication.h"
#include "Calendar.h"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

ScheduleApplication::ScheduleApplication(const WEnvironment &env)
    : WApplication(env), session_() {

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
    if (session_.login().loggedIn()) {
    }
    else {
    }
    content()->addWidget(make_unique<WText>("<h1>Not implemented</h1>"));
}
void ScheduleApplication::authWidget() {
    auto authWidget = std::make_unique<Wt::Auth::AuthWidget>(MySession::auth(), session_.users(), session_.login());

    authWidget->model()->addPasswordAuth(&MySession::passwordAuth());
    authWidget->setRegistrationEnabled(true);

    authWidget->processEnvironment();

    root()->addWidget(std::move(authWidget));
}
void ScheduleApplication::e404() {
    content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
}
