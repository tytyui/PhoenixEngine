#ifndef PHOENIX_CONSOLE_WINDOW_H
#define PHOENIX_CONSOLE_WINDOW_H

#if _WIN32
#include <windows.h> 
#endif

namespace Phoenix
{
	struct FConsoleWindow
	{
	public:
		FConsoleWindow() = delete;

		static void Hide();

		static void Show();
	};

	inline void FConsoleWindow::Hide()
	{
#if _WIN32
		/* https://msdn.microsoft.com/en-us/library/windows/desktop/ms683175%28v=vs.85%29.aspx */
		HWND ConsoleWindow = GetConsoleWindow();
		const int ShowWindowCommand = SW_HIDE;

		/* https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx */
		ShowWindow(ConsoleWindow, ShowWindowCommand);
#endif
	}

	inline void FConsoleWindow::Show()
	{
#if _WIN32
		/* https://msdn.microsoft.com/en-us/library/windows/desktop/ms683175%28v=vs.85%29.aspx */
		HWND ConsoleWindow = GetConsoleWindow();
		const int ShowWindowCommand = SW_SHOW;

		/* https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548%28v=vs.85%29.aspx */
		ShowWindow(ConsoleWindow, ShowWindowCommand);
#endif
	}
}

#endif
