--���ܣ�������ȡ
--NPC�����º��� ���

x211015_g_ScriptId = 211015
x211015_g_MissionName="������ȡ"

--**********************************

--������ں���

--**********************************

function x211015_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������ȡ")
		AddQuestText(sceneId, "���ٹ���Ϊ���ҵķ�չ����˽�ķ������Լ��������ǲ������Ǵ�ҶԹ��ҵķ����ġ������ּ�⣬�����︺��Է���Ҫ��Ĺ������һ���Ĳ�����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211015_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211015_g_ScriptId, x211015_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211015_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211015_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211015_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211015_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211015_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211015_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211015_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211015_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end