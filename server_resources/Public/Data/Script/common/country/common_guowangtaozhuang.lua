
x300657_g_ScriptId = 300657


--�����ı�����
x300657_g_MissionName="�����ҡ���ȡ������װ"

--������װID
x300657_g_King_Suit = 10300100

--**********************************
--������ں���
--**********************************
function x300657_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 and CountryGetOfficial(sceneId,selfId)~=7 then
		return
	end
	AddQuestNumText(sceneId,x300657_g_ScriptId,x300657_g_MissionName,3)
end
function x300657_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�	
	
	local Readme_1 = "#Y�����ҡ���ȡ������װ#r"	
	local Readme_2 = "#W�𾴵�#R"..GetName(sceneId, selfId).."#W���ã�#r"	
	local Readme_3 = "\t���˾Ϊ�����Ĵ�����һ��������˫��������װ�������Ѿ��깤��������������#r"	
	local Readme_4 = "\t���ȷ�����Ϳ��Խ������ߡ�#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4			
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x300657_g_ScriptId, -1 )
	
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x300657_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--����
--**********************************
function x300657_ProcAccept( sceneId, selfId )

	--�ٴμ���Ƿ��ǹ���������
	local official = CountryGetOfficial(sceneId,selfId)
	if official~=8 and official~=7 then
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ���������ǹ����������޷���ȡ������װ��", 8, 2 )
		return
	end
	
	--�ٴμ���Ƿ���ȡ��
	-- if CountryCanDrawBonus(sceneId,selfId,1) == 0 then
		-- Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����Ѿ���ȡ��������װ��", 8, 2 )
		-- return
	-- end
	
	--�����û��������װ
	if HaveItem(sceneId, selfId,x300657_g_King_Suit)>0 then
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����Ѿ���ȡ��������װ��", 8, 2 )
		return
	end
	
	--��ʼ����Ʒ
	BeginAddItem(sceneId)
	AddItem(sceneId,x300657_g_King_Suit,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret==1 then
		AddItemListToPlayer(sceneId,selfId)
		CountryDrawBonus(sceneId,selfId,1)	--����ȡ��־
		Msg2Player( sceneId,selfId, "��ϲ�������Ѿ��ɹ������������װ��", 8, 2 )
	else
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����İ����������޷���ȡ������װ��", 8, 2 )
	end
	
end

--**********************************
--����
--**********************************
function x300657_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--����
--**********************************
function x300657_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300657_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300657_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300657_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300657_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300657_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
