--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x570060_g_ScriptId = 570060

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x570060_g_MissionName="ƽ���츳ѧϰ"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570060_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	if GetGameOpenById(1054 ) == 0 then
		return
	end
	local inherenceLevel = GetInherenceLevel( sceneId, selfId )
	if  inherenceLevel < 30 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����츳�ȼ�����30����������ѧϰƽ���츳��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		OpenInherenceBalanceStudyUI(sceneId, selfId)
	end
	return 0
end

--**********************************
--�о��¼�
--**********************************
function x570060_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(1054 ) == 0 then
		return
	end
	
	AddQuestNumText(sceneId,x570060_g_ScriptId,x570060_g_MissionName,3);
end


--********************
--����������
--**********************************
function x570060_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x570060_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x570060_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570060_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570060_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570060_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570060_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570060_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570060_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
