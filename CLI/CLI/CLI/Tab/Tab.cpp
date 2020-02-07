#include "Tab.h"

CLI::Tab::Tab()
{
	component = gcnew System::ComponentModel::Container();
	label     = gcnew System::Collections::Generic::List<System::Windows::Forms::Label^>();
	page      = gcnew System::Collections::Generic::List<System::Windows::Forms::TabPage^>;
}

CLI::Tab::~Tab()
{
	if (page != nullptr) {
		delete page;
	}
	if (label != nullptr) {
		delete label;
	}
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Tab::AddTab(const char* comment)
{
	System::String^ str = gcnew System::String(comment);

	System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
	label->Text      = str;
	label->BackColor = System::Drawing::Color::White;
	this->label->Add(label);

	System::Windows::Forms::TabPage^ page = gcnew System::Windows::Forms::TabPage();
	page->Text      = str;
	page->BackColor = System::Drawing::Color::White;
	page->Controls->Add(this->label[this->label->Count - 1]);
	this->page->Add(page);

	Controls->Add(this->page[this->page->Count - 1]);
}
