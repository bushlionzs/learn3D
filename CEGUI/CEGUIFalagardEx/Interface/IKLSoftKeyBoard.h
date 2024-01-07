#pragma once
namespace CEGUI
{
	class Window;
	class IKLSoftKeyBoard
	{
	public:
		virtual void SetActiveEditBox( String& windowName ) = 0;
	};

};