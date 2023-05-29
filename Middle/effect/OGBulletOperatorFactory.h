#ifndef OGBulletOperatorFactory_h__
#define OGBulletOperatorFactory_h__


namespace Orphigine
{
	class BulletOperator;

	class BulletOperatorFactory
	{
	public:
		virtual String getName() const = 0;

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem) = 0;

		virtual void			destroyOperator(BulletOperator* bulletOperator);

		virtual ~BulletOperatorFactory(){}

	protected:
		BulletOperatorFactory(){}

		std::vector<BulletOperator*> m_operators;
	};
}
#endif // OGBulletOperatorFactory_h__