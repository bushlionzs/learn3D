--迷宫3层到凤翔府

x552003_g_ScriptId = 552003
x552003_g_ask ={"前往领地-凤翔府","确定"}
x552003_g_answer ={"\t只要你付出500文现银或银卡，我就可以将你送往领地-凤翔府。\n\t你确认要前往领地-凤翔府吗？"}
x552003_g_Notice = "您的等级还不足#R40级#Y，无法进入领地-凤翔府！"

function x552003_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552003_g_ScriptId, x552003_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552003_g_answer[1])
			AddQuestNumText(sceneId, x552003_g_ScriptId, x552003_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
           		local strText = ""
				local CanTrans = IsCashboxState(sceneId,selfId)	
				if CanTrans == 1 then
					BeginQuestEvent(sceneId)
					strText = "#Y运镖或者护送状态中，不允许传送"
					AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return
				end
            	
            	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
					return
				end
  --扣除500文银卡或现银
  local Level = GetLevel(sceneId, selfId)
   			if Level >= 40 then
					if IsEnoughMoney(sceneId, selfId, 500) == 1 then	
							if SpendMoney(sceneId, selfId, 500,302) == 1 then

							NewWorld( sceneId, selfId, 5, 202 + random( 0, 5), 162 + random( 0, 5), 552003)
						 	end
					else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "\t现银或银卡不足，不能传送");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"现银或银卡不足，不能传送",8,2)			
					end
					
 			   elseif Level < 40 then
					   		Msg2Player(sceneId,selfId,"#Y"..x552003_g_Notice.."#W",4,3)
			end
         
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x552003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552003_g_ScriptId, x552003_g_ask[1],0,1)
end
