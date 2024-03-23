x300751_g_ScriptId = 300751
x300751_g_ScriptName = "���ر�ͼ�ϳɡ�"
x300751_g_UICommandID = 100
x300751_g_Mixture_RESULT_LESS = -2  --��Ʒ����ȷ
x300751_g_Mixture_RESULT_FAILD = -1	--��Ʒ�ϳ�ʧ��
x300751_g_Mixture_RESULT_OK = 1	--��Ʒ�ϳɳɹ�
							 
-- �ر�ͼ��Ƭ����
x300751_FragmentTable       = 
                             {
                                12030109, 12030110, 12030111, 12030112 
                             }

-- �ر�ͼId
x300751_TargetTreasure      = 12030107

function x300751_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x300751_g_ScriptId, x300751_g_ScriptName,3)
end

function x300751_ProcEventEntry( sceneId, selfId, targetId, MissionId )--��֪�ͻ��˴򿪺ϳɽ���
    BeginUICommand(sceneId);
    UICommand_AddInt(sceneId, x300751_g_ScriptId);
    UICommand_AddInt(sceneId, targetId);
    DispatchUICommand(sceneId,selfId, x300751_g_UICommandID);
    EndUICommand(sceneId);
end

function x300751_OnMixture( sceneId, selfId, item1, item2, item3, item4 )
    --print( "************************" )
	local itemcount = 0;
	local index = 1;
	local firstitemid = 0;

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

    -- ֻҪ��һ����Ƭ�ǰ󶨵ģ����ɵı�ͼ���ǰ󶨵�
    local isBind = 0
    for i, item in itemPos do
        if IsItemBind( sceneId, selfId, item) == 1 then
            isBind = 1
            break
        end
    end

    -- �����Ƭ����
	if(itemcount < 4) then
		BeginQuestEvent(sceneId);
		AddQuestText( sceneId,"����ĵ��߲���ȷ���޷��ϳ�");
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		return x300751_g_Mixture_RESULT_LESS;
	end

	local tableindex = x300751_CheckItemFull( itemId[1], itemId[2], itemId[3], itemId[4] );
	if(tableindex <= 0) then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,"����ĵ��߲���ȷ���޷��ϳ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return x300751_g_Mixture_RESULT_LESS
	end

    -- �ϳ���Ʒ 
	BeginAddItem( sceneId);
    if isBind == 0 then
        AddItem( sceneId, x300751_TargetTreasure, 1)
    else
        AddBindItem( sceneId, x300751_TargetTreasure, 1)
    end
	local ret = EndAddItem( sceneId, selfId)
	if ( ret > 0 ) then
		for i = 1, 4 do
			if( itemPos[ i] ~= -1) then
                EraseItem( sceneId, selfId, itemPos[i], 1)
			end
		end
		AddItemListToPlayer(sceneId,selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ϳɳɹ���" );
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId)
		QuestMixtureResult( sceneId, selfId, x300751_g_Mixture_RESULT_OK, itemPos[1], itemPos[2], itemPos[3], itemPos[4] )
		return x300751_g_Mixture_RESULT_OK
	else
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "��Ʒ���������޷��ϳ���Ʒ��" )
		EndQuestEvent( sceneId)
		DispatchQuestTips( sceneId,selfId)
		return x300751_g_Mixture_RESULT_LESS
	end

end

--�����Ʒ�Ƿ���Ժϳ�
function x300751_CheckItemCanMixture( item1, item2, item3, item4, nIndex )
	local count = 1;
	-- local itemlist = {item1, item2, item3, item4};
	-- local firstitemid = itemlist[nIndex];
	
	-- if(nIndex >= 4) then
		-- return count;
	-- end
	
	-- for i = nIndex + 1, 4 do
		-- if(firstitemid == itemlist[i]) then
			-- count = count + 1;
		-- elseif(itemlist[i] > 0) then
			-- count = 0;
			-- return count;
		-- end
	-- end
	
	return count;
end

--��������ϳɵ��Ƿ��Ǳ�ͼ��Ƭ
function x300751_CheckItemFull( itemid1, itemid2, itemid3, itemid4)
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

    local bFind = 0
    for i, item in x300751_FragmentTable do
        if itemid1 == item then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return -1
    end

    bFind = 0
    for i, item in x300751_FragmentTable do
        if itemid2 == item then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return -1
    end

    bFind = 0
    for i, item in x300751_FragmentTable do
        if itemid3 == item then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return -1
    end

    bFind = 0
    for i, item in x300751_FragmentTable do
        if itemid4 == item then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return -1
    end

    return 1
end

