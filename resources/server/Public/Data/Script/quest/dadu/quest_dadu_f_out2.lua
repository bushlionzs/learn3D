--�����سǽű�

x270102_g_ScriptId = 270102
x270102_g_ask ={"�ص������˼䡤����","ȷ��"}
x270102_g_answer ={"\t��ȷ��Ҫ�뿪�˸��������������˼䡤������"}

function x270102_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x270102_g_ScriptId, x270102_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x270102_g_answer[1])
			AddQuestNumText(sceneId, x270102_g_ScriptId, x270102_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
			--if selfcountry ==0 then
					TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
					TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
					NewWorld(sceneId,selfId,40,203,55, 270102)
			--elseif selfcountry ==1 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,150,254,117, 270102)
			--elseif selfcountry ==2 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,250,254,117, 270102)
			--elseif selfcountry ==3 then
			--		TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
			--		NewWorld(sceneId,selfId,350,254,117, 270102)
			--end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x270102_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x270102_g_ScriptId, x270102_g_ask[1],0,1)
end








