#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sstream"
#include "kvm-rpm/utils/memory.h"
#include "kvm-rpm/utils/win_translate.h"
#include "kvm-rpm/utils/pattern_scan.h"
#include <QFile>
#include <QFileDialog>

extern win_context* g_ctx;

int currow = 0;
int curcolumn = 0;
uintptr_t pprocess = 0;
uintptr_t vprocess = 0;
p_data data2;

void RefreshList(win_process** process_list, QComboBox* combo)
{
	if (*process_list)
		free_process_list(*process_list);
	*process_list = get_process_list(g_ctx);
	QStringList pList = QStringList();

	win_process* p = *process_list;
	while (p) {
		std::stringstream stream;
		stream << "[" << p->pid << "] " << p->name << " (" << std::hex << p->phys_address << "; " << p->virt_address << ")";
		pList << stream.str().c_str();
		p = p->next;
	}
	combo->clear();
	combo->addItems(pList);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	hexEdit = new QHexEdit();
	process_list = NULL;
	ui->setupUi(this);
	ui->hexWidget->setWidget(hexEdit);
	RefreshList(&process_list, ui->processList);
}

MainWindow::~MainWindow()
{
	if (process_list)
		free_process_list(process_list);
	delete ui;
}


void MainWindow::on_refreshButton_clicked()
{
	RefreshList(&process_list, ui->processList);
}

void MainWindow::on_processList_currentIndexChanged(int index)
{
	uintptr_t pid;
	char name[16];
	sscanf(ui->processList->itemText(index).toLatin1().data(), "[%lu] %s (%lx; %lx)", &pid, name, &pprocess, &vprocess);
	int module_count = 0;
	ldr_module_ll* modules = get_memory_modules(g_ctx, vprocess, &module_count, 0);
	ui->moduleList->setRowCount(module_count);
	ui->moduleList->setColumnCount(3);

	uintptr_t dir_base;
	read_virtual_data(g_ctx->data, vprocess + g_ctx->offsets.dir_base, &dir_base, sizeof(uintptr_t));

	data2 = g_ctx->data;
	data2.dir_base = dir_base;

	QHeaderView* theader = ui->moduleList->horizontalHeader();
	theader->setSectionResizeMode(QHeaderView::Stretch);

	QStringList header;
	header << "Name" << "Start" << "End";

	ui->moduleList->setHorizontalHeaderLabels(header);

	int i = 0;
	while(modules && i < module_count) {
		ui->moduleList->setItem(i, 0, new QTableWidgetItem(modules->name));
		ui->moduleList->setItem(i, 1, new QTableWidgetItem(QString::number(modules->mod.base_address, 16)));
		ui->moduleList->setItem(i, 2, new QTableWidgetItem(QString::number(modules->mod.base_address + modules->mod.size_of_image, 16)));
		modules = modules->next;
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
		uintptr_t naddr = translate_address(addr, data2);

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
	char* buf = NULL;
	read_memory_region(&buf, start, end, data2);
	QString filename = QFileDialog::getSaveFileName(this, "Dump Module", "~/Documents", "Executables (*.dll *.exe)");
	QFile f(filename);
	f.open(QIODevice::WriteOnly);
	f.write(buf, (end - start));
	f.close();
}

void MainWindow::reloadHex(uintptr_t address, uintptr_t size = 16)
{
	char buf[4096];
	if (read_full_page(buf, address, data2))
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
	uintptr_t address = pattern_scan_s(ui->patternField->text().toLatin1(), data2, caddr, end, 0);
	if (!address)
		address = pattern_scan_s(ui->patternField->text().toLatin1(), data2, start, end, 0);

	reloadHex(address, (spaceCount(ui->patternField->text().toLatin1()) + 1));
}

void MainWindow::on_curAddress_returnPressed()
{
	uintptr_t addr = ui->curAddress->text().toLong(nullptr, 16);
	reloadHex(addr);
}
