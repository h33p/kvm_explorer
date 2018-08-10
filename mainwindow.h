#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vmread/hlapi/hlapi.h"
#include <QMainWindow>
#define private public
#include "qhexedit2/src/qhexedit.h"
#undef private

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_refreshButton_clicked();

	void on_processList_currentIndexChanged(int index);

	void on_refreshPaged_clicked();

	void on_moduleList_cellClicked(int row, int column);

	void on_dumpModule_clicked();

	void on_findPattern_clicked();

	void on_curAddress_returnPressed();

    void on_processName_returnPressed();

private:
	Ui::MainWindow *ui;
	QHexEdit* hexEdit;

	void reloadHex(uintptr_t address, uintptr_t size);
};

#endif // MAINWINDOW_H
