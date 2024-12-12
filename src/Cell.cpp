#include "Cell.h"
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

WDate Cell::date() {
    return date_;
}
void Cell::showAddNew() {
    dialog_ = std::make_unique<Wt::WDialog>();
}
void Cell::add_admin_buttons() {
    auto add_button   = addWidget(std::make_unique<Wt::WPushButton>("Add"));
    add_button->clicked().preventPropagation();
    add_button->clicked().connect(this, &Cell::showAddNew);
}
void Cell::update(const WDate& date, Wt::Dbo::ptr<Day> day_spots, bool logged_in) {
    date_ = date;
    clear();
    WString day = std::to_string(date.day());
    auto header = addWidget(std::make_unique<WText>(day));
    if (logged_in) {
        add_admin_buttons();
    }
    /*addWidget(std::move(header));*/
}

Cell::Cell() : WContainerWidget() {
    resize(100, 120);
}

