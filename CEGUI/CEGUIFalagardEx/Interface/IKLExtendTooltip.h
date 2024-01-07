
namespace CEGUI
{
	class IKLExtendTooltip
	{
	public:
		
		virtual void			resizeSelf() = 0;
		virtual Size			getRealSize() = 0;
		virtual float			getRealAbsoluteWidth() = 0;
		virtual float			getRealAbsoluteHeight() = 0;
		virtual void			setCurCondition(int curStarNum) = 0;
	};
}