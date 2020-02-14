#include "Label.h"

CLI::Label::Label()
{
	component = gcnew System::ComponentModel::Container();

	Initialize();
}

CLI::Label::Label(System::String^ str, const System::UInt32& x, const System::UInt32& y)
{
	component = gcnew System::ComponentModel::Container();

	Initialize();
	SetString(str);
	SetPos(x, y);
}

CLI::Label::Label(System::String^ str, const System::UInt32& x, const System::UInt32& y, const System::UInt32& width, const System::UInt32& height)
{
	component = gcnew System::ComponentModel::Container();

	Initialize();
	SetString(str);
	SetPos(x, y);
	SetSize(width, height);
}

CLI::Label::~Label()
{
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Label::Initialize(void)
{
	Padding = System::Windows::Forms::Padding(0);
	Margin  = System::Windows::Forms::Padding(0); 

	AutoSize = true;
}

void CLI::Label::SetString(System::String^ str)
{
	Text = str;
}

void CLI::Label::SetPos(const System::UInt32& x, const System::UInt32& y)
{
	Location = System::Drawing::Point(x, y);
}

void CLI::Label::SetSize(const System::UInt32& width, const System::UInt32& height)
{
	AutoSize = false;
	Size     = System::Drawing::Size(width, height);
}
