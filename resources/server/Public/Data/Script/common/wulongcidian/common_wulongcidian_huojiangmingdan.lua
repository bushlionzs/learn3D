--�ű��� 
--MisDescBegin
x310191_g_ScriptId = 310191
x310191_g_MissionName1="�鿴������"
--MisDescEnd

function x310191_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
local minute =  GetMinOfDay()
		if GetWeek() ~= 0 or minute <17*60+1 then
			return
		end     

		AddQuestNumText(sceneId, x310191_g_ScriptId, x310191_g_MissionName1,13,1)
end

function x310191_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)

  BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310191_g_MissionName1)
		for i=1, WULONGCIDIAN_AWARD_COUNT do
			if i==1 then
			local first = "\t��һ����������ʦ-#G"..WULONGCIDIAN_AWARD_NAME[i]
			AddQuestText(sceneId,first)
			elseif i==2 then
			local second = "\t�ڶ�������������-#G"..WULONGCIDIAN_AWARD_NAME[i]
			AddQuestText(sceneId,second)
			elseif i==3 then
			local third = "\t������������ǿ��-#G"..WULONGCIDIAN_AWARD_NAME[i]
			AddQuestText(sceneId,third)
			end
		end
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310191_g_ScriptId, x310191_g_MissionName1)

end