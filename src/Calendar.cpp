#include "Calendar.h"
#include "Cell.h"
#include "Models.h"

#include <Wt/WText.h>

Calendar::Calendar(MySession *session) : WCalendar(), session_(session) {
}

WWidget *Calendar::renderCell(WWidget *widget, const WDate &date) {
    if (!widget) {
        widget = new Cell;
    }

    Cell *g = (Cell *)widget;
    g->update(date);
    return g;
}
