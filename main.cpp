extern "C" {
#include "mainwindow.h"

}
#include "editor.h"
#include <cstdio>

int main(int argc, char** argv ) {

    int closed_state = 0; //just stores what to do next
    closed_state = newwindow(argc, argv, &closed_state);
    switch (closed_state) {
        default:
            puts("WTFFFFF\n");
            return 69;
        break;
        case 0 :
            puts("WTF\n");
        break;
        case 1:
            return 0;
        break;
        case 2:
            Editor *editor = new Editor();
            editor->neweditor(argc, argv);
        break;
    }

}
