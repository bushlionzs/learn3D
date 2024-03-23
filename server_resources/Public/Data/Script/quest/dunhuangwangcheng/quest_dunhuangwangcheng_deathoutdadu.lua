--轮回之地回大都脚本

x256013_g_ScriptId = 256013
x256013_g_ask ={"回到大都天坛","确定"}
x256013_g_answer ={"\t生死有命，灾祸常生，所以，你也不必太过沮丧。\n\t你要离开这里，返回大都天坛吗？"}

function x256013_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256013_g_ScriptId, x256013_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256013_g_answer[1])
			AddQuestNumText(sceneId, x256013_g_ScriptId, x256013_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            if level>= 40 then
            	if IsQuestHaveDone(sceneId, selfId, 1522) > 0 then
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,0) == 0 then
							return
					end
           			NewWorld( sceneId, selfId, 0, 124 + random( 0, 5), 177 + random( 0, 5), 256013)
            	else 
            		BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t很抱歉，你没有开通#G大都的传送#W，我不能将你送到那里。")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x256013_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level>= 40 then
			AddQuestNumText(sceneId, x256013_g_ScriptId, x256013_g_ask[1],0,1)
		end
end








