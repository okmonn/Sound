#include "Splash.h"

CLI::Splash::Splash()
{
	Initialize();
	Show();
}

CLI::Splash::Splash(const System::UInt32& width, const System::UInt32& height)
{
	Initialize();
	SetSize(width, height);
	Show();
}

CLI::Splash::~Splash()
{
	if (th != nullptr) {
		th->Wait(System::Threading::Timeout::Infinite);
		delete th;
	}
	if (wait != nullptr) {
		delete wait;
	}
	if (component != nullptr) {
		delete component;
	}
}

void CLI::Splash::Initialize(void)
{
	component = gcnew System::ComponentModel::Container();
	wait      = gcnew System::Threading::ManualResetEvent(false);
	th        = System::Threading::Tasks::Task::Run(gcnew System::Action(this, &Splash::Stream));

	BackgroundImage       = System::Drawing::Image::FromFile("MyLogo.png");
	BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
	StartPosition         = System::Windows::Forms::FormStartPosition::CenterScreen;
	FormBorderStyle       = System::Windows::Forms::FormBorderStyle::None;

	TopLevel = true;
	
	ShowIcon    = false;
	MaximizeBox = false;
	MinimizeBox = false;
}

void CLI::Splash::Stream(void)
{
	wait->WaitOne(System::Threading::Timeout::Infinite);
}

void CLI::Splash::Complete(void)
{
	wait->Set();
	Close();
}

void CLI::Splash::SetPos(const System::UInt32& x, const System::UInt32& y)
{
	Location = System::Drawing::Point(x, y);
}

void CLI::Splash::SetSize(const System::UInt32& width, const System::UInt32& height)
{
	Size       = System::Drawing::Size(width, height);
	ClientSize = Size;

	MaximumSize = Size;
	MinimumSize = Size;
}
