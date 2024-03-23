
x300740_g_ScriptId_ = 300740
x300740_g_MissionName = "�뿪����"
x300740_g_MissionInfo = "��Ҫ�뿪������"

--�����NPC��
function x300740_ProcEnumEvent( sceneId, selfId, targetId )

	AddQuestNumText(sceneId,x300740_g_ScriptId_,x300740_g_MissionName)
	
end



--�������ť������������ִ�д˽ű�
function x300740_ProcEventEntry( sceneId, selfId, targetId,state,index)	


	
		BeginQuestEvent(sceneId);AddQuestText(sceneId,x300740_g_MissionInfo);EndQuestEvent(sceneId);
		DispatchQuestInfo(sceneId, selfId, targetId, 300740, -1)
		

	
end



--�����ȷ����
function x300740_ProcAcceptCheck( sceneId, selfId )


	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,PK_PUNISH_PRISON_TIME_BUF_ID )

	if IsHaveFlag > 0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId,"ʱ��û���������ڼ��������������");EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"ʱ��û���������ڼ��������������",8,2)
		return
	end

	SetPKValue(sceneId, selfId, 0)
	SetCurPKMode(sceneId, selfId, 0, 1)		--ǿ��PKģʽΪ����ģʽ

	BeginQuestEvent(sceneId);AddQuestText(sceneId,"�����ˣ��ǵó�ȥ�Ժ�һ��Ҫ�͵�ѽ");EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,"�����ˣ��ǵó�ȥ�Ժ�һ��Ҫ�͵�ѽ",8,2)
	SetPlayerMutexState( sceneId, selfId,PLAYER_STATE_READYFUBEN,0 )
	SetPlayerMutexState( sceneId,selfId ,PLAYER_STATE_PRISON ,0)

	if GetLevel(sceneId, selfId) >= 10 then
		local PosX,PosY = 128,82
		if GetCurCountry( sceneId, selfId ) == 0 then--¥��
			NewWorld( sceneId, selfId ,50,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 1 then--��ɽ
			NewWorld( sceneId, selfId ,150,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 2 then--����
			NewWorld( sceneId, selfId ,250,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 3 then--�ػ�
			NewWorld( sceneId, selfId ,350,PosX,PosY,300740)
		end
	else
		local PosX,PosY = 76,62
		if GetCurCountry( sceneId, selfId ) == 0 then--¥��
			NewWorld( sceneId, selfId ,87,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 1 then--��ɽ
			NewWorld( sceneId, selfId ,187,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 2 then--����
			NewWorld( sceneId, selfId ,287,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 3 then--�ػ�
			NewWorld( sceneId, selfId ,387,PosX,PosY,300740)
		end		
	end

end

--**********************************
--����
--**********************************
function x300740_ProcAccept( sceneId, selfId )

end
--**********************************
--����
--**********************************
function x300740_ProcQuestAbandon( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300740_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300740_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300740_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId )
end
--**********************************
--ɱ����������
--**********************************
function x300740_ProcQuestObjectKilled( sceneId, selfId, objdataId )
end
--**********************************
--���������¼�
--**********************************
function x300740_ProcAreaEntered( sceneId, selfId, zoneId )
end
--**********************************
--���߸ı�
--**********************************
function x300740_ProcQuestItemChanged( sceneId, selfId, itemdataId )
end