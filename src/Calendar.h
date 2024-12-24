#pragma once
#include "Models.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WCalendar.h>


using namespace Wt;

class Calendar : public WCalendar {
    public:
        Calendar(MySession* session);
        Dbo::ptr<Day> getDay(WDate gday);
        void edit_off() { this->show_edit = false ; }
        void edit_on()  { this->show_edit = true  ; }
    private:
        // Pointer to current session
        MySession* session_ = nullptr;
        bool show_edit = false;
    protected:
        // Weird: Wt uses virtual on derived class method instead of in parent class method.
        virtual WWidget* renderCell(WWidget *widget, const WDate &date) override;
};
