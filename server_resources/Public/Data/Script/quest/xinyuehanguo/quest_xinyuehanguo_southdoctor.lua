--���ܣ�����ҽ��
--NPC������ҽ��

x211033_g_ScriptId = 211033
x211033_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x211033_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
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

function x211033_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211033_g_ScriptId, x211033_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211033_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211033_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211033_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211033_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211033_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211033_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211033_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211033_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end