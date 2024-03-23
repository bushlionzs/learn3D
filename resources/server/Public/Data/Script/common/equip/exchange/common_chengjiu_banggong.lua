--�ɾͶһ�����

--MisDescBegin
x570041_g_ScriptId = 570041
x570041_g_ExtTarget={}
x570041_g_MissionName1 = "�ﹱ�һ�����"
--MisDescEnd

-- �ȼ�ϵ�����ñ�80��֮��ÿ5����75�������30%��
x570041_g_LevelTable    = {
                            { minLevel = 1,  maxLevel = 75,  coff = 48000},
                            { minLevel = 75, maxLevel = 80,  coff = 70000},
                            { minLevel = 80, maxLevel = 85,  coff = 91000 },
							{ minLevel = 85, maxLevel = 90,  coff = 112000},
                            { minLevel = 90, maxLevel = 95,  coff = 133000},
                            { minLevel = 95, maxLevel = 161, coff = 154000},
}

--**********************************

--������ں���

--**********************************

function x570041_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)	--����������ִ�д˽ű�
    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570041_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�ﹱ�һ�����" )
		AddQuestText( sceneId, format( "\n\t����ȡ�õĳɾ���Ŀ���ã�#G�ﹱ#W������԰���������׵����֤������������������#R2000��#G�ﹱ#W�һ�#R%d��#G����#W����ÿ��ֻ���Զһ�һ�Ρ�\n \n\t��������#R%d��#G�ﹱ#W��", xp, GetGuildUserPoint( sceneId, selfId) ) )
        AddQuestText( sceneId, "\n\t��ȷ��Ҫ��#G�ﹱ#W�һ�#G����#Wô��" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x570041_g_ScriptId, -1)
end



--**********************************

--�о��¼�

--**********************************

function x570041_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x570041_g_ScriptId, x570041_g_MissionName1, 3, 1)
end

function x570041_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x570041_ProcAccept( sceneId, selfId)
    local score = GetGuildUserPoint( sceneId, selfId)
    if score < 2000 then
        Msg2Player( sceneId, selfId, "��İﹱ����2000�㣬�޷��һ�����", 8, 3)
        return
    end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_CHENGJIOU_BANGGONG[ 1], MD_CHENGJIOU_BANGGONG[ 2], MD_CHENGJIOU_BANGGONG[ 3] ) then
        Msg2Player( sceneId, selfId, "������Ѿ��һ���һ���ˣ�����������", 8, 3)
        return
    else
        SetQuestData( sceneId, selfId, MD_CHENGJIOU_BANGGONG[ 1], MD_CHENGJIOU_BANGGONG[ 2], MD_CHENGJIOU_BANGGONG[ 3], day)
    end

    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570041_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "���#R%d#cffcc00�㾭��", xp), 8, 3)
    Msg2Player( sceneId, selfId, format( "���#R%d#cffcc00�㾭�顣", xp), 8, 2)
	SubGuildUserPoint( sceneId, selfId, 2000)
end

