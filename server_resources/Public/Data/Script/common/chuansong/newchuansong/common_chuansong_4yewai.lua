--王城到野外
x550006_g_SceneID1 =50								--楼兰王城场景ID
x550006_g_SceneID2 =150	  						 	--天山王城场景ID
x550006_g_SceneID3 =250								--昆仑王城场景ID
x550006_g_SceneID4 =350								--敦煌王城场景ID

x550006_g_TargetTypeId = {8000,8001,8002,8003} --目标传送TypeId 针对WorldPos.tab

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
--x550006_g_MissionName				= "记忆之门"
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

--玩家在一个 area 呆了一段时间没走则定时触发
function x550006_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550006_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550006_ProcEventEntry( sceneId, monsterobjid )

end