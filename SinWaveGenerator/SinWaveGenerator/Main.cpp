#include "Splash/Splash.h"
#include "Window/Window.h"

int main() {
	System::Windows::Forms::Application::EnableVisualStyles();

	CLI::Splash s;

	CLI::Window win;
	s.Complete();
	win.Show();

	while (win.Created) {
		System::Windows::Forms::Application::DoEvents();
	}

	return 0;
}