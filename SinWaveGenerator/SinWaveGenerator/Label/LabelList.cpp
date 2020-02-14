#include "LabelList.h"
#include "Label.h"

CLI::LabelList::LabelList()
{
	component = gcnew System::ComponentModel::Container();
}

CLI::LabelList::~LabelList()
{
	if (component != nullptr) {
		delete component;
	}
}

void CLI::LabelList::AddList(Label^ label)
{
	Controls->Add(label);

	System::UInt32 index = Controls->Count - 1;
	((Label^)(Controls[index]))->Index = index;
	Controls[index]->Parent = this;
}
