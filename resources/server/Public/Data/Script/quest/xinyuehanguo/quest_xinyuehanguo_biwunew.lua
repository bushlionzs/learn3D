--���ܣ�������Ӫ
--NPC�����º��� �շ�

x211039_g_ScriptId = 211039
x211039_g_MissionName="��̨����"

--**********************************

--������ں���

--**********************************

function x211039_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������Ӫ")
		AddQuestText(sceneId, "��ָ���������Ӫ���������˾�û������Ĳ��ˣ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "��任Ϊ������Ӫ"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	SetCurCamp(sceneId, selfId, 0)
end



--**********************************

--�о��¼�

--**********************************

function x211039_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211039_g_ScriptId, "������Ӫ")
end



--**********************************

--����������

--**********************************

function x211039_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211039_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211039_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211039_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211039_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211039_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211039_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211039_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end