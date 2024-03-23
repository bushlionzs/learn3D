x570058_g_ScriptId = 570058
x570058_g_ScriptName = "二级平衡之书合成"
x570058_g_UICommandID = 100
x570058_g_Mixture_RESULT_LESS = -2  --物品不正确
x570058_g_Mixture_RESULT_FAILD = -1	--物品合成失败，有概率失败
x570058_g_Mixture_RESULT_OK = 1	--物品合成成功
x570058_g_Mixture_AddItem_UseType = 0	--特定物品使用类型 对应代码 eITEM_SPECIAL_USETYPE

--合成配置表
x570058_MixConfTable       = {itemid1 = 11010111, itemid1count = 2, itemid2 = 11010120, itemid2count = 1, itemid3 = 11010121, itemid3count = 1, itemid4 = -1,       itemid4count = 0, isNeedAdded = 1, mixitem = 11010112 , mixitemcount = 1, SuccRate = 50,  type = 570058 }


x570058_MixConfTable_Ext      = {
									{itemId = 11010111, alwaysKeep = 1},
									{itemId = 11010120, alwaysKeep = 0},
									{itemId = 11010121, alwaysKeep = 0},
								}

function x570058_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x570058_g_ScriptId, x570058_g_ScriptName,3)
end

function x570058_ProcEventEntry( sceneId, selfId, targetId, MissionId )--告知客户端打开合成界面
    BeginUICommand(sceneId);
    UICommand_AddInt(sceneId, x570058_g_ScriptId);
    UICommand_AddInt(sceneId, targetId);
    DispatchUICommand(sceneId,selfId, x570058_g_UICommandID);
    EndUICommand(sceneId);
end

function x570058_OnMixture( sceneId, selfId, item1, item2, item3, item4 ,AddedItemPos)

	local itemcount = 0;
	local itemId = {-1,-1,-1,-1};
	local itemPos = { item1, item2, item3, item4 };

	for i=1, 4 do
		if itemPos[i] ~= -1 then
			itemId[i] = GetItemTableIndexByIndex( sceneId, selfId, itemPos[i] );
			if( itemId[i] > 0 ) then
				itemcount = itemcount + 1;
			end
		end
	end

	--检查是否可以合成
	if x570058_CheckItemCanMixture(itemId[1], itemId[2], itemId[3], itemId[4]) <=0 then
		BeginQuestEvent(sceneId);
		AddQuestText( sceneId,"放入的道具不正确，无法合成");
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		return x570058_g_Mixture_RESULT_LESS;		
	end

	--检查材料是否足够
	if x570058_CheckItemCount(sceneId, selfId,itemId[1], itemId[2], itemId[3], itemId[4]) <=0 then
		BeginQuestEvent(sceneId);
		AddQuestText( sceneId,"放入的道具不足，无法合成");
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		return x570058_g_Mixture_RESULT_LESS;				
	end

    --只要有一件材料是绑定的，生成的物品就是绑定的
    local isBind = 0
    for i, item in itemPos do
    	if item ~= -1 then
			if IsItemBind( sceneId, selfId, item) == 1 then
				isBind = 1
				break
			end
		end
    end

	local nAddItemId = 	-1
	if x570058_isNeedAddedItem() > 0 then
		nAddItemId = x570058_GetAndCheckAddedItemId(sceneId, selfId,AddedItemPos)
		if nAddItemId == -2 then
			BeginQuestEvent(sceneId);
			AddQuestText( sceneId,"放入的消耗材料不正确，无法合成");
			EndQuestEvent( sceneId);
			DispatchQuestTips( sceneId, selfId);
			return x570058_g_Mixture_RESULT_LESS;				
		end
	end

    -- 合成物品
	if x570058_IsMixtureRandOK() == 1 then

		BeginAddItem( sceneId);
		if isBind == 0 then
			AddItem( sceneId, x570058_MixConfTable.mixitem, x570058_MixConfTable.mixitemcount)
		else
			AddBindItem( sceneId, x570058_MixConfTable.mixitem, x570058_MixConfTable.mixitemcount)
		end

		local ret = EndAddItem( sceneId, selfId)
		if ( ret > 0 ) then

			--消耗特殊物品
			if x570058_isNeedAddedItem() > 0 and nAddItemId > 0 then
				EraseItem( sceneId, selfId, AddedItemPos, 1)			
			end

			for i = 1, 4 do
				if( itemPos[ i] ~= -1) then
					local nDelCount = x570058_GetItemNeedCountByItemPos(sceneId, selfId, itemPos[ i])
					local nCurPosCount = GetItemCountInBagPos(sceneId, selfId,itemPos[ i])

					local nCurPosDelCount = nDelCount
					local nOtherPosDelCount = nDelCount - nCurPosCount;									 

					if nDelCount > nCurPosCount then
						nCurPosDelCount = nCurPosCount
					end

					if nCurPosDelCount > 0 then
						EraseItem( sceneId, selfId, itemPos[i], nCurPosDelCount)
					end

					if nOtherPosDelCount > 0 then
						 DelItemByIDInBag(sceneId,selfId,itemId[i],nOtherPosDelCount)
					end
				end
			end

			AddItemListToPlayer(sceneId,selfId);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "合成成功！" );
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId)
			QuestMixtureResult( sceneId, selfId, x570058_g_Mixture_RESULT_OK, itemPos[1], itemPos[2], itemPos[3], itemPos[4] )
			return x570058_g_Mixture_RESULT_OK
		else
			BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "物品栏已满，无法合成物品！" )
			EndQuestEvent( sceneId)
			DispatchQuestTips( sceneId,selfId)
			return x570058_g_Mixture_RESULT_LESS
		end
	else

		--消耗特殊物品
		if x570058_isNeedAddedItem() > 0 and nAddItemId > 0 then
			EraseItem( sceneId, selfId, AddedItemPos, 1)			
		end

		--合成失败也需扣除材料
		for i = 1, 4 do
			if( itemPos[ i] ~= -1) then
				--失败情况不删除物品的条件是:有消耗特殊物品及材料可以保留
				if x570058_isNeedAddedItem() <= 0  or  nAddItemId <= 0 or x570058_isAlwaysKeep(itemId[i]) <= 0 then
					local nDelCount = x570058_GetItemNeedCountByItemPos(sceneId, selfId, itemPos[ i])
					local nCurPosCount = GetItemCountInBagPos(sceneId, selfId,itemPos[ i])

					local nCurPosDelCount = nDelCount
					local nOtherPosDelCount = nDelCount - nCurPosCount;									 

					if nDelCount > nCurPosCount then
						nCurPosDelCount = nCurPosCount
					end

					if nCurPosDelCount > 0 then
						EraseItem( sceneId, selfId, itemPos[i], nCurPosDelCount)
					end

					if nOtherPosDelCount > 0 then
						 DelItemByIDInBag(sceneId,selfId,itemId[i],nOtherPosDelCount)
					end
				end
			end
		end

		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "合成失败！" );
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId)
		QuestMixtureResult( sceneId, selfId, x570058_g_Mixture_RESULT_OK, itemPos[1], itemPos[2], itemPos[3], itemPos[4] )
		return x570058_g_Mixture_RESULT_OK
	end
end

---------------------------------------------------------------------------
--检查材料是否可以合成
---------------------------------------------------------------------------
function x570058_CheckItemCanMixture( itemid1, itemid2, itemid3, itemid4 )
	
	--检查材料类型数量
	if x570058_GetMixItemIdInputCount(itemid1, itemid2, itemid3, itemid4) < x570058_GetMixItemIdNeedCount() then
		return -1
	end

	--检查材料是否匹配
	if x570058_CheckItemFull(itemid1, itemid2, itemid3, itemid4) <=0 then
		return -1
	end

	return 1
end

---------------------------------------------------------------------------
--检查材料是否匹配
---------------------------------------------------------------------------
function x570058_CheckItemFull( itemid1, itemid2, itemid3, itemid4)
    -- 首先保证4件物品没有两件是重复的
    if itemid1 == itemid2 or itemid1 == itemid3 or itemid1 == itemid4 then
        return -1
    end

    if itemid2 == itemid3 or itemid2 == itemid4 then
        return -1
    end

    if itemid3 == itemid4 then
        return -1
    end

	--判断是否需要的材料
    if x570058_IsNeedItem(itemid1) ~= 1 then
		return -1
	end

    if x570058_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

    if x570058_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

    if x570058_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

	return 1
end

---------------------------------------------------------------------------
--检查材料是否足够
---------------------------------------------------------------------------
function x570058_CheckItemCount(sceneId, selfId,itemId1, itemId2, itemId3, itemId4)

	local nNeedCount =0

    nNeedCount = x570058_GetItemNeedCountByItemId(sceneId, selfId, itemId1)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId1)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570058_GetItemNeedCountByItemId(sceneId, selfId, itemId2)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId2)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570058_GetItemNeedCountByItemId(sceneId, selfId, itemId3)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId3)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570058_GetItemNeedCountByItemId(sceneId, selfId, itemId4)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId4)  <  nNeedCount then
			return -1
		end
	end

	return 1

end
---------------------------------------------------------------------------
--通过背包下标获取需要某种材料数量
---------------------------------------------------------------------------
function x570058_GetItemNeedCountByItemPos(sceneId, selfId, itemPos)

	if itemPos == -1 then
		return 0
	end

	local itemid = GetItemTableIndexByIndex( sceneId, selfId, itemPos);

	if itemid < 0 then
		return 0	
	end

	return x570058_GetItemNeedCountByItemId(sceneId, selfId,itemid);

end
---------------------------------------------------------------------------
--能过物品Id获取需要某种材料数量
---------------------------------------------------------------------------
function x570058_GetItemNeedCountByItemId(sceneId, selfId, itemid)

	if itemid < 0 then
		return 0	
	end

	if x570058_MixConfTable.itemid1 == itemid then
		return x570058_MixConfTable.itemid1count
	end

	if x570058_MixConfTable.itemid2 == itemid then
		return x570058_MixConfTable.itemid2count
	end
	
	if x570058_MixConfTable.itemid3 == itemid then
		return x570058_MixConfTable.itemid3count
	end

	if x570058_MixConfTable.itemid4 == itemid then
		return x570058_MixConfTable.itemid4count
	end

	return 0

end
---------------------------------------------------------------------------
--输入的材料类型数量
---------------------------------------------------------------------------
function x570058_GetMixItemIdInputCount( itemid1, itemid2, itemid3, itemid4)
	local nInPutCount = 0
	
	if itemid1 ~= -1 then
		nInPutCount = nInPutCount + 1 
	end

	if itemid2 ~= -1 then
		nInPutCount = nInPutCount + 1 
	end

	if itemid3 ~= -1 then
		nInPutCount = nInPutCount + 1 
	end

	if itemid4 ~= -1 then
		nInPutCount = nInPutCount + 1 
	end
	
	return nInPutCount
end
---------------------------------------------------------------------------
--物品需要的材料类型数量
---------------------------------------------------------------------------
function x570058_GetMixItemIdNeedCount()
	local nCount =0;
	if x570058_MixConfTable.itemid1 ~= -1 then
		nCount = nCount + 1;
	end

	if x570058_MixConfTable.itemid2 ~= -1 then
		nCount = nCount + 1;
	end

	if x570058_MixConfTable.itemid3 ~= -1 then
		nCount = nCount + 1;
	end

	if x570058_MixConfTable.itemid4 ~= -1 then
		nCount = nCount + 1;
	end

	return nCount;
end
---------------------------------------------------------------------------
--是否是需要的材料
---------------------------------------------------------------------------
function x570058_IsNeedItem(itemid)
	if x570058_MixConfTable.itemid1 == itemid then
		return 1;
	end

	if x570058_MixConfTable.itemid2 == itemid then
		return 1;
	end

	if x570058_MixConfTable.itemid3 == itemid then
		return 1;
	end

	if x570058_MixConfTable.itemid4 == itemid then
		return 1;
	end
	
	return 0;
end
---------------------------------------------------------------------------
--合成是否随机成功
---------------------------------------------------------------------------
function  x570058_IsMixtureRandOK()

	local rate = random(1,100)

	if rate <= x570058_MixConfTable.SuccRate then
		return 	1	
	else
		return 0
	end
end


---------------------------------------------------------------------------
--是否需要添加物品
---------------------------------------------------------------------------
function  x570058_isNeedAddedItem()

	if x570058_MixConfTable.isNeedAdded > 0 then
		return 1
	else
		return 0
	end
end

---------------------------------------------------------------------------
--得到并检查添加物品id
---------------------------------------------------------------------------
function  x570058_GetAndCheckAddedItemId(sceneId, selfId, nItemPos)

	if nItemPos == nil or nItemPos < 0 then	 --玩家没有放入添加物品
		return -1;
	end

	--不能使用添加物品
	if x570058_MixConfTable.isNeedAdded < 0 then
		return -1;
	end

	local nAddedItemId = GetItemTableIndexByIndex( sceneId, selfId, nItemPos);

	if nAddedItemId <= 0 then
		return -2;	 --玩家放入添加物品不正确
	end

	local bRightItem = CheckSpecialItem(nAddedItemId,x570058_g_Mixture_AddItem_UseType);

	if bRightItem > 0 then
		return nAddedItemId;
	else
		return -2; --玩家放入添加物品不正确
	end

end

---------------------------------------------------------------------------
--是否总是保留物品，即使在失败的情况下
---------------------------------------------------------------------------
function  x570058_isAlwaysKeep(nItemId)

	if nItemId == nil or nItemId <=0 then
		return 0;
	end

	 for i,item in x570058_MixConfTable_Ext do
		if x570058_MixConfTable_Ext[i].itemId  == nItemId then
			return x570058_MixConfTable_Ext[i].alwaysKeep;
		end
	 end

	 return 0;
end
