x300319_g_MissionName = "�����ҡ������ػ���ѯ"
x300319_g_ScriptId = 300319

--**********************************

--�о��¼�

--**********************************

function x300319_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300319_g_ScriptId, x300319_g_MissionName,3)
	
end

function x300319_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	x300319_DispatchPlayInfo( sceneId, selfId, NPCId )
end


---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x300319_DispatchPlayInfo( sceneId, selfId, NPCId )

	local guild1 = GetCountrySpecialGuild(sceneId, selfId,0)
	local guild2 = GetCountrySpecialGuild(sceneId, selfId,1)
	
	local leaderName1 = "����"
	local leaderName2 = "����"
	local guildName1 = "����"
	local guildName2 = "����"
	
	if guild1>=0 then
		guildName1 = GetGuildName(guild1)
		leaderName1 = GetGuildLeaderName(guild1)
	end

	if guild2>=0 then
		guildName2 = GetGuildName(guild2)
		leaderName2 = GetGuildLeaderName(guild2)
	end

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x300319_g_MissionName)
		AddQuestText(sceneId,"\n")
		AddQuestText(sceneId,"#G����֮����#W"..leaderName1)
		AddQuestText(sceneId,"#G�����ػ���᣺#W"..guildName1)
		AddQuestText(sceneId,"\n")
		AddQuestText(sceneId,"#G��ȸ֮����#W"..leaderName2)
		AddQuestText(sceneId,"#G��ȸ�ػ���᣺#W"..guildName2)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()



	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300319_g_ScriptId, 0,0);
end
