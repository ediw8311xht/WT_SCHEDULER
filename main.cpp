#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCalendar.h>
#include <Wt/WDate.h>
#include <Wt/WLogger.h>
#include <cstdlib>


using namespace Wt;

// Just testing out stuff at the moment.
// Working from PlannerCalendar example from Wt codebase.

class Cell : public WContainerWidget {
    private:
        WDate date_;
    public:
        WDate date() { return date_; }
        Cell() : WContainerWidget() {
            resize(100, 120);
        }
        void update(const WDate& date) {
            date_ = date;
            clear();
            WString day = std::to_string(date.day());
            auto header = std::make_unique<WText>(day);
            addWidget(std::move(header));
        }
};

class Calendar : public WCalendar {
    protected:
        virtual WWidget* renderCell(WWidget *widget, const WDate &date) override {
            if (!widget) {
                widget = new Cell;
            }
            Cell* g = (Cell*)widget;
            g->update(date);
            return g;
        }
};

/*
 * Copyright (C) 2008 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

class PlannerApplication : public WApplication {
    public:
        PlannerApplication(const WEnvironment& env)
          : WApplication(env)
        {
          root()->clear();
          root()->addWidget(std::make_unique<Calendar>());
        }
};

std::unique_ptr<WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<PlannerApplication>(env);
}
int main(int argc, char **argv)
{
    std::srand(std::time(0));
    return WRun(argc, argv, &createApplication);
}
