--�ֻ�֮�ػش󶼽ű�

x256013_g_ScriptId = 256013
x256013_g_ask ={"�ص�����̳","ȷ��"}
x256013_g_answer ={"\t�����������ֻ����������ԣ���Ҳ����̫����ɥ��\n\t��Ҫ�뿪������ش���̳��"}

function x256013_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
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
            		AddQuestText(sceneId,"\t�ܱ�Ǹ����û�п�ͨ#G�󶼵Ĵ���#W���Ҳ��ܽ����͵����")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x256013_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level>= 40 then
			AddQuestNumText(sceneId, x256013_g_ScriptId, x256013_g_ask[1],0,1)
		end
end








