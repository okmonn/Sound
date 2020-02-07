#include "Page.h"

CLI::Page::Page()
{
	component = gcnew System::ComponentModel::Container();
	label     = gcnew System::Windows::Forms::Label();
}

CLI::Page::~Page()
{
	if (label != nullptr) {
		delete label;
	}
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Page::Initialize(void)
{
	label->BackColor = System::Drawing::Color::White;
	label->Text = "adada";

	Text = "tetete";
	BackColor = System::Drawing::Color::DarkOrange;
	this->Controls->Add(label);

	Text = "lhksdhfuio;ahsfiod;shjf;ahjgas";
}
