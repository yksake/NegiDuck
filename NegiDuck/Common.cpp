#include "Common.hpp"

Common::Common()
{
	
}


void Common::hideCursor()
{
	if (Cursor::OnClientRect())
	{
		Cursor::RequestStyle(CursorStyle::Hidden);
	}
}
