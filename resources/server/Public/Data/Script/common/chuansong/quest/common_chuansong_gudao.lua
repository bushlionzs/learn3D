--�ŵ�

x550172_g_ScriptId 					= 550172
x550172_g_MissionName			  = "��������"
x550172_g_TransTypeId				= {102,302,502,702}
x550172_g_TransPoint				= {2,202,402,602}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550172_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	
	AddQuestNumText(sceneId, x550172_g_ScriptId, x550172_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550172_ProcEventEntry(sceneId, selfId, targetId)


	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ʹ������",8,2)
		return
	end
	--�����������������ֹ���͵Ĵ���
	------------------------------------------------------
	local country = GetCurCountry(sceneId, selfId)
	--local nDefaultCamp = GetSceneCamp( sceneId )

	--nDefaultCamp = nDefaultCamp - 16
	
	--if country == nDefaultCamp then
		
		if country == 0 then
			DispatchTransferType(sceneId, selfId, targetId, x550172_g_TransTypeId[1], x550172_g_TransPoint[1])
		elseif country == 1 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550172_g_TransTypeId[2], x550172_g_TransPoint[2])
		elseif country == 2 then	                                                
			DispatchTransferType(sceneId, selfId, targetId, x550172_g_TransTypeId[3], x550172_g_TransPoint[3])
		elseif country == 3 then                                                  
			DispatchTransferType(sceneId, selfId, targetId, x550172_g_TransTypeId[4], x550172_g_TransPoint[4])
		end	

	--else
--	print(111111)
	--	return
	--end			
		
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550172_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550172_ProcAccept(sceneId, selfId, targetId)

end
