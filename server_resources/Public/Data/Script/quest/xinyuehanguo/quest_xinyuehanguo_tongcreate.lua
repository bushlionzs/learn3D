--���ܣ�������
--NPC��������

--MisDescBegin
x211000_g_ScriptId = 211000
x211000_g_MissionName = "����᡿�������"

--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211000_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
	
	local Readme_1 = "#Y����᡿�������#W#r #r"
	
	local Readme_2 = "���������Ҫ�������������#r #r"
	
	local Readme_3 = " ��һ�����������ĵȼ�������ڻ����30����#r #r"
	
	local Readme_4 = " �ڶ�������������ӵ�е��������ڻ����50����#r #r"
	
	local Readme_5 = "���Ƿ�Ҫ������᣿"
	
	-- local Readme_6 = "  3�������������#G�����#W����#Gһ��#W��#r #r"
	
	-- local Readme_7=  "#G����#W�������434,373��������Լ�������ӣ�����һ�����ʻ�ð���"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5--..Readme_6..Readme_7
	
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x211000_g_ScriptId, -1 );
	
end



--**********************************

--�о��¼�

--**********************************

function x211000_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

  --�Ϸ�����
	local flag = GetMergeDBToggle()
	if flag==1 then
		return
	end
	
	--�������ݿ⿪��
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end

 	local pos = GetGuildOfficial(sceneId, selfId)--�ж��Ƿ��������
	if pos ~= -1 then
		return
	end
		AddQuestNumText(sceneId, x211000_g_ScriptId, x211000_g_MissionName,3)
end



--**********************************

--����������

--**********************************

function x211000_ProcAcceptCheck(sceneId, selfId, targetId)
	--1.����
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < 30 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "�ܱ�Ǹ�����ĵȼ�����30�����޷�������ᡣ");
		Msg2Player(sceneId, selfId,"�ܱ�Ǹ�����ĵȼ�����30�����޷�������ᡣ",8,2)
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0
	end
	--2.Ǯ
	local nMoney = GetMoney(sceneId, selfId, 0)
	if nMoney < 50000 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "�ܱ�Ǹ���������е���������50�����޷�������ᡣ");
		Msg2Player(sceneId, selfId,"�ܱ�Ǹ���������е���������50�����޷�������ᡣ",8,2)
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);		
		return 0
	end
	--3.�����
	-- if HaveItem(sceneId, selfId,11990001) < 1 then
        -- BeginQuestEvent(sceneId);
        -- AddQuestText(sceneId, "�ܱ�Ǹ����������û�а����޷�������ᡣ");
		-- Msg2Player(sceneId, selfId,"�ܱ�Ǹ����������û�а����޷�������ᡣ",8,2)
        -- EndQuestEvent();
        -- DispatchQuestTips(sceneId, selfId);		
		-- return 0
	-- end
	
	return 1
end
--**********************************

--����

--**********************************

function x211000_ProcAccept(sceneId, selfId)
	GuildCreate(sceneId, selfId, 0)
end



--**********************************

--����

--**********************************

function x211000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211000_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211000_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x211000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end