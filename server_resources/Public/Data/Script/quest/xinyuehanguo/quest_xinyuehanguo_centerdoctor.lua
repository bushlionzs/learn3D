--���ܣ�����ҽ��
--NPC������ҽ��

x211023_g_ScriptId = 211023
x211023_g_MissionName="�������"
--**********************************

--������ں���

--**********************************

function x211023_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�������")
		AddQuestText(sceneId, "\tĿǰ���������ڲ��Ϸ�չ�׶Σ����������Ϊ��������ơ��������Ѿ��ָ��˽�����ȥ����������°ɡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local	strText = "��ָ��˽���"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
end



--**********************************

--�о��¼�

--**********************************

function x211023_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211023_g_ScriptId, x211023_g_MissionName , 3 )
end



--**********************************

--����������

--**********************************

function x211023_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211023_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211023_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211023_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211023_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211023_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211023_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211023_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end