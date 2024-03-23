
x256200_g_ScriptId = 256200
x256200_g_MissionId = 1411
x256200_g_MissionName = "【个人】江湖生涯<五>"

function x256200_ProcEnumEvent(sceneId, selfId, targetId)

	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x256200_g_MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0;
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0;
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0;
		end
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, x256200_g_MissionId ) > 0 then
		return 0;
	end
	local zhiye = GetZhiye( sceneId, selfId);
	if IsQuestHaveDoneNM( sceneId, selfId, 1450+zhiye ) > 0 then
		return 0;
	end
	
	if IsHaveQuestNM(sceneId, selfId, x256200_g_MissionId) > 0 then
		return 0;
	end
	
	AddQuestNumText( sceneId, x256200_g_MissionId, x256200_g_MissionName, 5)

end

function x256200_ProcEventEntry(sceneId, selfId, targetId, MissionId, switch)

	local zhiye = GetZhiye( sceneId, selfId);
	QuestCom(sceneId, selfId, x256200_g_MissionId)
	CallScriptFunction(MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, targetId, 1450+zhiye)

end

function x256200_ProcQuestAccept(sceneId, selfId, targetId, MissionId)

	local zhiye = GetZhiye( sceneId, selfId);
	QuestCom(sceneId, selfId, x256200_g_MissionId)
	CallScriptFunction(MISSION_SCRIPT, "ProcQuestAccept", sceneId, selfId, targetId, 1450+zhiye)

end