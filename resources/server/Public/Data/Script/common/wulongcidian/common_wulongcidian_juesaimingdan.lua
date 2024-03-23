--脚本号 
--MisDescBegin
x310190_g_ScriptId = 310190
x310190_g_MissionName1="查看入围终极挑战赛名单"
--MisDescEnd

function x310190_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
local minute =  GetMinOfDay()
		if GetWeek() ~= 0 or minute <16*60+1 then
			return
		end  

		AddQuestNumText(sceneId, x310190_g_ScriptId, x310190_g_MissionName1,13,1)
end

function x310190_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)
	
 		local count=0
 		local str=""

    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310190_g_MissionName1)
			for i=1, WULONGCIDIAN_STEPIN_COUNT do
			
				count = count+1
				local 	mingdan = "#G\t"..WULONGCIDIAN_STEPIN_NAME[i]
				str = str..mingdan;
				if count == 2 or i == WULONGCIDIAN_STEPIN_COUNT then
					AddQuestText(sceneId,str)
					count = 0
					str =""
				end
			end
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310190_g_ScriptId, x310190_g_MissionName1)

end