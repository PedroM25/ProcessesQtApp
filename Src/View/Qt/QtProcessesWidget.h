#pragma once

#include <QtWidgets>
#include <QMetaType>

#include "ProcessesController.h"
#include "ProcessInfo.h"
#include "AddRemoveProcsStruct.h"

namespace {
	const QString ButtonKillLabel = "KILL";
	const QString ProcKillStatusLabel = "Process kill status";
	const QString ConfirmKillLabel = "Kill process";
	const QString Column1 = "PID";
	const QString Column2 = "User";
	const QString Column3 = "Command";
	const QString Column4 = ConfirmKillLabel;
	const int PidColumn = 0;
	const int UserColumn = 1;
	const int CommandColumn = 2;
	const int KillColumn = 3;
	const int TimerVal = 1000; // in ms
}

class QtProcessesWidget : public QWidget
{
	Q_OBJECT
public:
	QtProcessesWidget(QWidget* parent, std::unique_ptr<ProcessesController> processesController);
	virtual ~QtProcessesWidget(){};

private:
	void clearAndPopulateTableWithProcessesToShow(AddRemoveProcsStruct diff);
	std::unique_ptr<ProcessesController> m_processesController;
	int m_maxNumAllProcesses = 0;
	QString m_currFilter{};
	std::atomic<bool> m_updateWidget;
	QLineEdit* m_lineEdit;
	QTableWidget* m_tableWidget;
	QLabel* m_currNumProcessesRunning;
	QTimer* m_updateTimer;

private slots:
	void handleUpdateWidget(AddRemoveProcsStruct diff, int numAllProcesses);
	void handleKillClick();
	void handleFilterChange(const QString& text);

signals:
	void updateWidget(AddRemoveProcsStruct diff, int numAllProcesses);
};

Q_DECLARE_METATYPE(AddRemoveProcsStruct);