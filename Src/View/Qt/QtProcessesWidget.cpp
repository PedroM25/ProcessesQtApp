#include "QtProcessesWidget.h"

#include <cstring>

QtProcessesWidget::QtProcessesWidget(QWidget* parent, std::unique_ptr<ProcessesController> processesController)
	: QWidget(parent)
	, m_processesController(std::move(processesController))
{
	// search bar
	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setPlaceholderText("Filter by Command");
	m_lineEdit->setClearButtonEnabled(true);

	connect(m_lineEdit, &QLineEdit::textEdited, this, &QtProcessesWidget::handleFilterChange);

	// table
	m_tableWidget = new QTableWidget(m_maxNumAllProcesses, 4, this);
	m_tableWidget->setColumnWidth(0, 60); // PID column width
	m_tableWidget->setColumnWidth(2, 295); // Command column width
	m_tableWidget->setColumnWidth(3, 60); // Kill process column width
	QStringList headers = {Column1, Column2, Column3, Column4};
	m_tableWidget->setHorizontalHeaderLabels(headers);
	m_tableWidget->verticalHeader()->hide();

	// label
	m_currNumProcessesRunning = new QLabel{this};

	// layout to HOLD everything
	QVBoxLayout* layout = new QVBoxLayout{this};
	layout->addWidget(m_lineEdit);
	layout->addWidget(m_tableWidget);
	layout->addWidget(m_currNumProcessesRunning);
	setLayout(layout);

	qRegisterMetaType<AddRemoveProcsStruct>();
	connect(this, &QtProcessesWidget::updateWidget, this, &QtProcessesWidget::handleUpdateWidget);

	m_processesController->startGetProcessesInfoThread([ptrThis = QPointer(this)](auto diff, auto numAllProcesses){
		if (ptrThis){
			emit ptrThis->updateWidget(diff, numAllProcesses);
		}
	});
}

void QtProcessesWidget::clearAndPopulateTableWithProcessesToShow(AddRemoveProcsStruct diff)
{
	std::vector<int> rowsToRemove;
	// first, remove old elements
	for (int i = 0; i < m_tableWidget->rowCount(); i++)
	{
		// HACK to make us of O(log(n)) search
		ProcessInfo currTableProc = ProcessInfo(
			m_tableWidget->item(i, PidColumn)->data(Qt::DisplayRole).toInt(),
			m_tableWidget->item(i, UserColumn)->data(Qt::DisplayRole).toString().toStdString(),
			m_tableWidget->item(i, CommandColumn)->data(Qt::DisplayRole).toString().toStdString());
		if (diff.getToRemove().find(currTableProc) != diff.getToRemove().end()) // PEDRO: the BUG was that these two would be different
		{
			rowsToRemove.push_back(i);
		}
	}
	for (auto it = rowsToRemove.rbegin(); it != rowsToRemove.rend(); ++it)
	{
		m_tableWidget->removeRow(*it);
	}

	// second, add new ones
	int i = m_tableWidget->rowCount();
	for (const auto& newProc : diff.getToAdd())
	{
		m_tableWidget->insertRow(i);

		QTableWidgetItem* pidCell = new QTableWidgetItem;
		pidCell->setData(Qt::EditRole, newProc.getPID());
		pidCell->setFlags(pidCell->flags() ^ Qt::ItemIsEditable);
		m_tableWidget->setItem(i, PidColumn, pidCell); // pid

		QTableWidgetItem* userCell = new QTableWidgetItem(QString::fromStdString(newProc.getUser()));
		userCell->setFlags(userCell->flags() ^ Qt::ItemIsEditable);
		m_tableWidget->setItem(i, UserColumn, userCell); // user

		QTableWidgetItem* commandCell = new QTableWidgetItem(QString::fromStdString(newProc.getCommand()));
		commandCell->setFlags(commandCell->flags() ^ Qt::ItemIsEditable);
		m_tableWidget->setItem(i, CommandColumn, commandCell); // command

		QPushButton* button = new QPushButton(ButtonKillLabel);
		connect(button, &QPushButton::clicked, this, &QtProcessesWidget::handleKillClick);
		m_tableWidget->setCellWidget(i, KillColumn, button); // kill
		i++;
	}

	m_tableWidget->sortByColumn(0, Qt::AscendingOrder);
}

/*
THIS IS A SLOT CALLED -> from CALLBACK
*/
void QtProcessesWidget::handleUpdateWidget(AddRemoveProcsStruct diff, int numAllProcesses)
{
	clearAndPopulateTableWithProcessesToShow(std::move(diff));
	m_currNumProcessesRunning->setText(
		QString::fromStdString("Curr. num of running processes: " + std::to_string(numAllProcesses)));
}

void QtProcessesWidget::handleKillClick()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button)
	{
		int row = m_tableWidget->indexAt(button->pos()).row();
		QString procPidSelected = m_tableWidget->item(row, 0)->text();
		auto reply = QMessageBox::question(
			this,
			ConfirmKillLabel,
			QString("Are you sure you want to kill process with PID %1?").arg(procPidSelected));
		if (reply == QMessageBox::Yes)
		{
			auto killProcessResult = m_processesController->killProcess(std::stoi(procPidSelected.toStdString()));
			if (killProcessResult == 0)
			{
				QMessageBox::information(
					this,
					ProcKillStatusLabel,
					QString("Process with PID %1 was killed successfully.").arg(procPidSelected));
			}
			else
			{
				QMessageBox::warning(
					this,
					ProcKillStatusLabel,
					QString("Process with PID %1 was not killed successfully.")
						.arg(procPidSelected)
				);
			}
		}
	}
}

void QtProcessesWidget::handleFilterChange(const QString& text)
{
	m_processesController->setFilter(text.toStdString());
	m_tableWidget->scrollToTop();
}
