x300836_g_ScriptId = 300836
x300836_g_MissionName = "【帮会】帮务发布"
x300836_g_MissionInfo = {
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_HUSHOU,
								name="【帮会】护兽令",
								Readme="#Y【帮会】帮务发布#r#W\t发布【帮会】护兽令根据帮会等级不同需要消耗数量不同的#Y帮会金钱#W。如果您确定发布【帮会】帮会神兽多倍，您帮会内所有成员在#R2小时内#W完成当天【帮会】帮会神兽任务时，将会获得#G2倍经验和帮贡#W，帮主获得#G4倍经验和帮贡#W，副帮主获得#G3倍经验和帮贡#W。#r",
								money = {1120000,1490000,1860000,2790000,3130000,3130000,3130000,3130000,3130000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_HEIMU,
								name="【帮会】图腾令",
								Readme="#Y【帮会】帮务发布#r#W\t发布【帮会】图腾令根据帮会等级不同需要消耗数量不同的#Y帮会金钱#W。如果您确定发布【帮会】帮会图腾多倍，您帮会内所有成员在#R2小时内#W完成当天【帮会】帮会图腾任务时，将会获得#G2倍经验和帮贡#W，帮主获得#G4倍经验和帮贡#W，副帮主获得#G3倍经验和帮贡#W。#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_ANZHAN,
								name="【帮会】暗战令",
								Readme="#Y【帮会】帮务发布#r#W\t发布【帮会】帮会暗战令根据帮会等级不同需要消耗数量不同的#Y帮会金钱#W。如果您确定发布【帮会】帮会暗战多倍，您帮会内所有成员在#R2小时内#W完成当天【帮会】帮会暗战任务时，将会获得#G2倍经验和帮贡#W，帮主获得#G4倍经验和帮贡#W，副帮主获得#G3倍经验和帮贡#W。#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_CHUYAO,
								name="【帮会】除魔令",
								Readme="#Y【帮会】帮务发布#r#W\t发布【帮会】除魔令根据帮会等级不同需要消耗数量不同的#Y帮会金钱#W。如果您确定发布【帮会】帮会除魔多倍，您帮会内所有成员在#R2小时内#W完成当天【帮会】帮会除魔任务时，将会获得#G2倍经验和帮贡#W，帮主获得#G4倍经验和帮贡#W，副帮主获得#G3倍经验和帮贡#W。#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_MUJI,
								name="【帮会】募集令",
								Readme="#Y【帮会】帮务发布#r#W\t发布【帮会】募集令根据帮会等级不同需要消耗数量不同的#Y帮会金钱#W。如果您确定发布【帮会】帮会募集多倍，您帮会内所有成员在#R2小时内#W提交【帮会】帮会募集时，将会获得#G2倍经验和帮贡#W，帮主获得#G4倍经验和帮贡#W，副帮主获得#G3倍经验和帮贡#W。#r",
								money = {560000,745000,930000,1395000,1565000,1565000,1565000,1565000,1565000,}
							},
						}


x300836_g_ElapseTime = 2*60*60	--多倍任务持续时间，2 小时

--点击（NPC）
function x300836_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGuildID( sceneId, selfId ) == -1 then
 		--不在帮会中
		return
	end
	
	AddQuestNumText(sceneId,300836,x300836_g_MissionName,8,0)


end

--点击（按钮）点击该任务后执行此脚本
function x300836_ProcEventEntry( sceneId, selfId, targetId,state,index)

	if index == 0 then
		local Readme = "#Y【帮会】帮务发布#r#W\t尊敬的帮主您好#G3级帮会#W以上帮主可以在我这里发布帮务任务！#G每日晚22点前#W只能进行#G一次#W帮务发布。您可以选择以下按钮来发布帮会多倍任务："
		local guildid = GetGuildID(sceneId,selfId)
		BeginQuestEvent(sceneId);
		for i,item in x300836_g_MissionInfo do
			if GetGuildCacheFreeParam(guildid,item.id) == -1 then
				AddQuestNumText(sceneId,300836,item.name.."(未发布)",3,item.id)
			else
				AddQuestNumText(sceneId,300836,item.name.."(已发布)",3,item.id)
			end
		end	
		AddQuestText(sceneId,Readme);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif index < 100 then
		for i,item in x300836_g_MissionInfo do
			if item.id == index then
				 Readme = item.Readme			
				break
			end
		end
		
		local money = x300836_GetDeductMoneyNum(sceneId, selfId,index)
		local ding = floor( money / (1000*1000) )
		local liang = floor( mod(money,1000*1000)/ 1000 )
		local wen = mod(money,1000)
		
		local str = format("#Y需要消耗帮会金钱：%d锭%d两%d文",ding,liang,wen)		
		BeginQuestEvent(sceneId);
		AddQuestNumText(sceneId,300836,"确定..",3,index+100)
		AddQuestText(sceneId,Readme);
		AddQuestText(sceneId,str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	else
		if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，只有帮主（副帮主）才能发布帮务任务！");
				DispatchQuestTips(sceneId,selfId)	
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"很抱歉，只有帮主（副帮主）才能发布帮务任务！",8,2)
			return
		end
		local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--得到帮会简单数据(等级) 
		if GuildLevel <3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您的帮会等级不足3级！");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您的帮会等级不足3级！",8,2)
			return
		end
		local hour,minute,second = GetHourMinSec()
		if ( hour < 22) then
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，请在22：00前发布帮务任务。");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，请在22：00前发布帮务任务。",8,2)
			return 
		end
			
		-- 判断钱是否足够
		local op = index - 100
		GetGuildQuestData(sceneId,selfId,GD_GUILD_INDEX_MULTI_MISSION_TODAY,x300836_g_ScriptId,op,"OnReturn1")
	end
	
end

function x300836_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	local op = MissionId
	if MissionData~=-1 then 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "今天已发布过一次任务，请明日再发！");
		DispatchQuestTips(sceneId,selfId)	
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您今天已发布过一次任务，请明日再发！",8,2)
		return	
	end
	
	GetGuildQuestData(sceneId,selfId,op,x300836_g_ScriptId,op,"OnReturn2")		
	
end

function x300836_OnReturn2(sceneId, selfId,MissionData,MissionId,targetId)
	if MissionData ~= -1 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你已发布过该任务");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)		
		return
	end
	local op = MissionId
	local money = x300836_GetDeductMoneyNum(sceneId, selfId,op)
		if GetGuildMoney(sceneId, selfId) < money then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您帮会内的帮会金钱不足！");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您帮会内的帮会金钱不足！",8,2)
			return
		end
	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	local guildid = GetGuildID(sceneId,selfId)
	SetGuildQuestData(sceneId,guildid,op,GetCurrentTime())
	SetGuildQuestData(sceneId,guildid,GD_GUILD_INDEX_MULTI_MISSION_TODAY,op)
	local Readme = ""
	BeginQuestEvent(sceneId)

	for i,item in x300836_g_MissionInfo do
		if item.id == op then
		Readme = item.name			
		break
		end
	end

	AddQuestText(sceneId, "您成功发布了"..Readme.."多倍任务");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	Msg2Player(sceneId,selfId,"帮主（副帮主）发布了"..Readme.."多倍任务，2小时内回复该任务双倍奖励！",6,2)
	SubGuildMoney(sceneId, selfId,money)
end

function x300836_GetDeductMoneyNum(sceneId,selfId,MissionType)

	local GuildLevel,xx1,xx2 = GetGuildSimpleData(GetGuildID(sceneId, selfId))
	for i,item in x300836_g_MissionInfo do
		if item.id == MissionType then
			return item.money[GuildLevel];
		end
	end
	
	
	return -1;
end


--点击（确定）
function x300836_ProcQuestAccept( sceneId, selfId, targetId )
	
end

--**********************************
--接受
--**********************************
function x300836_ProcAccept( sceneId, selfId )
	
	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	GetGuildQuestData(sceneId, selfId,-1,x300836_g_ScriptId)
end

--**********************************
--放弃
--**********************************
function x300836_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300836_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300836_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300836_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300836_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300836_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300836_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end