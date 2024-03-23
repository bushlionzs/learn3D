--寻龙任务脚本
x310054_g_ScritpId = 310054



function x310054_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end

function x310054_ProcEventEntry( sceneId, selfId, targetId, MissionId )

end


function x310054_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    
end

--杀死怪物
function x310054_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
		if NeedKilledNum >= 0 then
			local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
			for i = 0, KilledNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
								if InstIndex >= 0 then
									
									ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
										BeginAddItem(sceneId)
										AddItem( sceneId, ItemID, ItemDropNum )
										local ret = EndAddItem(sceneId,humanObjId)
										if ret > 0 then
											--AddItemListToPlayer(sceneId,selfId)
											AddItemListToPlayer(sceneId,humanObjId)

											--已经完成任务
											BeginQuestEvent(sceneId)
											local strText = format( "#Y已完成获得物品#G#{_ITEM%d}#Y: %d/%d", ItemID, 1, 1 )
											
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											DelQuest(sceneId, humanObjId, MissionId)
											GamePlayScriptLog(sceneId, humanObjId, 542)

										else
											BeginQuestEvent(sceneId)
											AddQuestText(sceneId,"背包已满，无法获得任务物品")
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



--物品改变
function x310054_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--寻找材料的任务完成后再添加合成任务

end


function x310054_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local str = "您放弃了任务：%s"

		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(str, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 4, 2)
	else
		--ret = -1
		--扣除任务物品失败处理
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
		target = "  消灭@npc_43004"
	elseif MissionId == 8055 then
		target = "  消灭@npc_44002"
	elseif MissionId == 8056 then
		target = "  消灭@npc_44006"
	elseif MissionId == 8057 then
		target = "  消灭@npc_45001"
	elseif MissionId == 8058 then
		target = "  消灭@npc_45002"
	elseif MissionId ==8059 then
		target = "  消灭@npc_45006"
	end


    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                str,                 -- 任务名字
                                target,               --任务目标
                                "无",                         --任务NPC
                                "",                   --任务攻略
                                "",                --任务描述
                                ""        --任务小提示
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end
