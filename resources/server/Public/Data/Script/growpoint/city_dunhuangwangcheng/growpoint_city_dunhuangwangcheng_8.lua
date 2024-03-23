--生长点

x301009_g_GrowpointId = 10 --对应生长点ID
x301009_g_ItemIndex = 13011003 --对应收集物品的ID
x301009_g_MissionId = 2730
x301009_g_Bossid =-1

--生成函数开始************************************************************************
function 	x301009_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301009_g_GrowpointId, sceneId, 0, x301009_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301009_OnOpen(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301009_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301009_g_MissionId) > 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) < 1   then
					return 0
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"您已经拔除了夏桑菊")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 1
			end
		end
		return 1
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301009_OnRecycle(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301009_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301009_g_MissionId) > 0 then
			SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("拔除夏桑菊    %d/1",GetQuestParam(sceneId,selfId,misIndex,0) ))
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					if GetQuestParam(sceneId,selfId,misIndex,0) >= 1   then
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
					local shuwang =random(1,10)
					if shuwang == 10 then
							local nFindObjid = 1
							local nMonsterCount = GetMonsterCount(sceneId)
							for i=1,nMonsterCount do
    							local objid = GetMonsterObjID(sceneId,i-1)
    							if objid == x301009_g_Bossid then
    									nFindObjid = 0
    									break
    							end
							end
							if nFindObjid ==1 then
									local nPlayerX, nPlayerZ = GetWorldPos(sceneId, selfId)
									--CreateMonster(SceneId,MonsterType,x,z,AIType,AIScript,Script,ObjGUID,CampID,LiveTime,FaceDir,Name,Title)
									x301009_g_Bossid=CreateMonster(sceneId, 1519,nPlayerX,nPlayerZ,5,1,-1,-1,21,300000,0)
							end
					end
					return 1
		end
		return 0

end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301009_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

