--�ֻ�֮�ػ������ű�

x256014_g_ScriptId = 256014
x256014_g_ask ={"�ص�������","ȷ��"}
x256014_g_answer ={"\t�����������ֻ����������ԣ���Ҳ����̫����ɥ��\n\t��Ҫ�뿪���������������"}

function x256014_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256014_g_ScriptId, x256014_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256014_g_answer[1])
			AddQuestNumText(sceneId, x256014_g_ScriptId, x256014_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            if level >=60 then
            	if IsQuestHaveDone(sceneId, selfId, 1522) > 0 then
            		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,15) == 0 then
							return
					end
            		NewWorld( sceneId, selfId, 15, 111 + random( 0, 5), 111 + random( 0, 5), 256014)
            	else 
            		BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t�ܱ�Ǹ����û�п�ͨ#G�����۵Ĵ���#W���Ҳ��ܽ����͵����")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x256014_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level >=60 then
			AddQuestNumText(sceneId, x256014_g_ScriptId, x256014_g_ask[1],0,1)
		end
end








