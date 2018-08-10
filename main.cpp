#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>

win_context* g_ctx = NULL;

int main(int argc, char *argv[])
{
	win_context ctx;
	ctx.data.pid = 2777;
	g_ctx = &ctx;
	initialize_context(g_ctx, ctx.data.pid, 100);


    QApplication a(argc, argv);
	MainWindow w;
    w.show();

    return a.exec();
}
