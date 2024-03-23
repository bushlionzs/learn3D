--天上人间·梦聊离开脚本

x310394_g_ScriptId = 310394
x310394_g_ask ={"离开天上人间·梦聊","确定"}
x310394_g_answer ={"\t在天上人间·梦聊里玩得尽兴么？如果你感到有些疲劳，我可以将你送出天上人间·梦聊，别忘记下周继续来这里寻找无尽的欢乐。\n\t你现在要离开么？"}
x310394_g_HongBuff		= 7536
x310394_g_LanBuff		= 7537
function x310394_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x310394_g_ScriptId, x310394_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x310394_g_answer[1])
			AddQuestNumText(sceneId, x310394_g_ScriptId, x310394_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
           if IsHaveSpecificImpact( sceneId, selfId, x310394_g_HongBuff) == 1 or IsHaveSpecificImpact( sceneId, selfId, x310394_g_LanBuff) == 1 then
           		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"变身状态无法传送。")
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
           else
						if IsHaveSpecificImpact( sceneId, selfId, 7718) == 1 then
								CancelSpecificImpact( sceneId, selfId, 7718)	
						end
           	NewWorld( sceneId, selfId, 36, 127 + random( 0, 5), 66 + random( 0, 5), 310394)
           end
       
        end
	

	
	
end


--**********************************

--列举事件

--**********************************

function x310394_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		
			AddQuestNumText(sceneId, x310394_g_ScriptId, x310394_g_ask[1],3,1)
end








