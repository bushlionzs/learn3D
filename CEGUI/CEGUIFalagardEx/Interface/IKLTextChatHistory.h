
namespace CEGUI
{

	class IKLTextChatHistory
	{
	public:
		
		virtual size_t			insertChatString(const String& strChat) = 0;

		
		virtual void			removeAllChatStrings() = 0;
		
		virtual void			scrollToEnd() = 0;
		
		virtual void			extendClearRegion() = 0;
	};

}