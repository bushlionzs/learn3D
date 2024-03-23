--生长点

x301207_g_GrowpointId = 157 --对应生长点ID
x301207_g_ItemIndex = 13030022 --对应收集物品的ID
x301207_g_BossType					= 	647                    --BOSS ID
x301207_g_BossCreate				=	{{	hash=1, type=x301207_g_BossType, x=182, z=121, ai=9, aiscript=1001	}}
x301207_g_Bossid =-1
---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x301207_CreateBoss(sceneId)
	for i, item in x301207_g_BossCreate do
		x301207_g_Bossid = CreateMonster(sceneId, x301207_g_BossType, 182, 121, 5, 1001, -1,-1,21);
		
	end

end										


--生成函数开始************************************************************************
function 	x301207_OnCreate(sceneId,growPointType,x,y)

	local ItemBoxId = ItemBoxEnterScene(x, y, x301207_g_GrowpointId, sceneId, 0, x301207_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301207_OnOpen(sceneId,selfId,targetId)
		local nFindObjid = 1
		local nMonsterCount = GetMonsterCount(sceneId)
		for i=1,nMonsterCount do
    		local objid = GetMonsterObjID(sceneId,i-1)
    		if objid == x301207_g_Bossid then
    			nFindObjid = 0
    			break
    		end
		end
		if nFindObjid == 1 then
    	local isHaveMission = IsHaveQuestNM(sceneId,selfId,359);
    	if isHaveMission == 1 then
    		if GetItemCount(sceneId,selfId,13030022) == 0 then
    	    return 0;
    	  else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你已经得到了狼人酒")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 1
				end
    	else
    	    return 1;
    	end
   	else
   		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"怪物已经被召唤出")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
   		return 1
   	end

end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301207_OnRecycle(sceneId,selfId,targetId)
   x301207_CreateBoss(sceneId)
   return 0
  --return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301207_g_GrowpointId, x301207_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301207_OnProcOver(sceneId,selfId,targetId)
  	--return CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


