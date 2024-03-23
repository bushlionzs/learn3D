--领地拜占庭

x300282_g_ScriptId = 300282
x300282_g_ask ={"回到匈牙利","确定"}
x300282_g_answer ={"\t你要离开这里，返回匈牙利吗？"}

function x300282_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x300282_g_ScriptId, x300282_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300282_g_answer[1])
			AddQuestNumText(sceneId, x300282_g_ScriptId, x300282_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            if level>= 40 then
            	if IsQuestHaveDone(sceneId, selfId, 1512) > 0 then
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,0) == 0 then
							return
					end
           			NewWorld( sceneId, selfId, 20, 204 + random( 0, 5), 74 + random( 0, 5), 300282)
            	else 
            		BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t很抱歉，你没有开通#G匈牙利的传送#W，我不能将你送到那里。")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x300282_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level>= 40 then
			AddQuestNumText(sceneId, x300282_g_ScriptId, x300282_g_ask[1],0,1)
		end
end








