
--����ϵͳȫ�ֺ����Ľű��ļ�

--�ű���
x888891_g_scriptId = 888891

x888891_g_AcceptMessage		= "#cffcf00������������%s"
x888891_g_AbandonMessage	= "#cffcf00������������%s"
x888891_g_CompleteMessage	= "#cffcf00�������%s����"
x888891_g_AbandonErrorMessage	= "#cffcf00����%s���ܱ�������"
x888891_g_BlueItemMissionList = {
									{misId = 9410, scriptId = 300783},
								}

function x888891_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return 0--���������ɣ�����
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- ������Խ��������
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
			AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
			return 1
		end
	end

	return 0
end

--ѡ������
function x888891_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	--����������Ѿ����ֱ���˳�(�ܻ���������)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������

		if  IsNpcHaveQuestNM(sceneId, selfId, targetId, MissionId) == 1 then--�����ж�npc�����Ƿ���������񣬷�����bug

			local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- ������Խ��������
				AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			else
				local strText = "#cffcf00δ֪�����޷����µ�����"
				if ret == -1 then
					strText = "#cffcf00�ȼ����㣬�޷����µ�����"
				elseif ret == -2 then
					strText = "#cffcf00�ȼ����ߣ��޷����µ�����"
				elseif ret == -3 then
					strText = "#cffcf00��Ǯ���㣬�޷����µ�����"
				elseif ret == -4 then
					strText = "#cffcf00�����Ǳ�����ң��޷����µ�����"
				elseif ret == -5 then
					strText = "#cffcf00ְҵ���Ͳ������޷����µ�����"
				elseif ret == -6 then
					strText = "#cffcf00��Ӫ�������޷����µ�����"
				elseif ret == -7 then
					strText = "#cffcf00�����޴�����"
				end
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		else
			local strText = "#cffcf00�����޴�����"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
	end
end

--��������
function x888891_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	--����������Ѿ����ֱ���˳�(�ܻ���������)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- ��ȡ������������Ϣ
	if ret > 0 then -- ������Խ��������
		local retAddMission = AddQuestNM( sceneId, selfId, MissionId ) -- ������������

		--SetPlayerAbilityLevel(sceneId, selfId, 26, 1)	--��ֹ��Ҳ���ɼ��������,playertemplate���ƺ󣬿��Բ���Ҫ�˶�

		for i = 0, 4 do
			local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, MissionId, i)
			if SceneID ~= -1 then
				CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
			end
		end
		
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x888891_g_AcceptMessage, MissionName);
		local strText = message
		if retAddMission == 0 then
			strText = "#cffcf00�������ʧ��"

            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)
            
            return 1

		elseif retAddMission == -1 then
			
            strText = "#cffcf00��������,�����������������"
            
            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)

            return 1

		elseif retAddMission == -2 then
            strText = "#cffcf00��������������"

            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)

            return 1
        end

        Msg2Player(sceneId, selfId, strText, 0, 2)
		Msg2Player(sceneId, selfId, strText, 0, 3)
		return 1
	end

	return 0
end

--ɱ������
function x888891_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
															--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )


	if NeedKilledNum == 0 then --ɱ�ֵ���Ʒ���͵�����
		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
                    local ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
                            --Ҫ�ռ��ĸ�������ƷID�������ʣ�һ��������
                    if ItemCount > 0 then
                        local ItemNumOnPlayer = GetItemCount( sceneId, humanObjId, ItemID )
                        if ItemNumOnPlayer < ItemCount then
                            local droprand = random(100)
                            if droprand <= ItemRand then
                                local dropnum = random(ItemDropNum)
                                if dropnum == 0 then
                                    dropnum = 1
                                end
                                if dropnum > ItemID - ItemNumOnPlayer then
                                    dropnum = ItemID - ItemNumOnPlayer
                                end
                                BeginAddItem(sceneId)
                                AddItem( sceneId, ItemID, dropnum )
                                local ret = EndAddItem(sceneId,humanObjId)
                                if ret > 0 then
                                    AddItemListToPlayer(sceneId,humanObjId)
                                else
                                    BeginQuestEvent(sceneId)
                                    AddQuestText(sceneId,"#cffcf00��Ʒ���������޷��õ�������Ʒ��")
                                    EndQuestEvent(sceneId)
                                    DispatchQuestTips(sceneId,humanObjId)
                                end
                            end
                        end
                    end
                end
            end
		end
	elseif NeedKilledNum > 0 then --������ɱ������
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, HumenNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
                if humanObjId ~= -1 then
                    if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
                                local strText = "";
                                local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
                                local KilledNum = GetQuestParam( sceneId, humanObjId, misIndex, InstIndex )

                            if KilledNum < NeedKilledNum then
                                    SetQuestByIndex( sceneId, humanObjId, misIndex, InstIndex, KilledNum+1 )
                                    if KilledNum == NeedKilledNum - 1 then
                                            --if IfQuestFinishdKillObjNM( sceneId, humanObjId, MissionId, InstIndex ) then
                                                --����ˡ���
                                                BeginQuestEvent(sceneId)
                                                if ObjName == "" then
                                                    if NeedKilledNum > 1 then
                                                        strText = format( "#cffcf00�������˹���(%d/%d)", KilledNum+1, NeedKilledNum )
                                                    else
                                                        strText = format( "#cffcf00�������˹���(%d/%d)", KilledNum+1, NeedKilledNum )
                                                    end
                                                else
                                                    if NeedKilledNum > 1 then
                                                        strText = format( "#cffcf00��������%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                                    else
                                                        strText = format( "#cffcf00��������%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                                    end
                                                end
                                                AddQuestText( sceneId, strText )
                                                EndQuestEvent( sceneId )
                                                DispatchQuestTips( sceneId, humanObjId )
                                            --end

                                            local MisCareNPC = QuestCareNPCNM( sceneId, humanObjId, misIndex )
                                            if MisCareNPC == 0 then --�����Զ����
                                                local ret = QuestCheckSubmitNM( sceneId, humanObjId, humanObjId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
                                                if ret > 0 then -- ����������
                                                    return x888891_MissionComplate( sceneId, humanObjId, humanObjId, -1, MissionId )
                                                end
                                            end
                                    else
                                            BeginQuestEvent(sceneId)
                                            if ObjName == "" then
                                                strText = format( "#cffcf00�������˹���(%d/%d)", KilledNum+1, NeedKilledNum )
                                            else
                                                strText = format( "#cffcf00��������%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                            end
                                            AddQuestText( sceneId, strText )
                                            EndQuestEvent( sceneId )
                                            DispatchQuestTips( sceneId, humanObjId )
                                    end
                            end
                    end
                end
		end
	end
	return 0
end


--�������
function x888891_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	
	--��������Ƿ������������
	if IsQuestCanAbandonNM(MissionId) <= 0 then
		local message = format(x888891_g_AbandonErrorMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)
		return		
	end
	
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local message = format(x888891_g_AbandonMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)

--		Msg2Player(sceneId, selfId, message, 4, 2);
	else
		--ret = -1
		--�۳�������Ʒʧ�ܴ���
	end
end

function x888891_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return
	end

	local npcName = GetName( sceneId, npcId )
	if npcName == "" then	--NPC���ֻ��ǿյ�ô
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	if guid ~= -1 then --�����������ɵ�NPC
		if guid == npcGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
			AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
		end
	else
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	end
end


--�������
--����1����ɹ���0��������ʧ��
function x888891_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	--����������Ѿ����ֱ���˳�(�ܻ���������)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
		local strText = "#cffcf00��û�н����������"
		if MissionName == nil or MissionName == "" then
			strText = "#cffcf00��û�н����������"
		else
			strText = format("#cffcf00��û�н���%s��", MissionName);
		end
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
	if ret > 0 then -- ����������
		return x888891_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--�������
function x888891_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId,selectId ) -- ��ȡ���������Ϣ
	if ret == 1 then -- ����ɹ����
		--��ʾ����������
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x888891_g_CompleteMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)

        --�ǵ��߽���
        QuestBonusNotItemNM(sceneId, selfId, MissionId )
		x888891_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)

        --���߽���
        QuestBonusItemNM(sceneId, selfId, MissionId ,selectId)

		local AfterMissionType, AfterMissionScript = GetAfterQuestIdNM( sceneId, selfId, MissionId )
		if AfterMissionScript ~= -1 then
			if AfterMissionType == 0 then
				--������һ������Ľ���
				x888891_ProcEventEntry( sceneId, selfId, targetId, AfterMissionScript )
			else
				--ֱ��PUSH��һ������
				PushAfterQuestNM( sceneId, selfId, targetId, AfterMissionScript )
			end
		end
		return 1 -- ���سɹ�
	else -- ���δ�ɹ����
		BeginQuestEvent(sceneId)
		local strText = "#cffcf00δ֪�����޷��������"
		if ret == -2 then
			strText = "#cffcf00��ѡ������Ʒ"
		elseif ret == -3 then
			strText = "#cffcf00��������,�����������������"
		elseif ret == -4 then
			strText = "#cffcf00�۳�������Ʒʧ��"
		end
		AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	return 0
end

function x888891_DisplayAwardInfo(sceneId, selfId, targetId, selectId, MissionId, moneyType, money, expAward, honorType, honor, vigorType,vigor, guildRewardType,guildReward)--��ʾ��ҽ�Ǯ���������Ľ�����Ϣ
	if MissionId >= 0 then
		moneyType, money, expAward, honorType, honor, vigorType,vigor, guildRewardType,guildReward = AwardMoneyExpHonorNM(sceneId, selfId, targetId, selectId, MissionId)
	end

	if expAward > 0 then
		Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", expAward),4,2)
	end

    if money > 0 then
		if moneyType == 0 then --��
			Msg2Player(sceneId,selfId,format("#cffcf00���#G#{_MONEY%d}#cffcf00���ҵĽ�����", money),4,2)
		elseif moneyType == 1 then -- ����
			Msg2Player(sceneId,selfId,format("#cffcf00���#G#{_MONEY%d}#cffcf00�����Ľ�����", money),4,2)
		elseif moneyType == 2 then --��
			Msg2Player(sceneId,selfId,format("#cffcf00���#G#{_MONEY%d}#cffcf00��ҵĽ�����", money),4,2)
		elseif moneyType == 3 then -- �󶨽�
			Msg2Player(sceneId,selfId,format("#cffcf00���#G#{_MONEY%d}#cffcf00�𿨵Ľ�����", money),4,2)
		else--�������
		end
	end

	if honor > 0 then
		if honorType == 0 then --��͢����
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", honor),4,2)
		elseif honorType == 1 then	--��������
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", honor),4,2)
		elseif honorType == 2 then --PK
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00PKֵ�Ľ�����", honor),4,2)
		elseif honorType == 3 then --����
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", honor),4,2)
		elseif honorType == 4 then -- �ﹱ
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00�ﹱֵ�Ľ�����", honor),4,2)
		elseif honorType == 5 then -- �Ĳ�
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00�Ĳ�ֵ�Ľ�����", honor),4,2)
		elseif honorType == 6 then -- ����
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", honor),4,2)
		elseif honorType == 7 then -- �츳ֵ
			Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00�츳ֵ�Ľ�����", honor),4,2)
		end
	end

    if vigorType >= 0 and vigor > 0 then
        
        if vigorType == 0 then              --����
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", vigor),4,2)
        elseif vigorType == 1 then          --����
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00����ֵ�Ľ�����", vigor),4,2)
        elseif vigorType == 2 then          --�츳
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00�츳ֵ�Ľ�����", vigor),4,2)
        end
    end

    if guildRewardType ~= nil and  guildRewardType >= 0 and guildReward > 0 then
        
        if guildRewardType == 0 then
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00��ᾭ��ֵ�Ľ�����", guildReward),4,2)
        elseif guildRewardType == 1 then
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00������Դ-ʳ��Ľ�����", guildReward),4,2)
        elseif guildRewardType == 2 then
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00������Դ-��Ǯ�Ľ�����", guildReward),4,2)
        elseif guildRewardType == 3 then
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00������Դ-ľ�ĵĽ�����", guildReward),4,2)
        elseif guildRewardType == 4 then
            Msg2Player(sceneId,selfId,format("#cffcf00���#G%d��#cffcf00������Դ-�����Ľ�����", guildReward),4,2)
        end
    end

end

--��Ʒ�ı�
function x888891_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType)

    if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end    
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --��û���������

            if nChangeType == 0 then --ɾ����Ʒ������ʾ
                BeginQuestEvent(sceneId)
                local strText = format("#cffcf00���������Ʒ#G#{_ITEM%d}#cffcf00(%d/%d)", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num >= NeedNum then
			
			--��������
			local ShowNum = Num 
			if ShowNum > NeedNum then
				ShowNum = NeedNum
			end
			
			--�Ѿ��������
            if nChangeType == 0 then --ɾ����Ʒ������ʾ
                BeginQuestEvent(sceneId)
                local strText = format( "#cffcf00���������Ʒ#G#{_ITEM%d}#cffcf00(%d/%d)", itemdataId, ShowNum, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, ShowNum )         --by zheng
			--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --�����Զ����
				local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
				if ret > 0 then -- ����������
					return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
				end
			end
		end
	else
        if ObjIndex >= 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, 0 )         --by czg
        end

    end
end

function x888891_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

    if MissionId < 0 then
        return 0
    end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local MissionIdx = GetQuestEnterAreaIndexNM( sceneId, selfId, MissionId, zoneId )
	if MissionIdx == -1 then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 0 then
		SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )
		SendQuestEnterAreaTipsNM( sceneId, selfId, selfId, MissionId, MissionIdx )
	end

	--�����Զ����
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --�����Զ����
		local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
		if ret > 0 then -- ����������
			return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
		end
	end

	return 1
end

--�뿪����
function x888891_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
end

--����ʱ��
function x888891_ProcTiming( sceneId, selfId, ScriptId, MissionId )
end


--**********************************************************************
--����ʹ����Ʒ����
function x888891_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--����������Ѿ����ֱ���˳�

	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --�õ���ƷID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--û���ҵ��������
		return 0
	end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr, errorStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	if scene == -1 or sceneId ~= scene then --û���ҵ����������Ϣ
		local strText = errorStr
        if errorStr == nil or errorStr == "" then
            strText = "#cffcf00�޷�������ʹ�������Ʒ����鿴����������"
        end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		return 0
	end

	if posx > 0 then --��Ҫ���ص�
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
            local strText = errorStr
            if errorStr == nil or errorStr == "" then
			    --strText = format("��Ӧ����@sceneid_%d[%d,%d]ʹ�ô���Ʒ��", scene, posx, posz )
                strText = "#cffcf00�޷�������ʹ�������Ʒ����鿴����������"
            end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			return 0
		end
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
		return 0
	end

	--ɾ����Ʒ
	EraseItem(sceneId, selfId, BagIndex)

	--������ʾ
	SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, dispStr)
	DispatchQuestTips(sceneId,selfId) 
	EndQuestEvent(sceneId)

	--����Ч��
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end

	--�����Զ����
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --�����Զ����
		local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
		if ret > 0 then -- ����������
			return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
		end
	end

	return 1
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x888891_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 1 --û���������
	end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 1
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId)
		local str = "#cffcf00��û�н����������"
		if MissionName == nil or MissionName == "" then
			str = "#cffcf00��û�н����������"
		else
			str = format("#cffcf00��û�н���%s��", MissionName);
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		local str = "#cffcf00��Ʒ�Ѿ��ռ���ȫ��"
		if needItemCount > 0 then	
			str = "#cffcf00��Ʒ�Ѿ��ռ���ȫ��";
		else
			str = "#cffcf00������Ҫ�����Ʒ��";
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	return 0
end

--����
function x888891_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 1 --û���������
	end

	--����������Ѿ����ֱ���˳�
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00��Ʒ�Ѿ��ռ���ȫ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--����һ�βɼ�����
	local itemAdd = needItemCount - itemCountNow
	if collNum == -1 then
		itemAdd = 1
	else
		if itemAdd > collNum then
			itemAdd = collNum
		end
	end
	if itemAdd > 1 then
		itemAdd = random(itemAdd)
		if itemAdd == 0 then
			itemAdd = 1
		end
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00�޷��õ��ɼ���Ʒ���������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
end

--��
function x888891_OnProcOver( sceneId, selfId, targetId )
end

--�򿪺���
function x888891_OpenCheck( sceneId, selfId, targetId )
end


--**********************************************************************

--���󴴽�BUS
function x888891_CreateBus( sceneId, selfId, targetId, MissionId )
	--ȡ���������λ��
	local PosX,PosZ = GetWorldPos(sceneId, selfId)
	
	--��ʼ��һЩ��������,�Ժ�ű��ӿ����˺�,ɾ������,����������д�
	--local	CarType, BaseAI, AIScript, EventScript, Impact,ShapeType, Name, Title = 1 , 3 , -1, MISSION_SCRIPT, 1210, -1, "�޵����ڳ�", "�����ھ�"
	--local	WaitTime,  LifeTime = 5, 120
	--local	PatrolID = 0
	
	--ͨ���ű��ӿڡ� GetQuestBusInfoNM(sceneId, selfId, misIndex)��ȡ�����͵�BUS��һЩ��Ϣ
	--      BUS���͡�����AI����չAI��  ���¼��ű����ϳ�BUFF			
	local  CarType, BaseAI, AIScript, EventScript, Impact, Name, Title, WaitTime,  LifeTime, PatrolID = GetQuestBusInfoNM(sceneId, selfId, MissionId)
	
	--��ʽ����BUS
	local ObjID = CreateBus(sceneId, CarType, PosX, PosZ, BaseAI, AIScript, EventScript, selfId, Impact, MissionId,targetId)
end

--**********************************************************************
--bus�����ɹ�
function x888891_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)

	--�޸�BUS������,��û����BUS�ı���BUFF,��ʱ������
	--SendSpecificImpactToUnit(sceneId, selfId, selfId, ObjID, nImpactDataIndex, nDelayTime)

	--�޸�BUS��title
	local  CarType, BaseAI, AIScript, EventScript, Impact, Name, Title, WaitTime,  LifeTime, PatrolID = GetQuestBusInfoNM(sceneId, selfId, MissionId)	
	local BusTitle = GetName( sceneId, selfId ).."��"..Title
	SetBusTitle(sceneId , busId, BusTitle)
	
	--�޸�BUS������,Ŀǰ�ýӿڻ�û��
	--SetBusName(sceneId , busId, Name)
	
	--����BUS�Ŀճ�ʱ��/����ʱ��
	SetBusTimerTick(sceneId , busId, 1000)
	SetBusTimerOpen(sceneId, busId, 1)
	if WaitTime>0 then
		SetBusWaitTime(sceneId , busId, WaitTime)
	end
	if LifeTime>0 then
		SetBusLifeTime(sceneId , busId, LifeTime)
	end
	
	--ȡ��BUS������,0--�ڳ���1--BUS��2--����ΪBUS���ڳ�,2��ʹ��
	local BusType  = GetBusType(sceneId, busId)
	local MessageStr = ""
	if BusType == 0 then
		MessageStr = "�㿪ʼ������"
	elseif BusType == 1 then
		--���͵Ļ�,�����Զ�Ѳ��·��
		if PatrolID == -1 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"������д��ȫ,����û�а�Ѳ��·��");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)	
			return
		end
		SetBusPatrolId(sceneId , busId, PatrolID)
		MessageStr = "�㿪ʼ������,��Ҫ�뿪BUS����5��"
	else
		MessageStr = "-_!!������д����,�����"	
	end
		
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,MessageStr);
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)	
end




function x888891_DeleteBus(sceneId, ObjId)		
	DeleteBus(sceneId, ObjId,1)
end


--����������BUS
--selfId�����ID
--targetId��BUSID
function x888891_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ��ڳ�����");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"�������Ѿ�������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end
	

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )	
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

--����뿪BUS
--selfId�����ID
function x888891_OnLeaveBusEvent(sceneId, selfId,BusId)
	local BusType  = GetBusType(sceneId, BusId)
	if BusType == 0 then	
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"���������ڣ��޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
	elseif  BusType == 1 then	
		DelBusMember(sceneId, selfId,BusId)
	end
end


function x888891_OnTime(sceneId, BusId, MissionId)
    
    --���ID�Ƿ���Ч
    if( IsObjValid(sceneId,BusId) ~= 1 )then
        return
    end
    
	local BusPosX, BusPosZ = GetWorldPos(sceneId, BusId)
	--��������
	local EndSceneID = -1
	local EndPosX = 0
	local EndPosZ = 0
	
	--ȡ������Ҫ�͵��ĵط����Զ�Ѱ·����(Mission_List.tab�����),ͨ����������鵽�յ������,
	local roadId = GetQuestXunLuIndexNM( MissionId )
	if roadId > 0 then
		EndSceneID,EndPosX,EndPosZ = GetQuestEndPosNM( roadId )
	else
        --�˴�û�����죬Ŀǰ���ι��޸ģ����������ҳ��ι� 2009-02-10
		--BeginQuestEvent(sceneId)
		--  AddQuestText(sceneId,"�յ�����û����д��ȷ,����");
		--EndQuestEvent()
		--DispatchQuestTips(sceneId,selfId)
		return
	end

	if sceneId == EndSceneID then
		local distance = floor((BusPosX-EndPosX)*(BusPosX-EndPosX)+(BusPosZ-EndPosZ)*(BusPosZ-EndPosZ))
		if distance<100 then
			
			--������������ɴ���,���к���������Ҫ ���� ���
			local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"�������");
			EndQuestEvent()
			DispatchQuestTips(sceneId,PlayerId)
			x888891_DeleteBus(sceneId, BusId)	
			
			local misIndex = GetQuestIndexByID( sceneId, PlayerId, MissionId )	--�õ�������ϵ���������
			local MissionIdx = GetQuestHuSongIndexNM( sceneId, PlayerId, MissionId )	--�õ�����������Mission_List���е����� 0-4
			if MissionIdx > 0 and misIndex > 0 then
				if GetQuestParam( sceneId, PlayerId, misIndex, MissionIdx ) == 0 then
					SetQuestByIndex( sceneId, PlayerId, misIndex, MissionIdx, 1 )	--���û����������
				end
			end
		end
	end
end

function x888891_OnLifeTimeOut(sceneId, BusId, MissionId)
	
	--����������ʧ�ܴ���,���к���������Ҫ ���� ���
	
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"����ʧ��");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)
	x888891_DeleteBus(sceneId, BusId)
	
	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R��������["..MissionName.."]ʧ�ܣ�", MSG2PLAYER_PARA )
	end
end

function x888891_OnWaitTimeOut(sceneId, BusId, MissionId)
	
	--����������ʧ�ܴ���,���к���������Ҫ ���� ���
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"����ʧ��");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)
	x888891_DeleteBus(sceneId, BusId)

	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R��������["..MissionName.."]ʧ�ܣ�", MSG2PLAYER_PARA )
	end
end

function x888891_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x888891_OnDie( sceneId, killerId , BusId, MissionId)
	--����������ʧ�ܴ���,���к���������Ҫ ���� ���
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"����ʧ��");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)

	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R��������["..MissionName.."]ʧ�ܣ�", MSG2PLAYER_PARA )
	end
end

function x888891_OnSelectSubmitItem( sceneId, selfId , bagIndex,nGuid_Serial, nGuid_Server, nGuid_World)
	
	for i,item in x888891_g_BlueItemMissionList do
		if IsHaveQuestNM( sceneId, selfId, item.misId )>0 then
			CallScriptFunction(item.scriptId,"OnSelectSubmitItem", sceneId,selfId,bagIndex,nGuid_Serial, nGuid_Server, nGuid_World)
		end
	end
	return 1
end