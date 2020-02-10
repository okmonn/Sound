#include "Window.h"

Window::Window()
{
	component = gcnew System::ComponentModel::Container();

	Initialize();
	SetEvent();
	Show();
}

Window::~Window()
{
	if (Icon != nullptr) {
		delete Icon;
	}
	if (component != nullptr) {
		delete component;
	}
}

void Window::Initialize(void)
{
	Size          = System::Drawing::Size(900, 480);
	StartPosition = System::Windows::Forms::FormStartPosition::Manual;
	Location      = System::Drawing::Point(0, 0);

	Icon          = gcnew System::Drawing::Icon("MyLogo.ico");
	Text          = "‚¨‚©‚à‚ñ";
	BackColor     = System::Drawing::Color::White;
	Padding       = System::Windows::Forms::Padding(0);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	Dock          = System::Windows::Forms::DockStyle::Fill;
	
	TopLevel      = true;
	ShowInTaskbar = true;
	ShowIcon      = true;
	KeyPreview    = true;
	MaximizeBox   = false;
	MinimizeBox   = false;
}

void Window::CloseEvent(System::Object^ obj, System::ComponentModel::CancelEventArgs^ args)
{
	System::Windows::Forms::Application::ExitThread();
}

void Window::SetEvent(void)
{
	Closing += gcnew System::ComponentModel::CancelEventHandler(this, &Window::CloseEvent);
}
