--���ܣ�����ҽ��
--NPC������ҽ��

x211029_g_ScriptId = 211029
x211029_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x211029_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�������")
		AddQuestText(sceneId, "Ŀǰ���������ڲ��Ϸ�չ�׶Σ�������Ҳ��Ӧ���٣�Ϊ���������ơ��������Ѿ��ָ������ˣ�ȥ����������°ɣ���Ҫ�ķ��˹�����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "��ȫ��ָ��˽���"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	RestoreHp(sceneId, selfId,100)
	RestoreRage(sceneId, selfId,100)
end



--**********************************

--�о��¼�

--**********************************

function x211029_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211029_g_ScriptId, x211029_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211029_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211029_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211029_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211029_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211029_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211029_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211029_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211029_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end