#pragma once
#include "Models.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WCalendar.h>
#include <Wt/WDialog.h>

using namespace Wt;

class Cell : public WContainerWidget {
    private:
        WDate date_;
        // unique_ptr so dialog will be deleted when out of use.
        std::unique_ptr<WDialog> dialog_;
    public:
        Cell();
        WDate date();
        void update(const WDate& date, Dbo::ptr<Day> days, bool logged_in);
        void add_admin_buttons();
        void showAddNew();
};
