--婆罗洲至威海港马车夫

x550056_g_ScriptId 					= 550056
x550056_g_MissionName			= "威海港传送"
x550056_g_TransTypeId				= {370,1370,2370,3370}
x550056_g_TransPoint				= {510,1510,2510,3510}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550056_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550056_g_ScriptId, x550056_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550056_ProcEventEntry(sceneId, selfId, targetId)

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
	
	--if country == nDefaultCamp then
		
		if country == 0 then
			DispatchTransferType(sceneId, selfId, targetId, x550056_g_TransTypeId[1], x550056_g_TransPoint[1])
		elseif country == 1 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550056_g_TransTypeId[2], x550056_g_TransPoint[2])
		elseif country == 2 then	                                                
			DispatchTransferType(sceneId, selfId, targetId, x550056_g_TransTypeId[3], x550056_g_TransPoint[3])
		elseif country == 3 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550056_g_TransTypeId[4], x550056_g_TransPoint[4])
		end	

	--else
		--return
	--end			
		
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550056_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550056_ProcAccept(sceneId, selfId, targetId)

end