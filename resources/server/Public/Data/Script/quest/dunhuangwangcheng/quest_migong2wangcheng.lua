--�Թ��سǽű�

x256000_g_ScriptId = 256000
x256000_g_ask ={"�ص�����","ȷ��"}
x256000_g_answer ={"\t��ȷ��Ҫ�뿪�Թ�8�㷵��������"}

function x256000_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256000_g_ScriptId, x256000_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256000_g_answer[1])
			AddQuestNumText(sceneId, x256000_g_ScriptId, x256000_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
			if selfcountry == 0 then
            NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 118 + random( 0, 5), 256000)
			elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 118 + random( 0, 5), 256000)
			elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 138 + random( 0, 5), 256000)
			elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 128 + random( 0, 5), 138 + random( 0, 5), 256000)
			end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x256000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x256000_g_ScriptId, x256000_g_ask[1],0,1)
end








