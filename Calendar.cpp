#include "Cell.h"
#include "Calendar.h"

WWidget *Calendar::renderCell(WWidget *widget, const WDate &date) {
    if (!widget) {
        widget = new Cell;
    }

    Cell *g = (Cell *)widget;
    g->update(date);
    return g;
}
