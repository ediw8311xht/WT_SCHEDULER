#include "Cell.h"
#include <Wt/WText.h>

WDate Cell::date() {
    return date_;
}
void Cell::update(const WDate& date) {
    date_ = date;
    clear();
    WString day = std::to_string(date.day());
    auto header = std::make_unique<WText>(day);
    addWidget(std::move(header));
}

Cell::Cell() : WContainerWidget() {
    resize(100, 120);
}

