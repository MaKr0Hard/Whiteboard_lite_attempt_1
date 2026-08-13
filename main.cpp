extern "C" {
#include "mainwindow.h"

}
#include "editor.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv ) {
    #if defined(__linux__) || defined(__unix__)
    setenv("GDK_BACKEND", "x11", 1);
    #endif
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
