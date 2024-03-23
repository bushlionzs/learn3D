--���뵱����
--MisDescBegin
--�ű���
x800024_g_ScriptId = 800024

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800024_g_MissionName="�����ҡ��������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800024_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
	
	local Readme_1 = "#Y�����ҡ��������#W#r #r"
	
	local Readme_2 = "\t�ɼ�˼���У���Ҫ��Ϊ��������Ҫ�����ĸ�������#r #r"
	
	local Readme_3 = "  1���������е���������#G����50��#W��#r #r"
	
	local Readme_4 = "  2����������ĳ��#G���#W��#G����#W��#r #r"
	
	local Readme_5 = "  3������#G���ȼ�#W�������#G2��#W��#r #r"
	
	local Readme_6 = "  4������#G�������#W�������#G15��#W��#r #r"
	
	local Readme_7 = "���Ƿ����Ҫ���������"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7
	
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x800024_g_ScriptId, -1 )
	
end

--**********************************
--�о��¼�
--**********************************
function x800024_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local nCountry = GetCurCountry(sceneId, selfId)
	if CountryGetKingGUID(nCountry) == -1 then
		AddQuestNumText(sceneId,x800024_g_ScriptId,x800024_g_MissionName,3)
	end
end


--********************
--����������
--**********************************
function x800024_ProcAcceptCheck( sceneId, selfId, NPCId )
	--1. Ǯ
	if GetMoney(sceneId, selfId, 0) < 50000 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "��������50���������������");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	--2. �Ƿ����
	if GetGuildOfficial(sceneId, selfId) ~= 5 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "���ǰ����������������");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	local guildID = GetGuildID(sceneId, selfId)
	if guildID == -1 then
		return 0
	end
	
	local nLevel, nCount, nExp = GetGuildSimpleData(guildID)
	--3. ��ἶ��
	if nLevel<2 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "���ȼ�С��2���������������");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	--4. �������
	if nCount<15 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "����Ա����15�ˣ������������");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	return 1
end

--**********************************
--����
--**********************************
function x800024_ProcAccept( sceneId, selfId )
	ApplyKing(sceneId, selfId)
end

--**********************************
--����
--**********************************
function x800024_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800024_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800024_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800024_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800024_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800024_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800024_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
