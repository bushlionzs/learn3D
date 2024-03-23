
x300839_g_ScriptId = 300839

--任务文本描述
x300839_g_MissionName1 = "【帮会】帮会捐献"
x300839_g_MissionName2 = "【帮会】捐献10两现银"
x300839_g_MissionName3 = "【帮会】捐献100两现银"
x300839_g_MissionName4 = "【帮会】捐献1锭现银"
-- 帮会等级对应金钱上限表
x300839_g_GuildLevelMoney   = {
                                 6000000, 
                                 8000000, 
                                20000000, 
                                24000000, 
                                42000000, 
                                48000000, 
                                54000000, 
                                60000000, 
                                66000000, 
}
x300839_g_GuildDayMoney	= 30000000
--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300839_ProcEventEntry( sceneId, selfId, targetId, MissionId, idExt)	--点击该任务后执行此脚本

	if idExt == 1 then 

		local Readme_1 = "#Y【帮会】帮会捐献#r#W"
		
		local Readme_2 = "\t您可以通过捐献现银来增加#G帮会金钱#W，每捐献#G1两#W现银，帮会金钱也会增加#G1两#W，您每次捐献都会获得帮会活跃度和帮贡的奖励。每天整个帮会在未达到帮会金钱上限的条件下，最多可以接受#G30锭#W的捐献。"
		
		local Readme_3 = "#W#r#Y\t请选择您要捐献的现银数量。"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName2, 3, 2)
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName3, 3, 3)
		AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName4, 3, 4)
		DispatchQuestEventList(sceneId,selfId,targetId);
	
	elseif idExt == 2 then

		local Readme_1 = "#Y【帮会】捐献10两现银#r#W"
		
		local Readme_2 = "\t捐献10两现银，会增加#G10两帮会金钱#W，同时您将会获得#G1#W点帮会活跃度和#G1#W点帮贡。"
		
		local Readme_3 = "#W#r#Y\t您是否要进行帮会捐献？"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 10000)
	elseif idExt == 3 then
			
		local Readme_1 = "#Y【帮会】捐献100两现银#r#W"
		
		local Readme_2 = "\t捐献100两现银，会增加#G100两帮会金钱#W，同时您将会获得#G10#W点帮会活跃度和#G10#W点帮贡。"
		
		local Readme_3 = "#W#r#Y\t您是否要进行帮会捐献？"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 100000)
	elseif idExt == 4 then
		local Readme_1 = "#Y【帮会】捐献1锭现银#r#W"
		
		local Readme_2 = "\t捐献1锭现银，会增加#G1锭帮会金钱#W，同时您将会获得#G100#W点帮会活跃度和#G100#W点帮贡。"
		
		local Readme_3 = "#W#r#Y\t您是否要进行帮会捐献？"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);
		DispatchQuestInfo( sceneId, selfId, targetId, x300839_g_ScriptId, -1 );
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1000000)
	end
	
end

--**********************************
--列举事件
--**********************************
function x300839_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end
	
    AddQuestNumText(sceneId, x300839_g_ScriptId, x300839_g_MissionName1, 3, 1)
    local gid = GetGuildID( sceneId, selfId)
    if gid >= 0 then
        local today = GetDayOfYear()
        if today ~= GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_DATE) then
            SetGuildParam( gid, GD_GUILD_HANDIN_DATE, today)
            SetGuildParam( gid, GD_GUILD_HANDIN_MONEY, 0)
        end
    end
end


--********************
--检测接受条件
--**********************************
function x300839_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300839_ProcAccept( sceneId, selfId)
    local money = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
    SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
    local gmoney = GetGuildMoney( sceneId, selfId)
    local glv = GetGuildLevel( sceneId, selfId)
    local gid = GetGuildID( sceneId, selfId)

    if gid < 0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "您需要先加入一个帮会。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您不是帮会成员，无法进行帮会捐献。",8,2)
		return
    end

    if glv <= 0 then
        return
    end

	if GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) >= x300839_g_GuildDayMoney then
        Msg2Player( sceneId, selfId, "今天帮会捐献总额已达上限，请明天再来", 8, 3)
        return
    elseif GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) + money > x300839_g_GuildDayMoney then
        Msg2Player( sceneId, selfId, "捐献的数额超过今日帮会可捐上限，无法捐献", 8, 3)
        return
    end

    if gmoney + money > x300839_g_GuildLevelMoney[ glv] then
        Msg2Player( sceneId, selfId, "帮会金钱接近或已到达上限，无法捐献", 8, 3)
        return
    end

	if GetMoney(sceneId, selfId, 0) < money then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "很抱歉，您的现银不足。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您的现银不足，无法进行帮会捐献。",8,2)
		return
	end

	CostMoney(sceneId, selfId, 0, money, 310)
	BeginQuestEvent(sceneId);AddQuestText(sceneId, format("扣除金钱#G#{_MONEY%d}#cFFCF00，获得帮贡#G"..tostring( money / 10000).."#cFFCF00点，帮会活跃度#G"..tostring( money / 10000).."#cFFCF00点", money));EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,format("【帮会】帮会捐献:扣除金钱#G#{_MONEY%d}#W", money),8,2)

	AddGuildUserPoint( sceneId, selfId, money / 10000)
	Msg2Player(sceneId,selfId,"获得帮贡#G"..tostring( money / 10000).."#cFFCF00点",8,2)

	AddGuildActivity( sceneId, selfId, money / 10000)
	Msg2Player(sceneId,selfId,"帮会活跃度增加#G"..tostring( money / 10000).."#cFFCF00点",8,2)

	AddGuildMoney( sceneId, selfId, money)
	Msg2Player( sceneId, selfId, format("%s慷慨捐助，使帮会金钱增加了#{_MONEY%d}。",GetName(sceneId, selfId), money), 6)

    SetGuildParam( gid, GD_GUILD_HANDIN_MONEY, money + GetGuildCacheFreeParam( gid, GD_GUILD_HANDIN_MONEY) )
end

--**********************************
--放弃
--**********************************
function x300839_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300839_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300839_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300839_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300839_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300839_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300839_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


