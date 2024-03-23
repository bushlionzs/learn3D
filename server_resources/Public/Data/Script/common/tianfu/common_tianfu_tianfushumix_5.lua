x570062_g_ScriptId = 570062
x570062_g_ScriptName = "�弶ƽ��֮��ϳ�"
x570062_g_UICommandID = 100
x570062_g_Mixture_RESULT_LESS = -2  --��Ʒ����ȷ
x570062_g_Mixture_RESULT_FAILD = -1	--��Ʒ�ϳ�ʧ�ܣ��и���ʧ��
x570062_g_Mixture_RESULT_OK = 1	--��Ʒ�ϳɳɹ�
x570062_g_Mixture_AddItem_UseType = 0	--�ض���Ʒʹ������ ��Ӧ���� eITEM_SPECIAL_USETYPE

--�ϳ����ñ�
x570062_MixConfTable       = 	{itemid1 = 11010114, itemid1count = 2, itemid2 = 11010120, itemid2count = 1, itemid3 = 11010121, itemid3count = 1, itemid4 = -1,       itemid4count = 0, isNeedAdded = 1, mixitem = 11010115 , mixitemcount = 1, SuccRate = 50,  type = 570062 }


x570062_MixConfTable_Ext      = {
									{itemId = 11010114, alwaysKeep = 1},
									{itemId = 11010120, alwaysKeep = 0},
									{itemId = 11010121, alwaysKeep = 0},
								}

function x570062_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x570062_g_ScriptId, x570062_g_ScriptName,3)
end

function x570062_ProcEventEntry( sceneId, selfId, targetId, MissionId )--��֪�ͻ��˴򿪺ϳɽ���
    BeginUICommand(sceneId);
    UICommand_AddInt(sceneId, x570062_g_ScriptId);
    UICommand_AddInt(sceneId, targetId);
    DispatchUICommand(sceneId,selfId, x570062_g_UICommandID);
    EndUICommand(sceneId);
end

function x570062_OnMixture( sceneId, selfId, item1, item2, item3, item4 ,AddedItemPos)

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

	--����Ƿ���Ժϳ�
	if x570062_CheckItemCanMixture(itemId[1], itemId[2], itemId[3], itemId[4]) <=0 then
		BeginQuestEvent(sceneId);
		AddQuestText( sceneId,"����ĵ��߲���ȷ���޷��ϳ�");
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		return x570062_g_Mixture_RESULT_LESS;		
	end

	--�������Ƿ��㹻
	if x570062_CheckItemCount(sceneId, selfId,itemId[1], itemId[2], itemId[3], itemId[4]) <=0 then
		BeginQuestEvent(sceneId);
		AddQuestText( sceneId,"����ĵ��߲��㣬�޷��ϳ�");
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		return x570062_g_Mixture_RESULT_LESS;				
	end

    --ֻҪ��һ�������ǰ󶨵ģ����ɵ���Ʒ���ǰ󶨵�
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
	if x570062_isNeedAddedItem() > 0 then
		nAddItemId = x570062_GetAndCheckAddedItemId(sceneId, selfId,AddedItemPos)
		if nAddItemId == -2 then
			BeginQuestEvent(sceneId);
			AddQuestText( sceneId,"��������Ĳ��ϲ���ȷ���޷��ϳ�");
			EndQuestEvent( sceneId);
			DispatchQuestTips( sceneId, selfId);
			return x570062_g_Mixture_RESULT_LESS;				
		end
	end

    -- �ϳ���Ʒ
	if x570062_IsMixtureRandOK() == 1 then

		BeginAddItem( sceneId);
		if isBind == 0 then
			AddItem( sceneId, x570062_MixConfTable.mixitem, x570062_MixConfTable.mixitemcount)
		else
			AddBindItem( sceneId, x570062_MixConfTable.mixitem, x570062_MixConfTable.mixitemcount)
		end

		local ret = EndAddItem( sceneId, selfId)
		if ( ret > 0 ) then

			--����������Ʒ
			if x570062_isNeedAddedItem() > 0 and nAddItemId > 0 then
				EraseItem( sceneId, selfId, AddedItemPos, 1)			
			end

			for i = 1, 4 do
				if( itemPos[ i] ~= -1) then
					local nDelCount = x570062_GetItemNeedCountByItemPos(sceneId, selfId, itemPos[ i])
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
			AddQuestText(sceneId, "�ϳɳɹ���" );
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId)
			QuestMixtureResult( sceneId, selfId, x570062_g_Mixture_RESULT_OK, itemPos[1], itemPos[2], itemPos[3], itemPos[4] )
			return x570062_g_Mixture_RESULT_OK
		else
			BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "��Ʒ���������޷��ϳ���Ʒ��" )
			EndQuestEvent( sceneId)
			DispatchQuestTips( sceneId,selfId)
			return x570062_g_Mixture_RESULT_LESS
		end
	else

		--����������Ʒ
		if x570062_isNeedAddedItem() > 0 and nAddItemId > 0 then
			EraseItem( sceneId, selfId, AddedItemPos, 1)			
		end

		--�ϳ�ʧ��Ҳ��۳�����
			for i = 1, 4 do
				if( itemPos[ i] ~= -1) then
				--ʧ�������ɾ����Ʒ��������:������������Ʒ�����Ͽ��Ա���
				if x570062_isNeedAddedItem() <= 0  or  nAddItemId <= 0 or x570062_isAlwaysKeep(itemId[i]) <= 0 then
					local nDelCount = x570062_GetItemNeedCountByItemPos(sceneId, selfId, itemPos[ i])
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
		AddQuestText(sceneId, "�ϳ�ʧ�ܣ�" );
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId)
		QuestMixtureResult( sceneId, selfId, x570062_g_Mixture_RESULT_OK, itemPos[1], itemPos[2], itemPos[3], itemPos[4] )
		return x570062_g_Mixture_RESULT_OK
	end
end

---------------------------------------------------------------------------
--�������Ƿ���Ժϳ�
---------------------------------------------------------------------------
function x570062_CheckItemCanMixture( itemid1, itemid2, itemid3, itemid4 )
	
	--��������������
	if x570062_GetMixItemIdInputCount(itemid1, itemid2, itemid3, itemid4) < x570062_GetMixItemIdNeedCount() then
		return -1
	end

	--�������Ƿ�ƥ��
	if x570062_CheckItemFull(itemid1, itemid2, itemid3, itemid4) <=0 then
		return -1
	end

	return 1
end

---------------------------------------------------------------------------
--�������Ƿ�ƥ��
---------------------------------------------------------------------------
function x570062_CheckItemFull( itemid1, itemid2, itemid3, itemid4)
    -- ���ȱ�֤4����Ʒû���������ظ���
    if itemid1 == itemid2 or itemid1 == itemid3 or itemid1 == itemid4 then
        return -1
    end

    if itemid2 == itemid3 or itemid2 == itemid4 then
        return -1
    end

    if itemid3 == itemid4 then
        return -1
    end

	--�ж��Ƿ���Ҫ�Ĳ���
    if x570062_IsNeedItem(itemid1) ~= 1 then
		return -1
	end

    if x570062_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

    if x570062_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

    if x570062_IsNeedItem(itemid2) ~= 1 then
		return -1
	end

	return 1
end

---------------------------------------------------------------------------
--�������Ƿ��㹻
---------------------------------------------------------------------------
function x570062_CheckItemCount(sceneId, selfId,itemId1, itemId2, itemId3, itemId4)

	local nNeedCount =0

    nNeedCount = x570062_GetItemNeedCountByItemId(sceneId, selfId, itemId1)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId1)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570062_GetItemNeedCountByItemId(sceneId, selfId, itemId2)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId2)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570062_GetItemNeedCountByItemId(sceneId, selfId, itemId3)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId3)  <  nNeedCount then
			return -1
		end
	end

    nNeedCount = x570062_GetItemNeedCountByItemId(sceneId, selfId, itemId4)
	if  nNeedCount > 0 then
		if GetItemCountInBag(sceneId, selfId,itemId4)  <  nNeedCount then
			return -1
		end
	end

	return 1

end
---------------------------------------------------------------------------
--ͨ�������±��ȡ��Ҫĳ�ֲ�������
---------------------------------------------------------------------------
function x570062_GetItemNeedCountByItemPos(sceneId, selfId, itemPos)

	if itemPos == -1 then
		return 0
	end

	local itemid = GetItemTableIndexByIndex( sceneId, selfId, itemPos);

	if itemid < 0 then
		return 0	
	end

	return x570062_GetItemNeedCountByItemId(sceneId, selfId,itemid);

end
---------------------------------------------------------------------------
--�ܹ���ƷId��ȡ��Ҫĳ�ֲ�������
---------------------------------------------------------------------------
function x570062_GetItemNeedCountByItemId(sceneId, selfId, itemid)

	if itemid < 0 then
		return 0	
	end

	if x570062_MixConfTable.itemid1 == itemid then
		return x570062_MixConfTable.itemid1count
	end

	if x570062_MixConfTable.itemid2 == itemid then
		return x570062_MixConfTable.itemid2count
	end
	
	if x570062_MixConfTable.itemid3 == itemid then
		return x570062_MixConfTable.itemid3count
	end

	if x570062_MixConfTable.itemid4 == itemid then
		return x570062_MixConfTable.itemid4count
	end

	return 0

end
---------------------------------------------------------------------------
--����Ĳ�����������
---------------------------------------------------------------------------
function x570062_GetMixItemIdInputCount( itemid1, itemid2, itemid3, itemid4)
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
--��Ʒ��Ҫ�Ĳ�����������
---------------------------------------------------------------------------
function x570062_GetMixItemIdNeedCount()
	local nCount =0;
	if x570062_MixConfTable.itemid1 ~= -1 then
		nCount = nCount + 1;
	end

	if x570062_MixConfTable.itemid2 ~= -1 then
		nCount = nCount + 1;
	end

	if x570062_MixConfTable.itemid3 ~= -1 then
		nCount = nCount + 1;
	end

	if x570062_MixConfTable.itemid4 ~= -1 then
		nCount = nCount + 1;
	end

	return nCount;
end
---------------------------------------------------------------------------
--�Ƿ�����Ҫ�Ĳ���
---------------------------------------------------------------------------
function x570062_IsNeedItem(itemid)
	if x570062_MixConfTable.itemid1 == itemid then
		return 1;
	end

	if x570062_MixConfTable.itemid2 == itemid then
		return 1;
	end

	if x570062_MixConfTable.itemid3 == itemid then
		return 1;
	end

	if x570062_MixConfTable.itemid4 == itemid then
		return 1;
	end
	
	return 0;
end
---------------------------------------------------------------------------
--�ϳ��Ƿ�����ɹ�
---------------------------------------------------------------------------
function  x570062_IsMixtureRandOK()

	local rate = random(1,100)

	if rate <= x570062_MixConfTable.SuccRate then
		return 	1	
	else
		return 0
	end
end


---------------------------------------------------------------------------
--�Ƿ���Ҫ�����Ʒ
---------------------------------------------------------------------------
function  x570062_isNeedAddedItem()

	if x570062_MixConfTable.isNeedAdded > 0 then
		return 1
	else
		return 0
	end
end

---------------------------------------------------------------------------
--�õ�����������Ʒid
---------------------------------------------------------------------------
function  x570062_GetAndCheckAddedItemId(sceneId, selfId, nItemPos)

	if nItemPos == nil or nItemPos < 0 then	 --���û�з��������Ʒ
		return -1;
	end

	--����ʹ�������Ʒ
	if x570062_MixConfTable.isNeedAdded < 0 then
		return -1;
	end

	local nAddedItemId = GetItemTableIndexByIndex( sceneId, selfId, nItemPos);

	if nAddedItemId <= 0 then
		return -2;	 --��ҷ��������Ʒ����ȷ
	end

	local bRightItem = CheckSpecialItem(nAddedItemId,x570062_g_Mixture_AddItem_UseType);

	if bRightItem > 0 then
		return nAddedItemId;
	else
		return -2; --��ҷ��������Ʒ����ȷ
	end

end

---------------------------------------------------------------------------
--�Ƿ����Ǳ�����Ʒ����ʹ��ʧ�ܵ������
---------------------------------------------------------------------------
function  x570062_isAlwaysKeep(nItemId)

	if nItemId == nil or nItemId <=0 then
		return 0;
	end

	 for i,item in x570062_MixConfTable_Ext do
		if x570062_MixConfTable_Ext[i].itemId  == nItemId then
			return x570062_MixConfTable_Ext[i].alwaysKeep;
		end
	 end

	 return 0;
end
