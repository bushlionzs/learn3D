--���ܣ�PK��Ӫ
--NPC�����º��� �շ�

x211038_g_ScriptId = 211038
x211038_g_MissionName="��̨����"

--**********************************

--������ں���

--**********************************

function x211038_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#YPK��Ӫ")
		AddQuestText(sceneId, "�������Ѿ���PK��Ӫ�ˣ���Щ��������ս��ս�������Լ�������������Σ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "��任ΪPK��Ӫ"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	SetCurCamp(sceneId, selfId, 4)
end



--**********************************

--�о��¼�

--**********************************

function x211038_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211038_g_ScriptId, "PK��Ӫ")
end



--**********************************

--����������

--**********************************

function x211038_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211038_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211038_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211038_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211038_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211038_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211038_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211038_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end