#ifndef OGBulletFlowSystemManager_h__
#define OGBulletFlowSystemManager_h__

#include "OgreSingleton.h"
#include "OGBulletCallbacks.h"


namespace Orphigine
{
	class BulletEventSystem;
	class BulletFlowSystem;
	class BulletOperator;
	class BulletSystem;
	class BulletOperatorFactory;
	
	class _OrphigineExport BulletFlowSystemManager :
		public Ogre::Singleton<BulletFlowSystemManager>
	{
	public:
		BulletFlowSystemManager();
		virtual ~BulletFlowSystemManager();

		/*
		*	����ScriptLoader���麯��
		*/
		virtual const StringVector& getScriptPatterns(void) const;

		virtual void				parseScript(Ogre::DataStreamPtr& stream, const String& groupName, const String& scriptPath = "");

		virtual void				reloadParseScript(Ogre::DataStreamPtr& stream, const String& groupName);

		virtual Real				getLoadingOrder(void) const;

		//reload�Ƿ����¼��� by changhao
		void						parseBulletFlowTemplateSegment(const String& name,Ogre::DataStreamPtr& stream, const String& groupName, bool reload = false);

		BulletFlowSystem*			createBulletFlowSystem(const String& templateName);
 
		void						destroyBulletFlowSystem(BulletFlowSystem* bulletFlowSystem);

		BulletFlowSystem*			createBulletFlowSystemTemplate(const String& name);
		void						addBulletFlowSystemTemplate(const String& name,
			BulletFlowSystem* bulletFlowSystem);
		BulletFlowSystem*			getBulletFlowSystemTemplate(const String& name);
		void						destroyBulletFlowSystemTemplate(const String& name);

		BulletEventSystem*			createBulletEventSystem(const String& name,BulletFlowSystem* flowSystem);

		void						destroyBulletEventSystem(BulletEventSystem* bulletEventSystem);
		BulletOperator*				createBulletOperator(const String& typeName,BulletEventSystem* eventSystem);

		void						destroyBulletOperator(BulletOperator* bulletOperator);

		void						addBulletOperatorFactory(BulletOperatorFactory* operatorFactory);

		CreateBulletFlowCallback*				getCreateBulletFlowCallback() const;
		void									setCreateBulletFlowCallback(CreateBulletFlowCallback* val);

		AfterCreatedBulletSystemCallback*		getAfterCreatedBulletSystemCallback() const;
		void									setAfterCreatedBulletSystemCallback(AfterCreatedBulletSystemCallback* val);

		BeforeDeleteBulletSystemCallback*		getBeforeDeleteBulletSystemCallback() const;
		void									setBeforeDeleteBulletSystemCallback(BeforeDeleteBulletSystemCallback* val);

		BulletSystemHitTargetCallback*			getBulletSystemHitTargetCallback() const;
		void									setBulletSystemHitTargetCallback(BulletSystemHitTargetCallback* val);

	protected:
		void						registerOperatorFactories();

		void						parseAttrib(const String& line,BulletFlowSystem* bulletFlowSystem);
		
		void						parseNewBulletEventSystem(const String& name,Ogre::DataStreamPtr& stream,
			BulletFlowSystem* bulletFlowSystem);
		void						parseBulletEventSystemAttrib(const String& line,BulletEventSystem* bulletEventSystem);
		
		void						parseNewBulletOperator(const String& name,Ogre::DataStreamPtr& stream,BulletEventSystem* eventSystem);
		void						parseBulletOperatorAttrib(const String& line,BulletOperator* bulletOperator);

		void						skipToNextCloseBrace(Ogre::DataStreamPtr& chunk);
		void						skipToNextOpenBrace(Ogre::DataStreamPtr& chunk);
		/// ���������Ϣ
		void						_logErrorInfo(const String& errorInfo, const String& lineContent, 
									const String& functionName);
	protected:
		StringVector								m_scriptPatterns;
		/// ÿ�ν���getLine��ʱ��͵����кţ���Ϊ����������Ϣ
		int											m_WrongLineNum;
		/// ��ǰ�������ļ�����
		String										m_ParsingFileName;
		std::map<String,BulletFlowSystem*>			m_bulletFlowSystemTemplate;
		std::map<String,BulletOperatorFactory*>		m_operatorFactories;

		CreateBulletFlowCallback*					m_createBulletFlowCallback;
		AfterCreatedBulletSystemCallback*			m_afterCreatedBulletSystemCallback;
		BeforeDeleteBulletSystemCallback*			m_beforeDeleteBulletSystemCallback;
		BulletSystemHitTargetCallback*				m_bulletSystemHitTargetCallback;

	private:
	};
}
#endif // OGBulletFlowSystemManager_h__