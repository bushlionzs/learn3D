-- ������籭
x300615_g_ScriptId 					= 300615
-- ����᡿���籭����
x300615_g_Name                      = "����᡿���籭"
-- ս��·��
x300615_g_SceneName                 = "zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn"
x300615_g_SceneScript               = { { Name = "zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn", ScriptID = 300615} }

-- ������籭״̬���ο�GLServer\World\WorldData\GuildContendManager.h�е�GuildContendState
-- ����ǰ������׼��״̬
x300615_State_Prepare               = 1
-- ������ʼ
x300615_State_Start                 = 2
-- ��������
x300615_State_End                   = 3
-- ���°�����籭����
x300615_State_Finished              = 4
-- ������籭ս��ʱ�䣨�룩
x300615_g_FightTime                 = 1800

x300615_g_strNotJoinGuild           = "\t����δ�����κΰ�ᣡ"
x300615_g_strOnlyforLeader          = "\tֻ�а�������ʹ�ô˹��ܡ�"
x300615_g_strSignupTimePassed       = "\t���ڲ��Ǳ���ʱ�䣡"

-- GLServer�������������붨�壬������WGGuildContend.h��WGReplyCodeö��ֵ����һ��
GCR_SIGNUP_SUCCESS                  = 0     -- �����ɹ���
GCR_SIGNUP_HASSIGNEDUP              = 1     -- �Ѿ��������ˡ�
GCR_SIGNUP_STRENGTHNOTENOUGH        = 2     -- �����ۺ�ʵ�������μӰ�����籭��
GCR_SIGNUP_NOTEXIST                 = 3     -- ��������Ѳ����ڣ������ǽ�ɢ�ˡ�
GCR_WASHOUT                         = 4     -- �����ڰ���ѱ���̭
GCR_NOTPATICIPATE                   = 5     -- �����ڰ��û����ѡ���µİ�����籭
GCR_INHIGHGROUP                     = 6     -- ����Ѿ���A���B�����ˡ�
GCR_NOMATCHTOJOIN                   = 7     -- ����û�пɲμӵı�����
-- ս����Ӫ��ʼ����
x300615_g_RedInitPosX               = 23
x300615_g_RedInitPosZ               = 123
x300615_g_BlueInitPosX              = 229
x300615_g_BlueInitPosZ              = 123
-- ���ذ�սNPC����
x300615_g_PosX                      = 127
x300615_g_PosZ                      = 117
-- ��ʤ����
x300615_g_TotalScore                = 2000
-- �ɼ���ƷId
x300615_g_ItemId                    = 13080024
x300615_g_MutexTable                = {
                                        PLAYER_STATE_STALL                , --��̯
                                        PLAYER_STATE_FUBEN                , --����
                                        PLAYER_STATE_GUILDBATTLEFIELDSCENE, --ս��
                                        PLAYER_STATE_ARENASSCENE          , --��̨
                                        PLAYER_STATE_CITSCENE             , --����
                                        PLAYER_STATE_PRISONSCENE          , --����
                                        PLAYER_STATE_DIE                  , --����
                                        PLAYER_STATE_BUS                  , --BUS
                                        PLAYER_STATE_CRASHBOX             , --����
                                        PLAYER_STATE_EXCHANGE             , --����
                                        PLAYER_STATE_MENTALGAME           , --����
                                        PLAYER_STATE_AUTOPLAY             , --�һ�
                                        PLAYER_STATE_SUBTRAIN             , --����
                                        PLAYER_STATE_PRISON               , --����
                                        PLAYER_STATE_OPENBOX              , --����
                                        PLAYER_STATE_KEYBORDMOVE          , --�����ƶ�
                                        PLAYER_STATE_TIESAN               , --��������
                                        PLAYER_STATE_READYFUBEN           , --���븱��״̬
                                        PLAYER_STATE_DUOQIBUFF			  , --����������buffʱ��״̬
                                        PLAYER_STATE_TONGQUBUFF			  , --ͯȤ������buffʱ��״̬
                                        PLAYER_STATE_FORBID_RIDE		  , --��ֹ����״̬
                                        PLAYER_STATE_WEDDING			  , --����״̬
                                        PLAYER_STATE_ENJAIL				  , --����״̬
                                        PLAYER_STATE_Award				  , --�콱״̬
                                        PLAYER_STATE_TransGold			  , --��ȡ�ֽ�״̬
                                        PLAYER_STATE_DANCERY              , --�������һ�
}
-- �漣�ɼ�������Id
x300615_GT_Miracle                  = 727
-- ����ɼ�������Id
x300615_GT_ArmyFlag                 = 726
-- ս��ɼ�������Id
x300615_GT_Flag_A                   = 728
-- ս��ɼ�������Id
x300615_GT_Flag_B                   = 729
-- ռ��ս�������
x300615_g_Occupy                    = {}
-- ռ��ս�������
x300615_g_Occupy_B                  = {}
-- ����ռ��ÿ�������÷���
x300615_g_FlagScore                 = 2
-- �漣Buff����100������
x300615_g_MiracleId                 = 7800
-- ÿ�������Խ������籭ս�����������
x300615_g_MaxCountInBattleScene     = 50
-- ���ؼ���
x300615_g_HideTowerTable            = {
                                        { typeid = 9732, x = 60,  z = 121, guid = 129721, base_ai = 22, aiscript = -1, campid = 5, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 60,  z = 127, guid = 129722, base_ai = 22, aiscript = -1, campid = 5, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 195, z = 127, guid = 129726, base_ai = 22, aiscript = -1, campid = 6, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 195, z = 120, guid = 129727, base_ai = 22, aiscript = -1, campid = 6, faceDir = 270, title = "", name = "", score = 200 }, 
}
-- ��ʾ�����������ؼ������ݻ�ʱ�Ѷ�Ӧ��ʾ�ļ���Ҳɾ����
x300615_g_ShowTowerTable            = {
                                        { typeid = 9737, x = 60,  z = 121, guid = 129741, base_ai = 3, aiscript = -1, campid = 5, faceDir = 270, title = "��������", name = "����", score = 200 }, 
                                        { typeid = 9737, x = 60,  z = 127, guid = 129742, base_ai = 3, aiscript = -1, campid = 5, faceDir = 270, title = "��������", name = "����", score = 200 }, 
                                        { typeid = 9737, x = 195, z = 127, guid = 129746, base_ai = 3, aiscript = -1, campid = 6, faceDir = 270, title = "��Ԫ����", name = "����", score = 200 }, 
                                        { typeid = 9737, x = 195, z = 120, guid = 129747, base_ai = 3, aiscript = -1, campid = 6, faceDir = 270, title = "��Ԫ����", name = "����", score = 200 }, 
}
-- RD_GUILDCONTEND_KILL_LEADER         = 28        --������籭ɱ�˼���
-- RD_GUILDCONTEND_KILL_ASSIST         = 29        --������籭�ɼ�����
-- RD_GUILDCONTEND_KILL_FAMILY         = 30        --������籭ռ���漣����
-- RD_GUILDCONTEND_KILL_GOLD           = 31        --������籭ռ��������
-- RD_GUILDCONTEND_KILL_OTHER          = 32        --������籭�ݻټ�������
-- RD_GUILDCONTEND_DIECOUNT            = 33        --������籭��ɱ����
-- RD_GUILDCONTEND_SCORE               = 34        --������籭���˻���
x300615_g_NPCTable                  = {
                                        129730,
                                        129731,
                                        129732,
                                        129733,
                                        129734,
                                        129735,
                                        129736,
                                        129737,
                                        129738,
                                        129739,
}
-- �������ñ�
x300615_g_RewardTable               = {
                                        { groupType = 2, turnNumber = 0, 
                                            rewards = { 
                                            { xpCoff = 65000, merit = 18, bangGong = 360, gxp = 180, gmoney = 7200000, gshiming = 65, }, 
                                            { xpCoff = 32500, merit = 10, bangGong = 180, gxp = 90,  gmoney = 3600000, gshiming = 35, }, 
                                                      }
                                        }, 
                                        { groupType = 2, turnNumber = 1, 
                                            rewards = { 
                                            { xpCoff = 80000, merit = 22, bangGong = 440, gxp = 220, gmoney = 8800000, gshiming = 80, }, 
                                            { xpCoff = 40000, merit = 15, bangGong = 220, gxp = 110, gmoney = 4400000, gshiming = 40, }, 
                                                      }
                                        }, 
                                        { groupType = 2, turnNumber = 2, 
                                            rewards = { 
                                            { xpCoff = 63000, merit = 20, bangGong = 350, gxp = 175, gmoney = 7000000, gshiming = 65, }, 
                                            { xpCoff = 45000, merit = 15, bangGong = 250, gxp = 125, gmoney = 5000000, gshiming = 45, }, 
                                                      }
                                        }, 
                                        { groupType = 2, turnNumber = 3, 
                                            rewards = { 
                                            { xpCoff = 126000, merit = 35, bangGong = 700, gxp = 350, gmoney = 14000000, gshiming = 125, }, 
                                            { xpCoff = 90000,  merit = 25, bangGong = 500, gxp = 250, gmoney = 10000000, gshiming = 90, }, 
                                                      }
                                        }, 
                                        { groupType = 1, turnNumber = 0, 
                                            rewards = { 
                                            { xpCoff = 43335, merit = 15, bangGong = 240, gxp = 120, gmoney = 4800000, gshiming = 45, }, 
                                            { xpCoff = 21670, merit = 10, bangGong = 120, gxp = 60,  gmoney = 2400000, gshiming = 25, }, 
                                                      }
                                        }, 
                                        { groupType = 1, turnNumber = 1, 
                                            rewards = { 
                                            { xpCoff = 53335, merit = 15, bangGong = 295, gxp = 150, gmoney = 5870000, gshiming = 55, }, 
                                            { xpCoff = 26670, merit = 10, bangGong = 150, gxp = 75,  gmoney = 2940000, gshiming = 30, }, 
                                                      }
                                        }, 
                                        { groupType = 1, turnNumber = 2, 
                                            rewards = { 
                                            { xpCoff = 42000, merit = 15, bangGong = 235, gxp = 120, gmoney = 4670000, gshiming = 45, }, 
                                            { xpCoff = 30000, merit = 10, bangGong = 170, gxp = 85,  gmoney = 3340000, gshiming = 30, }, 
                                                      }
                                        }, 
                                        { groupType = 1, turnNumber = 3, 
                                            rewards = { 
                                            { xpCoff = 84000, merit = 25, bangGong = 470, gxp = 235, gmoney = 9340000, gshiming = 85, }, 
                                            { xpCoff = 60000, merit = 20, bangGong = 335, gxp = 170, gmoney = 6670000, gshiming = 60, }, 
                                                      }
                                        }, 
}
-- ���籭˵��
x300615_g_DescriptionTable          = {
                                        "\t���ã����ǡ���᡿���籭�����ˣ�����᡿���籭������������ͨ���ҽ��롾��᡿���籭ս��.", 
                                        "\t����᡿���籭�����������£�", 
                                        "һ����������������ȼ����а��һ������70������Ὺ������᡿���籭����������ʱ��Ϊ���»����µĵ�һ������16��00-16��30��#r", 
                                        
                                        "�����������飺�״ο���ʱ��ȡ���ʵ����ǰ16�����жԿ���ǰ8��Ϊ���籭����A�飬��8��Ϊ���籭����B�顣���±���ʱ��A��ǰ4����B��ǰ4����ᣬ�������ΪA�飬B��������������ᱨ����ɡ�#r", 
                                        
                                        "��������ʱ�䣺������ÿ�µĵ�һ�����ջ����8��4���ڶ������ս���4��2�����������ս��е�������������ս�����ĸ����ս��е�һ����������ս��#r", 
                                        
                                        "�ģ���̭����A��8��4������ʤ��Ϊǰ����ֱ�ӽ������²μ�A�����������ΪA��1-4�������߽��������ߴ��²���ʱ��Ҫ�����μӣ�4��2������ʤ������һ��������������������������\nB��8��4������ʤ��ֱ�ӽ������²μ�A�����������ΪA��5-8�������߽��������²���ʱ��Ҫ�����μӣ�4��2������ʤ������B��һ��������������B�������������#r", 
                                         
                                        "�壬�������򣺵������籭ȫ������ʱ��ʼ���������µĵ�һ������14��00��ֹ�����������������������򰴰��ʵ���������иߵĶ������е͵ģ��������ᣬ�����յ��ʼ�֪ͨ��#r", 
                                         
                                         "\t����᡿���籭ս���������£�", 
										"1��ÿ��������������Խ���50�ˡ�",
                                        "2��ս�����û����ƣ�ռ����³��ս��ÿ10���2�֣������괦��ȡ���齻����������ͳ˧ÿ��50�֣��ݻٵз�������200�֣���ȡ�������Ҳ�����ʹ�ü��ܡ�#r", 
                                        "3����ս����ͨ���ɼ�����ˮ���õ��Ĺ�������������������ͳ˧ÿ�ε�1�֡�#r", 
                                        "4�����籭����ʱ��Ϊ30���ӣ��ȵõ�2000�ֵ�һ����ֱ�ӻ��ʤ����������һ�������籭������������Ϊ0ʱ����ֱ���и������籭���������󣬾�δ�ﵽ2000�֣���ָ���ȡʤ������һ��ʱ��A����ǰ��������ʤ��B���������������ʤ��#r", 
                                        "5��ս���ڲ��ܽ���ԭ�ظ��", 
}
-- �ر���Ч��ɫOBJ�б�
x300615_g_ToStopEffectList          = {}
-- ÿ����������˵���Ч
x300615_g_ClearPerSecond            = 20
-- ����Guid
x300615_g_RuinList                  = {}

function x300615_OnMapInit( sceneId)
    x300615_g_ToStopEffectList[ sceneId] = {}
    x300615_g_Occupy[ sceneId] = 0
    x300615_g_Occupy_B[ sceneId] = 0
    x300615_g_RuinList[ sceneId] = {}
end
-- ���NPC�¼�����
function x300615_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText( sceneId, x300615_g_ScriptId, "����᡿���籭����", 1, 1)
    local state = GetWorldCupState( sceneId)

    -- print( state)
    -- AddGuildExp( sceneId, selfId, 1999999)
    if state == STATE_GUILD_WORLDCUP_PREPARE or state == STATE_GUILD_WORLDCUP_START then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "���롾��᡿���籭", 3, 2)
    end

    --print( state)
    if state == STATE_GUILD_WORLDCUP_SIGNUP then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "����᡿���籭����", 3, 3)
    end

    if state > STATE_GUILD_WORLDCUP_SIGNUP then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "����᡿���籭��ѯ", 3, 4)
    end
end

--�������ť������������ִ�д˽ű�
function x300615_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)
    if indexId == 1 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            for i, item in x300615_g_DescriptionTable do
                AddQuestText( sceneId, item)
            end
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
    elseif indexId == 2 then
        x300615_ShowGuildContendInfo( sceneId, selfId, targetId)
    elseif indexId == 3 then
        x300615_Signup( sceneId, selfId, targetId)
    elseif indexId == 4 then
        x300615_Query( sceneId, selfId, targetId)
    end
end

-- ���籭��ѯ����
function x300615_Query( sceneId, selfId, targetId)
    -- �ӳ��������л�ȡ������Ϣ����
    local vsInfo = {}
    vsInfo[ 1] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS1)
    vsInfo[ 2] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS2)
    vsInfo[ 3] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS3)
    vsInfo[ 4] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS4)
    vsInfo[ 5] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS5)
    vsInfo[ 6] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS6)
    vsInfo[ 7] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS7)
    vsInfo[ 8] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS8)

    -- ��ȡ������Ϣ
    local versus = {}
    local iCount = 0
    for i, item in vsInfo do
        versus[ i] = {}
        if item <= 0 then
            versus[ i][ 1] = -1
            versus[ i][ 2] = -1
        else
            if item >= 100000 then
                versus[ i][ 1] = floor( item / 100000) - 1
            else
                versus[ i][ 1] = -1
            end

            local g2 = mod( item, 100000)
            if g2 == 0 then
                versus[ i][ 2] = -1
            else
                versus[ i][ 2] = g2 - 1
            end
            iCount = iCount + 1
        end
    end

    local strA = ""
    local strB = ""
    for i, item in versus do
        if i < 5 then
            if item[ 1] ~= -1 and item[ 2] ~= -1 then
                strA = strA..format( "���#R%s#W VS ���#R%s#W\n", GetGuildName( item[ 1] ), GetGuildName( item[ 2] ) )
            elseif item[ 1] ~= -1 then
                strA = strA..format( "���#R%s#W�ֿ�\n", GetGuildName( item[ 1] ) )
            elseif item[ 2] ~= -1 then
                strA = strA..format( "���#R%s#W�ֿ�\n", GetGuildName( item[ 2] ) )
            end
        else
            if item[ 1] ~= -1 and item[ 2] ~= -1 then
                strB = strB..format( "���#R%s#W VS ���#R%s#W\n", GetGuildName( item[ 1] ), GetGuildName( item[ 2] ) )
            elseif item[ 1] ~= -1 then
                strB = strB..format( "���#R%s#W�ֿ�\n", GetGuildName( item[ 1] ) )
            elseif item[ 2] ~= -1 then
                strB = strB..format( "���#R%s#W�ֿ�\n", GetGuildName( item[ 2] ) )
            end
        end
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y�������籭���������᣺" )
        AddQuestText( sceneId, " " )
        if iCount > 0 then
            AddQuestText( sceneId, "A�飺" )
            AddQuestText( sceneId, strA)
            AddQuestText( sceneId, "B�飺" )
            AddQuestText( sceneId, strB)
        else
            AddQuestText( sceneId, "����û�б�����" )
        end
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- ������籭����
function x300615_Signup( sceneId, selfId, targetId)
    -- ���ȼ������Ƿ��ڰ����
    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strNotJoinGuild)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- ��鱨�����ǲ��ǰ���
    local guildStatus = GetGuildOfficial( sceneId, selfId)
    if guildStatus ~= 5 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strOnlyforLeader)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- ����Ƿ�Ϊ״̬״̬�������ڱ���ʱ���NPC�Ի��򣬵����ʱ�Ѿ����˱���ʱ��
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_SIGNUP then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strSignupTimePassed)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- ��GLServer���ͱ�������
    GuildContendSignup( sceneId, selfId, targetId, guildId)
end

-- GLServer�����������
function x300615_OnReply( sceneId, selfId, targetId, ReplyCode)
    local strInfo = ""
    if ReplyCode == GCR_SIGNUP_SUCCESS then
        strInfo = "\t�����ɹ���"
    elseif ReplyCode == GCR_SIGNUP_HASSIGNEDUP then
        strInfo = "\t��İ���Ѿ��������ˣ�"
    elseif ReplyCode == GCR_SIGNUP_STRENGTHNOTENOUGH then
        strInfo = "\t��İ��İ��ʵ�����ϵ��������ͣ�����ʧ�ܣ�"
    elseif ReplyCode == GCR_SIGNUP_NOTEXIST then
        strInfo = "\t��İ���Ѿ���ɢ�ˣ�"
    elseif ReplyCode == GCR_WASHOUT then
        strInfo = "\t�����ڰ���ѱ���̭�ˣ�"
    elseif ReplyCode == GCR_NOTPATICIPATE then
        strInfo = "\t�����ڰ��û�б����μӱ���ġ���᡿���籭��"
    elseif ReplyCode == GCR_INHIGHGROUP then
        strInfo = "\t��İ���Ѿ��������籭����Ȧ�����ܱ����μ�Ԥѡ����"
    elseif ReplyCode == GCR_NOMATCHTOJOIN then
        strInfo = "\t�ܱ�Ǹ�������ڵİ�᲻�������ڣ�û�пɲμӵı�����"
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300615_g_Name)
        AddQuestText( sceneId, strInfo)
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- ��ʾ���������籭ȷ�ϴ���
function x300615_ShowGuildContendInfo( sceneId, selfId, targetId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300615_g_Name)
        AddQuestText( sceneId, "\t����᡿���籭�Ѿ���ʼ����ȷ��Ҫ����ս��ô��" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
end

-- �жϳ����Ƿ��ǰ�����籭����
function x300615_IsGuildContendScene( sceneId)
    -- �������ͣ��ο�scenedefines.tab����PVPս����2��������
    local sceneType = GetSceneType( sceneId)
    if sceneType ~= 2 then
        return 0
    end

    -- �������ǰ�����籭������������
    if GetBattleSceneName( sceneId) ~= x300615_g_SceneName then
        return 0
    end

    return 1
end

-- ����ͷ������
function x300615_UpdateTitle( sceneId, selfId, title)
    AwardTitle( sceneId, selfId, title)
end

-- ���ͷ���ƺ�
function x300615_ClearTitle( sceneId, selfId, title)
    if IsHaveTitle( sceneId, selfId, title) == 1 then
        DeleteTitle( sceneId, selfId, title)
    end
end

-- ����״̬�仯���ɳ������
function x300615_OnChangeState( sceneId, stateId, turnNumber, guildCount)
    local sceneType = GetSceneType( sceneId)

    if sceneType == 0 then --������������ͨ����
        if stateId == STATE_GUILD_WORLDCUP_FINISHED then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_FINISHED)
            --WriteLog( 1, format( "GCL: STATE_GUILD_WORLDCUP_FINISHED, sceneId = %d, sceneType = 2", sceneId) )
            return
        elseif stateId == STATE_GUILD_WORLDCUP_PREPARE then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_PREPARE)
            --WriteLog( 1, format( "GCL: STATE_GUILD_WORLDCUP_PREPARE, sceneId = %d, sceneType = 2", sceneId) )
            return
        elseif stateId == STATE_GUILD_WORLDCUP_END then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
            return
        elseif stateId == STATE_GUILD_WORLDCUP_SIGNUP then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_SIGNUP)
            return
        elseif stateId == STATE_GUILD_WORLDCUP_SIGNUPEND then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_SIGNUPEND)
            return
        elseif stateId == STATE_GUILD_WORLDCUP_DISABLESIGNUP then
            SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_DISABLESIGNUP)
            return
        end
    elseif sceneType == 2 then --���������ǰ�����籭����
        if x300615_IsGuildContendScene( sceneId) == 0 then
            -- ������ǰ�����籭����
            return
        end

        -- ״̬�仯�Ÿ���
        if GetWorldCupState( sceneId) == stateId then
            return
        else
            SetWorldCupState( sceneId, stateId)
        end

        if stateId == STATE_GUILD_WORLDCUP_PREPARE then
            -- ���������������Ķ���˫�����ID��
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, 0)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, 0)

            x300615_InitBattleField( sceneId)

            -- ������籭������GLServerע����á�
            GuildContendAskInit( sceneId)
        elseif stateId == STATE_GUILD_WORLDCUP_START then
            -- ������ʼ
            x300615_OnBattleBegin( sceneId)
        elseif stateId == STATE_GUILD_WORLDCUP_END then
            -- ��������
            x300615_OnBattleEnd( sceneId)
        end
    end
end

-- ��ʼ��ս������������
function x300615_InitBattleField( sceneId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- �ݻټ����ͷ��棬����еĻ�
    local show = 0
    local hide = 0
    local ruin = 0
	local nMonsterCount = GetMonsterCount( sceneId)
	for i = 0, nMonsterCount - 1 do
		local objId = GetMonsterObjID( sceneId, i)
        hide = 0
        for j, item in x300615_g_HideTowerTable do
            if item.guid == GetMonsterGUID( sceneId, objId) then
                hide = 1
                break
            end
        end
        show = 0
        for j, item in x300615_g_ShowTowerTable do
            if item.guid == GetMonsterGUID( sceneId, objId) then
                show = 1
                break
            end
        end
        ruin = 0
        for j, item in x300615_g_RuinList[ sceneId] do
            if item == GetMonsterGUID( sceneId, objId) then
                ruin = 1
                break
            end
        end
        if show == 1 or hide == 1 or ruin == 1 then
            if IsObjValid( sceneId, objId) == 1 and GetHp( sceneId, objId) > 0 then
                DeleteMonster( sceneId, objId)
            end
        end
	end

    -- �������GUID
    x300615_g_RuinList[ sceneId] = {}

    -- ��������
    for i, item in x300615_g_HideTowerTable do
        CreateMonster( sceneId, item.typeid, item.x, item.z, item.base_ai, item.aiscript, x300615_g_ScriptId, item.guid, item.campid, 3600000, item.faceDir, item.name, item.title)
    end
    for i, item in x300615_g_ShowTowerTable do
        CreateMonster( sceneId, item.typeid, item.x, item.z, item.base_ai, item.aiscript, x300615_g_ScriptId, item.guid, item.campid, 3600000, item.faceDir, item.name, item.title)
    end

    -- �����赲
    AddSceneTempImpassable( sceneId, 186, 116, 194, 130)
    AddSceneTempImpassable( sceneId,  56, 118,  60, 134)
end

-- ע�᳡���ɹ���GLServer���ؽ�ս˫�����ID
function x300615_RegisterScene( sceneId, GuildIdA, GuildIdB)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, GuildIdA)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, GuildIdB)
end

-- GLServer֪ͨ������ʼ
function x300615_OnBattleBegin( sceneId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local GuildIdA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local GuildIdB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)

    if GuildIdA == -1 and GuildIdB == -1 then
        return
    end

    -- ����ֿ�ֱ�ӽ�����˳��������ֿ�
    if GuildIdA == -1 and GuildIdB ~= -1 then
        local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
        -- ���»�ʤ���μ���
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        -- �����ִ���Ϣ
        UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 1, 0, groupType)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
        return
    end
    if GuildIdB == -1 and GuildIdA ~= -1 then
        local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
        -- ���»�ʤ���μ���
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        -- �����ִ���Ϣ
        UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 1, 0, groupType)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
        return
    end

    LuaThisScenceM2Wrold( sceneId, "����᡿���籭��ʼ��", 5, 1)

    SetSceneMapDataFlag( sceneId, 1, 7, "����", 126, 124, -1)

    -- ɾ���赲
    DelSceneTempImpassable( sceneId, 186, 116, 194, 130)
    DelSceneTempImpassable( sceneId,  56, 118,  60, 134)

    -- ��ʼ��˫�������÷�
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, 0)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, 0)
    -- ���ս��ռ����
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
    -- ս��ռ�����������
    x300615_g_Occupy[ sceneId] = 0
    x300615_g_Occupy_B[ sceneId] = 0
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A, -1)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B, -1)

    -- ��������˵�ս������
    local nHumanCount = GetScenePlayerCount( sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_LEADER, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_ASSIST, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_FAMILY, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_GOLD, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_OTHER, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_SCORE, 0)
            SetPlayerRuntimeData( sceneId, objId, RD_DANCERY_BODYID, 0)
        end

        -- ��սʱ������Ϊ�ж���Ӫ
        local guildId = GetGuildID( sceneId, objId)
        local rx = random( 2, 5)
        local rz = random( 2, 5)
        if guildId == GuildIdA then
            SetCurCamp( sceneId, objId, 5)
            -- SetPos( sceneId, objId, x300615_g_RedInitPosX + rx, x300615_g_RedInitPosZ + rz)
        elseif guildId == GuildIdB then
            SetCurCamp( sceneId, objId, 6)
            -- SetPos( sceneId, objId, x300615_g_BlueInitPosX + rx, x300615_g_BlueInitPosZ + rz)
        else
            -- ����������ڸ�ս���İ��ʹ��ͳ�ȥ
            x300615_OnPlayerAskLeave( sceneId, objId)
        end
        -- ��Obj���浽ȫ���б�
        x300615_g_ToStopEffectList[ sceneId][ getn( x300615_g_ToStopEffectList[ sceneId] ) + 1] = objId
		-- CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, objId, 30)
		-- CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, objId, 31)
    end
end

-- GLServer֪ͨ��������
function x300615_OnBattleEnd( sceneId)
    -- ȡ�ö�ս˫���������ID
    local GuildIdA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local GuildIdB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local turnNumber = GetWorldCupSceneData_Param( sceneId, LD_GUILD_CONTEND_TURNNUMBER)
    local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
    local matchFlag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAG)
    local index = 1

    -- �ҵ���������������
    for i, item in x300615_g_RewardTable do
        if turnNumber == item.turnNumber and groupType == item.groupType then
            index = i
            break
        end
    end

    -- �˳���û�н��б���
    if GuildIdA == -1 and GuildIdB == -1 then
        return
    end

    -- �ֿհ�ֱ�ӽ���
    if GuildIdA == -1 then
        UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 0, 0, groupType)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        return
    end
    if GuildIdB == -1 then
        UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 0, 0, groupType)
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        return
    end

    local TitleBlue = GetGuildName( GuildIdA)
    local TitleRed  = GetGuildName( GuildIdB)
    local nHumanCount = GetScenePlayerCount( sceneId)
    local scoreA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE)
    local scoreB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE)
    SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
    SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)

    -- ͳ�Ʊ������ --
    -- ���ʣ�����ʱ��
    local nTime = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_COUNT_ITME)

    -- �õ���ʤ����0ΪA����ʤ��1ΪB����ʤ��û��ƽ��
    local Winner = 0
    if scoreA == scoreB then
        -- ���������ͬ������ս���ֳɼ��ж�ʤ��
        local gbA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GB_SCORE)
        local gbB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GB_SCORE)
        if gbA > gbB then
            Winner = 1
        elseif gbA < gbB then
            Winner = 0
        else
            -- �����ս������ͬ�����ѡһ����ʤ��
            if random( 1, 2) == 1 then
                Winner = 0
            else
                Winner = 1
            end
        end
    else
        if scoreA > scoreB then
            Winner = 0
        else
            Winner = 1
        end
    end

    -- �㲥��ս�������ݸ�����ս���е����
    GuildContendSendBaseInfo( sceneId, TitleBlue, TitleRed, Winner, nTime)
    -- �㲥ÿ����ս��ҵı�������
    local i = 0
    local nGuildFlag = 0
    local firstWin = 0
    local firstLose = 0
    local allResult = {}
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        allResult[ i + 1] = { kill = 0, collect = 0, occour = 0, flag = 0, tower = 0, score = 0, nGuildFlag = 0, nCountryId = 0, name = "" }
        RestoreHp( sceneId, objId, 0)
        if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
            local nGuildId = GetGuildID( sceneId, objId)

            -- �ָ���Ӫ
            SetCurCamp( sceneId, objId, 4)

            -- ��������ȸ������Ῠ����ͳ�ƽ������
            if IsPlayerMutexState( sceneId, objId, PLAYER_STATE_DIE) > 0 then
                RelivePlayerNM( sceneId, objId, 2)
            end

            -- ���ʤ��
            local isWin = 1
            local oppoGuildName = ""
            if Winner == 0 then -- A��ʤ
                if nGuildId == GuildIdA then
                    isWin = 1
                    nGuildFlag = 0
                    oppoGuildName = GetGuildName( GuildIdB)
                else
                    isWin = 0
                    nGuildFlag = 1
                    oppoGuildName = GetGuildName( GuildIdA)
                end
            else -- B��ʤ
                if nGuildId == GuildIdB then
                    isWin = 1
                    nGuildFlag = 1
                    oppoGuildName = GetGuildName( GuildIdA)
                else
                    isWin = 0
                    nGuildFlag = 0
                    oppoGuildName = GetGuildName( GuildIdB)
                end
            end
            -- ����ʤ�����͵��ͻ���
            if isWin == 0 then
                -- ʧ��
                local level = GetLevel( sceneId, objId)
                local name = GetName( sceneId, objId)

                local strInfo = "�������������ź������ڵİ�ᱻ��̭��"
                if groupType == 0 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭C��1/8�������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00��̭���֡�"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭C��1/4�������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00��̭���֡�"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭C���������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ�ʧȥ���������ʸ����ֽ��μ������������ı�����"
                    elseif turnNumber == 3 then
                        if matchFlag == 1 then
                            strInfo = "���졾��᡿���籭C�����������������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ���C�����������B�顣"
                        else
                            strInfo = "���졾��᡿���籭C����������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ���C���Ǿ�����ݽ���B�顣"
                        end
                    end
                elseif groupType == 1 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭B��1/4�������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ�ʧȥ����A���ʸ�"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭B���������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ�ʧȥ���������ʸ����ֽ��μ������������ı�����"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭B���������������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ����B���������"
                    elseif turnNumber == 3 then
                        strInfo = "����᡿���籭B��������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ����B���Ǿ���"
                    end
                elseif groupType == 2 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭A��1/4�������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ���A�齵����B�顣"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭A���������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ�ʧȥ���������ʸ����ֽ��μ������������ı�����"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭A���������������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ����A���������"
                    elseif turnNumber == 3 then
                        strInfo = "����᡿���籭A��������ǵİ�ᱻ#R"..oppoGuildName.."#cffcf00���ܣ����A���Ǿ���"
                    end
                end
                LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)

                --����Player�����Ϣ
                local nCountryId   = GetCurCountry( sceneId, objId)
                local nBeKilled    = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_DIECOUNT)

                allResult[ i + 1].kill = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_LEADER)
                allResult[ i + 1].collect = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_ASSIST)
                allResult[ i + 1].occour = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_FAMILY)
                allResult[ i + 1].flag = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_GOLD)
                allResult[ i + 1].tower = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_OTHER)
                allResult[ i + 1].score = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_SCORE)
                allResult[ i + 1].nGuildFlag = nGuildFlag
                allResult[ i + 1].nCountryId = nCountryId
                allResult[ i + 1].name = name
                Msg2Player( sceneId, objId, format( "���#R#{_MONEY%d}#cffcc00����Ǯ", x300615_g_RewardTable[ index].rewards[ 2].gmoney), 8, 2)
                Msg2Player( sceneId, objId, format( "���#R%d#cffcc00���ʹ��", x300615_g_RewardTable[ index].rewards[ 2].gshiming), 8, 2)
                Msg2Player( sceneId, objId, format( "���#R%d��#cffcc00��ᾭ��", x300615_g_RewardTable[ index].rewards[ 2].gxp), 8, 2)
                if firstLose == 0 then
                    -- һ���Ը�ʧ����ά��
                    firstLose = 1
                    AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gmoney)
                    AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gshiming)
                    AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gxp)
                end
            else
                -- ��ʤ
                local level = GetLevel( sceneId, objId)
                local name = GetName( sceneId, objId)

                local strInfo = "�����ڵİ��ɹ�������"
                if groupType == 0 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭C��1/8�������ǵİ����̭#R"..oppoGuildName.."#cffcf00���ɹ�����8ǿ��"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭C��1/4�������ǵİ����̭#R"..oppoGuildName.."#cffcf00���ɹ�����4ǿ�������½�������B�顣"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭C���������ǵİ�����#R"..oppoGuildName.."#cffcf00���ɹ��������������ֽ�����C��ھ���"
                    elseif turnNumber == 3 then
                        if matchFlag == 1 then
                            strInfo = "���졾��᡿���籭C�����������������ǵİ�����#R"..oppoGuildName.."#cffcf00�����C�鼾����"
                        else
                            strInfo = "���졾��᡿���籭C����������ǵİ�����#R"..oppoGuildName.."#cffcf00�����C��ھ���"
                        end
                    end
                elseif groupType == 1 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭B��1/4�������ǵİ����̭#R"..oppoGuildName.."#cffcf00���ɹ�����4ǿ�������½�������A�顣"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭B���������ǵİ�����#R"..oppoGuildName.."#cffcf00���ɹ�����B�������"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭B���������������ǵİ�����#R"..oppoGuildName.."#cffcf00�����B�鼾����"
                    elseif turnNumber == 3 then
                        strInfo = "����᡿���籭B��������ǵİ�����#R"..oppoGuildName.."#cffcf00�����B��ھ���"
                    end
                elseif groupType == 2 then
                    if turnNumber == 0 then
                        strInfo = "����᡿���籭A��1/4�������ǵİ����̭#R"..oppoGuildName.."#cffcf00���ɹ�����4ǿ��"
                    elseif turnNumber == 1 then
                        strInfo = "����᡿���籭A���������ǵİ�����#R"..oppoGuildName.."#cffcf00���ɹ��������������ֺ����᱾�졾��᡿���籭��ڡ�"
                    elseif turnNumber == 2 then
                        strInfo = "����᡿���籭A���������������ǵİ�����#R"..oppoGuildName.."#cffcf00�����A�鼾����"
                    elseif turnNumber == 3 then
                        strInfo = "����᡿���籭A��������ǵİ�����#R"..oppoGuildName.."#cffcf00�����A��ھ���"
                    end
                end
                LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)

                --����Player�����Ϣ
                local nCountryId   = GetCurCountry( sceneId, objId)
                local nBeKilled    = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_DIECOUNT)

                allResult[ i + 1].kill = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_LEADER)
                allResult[ i + 1].collect = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_ASSIST)
                allResult[ i + 1].occour = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_FAMILY)
                allResult[ i + 1].flag = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_GOLD)
                allResult[ i + 1].tower = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_KILL_OTHER)
                allResult[ i + 1].score = GetPlayerRuntimeData( sceneId, objId, RD_GUILDCONTEND_SCORE)
                allResult[ i + 1].nGuildFlag = nGuildFlag
                allResult[ i + 1].nCountryId = nCountryId
                allResult[ i + 1].name = name
                Msg2Player( sceneId, objId, format( "���#R#{_MONEY%d}#cffcc00����Ǯ", x300615_g_RewardTable[ index].rewards[ 1].gmoney), 8, 2)
                Msg2Player( sceneId, objId, format( "���#R%d#cffcc00���ʹ��", x300615_g_RewardTable[ index].rewards[ 1].gshiming), 8, 2)
                Msg2Player( sceneId, objId, format( "���#R%d��#cffcc00��ᾭ��", x300615_g_RewardTable[ index].rewards[ 1].gxp), 8, 2)
                if firstWin == 0 then
                    -- һ���Ը���ʤ��ά��
                    firstWin = 1
                    AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gmoney)
                    AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gshiming)
                    AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gxp)
                end
            end
        end
    end

    -- ����������
    sort( allResult, function ( a, b) return a.score > b.score end)
    -- �ͻ�����ʾǰ20��
    for i, item in allResult do
        if i > 20 then
            break
        end
        GuildContendSendPlayerInfo( sceneId, item.name, item.nCountryId, 
            item.kill, 
            item.collect, 
            item.occour, 
            item.flag, 
            item.tower, 
            item.score, 
            item.nGuildFlag)
    end

    -- ֪ͨGLServer�����°�����籭ʤ������
    if Winner == 0 then
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
        UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 0, 0, groupType)
    else
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 0, 0, groupType)
    end

    -- ���³���״̬
    SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
end

-- ����
function x300615_OnPlayerRelive( sceneId, selfId, ReliveType)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local nGuildId = GetGuildID( sceneId, selfId)
    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local rx = random( 1, 3)
    local rz = random( 1, 3)

    if nGuildId == nGuildA then
        SetPos( sceneId, selfId, x300615_g_RedInitPosX + rx, x300615_g_RedInitPosZ + rz)
    else
        SetPos( sceneId, selfId, x300615_g_BlueInitPosX + rx, x300615_g_BlueInitPosZ + rz)
    end

    ClearRageRecoverTick( sceneId, selfId)
    RestoreHp( sceneId, selfId, 100)
    RestoreRage( sceneId, selfId, 100)
    ClearMutexState( sceneId, selfId, 6)
    SendReliveResult( sceneId, selfId, 1)
end

-- GLServer
function x300615_OnWinLose( sceneId, selfId, winGuild, loseGuild, turnNumber)
    -- print( "*-*-*-*-*-*-*-*-*-*-*-*-*-*" )
end

-- GLServer������ս��ʱ��ͬ����Ϣ��iTimeΪս���ѽ���ʱ�䡣
function x300615_OnSyncGuildBattleTime( sceneId, iTime)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- print( sceneId.."ͬ��ʱ�䣺"..iTime)

    -- ����ʣ�����ʱ��
    local remainTime = x300615_g_FightTime - iTime
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_COUNT_ITME, remainTime)

    -- ����ǰ�����е��������ͬ��ս��ʱ��
    local nHumanCount = GetScenePlayerCount( sceneId)
    local i = 0
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        if objId >= 0 then
            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILD_CONTEND_SCRIPT, -1, -1)

            if iTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILD_CONTEND_SCRIPT, remainTime, remainTime)
            end
        end
    end
end

-- �������֪ͨ��Ҽ��������籭
-- turnNumber ������籭�ִκţ�0����3��
-- groupType �������id
-- oppoGuildId ���ֶ��ְ��ID
function x300615_OnInformJoin( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildId)
    local strInfo = "�μӡ���᡿���籭��"
    local oppoGuildName = GetGuildName( oppoGuildId)

    -- ״̬���
    for i, item in x300615_g_MutexTable do
        if IsPlayerMutexState( sceneId, selfId, item) > 0 then
            return
        end
    end

    -- ����ʱ���ܽ���
    if IsHaveSpecificImpact( sceneId, selfId, 7702) == 1 then
        return
    end

    if GetPKMode( sceneId, selfId) ~= 0 then
        return
    end

    if IsHideName( sceneId, selfId) == 1 then
        return
    end

	if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
	end

	if IsCharacterLiving( sceneId, selfId) == 0 then
		return
	end

    if groupType == 0 then
        if turnNumber == 0 then
            strInfo = "׼���μӡ���᡿���籭C��1/8������"
        elseif turnNumber == 1 then
            strInfo = "׼���μӡ���᡿���籭C��1/4������"
        elseif turnNumber == 2 then
            strInfo = "׼���μӡ���᡿���籭C��������"
        elseif turnNumber == 3 then
            if matchFlag == 1 then
                strInfo = "׼���μӡ���᡿���籭C��������������"
            else
                strInfo = "׼���μӡ���᡿���籭C�������"
            end
        end
    elseif groupType == 1 then
        if turnNumber == 0 then
            strInfo = "׼���μӡ���᡿���籭B��1/4������"
        elseif turnNumber == 1 then
            strInfo = "׼���μӡ���᡿���籭B��������"
        elseif turnNumber == 2 then
            strInfo = "׼���μӡ���᡿���籭B��������������"
        elseif turnNumber == 3 then
            strInfo = "׼���μӡ���᡿���籭B�������"
        end
    elseif groupType == 2 then
        if turnNumber == 0 then
            strInfo = "׼���μӡ���᡿���籭A��1/4������"
        elseif turnNumber == 1 then
            strInfo = "׼���μӡ���᡿���籭A��������"
        elseif turnNumber == 2 then
            strInfo = "׼���μӡ���᡿���籭A��������������"
        elseif turnNumber == 3 then
            strInfo = "׼���μӡ���᡿���籭A�������"
        end
    end
    Msg2Player( sceneId, selfId, strInfo, 8, 2)

    local strMsg = format( "WCL: Inform player %s enter world cup. SceneID=%d, GroupID=%d, OpponentGuild=%d", GetName( sceneId, selfId), sceneId, groupType, oppoGuildId)
    WriteLog( 1, strMsg)

    if oppoGuildId ~= -1 then
        AskPlayerToJoinWorldCup( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildName)
    end
end

-- ֪ͨ���ֱ�ӽ�����һ��
function x300615_OnPromotion( sceneId, selfId, groupType, turnNumber, matchFlag)
    local strInfo = "ֱ�ӽ�����"

    if groupType == 0 then
        if turnNumber == 0 then
            strInfo = "����᡿���籭C��1/8�������ǵİ���ֿգ�ֱ�ӽ���8ǿ��"
        elseif turnNumber == 1 then
            strInfo = "����᡿���籭C��1/4�������ǵİ���ֿգ�ֱ�ӽ���4ǿ��"
        elseif turnNumber == 2 then
            strInfo = "����᡿���籭C���������ǵİ���ֿգ�ֱ�ӽ��������"
        elseif turnNumber == 3 then
            if matchFlag == 1 then
                strInfo = "����᡿���籭C�����������������ǵİ���ֿգ�ֱ�ӻ��C�鼾����"
            else
                strInfo = "����᡿���籭C����������ǵİ���ֿգ�ֱ�ӻ��C��ھ���"
            end
        end
    elseif groupType == 1 then
        if turnNumber == 0 then
            strInfo = "����᡿���籭B��1/4�������ǵİ���ֿգ�ֱ�ӽ���B��4ǿ��"
        elseif turnNumber == 1 then
            strInfo = "����᡿���籭B���������ǵİ���ֿգ�ֱ�ӽ��������"
        elseif turnNumber == 2 then
            strInfo = "����᡿���籭B���������������ǵİ���ֿգ�ֱ�ӳ�ΪB�鼾����"
        elseif turnNumber == 3 then
            strInfo = "����᡿���籭B��������ǵİ���ֿգ�ֱ�ӳ�ΪB��ھ���"
        end
    elseif groupType == 2 then
        if turnNumber == 0 then
            strInfo = "����᡿���籭A��1/4�������ǵİ���ֿգ�ֱ�ӽ���4ǿ��"
        elseif turnNumber == 1 then
            strInfo = "����᡿���籭A���������ǵİ���ֿգ�ֱ�ӽ��������"
        elseif turnNumber == 2 then
            strInfo = "����᡿���籭A���������������ǵİ���ֿգ�ֱ�ӳ�ΪA�鼾����"
        elseif turnNumber == 3 then
            strInfo = "����᡿���籭A��������ǵİ���ֿգ�ֱ�ӳ�ΪA��ھ���"
        end
    end
    Msg2Player( sceneId, selfId, strInfo, 8, 2)

    local strMsg = format( "WCL: Inform player %s promotion. SceneID=%d, GroupID=%d", GetName( sceneId, selfId), sceneId, groupType)
    WriteLog( 1, strMsg)
end

-- �ͻ��������뿪ս��
function x300615_OnPlayerAskLeave( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    RestoreHp( sceneId, selfId, 100)
    RelivePlayerNM( sceneId, selfId, 2)
    --�������״̬(������˵Ļ�)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE, 0)

    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7801)
        -- ��ԭս��ɼ���
        SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
        SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        SetSceneMapDataFlag( sceneId, 1, 7, "����", 126, 124, -1)
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7802) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7802)
    end

    -- �ָ���Ӫ
    local nCountryId = GetCurCountry( sceneId, selfId)
    SetCurCamp( sceneId, selfId, nCountryId)

    -- ����漣Buff������еĻ�
    -- if IsHaveSpecificImpact( sceneId, selfId, x300615_g_MiracleId) == 1 then
        -- CancelSpecificImpact( sceneId, selfId, x300615_g_MiracleId)
    -- end

    -- �����������ˮ�������
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    -- ���ؽ���ս��ǰ�ĵط�
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 and x ~= 0 and z ~= 0 then
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
        NewWorld( sceneId, selfId, nBakSceneId, x, z, x300615_g_ScriptId)
        return
    end

    --���ؽ���NPC���
    local nCountry = GetCurCountry( sceneId, selfId)
    local nDestSceneId = 0
    if nCountry == 0 then
        --¥��
        nDestSceneId = 50
    elseif nCountry == 1 then
        --��ɽ
        nDestSceneId = 150
    elseif nCountry == 2 then
        --����
        nDestSceneId = 250
    elseif nCountry == 3 then
        --�ػ�
        nDestSceneId = 350
    end

    local nOffsetX = random( 8, 12)
    local nOffsetZ = random( 8, 12)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
    NewWorld( sceneId, selfId, nDestSceneId, x300615_g_PosX + nOffsetX, x300615_g_PosZ + nOffsetZ, 300615)
end

--�����ȷ����
function x300615_ProcAcceptCheck( sceneId, selfId, targetId)
    x300615_OnPlayerAskEnter( sceneId, selfId, targetId)
end

function x300615_OnPlayerAskEnter( sceneId, selfId, targetId)
    local nGuildId = GetGuildID( sceneId, selfId)
    if nGuildId < 0 or nGuildId > 1024 then
        if targetId ~= 0 then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300615_g_Name)
                AddQuestText( sceneId, "����δ�����κΰ�ᣡ���ܽ���ս����" )
            EndQuestEvent()
            DispatchQuestEventList( sceneId, selfId, targetId)
            return
        end
    end

    -- ״̬���
    for i, item in x300615_g_MutexTable do
        if IsPlayerMutexState( sceneId, selfId, item) > 0 then
            Msg2Player( sceneId, selfId, "�����ڲ��ܽ������籭ս��", 8, 3)
            return
        end
    end

    -- ����ʱ���ܽ���
    if IsHaveSpecificImpact( sceneId, selfId, 7702) == 1 then
        Msg2Player( sceneId, selfId, "�������ʱ���ܽ������籭ս��", 8, 3)
        return
    end

    if GetPKMode( sceneId, selfId) ~= 0 then
        Msg2Player( sceneId, selfId, "����PKģʽ���ܽ������籭ս��", 8, 3)
        return
    end

    if IsHideName( sceneId, selfId) == 1 then
        Msg2Player( sceneId, selfId, "����״̬���ܽ������籭ս��", 8, 3)
        return
    end

    GuildContendAskEnter( sceneId, selfId)
end

-- ���ڰ��û����ѡ����İ�����籭
function x300615_OnRejectEnter( sceneId, selfId)
    Msg2Player( sceneId, selfId, "�����ڵİ��û����ѡ����ġ���᡿���籭�����ܽ���ս����", 8, 2)
end

-- �������ս���Ľ�ɫ��δ�����κΰ��
function x300615_OnNotBelongGuild( sceneId, selfId)
    Msg2Player( sceneId, selfId, "����δ�����κΰ�ᣡ���ܽ���ս����", 8, 2)
end

-- �������ս���Ľ�ɫ���ڵİ�᱾�ֱ����ֿ�
function x300615_OnNotOpponent( sceneId, selfId)
    Msg2Player( sceneId, selfId, "�����ڵİ�᱾�����籭�ֿգ����ܽ���ս����", 8, 2)
end

-- ���ݳ���ID��ð�����籭�ű�ID������Ƿ��ؽű�ID�����򷵻�0
function x300615_GetGuildContendScript( sceneId)
    local sceneName = GetBattleSceneName( sceneId)
    for i, item in x300615_g_SceneScript do
        if item.Name == sceneName then
            return item.ScriptID
        end
    end

    return 0
end

-- ��ҽ��������籭ս��
function x300615_OnPlayerEnter( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)

    if x300615_GetGuildContendScript( sceneId) == 0 then
        return
    end

    local strGuildA = GetGuildName( nGuildA)
    local strGuildB = GetGuildName( nGuildB)
    local rx = random( 1, 3)
    local rz = random( 1, 3)

    local nGuildId = GetGuildID( sceneId, selfId)
    if nGuildA == nGuildId then
        --SetCurCamp( sceneId, selfId, 5)
        SendGuildContendDisable( sceneId, selfId, 0, 0)
        SetPos( sceneId, selfId, x300615_g_RedInitPosX + rx, x300615_g_RedInitPosZ + rz)
    elseif nGuildB == nGuildId then
        --SetCurCamp( sceneId, selfId, 6)
        SendGuildContendDisable( sceneId, selfId, 0, 1)
        SetPos( sceneId, selfId, x300615_g_BlueInitPosX + rx, x300615_g_BlueInitPosZ + rz)
    end

    --�����ԭ�ȵĳ������б���
    local scenePre = GetPlayerRuntimeData( sceneId,selfId, RD_HUMAN_SCENE_PRE)
    if scenePre >= 0 then
        local CurX = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo( sceneId, selfId, scenePre, CurX, CurZ)

        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_SCENE_PRE, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSX_PRE, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSZ_PRE, 0)
    end

    -- ��Ӫ����
    if GetWorldCupState( sceneId) == STATE_GUILD_WORLDCUP_START then
        local guildId = GetGuildID( sceneId, selfId)
        if guildId == nGuildA then
            SetCurCamp( sceneId, selfId, 5)
        elseif guildId == nGuildB then
            SetCurCamp( sceneId, selfId, 6)
        else
            -- ����������ڸ�ս���İ��ʹ��ͳ�ȥ
            x300615_OnPlayerAskLeave( sceneId, selfId)
        end
    else
        -- ��սǰ����ͳһ��Ӫ��������ǰPK
        SetCurCamp( sceneId, selfId, 4)
        -- ����Ч
		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 30)
		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 31)
    end
end

function x300615_OnPlayerLeaveGuild( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end
    
    x300615_OnPlayerAskLeave( sceneId, selfId)
    --SetGuildBattleDisable( sceneId, selfId, 1, 0)
end

function x300615_OnPlayerLeave( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    RestoreHp( sceneId, selfId, 100)
    if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE) == 1 then
        --�������״̬(������˵Ļ�)
        RelivePlayerNM( sceneId, selfId, 2)
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE, 0)
    end

    -- �ָ���Ӫ
    local nCountryId = GetCurCountry( sceneId, selfId)
    SetCurCamp( sceneId, selfId, nCountryId)

    -- ����漣Buff������еĻ�
    -- if IsHaveSpecificImpact( sceneId, selfId, x300615_g_MiracleId) == 1 then
        -- CancelSpecificImpact( sceneId, selfId, x300615_g_MiracleId)
    -- end

    -- �����������ˮ�������
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    -- ���ؽ���ս��ǰ�ĵط�
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
        NewWorld( sceneId, selfId, nBakSceneId, x, z, x300615_g_ScriptId)
        return
    end

    --���ؽ���NPC���
    local nCountry = GetCurCountry( sceneId, selfId)
    local nDestSceneId = 0
    if nCountry == 0 then
        --¥��
        nDestSceneId = 50
    elseif nCountry == 1 then
        --��ɽ
        nDestSceneId = 150
    elseif nCountry == 2 then
        --����
        nDestSceneId = 250
    elseif nCountry == 3 then
        --�ػ�
        nDestSceneId = 350
    end

    local nOffsetX = random( 8, 12)
    local nOffsetZ = random( 8, 12)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
    NewWorld( sceneId, selfId, nDestSceneId, x300615_g_PosX + nOffsetX, x300615_g_PosZ + nOffsetZ, 300615)
end

-- �������Ա֮��PK��������ݱ�ɱ����ݼ�¼����
-- selfId����ɱ�ߵ�ObjId
-- killerId��ɱ���ߵ�ObjId
function x300615_OnPlayerDie( sceneId, selfId, killerId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- �����������ˮ�������
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    local ownerId = GetOwnerID( sceneId, killerId)
    local muderer = killerId
    if ownerId ~= -1 then
        -- ������ӥɱ������
        SetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_KILL_LEADER, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER) + 1)
        muderer = ownerId
    else
        SetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER) + 1)
    end

    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        -- ���ϴ���ս��
        CancelSpecificImpact( sceneId, selfId, 7801)
        CancelSpecificImpact( sceneId, selfId, 7802)
        local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        -- ɱ�������߲��������,����û������,������30����,����Ϊ��Ч,���������
        if IsPlayerStateNormal( sceneId, muderer) == 1 and 
            IsPlayerMutexState( sceneId, muderer, PLAYER_STATE_DIE) ~= 1 and 
            GetDist( sceneId, selfId, muderer, 30) <= 30 then
            ReCallHorse( sceneId, muderer)
            SendSpecificImpactToUnit( sceneId, muderer, muderer, muderer, 7801, 0)
            SendSpecificImpactToUnit( sceneId, muderer, muderer, muderer, 7802, 0)
            local x,y = GetWorldPos( sceneId, muderer)
            SetSceneMapDataFlag( sceneId, 1, 7, "����", x, y, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, muderer)
            SetPlayerRuntimeData( sceneId, muderer, RD_DANCERY_BODYID, growPointid)
        else
            -- ԭ�ص��䣬�����ڱ�ɱ�����òɼ���
            local x,y = GetWorldPos( sceneId, selfId)
            SetGrowPointPos( sceneId, growPointid, x + 1, y + 1)
            SetGrowPointIntervalContainer( sceneId, growPointid, 1000)
            SetSceneMapDataFlag( sceneId, 1, 7, "����", x + 1, y + 1, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -2)
        end
    end

    --��¼��ɱ����
    SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_DIECOUNT, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_DIECOUNT) + 1)
end

-- �������ֱ�ӽ��������籭��������
function x300615_OnPlayerNewConnectEnter( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        x300615_OnPlayerAskLeave( sceneId, selfId)
    end
end

-- ������ʱ��
function x300615_ProcTiming( sceneId, nowTime)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local state = GetWorldCupState( sceneId)
    -- �ڱ�����ʼ��ʱ�����վ��Ϊ�ղ���ʼ���˵�ͬʱ���ܻ�����ҽ���ս������Ҫ�ٴ��߳�
    if state == STATE_GUILD_WORLDCUP_FINISHED then
        local nHumanCount = GetScenePlayerCount( sceneId)
        for i = 0, nHumanCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
                -- �ָ���Ӫ
                local nCountryId = GetCurCountry( sceneId, objId)
                SetCurCamp( sceneId, objId, nCountryId)
                x300615_OnPlayerAskLeave( sceneId, objId)
            end
        end
        return
    end

    local GuildIdA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local GuildIdB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local flag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A)

    -- ���������ǰ����
    if state == STATE_GUILD_WORLDCUP_END then
        return
    end

    if state == STATE_GUILD_WORLDCUP_START and flag ~= -1 then
        x300615_g_Occupy[ sceneId] = x300615_g_Occupy[ sceneId] + 1
        if x300615_g_Occupy[ sceneId] >= 10 then
            if flag == GuildIdA then
                SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + x300615_g_FlagScore)
            elseif flag == GuildIdB then
                SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + x300615_g_FlagScore)
            end
            x300615_g_Occupy[ sceneId] = 0
        end
    end
    flag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B)
    if state == STATE_GUILD_WORLDCUP_START and flag ~= -1 then
        x300615_g_Occupy_B[ sceneId] = x300615_g_Occupy_B[ sceneId] + 1
        if x300615_g_Occupy_B[ sceneId] >= 10 then
            if flag == GuildIdA then
                SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + x300615_g_FlagScore)
            elseif flag == GuildIdB then
                SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + x300615_g_FlagScore)
            end
            x300615_g_Occupy_B[ sceneId] = 0
        end
    end

    if GuildIdA == -1 and GuildIdB == -1 then
        return
    end

    -- ���»��ֵ��ͻ���
    local scoreA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE)
    local scoreB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE)
    BroadcastGuildContendScore( sceneId, 0, scoreA)
    BroadcastGuildContendScore( sceneId, 1, scoreB)

    local nSize = getn( x300615_g_ToStopEffectList[ sceneId] )
    if nSize > 0 then
        local temp = x300615_g_ToStopEffectList[ sceneId]
        x300615_g_ToStopEffectList[ sceneId] = {}
        if nSize > x300615_g_ClearPerSecond then
            for i = nSize - x300615_g_ClearPerSecond + 1, nSize do
                if IsPlayerStateNormal( sceneId, temp[ i] ) == 1 and IsObjValid( sceneId, temp[ i] ) == 1 then
                    CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, temp[ i], 30)
                    CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, temp[ i], 31)
                end
            end
            for i = 1, nSize - x300615_g_ClearPerSecond do
                x300615_g_ToStopEffectList[ sceneId][ i] = temp[ i]
            end
        else
            for i = 1, nSize do
                if IsPlayerStateNormal( sceneId, temp[ i] ) == 1 and IsObjValid( sceneId, temp[ i] ) == 1 then
                    CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, temp[ i], 30)
                    CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, temp[ i], 31)
                end
            end
        end
    end

    -- ���ս���������Ƿ���Ч
	local capflag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY)
	if capflag > -1 then
		if IsObjValid( sceneId, capflag) == 0 or IsPlayerStateNormal( sceneId, capflag) ~= 1 or IsPlayerMutexState( sceneId, capflag, PLAYER_STATE_DIE) == 1 then
			SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
			SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
			SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
            SetSceneMapDataFlag( sceneId, 1, 7, "����", 126, 124, -1)
        else
            local x, z = GetWorldPos( sceneId, capflag)
            SetSceneMapDataFlag( sceneId, 1, 7, "����", x, z, -1)
		end
    elseif capflag ~= -2 then
        -- �������뿪ս��
        SetSceneMapDataFlag( sceneId, 1, 7, "����", 126, 124, -1)
	end

    -- ͳ��˫������
    local CountA = 0
    local CountB = 0
    local nHumanCount = GetScenePlayerCount( sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
            local nGuildId = GetGuildID( sceneId, objId)
            if nGuildId == GuildIdA then
                CountA = CountA + 1
            elseif nGuildId == GuildIdB then
                CountB = CountB + 1
            end
        end
    end
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_COUNT, CountA)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_COUNT, CountB)
    -- �����һ����������������ָ��ֵ�Ͱ�����ǵ�T��ս��
    if CountA > x300615_g_MaxCountInBattleScene or CountB > x300615_g_MaxCountInBattleScene then
        for i = 0, nHumanCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if GetPlayerRuntimeData( sceneId, objId, RD_COLLECT_HORSE_HIGH) == 1 then
                Msg2Player( sceneId, objId, format( "�����ڰ�����ս�������Ѵ�����%d�ˣ������ٽ����ˡ�", x300615_g_MaxCountInBattleScene), 8, 2)
                x300615_OnPlayerLeave( sceneId, objId)
            end
        end
    end

    -- �����һ����ս������Ϊ0�����ж��ֻ�ʤ
    local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
    local turnNumber = GetWorldCupSceneData_Param( sceneId, LD_GUILD_CONTEND_TURNNUMBER)
    local matchFlag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAG)
    if state == STATE_GUILD_WORLDCUP_START and CountB == 0 and CountA > 0 then
        x300615_GenResult( sceneId, GuildIdA, GuildIdB)
        x300615_PerfectVictory( sceneId, turnNumber, groupType, matchFlag, GetGuildName( GuildIdB) )

        return
    end
    if state == STATE_GUILD_WORLDCUP_START and CountA == 0 and CountB > 0 then
        x300615_GenResult( sceneId, GuildIdB, GuildIdA)
        x300615_PerfectVictory( sceneId, turnNumber, groupType, matchFlag, GetGuildName( GuildIdA) )

        return
    end

    -- ������ᶼû����ս��������ж�ʤ��
    if state == STATE_GUILD_WORLDCUP_START and CountA == 0 and CountB == 0 then
        if random( 1, 2) == 1 then
            SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
            SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
            UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 1, 1, groupType)
        else
            SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
            SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
            UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 1, 1, groupType)
        end

        -- ���³���״̬
        SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        -- �������˫�����ID������������������ٴθ����ִ�
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)

        return
    end

    -- ���������һ�����ִﵽx300615_g_TotalScore�����ж�ʤ��
    if state == STATE_GUILD_WORLDCUP_START and scoreA >= x300615_g_TotalScore or scoreB >= x300615_g_TotalScore then
        x300615_OnBattleEnd( sceneId)
        -- �������˫�����ID������������������ٴθ����ִ�
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
    end
end

function x300615_ProcMapPlayerEnter( sceneId, selfId)
    local aCount = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_COUNT)
    local bCount = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_COUNT)
    local aGuild = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local bGuild = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local gid = GetGuildID( sceneId, selfId)

    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, 0)
    if gid == aGuild then
        if aCount < x300615_g_MaxCountInBattleScene then
            return
        end
    elseif gid == bGuild then
        if bCount < x300615_g_MaxCountInBattleScene then
            return
        end
    end
    -- ����ս�������������������ϱ�ǣ��ڶ�ʱ����T��
    SetPlayerRuntimeData( sceneId, selfId, RD_COLLECT_HORSE_HIGH, 1)
end

function x300615_GenResult( sceneId, winGuild, loseGuild)
    local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
    local turnNumber = GetWorldCupSceneData_Param( sceneId, LD_GUILD_CONTEND_TURNNUMBER)
    local matchFlag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAG)

    SetGuildQuestData( sceneId, winGuild, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
    SetGuildQuestData( sceneId, loseGuild, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
    SetGuildQuestData( sceneId, winGuild, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
    SetGuildQuestData( sceneId, loseGuild, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
    UpdateGuildContendTurnsInfo( sceneId, winGuild, 0, 1, groupType)

    -- ���³���״̬
    SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
    -- �������˫�����ID������������������ٴθ����ִ�
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
end

-- ����ȫ���뿪ս�������û�μӣ�ֱ�ӻ�ʤ���ѻ�ʤ������г�Ա����ս��
function x300615_PerfectVictory( sceneId, turnNumber, groupType, matchFlag, oppoGuildName)
    local nHumanCount = GetScenePlayerCount( sceneId)
    local strOppoName = "����"
    if oppoGuildName ~= "" then
        strOppoName = oppoGuildName
    end

    -- �ҵ���������������
    local index = 1
    for i, item in x300615_g_RewardTable do
        if turnNumber == item.turnNumber and groupType == item.groupType then
            index = i
            break
        end
    end

    local firstWin = 0
    -- �����а���Ա����ս��
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        local name = GetName( sceneId, objId)
        local strInfo = "�������ڰ�����İ��ĳ�Ա������ս��������ֱ�ӻ��ʤ����"
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "����᡿���籭C��1/8�������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ�����C��8ǿ�����ֽ���������B������ᡣ"
            elseif turnNumber == 1 then
                strInfo = "����᡿���籭C��1/4�������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ�����C��4ǿ�������½�������B�顣"
            elseif turnNumber == 2 then
                strInfo = "����᡿���籭C���������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ�������������������C��ھ���"
            elseif turnNumber == 3 then
                if matchFlag == 1 then
                    strInfo = "����᡿���籭C���������������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪC�鼾����"
                else
                    strInfo = "����᡿���籭C��������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪC��ھ���"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "����᡿���籭B��1/4�������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ�����B��4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "����᡿���籭B���������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ��������������ֺ�����B��ھ���"
            elseif turnNumber == 2 then
                strInfo = "����᡿���籭B���������������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪB�鼾����"
            elseif turnNumber == 3 then
                strInfo = "����᡿���籭B��������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪB��ھ���"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "����᡿���籭A��1/4�������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ�����4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "����᡿���籭A���������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ�����ɹ��������������ֺ�����A��ھ���"
            elseif turnNumber == 2 then
                strInfo = "����᡿���籭A���������������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪA�鼾����"
            elseif turnNumber == 3 then
                strInfo = "����᡿���籭A��������ǰ��Ķ���#R"..strOppoName.."#cffcf00�ĳ�Ա������ս��������ֱ�ӻ��ʤ������ΪA��ھ���"
            end
        end
        LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)
        Msg2Player( sceneId, objId, format( "���#R#{_MONEY%d}#cffcc00����Ǯ", x300615_g_RewardTable[ index].rewards[ 1].gmoney), 8, 2)
        Msg2Player( sceneId, objId, format( "���#R%d#cffcc00���ʹ��", x300615_g_RewardTable[ index].rewards[ 1].gshiming), 8, 2)
        Msg2Player( sceneId, objId, format( "���#R%d��#cffcc00��ᾭ��", x300615_g_RewardTable[ index].rewards[ 1].gxp), 8, 2)
        if firstWin == 0 then
            firstWin = 1
            AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gmoney)
            AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gshiming)
            AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gxp)
        end
        -- �ָ���Ӫ
        local nCountryId = GetCurCountry( sceneId, objId)
        SetCurCamp( sceneId, objId, nCountryId)
        x300615_OnPlayerAskLeave( sceneId, objId)
    end
end

-- ��������
function x300615_UpdateReward( sceneId, selfId, groupType, turnNumber, result)
    local index = 1
    for i, item in x300615_g_RewardTable do
        if turnNumber == item.turnNumber and groupType == item.groupType then
            index = i
            break
        end
    end

    local strtip = ""
    local strgroup = ""
    local strresult = ""
    if groupType == 1 then
        strgroup = "B��"
    elseif groupType == 2 then
        strgroup = "A��"
    end
    if turnNumber == 0 then
        strtip = "�ķ�֮һ����"
    elseif turnNumber == 1 then
        strtip = "�����"
    elseif turnNumber == 2 then
        strtip = "����������"
    elseif turnNumber == 3 then
        strtip = "����"
    end
    if result == 1 then
        strresult = "��ʤ"
    elseif result == 2 then
        strresult = "ʧ��"
    end

    Msg2Player( sceneId, selfId, format( "����᡿���籭%s%s�������ڰ��%s��", strgroup, strtip, strresult), 8, 2)
    local xp = x300615_g_RewardTable[ index].rewards[ result].xpCoff * GetLevel( sceneId, selfId)
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "���#R%d#cffcc00�㾭�顣", xp), 8, 2)
    local bangGong = x300615_g_RewardTable[ index].rewards[ result].bangGong
    AddGuildUserPoint( sceneId, selfId, bangGong)
    Msg2Player( sceneId, selfId, format( "���#R%d#cffcc00��ﹱ��", bangGong), 8, 2)
end

-- ��ǰ������ʼ
function x300615_OnOpenItemBox( sceneId, selfId, targetId, GrowpointId, ItemIndex)
    -- ����û��ʼ������ɼ�����
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        Msg2Player( sceneId, selfId, "������û��ʼ�����ܽ��д˲���", 8, 3)
        return 1
    end

    if GrowpointId == x300615_GT_ArmyFlag then
        -- �Ƿ��Ѿ�������ռ��
    elseif GrowpointId == x300615_GT_Flag_A then
        if GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A) == GetGuildID( sceneId, selfId) then
            Msg2Player( sceneId, selfId, "�Ѿ��������ڵİ��ռ��", 8, 3)
            return 1
        end
    elseif GrowpointId == x300615_GT_Flag_B then
        if GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B) == GetGuildID( sceneId, selfId) then
            Msg2Player( sceneId, selfId, "�Ѿ��������ڵİ��ռ��", 8, 3)
            return 1
        end
    elseif GrowpointId == x300615_GT_Miracle then
        -- ��鱳���ռ�
		if GetBagSpace( sceneId, selfId) <= 0 then
			Msg2Player( sceneId, selfId, "��Ʒ�����������ܽ��вɼ�", 8, 3)
            return 1
		end
        -- �������Ƿ��Ѿ����Ĺ�������
        if GetItemCountInBag( sceneId, selfId, x300615_g_ItemId) > 0 then
            Msg2Player( sceneId, selfId, "�����ظ��ɼ�@item_"..x300615_g_ItemId, 8, 3)
            return 1
        end
    end

    return 0
end

function x300615_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
    -- print( "���밲ȫ��" )
    -- �����û�����������Buff���о���������������Ż�ԭ��
    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7801)
        local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
        SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
        SetSceneMapDataFlag( sceneId, 1, 7, "����", 126, 124, -1)
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7802) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7802)
    end
    
end

function x300615_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId)
    -- print( "�뿪��ȫ��" )
end

-- ���պ�����ʼ
function x300615_OnRecycle( sceneId, selfId, targetId, GrowpointId, ItemIndex)
    -- ����û��ʼ������ɼ�����
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        return 0
    end

    -- print( "x300615_OnRecycle" )
    if GrowpointId == x300615_GT_ArmyFlag then
        --ǿ������
        ReCallHorse( sceneId, selfId)
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7801,   200)    --200����
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7802, 200)    --200����
        -- ���²ɼ�������ʱ��
        SetGrowPointIntervalContainer( sceneId, GrowpointId, -1)
        -- ��¼�ɼ���ObjID
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, selfId)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, GrowpointId)
    elseif GrowpointId == x300615_GT_Flag_A then
        -- ����ռ����
        local guildId = GetGuildID( sceneId, selfId)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A, guildId)
        -- ���¸���ռ�����
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD) + 1)
        -- ���¼�����
        x300615_g_Occupy[ sceneId] = 0
        LuaThisScenceM2Wrold( sceneId, format( "���%sռ����ռ����³��ս��", GetGuildName( guildId) ), 5, 1)
    elseif GrowpointId == x300615_GT_Flag_B then
        -- ����ռ����
        local guildId = GetGuildID( sceneId, selfId)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B, guildId)
        -- ���¸���ռ�����
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD) + 1)
        -- ���¼�����
        x300615_g_Occupy_B[ sceneId] = 0
        LuaThisScenceM2Wrold( sceneId, format( "���%sռ����ռ����³��ս��", GetGuildName( guildId) ), 5, 1)
    elseif GrowpointId == x300615_GT_Miracle then
        -- local guildId = GetGuildID( sceneId, selfId)
        -- -- ���¸���ռ�����
        -- SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY) + 1)
        -- -- �������������ս���ĳ�Ա��Buff
        -- local nHumanCount = GetScenePlayerCount( sceneId)
        -- for i = 0, nHumanCount - 1 do
            -- local objId = GetScenePlayerObjId( sceneId, i)
            -- if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
                -- if guildId == GetGuildID( sceneId, objId) then
                    -- SendSpecificImpactToUnit( sceneId, objId, objId, objId, x300615_g_MiracleId, 0)
                -- else
                    -- CancelSpecificImpact( sceneId, objId, x300615_g_MiracleId)
                -- end
            -- end
        -- end
 		BeginAddItem( sceneId)
		AddItem( sceneId, x300615_g_ItemId, 1)
		local ret = EndAddItem( sceneId, selfId)
		if ret > 0 then
			AddItemListToPlayer( sceneId, selfId)
		else
			Msg2Player( sceneId, selfId, "��Ʒ���������ɼ�ʧ��", 8, 3)
		end
    end

    return 1
end

-- ֪ͨս�������а���Ա���
function x300615_OnInformOutofBF( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildId, result)
    local name = GetName( sceneId, selfId)
    local strInfo = nil
    if result == 1 then
        -- ��ʤ
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������C��8ǿ��"
            elseif turnNumber == 1 then
                if matchFlag == 1 then
                    strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������C�鱣���ɹ���"
                else
                    strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������C��4ǿ�������½�������B�顣"
                end
            elseif turnNumber == 2 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������C�������"
            elseif turnNumber == 3 then
                if matchFlag == 0 then
                    strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭C��ھ���"
                else
                    strInfo = "�����ڰ��Ͷ���İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭C�鼾����"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������B��4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������B�������"
            elseif turnNumber == 2 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭B�鼾����"
            elseif turnNumber == 3 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭B��ھ���"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������A��4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ��������A�������"
            elseif turnNumber == 2 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭A�鼾����"
            elseif turnNumber == 3 then
                strInfo = "�������ڰ�����İ���Ա������ս�����������˵Ļ��ʤ������ñ��졾��᡿���籭A��ھ���"
            end
        end
    else
        -- ʧ��
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ��ұ���̭��û�ܽ���C��8ǿ��"
            elseif turnNumber == 1 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ��ұ���̭��û�ܽ���C��4ǿ��"
            elseif turnNumber == 2 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ����û�ܽ���C�������"
            elseif turnNumber == 3 then
                if matchFlag == 0 then
                    strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ�������ӱ��졾��᡿���籭C���Ǿ���"
                else
                    strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ������ñ��졾��᡿���籭C������"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ��ұ���̭��û�ܽ���B��4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ����û�ܽ���B�������"
            elseif turnNumber == 2 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ������ñ��졾��᡿���籭B������"
            elseif turnNumber == 3 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ�������ӱ��졾��᡿���籭B���Ǿ���"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ��ұ���̭��û�ܽ���A��4ǿ��"
            elseif turnNumber == 1 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ����û�ܽ���A�������"
            elseif turnNumber == 2 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ������ñ��졾��᡿���籭A������"
            elseif turnNumber == 3 then
                strInfo = "�����ڰ��ĳ�Ա������ս�������ǲ���ʧ�������ӱ��졾��᡿���籭A���Ǿ���"
            end
        end
    end

    if strInfo ~= nil then
        LuaScenceM2Player( sceneId, selfId, strInfo, name, 2, 1)
    end
end

-- �������ݻ�
function x300615_OnDie( sceneId, selfId, killerId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- �õ�ɱ�����������
    local nGuildId = GetGuildID( sceneId, killerId)
    local ownerId = GetOwnerID( sceneId, killerId)
    if ownerId ~= -1 then
        -- ������ӥɱ������
        nGuildId = GetGuildID( sceneId, ownerId)
        SetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_KILL_OTHER, GetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_KILL_OTHER) + 1)
    else
        SetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_OTHER, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_OTHER) + 1)
    end

    local score = 0
    local strTitle = ""
    local strName = ""
    local bFind = 0
    for i, item in x300615_g_HideTowerTable do
        if GetMonsterGUID( sceneId, selfId) == item.guid then
            local objId = FindMonsterByGUID( sceneId, x300615_g_ShowTowerTable[ i].guid)
            if IsObjValid( sceneId, objId) == 1 then
                DeleteMonster( sceneId, objId)
            end
            -- ��������
            CreateMonster( sceneId, 9738, item.x, item.z, 3, 409, -1, item.guid + 100, 4)
            -- �������GUID
            x300615_g_RuinList[ sceneId][ getn( x300615_g_RuinList) + 1] = item.guid + 100
            score = item.score
            strTitle = x300615_g_ShowTowerTable[ i].title
            strName = x300615_g_ShowTowerTable[ i].name
            bFind = 1
            break
        end
    end

    -- ���¸��˵÷�
    if ownerId ~= -1 then
        SetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_SCORE) + score)
    else
        SetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_SCORE) + score)
    end
    -- ���ݴݻٵļ������͸����ӷ�
    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    if nGuildA == nGuildId then
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + score)
    elseif nGuildB == nGuildId then
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + score)
    end
    if bFind == 1 then
        local strBroadcast = format( "���%s�ݻ���%s��%s", GetGuildName( nGuildId), strTitle, strName)
        local iCount = GetScenePlayerCount( sceneId)
        for i = 0, iCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if IsPlayerStateNormal( sceneId, objId) == 1 then
                LuaScenceM2Player( sceneId, objId, strBroadcast, GetName( sceneId, objId), 5, 1)
            end
        end
    end
end

