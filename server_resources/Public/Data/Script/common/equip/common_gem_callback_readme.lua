x800112_g_ScriptId = 800112
x800112_g_ask ={"����ʯ����˵����"}
x800112_g_answer ={"#Y����ʯ����˵����#W\n\t����ʹ�����������Ķ�ʱ�ʯ������������������ճ����Ӧ�ĳɱ���\n#Y����˵��#W��\n\t1.������#Gװ�����մ�ʦ#W���#Gװ�����մ�ʦ#W�Ի���\n\t2.ѡ��#G��ʱ�ʯ����#Wѡ�\n\t3.����Ҫ���յĶ�ʱ�ʯ���뵽��ʱ�ʯ���ս����м�ĸ����ڡ�\n\t4.��������·����հ�ť��\n#Yע������#W��\n\t���ж�ʱ�ʯ��������������һ���100%�ĳɱ���"}

function x800112_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[1])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[2])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[3])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[4])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[5])
			AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x800112_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[1],0,0)
end








