
x310201_g_ScriptId = 310201


--�����ı�����
x310201_g_MissionName="�����ҡ���������"


--**********************************
--������ں���
--**********************************
function x310201_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 then
		return
	end
	AddQuestNumText(sceneId,x310201_g_ScriptId,x310201_g_MissionName,3)	
end

function x310201_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�	
      
        
	local Readme_1 = "#Y�����ҡ���������#W#r #r"	
	local Readme_2 = "\t�𾴵Ĺ������£������Ը�⽫�����ڵ�����ޱȵĹ���λ�����ø����ĸ�������#r"
	local Readme_3 = "\t�������Ϊһʱ���첻���뵣�ι����ˣ���ô�ҽ������侲��������������������Ѿ�������#G��˼����#W����ô�ҿ��԰���������ù�����������#r"
	local Readme_4 = "\tÿ��#G���ܶ�����������#W���κ�ʱ�䣬����������������������ã�����#Gÿ��#Wֻ������#Gһ��#W������Ҫ�����Ĺ���λ�ú͹��Ҵ�Ȩ#G����#W����#G������#W��#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x310201_g_ScriptId, -1 )
	
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x310201_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--����
--**********************************
function x310201_ProcAccept( sceneId, selfId )
	if CountryGetOfficial(sceneId,selfId)~=8 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ǹ�����û��������λ��Ȩ����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ǹ�����û��������λ��Ȩ����",8,2)	
		return
	end
	
	if GetWeek() == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ղ��ܽ��й������á�")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ղ��ܽ��й������á�",8,2)
		return
	end		
	
	if GetWeek() == 2 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ܶ����ܽ��й������á�")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ܶ����ܽ��й������á�",8,2)
		return
	end
		CountryGuildDemise(sceneId, selfId)
		
end

--**********************************
--����
--**********************************
function x310201_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--����
--**********************************
function x310201_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310201_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x310201_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x310201_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x310201_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x310201_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
