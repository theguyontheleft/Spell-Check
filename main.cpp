/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-27-13
 *
 *    Main Implementation File
 */

#include <QtGui/QApplication>
#include "dictionarygui.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dictionaryGUI w;
    w.show();
    /* The return runs anytime something is changed in the GUI
     * This allows the main to be only a small number of lines
     */
    return a.exec();
}
