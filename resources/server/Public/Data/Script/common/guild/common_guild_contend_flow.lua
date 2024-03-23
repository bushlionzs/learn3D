-- 帮会世界杯
x300615_g_ScriptId 					= 300615
-- 【帮会】世界杯名称
x300615_g_Name                      = "【帮会】世界杯"
-- 战场路径
x300615_g_SceneName                 = "zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn"
x300615_g_SceneScript               = { { Name = "zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn", ScriptID = 300615} }

-- 帮会世界杯状态，参考GLServer\World\WorldData\GuildContendManager.h中的GuildContendState
-- 比赛前的自由准备状态
x300615_State_Prepare               = 1
-- 比赛开始
x300615_State_Start                 = 2
-- 比赛结束
x300615_State_End                   = 3
-- 本月帮会世界杯结束
x300615_State_Finished              = 4
-- 帮会世界杯战斗时间（秒）
x300615_g_FightTime                 = 1800

x300615_g_strNotJoinGuild           = "\t你尚未加入任何帮会！"
x300615_g_strOnlyforLeader          = "\t只有帮主才能使用此功能。"
x300615_g_strSignupTimePassed       = "\t现在不是报名时间！"

-- GLServer返回玩家请求代码定义，必须与WGGuildContend.h的WGReplyCode枚举值保持一致
GCR_SIGNUP_SUCCESS                  = 0     -- 报名成功。
GCR_SIGNUP_HASSIGNEDUP              = 1     -- 已经报过名了。
GCR_SIGNUP_STRENGTHNOTENOUGH        = 2     -- 帮会的综合实力不够参加帮会世界杯。
GCR_SIGNUP_NOTEXIST                 = 3     -- 报名帮会已不存在，可能是解散了。
GCR_WASHOUT                         = 4     -- 你所在帮会已被淘汰
GCR_NOTPATICIPATE                   = 5     -- 你所在帮会没有入选本月的帮会世界杯
GCR_INHIGHGROUP                     = 6     -- 帮会已经在A组或B组中了。
GCR_NOMATCHTOJOIN                   = 7     -- 本轮没有可参加的比赛。
-- 战场阵营初始坐标
x300615_g_RedInitPosX               = 23
x300615_g_RedInitPosZ               = 123
x300615_g_BlueInitPosX              = 229
x300615_g_BlueInitPosZ              = 123
-- 返回帮战NPC坐标
x300615_g_PosX                      = 127
x300615_g_PosZ                      = 117
-- 获胜积分
x300615_g_TotalScore                = 2000
-- 采集物品Id
x300615_g_ItemId                    = 13080024
x300615_g_MutexTable                = {
                                        PLAYER_STATE_STALL                , --摆摊
                                        PLAYER_STATE_FUBEN                , --副本
                                        PLAYER_STATE_GUILDBATTLEFIELDSCENE, --战场
                                        PLAYER_STATE_ARENASSCENE          , --擂台
                                        PLAYER_STATE_CITSCENE             , --城市
                                        PLAYER_STATE_PRISONSCENE          , --监狱
                                        PLAYER_STATE_DIE                  , --死亡
                                        PLAYER_STATE_BUS                  , --BUS
                                        PLAYER_STATE_CRASHBOX             , --运镖
                                        PLAYER_STATE_EXCHANGE             , --交易
                                        PLAYER_STATE_MENTALGAME           , --答题
                                        PLAYER_STATE_AUTOPLAY             , --挂机
                                        PLAYER_STATE_SUBTRAIN             , --代练
                                        PLAYER_STATE_PRISON               , --监狱
                                        PLAYER_STATE_OPENBOX              , --开箱
                                        PLAYER_STATE_KEYBORDMOVE          , --键盘移动
                                        PLAYER_STATE_TIESAN               , --铁人三项
                                        PLAYER_STATE_READYFUBEN           , --进入副本状态
                                        PLAYER_STATE_DUOQIBUFF			  , --夺旗任务有buff时的状态
                                        PLAYER_STATE_TONGQUBUFF			  , --童趣任务有buff时的状态
                                        PLAYER_STATE_FORBID_RIDE		  , --禁止骑马状态
                                        PLAYER_STATE_WEDDING			  , --婚礼状态
                                        PLAYER_STATE_ENJAIL				  , --囚禁状态
                                        PLAYER_STATE_Award				  , --领奖状态
                                        PLAYER_STATE_TransGold			  , --领取现金状态
                                        PLAYER_STATE_DANCERY              , --在舞厅挂机
}
-- 奇迹采集点类型Id
x300615_GT_Miracle                  = 727
-- 军旗采集点类型Id
x300615_GT_ArmyFlag                 = 726
-- 战旗采集点类型Id
x300615_GT_Flag_A                   = 728
-- 战旗采集点类型Id
x300615_GT_Flag_B                   = 729
-- 占领战旗计数器
x300615_g_Occupy                    = {}
-- 占领战旗计数器
x300615_g_Occupy_B                  = {}
-- 军旗占领每分钟所得分数
x300615_g_FlagScore                 = 2
-- 奇迹Buff（加100攻击）
x300615_g_MiracleId                 = 7800
-- 每个帮会可以进入世界杯战场的最大人数
x300615_g_MaxCountInBattleScene     = 50
-- 隐藏箭塔
x300615_g_HideTowerTable            = {
                                        { typeid = 9732, x = 60,  z = 121, guid = 129721, base_ai = 22, aiscript = -1, campid = 5, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 60,  z = 127, guid = 129722, base_ai = 22, aiscript = -1, campid = 5, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 195, z = 127, guid = 129726, base_ai = 22, aiscript = -1, campid = 6, faceDir = 270, title = "", name = "", score = 200 }, 
                                        { typeid = 9732, x = 195, z = 120, guid = 129727, base_ai = 22, aiscript = -1, campid = 6, faceDir = 270, title = "", name = "", score = 200 }, 
}
-- 显示箭塔，当隐藏箭塔被摧毁时把对应显示的箭塔也删除掉
x300615_g_ShowTowerTable            = {
                                        { typeid = 9737, x = 60,  z = 121, guid = 129741, base_ai = 3, aiscript = -1, campid = 5, faceDir = 270, title = "汗国联军", name = "箭塔", score = 200 }, 
                                        { typeid = 9737, x = 60,  z = 127, guid = 129742, base_ai = 3, aiscript = -1, campid = 5, faceDir = 270, title = "汗国联军", name = "箭塔", score = 200 }, 
                                        { typeid = 9737, x = 195, z = 127, guid = 129746, base_ai = 3, aiscript = -1, campid = 6, faceDir = 270, title = "大元联军", name = "箭塔", score = 200 }, 
                                        { typeid = 9737, x = 195, z = 120, guid = 129747, base_ai = 3, aiscript = -1, campid = 6, faceDir = 270, title = "大元联军", name = "箭塔", score = 200 }, 
}
-- RD_GUILDCONTEND_KILL_LEADER         = 28        --帮会世界杯杀人计数
-- RD_GUILDCONTEND_KILL_ASSIST         = 29        --帮会世界杯采集计数
-- RD_GUILDCONTEND_KILL_FAMILY         = 30        --帮会世界杯占领奇迹计数
-- RD_GUILDCONTEND_KILL_GOLD           = 31        --帮会世界杯占领军旗计数
-- RD_GUILDCONTEND_KILL_OTHER          = 32        --帮会世界杯摧毁箭塔计数
-- RD_GUILDCONTEND_DIECOUNT            = 33        --帮会世界杯被杀次数
-- RD_GUILDCONTEND_SCORE               = 34        --帮会世界杯个人积分
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
-- 奖励配置表
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
-- 世界杯说明
x300615_g_DescriptionTable          = {
                                        "\t您好，我是【帮会】世界杯传送人，【帮会】世界杯开启后，您可以通过我进入【帮会】世界杯战场.", 
                                        "\t【帮会】世界杯大赛规则如下：", 
                                        "一，开启条件：如果等级排行榜第一名大于70级，则会开启【帮会】世界杯大赛，开启时间为本月或下月的第一个周日16：00-16：30。#r", 
                                        
                                        "二，大赛分组：首次开启时，取帮会实力榜前16名进行对抗，前8名为世界杯大赛A组，后8名为世界杯大赛B组。次月比赛时，A组前4名及B组前4名帮会，重新组成为A组，B组则需由其他帮会报名组成。#r", 
                                        
                                        "三，比赛时间：开启后，每月的第一个周日会进行8进4，第二个周日进行4进2，第三个周日进行第三、四名争夺战，第四个周日进行第一、二名争夺战。#r", 
                                        
                                        "四，淘汰规则：A组8进4比赛，胜者为前四名直接晋级次月参加A组比赛，排名为A组1-4名，负者降级，负者次月参赛时需要报名参加；4进2比赛，胜者争夺一、二名，负者争夺三、四名。\nB组8进4比赛，胜者直接晋级次月参加A组比赛，排名为A组5-8名，负者降级，次月参赛时需要报名参加；4进2比赛，胜者争夺B组一、二名，负者争B组夺三、四名。#r", 
                                         
                                        "五，报名规则：当月世界杯全部结束时开始报名，次月的第一个周日14：00截止报名。若报名名额已满，则按帮会实力榜由排行高的顶替排行低的，被顶替帮会，将会收到邮件通知。#r", 
                                         
                                         "\t【帮会】世界杯战场规则如下：", 
										"1、每个参赛帮会最多可以进入50人。",
                                        "2、战场采用积分制，占领苏鲁锭战旗每10秒得2分，在龙魂处夺取龙珠交给本方联军统帅每次50分，摧毁敌方箭塔得200分，夺取龙珠的玩家不可以使用技能。#r", 
                                        "3、在战场内通过采集龙谷水晶得到幽谷玄冰，交给本方联军统帅每次得1分。#r", 
                                        "4、世界杯大赛时间为30分钟，先得到2000分的一方，直接获得胜利，若其中一方在世界杯大赛场景人数为0时，则直接判负。世界杯大赛结束后，均未达到2000分，则分高者取胜，分数一样时，A组赛前排名低者胜，B组帮会积分排名低者胜。#r", 
                                        "5、战场内不能进行原地复活。", 
}
-- 关闭特效角色OBJ列表
x300615_g_ToStopEffectList          = {}
-- 每秒清除多少人的特效
x300615_g_ClearPerSecond            = 20
-- 废墟Guid
x300615_g_RuinList                  = {}

function x300615_OnMapInit( sceneId)
    x300615_g_ToStopEffectList[ sceneId] = {}
    x300615_g_Occupy[ sceneId] = 0
    x300615_g_Occupy_B[ sceneId] = 0
    x300615_g_RuinList[ sceneId] = {}
end
-- 点击NPC事件处理
function x300615_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText( sceneId, x300615_g_ScriptId, "【帮会】世界杯介绍", 1, 1)
    local state = GetWorldCupState( sceneId)

    -- print( state)
    -- AddGuildExp( sceneId, selfId, 1999999)
    if state == STATE_GUILD_WORLDCUP_PREPARE or state == STATE_GUILD_WORLDCUP_START then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "进入【帮会】世界杯", 3, 2)
    end

    --print( state)
    if state == STATE_GUILD_WORLDCUP_SIGNUP then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "【帮会】世界杯报名", 3, 3)
    end

    if state > STATE_GUILD_WORLDCUP_SIGNUP then
        AddQuestNumText( sceneId, x300615_g_ScriptId, "【帮会】世界杯查询", 3, 4)
    end
end

--点击（按钮）点击该任务后执行此脚本
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

-- 世界杯查询对阵
function x300615_Query( sceneId, selfId, targetId)
    -- 从场景数据中获取对阵信息数据
    local vsInfo = {}
    vsInfo[ 1] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS1)
    vsInfo[ 2] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS2)
    vsInfo[ 3] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS3)
    vsInfo[ 4] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS4)
    vsInfo[ 5] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS5)
    vsInfo[ 6] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS6)
    vsInfo[ 7] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS7)
    vsInfo[ 8] = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_VERSUS8)

    -- 提取对阵信息
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
                strA = strA..format( "帮会#R%s#W VS 帮会#R%s#W\n", GetGuildName( item[ 1] ), GetGuildName( item[ 2] ) )
            elseif item[ 1] ~= -1 then
                strA = strA..format( "帮会#R%s#W轮空\n", GetGuildName( item[ 1] ) )
            elseif item[ 2] ~= -1 then
                strA = strA..format( "帮会#R%s#W轮空\n", GetGuildName( item[ 2] ) )
            end
        else
            if item[ 1] ~= -1 and item[ 2] ~= -1 then
                strB = strB..format( "帮会#R%s#W VS 帮会#R%s#W\n", GetGuildName( item[ 1] ), GetGuildName( item[ 2] ) )
            elseif item[ 1] ~= -1 then
                strB = strB..format( "帮会#R%s#W轮空\n", GetGuildName( item[ 1] ) )
            elseif item[ 2] ~= -1 then
                strB = strB..format( "帮会#R%s#W轮空\n", GetGuildName( item[ 2] ) )
            end
        end
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y本周世界杯大赛对阵帮会：" )
        AddQuestText( sceneId, " " )
        if iCount > 0 then
            AddQuestText( sceneId, "A组：" )
            AddQuestText( sceneId, strA)
            AddQuestText( sceneId, "B组：" )
            AddQuestText( sceneId, strB)
        else
            AddQuestText( sceneId, "本周没有比赛。" )
        end
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- 帮会世界杯报名
function x300615_Signup( sceneId, selfId, targetId)
    -- 首先检查玩家是否在帮会中
    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strNotJoinGuild)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- 检查报名者是不是帮主
    local guildStatus = GetGuildOfficial( sceneId, selfId)
    if guildStatus ~= 5 then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strOnlyforLeader)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- 检查是否为状态状态，例如在报名时间打开NPC对话框，但点击时已经过了报名时间
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_SIGNUP then
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300615_g_Name)
            AddQuestText( sceneId, x300615_g_strSignupTimePassed)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
        return
    end

    -- 向GLServer发送报名请求
    GuildContendSignup( sceneId, selfId, targetId, guildId)
end

-- GLServer返回玩家请求
function x300615_OnReply( sceneId, selfId, targetId, ReplyCode)
    local strInfo = ""
    if ReplyCode == GCR_SIGNUP_SUCCESS then
        strInfo = "\t报名成功。"
    elseif ReplyCode == GCR_SIGNUP_HASSIGNEDUP then
        strInfo = "\t你的帮会已经报过名了！"
    elseif ReplyCode == GCR_SIGNUP_STRENGTHNOTENOUGH then
        strInfo = "\t你的帮会的帮会实力榜上的排名过低，报名失败！"
    elseif ReplyCode == GCR_SIGNUP_NOTEXIST then
        strInfo = "\t你的帮会已经解散了！"
    elseif ReplyCode == GCR_WASHOUT then
        strInfo = "\t你所在帮会已被淘汰了！"
    elseif ReplyCode == GCR_NOTPATICIPATE then
        strInfo = "\t你所在帮会没有报名参加本届的【帮会】世界杯！"
    elseif ReplyCode == GCR_INHIGHGROUP then
        strInfo = "\t你的帮会已经进入世界杯决赛圈，不能报名参加预选赛！"
    elseif ReplyCode == GCR_NOMATCHTOJOIN then
        strInfo = "\t很抱歉，您所在的帮会不在赛程内，没有可参加的比赛。"
    end

    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300615_g_Name)
        AddQuestText( sceneId, strInfo)
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- 显示进入帮会世界杯确认窗口
function x300615_ShowGuildContendInfo( sceneId, selfId, targetId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300615_g_Name)
        AddQuestText( sceneId, "\t【帮会】世界杯已经开始，你确认要进入战场么？" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x300615_g_ScriptId, -1)
end

-- 判断场景是否是帮会世界杯场景
function x300615_IsGuildContendScene( sceneId)
    -- 场景类型（参考scenedefines.tab）非PVP战场（2）不处理
    local sceneType = GetSceneType( sceneId)
    if sceneType ~= 2 then
        return 0
    end

    -- 场景名非帮会世界杯场景名不处理
    if GetBattleSceneName( sceneId) ~= x300615_g_SceneName then
        return 0
    end

    return 1
end

-- 更新头顶文字
function x300615_UpdateTitle( sceneId, selfId, title)
    AwardTitle( sceneId, selfId, title)
end

-- 清除头顶称号
function x300615_ClearTitle( sceneId, selfId, title)
    if IsHaveTitle( sceneId, selfId, title) == 1 then
        DeleteTitle( sceneId, selfId, title)
    end
end

-- 场景状态变化，由程序调用
function x300615_OnChangeState( sceneId, stateId, turnNumber, guildCount)
    local sceneType = GetSceneType( sceneId)

    if sceneType == 0 then --场景类型是普通场景
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
    elseif sceneType == 2 then --场景类型是帮会世界杯场景
        if x300615_IsGuildContendScene( sceneId) == 0 then
            -- 如果不是帮会世界杯场景
            return
        end

        -- 状态变化才更新
        if GetWorldCupState( sceneId) == stateId then
            return
        else
            SetWorldCupState( sceneId, stateId)
        end

        if stateId == STATE_GUILD_WORLDCUP_PREPARE then
            -- 清除场景参数保存的对阵双方帮会ID。
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, 0)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, 0)

            x300615_InitBattleField( sceneId)

            -- 帮会世界杯场景向GLServer注册可用。
            GuildContendAskInit( sceneId)
        elseif stateId == STATE_GUILD_WORLDCUP_START then
            -- 比赛开始
            x300615_OnBattleBegin( sceneId)
        elseif stateId == STATE_GUILD_WORLDCUP_END then
            -- 比赛结束
            x300615_OnBattleEnd( sceneId)
        end
    end
end

-- 初始化战场，创建箭塔
function x300615_InitBattleField( sceneId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- 摧毁箭塔和废墟，如果有的话
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

    -- 清除废墟GUID
    x300615_g_RuinList[ sceneId] = {}

    -- 创建箭塔
    for i, item in x300615_g_HideTowerTable do
        CreateMonster( sceneId, item.typeid, item.x, item.z, item.base_ai, item.aiscript, x300615_g_ScriptId, item.guid, item.campid, 3600000, item.faceDir, item.name, item.title)
    end
    for i, item in x300615_g_ShowTowerTable do
        CreateMonster( sceneId, item.typeid, item.x, item.z, item.base_ai, item.aiscript, x300615_g_ScriptId, item.guid, item.campid, 3600000, item.faceDir, item.name, item.title)
    end

    -- 设置阻挡
    AddSceneTempImpassable( sceneId, 186, 116, 194, 130)
    AddSceneTempImpassable( sceneId,  56, 118,  60, 134)
end

-- 注册场景成功，GLServer返回交战双方帮会ID
function x300615_RegisterScene( sceneId, GuildIdA, GuildIdB)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, GuildIdA)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, GuildIdB)
end

-- GLServer通知比赛开始
function x300615_OnBattleBegin( sceneId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local GuildIdA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local GuildIdB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)

    if GuildIdA == -1 and GuildIdB == -1 then
        return
    end

    -- 如果轮空直接晋级或此场景本轮轮空
    if GuildIdA == -1 and GuildIdB ~= -1 then
        local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
        -- 更新获胜场次计数
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        -- 更新轮次信息
        UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 1, 0, groupType)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
        return
    end
    if GuildIdB == -1 and GuildIdA ~= -1 then
        local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
        -- 更新获胜场次计数
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        -- 更新轮次信息
        UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 1, 0, groupType)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
        return
    end

    LuaThisScenceM2Wrold( sceneId, "【帮会】世界杯开始！", 5, 1)

    SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", 126, 124, -1)

    -- 删除阻挡
    DelSceneTempImpassable( sceneId, 186, 116, 194, 130)
    DelSceneTempImpassable( sceneId,  56, 118,  60, 134)

    -- 初始化双方比赛得分
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, 0)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, 0)
    -- 清除战旗占领标记
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
    -- 战旗占领计数器清零
    x300615_g_Occupy[ sceneId] = 0
    x300615_g_Occupy_B[ sceneId] = 0
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A, -1)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B, -1)

    -- 清除所有人的战斗数据
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

        -- 开战时才设置为敌对阵营
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
            -- 如果不是属于该战场的帮会就传送出去
            x300615_OnPlayerAskLeave( sceneId, objId)
        end
        -- 把Obj保存到全局列表
        x300615_g_ToStopEffectList[ sceneId][ getn( x300615_g_ToStopEffectList[ sceneId] ) + 1] = objId
		-- CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, objId, 30)
		-- CallScriptFunction( UTILITY_SCRIPT, "StopEffect", sceneId, objId, 31)
    end
end

-- GLServer通知比赛结束
function x300615_OnBattleEnd( sceneId)
    -- 取得对战双方帮会名及ID
    local GuildIdA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local GuildIdB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local turnNumber = GetWorldCupSceneData_Param( sceneId, LD_GUILD_CONTEND_TURNNUMBER)
    local groupType = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_GROUPTYPE)
    local matchFlag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAG)
    local index = 1

    -- 找到比赛奖励表索引
    for i, item in x300615_g_RewardTable do
        if turnNumber == item.turnNumber and groupType == item.groupType then
            index = i
            break
        end
    end

    -- 此场景没有进行比赛
    if GuildIdA == -1 and GuildIdB == -1 then
        return
    end

    -- 轮空帮直接晋级
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

    -- 统计比赛结果 --
    -- 获得剩余比赛时间
    local nTime = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_COUNT_ITME)

    -- 得到获胜方，0为A方获胜，1为B方获胜，没有平局
    local Winner = 0
    if scoreA == scoreB then
        -- 如果积分相同，按帮战积分成绩判定胜者
        local gbA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GB_SCORE)
        local gbB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GB_SCORE)
        if gbA > gbB then
            Winner = 1
        elseif gbA < gbB then
            Winner = 0
        else
            -- 如果帮战积分相同，随机选一个获胜者
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

    -- 广播帮战基本数据给所有战场中的玩家
    GuildContendSendBaseInfo( sceneId, TitleBlue, TitleRed, Winner, nTime)
    -- 广播每个参战玩家的比赛数据
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

            -- 恢复阵营
            SetCurCamp( sceneId, objId, 4)

            -- 如果死了先复活，否则会卡死在统计结果界面
            if IsPlayerMutexState( sceneId, objId, PLAYER_STATE_DIE) > 0 then
                RelivePlayerNM( sceneId, objId, 2)
            end

            -- 检测胜负
            local isWin = 1
            local oppoGuildName = ""
            if Winner == 0 then -- A帮胜
                if nGuildId == GuildIdA then
                    isWin = 1
                    nGuildFlag = 0
                    oppoGuildName = GetGuildName( GuildIdB)
                else
                    isWin = 0
                    nGuildFlag = 1
                    oppoGuildName = GetGuildName( GuildIdA)
                end
            else -- B帮胜
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
            -- 根据胜负发送到客户端
            if isWin == 0 then
                -- 失利
                local level = GetLevel( sceneId, objId)
                local name = GetName( sceneId, objId)

                local strInfo = "比赛结束，很遗憾你所在的帮会被淘汰！"
                if groupType == 0 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯C组1/8决赛你们的帮会被#R"..oppoGuildName.."#cffcf00淘汰出局。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯C组1/4决赛你们的帮会被#R"..oppoGuildName.."#cffcf00淘汰出局。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯C组半决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，失去晋级决赛资格，下轮将参加争夺三四名的比赛。"
                    elseif turnNumber == 3 then
                        if matchFlag == 1 then
                            strInfo = "本届【帮会】世界杯C组三四名决赛中你们的帮会被#R"..oppoGuildName.."#cffcf00击败，以C组第四名晋级B组。"
                        else
                            strInfo = "本届【帮会】世界杯C组决赛中你们的帮会被#R"..oppoGuildName.."#cffcf00击败，以C组亚军的身份晋级B组。"
                        end
                    end
                elseif groupType == 1 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯B组1/4决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，失去晋级A组资格。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯B组半决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，失去晋级决赛资格，下轮将参加争夺三四名的比赛。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯B组三四名决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，获得B组第四名。"
                    elseif turnNumber == 3 then
                        strInfo = "【帮会】世界杯B组决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，获得B组亚军。"
                    end
                elseif groupType == 2 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯A组1/4决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，从A组降级到B组。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯A组半决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，失去晋级决赛资格，下轮将参加争夺三四名的比赛。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯A组三四名决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，获得A组第四名。"
                    elseif turnNumber == 3 then
                        strInfo = "【帮会】世界杯A组决赛你们的帮会被#R"..oppoGuildName.."#cffcf00击败，获得A组亚军。"
                    end
                end
                LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)

                --发送Player相关信息
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
                Msg2Player( sceneId, objId, format( "获得#R#{_MONEY%d}#cffcc00帮会金钱", x300615_g_RewardTable[ index].rewards[ 2].gmoney), 8, 2)
                Msg2Player( sceneId, objId, format( "获得#R%d#cffcc00帮会使命", x300615_g_RewardTable[ index].rewards[ 2].gshiming), 8, 2)
                Msg2Player( sceneId, objId, format( "获得#R%d点#cffcc00帮会经验", x300615_g_RewardTable[ index].rewards[ 2].gxp), 8, 2)
                if firstLose == 0 then
                    -- 一次性给失利帮会奖励
                    firstLose = 1
                    AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gmoney)
                    AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gshiming)
                    AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 2].gxp)
                end
            else
                -- 获胜
                local level = GetLevel( sceneId, objId)
                local name = GetName( sceneId, objId)

                local strInfo = "你所在的帮会成功晋级！"
                if groupType == 0 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯C组1/8决赛你们的帮会淘汰#R"..oppoGuildName.."#cffcf00，成功晋级8强。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯C组1/4决赛你们的帮会淘汰#R"..oppoGuildName.."#cffcf00，成功晋级4强，并在下届升级到B组。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯C组半决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，成功晋级决赛，下轮将争夺C组冠军。"
                    elseif turnNumber == 3 then
                        if matchFlag == 1 then
                            strInfo = "本届【帮会】世界杯C组三四名决赛中你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得C组季军。"
                        else
                            strInfo = "本届【帮会】世界杯C组决赛中你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得C组冠军！"
                        end
                    end
                elseif groupType == 1 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯B组1/4决赛你们的帮会淘汰#R"..oppoGuildName.."#cffcf00，成功晋级4强，并在下届升级到A组。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯B组半决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，成功晋级B组决赛。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯B组三四名决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得B组季军。"
                    elseif turnNumber == 3 then
                        strInfo = "【帮会】世界杯B组决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得B组冠军！"
                    end
                elseif groupType == 2 then
                    if turnNumber == 0 then
                        strInfo = "【帮会】世界杯A组1/4决赛你们的帮会淘汰#R"..oppoGuildName.."#cffcf00，成功晋级4强。"
                    elseif turnNumber == 1 then
                        strInfo = "【帮会】世界杯A组半决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，成功晋级决赛，两轮后将争夺本届【帮会】世界杯桂冠。"
                    elseif turnNumber == 2 then
                        strInfo = "【帮会】世界杯A组三四名决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得A组季军。"
                    elseif turnNumber == 3 then
                        strInfo = "【帮会】世界杯A组决赛你们的帮会击败#R"..oppoGuildName.."#cffcf00，获得A组冠军！"
                    end
                end
                LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)

                --发送Player相关信息
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
                Msg2Player( sceneId, objId, format( "获得#R#{_MONEY%d}#cffcc00帮会金钱", x300615_g_RewardTable[ index].rewards[ 1].gmoney), 8, 2)
                Msg2Player( sceneId, objId, format( "获得#R%d#cffcc00帮会使命", x300615_g_RewardTable[ index].rewards[ 1].gshiming), 8, 2)
                Msg2Player( sceneId, objId, format( "获得#R%d点#cffcc00帮会经验", x300615_g_RewardTable[ index].rewards[ 1].gxp), 8, 2)
                if firstWin == 0 then
                    -- 一次性给获胜帮会奖励
                    firstWin = 1
                    AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gmoney)
                    AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gshiming)
                    AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gxp)
                end
            end
        end
    end

    -- 按积分排序
    sort( allResult, function ( a, b) return a.score > b.score end)
    -- 客户端显示前20名
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

    -- 通知GLServer，更新帮会世界杯胜负计数
    if Winner == 0 then
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
        UpdateGuildContendTurnsInfo( sceneId, GuildIdA, 0, 0, groupType)
    else
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_LOSE_COUNT, 1, 1)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_WIN_COUNT,  1, 1)
        UpdateGuildContendTurnsInfo( sceneId, GuildIdB, 0, 0, groupType)
    end

    -- 更新场景状态
    SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
end

-- 复活
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

-- GLServer发来的战场时间同步消息。iTime为战斗已进行时间。
function x300615_OnSyncGuildBattleTime( sceneId, iTime)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- print( sceneId.."同步时间："..iTime)

    -- 保存剩余比赛时间
    local remainTime = x300615_g_FightTime - iTime
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_COUNT_ITME, remainTime)

    -- 给当前场景中的所有玩家同步战场时间
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

-- 程序调用通知玩家加入帮会世界杯
-- turnNumber 帮会世界杯轮次号（0——3）
-- groupType 组别类型id
-- oppoGuildId 本轮对手帮会ID
function x300615_OnInformJoin( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildId)
    local strInfo = "参加【帮会】世界杯。"
    local oppoGuildName = GetGuildName( oppoGuildId)

    -- 状态检查
    for i, item in x300615_g_MutexTable do
        if IsPlayerMutexState( sceneId, selfId, item) > 0 then
            return
        end
    end

    -- 夺旗时不能进入
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
            strInfo = "准备参加【帮会】世界杯C组1/8决赛。"
        elseif turnNumber == 1 then
            strInfo = "准备参加【帮会】世界杯C组1/4决赛。"
        elseif turnNumber == 2 then
            strInfo = "准备参加【帮会】世界杯C组半决赛。"
        elseif turnNumber == 3 then
            if matchFlag == 1 then
                strInfo = "准备参加【帮会】世界杯C组三四名决赛。"
            else
                strInfo = "准备参加【帮会】世界杯C组决赛。"
            end
        end
    elseif groupType == 1 then
        if turnNumber == 0 then
            strInfo = "准备参加【帮会】世界杯B组1/4决赛。"
        elseif turnNumber == 1 then
            strInfo = "准备参加【帮会】世界杯B组半决赛。"
        elseif turnNumber == 2 then
            strInfo = "准备参加【帮会】世界杯B组三四名决赛。"
        elseif turnNumber == 3 then
            strInfo = "准备参加【帮会】世界杯B组决赛。"
        end
    elseif groupType == 2 then
        if turnNumber == 0 then
            strInfo = "准备参加【帮会】世界杯A组1/4决赛。"
        elseif turnNumber == 1 then
            strInfo = "准备参加【帮会】世界杯A组半决赛。"
        elseif turnNumber == 2 then
            strInfo = "准备参加【帮会】世界杯A组三四名决赛。"
        elseif turnNumber == 3 then
            strInfo = "准备参加【帮会】世界杯A组决赛。"
        end
    end
    Msg2Player( sceneId, selfId, strInfo, 8, 2)

    local strMsg = format( "WCL: Inform player %s enter world cup. SceneID=%d, GroupID=%d, OpponentGuild=%d", GetName( sceneId, selfId), sceneId, groupType, oppoGuildId)
    WriteLog( 1, strMsg)

    if oppoGuildId ~= -1 then
        AskPlayerToJoinWorldCup( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildName)
    end
end

-- 通知玩家直接晋级下一轮
function x300615_OnPromotion( sceneId, selfId, groupType, turnNumber, matchFlag)
    local strInfo = "直接晋级。"

    if groupType == 0 then
        if turnNumber == 0 then
            strInfo = "【帮会】世界杯C组1/8决赛你们的帮会轮空，直接进入8强。"
        elseif turnNumber == 1 then
            strInfo = "【帮会】世界杯C组1/4决赛你们的帮会轮空，直接进入4强。"
        elseif turnNumber == 2 then
            strInfo = "【帮会】世界杯C组半决赛你们的帮会轮空，直接进入决赛。"
        elseif turnNumber == 3 then
            if matchFlag == 1 then
                strInfo = "【帮会】世界杯C组三四名决赛中你们的帮会轮空，直接获得C组季军。"
            else
                strInfo = "【帮会】世界杯C组决赛中你们的帮会轮空，直接获得C组冠军。"
            end
        end
    elseif groupType == 1 then
        if turnNumber == 0 then
            strInfo = "【帮会】世界杯B组1/4决赛你们的帮会轮空，直接进入B组4强。"
        elseif turnNumber == 1 then
            strInfo = "【帮会】世界杯B组半决赛你们的帮会轮空，直接进入决赛。"
        elseif turnNumber == 2 then
            strInfo = "【帮会】世界杯B组三四名决赛你们的帮会轮空，直接成为B组季军。"
        elseif turnNumber == 3 then
            strInfo = "【帮会】世界杯B组决赛你们的帮会轮空，直接成为B组冠军。"
        end
    elseif groupType == 2 then
        if turnNumber == 0 then
            strInfo = "【帮会】世界杯A组1/4决赛你们的帮会轮空，直接进入4强。"
        elseif turnNumber == 1 then
            strInfo = "【帮会】世界杯A组半决赛你们的帮会轮空，直接进入决赛。"
        elseif turnNumber == 2 then
            strInfo = "【帮会】世界杯A组三四名决赛你们的帮会轮空，直接成为A组季军。"
        elseif turnNumber == 3 then
            strInfo = "【帮会】世界杯A组决赛你们的帮会轮空，直接成为A组冠军。"
        end
    end
    Msg2Player( sceneId, selfId, strInfo, 8, 2)

    local strMsg = format( "WCL: Inform player %s promotion. SceneID=%d, GroupID=%d", GetName( sceneId, selfId), sceneId, groupType)
    WriteLog( 1, strMsg)
end

-- 客户端请求离开战场
function x300615_OnPlayerAskLeave( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    RestoreHp( sceneId, selfId, 100)
    RelivePlayerNM( sceneId, selfId, 2)
    --清除死亡状态(如果死了的话)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE, 0)

    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7801)
        -- 还原战旗采集点
        SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
        SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", 126, 124, -1)
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7802) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7802)
    end

    -- 恢复阵营
    local nCountryId = GetCurCountry( sceneId, selfId)
    SetCurCamp( sceneId, selfId, nCountryId)

    -- 清除奇迹Buff，如果有的话
    -- if IsHaveSpecificImpact( sceneId, selfId, x300615_g_MiracleId) == 1 then
        -- CancelSpecificImpact( sceneId, selfId, x300615_g_MiracleId)
    -- end

    -- 背包里如果有水晶就清除
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    -- 传回进入战场前的地方
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 and x ~= 0 and z ~= 0 then
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
        NewWorld( sceneId, selfId, nBakSceneId, x, z, x300615_g_ScriptId)
        return
    end

    --传回进入NPC身边
    local nCountry = GetCurCountry( sceneId, selfId)
    local nDestSceneId = 0
    if nCountry == 0 then
        --楼兰
        nDestSceneId = 50
    elseif nCountry == 1 then
        --天山
        nDestSceneId = 150
    elseif nCountry == 2 then
        --昆仑
        nDestSceneId = 250
    elseif nCountry == 3 then
        --敦煌
        nDestSceneId = 350
    end

    local nOffsetX = random( 8, 12)
    local nOffsetZ = random( 8, 12)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
    NewWorld( sceneId, selfId, nDestSceneId, x300615_g_PosX + nOffsetX, x300615_g_PosZ + nOffsetZ, 300615)
end

--点击（确定）
function x300615_ProcAcceptCheck( sceneId, selfId, targetId)
    x300615_OnPlayerAskEnter( sceneId, selfId, targetId)
end

function x300615_OnPlayerAskEnter( sceneId, selfId, targetId)
    local nGuildId = GetGuildID( sceneId, selfId)
    if nGuildId < 0 or nGuildId > 1024 then
        if targetId ~= 0 then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y"..x300615_g_Name)
                AddQuestText( sceneId, "你尚未加入任何帮会！不能进入战场。" )
            EndQuestEvent()
            DispatchQuestEventList( sceneId, selfId, targetId)
            return
        end
    end

    -- 状态检查
    for i, item in x300615_g_MutexTable do
        if IsPlayerMutexState( sceneId, selfId, item) > 0 then
            Msg2Player( sceneId, selfId, "你现在不能进入世界杯战场", 8, 3)
            return
        end
    end

    -- 夺旗时不能进入
    if IsHaveSpecificImpact( sceneId, selfId, 7702) == 1 then
        Msg2Player( sceneId, selfId, "异国夺旗时不能进入世界杯战场", 8, 3)
        return
    end

    if GetPKMode( sceneId, selfId) ~= 0 then
        Msg2Player( sceneId, selfId, "处于PK模式不能进入世界杯战场", 8, 3)
        return
    end

    if IsHideName( sceneId, selfId) == 1 then
        Msg2Player( sceneId, selfId, "蒙面状态不能进入世界杯战场", 8, 3)
        return
    end

    GuildContendAskEnter( sceneId, selfId)
end

-- 所在帮会没有入选本届的帮会世界杯
function x300615_OnRejectEnter( sceneId, selfId)
    Msg2Player( sceneId, selfId, "你所在的帮会没有入选本届的【帮会】世界杯！不能进入战场。", 8, 2)
end

-- 请求进入战场的角色尚未加入任何帮会
function x300615_OnNotBelongGuild( sceneId, selfId)
    Msg2Player( sceneId, selfId, "你尚未加入任何帮会！不能进入战场。", 8, 2)
end

-- 请求进入战场的角色所在的帮会本轮比赛轮空
function x300615_OnNotOpponent( sceneId, selfId)
    Msg2Player( sceneId, selfId, "你所在的帮会本轮世界杯轮空，不能进入战场！", 8, 2)
end

-- 根据场景ID获得帮会世界杯脚本ID，如果是返回脚本ID，否则返回0
function x300615_GetGuildContendScript( sceneId)
    local sceneName = GetBattleSceneName( sceneId)
    for i, item in x300615_g_SceneScript do
        if item.Name == sceneName then
            return item.ScriptID
        end
    end

    return 0
end

-- 玩家进入帮会世界杯战场
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

    --对玩家原先的场景进行备份
    local scenePre = GetPlayerRuntimeData( sceneId,selfId, RD_HUMAN_SCENE_PRE)
    if scenePre >= 0 then
        local CurX = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo( sceneId, selfId, scenePre, CurX, CurZ)

        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_SCENE_PRE, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSX_PRE, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_POSZ_PRE, 0)
    end

    -- 阵营处理
    if GetWorldCupState( sceneId) == STATE_GUILD_WORLDCUP_START then
        local guildId = GetGuildID( sceneId, selfId)
        if guildId == nGuildA then
            SetCurCamp( sceneId, selfId, 5)
        elseif guildId == nGuildB then
            SetCurCamp( sceneId, selfId, 6)
        else
            -- 如果不是属于该战场的帮会就传送出去
            x300615_OnPlayerAskLeave( sceneId, selfId)
        end
    else
        -- 开战前设置统一阵营，避免提前PK
        SetCurCamp( sceneId, selfId, 4)
        -- 开特效
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
        --清除死亡状态(如果死了的话)
        RelivePlayerNM( sceneId, selfId, 2)
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE, 0)
    end

    -- 恢复阵营
    local nCountryId = GetCurCountry( sceneId, selfId)
    SetCurCamp( sceneId, selfId, nCountryId)

    -- 清除奇迹Buff，如果有的话
    -- if IsHaveSpecificImpact( sceneId, selfId, x300615_g_MiracleId) == 1 then
        -- CancelSpecificImpact( sceneId, selfId, x300615_g_MiracleId)
    -- end

    -- 背包里如果有水晶就清除
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    -- 传回进入战场前的地方
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
        NewWorld( sceneId, selfId, nBakSceneId, x, z, x300615_g_ScriptId)
        return
    end

    --传回进入NPC身边
    local nCountry = GetCurCountry( sceneId, selfId)
    local nDestSceneId = 0
    if nCountry == 0 then
        --楼兰
        nDestSceneId = 50
    elseif nCountry == 1 then
        --天山
        nDestSceneId = 150
    elseif nCountry == 2 then
        --昆仑
        nDestSceneId = 250
    elseif nCountry == 3 then
        --敦煌
        nDestSceneId = 350
    end

    local nOffsetX = random( 8, 12)
    local nOffsetZ = random( 8, 12)
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_GUILDBATTLEFIELDSCENE, 0)
    NewWorld( sceneId, selfId, nDestSceneId, x300615_g_PosX + nOffsetX, x300615_g_PosZ + nOffsetZ, 300615)
end

-- 处理帮会成员之间PK结果，根据被杀者身份记录积分
-- selfId：被杀者的ObjId
-- killerId：杀人者的ObjId
function x300615_OnPlayerDie( sceneId, selfId, killerId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- 背包里如果有水晶就清除
    local iCount = GetItemCountInBag( sceneId, selfId, x300615_g_ItemId)
    if iCount > 0 then
        DelItem( sceneId, selfId, x300615_g_ItemId, iCount)
    end

    local ownerId = GetOwnerID( sceneId, killerId)
    local muderer = killerId
    if ownerId ~= -1 then
        -- 狗或者鹰杀死敌人
        SetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_KILL_LEADER, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER) + 1)
        muderer = ownerId
    else
        SetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_KILL_LEADER) + 1)
    end

    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        -- 身上带着战旗
        CancelSpecificImpact( sceneId, selfId, 7801)
        CancelSpecificImpact( sceneId, selfId, 7802)
        local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        -- 杀人者在线并且是玩家,并且没有死亡,并且在30码内,则认为有效,否则掉地上
        if IsPlayerStateNormal( sceneId, muderer) == 1 and 
            IsPlayerMutexState( sceneId, muderer, PLAYER_STATE_DIE) ~= 1 and 
            GetDist( sceneId, selfId, muderer, 30) <= 30 then
            ReCallHorse( sceneId, muderer)
            SendSpecificImpactToUnit( sceneId, muderer, muderer, muderer, 7801, 0)
            SendSpecificImpactToUnit( sceneId, muderer, muderer, muderer, 7802, 0)
            local x,y = GetWorldPos( sceneId, muderer)
            SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", x, y, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, muderer)
            SetPlayerRuntimeData( sceneId, muderer, RD_DANCERY_BODYID, growPointid)
        else
            -- 原地掉落，就是在被杀处设置采集点
            local x,y = GetWorldPos( sceneId, selfId)
            SetGrowPointPos( sceneId, growPointid, x + 1, y + 1)
            SetGrowPointIntervalContainer( sceneId, growPointid, 1000)
            SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", x + 1, y + 1, -1)
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -2)
        end
    end

    --记录被杀次数
    SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_DIECOUNT, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_DIECOUNT) + 1)
end

-- 玩家上线直接进入帮会世界杯场景处理
function x300615_OnPlayerNewConnectEnter( sceneId, selfId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        x300615_OnPlayerAskLeave( sceneId, selfId)
    end
end

-- 场景定时器
function x300615_ProcTiming( sceneId, nowTime)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    local state = GetWorldCupState( sceneId)
    -- 在比赛开始后定时器检查站场为空并开始踢人的同时可能会有玩家进入战场，需要再次踢出
    if state == STATE_GUILD_WORLDCUP_FINISHED then
        local nHumanCount = GetScenePlayerCount( sceneId)
        for i = 0, nHumanCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if objId >= 0 and IsPlayerStateNormal( sceneId, objId) == 1 then
                -- 恢复阵营
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

    -- 如果比赛提前结束
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

    -- 更新积分到客户端
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

    -- 检查战旗所有人是否有效
	local capflag = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY)
	if capflag > -1 then
		if IsObjValid( sceneId, capflag) == 0 or IsPlayerStateNormal( sceneId, capflag) ~= 1 or IsPlayerMutexState( sceneId, capflag, PLAYER_STATE_DIE) == 1 then
			SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
			SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
			SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
            SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", 126, 124, -1)
        else
            local x, z = GetWorldPos( sceneId, capflag)
            SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", x, z, -1)
		end
    elseif capflag ~= -2 then
        -- 扛旗者离开战场
        SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", 126, 124, -1)
	end

    -- 统计双方人数
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
    -- 如果有一个帮会的总人数大于指定值就把做标记的T出战场
    if CountA > x300615_g_MaxCountInBattleScene or CountB > x300615_g_MaxCountInBattleScene then
        for i = 0, nHumanCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if GetPlayerRuntimeData( sceneId, objId, RD_COLLECT_HORSE_HIGH) == 1 then
                Msg2Player( sceneId, objId, format( "你所在帮会进入战场人数已达上限%d人，不能再进人了。", x300615_g_MaxCountInBattleScene), 8, 2)
                x300615_OnPlayerLeave( sceneId, objId)
            end
        end
    end

    -- 如果有一方在战场人数为0立刻判对手获胜
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

    -- 两个帮会都没人在战场，随机判定胜负
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

        -- 更新场景状态
        SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
        SetGuildQuestData( sceneId, GuildIdA, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        SetGuildQuestData( sceneId, GuildIdB, GD_GUILD_INDEX_CONTEND_STATE, STATE_GUILD_WORLDCUP_END, 0)
        -- 清除对阵双方帮会ID，避免正常结束后会再次更新轮次
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)

        return
    end

    -- 如果有任意一方积分达到x300615_g_TotalScore立即判定胜利
    if state == STATE_GUILD_WORLDCUP_START and scoreA >= x300615_g_TotalScore or scoreB >= x300615_g_TotalScore then
        x300615_OnBattleEnd( sceneId)
        -- 清除对阵双方帮会ID，避免正常结束后会再次更新轮次
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
    -- 超过战场人数上限在人物身上标记，在定时器里T出
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

    -- 更新场景状态
    SetWorldCupState( sceneId, STATE_GUILD_WORLDCUP_END)
    -- 清除对阵双方帮会ID，否则正常结束后会再次更新轮次
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD, -1)
    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD, -1)
end

-- 对手全部离开战场或根本没参加，直接获胜。把获胜帮会所有成员拉出战场
function x300615_PerfectVictory( sceneId, turnNumber, groupType, matchFlag, oppoGuildName)
    local nHumanCount = GetScenePlayerCount( sceneId)
    local strOppoName = "对手"
    if oppoGuildName ~= "" then
        strOppoName = oppoGuildName
    end

    -- 找到比赛奖励表索引
    local index = 1
    for i, item in x300615_g_RewardTable do
        if turnNumber == item.turnNumber and groupType == item.groupType then
            index = i
            break
        end
    end

    local firstWin = 0
    -- 把所有帮会成员拉出战场
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        local name = GetName( sceneId, objId)
        local strInfo = "与你所在帮会对阵的帮会的成员都不在战场，你们直接获得胜利。"
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "【帮会】世界杯C组1/8决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级C组8强，下轮将进行升级B组的争夺。"
            elseif turnNumber == 1 then
                strInfo = "【帮会】世界杯C组1/4决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级C组4强，并在下届升级到B组。"
            elseif turnNumber == 2 then
                strInfo = "【帮会】世界杯C组半决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级决赛，下轮争夺C组冠军。"
            elseif turnNumber == 3 then
                if matchFlag == 1 then
                    strInfo = "【帮会】世界杯C组三四名决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为C组季军。"
                else
                    strInfo = "【帮会】世界杯C组决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为C组冠军。"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "【帮会】世界杯B组1/4决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级B组4强。"
            elseif turnNumber == 1 then
                strInfo = "【帮会】世界杯B组半决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级决赛，两轮后争夺B组冠军。"
            elseif turnNumber == 2 then
                strInfo = "【帮会】世界杯B组三四名决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为B组季军。"
            elseif turnNumber == 3 then
                strInfo = "【帮会】世界杯B组决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为B组冠军。"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "【帮会】世界杯A组1/4决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级4强。"
            elseif turnNumber == 1 then
                strInfo = "【帮会】世界杯A组半决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成功晋级决赛，两轮后争夺A组冠军。"
            elseif turnNumber == 2 then
                strInfo = "【帮会】世界杯A组三四名决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为A组季军。"
            elseif turnNumber == 3 then
                strInfo = "【帮会】世界杯A组决赛你们帮会的对手#R"..strOppoName.."#cffcf00的成员都不在战场，你们直接获得胜利，成为A组冠军。"
            end
        end
        LuaScenceM2Player( sceneId, objId, strInfo, name, 2, 1)
        Msg2Player( sceneId, objId, format( "获得#R#{_MONEY%d}#cffcc00帮会金钱", x300615_g_RewardTable[ index].rewards[ 1].gmoney), 8, 2)
        Msg2Player( sceneId, objId, format( "获得#R%d#cffcc00帮会使命", x300615_g_RewardTable[ index].rewards[ 1].gshiming), 8, 2)
        Msg2Player( sceneId, objId, format( "获得#R%d点#cffcc00帮会经验", x300615_g_RewardTable[ index].rewards[ 1].gxp), 8, 2)
        if firstWin == 0 then
            firstWin = 1
            AddGuildMoney( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gmoney)
            AddGuildShiMing( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gshiming)
            AddGuildExp( sceneId, objId, x300615_g_RewardTable[ index].rewards[ 1].gxp)
        end
        -- 恢复阵营
        local nCountryId = GetCurCountry( sceneId, objId)
        SetCurCamp( sceneId, objId, nCountryId)
        x300615_OnPlayerAskLeave( sceneId, objId)
    end
end

-- 比赛奖励
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
        strgroup = "B组"
    elseif groupType == 2 then
        strgroup = "A组"
    end
    if turnNumber == 0 then
        strtip = "四分之一决赛"
    elseif turnNumber == 1 then
        strtip = "半决赛"
    elseif turnNumber == 2 then
        strtip = "三四名决赛"
    elseif turnNumber == 3 then
        strtip = "决赛"
    end
    if result == 1 then
        strresult = "获胜"
    elseif result == 2 then
        strresult = "失利"
    end

    Msg2Player( sceneId, selfId, format( "【帮会】世界杯%s%s，你所在帮会%s。", strgroup, strtip, strresult), 8, 2)
    local xp = x300615_g_RewardTable[ index].rewards[ result].xpCoff * GetLevel( sceneId, selfId)
    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验。", xp), 8, 2)
    local bangGong = x300615_g_RewardTable[ index].rewards[ result].bangGong
    AddGuildUserPoint( sceneId, selfId, bangGong)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点帮贡。", bangGong), 8, 2)
end

-- 打开前函数开始
function x300615_OnOpenItemBox( sceneId, selfId, targetId, GrowpointId, ItemIndex)
    -- 比赛没开始不允许采集操作
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        Msg2Player( sceneId, selfId, "比赛还没开始，不能进行此操作", 8, 3)
        return 1
    end

    if GrowpointId == x300615_GT_ArmyFlag then
        -- 是否已经被本方占领
    elseif GrowpointId == x300615_GT_Flag_A then
        if GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A) == GetGuildID( sceneId, selfId) then
            Msg2Player( sceneId, selfId, "已经被你所在的帮会占领", 8, 3)
            return 1
        end
    elseif GrowpointId == x300615_GT_Flag_B then
        if GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B) == GetGuildID( sceneId, selfId) then
            Msg2Player( sceneId, selfId, "已经被你所在的帮会占领", 8, 3)
            return 1
        end
    elseif GrowpointId == x300615_GT_Miracle then
        -- 检查背包空间
		if GetBagSpace( sceneId, selfId) <= 0 then
			Msg2Player( sceneId, selfId, "物品栏已满，不能进行采集", 8, 3)
            return 1
		end
        -- 背包里是否已经有幽谷玄冰了
        if GetItemCountInBag( sceneId, selfId, x300615_g_ItemId) > 0 then
            Msg2Player( sceneId, selfId, "不能重复采集@item_"..x300615_g_ItemId, 8, 3)
            return 1
        end
    end

    return 0
end

function x300615_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
    -- print( "进入安全区" )
    -- 检查有没有龙柱的相关Buff，有就清除，并把龙柱放回原点
    if IsHaveSpecificImpact( sceneId, selfId, 7801) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7801)
        local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        SetGrowPointPos( sceneId, x300615_GT_ArmyFlag, 126, 124)
        SetGrowPointIntervalContainer( sceneId, x300615_GT_ArmyFlag, 1000)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
        SetSceneMapDataFlag( sceneId, 1, 7, "龙珠", 126, 124, -1)
    end
    if IsHaveSpecificImpact( sceneId, selfId, 7802) == 1 then
        CancelSpecificImpact( sceneId, selfId, 7802)
    end
    
end

function x300615_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId)
    -- print( "离开安全区" )
end

-- 回收函数开始
function x300615_OnRecycle( sceneId, selfId, targetId, GrowpointId, ItemIndex)
    -- 比赛没开始不允许采集操作
    if GetWorldCupState( sceneId) ~= STATE_GUILD_WORLDCUP_START then
        return 0
    end

    -- print( "x300615_OnRecycle" )
    if GrowpointId == x300615_GT_ArmyFlag then
        --强制下马
        ReCallHorse( sceneId, selfId)
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7801,   200)    --200毫秒
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7802, 200)    --200毫秒
        -- 更新采集点重生时间
        SetGrowPointIntervalContainer( sceneId, GrowpointId, -1)
        -- 记录采集者ObjID
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, selfId)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, GrowpointId)
    elseif GrowpointId == x300615_GT_Flag_A then
        -- 更新占领标记
        local guildId = GetGuildID( sceneId, selfId)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_A, guildId)
        -- 更新个人占领计数
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD) + 1)
        -- 更新计数器
        x300615_g_Occupy[ sceneId] = 0
        LuaThisScenceM2Wrold( sceneId, format( "帮会%s占领了占领苏鲁锭战旗", GetGuildName( guildId) ), 5, 1)
    elseif GrowpointId == x300615_GT_Flag_B then
        -- 更新占领标记
        local guildId = GetGuildID( sceneId, selfId)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_CATCHFLAG_B, guildId)
        -- 更新个人占领计数
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_GOLD) + 1)
        -- 更新计数器
        x300615_g_Occupy_B[ sceneId] = 0
        LuaThisScenceM2Wrold( sceneId, format( "帮会%s占领了占领苏鲁锭战旗", GetGuildName( guildId) ), 5, 1)
    elseif GrowpointId == x300615_GT_Miracle then
        -- local guildId = GetGuildID( sceneId, selfId)
        -- -- 更新个人占领计数
        -- SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY) + 1)
        -- -- 给本帮会所有在战场的成员加Buff
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
			Msg2Player( sceneId, selfId, "物品栏已满，采集失败", 8, 3)
		end
    end

    return 1
end

-- 通知战场外所有帮会成员结果
function x300615_OnInformOutofBF( sceneId, selfId, turnNumber, groupType, matchFlag, oppoGuildId, result)
    local name = GetName( sceneId, selfId)
    local strInfo = nil
    if result == 1 then
        -- 获胜
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入C组8强。"
            elseif turnNumber == 1 then
                if matchFlag == 1 then
                    strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，在C组保级成功。"
                else
                    strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入C组4强，并在下届升级到B组。"
                end
            elseif turnNumber == 2 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入C组决赛。"
            elseif turnNumber == 3 then
                if matchFlag == 0 then
                    strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯C组冠军！"
                else
                    strInfo = "你所在帮会和对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯C组季军！"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入B组4强。"
            elseif turnNumber == 1 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入B组决赛。"
            elseif turnNumber == 2 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯B组季军！"
            elseif turnNumber == 3 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯B组冠军！"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入A组4强。"
            elseif turnNumber == 1 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，进入A组决赛。"
            elseif turnNumber == 2 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯A组季军！"
            elseif turnNumber == 3 then
                strInfo = "与你所在帮会对阵的帮会成员都不在战场，你们幸运的获得胜利，获得本届【帮会】世界杯A组冠军！"
            end
        end
    else
        -- 失利
        if groupType == 0 then
            if turnNumber == 0 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸被淘汰，没能进入C组8强。"
            elseif turnNumber == 1 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸被淘汰，没能进入C组4强。"
            elseif turnNumber == 2 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，没能进入C组决赛。"
            elseif turnNumber == 3 then
                if matchFlag == 0 then
                    strInfo = "你所在帮会的成员都不在战场，你们不幸失利，屈居本届【帮会】世界杯C组亚军！"
                else
                    strInfo = "你所在帮会的成员都不在战场，你们不幸失利，获得本届【帮会】世界杯C组殿军！"
                end
            end
        elseif groupType == 1 then
            if turnNumber == 0 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸被淘汰，没能进入B组4强。"
            elseif turnNumber == 1 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，没能进入B组决赛。"
            elseif turnNumber == 2 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，获得本届【帮会】世界杯B组殿军！"
            elseif turnNumber == 3 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，屈居本届【帮会】世界杯B组亚军！"
            end
        elseif groupType == 2 then
            if turnNumber == 0 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸被淘汰，没能进入A组4强。"
            elseif turnNumber == 1 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，没能进入A组决赛。"
            elseif turnNumber == 2 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，获得本届【帮会】世界杯A组殿军！"
            elseif turnNumber == 3 then
                strInfo = "你所在帮会的成员都不在战场，你们不幸失利，屈居本届【帮会】世界杯A组亚军！"
            end
        end
    end

    if strInfo ~= nil then
        LuaScenceM2Player( sceneId, selfId, strInfo, name, 2, 1)
    end
end

-- 箭塔被摧毁
function x300615_OnDie( sceneId, selfId, killerId)
    if x300615_IsGuildContendScene( sceneId) == 0 then
        return
    end

    -- 得到杀人者所属帮会
    local nGuildId = GetGuildID( sceneId, killerId)
    local ownerId = GetOwnerID( sceneId, killerId)
    if ownerId ~= -1 then
        -- 狗或者鹰杀死敌人
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
            -- 创建废墟
            CreateMonster( sceneId, 9738, item.x, item.z, 3, 409, -1, item.guid + 100, 4)
            -- 保存废墟GUID
            x300615_g_RuinList[ sceneId][ getn( x300615_g_RuinList) + 1] = item.guid + 100
            score = item.score
            strTitle = x300615_g_ShowTowerTable[ i].title
            strName = x300615_g_ShowTowerTable[ i].name
            bFind = 1
            break
        end
    end

    -- 更新个人得分
    if ownerId ~= -1 then
        SetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, ownerId, RD_GUILDCONTEND_SCORE) + score)
    else
        SetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, killerId, RD_GUILDCONTEND_SCORE) + score)
    end
    -- 根据摧毁的箭塔类型给帮会加分
    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    if nGuildA == nGuildId then
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + score)
    elseif nGuildB == nGuildId then
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + score)
    end
    if bFind == 1 then
        local strBroadcast = format( "帮会%s摧毁了%s的%s", GetGuildName( nGuildId), strTitle, strName)
        local iCount = GetScenePlayerCount( sceneId)
        for i = 0, iCount - 1 do
            local objId = GetScenePlayerObjId( sceneId, i)
            if IsPlayerStateNormal( sceneId, objId) == 1 then
                LuaScenceM2Player( sceneId, objId, strBroadcast, GetName( sceneId, objId), 5, 1)
            end
        end
    end
end

