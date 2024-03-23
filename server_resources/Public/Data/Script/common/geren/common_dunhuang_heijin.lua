--MisDescBegin

x300873_g_ScriptId 	  = 300873
x300873_g_MissionKind 				= 	1                       --任务类型
x300873_g_Mis_Count   = 1--每天可做的次数
x300873_g_MissionId = 7647;
x300873_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }

--MisDescEnd

--子任务
x300873_g_SubMissionID				=	{ { MisID=7608,MissionName = "【个人】官府押运",LevelLess = 30,LevelMax = 40  }, 
										  {	MisID=7609,MissionName = "【个人】官府押运",LevelLess = 40,LevelMax = 50  },
										  {	MisID=7610,MissionName = "【个人】官府押运",LevelLess = 50,LevelMax = 60  },
										  {	MisID=7611,MissionName = "【个人】官府押运",LevelLess = 60,LevelMax = 70  },
										  {	MisID=7612,MissionName = "【个人】官府押运",LevelLess = 70,LevelMax = 80  },	
										  {	MisID=7613,MissionName = "【个人】官府押运",LevelLess = 80,LevelMax = 150  },											  
										}								

function x300873_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local index = 0
	local level = GetLevel(sceneId,selfId)
	for i,itm in x300873_g_SubMissionID do
		if level >= itm.LevelLess and level < itm.LevelMax then
			index = i
			break
		end
	end

	local bHaveMission = x300873_IsHaveMission(sceneId, selfId)
	if bHaveMission <= 0 and index > 0 then
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300873_g_SubMissionID[index].MisID)
		AddQuestNumText(sceneId,x300873_g_SubMissionID[index].MisID,x300873_g_SubMissionID[index].MissionName,state,index);
	end

end



--点击（按钮）点击该任务后执行此脚本
function x300873_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )
end

--检查是否有任务
function x300873_IsHaveMission( sceneId, selfId )

	local bHaveMission = 0
	for i,itm in x300873_g_SubMissionID do
		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID );
		if bHaveMission > 0 then
			break
		end
	end
	
	return bHaveMission
end


--**********************************
--接受
--**********************************
function x300873_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
end


--**********************************
--接受
--**********************************
function x300873_ProcAccept( sceneId, selfId )
	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300873_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300873_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300873_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300873_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300873_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end




