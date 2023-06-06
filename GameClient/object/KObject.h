#pragma once

class GameEntity;

enum ObjectType
{
	ObjectType_None = 0,
	ObjectType_Item,
	ObjectType_ItemEquip,
	ObjectType_ItemGem,
	ObjectType_ItemMedicine,
	ObjectType_ItemTask,
	ObjectType_ItemBag,
	ObjectType_Npc,
	ObjectType_Player,
	ObjectType_PlayerOfMe
};
class KObject
{
public:
	KObject();
	~KObject();
	virtual uint32_t getObjectType();
	void setId(int64_t id);
	int64_t getId();
	void setPosition(const Ogre::Vector3& pos);
	const Ogre::Vector3& getPosition();
	void setOrientation(const Ogre::Vector3& dir);
	const Ogre::Vector3& getOrientation();

	GameEntity* createGameEntity(int32_t entityType);

	uint64_t GetCreateTime() 
	{ 
		return mCreateTime;
	}

	int32_t			GetBaseLogicCount(void) const 
	{ 
		return m_nBaseLogicCount; 
	}
	void			SetBaseLogicCount(int32 nLogicCount) 
	{ 
		m_nBaseLogicCount = nLogicCount; 
	}
	virtual void	ResetBaseLogicCount(void) 
	{ 
		m_nBaseLogicCount = -1; 
	}

	int32_t			GetActionLogicCount(void) const 
	{ 
		return m_nActionLogicCount; 
	}
	void			SetActionLogicCount(int32 nLogicCount) 
	{ 
		m_nActionLogicCount = nLogicCount; 
	}
	virtual void	ResetActionLogicCount(void)
	{
		m_nActionLogicCount = -1;
	}
public:
	virtual void update(float delta) {}
protected:
	std::shared_ptr<GameEntity> mMainEntity;
	
	int64_t mServerId;

	ObjectType mObjectType;
	Ogre::Vector3 mPosition;
	Ogre::Vector3 mOrientation;

	uint64_t mCreateTime;
	int32_t m_nBaseLogicCount;
	int32_t m_nActionLogicCount;
};