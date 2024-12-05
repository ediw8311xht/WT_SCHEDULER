#include "Calendar.h"
#include "Cell.h"

#include <Wt/WText.h>

WWidget *Calendar::renderCell(WWidget *widget, const WDate &date) {
    if (!widget) {
        widget = new Cell;
    }

    Cell *g = (Cell *)widget;
    g->update(date);
    return g;
}
