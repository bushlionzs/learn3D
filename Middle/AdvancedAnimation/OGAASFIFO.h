#ifndef OGAASFIFO_h__
#define OGAASFIFO_h__

namespace Orphigine
{
	enum RefreshStateResult
	{
		FSR_NOTHING = 0,
		FSR_REPLACE,
		FSR_PUSHBACK
	};

	class AASPort;

	class AASFIFO
	{
	public:
		AASFIFO();
		~AASFIFO();

	protected:
		virtual RefreshStateResult		setActiveChildBackup(AASPort* newStatePort);

		AASPort*						getTopStatePort() const;
		void							setTopStatePort(AASPort* val);

		AASPort*						getBottomStatePort() const;
		void							setBottomStatePort(AASPort* val);

		virtual void					transitionFinished();

		bool							getInTransit() const;
		void							setInTransit(bool val);
	protected:
		AASPort*						m_topStatePort;
		AASPort*						m_bottomStatePort;
		bool							m_isInTransit;

	private:
	};
}
#endif // OGAASFIFO_h__