--���ܣ�������
--NPC��������

--MisDescBegin
x211035_g_ScriptId = 211035
x211035_g_MissionName = "����᡿������"

--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211035_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	
	
	local Readme_1 = "#Y����᡿������#W#r #r"
	
	local Readme_2 = "��������Ҫ�������������#r #r"
	
	local Readme_3 = "  1������������#G�ȼ�#W����#G20��#W��#r #r"
	
	local Readme_4 = "  2�������������#G�ް��״̬#W������#G�뿪���#W��#G24Сʱ#W���ϡ�#r #r"
	
	local Readme_5 = "�����������������#Gȷ��#W�Ϳ���#G�鿴���#W��Ϣ����һ�����ҵ����ǵİ�ᣬף���ɹ���#r #r"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x211035_g_ScriptId, -1 );	
end



--**********************************

--�о��¼�

--**********************************

function x211035_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
 	local pos = GetGuildOfficial(sceneId, selfId)--�ж��Ƿ��������
	if pos ~= -1 then
		return
	end
	AddQuestNumText(sceneId, x211035_g_ScriptId, x211035_g_MissionName, 3)
end



--**********************************

--����������

--**********************************

function x211035_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end
--**********************************

--����

--**********************************

function x211035_ProcAccept(sceneId, selfId)
	GuildList(sceneId, selfId, 0)
end



--**********************************

--����

--**********************************

function x211035_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211035_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211035_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x211035_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211035_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211035_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end