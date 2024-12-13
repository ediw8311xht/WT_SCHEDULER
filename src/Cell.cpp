#include "Cell.h"
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

// Getter for date_
WDate Cell::date() {
    return date_;
}

// This is for showing dialogue when adding new appointment.
// Not implemented yet.
void Cell::showAddNew() {
    dialog_ = std::make_unique<Wt::WDialog>();
}

// Only called if user is logged in.
// Shows buttons to add appointment.
void Cell::add_admin_buttons() {
    auto add_button   = addWidget(std::make_unique<Wt::WPushButton>("Add"));
    // Prevent children element from recieving button click event.
    add_button->clicked().preventPropagation();
    // Connect click, to callback.
    add_button->clicked().connect(this, &Cell::showAddNew);
}

// This updates `Cell` of Calendar.
void Cell::update(const WDate& date, Wt::Dbo::ptr<Day> day_spots, bool logged_in) {
    // Setting date_
    date_ = date;
    // Clear `Cell` contents
    // provided from the inherited class WContainerWidget.
    clear();
    // Current day.
    WString day = std::to_string(date.day());
    // Creates header showing the date of cell.
    // addWidget provided from the inherited class WContainerWidget.
    // returns pointer to Widget added.
    auto header = addWidget(std::make_unique<WText>(day));
    if (logged_in) {
        add_admin_buttons();
    }
}

// Take constructor, resizing to 100,120 for now.
// Need to write CSS/figure out styling to adjust for appointment(s) in calendar.
Cell::Cell() : WContainerWidget() {
    resize(100, 120);
}

