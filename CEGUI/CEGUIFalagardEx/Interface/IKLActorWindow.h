
namespace CEGUI
{

	class IKLActorWindow
	{
	public:
		
		virtual void	subscribeShownEvent(Event::Subscriber subscriber) = 0;
		
		virtual void	subscribeHidenEvent(Event::Subscriber subscriber) = 0;
	};

}