#include <vector>
#include <stdexcept>

#include "display/WindowManager.h"
#include "display/Window.h"

WindowManager::WindowManager()
{
}

void WindowManager::addWindow(Window* win)
{
	//Add the Window to the bottom of the stack.
	_windows.push_back(win);
}

Window* WindowManager::getWindow(uint32_t idx)
{
	if(idx < _windows.size())
	{
		return _windows[idx];
	} else {
		throw std::out_of_range("Referenced Window does not exist");
	}
}

void WindowManager::refresh()
{
	//From top to bottom of the stack...
	for(std::vector<Window*>::size_type i = 0; i < _windows.size(); i++)
	{
		//...refresh each Window in sequence.
		_windows[i]->refresh();
	}
}

