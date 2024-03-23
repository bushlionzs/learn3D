

x310032_g_ScriptId = 310032

x310032_g_SceneId = { 58, 158, 258, 358 }

function x310032_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
		YX_LOULAN_HUMAN_NUM1 = 0
		YX_LOULAN_HUMAN_NUM2 = 0
		YX_LOULAN_HUMAN_NUM3 = 0
		YX_LOULAN_HUMAN_NUM4 = 0
		YX_LOULAN_HUMAN_NUM5 = 0
		YX_LOULAN_HUMAN_NUM6 = 0
		YX_LOULAN_HUMAN_NUM7 = 0
		YX_LOULAN_HUMAN_NUM8 = 0
	
		YX_LAIYIN_HUMAN_NUM1 = 0
		YX_LAIYIN_HUMAN_NUM2 = 0
		YX_LAIYIN_HUMAN_NUM3 = 0
		YX_LAIYIN_HUMAN_NUM4 = 0
		YX_LAIYIN_HUMAN_NUM5 = 0
		YX_LAIYIN_HUMAN_NUM6 = 0
		YX_LAIYIN_HUMAN_NUM7 = 0
		YX_LAIYIN_HUMAN_NUM8 = 0
		
		YX_KUNLUN_HUMAN_NUM1 = 0
		YX_KUNLUN_HUMAN_NUM2 = 0
		YX_KUNLUN_HUMAN_NUM3 = 0
		YX_KUNLUN_HUMAN_NUM4 = 0
		YX_KUNLUN_HUMAN_NUM5 = 0
		YX_KUNLUN_HUMAN_NUM6 = 0
		YX_KUNLUN_HUMAN_NUM7 = 0
		YX_KUNLUN_HUMAN_NUM8 = 0
			
		YX_DUNHUANG_HUMAN_NUM1 = 0
		YX_DUNHUANG_HUMAN_NUM2 = 0
		YX_DUNHUANG_HUMAN_NUM3 = 0
		YX_DUNHUANG_HUMAN_NUM4 = 0
		YX_DUNHUANG_HUMAN_NUM5 = 0
		YX_DUNHUANG_HUMAN_NUM6 = 0
		YX_DUNHUANG_HUMAN_NUM7 = 0
		YX_DUNHUANG_HUMAN_NUM8 = 0
end

function x310032_ReliveHuman(sceneId,selfId)

	if GetHp(sceneId,selfId) > 0  then
		return
	end
	
	ClearRageRecoverTick(sceneId, selfId)
	RestoreHp(sceneId, selfId,100)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)	
	if usehorse==1 then
		LastMount(sceneId, selfId )
		RestoreHp(sceneId, selfId,0)
	end
end

function x310032_KickHuman( sceneId, actId, uTime )
	
    --local PosX, PosZ;
--if  sceneId == YX_LOULAN_SCENE_ID1 or sceneId == YX_LAIYIN_SCENE_ID1 or sceneId == YX_KUNLUN_SCENE_ID1 or sceneId == YX_DUNHUANG_SCENE_ID1 then
--	PosX =128
--	PosZ = 70
--elseif sceneId == YX_LOULAN_SCENE_ID2 or sceneId ==YX_LAIYIN_SCENE_ID2 or sceneId ==YX_KUNLUN_SCENE_ID2 or sceneId ==YX_DUNHUANG_SCENE_ID2 then
--	PosX =129
--	PosZ = 56
--elseif sceneId ==YX_LOULAN_SCENE_ID3 or sceneId ==YX_LAIYIN_SCENE_ID3 or sceneId ==YX_KUNLUN_SCENE_ID3 or sceneId ==YX_DUNHUANG_SCENE_ID3 then
--	PosX =126
--	PosZ = 45
--elseif sceneId ==YX_LOULAN_SCENE_ID4 or sceneId ==YX_LAIYIN_SCENE_ID4 or sceneId ==YX_KUNLUN_SCENE_ID4 or sceneId ==YX_DUNHUANG_SCENE_ID4 then
--	PosX =111
--	PosZ = 53
--elseif sceneId ==YX_LOULAN_SCENE_ID5 or sceneId ==YX_LAIYIN_SCENE_ID5 or sceneId ==YX_KUNLUN_SCENE_ID5 or sceneId ==YX_DUNHUANG_SCENE_ID5 then
--	PosX =128
--	PosZ = 70
--elseif sceneId ==YX_LOULAN_SCENE_ID6 or sceneId ==YX_LAIYIN_SCENE_ID6 or sceneId ==YX_KUNLUN_SCENE_ID6 or sceneId ==YX_DUNHUANG_SCENE_ID6 then
--	PosX =128
--	PosZ = 70
--end
   local PosX={ 128, 128, 162, 100}
   local PosZ={ 66, 66, 130, 133}     
         
	local nHumanCount = GetScenePlayerCount( sceneId )

    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
        
            local nCountryId = GetCurCountry( sceneId,objId )
		    local NewSceneId = x310032_g_SceneId[nCountryId+1]
		    local Posx = PosX[nCountryId+1]
		    local Posz = PosZ[nCountryId+1]
		    
		    x310032_ReliveHuman(sceneId,objId)
		    NewWorld(sceneId, objId,NewSceneId,Posx+random( 0, 3),Posz+random( 0, 3), 310032)
        
        end
    end
	
	CallScriptFunction( 310031, "KickMonster", sceneId, actId, uTime)
end

function x310032_ProcTiming( sceneId, actId, uTime )

end
