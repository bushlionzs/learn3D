--�������

x300275_g_ScriptId = 300275
x300275_g_ask ={"�ص����踮","ȷ��"}
x300275_g_answer ={"\t��Ҫ�뿪������ط��踮��"}

function x300275_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x300275_g_ScriptId, x300275_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300275_g_answer[1])
			AddQuestNumText(sceneId, x300275_g_ScriptId, x300275_g_ask[2],0,2)
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
           			NewWorld( sceneId, selfId, 5, 146 + random( 0, 5), 60 + random( 0, 5), 300275)
            	else 
            		BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t�ܱ�Ǹ����û�п�ͨ#G���踮�Ĵ���#W���Ҳ��ܽ����͵����")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x300275_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level>= 40 then
			AddQuestNumText(sceneId, x300275_g_ScriptId, x300275_g_ask[1],0,1)
		end
end








