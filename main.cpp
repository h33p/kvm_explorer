#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>

WinContext* g_ctx = NULL;

int main(int argc, char *argv[])
{
        pid_t pid;
        FILE* pipe = popen("pidof qemu-system-x86_64", "r");
        fscanf(pipe, "%d", &pid);
        pclose(pipe);

	WinContext ctx(pid);
	g_ctx = &ctx;

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
