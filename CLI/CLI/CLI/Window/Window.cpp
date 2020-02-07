#include "Window.h"

CLI::Window::Window()
{
	component = gcnew System::ComponentModel::Container();
	tabCtl    = gcnew System::Windows::Forms::TabControl();
	page      = gcnew Page();

	Initialize();
	ShowDialog();
}

CLI::Window::~Window()
{
	if (Icon != nullptr) {
		delete Icon;
	}
	if (tabCtl != nullptr) {
		delete tabCtl;
	}
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Window::Initialize(void)
{
	Text          = "‚¨‚©‚à‚ñ";
	Size          = System::Drawing::Size(900, 480);
	Padding       = System::Windows::Forms::Padding(0);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	MaximizeBox   = false;
	MinimizeBox   = false;
	Icon          = gcnew System::Drawing::Icon("MyLogo.ico");
	BackColor     = System::Drawing::Color::White;
	StartPosition = System::Windows::Forms::FormStartPosition::Manual;
	Location      = System::Drawing::Point(0, 0);
	TopLevel      = true;
	Dock          = System::Windows::Forms::DockStyle::Fill;
	ShowInTaskbar = true;
	ShowIcon      = true;

	System::Windows::Forms::Label^ l = gcnew System::Windows::Forms::Label();
	l->Text = "Test";
	System::Windows::Forms::TabPage^ p = gcnew System::Windows::Forms::TabPage();
	p->Text = "TTT";
	p->Controls->Add(l);
	tabCtl->Controls->Add(p);

	tabCtl->Controls->Add(page);
	tabCtl->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
	tabCtl->Size = System::Drawing::Size(900, 480);
	this->Controls->Add(tabCtl);
}
