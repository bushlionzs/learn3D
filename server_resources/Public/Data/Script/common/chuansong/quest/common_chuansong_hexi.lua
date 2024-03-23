--边境河西马车夫

x550021_g_ScriptId 					= 550021
x550021_g_MissionName				= "边塞传送"
x550021_g_TransTypeId				= {206,1206,2206,3206}
x550021_g_TransPoint				= {4005,5005,6005,7005}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550021_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550021_g_ScriptId, x550021_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550021_ProcEventEntry(sceneId, selfId, targetId)

	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法使用马车夫",8,2)
		return
	end
	--以上用于铁人三项禁止传送的处理
	------------------------------------------------------
	local country = GetCurCountry(sceneId, selfId)
	local nDefaultCamp = GetSceneCamp( sceneId )

	nDefaultCamp = nDefaultCamp - 16
	
	if country == nDefaultCamp then
	
		if country == 0 then
			DispatchTransferType(sceneId, selfId, targetId, x550021_g_TransTypeId[1], x550021_g_TransPoint[1])
		elseif country == 1 then
			DispatchTransferType(sceneId, selfId, targetId, x550021_g_TransTypeId[2], x550021_g_TransPoint[2])
		elseif country == 2 then	
			DispatchTransferType(sceneId, selfId, targetId, x550021_g_TransTypeId[3], x550021_g_TransPoint[3])
		elseif country == 3 then
			DispatchTransferType(sceneId, selfId, targetId, x550021_g_TransTypeId[4], x550021_g_TransPoint[4])
		end	
	
	else
		return
	end		
		
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550021_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550021_ProcAccept(sceneId, selfId, targetId)

end