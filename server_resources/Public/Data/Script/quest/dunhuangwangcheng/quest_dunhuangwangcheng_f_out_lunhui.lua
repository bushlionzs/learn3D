--�����سǽű�

x256008_g_ScriptId = 256008
x256008_g_ask ={"�ص�����","ȷ��"}
x256008_g_answer ={"\t��ȷ��Ҫ�뿪�˸���������������"}

function x256008_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x256008_g_ScriptId, x256008_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256008_g_answer[1])
			AddQuestNumText(sceneId, x256008_g_ScriptId, x256008_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
			if selfcountry == 0 then
            NewWorld( sceneId, selfId, selfcountry * 100 + 50, 108 + random( 0, 5), 104 + random( 0, 5), 256008)
			elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 108 + random( 0, 5), 104 + random( 0, 5), 256008)
			elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 142 + random( 0, 5), 154+ random( 0, 5), 256008)
			elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 142 + random( 0, 5), 154 + random( 0, 5), 256008)
			end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x256008_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x256008_g_ScriptId, x256008_g_ask[1],0,1)
end








