x310051_g_scriptId = 310051 

x310051_g_Missionlist = { 8060, 8061,8062,8063,8064,8065 }
x310051_g_Missionlist2 = { 8054, 8055,8056,8057,8058,8059 }


function x310051_ProcEventEntry( sceneId, selfId, BagIndex )
	local level = GetLevel( sceneId, selfId )
	if level < 40 then
		local strText = "���ĵȼ�̫�ͣ����޷�����������İ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,"���ĵȼ�̫�ͣ����޷�����������İ���",8,2)
		return
	end
	
	local rand = random(1,6)
	local ret = 0
	if level >=40 and level<65 then
		for i, item in x310051_g_Missionlist do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then	-- ���û�������ֱ���˳�
				local strText = "���Ѿ��л��������������ˣ��޷��ظ���ȡ"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
				Msg2Player(sceneId,selfId,"���Ѿ��л��������������ˣ��޷��ظ���ȡ",8,2)
				return 
			end
		
		end

		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310051_g_Missionlist[rand] )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end

		ret = AddQuestNM( sceneId, selfId, x310051_g_Missionlist[rand])
	else
		for i, item in x310051_g_Missionlist2 do
			if IsHaveQuestNM( sceneId, selfId, item ) > 0 then	-- ���û�������ֱ���˳�
				local strText = "���Ѿ��л��������������ˣ��޷��ظ���ȡ"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
				Msg2Player(sceneId,selfId,"���Ѿ��л��������������ˣ��޷��ظ���ȡ",8,2)
				return 
			end
		
		end

		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x310051_g_Missionlist2[rand] )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0--���ǰ������û��ֱ�ӷ���
			end
		end

		ret = AddQuestNM( sceneId, selfId, x310051_g_Missionlist2[rand])

	end				
	
	if ret < 1 then
		if ret == -2 then
			local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return
		end

		local strText = "�������ʧ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		return 
	else
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ	
		local strText = "����������񣺻���������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,"����������񣺻���������",8,2)

		GamePlayScriptLog(sceneId, selfId, 541)
	end

	
end

function x310051_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310051_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x310051_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310051_OnDeplete( sceneId, selfId )

	return 0
end

function x310051_OnActivateOnce( sceneId, selfId )
end

function x310051_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
