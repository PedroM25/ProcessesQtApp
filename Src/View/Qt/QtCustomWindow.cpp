#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>

class QtCustomWindow : public QMainWindow
{
public:
	QtCustomWindow(QWidget* parent = nullptr)
		: QMainWindow(parent)
	{
		// Create menu bar
		QMenuBar* menuBar = new QMenuBar(this);

		// Create "Help" tab
		QMenu* helpTab = new QMenu("&Help", this);
		menuBar->addMenu(helpTab);

		// Add "About" action
		QAction* aboutAction = new QAction("&About", this);

		helpTab->addAction(aboutAction);

		// Connect action to slot
		connect(
			aboutAction,
			&QAction::triggered,
			this,
			[this]
			{
				QMessageBox::about(
					this,
					"About",
					"This app was developed by Pedro Ribeiro");
			});
		setMenuBar(menuBar);
	}
};