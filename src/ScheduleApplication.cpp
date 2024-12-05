#include "ScheduleApplication.h"
#include "Models.h"
#include "Calendar.h"

ScheduleApplication::ScheduleApplication(const WEnvironment &env)
    : WApplication(env) {

    auto sqlite3 = std::make_unique<Dbo::backend::Sqlite3>("schedule.db");
    sqlite3->setProperty("show-queries", "true");
    session.setConnection(std::move(sqlite3));

    session.mapClass<Spot>("Spot");
    session.mapClass<User>("User");

    Dbo::Transaction transaction(session);
    try {
        session.createTables();
        log("info") << "Database created";
    } catch (...) {
        log("info") << "Using existing database";
    }
    // Handle urls
    _content = 0;
    internalPathChanged().connect(this,
                                  &ScheduleApplication::onInternalPathChange);
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
    map<string, int> test = {{"HI", 9}};
    // test.contains("HI");
    // if ( url_map.contains(internalPath()) ) {
    //     renderThis(internalPath());
    // }
    // else {
    //     renderThis("404");
    // }
}
void ScheduleApplication::navbar() {
    auto button = root()->addWidget(make_unique<Wt::WPushButton>("Admin"));
    button->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/admin"));
}
void ScheduleApplication::calendar() {
    content()->addWidget(make_unique<Calendar>());
}
void ScheduleApplication::admin() {
    content()->addWidget(make_unique<WText>("<h1>Not implemented</h1>"));
}
void ScheduleApplication::e404() {
    content()->addWidget(make_unique<WText>("<h1>my404</h1>"));
}
