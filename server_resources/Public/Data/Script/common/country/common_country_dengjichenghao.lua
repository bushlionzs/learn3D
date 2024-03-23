-- �ȼ��ƺ�

--�ű���
x300661_g_ScriptId = 300661

-- ����ID����ȼ����а�ID��Ӧ��
x300661_g_CountryToplistTable   = {
                                    67, 69, 71, 73
}
-- ����ID����ƺ�ID��Ӧ��
x300661_g_CountryTitleTable     = {
                                    107, 108, 109, 110
}

function x300661_ProcEnumEvent( sceneId, selfId, NPCId)
    AddQuestNumText( sceneId, x300661_g_ScriptId, "�����ҡ����ҷ���", 3, 1)
end

function x300661_ProcEventEntry( sceneId, selfId, NPCId)

	local countryId = GetCurCountry(sceneId,selfId)
	local countryName = GetCountryName(countryId)
	
    local rank = GetToplistRank( sceneId, selfId, x300661_g_CountryToplistTable[ GetCurCountry( sceneId, selfId) + 1] )
	if rank == -1 then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "#Y�����ҡ����ҷ���#W#r #r\t��ʿ���������ǹ��Ұ�ȫ�ı��ϡ�#r\t������ĵȼ�#G�ﵽ60��#W���������ҹ��ȼ����а���#Gǰ25λ#W����ʿ����#G��һ#W��ʱ�򶼿�������������ȡ���ͣ�#r #r#G���ͳƺţ�#r#Y�ȷ���ʿ#W#r #r#G�ƺ����ԣ�#r#Y����+3#r����+3#r����+3#r����+3#r #r#R������û�н��뱾���ȼ����а����ٽ�������") )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x300661_g_ScriptId, -1)
	else
		BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "#Y�����ҡ����ҷ���#W#r #r\t��ʿ���������ǹ��Ұ�ȫ�ı��ϡ�#r\t������ĵȼ�#G�ﵽ60��#W���������ҹ��ȼ����а���#Gǰ25λ#W����ʿ����#G��һ#W��ʱ�򶼿�������������ȡ���ͣ�#r #r#G���ͳƺţ�#r#Y�ȷ���ʿ#W#r #r#G�ƺ����ԣ�#r#Y����+3#r����+3#r����+3#r����+3#r #r#R�������ڱ����ĵȼ������ǵ�#B%d#R����#r #r�Ƿ���ܹ��ҵķ��ͣ�",rank + 1) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x300661_g_ScriptId, -1)
	end
end

function x300661_ProcAcceptCheck( sceneId, selfId, NPCId)

    local day, week = GetWeek()
    if week == GetQuestData( sceneId, selfId, MD_LEVEL_TITLE[ 1], MD_LEVEL_TITLE[ 2], MD_LEVEL_TITLE[ 3] ) then
        Msg2Player( sceneId, selfId, "�������Ѿ����ܹ����ҵķ�����", 8, 3)
		Msg2Player( sceneId, selfId, "�������Ѿ����ܹ����ҵķ�����", 8, 2)
        return 0
    end

    local rank = GetToplistRank( sceneId, selfId, x300661_g_CountryToplistTable[ GetCurCountry( sceneId, selfId) + 1] )
    if rank == -1 then
	Msg2Player( sceneId,selfId,"�����ܵĵȼ�����δ�ܽ��뱾��ǰ25��",8,3)
	Msg2Player( sceneId,selfId,"�����ܵĵȼ�����δ�ܽ��뱾��ǰ25��",8,2)
		return 0
	end
	
	local level = GetLevel(sceneId,selfId)
	if level < 60 then
	Msg2Player( sceneId,selfId,"�ȼ��ﵽ60���ſ��Խ��ܹ��ҷ���",8,3)
	Msg2Player( sceneId,selfId,"�ȼ��ﵽ60���ſ��Խ��ܹ��ҷ���",8,2)
		return 0
	end
	
	local week1 = GetWeek()
	if week1 ~= 1 then
	Msg2Player(sceneId,selfId,"ֻ����һ�ſ��Խ��ܹ��ҷ���",8,3)
	Msg2Player(sceneId,selfId,"ֻ����һ�ſ��Խ��ܹ��ҷ���",8,2)
		return 0
	end
	
	local msg = "��ϲ��������ȷ���ʿ�������ƺ�"
        --Msg2Player( sceneId, selfId, msg, 8, 3)
	    Msg2Player( sceneId, selfId, msg, 8, 2)
    -- ������ȡ�ƺ�����
    SetQuestData( sceneId, selfId, MD_LEVEL_TITLE[ 1], MD_LEVEL_TITLE[ 2], MD_LEVEL_TITLE[ 3], week)
    AwardTitle( sceneId, selfId, x300661_g_CountryTitleTable[ GetCurCountry( sceneId, selfId) + 1] )

	return	1
end

function x300661_ProcAccept( sceneId, selfId )
end
