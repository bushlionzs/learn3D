--���ӡ�Ⱥ�

x300276_g_ScriptId = 300276
x300276_g_ask ={"�ص�����","ȷ��"}
x300276_g_answer ={"\t��Ҫ�뿪������ش�����"}

function x300276_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x300276_g_ScriptId, x300276_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300276_g_answer[1])
			AddQuestNumText(sceneId, x300276_g_ScriptId, x300276_g_ask[2],0,2)
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
           			NewWorld( sceneId, selfId, 30, 100 + random( 0, 5), 100 + random( 0, 5), 300276)
            	else 
            		BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t�ܱ�Ǹ����û�п�ͨ#G����Ĵ���#W���Ҳ��ܽ����͵����")
            		EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, NPCId)
            	end
            end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x300276_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level =GetLevel(sceneId, selfId)
		if level>= 40 then
			AddQuestNumText(sceneId, x300276_g_ScriptId, x300276_g_ask[1],0,1)
		end
end








