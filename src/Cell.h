#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WCalendar.h>

using namespace Wt;

class Cell : public WContainerWidget {
    private:
        WDate date_;
    public:
        Cell();
        WDate date();
        void update(const WDate& date);
};