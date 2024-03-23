

x310404_g_ScriptId = 310404

function x310404_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	 if sceneId == 0 then
		QT_LOULAN_HUMAN_NUM = 0
	
		QT_LAIYIN_HUMAN_NUM = 0
	
		QT_KUNLUN_HUMAN_NUM = 0
	
		QT_DUNHUANG_HUMAN_NUM = 0	
	end
end

function x310404_KickHuman( sceneId, actId, uTime )
	local nHumanCount = GetScenePlayerCount( sceneId )

    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nCountryId = GetCurCountry( sceneId,objId )
			local PosX = 150
			local PosZ = 180
			NewWorld(sceneId, objId,15,PosX,PosZ, 310404)
        end
    end
	
	CallScriptFunction( 310403, "KickMonster", sceneId, actId, uTime)
end

function x310404_ProcTiming( sceneId, actId, uTime )

end
