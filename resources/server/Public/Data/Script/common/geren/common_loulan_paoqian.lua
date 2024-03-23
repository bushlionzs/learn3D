--MisDescBegin

x300756_g_ScriptId 					= 	300756                  --脚本ID
x300756_g_MissionId 				= 	7555                    --任务ID

x300756_g_MissionKind 				= 	1                       --任务类型

x300756_g_MissionName				= 	"【个人】黑金押运"                --任务名称(512)
x300756_g_MissionTarget				= 	"杀死@npc_72005"          --任务目标
x300756_g_MissionInfo				= 	"\t杀死@npc_72004的@npc_72005,找到@npc_137600"            --任务信息
x300756_g_ContinueInfo				= 	"@npc_137602一直请求我帮他清除@npc_72004的@npc_72005，我却一直抽不开身。"  --任务继续信息
x300756_g_MissionCompleted			= 	"@npc_137602已经把信件给我了，看来海都又把元素魔这怪物派来了，必须赶快通知@npc_137400。"  --任务完成信息
x300756_g_MissionHelp				=	""          --任务提示信息

--目标
x300756_g_ExtTarget					=	{ {type=20,n=3,target="@npc_72005"} }


--奖励
x300756_g_ExpBonus					= 	1000                    	--奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x300756_g_BonusItem					=	{}	--奖励：物品

x300756_g_BonusMoney1               = 	0    --任务奖励绑定银币
x300756_g_BonusMoney2               =   0    --任务奖励非绑定银币
x300756_g_BonusMoney3               =   0    --任务奖励绑定金币
x300756_g_BonusMoney4               =   0  --任务奖励朝廷声望
x300756_g_BonusMoney5               =   0  --任务奖励江湖声望
x300756_g_BonusMoney6               =   10  --任务奖励荣誉

x300756_g_BonusChoiceItem           =   {}

--MisDescEnd


--子任务
x300756_g_SubMissionID				=	{ { MisID=7556,MissionName = "【黑金】黑金押运",LevelLess = 30,LevelMax = 40  }, 
										  {	MisID=7557,MissionName = "【黑金】黑金押运",LevelLess = 40,LevelMax = 50  },
										  {	MisID=7558,MissionName = "【黑金】黑金押运",LevelLess = 50,LevelMax = 60  },
										  {	MisID=7546,MissionName = "【黑金】黑金押运",LevelLess = 60,LevelMax = 70  },
										  {	MisID=7547,MissionName = "【黑金】黑金押运",LevelLess = 70,LevelMax = 80  },	
										  {	MisID=7548,MissionName = "【黑金】黑金押运",LevelLess = 80,LevelMax = 150  },											  
										}								


--**********************************
--列举事件
--**********************************
function x300756_ProcEnumEvent( sceneId, selfId, NPCId )

	local index = 0
	local level = GetLevel(sceneId,selfId)
	for i,itm in x300756_g_SubMissionID do
		if level >= itm.LevelLess and level < itm.LevelMax then
			index = i
			break
		end
	end
	
	local bHaveMission = x300756_IsHaveMission(sceneId, selfId)
	if bHaveMission <= 0 and index > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x300756_g_SubMissionID[index].MisID)
		AddQuestNumText(sceneId,x300756_g_SubMissionID[index].MisID,x300756_g_SubMissionID[index].MissionName,state,index);
	end
end


--**********************************
--任务入口函数
--**********************************
function x300756_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--点击该任务后执行此脚本
end

--检查是否有任务
function x300756_IsHaveMission( sceneId, selfId )

	local bHaveMission = 0
	for i,itm in x300756_g_SubMissionID do
		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID );
		if bHaveMission > 0 then
			break
		end
	end
	
	return bHaveMission
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300756_ProcQuestAbandon(sceneId, selfId, MissionId)
end


---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300756_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
end

function x300756_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

