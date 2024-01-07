
namespace CEGUI
{

	class IKLKeyImageAnimation
	{
	public:
		
		virtual void	Play(bool bPlay) = 0;
		virtual size_t   getFrameNumber() = 0;
		virtual String getFrameName(const size_t &) = 0;

	};

}