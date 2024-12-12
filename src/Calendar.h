#pragma once
#include "Models.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WCalendar.h>


using namespace Wt;

class Calendar : public WCalendar {
    public:
        Calendar(MySession* session);
        Wt::Dbo::ptr<Day> getDay(Wt::WDate gday);
    private:
        MySession* session_ = nullptr;
    protected:
        // Weird: Wt uses virtual on derived class method instead of in parent class method.
        virtual WWidget* renderCell(WWidget *widget, const WDate &date) override;
};
