x800067_g_ScriptId = 800067
x800067_g_ask ={"װ����ֵ��ͬ��װ����˵��"}
x800067_g_answer ={"\tͬ��װ����ֵ�����Խ�ԭ��װ�������ǣ�������̣��齫���̣���ף���ɫ���������ĸ��Ƶ���װ���ϡ�\n\t��ֵ��װ����ԭ��װ������ΪƷ�ʣ�������ȫһ�µ����ּ�װ�������ּ�װ�����ұ�ֵ���װ�����Ϊ��װ����ԭ��װ������Ϊ��ɫװ����\n\tע�⣺ԭ��װ����#G����#W��#G�������#W��#G�齫����#W��#G���#W��#G��ɫ����#W�������ԣ�������ȫ������װ���Ĵ��������ԣ�#R���ԭ��װ��û��ĳ�����ԣ���װ��Ҳ����û�С�"}

function x800067_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800067_g_answer[1])
			--AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800067_g_answer[2])
			--AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800067_g_answer[3])
			--AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800067_g_answer[4])
			--AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800067_g_answer[5])
			AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--�о��¼�

--**********************************

function x800067_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800067_g_ScriptId, x800067_g_ask[1],0,0)
end








