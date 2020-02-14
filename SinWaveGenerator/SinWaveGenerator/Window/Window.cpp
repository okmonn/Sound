#include "Window.h"

CLI::Window::Window()
{
	Initialize();
}

CLI::Window::Window(const System::UInt32& width, const System::UInt32& height)
{
	SetSize(width, height);
	Initialize();
}

CLI::Window::~Window()
{
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Window::Initialize(void)
{
	component = gcnew System::ComponentModel::Container();

	Text = "‚¨‚©‚à‚ñ";
	Icon = gcnew System::Drawing::Icon("MyLogo.ico");
	StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	BackColor     = System::Drawing::SystemColors::Window;
	FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	Padding         = System::Windows::Forms::Padding(0);
	Margin          = System::Windows::Forms::Padding(0);

	TopLevel    = true;
	ShowIcon    = true;

	MaximizeBox = false;
	MinimizeBox = false;
}

void CLI::Window::AddLabel(Label^ label)
{
	Controls->Add(label);
	label->Parent = this;
}

void CLI::Window::AddButton(Button^ button)
{
	Controls->Add(button);
	button->Parent = this;
}

void CLI::Window::SetPos(const System::UInt32& x, const System::UInt32& y)
{
	Location = System::Drawing::Point(x, y);
}

void CLI::Window::SetSize(const System::UInt32& width, const System::UInt32& height)
{
	Size       = System::Drawing::Size(width, height);
	ClientSize = Size;

	MaximumSize = Size;
	MinimumSize = Size;
}
