--Ѱ������ű�
x310053_g_ScritpId = 310053



function x310053_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end

function x310053_ProcEventEntry( sceneId, selfId, targetId, MissionId )

end


function x310053_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    
end

--ɱ������
function x310053_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
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
function x310053_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����

end


function x310053_ProcQuestAbandon( sceneId, selfId, MissionId )
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

function x310053_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
end

function x310053_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
end

function x310053_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
	local target;

	if MissionId == 8060 then
		target = "  ����@npc_72005"
	elseif MissionId == 8061 then
		target = "  ����@npc_72006"
	elseif MissionId == 8062 then
		target = "  ����@npc_72007"
	elseif MissionId == 8063 then
		target = "  ����@npc_72008"
	elseif MissionId == 8064 then
		target = "  ����@npc_72009"
	elseif MissionId == 8065 then
		target = "  ����@npc_72010"
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
