#include "Calendar.h"
#include "Cell.h"
#include "Models.h"

#include <Wt/WText.h>

// Use constructor from WCalendar, additionally take in session to attribute `session_`
Calendar::Calendar(MySession *session) : WCalendar(), session_(session) {
}

// This returns the `Day` from the database based on a date (Wt::WDate)
// If it doesn't find `Day` with specific date in database, it creates and empty `Day`
// And commits to database.
Wt::Dbo::ptr<Day> Calendar::getDay(Wt::WDate gday) {
    Wt::Dbo::Transaction t(*session_);
    Wt::Dbo::ptr<Day> g = session_->find<Day>("where date = ?").bind(gday);
    if (!g) {
        Wt::Dbo::ptr<Day> g = session_->add(std::make_unique<Day>(gday, Wt::WTime(), Wt::WTime(), Spots()));
    }
    t.commit();
    return g;
}

// This determines how each `Calendar` date is rendered.
// Uses `Cell` to implement each date.
// Takes pointer to WWidget (Cell) and the date (WDate)
WWidget *Calendar::renderCell(WWidget *widget, const WDate &date) {
    // If Cell doesn't exist create it.
    if (!widget) {
        widget = new Cell;
    }
    // Get the `Day` with the date
    // which contains `Spots` i.e. the appointment(s) information for the `Day`
    Wt::Dbo::ptr<Day> day_spots = getDay(date);

    // Cast to *Cell (only needed for when WWidget* is passed as not null)
    Cell *g = (Cell *)widget;
    // Update the Cell, passing the current `Day` for cell and whether the user is logged in or not.
    // Need to Update: Should use different code for view/edit calendar
    bool logged_in = session_->login().loggedIn();
    g->update(date, day_spots, logged_in);

    if (logged_in && show_edit) {
        g->add_admin_buttons();
    }
    return g;
}
