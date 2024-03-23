--迷宫8层到野外匈牙利

x552019_g_ScriptId = 552019
x552019_g_ask ={"前往领地-大马士革","确定"}
x552019_g_answer ={"\t只要你付出2两现银或银卡，我就可以将你送往领地-大马士革。\n\t你确认要前往领地-大马士革吗？"}
x552019_g_Notice = "您的等级还不足#R40级#Y，无法进入领地-大马士革！"

function x552019_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
   local Level = GetLevel(sceneId, selfId)
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552019_g_ScriptId, x552019_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552019_g_answer[1])
			AddQuestNumText(sceneId, x552019_g_ScriptId, x552019_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
				if BusId ~=-1 then
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
                    
					if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
					      if Level >= 40 then
					      ReadyBusChangeScene(sceneId, 23,BusId)
                   NewWorld( sceneId, selfId, 23, 104 + random( 0, 5), 139 + random( 0, 5), 552019)
					         DeleteBus(sceneId, BusId,0)	
					      elseif Level < 40 then
					   		   Msg2Player(sceneId,selfId,"#Y"..x552019_g_Notice.."#W",4,3)
					    	end
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
--扣除2两银卡或现银
  if Level >= 40 then
	       if IsEnoughMoney(sceneId, selfId, 2000) == 1 then
						
						if SpendMoney(sceneId, selfId, 2000,302) == 1 then
						     
							       NewWorld( sceneId, selfId, 23, 104 + random( 0, 5), 139 + random( 0, 5), 552019)
							 
						end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "\t现银或银卡不足，不能传送");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"现银或银卡不足，不能传送",8,2)			
					 end
					               
   elseif Level < 40 then
	      Msg2Player(sceneId,selfId,"#Y"..x552019_g_Notice.."#W",4,3)
	 end
	 
  end
  
	end
		
end

--**********************************

--列举事件

--**********************************

function x552019_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552019_g_ScriptId, x552019_g_ask[1],0,1)
end
