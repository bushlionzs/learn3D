--���ܣ�����ҽ��
--NPC������ҽ��

x211031_g_ScriptId = 211031
x211031_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x211031_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
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

function x211031_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211031_g_ScriptId, x211031_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211031_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211031_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211031_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211031_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211031_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211031_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211031_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211031_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end