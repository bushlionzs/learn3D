--�Թ�6�㵽Ī˹��

x552007_g_ScriptId = 552007
x552007_g_ask ={"ǰ�����-Ī˹�ƹ���","ȷ��"}
x552007_g_answer ={"\tֻҪ�㸶��1��400���������������ҾͿ��Խ����������-Ī˹�ƹ�����\n\t��ȷ��Ҫǰ�����-Ī˹�ƹ�����"}
x552007_g_Notice = "���ĵȼ�������#R40��#Y���޷��������-Ī˹�ƹ�����"

function x552007_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
   local Level = GetLevel(sceneId, selfId)
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552007_g_ScriptId, x552007_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552007_g_answer[1])
			AddQuestNumText(sceneId, x552007_g_ScriptId, x552007_g_ask[2],0,2)
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
					      ReadyBusChangeScene(sceneId, 17,BusId)
                   NewWorld( sceneId, selfId, 17, 140.5 + random( 0, 5), 47 + random( 0, 5), 552007)
					         DeleteBus(sceneId, BusId,0)	
					      elseif Level < 40 then
					   		   Msg2Player(sceneId,selfId,"#Y"..x552007_g_Notice.."#W",4,3)
					    	end
				else
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
							return
					end
--�۳�1��400������������
  if Level >= 40 then
	       if IsEnoughMoney(sceneId, selfId, 1400) == 1 then
						
						if SpendMoney(sceneId, selfId, 1400,302) == 1 then
						     
							       NewWorld( sceneId, selfId, 17, 140.5 + random( 0, 5), 47 + random( 0, 5), 552007)
							 
						end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "\t�������������㣬���ܴ���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"�������������㣬���ܴ���",8,2)			
					 end
					               
   elseif Level < 40 then
	      Msg2Player(sceneId,selfId,"#Y"..x552007_g_Notice.."#W",4,3)
	 end
	 
  end
  
	end
		
end

--**********************************

--�о��¼�

--**********************************

function x552007_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552007_g_ScriptId, x552007_g_ask[1],0,1)
end
