--�����Ʊ�ű�

--�ű���
x300673_g_scriptId 		= 300673 
--��Ʒ��
x300673_g_ItemID		= 13030128
--�����Ǯ����id
x300673_g_MissionId		= 7026
x300673_g_MissionId1	= 7027
x300673_g_MissionId2	= 7028
x300673_g_MissionId3	= 7029

--**********************************
--�¼��������
--**********************************
function x300673_ProcEventEntry( sceneId, selfId, bagIndex )

	if IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId ) == 1 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "�����Ʊ�ڵĽ�Ǯ���#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId1 ) == 1 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId1)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "�����Ʊ�ڵĽ�Ǯ���#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId2 ) == 1 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId2)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "�����Ʊ�ڵĽ�Ǯ���#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId3 ) == 1 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId3)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "�����Ʊ�ڵĽ�Ǯ���#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�㻹û�н��ܰ����������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�㻹û�н��ܰ����������",8,2)	
		return
	end

end

function x300673_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
