--�Թ�3�㵽���踮

x552003_g_ScriptId = 552003
x552003_g_ask ={"ǰ�����-���踮","ȷ��"}
x552003_g_answer ={"\tֻҪ�㸶��500���������������ҾͿ��Խ����������-���踮��\n\t��ȷ��Ҫǰ�����-���踮��"}
x552003_g_Notice = "���ĵȼ�������#R40��#Y���޷��������-���踮��"

function x552003_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
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
					strText = "#Y���ڻ��߻���״̬�У���������"
					AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return
				end
            	
            	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneId) == 0 then
					return
				end
  --�۳�500������������
  local Level = GetLevel(sceneId, selfId)
   			if Level >= 40 then
					if IsEnoughMoney(sceneId, selfId, 500) == 1 then	
							if SpendMoney(sceneId, selfId, 500,302) == 1 then

							NewWorld( sceneId, selfId, 5, 202 + random( 0, 5), 162 + random( 0, 5), 552003)
						 	end
					else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "\t�������������㣬���ܴ���");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"�������������㣬���ܴ���",8,2)			
					end
					
 			   elseif Level < 40 then
					   		Msg2Player(sceneId,selfId,"#Y"..x552003_g_Notice.."#W",4,3)
			end
         
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x552003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552003_g_ScriptId, x552003_g_ask[1],0,1)
end
