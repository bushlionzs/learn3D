--�����˼䡤�����뿪�ű�

x310328_g_ScriptId = 310328
x310328_g_ask ={"�뿪�����˼䡤����","ȷ��"}
x310328_g_answer ={"\t�������˼䡤��������þ���ô�������е���Щƣ�ͣ��ҿ��Խ����ͳ������˼䡤���룬���������ܼ���������Ѱ���޾��Ļ��֡�\n\t������Ҫ�뿪ô��"}
x310328_g_HongBuff		= 7536
x310328_g_LanBuff		= 7537
function x310328_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		local level =GetLevel(sceneId, selfId)
		if which == 0 then
		
			BeginQuestEvent(sceneId)
			AddQuestNumText(sceneId, x310328_g_ScriptId, x310328_g_ask[1],0,1)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x310328_g_answer[1])
			AddQuestNumText(sceneId, x310328_g_ScriptId, x310328_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			--local selfcountry =GetCurCountry( sceneId, selfId)
            --TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
            --TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
           if IsHaveSpecificImpact( sceneId, selfId, x310328_g_HongBuff) == 1 or IsHaveSpecificImpact( sceneId, selfId, x310328_g_LanBuff) == 1 then
           		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����״̬�޷����͡�")
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
           else
          	if IsHaveSpecificImpact( sceneId, selfId, 7717) == 1 then
							CancelSpecificImpact( sceneId, selfId, 7717)	
						end
           			NewWorld( sceneId, selfId, 36, 127 + random( 0, 5), 66 + random( 0, 5), 310328)
           end
       
        end
	

	
	
end


--**********************************

--�о��¼�

--**********************************

function x310328_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		
			AddQuestNumText(sceneId, x310328_g_ScriptId, x310328_g_ask[1],3,1)
end








