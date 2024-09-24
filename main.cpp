#include "QtProcessesView.h"
#include "ModelFactory.h"

int main(int argc, char* argv[])
{
	ModelFactory factory{};
	auto model = factory.getPlatformDependentModel();
	std::unique_ptr<ProcessesController> controller = std::make_unique<ProcessesController>(std::move(model));

	// TODO: add an argument to instance different UIs
	// or make it so CMAKE compiles with one UI or another w a flag

	// for now, default = Qt ui
	QtProcessesView view{std::move(controller)};
	return view.start(argc, argv);
}
