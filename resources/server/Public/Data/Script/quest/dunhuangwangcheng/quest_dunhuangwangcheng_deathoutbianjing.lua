--�ֻ�֮�ػر߾��ű�

x256012_g_ScriptId = 256012
x256012_g_ask ={"�ص�����","ȷ��"}
x256012_g_answer ={"\t�����������ֻ����������ԣ���Ҳ����̫����ɥ��\n\t��Ҫ�뿪������ر�����"}

function x256012_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local country = GetCurCountry(sceneId, selfId)
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256012_g_ScriptId, x256012_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
			
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256012_g_answer[1])
			AddQuestNumText(sceneId, x256012_g_ScriptId, x256012_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
		
			local selfcountry =GetCurCountry( sceneId, selfId)
           -- TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           -- TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            if level	>=	30 then
            	
            if IsQuestHaveDone(sceneId, selfId, 1502) > 0 then
            	
            	if country == 0 then 
            		NewWorld( sceneId, selfId, selfcountry * 100 + 51, 126.6 + random( 0, 5), 64 + random( 0, 5), 256012)
            	elseif 	country == 1 then 
            		NewWorld( sceneId, selfId, selfcountry * 100 + 51, 126 + random( 0, 5), 63 + random( 0, 5), 256012)
              elseif 	country == 2 then 
            		NewWorld( sceneId, selfId, selfcountry * 100 + 51, 131 + random( 0, 5), 182.5 + random( 0, 5), 256012)
            	elseif 	country == 3 then 
            		NewWorld( sceneId, selfId, selfcountry * 100 + 51, 131.5 + random( 0, 5), 183.5 + random( 0, 5), 256012)
            	end
           	else
           			BeginQuestEvent(sceneId)
            		AddQuestText(sceneId,"\t�ܱ�Ǹ����û�п�ͨ#G�������Źش���#W���Ҳ��ܽ����͵����")
            		EndQuestEvent()	
            		DispatchQuestEventList(sceneId, selfId, NPCId)

            end
            end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x256012_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			local level =GetLevel(sceneId, selfId)
			if level	>=	30 then
			AddQuestNumText(sceneId, x256012_g_ScriptId, x256012_g_ask[1],0,1)
			end
end








