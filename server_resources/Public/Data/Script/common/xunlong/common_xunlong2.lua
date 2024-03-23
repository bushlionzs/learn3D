--Ѱ������ű�
x310054_g_ScritpId = 310054



function x310054_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end

function x310054_ProcEventEntry( sceneId, selfId, targetId, MissionId )

end


function x310054_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    
end

--ɱ������
function x310054_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID

	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
		if NeedKilledNum >= 0 then
			local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
			for i = 0, KilledNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
								if InstIndex >= 0 then
									
									ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
										BeginAddItem(sceneId)
										AddItem( sceneId, ItemID, ItemDropNum )
										local ret = EndAddItem(sceneId,humanObjId)
										if ret > 0 then
											--AddItemListToPlayer(sceneId,selfId)
											AddItemListToPlayer(sceneId,humanObjId)

											--�Ѿ��������
											BeginQuestEvent(sceneId)
											local strText = format( "#Y����ɻ����Ʒ#G#{_ITEM%d}#Y: %d/%d", ItemID, 1, 1 )
											
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											DelQuest(sceneId, humanObjId, MissionId)
											GamePlayScriptLog(sceneId, humanObjId, 542)

										else
											BeginQuestEvent(sceneId)
											AddQuestText(sceneId,"�����������޷����������Ʒ")
											EndQuestEvent(sceneId)
											DispatchQuestTips(sceneId,humanObjId)
										end
												
								end
							end

						end--end
					end
				end
			end
		end


end



--��Ʒ�ı�
function x310054_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����

end


function x310054_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local str = "������������%s"

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(str, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 4, 2)
	else
		--ret = -1
		--�۳�������Ʒʧ�ܴ���
	end
end

function x310054_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
end

function x310054_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
end

function x310054_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
	local target;

	if MissionId == 8054 then
		target = "  ����@npc_43004"
	elseif MissionId == 8055 then
		target = "  ����@npc_44002"
	elseif MissionId == 8056 then
		target = "  ����@npc_44006"
	elseif MissionId == 8057 then
		target = "  ����@npc_45001"
	elseif MissionId == 8058 then
		target = "  ����@npc_45002"
	elseif MissionId ==8059 then
		target = "  ����@npc_45006"
	end


    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- ����
                                str,                 -- ��������
                                target,               --����Ŀ��
                                "��",                         --����NPC
                                "",                   --������
                                "",                --��������
                                ""        --����С��ʾ
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end
