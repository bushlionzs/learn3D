x800068_g_ScriptId = 800068
x800068_g_ask ={"װ����ֵ���缶װ����˵��"}
x800068_g_answer ={"\t�缶װ����ֵ�����Խ�ԭ��װ�������ǣ�������̣��齫���̣���ף���ɫ���������ĸ��Ƶ���װ���ϡ�\n\tֻ�ܽ����ּ�װ����������Ը��Ƶ����ּ�װ���ϣ������ּ�װ������Ϊ��ɫװ��������ֵװ����Ʒ�ʣ�����������ȫһ�£���ֵ���װ�����Ϊ��װ����\n\tע�⣺ԭ��װ����#G����#W��#G�������#W��#G�齫����#W��#G���#W��#G��ɫ����#W�������ԣ�������ȫ������װ���Ĵ��������ԣ�#R���ԭ��װ��û��ĳ�����ԣ���װ��Ҳ����û�С�"}

function x800068_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[1])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[2])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[3])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[4])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[5])
			AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x800068_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[1],0,0)
end








