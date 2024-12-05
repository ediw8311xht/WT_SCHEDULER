#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WCalendar.h>


using namespace Wt;

class Calendar : public WCalendar {
    protected:
        // Weird: Wt uses virtual on derived class method instead of in parent class method.
        virtual WWidget* renderCell(WWidget *widget, const WDate &date) override;
};
