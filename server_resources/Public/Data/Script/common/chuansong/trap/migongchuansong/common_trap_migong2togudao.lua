--�Թ�1�㵽���

x552001_g_ScriptId = 552001
x552001_g_ask ={"ǰ���ŵ�","ȷ��"}
x552001_g_answer ={"\t��ȷ��Ҫǰ�������ŵ���"}

function x552001_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x552001_g_ScriptId, x552001_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x552001_g_answer[1])
			AddQuestNumText(sceneId, x552001_g_ScriptId, x552001_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
           --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
            local BusId = GetBusId(sceneId, selfId)
			if selfcountry == 0 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 86,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 112 + random( 0, 5), 135 + random( 0, 5), 552001)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 112 + random( 0, 5), 135 + random( 0, 5), 552001)
            	end
			elseif selfcountry ==1 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 186,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 169 + random( 0, 5), 110 + random( 0, 5), 552001)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 169 + random( 0, 5), 110 + random( 0, 5), 552001)
				end
			elseif selfcountry ==2 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 286,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 121 + random( 0, 5), 146 + random( 0, 5), 552001)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 121 + random( 0, 5), 146 + random( 0, 5), 552001)
				end
			elseif selfcountry ==3 then
				if BusId ~=-1 then

                    ReadyBusChangeScene(sceneId, 386,BusId)

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 158 + random( 0, 5), 116 + random( 0, 5), 552001)
					DeleteBus(sceneId, BusId,0)	
				else

                   NewWorld( sceneId, selfId, selfcountry * 100 + 86, 158 + random( 0, 5), 116 + random( 0, 5), 552001)
				end
			end
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x552001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x552001_g_ScriptId, x552001_g_ask[1],0,1)
end
