--大都天坛马车夫

x550044_g_ScriptId 					= 550044
x550044_g_MissionName				= "大都传送"
x550044_g_TransTypeId				= {301,1301,2301,3301}
x550044_g_TransPoint				=  {4512,5512,6512,7512}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550044_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550044_g_ScriptId, x550044_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550044_ProcEventEntry(sceneId, selfId, targetId)

	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法使用马车夫",8,2)
		return
	end
	--以上用于铁人三项禁止传送的处理
	------------------------------------------------------
	local country = GetCurCountry(sceneId, selfId)

		if country == 0 then
			DispatchTransferType(sceneId, selfId, targetId, x550044_g_TransTypeId[1], x550044_g_TransPoint[1])
		elseif country == 1 then
			DispatchTransferType(sceneId, selfId, targetId, x550044_g_TransTypeId[2], x550044_g_TransPoint[2])
		elseif country == 2 then	
			DispatchTransferType(sceneId, selfId, targetId, x550044_g_TransTypeId[3], x550044_g_TransPoint[3])
		elseif country == 3 then
			DispatchTransferType(sceneId, selfId, targetId, x550044_g_TransTypeId[4], x550044_g_TransPoint[4])
		end	
					
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550044_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550044_ProcAccept(sceneId, selfId, targetId)

end