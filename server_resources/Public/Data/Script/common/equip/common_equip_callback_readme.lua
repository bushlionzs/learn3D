x800069_g_ScriptId = 800069
x800069_g_ask ={"��װ������˵����"}
x800069_g_answer ={"#Y��װ������˵����#W\n\t����ʹ���������������ﹱ��ս�����ֻ�����װ��������������������ճ����Ӧ�ĳɱ���\n#Y����˵��#W��\n\t1.������#Gװ�����մ�ʦ#W���#Gװ�����մ�ʦ#W�Ի���\n\t2.ѡ��#Gװ������#Wѡ�\n\t3.����Ҫ���յ�װ�����뵽װ�����ս����м�ĸ����ڡ�\n\t4.��������·����հ�ť��\n#Yע������#W��\n\t��ɫ��װ����������ֻ�ܶһ���70%�ĳɱ�������ɫ��װ����Ϊ������������Զһ���100%�ĳɱ���"}

function x800069_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800069_g_answer[1])
			--AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800069_g_answer[2])
			--AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800069_g_answer[3])
			--AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800069_g_answer[4])
			--AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800069_g_answer[5])
			AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x800069_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800069_g_ScriptId, x800069_g_ask[1],0,0)
end








