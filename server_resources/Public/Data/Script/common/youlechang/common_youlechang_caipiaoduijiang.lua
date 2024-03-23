x310336_g_ScriptId 		= 310336
-- 幸运券兑换
x310336_g_ScriptName	= "兑取乐透大奖！"

x310336_g_SubmitItem	= 12035005 -- 无敌幸运星

x310336_g_TitleInfo		= "#Y【个人】幸运乐透大奖\n\t#W幸运乐透大奖，那可是一笔巨额的财富！它的得主，究竟会是谁呢？\n\t你是这个天上人间·麒麟里最幸运的人吗？\n\t如果你这次没有中奖，记得下周继续来试试你的运气；要是你是那最幸运的家伙，更要记得每周来这里看看我，朋友！"
		
x310336_g_GameId = 1041
function x310336_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--点击该任务后执行此脚本
	if GetGameOpenById(x310336_g_GameId) <= 0 then
		Msg2Player(sceneId,selfId,"此活动已关闭",8,3)
		return
	end
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x310336_g_TitleInfo)
		
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x310336_g_ScriptId, x310336_g_ScriptId)
end

--列举事件
function x310336_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	--local state = GetQuestStateNM( sceneId, selfId, NPCId, x310336_g_MissionId)
    AddQuestNumText(sceneId,x310336_g_ScriptId,x310336_g_ScriptName,3,0)
end

function x310336_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--点确定后
function x310336_ProcAccept( sceneId, selfId )

	local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310336_g_SubmitItem)
	if bagIndex < 0 then
		local msg = format("没有#{_ITEM%d}。", x310336_g_SubmitItem)
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	local firstTime = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
	local currtime = GetDayOfYear()
	if currtime ~= firstTime then
		Msg2Player( sceneId, selfId, "已经超过了保质期，无法兑换奖励,请丢弃此道具！", 8, 3)
		return
	end
	
	local index = GetItemParam( sceneId, selfId, bagIndex, 4, 2 )
	
	local caipiao1 = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1)
	local caipiao2 = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1)
	local caipiao3 = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1)
	local caipiao4 = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2)
	local caipiao5 = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2)
	local caipiao6 = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2)
	local caipiao7 = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2)
	
	if caipiao1 == -1 and caipiao2 == -1 and caipiao3 == -1 and caipiao4 == -1 and
		caipiao5 == -1 and caipiao6 == -1 and caipiao7 == -1 then
		Msg2Player( sceneId, selfId, "很抱歉，现在还没有开出幸运号码", 8, 3)
		return
	end
	
	local ret = 0
	if index == caipiao1 then
		ret = 1
	elseif index == caipiao2 then
		ret = 1
	elseif index == caipiao3 then
		ret = 1
	elseif index == caipiao4 then
		ret = 1
	elseif index == caipiao5 then
		ret = 1
	elseif index == caipiao6 then
		ret = 1
	elseif index == caipiao7 then
		ret = 1
	end
	
	if ret == 0 then
		Msg2Player( sceneId, selfId, "很抱歉，您手中的号码不在今天已开出的幸运号码之内", 8, 3)
		return
	end
	
	DelItem( sceneId, selfId, x310336_g_SubmitItem, 1)
	
	GamePlayScriptLog(sceneId, selfId, 1612)
	
	local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)-1000
	AddMoney(sceneId,selfId,1,count*1000)
	
	Msg2Player( sceneId, selfId, format("恭喜你中了乐透大奖！你获得了#{_MONEY%d}银卡的奖励！", count*1000), 8, 3)
end