--�����سǽű�

x270100_g_ScriptId = 270100
x270100_g_ask ={"�ص������˼䡤����","ȷ��"}
x270100_g_answer ={"\t��ȷ��Ҫ�뿪�˸��������������˼䡤������"}

function x270100_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x270100_g_ScriptId, x270100_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x270100_g_answer[1])
			AddQuestNumText(sceneId, x270100_g_ScriptId, x270100_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
			--if selfcountry ==0 then
					TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
					TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
					NewWorld(sceneId,selfId,39,173,173, 270100)
			--elseif selfcountry ==1 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,150,254,117, 270100)
			--elseif selfcountry ==2 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,250,254,117, 270100)
			--elseif selfcountry ==3 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,350,254,117, 270100)
			--end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x270100_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x270100_g_ScriptId, x270100_g_ask[1],0,1)
end








