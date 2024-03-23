--生长点

x301218_g_GrowpointId = 170 --对应生长点ID
x301218_g_ItemIndex = 13030067 --对应收集物品的ID
x301218_g_BossType					= 	815                    --BOSS ID
x301218_g_BossCreate				=	{{	hash=1, type=x301218_g_BossType, x=44, z=210, ai=9, aiscript=-1	}}
x301218_g_Bossid =-1
---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x301218_CreateBoss(sceneId)
	for i, item in x301218_g_BossCreate do
		x301218_g_Bossid = CreateMonster(sceneId, x301218_g_BossType, 44, 210, 5, 1001, -1,-1,21);
		
	end

end										


--生成函数开始************************************************************************
function 	x301218_OnCreate(sceneId,growPointType,x,y)
--    print(11111111)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301218_g_GrowpointId, sceneId, 0, x301218_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301218_OnOpen(sceneId,selfId,targetId)
		local nFindObjid = 1
		local nMonsterCount = GetMonsterCount(sceneId)
		for i=1,nMonsterCount do
    		local objid = GetMonsterObjID(sceneId,i-1)
    		if objid == x301218_g_Bossid then
    			nFindObjid = 0
    			break
    		end
		end
		if nFindObjid == 1 then
    	local isHaveMission = IsHaveQuestNM(sceneId,selfId,468);
    	if isHaveMission == 1 then
    		if GetItemCount(sceneId,selfId,13030067) == 0 then
    	    return 0;
    	  else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你已经得到了冰晶戒指")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 1
				end
    	else
    	    return 1;
    	end
   	else
   		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"似乎“半只耳”不在洞里")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
   		return 1
   	end

end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301218_OnRecycle(sceneId,selfId,targetId)
   x301218_CreateBoss(sceneId)
   return 1
  --return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301218_g_GrowpointId, x301218_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301218_OnProcOver(sceneId,selfId,targetId)
  	--return CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

