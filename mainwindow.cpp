#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sstream"
#include <QFile>
#include <QFileDialog>
#include "framework/utils/pattern_scan.h"

extern WinContext* g_ctx;
WinProcess* proc = nullptr;

template<typename T, typename N>
T Read(N addr)
{
	return proc->Read<T>(addr);
}

template<typename T, typename N>
void ReadArr(N addr, T* arr, size_t count)
{
	VMemRead(&g_ctx->ctx.process, proc->proc.dirBase, (uint64_t)arr, addr, sizeof(T) * count);
}
template uintptr_t Read(uintptr_t);
template unsigned int Read(uintptr_t);
template int Read(uintptr_t);
template void ReadArr(uintptr_t, char*, size_t);

template<typename T, typename N>
T Write(N addr, T value)
{
	proc->Write(addr, value);
}


int currow = 0;
int curcolumn = 0;
uintptr_t pprocess = 0;
uintptr_t vprocess = 0;

void RefreshList(QComboBox* combo)
{
	QStringList pList = QStringList();

	g_ctx->processList.Refresh();
	for (auto& p : g_ctx->processList) {
		std::stringstream stream;
		stream << "[" << p.proc.pid << "] " << p.proc.name << " (" << std::hex << p.proc.physProcess << "; " << p.proc.process << ")";
		pList << stream.str().c_str();
	}
	combo->clear();
	combo->addItems(pList);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	hexEdit = new QHexEdit();
	ui->setupUi(this);
	ui->hexWidget->setWidget(hexEdit);
	RefreshList(ui->processList);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_refreshButton_clicked()
{
	RefreshList(ui->processList);
}

void MainWindow::on_processList_currentIndexChanged(int index)
{
	uintptr_t pid;
	char name[16];
	sscanf(ui->processList->itemText(index).toLatin1().data(), "[%lu] %s (%lx; %lx)", &pid, name, &pprocess, &vprocess);
	int module_count = 0;

	proc = nullptr;
	for (auto& p : g_ctx->processList)
		if (p.proc.pid == pid) {
			proc = &p;
			break;
		}

	if (!proc)
		return;

	ui->moduleList->setRowCount(proc->modules.getSize());
	ui->moduleList->setColumnCount(3);

	QHeaderView* theader = ui->moduleList->horizontalHeader();
	theader->setSectionResizeMode(QHeaderView::Stretch);

	QStringList header;
	header << "Name" << "Start" << "End";

	ui->moduleList->setHorizontalHeaderLabels(header);
	
	int i = 0;
	for (auto& m : proc->modules) {
		ui->moduleList->setItem(i, 0, new QTableWidgetItem(m.info.name));
		ui->moduleList->setItem(i, 1, new QTableWidgetItem(QString::number(m.info.baseAddress, 16)));
		ui->moduleList->setItem(i, 2, new QTableWidgetItem(QString::number(m.info.baseAddress + m.info.sizeOfModule, 16)));
		i++;
	}
}

void MainWindow::on_refreshPaged_clicked()
{
	uintptr_t start = ui->moduleList->item(currow, 1)->text().toLong(nullptr, 16);
	uintptr_t end = ui->moduleList->item(currow, 2)->text().toLong(nullptr, 16);
	uintptr_t success_count = 0;
	uintptr_t try_count = 0;

	for (uintptr_t addr = (start & ~0xfff); addr < end; addr += 0x1000) {
		uintptr_t naddr = VTranslate(&g_ctx->ctx.process, proc->proc.dirBase, addr);

		if (naddr)
			success_count++;
		try_count++;
	}

	ui->amountUnpaged->setMaximum(try_count);
	ui->amountUnpaged->setValue(success_count);
}

void MainWindow::on_moduleList_cellClicked(int row, int column)
{
	currow = row;
	curcolumn = column;
}

void MainWindow::on_dumpModule_clicked()
{
	uintptr_t start = ui->moduleList->item(currow, 1)->text().toLong(nullptr, 16);
	uintptr_t end = ui->moduleList->item(currow, 2)->text().toLong(nullptr, 16);
	char* buf = (char*)malloc(end - start);
	VMemRead(&g_ctx->ctx.process, proc->proc.dirBase, (uint64_t)buf, start, end - start);
	QString filename = QFileDialog::getSaveFileName(this, "Dump Module", "~/Documents", "Executables (*.dll *.exe)");
	QFile f(filename);
	f.open(QIODevice::WriteOnly);
	f.write(buf, (end - start));
	f.close();
	free(buf);
}

void MainWindow::reloadHex(uintptr_t address, uintptr_t size = 16)
{
	char buf[4096];
	if (VMemRead(&g_ctx->ctx.process, proc->proc.dirBase, (uint64_t)buf, address & ~0xfff, 4096) < 0)
		memset(buf, 0, 4096);
	QByteArray data(buf, 4096);

	hexEdit->setAddressWidth(16);
	hexEdit->setData(data);
	hexEdit->setAddressOffset(address & ~0xfff);
	hexEdit->setCursorPosition(address & 0xfff);
	hexEdit->resetSelection((address & 0xfff) * 2);
	hexEdit->setSelection(((address + size) & 0xfff) * 2);

}

uintptr_t spaceCount(const char* text)
{
	char* t = (char*)text - 1;
	uintptr_t c = 0;
	while (*(++t) != '\0')
		if (*t == ' ')
			c++;
	return c;
}

void MainWindow::on_findPattern_clicked()
{
	uintptr_t start = ui->moduleList->item(currow, 1)->text().toLong(nullptr, 16);
	uintptr_t end = ui->moduleList->item(currow, 2)->text().toLong(nullptr, 16);

	uintptr_t caddr = ui->curAddress->text().toLong(nullptr, 16);
	uintptr_t address = PatternScan::FindPattern(ui->patternField->text().toLatin1(), caddr, end);
	if (!address)
		address = PatternScan::FindPattern(ui->patternField->text().toLatin1(), start, end);

	reloadHex(address, (spaceCount(ui->patternField->text().toLatin1()) + 1));
}

void MainWindow::on_curAddress_returnPressed()
{
	uintptr_t addr = ui->curAddress->text().toLong(nullptr, 16);
	reloadHex(addr);
}

void MainWindow::on_processName_returnPressed()
{
	char* str = strdup(ui->processName->text().toLatin1().data());

	int i = 0;
	for (auto& p : g_ctx->processList) {
		if (!strcmp(p.proc.name, str)) {
			ui->processList->setCurrentIndex(i);
			return;
		}
		i++;
	}
	free(str);
}
