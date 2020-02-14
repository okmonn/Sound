#include "Button.h"

CLI::Button::Button()
{
	Initialize();
}

CLI::Button::Button(System::String^ str, const System::UInt32& x, const System::UInt32& y)
{
	Initialize();
	SetString(str);
	SetPos(x, y);
}

CLI::Button::Button(System::String^ str, const System::UInt32& x, const System::UInt32& y, const System::UInt32& width, const System::UInt32& height)
{
	Initialize();
	SetString(str);
	SetPos(x, y);
	SetSize(width, height);
}

CLI::Button::~Button()
{
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Button::Initialize(void)
{
	component = gcnew System::ComponentModel::Container();

	Padding = System::Windows::Forms::Padding(0);
	Margin  = System::Windows::Forms::Padding(0);

	AutoSize = true;
}

void CLI::Button::SetString(System::String^ str)
{
	Text = str;
}

void CLI::Button::SetPos(const System::UInt32& x, const System::UInt32& y)
{
	Location = System::Drawing::Point(x, y);
}

void CLI::Button::SetSize(const System::UInt32& width, const System::UInt32& height)
{
	AutoSize = false;

	Size        = System::Drawing::Size(width, height);
	MaximumSize = Size;
	MinimumSize = Size;
}
