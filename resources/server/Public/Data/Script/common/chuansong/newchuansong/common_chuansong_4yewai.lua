--���ǵ�Ұ��
x550006_g_SceneID1 =50								--¥�����ǳ���ID
x550006_g_SceneID2 =150	  						 	--��ɽ���ǳ���ID
x550006_g_SceneID3 =250								--�������ǳ���ID
x550006_g_SceneID4 =350								--�ػ����ǳ���ID

x550006_g_TargetTypeId = {8000,8001,8002,8003} --Ŀ�괫��TypeId ���WorldPos.tab

-------------------------



function x550006_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local country = GetCurCountry(sceneId, selfId)
	local nDefaultCamp = GetSceneCamp( sceneId )

	nDefaultCamp = nDefaultCamp - 16
	
	if country == nDefaultCamp then
		if country == 0 then
			DispatchTransferType(sceneId, selfId, -1, x550006_g_TargetTypeId[1], -1)
		elseif country == 1 then                  
			DispatchTransferType(sceneId, selfId, -1, x550006_g_TargetTypeId[2], -1)
		elseif country == 2 then                  
			DispatchTransferType(sceneId, selfId, -1, x550006_g_TargetTypeId[3], -1)
		elseif country == 3 then                  
			DispatchTransferType(sceneId, selfId, -1, x550006_g_TargetTypeId[4], -1)
		end
	else
		return
	end
end

function x550006_ProcEventEntry( sceneId, selfId,targetId )
--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )
--
--	nDefaultCamp = nDefaultCamp - 16
--	
--	if country == nDefaultCamp then
--		if country == 0 then
--			DispatchTransferType(sceneId, selfId, targetId, x550006_g_TargetTypeId[1], -1)
--		elseif country == 1 then
--			DispatchTransferType(sceneId, selfId, targetId, x550006_g_TargetTypeId[2], -1)
--		elseif country == 2 then
--			DispatchTransferType(sceneId, selfId, targetId, x550006_g_TargetTypeId[3], -1)
--		elseif country == 3 then
--			DispatchTransferType(sceneId, selfId, targetId, x550006_g_TargetTypeId[4], -1)
--		end
--	else
--		return
--	end
	
end







--x550006_g_ScriptId 					= 550006
--x550006_g_MissionName				= "����֮��"
---------------------------
----***********************
----ProcEnumEvent
----***********************
---------------------------
--
--function x550006_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
--	
--	AddQuestNumText(sceneId, x550006_g_ScriptId, x550006_g_MissionName);
--	
--end
--
---------------------------
----***********************
----ProcEventEntry
----***********************
---------------------------
--
--function x550006_ProcEventEntry(sceneId, selfId, targetId)
--		DispatchTransferType(sceneId, selfId, targetId, 1000, -1)
--end
--
---------------------------
----***********************
----ProcAcceptCheck
----***********************
---------------------------
--
--function x550006_ProcAcceptCheck(sceneId, selfId, targetId)
--
--end
--
---------------------------
----***********************
----ProcAccept
----***********************
---------------------------
--
--function x550006_ProcAccept(sceneId, selfId, targetId)
--
--end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550006_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550006_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550006_ProcEventEntry( sceneId, monsterobjid )

end