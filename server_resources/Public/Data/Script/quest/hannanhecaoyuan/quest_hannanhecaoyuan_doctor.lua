--���ܣ�����ҽ��
--NPC������ҽ��

x222002_g_ScriptId = 222002
x222002_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x222002_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�������")
		AddQuestText(sceneId, "�������Ѿ��ָ������ˣ�ȥ����������°ɡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "��ȫ��ָ��˽���"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
end



--**********************************

--�о��¼�

--**********************************

function x222002_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x222002_g_ScriptId, x222002_g_MissionName , 3 )
end



--**********************************

--����������

--**********************************

function x222002_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x222002_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x222002_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x222002_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x222002_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x222002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x222002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x222002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end