#include "QtProcessesView.h"

#include <QApplication>
#include <QPluginLoader>
#include <QWidget>
#include <iostream>

#include "QtCustomWindow.cpp"
#include "QtProcessesWidget.cpp"

int QtProcessesView::start(int argc, char* argv[])
{
	QApplication app(argc, argv);

	qDebug() << "[DEBUG] Hello world!!";

	// 1. Create widget to be put inside window
	auto centralWidget = new QtProcessesWidget(nullptr, std::move(m_processesController));

	// 2. Create the main window
	auto appWindow = new QtCustomWindow();
	appWindow->setCentralWidget(centralWidget); // 3. set main window's central widget
	appWindow->setWindowTitle("My IoT app");
	appWindow->resize(550, 600);
	appWindow->show();

	return app.exec();
}