--保定路马车夫

x550039_g_ScriptId 					= 550039
x550039_g_MissionName				= "大都传送"
x550039_g_TransTypeId				= {311,1311,2311,3311}
x550039_g_TransPoint				=  {4507,5507,6507,7507}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550039_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550039_g_ScriptId, x550039_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550039_ProcEventEntry(sceneId, selfId, targetId)

	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法使用马车夫",8,2)
		return
	end
	--以上用于铁人三项禁止传送的处理
	------------------------------------------------------
	local country = GetCurCountry(sceneId, selfId)
	local nDefaultCamp = GetSceneCamp( sceneId )

	--nDefaultCamp = nDefaultCamp - 16
	
--	if country == nDefaultCamp then
	
		if country == 0 then
			DispatchTransferType(sceneId, selfId, targetId, x550039_g_TransTypeId[1], x550039_g_TransPoint[1])
		elseif country == 1 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550039_g_TransTypeId[2], x550039_g_TransPoint[2])
		elseif country == 2 then	                                                
			DispatchTransferType(sceneId, selfId, targetId, x550039_g_TransTypeId[3], x550039_g_TransPoint[3])
		elseif country == 3 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550039_g_TransTypeId[4], x550039_g_TransPoint[4])
		else
			return
	end	
		
	--end			
		
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550039_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550039_ProcAccept(sceneId, selfId, targetId)

end