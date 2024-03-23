
x310200_g_ScriptId = 310200


--�����ı�����
x310200_g_MissionName="�����ҡ���Ա��ְ"


--**********************************
--������ں���
--**********************************
function x310200_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if  CountryGetOfficial(sceneId,selfId)~=6 
	and CountryGetOfficial(sceneId,selfId)~=5
	and CountryGetOfficial(sceneId,selfId)~=4
	and CountryGetOfficial(sceneId,selfId)~=3
	and CountryGetOfficial(sceneId,selfId)~=2	then
		return
	end
	AddQuestNumText(sceneId,x310200_g_ScriptId,x310200_g_MissionName,3)
end
function x310200_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�	

	local Readme_1 = "#Y�����ҡ���Ա��ְ#W#r #r"	
	local Readme_2 = "\t��Ϊһ�����ҹ�Ա����������������Ҳ��һ��#G����#W�� #r"
	local Readme_3 = "\t�������Ϊһʱ���첻���뵣����Ŀǰ�Ĺ���ְ����ô�ҽ������侲��������������������Ѿ�������#G��˼����#W����ô�ҿ��԰�������ȥ����ְ���������#r"
	local Readme_4 = "\t���������������ǲ����Դ�ְ�ģ�ֻ�д󽫾�����ة�����ࡢ�����󲶡������Ҳ����Դ�ְ��#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x310200_g_ScriptId, -1 )
	
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x310200_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--����
--**********************************
function x310200_ProcAccept( sceneId, selfId )
	if  CountryGetOfficial(sceneId,selfId)~=6 
	and CountryGetOfficial(sceneId,selfId)~=5
	and CountryGetOfficial(sceneId,selfId)~=4
	and CountryGetOfficial(sceneId,selfId)~=3
	and CountryGetOfficial(sceneId,selfId)~=2	then
		return
	end
		DismissCountryOfficial_Self(sceneId, selfId)
		Msg2Player( sceneId,selfId, "��ϲ������ְ�ɹ���", 8, 2 )	
end

--**********************************
--����
--**********************************
function x310200_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--����
--**********************************
function x310200_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310200_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x310200_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x310200_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x310200_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x310200_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
