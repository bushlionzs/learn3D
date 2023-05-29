#ifndef OGBulletCallbacks_h__
#define OGBulletCallbacks_h__

#include "OGImpact.h"

namespace Orphigine
{
	class BulletFlowSystem;
	class BulletSystem;

	struct CreateBulletFlowCallback
	{
		virtual void	onCreateBulletFlow(const String& bulletFlowTemplateName,const String& attachPoint,
			const TransformInfo& transInfo,void* skillUserData, int priority) = 0;
	};

	struct AfterCreatedBulletSystemCallback
	{
		virtual void	onAfterCreatedBulletSystem(BulletFlowSystem* bulletFlow,BulletSystem* bulletSystem) = 0;
		
	};

	struct BeforeDeleteBulletSystemCallback
	{ 
		virtual void	onBeforeDeleteBulletSystem(BulletSystem* bulletSystem) = 0;
	};

	struct BulletSystemHitTargetCallback
	{
		virtual void	onHitTargetCallback(BulletFlowSystem* bulletFlow,BulletSystem* bulletSystem) = 0;
	};
}

#endif // OGBulletCallbacks_h__