#include "Calendar.h"
#include "Cell.h"
#include "Models.h"

#include <Wt/WText.h>

Calendar::Calendar(MySession *session) : WCalendar(), session_(session) {
}

Wt::Dbo::ptr<Day> Calendar::getDay(Wt::WDate gday) {
    Wt::Dbo::Transaction t(*session_);
    Wt::Dbo::ptr<Day> g = session_->find<Day>("where date = ?").bind(gday);
    if (!g) {
        Wt::Dbo::ptr<Day> g = session_->add(std::make_unique<Day>(gday, Wt::WTime(), Wt::WTime(), Spots()));
    }
    t.commit();
    return g;
}

WWidget *Calendar::renderCell(WWidget *widget, const WDate &date) {
    if (!widget) {
        widget = new Cell;
    }
    Wt::Dbo::ptr<Day> day_spots = getDay(date);

    Cell *g = (Cell *)widget;
    g->update(date, day_spots);
    return g;
}
