--敌国抢粮物品合成

x300630_g_MissionName="异国杀怪物品合成"
x300630_g_ItemID1 = 13011007         	--所需的物品
x300630_g_ItemID2 = 13011008         	--所需的物品
x300630_g_ItemID3 = 13011009         	--决定是否100%成功的物品
x300630_g_AwardItemId = 13010021        --奖励的物品

x300630_g_MissionId = 7017
x300630_g_KillMissionId =  7007

x300630_g_UICommandID = 100

--脚本号
x300630_g_ScriptId = 300630

x300630_g_OR_MIXTURE_FAIL = -2   --混合失败，物品不对
x300630_g_OR_FAIL = -1           --失败，有概率失败
x300630_g_OR_SUCC = 1            --成功

--**********************************
--列举事件
--**********************************
function x300630_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x300630_g_ScriptId,x300630_g_MissionName);
end


--**********************************
--任务入口函数
--**********************************
function x300630_ProcEventEntry( sceneId, selfId, targetId )

   	local ItemNum1 = GetItemCount( sceneId, selfId,x300630_g_ItemID1 )
    local ItemNum2 = GetItemCount( sceneId, selfId,x300630_g_ItemID1 )
	if ItemNum1 <= 0 or ItemNum2 <= 0 then
	 	BeginQuestEvent(sceneId);
		AddQuestText( sceneId, "材料不够，去采集足够的原材料在来合成吧！" );
		EndQuestEvent();
		DispatchQuestEventList(sceneId, selfId, -1)
		return
	end

	--告知客户端打开合成界面
	BeginUICommand(sceneId);
	UICommand_AddInt(sceneId, x300630_g_ScriptId);
	UICommand_AddInt(sceneId, targetId);
	DispatchUICommand(sceneId,selfId, x300630_g_UICommandID );
	EndUICommand(sceneId);

 	--DispatchQuestInfo( sceneId, selfId, targetId, x300630_g_ScriptId,-1 )

end


function x300630_OnMixture( sceneId, selfId, item1, item2, item3, item4 )

	local itemId = {-1,-1,-1,-1};
	local itemPos = { item1, item2, item3, item4 };

	for i=1, 4 do
		if itemPos[i] ~= -1 then
			itemId[i] = GetItemTableIndexByIndex( sceneId, selfId, itemPos[i] );
		end
	end

	local sign1 = -1;
	local sign2 = -1;
	local sign3 = -1;

	for i=1, 4 do
		local toggle = 0;

		if itemId[i] > 0 then

			if itemId[i] == x300630_g_ItemID1 then
				sign1 = i;
				toggle=1;
			elseif itemId[i] == x300630_g_ItemID2 then
				sign2 = i;
				toggle=1;
			elseif itemId[i] == x300630_g_ItemID3 then
				sign3= i;
				toggle=1;
			end

			if toggle == 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"放入的材料不正确")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0;
			end
			
		end

	end

	local result;
	local percent = 60;

	if sign3 ~= -1 then
		percent = 95;
	end

	if sign1~= -1 and sign2 ~= -1 then   --可以合成

		    result = 1;
			if percent >= random(1,95) then
				--成功
			else
				--失败
				EraseItem(sceneId, selfId, itemPos[sign1]); --删除物品
	       		EraseItem(sceneId, selfId, itemPos[sign2]);
	       		if percent == 95 then
                   EraseItem(sceneId, selfId, itemPos[sign3]);
	       		end
	       		
				--Msg2Player( sceneId, selfId, "#R合成失败", MSG2PLAYER_PARA );
				Msg2Player(sceneId,selfId,"合成失败",4,2)
				result = x300630_g_OR_FAIL;
				QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
				return 0
			end

			--删除物品
    		BeginAddItem(sceneId)
			AddItem( sceneId, x300630_g_AwardItemId, 1 )
			local ret = EndAddItem(sceneId,selfId)

			if ret > 0 then
				EraseItem(sceneId, selfId, itemPos[sign1]); --删除物品
	       		EraseItem(sceneId, selfId, itemPos[sign2]);
	       		
	       		if percent == 95 then
                   EraseItem(sceneId, selfId, itemPos[sign3]);
	       		end

	       		itemPos[sign1] = -1;
	        	itemPos[sign2] = -1;

				Msg2Player(sceneId,selfId,"合成成功",4,2)
				AddItemListToPlayer(sceneId,selfId)

				DelQuest(sceneId, selfId, x300630_g_KillMissionId);
				x300630_Accept(sceneId, selfId, x300630_g_MissionId )
				--Msg2Player( sceneId, selfId, "#R合成成功", MSG2PLAYER_PARA );
				
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法得到目标物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

	    result = x300630_g_OR_SUCC;

	else
		Msg2Player( sceneId, selfId, "#R请放入相应的物品", MSG2PLAYER_PARA );
		result = x300630_g_OR_FAIL;

	end

	QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );

	return 0;
end

function x300630_Accept( sceneId, selfId, MissionId )

	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return -3
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return -4
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return -5
		end
	end

	local	ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务

	local strText = GetQuestNameNM( sceneId, selfId, MissionId )

	strText = "接受任务:" .. strText
	if ret == 0 then
		strText = "添加任务失败"
	elseif ret == -1 then
		strText = "背包已满,请整理后再来接任务"
	elseif ret == -2 then
		strText = "任务已达到上限，无法接新的任务"
	else

		return 1
	end

	return -1
end

