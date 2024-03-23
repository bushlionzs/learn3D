
x300660_g_ScriptId = 300660

--�����ı�����
x300660_g_MissionName="�����ҡ���ȡ��������"

--�������ID
x300660_g_King_QiCheng = 12050300

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300660_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 and CountryGetOfficial(sceneId,selfId)~=7 then
		return
	end
	AddQuestNumText(sceneId,x300660_g_ScriptId,x300660_g_MissionName,3)
end

function x300660_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�	

	local Readme_1 = "#Y�����ҡ���ȡ��������#W#r #r"	
	local Readme_2 = "\t��������ѩ˪ͬ��ë�����������ۡ�#r #r"
	local Readme_3 = "\t�λ����������򣬰�սɳ��սȺ�ۡ�#r #r"
	local Readme_4 = "\tѲ����¥�����죬һ��˻���仨�硣#r #r"
	local Readme_5 = "\t�����Ὣ����Ѱ���ֱֳ�����������#r #r"
	local Readme_6 = "#W���𾴵�#R"..GetName(sceneId, selfId).."#W�����򲻸������ˣ��������ڸ����ҵ���ʫ���еı�����ȷ�����Ϳ���һ�����ɡ�#r"	
	local Readme = Readme_1 .. Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x300660_g_ScriptId, -1 )
	
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x300660_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--����
--**********************************
function x300660_ProcAccept( sceneId, selfId )
	
	--�ٴμ���Ƿ��ǹ���������
	local official = CountryGetOfficial(sceneId,selfId)
	if official~=8 and official~=7 then
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ���������ǹ����������޷���ȡ�������", 8, 2 )
		return
	end
	
	--�ٴμ���Ƿ���ȡ��
	if CountryCanDrawBonus(sceneId,selfId,2) == 0 then
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����Ѿ���ȡ���������", 8, 2 )
		return
	end
	
	--�����û�������������У����Ѿ���ȡ����
	if HaveItem(sceneId, selfId,x300660_g_King_QiCheng)>0 or IsHaveHorse(sceneId, selfId,3004)>0 then
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����Ѿ���ȡ���������", 8, 2 )
		return
	end	
	
	--��ʼ����Ʒ
	BeginAddItem(sceneId)
	AddItem(sceneId,x300660_g_King_QiCheng,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret==1 then
		AddItemListToPlayer(sceneId,selfId)
		CountryDrawBonus(sceneId,selfId,2)	--����ȡ��־
		Msg2Player( sceneId,selfId, "��ϲ�������Ѿ��ɹ�������������", 8, 2 )
	else
		Msg2Player( sceneId,selfId, "�ܱ�Ǹ�����İ����������޷���ȡ�������", 8, 2 )
	end
	
end

--**********************************
--����
--**********************************
function x300660_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300660_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300660_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300660_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300660_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300660_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300660_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
