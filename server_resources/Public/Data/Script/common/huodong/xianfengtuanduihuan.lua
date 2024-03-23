x302512_g_scriptId 		= 302512
x302512_g_Name          = "�������˿�ȷ��Ŷһ�#r"
-- �һ���Ʒ�б�
x302512_g_ItemTable     = {
                            { id = 11000300, sid = 11010020, count = 180, name = "���ӡ" }, 
                            { id = 12030031, sid = 11010020, count = 20,  name = "���з�" }, 
                            { id = 11000501, sid = 11010020, count = 8,  name = "��̴ľ̿" }, 
                            { id = 12030258, sid = 11010020, count = 6,  name = "ȫ���±�" }, 
                            { id = 12030016, sid = 11010020, count = 8,  name = "�����ټ���" }, 
                            { id = 12030241, sid = 11010020, count = 180,  name = "��һɫ(30��)���" }, 
                            { id = 12030240, sid = 11010020, count = 80,  name = "����ʱװ(14��)���" }, 

}

function x302512_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x302512_g_scriptId, "�������˿�ȷ��Ŷһ�", 3, 99)
end

function x302512_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)
    if nExtIdx == 99 then
		BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
			AddQuestNumText( sceneId, x302512_g_scriptId, "�ȷ���¶һ�", 3, 100)
			AddQuestNumText( sceneId, x302512_g_scriptId, "�ƽ��ȷ���¶һ�", 3, 101)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 100 then
		BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x302512_g_Name)
        for i, iter in x302512_g_ItemTable do
            AddQuestNumText( sceneId, x302512_g_scriptId, format( "�һ�%s", iter.name), 3, i)
        end
        AddQuestNumText( sceneId, x302512_g_scriptId, "�һ�����", 3, getn( x302512_g_ItemTable) + 1)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 101 then
		BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
            local count = GetItemCountInBag( sceneId, selfId, 11010021)
            AddQuestText( sceneId, format( "\t��һ����%d���ƽ��ȷ���£��ɶһ�#{_MONEY%d}�𿨣���ȷ��Ҫ�һ�ô��", count, count * 250) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x302512_g_scriptId, -1)
		SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, nExtIdx)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
        if nExtIdx <= getn( x302512_g_ItemTable) then
            AddQuestText( sceneId, format( "\t�һ�#G%s#W��Ҫ#G%s#W���ȷ���£���ȷ��Ҫ�һ�ô��", x302512_g_ItemTable[ nExtIdx].name, x302512_g_ItemTable[ nExtIdx].count) )
        elseif nExtIdx == getn( x302512_g_ItemTable) + 1 then
            local count = GetItemCountInBag( sceneId, selfId, 11010020)
            AddQuestText( sceneId, format( "\t��һ����%d���ȷ���£��ɶһ�%d���飬��ȷ��Ҫ�һ�ô��", count, count * 180000) )
        end
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x302512_g_scriptId, -1)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, nExtIdx)
    end
end

function x302512_ProcAcceptCheck( sceneId, selfId, NPCId)

    local index = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER)
    
	if index == 101 then
		local count = GetItemCountInBag( sceneId, selfId, 11010021)
		if count > 0 then
			AddMoney( sceneId, selfId, 3, count * 250 )
			-- ɾ��Դ��Ʒ
			DelItem( sceneId, selfId, 11010021, count)
		end
		return
	end
	
    if index <= getn( x302512_g_ItemTable) then
		-- ��鱳������û���㹻�Ķһ���Ʒ
		local count = GetItemCountInBag( sceneId, selfId, x302512_g_ItemTable[ index].sid)
		if count < x302512_g_ItemTable[ index].count then
			Msg2Player( sceneId, selfId,  "#Y���#G�ȷ����#Y�������㣬�޷��һ�", 8, 3)
			Msg2Player( sceneId, selfId,  "#Y���#G�ȷ����#Y�������㣬�޷��һ�", 8, 2)
			return 0
		end

		BeginAddItem( sceneId)
		AddBindItem( sceneId, x302512_g_ItemTable[ index].id, 1)
		local b = EndAddItem( sceneId, selfId)
		if b == 0 then
			Msg2Player( sceneId, selfId, "�����ռ䲻�㣬�޷��һ�", 8, 3)
			return 0
		end
		-- ���Ҫ����Ʒ
		AddItemListToPlayer( sceneId, selfId)
		-- ɾ��Դ��Ʒ
		DelItem( sceneId, selfId, x302512_g_ItemTable[ index].sid, x302512_g_ItemTable[ index].count)
    elseif index == getn( x302512_g_ItemTable) + 1 then
        local count = GetItemCountInBag( sceneId, selfId, 11010020)
        if count > 0 then
			AddExp( sceneId, selfId, count * 180000)
			-- ɾ��Դ��Ʒ
			DelItem( sceneId, selfId, 11010020, count)
		end
    end
end


