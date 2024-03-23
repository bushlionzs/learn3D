-- 三番副本添加周末功能

x701031_g_ScriptId 		= 701031
x701031_g_ScriptName	= "提交三番令"

x701031_g_SubmitItem	= 11990011

x701031_g_TitleInfo		= "\t父亲临走之前吩咐过我要收集#G三番令#W，只要你交给我一个#G三番令#W我就能给予你完成三番副本对应的经验和天赋。当然这么做会#Y占用一次三番副本次数#W。\n\t怎么样，你愿意交给我一个#G三番令#W，获得等同于完成三番副本的经验和天赋吗？\n \n#G小提示：\n\t一天只能提交一次三番令。\n\t有江湖请柬或朝廷请柬效果时提交，经验奖励会翻倍。"

						
function x701031_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--点击该任务后执行此脚本
	local level = GetLevel(sceneId,selfId)
	BeginQuestEvent(sceneId)
		--任务信息
		local exp =level*163350
		if level < 70 then
			exp =3256200
		elseif level < 75 then
			exp =3499200
		elseif level < 80 then
			exp =12577950
		elseif level < 85 then
			exp =level*163350
		end				
		AddQuestText(sceneId,"#Y"..x701031_g_ScriptName.."#W")
		AddQuestText(sceneId,x701031_g_TitleInfo)
		
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x701031_g_ScriptId, x701031_g_ScriptId)
end

--列举事件
function x701031_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local week = GetWeek()
	if week == 0 or week == 6 then
		AddQuestNumText(sceneId,x701031_g_ScriptId,x701031_g_ScriptName,3,0)
	end
end

function x701031_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--点确定后
function x701031_ProcAccept( sceneId, selfId )
	local week = GetWeek()
	if week == 1 or week == 2 or week == 3 or week == 4 or week == 5 then
				Msg2Player(sceneId, selfId,format("提交#{_ITEM%d}失败，请于周六或周日再来", x701031_g_SubmitItem), 0, 2)
				Msg2Player(sceneId, selfId,format("提交#{_ITEM%d}失败，请于周六或周日再来", x701031_g_SubmitItem), 0, 3)
				return
	end			

	local level = GetLevel(sceneId,selfId)
	if level <65 then
		Msg2Player( sceneId, selfId, "很抱歉，你等级过低，提交失败", 8, 3)
		Msg2Player( sceneId, selfId, "很抱歉，你等级过低，提交失败", 8, 2)
		return
	end


	if HaveItemInBag(sceneId, selfId, x701031_g_SubmitItem) <= 0 then
		local msg = format("很抱歉，你没有#{_ITEM%d}，提交失败", x701031_g_SubmitItem)
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	local weekcount = 0
	local dayCount = 0
	
	local weekIndex = GetWeekIndex()
	local lastWeek = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1],MD_FUBEN_QIULONGDAO_DATE[2],MD_FUBEN_QIULONGDAO_DATE[3])
	if lastWeek == weekIndex then
		weekcount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1],MD_FUBEN_QIULONGDAO_DAYCOUNT[2],MD_FUBEN_QIULONGDAO_DAYCOUNT[3] )
	end
			
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1],MD_FUBEN_QIULONGDAO_TODAY[2],MD_FUBEN_QIULONGDAO_TODAY[3] )
	if today == lastDay then	
		dayCount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1],MD_FUBEN_QIULONGDAO_TODAYCOUNT[2],MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
	end
	
	if weekcount > 18 or dayCount > 6 then
		local msg = "很抱歉，您今天已经没有剩余的三番次数"
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	local date = GetQuestData(sceneId, selfId, MD_FUBEN_WEEKEND_SANFAN_DATE[1],MD_FUBEN_WEEKEND_SANFAN_DATE[2],MD_FUBEN_WEEKEND_SANFAN_DATE[3])
	if today == date then
		local msg = "很抱歉，一天只能提交一次三番令"
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	
	if weekIndex ~= lastWeek then
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1], MD_FUBEN_QIULONGDAO_DATE[2], MD_FUBEN_QIULONGDAO_DATE[3], weekIndex)
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], 3)
	else
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], weekcount+3)
	end
	
	if today ~= lastDay then
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1], MD_FUBEN_QIULONGDAO_TODAY[2], MD_FUBEN_QIULONGDAO_TODAY[3], today)
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], 3)
	else
		SetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], dayCount+3)
	end
	
	SetQuestData(sceneId, selfId, MD_FUBEN_WEEKEND_SANFAN_DATE[1], MD_FUBEN_WEEKEND_SANFAN_DATE[2], MD_FUBEN_WEEKEND_SANFAN_DATE[3], today)
	
	DelItem(sceneId, selfId, x701031_g_SubmitItem, 1)
	
	local exp =level*163350
		if level < 70 then
			exp =3256200
		elseif level < 75 then
			exp =3499200
		elseif level < 80 then
			exp =12577950
		elseif level < 85 then
			exp =level*163350
		end				
	if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
		AddExp(sceneId, selfId, exp*2)
		Msg2Player(sceneId, selfId,format("提交三番令成功，在请柬作用下获得了#G经验%d#cffcf00点",exp*2), 0, 2)
		Msg2Player(sceneId, selfId,format("提交三番令成功，在请柬作用下获得了#G经验%d#cffcf00点",exp*2), 0, 3)
	else	
		AddExp(sceneId, selfId, exp)
		Msg2Player(sceneId, selfId,format("提交三番令成功，获得了#G经验%d#cffcf00点",exp), 0, 2)
		Msg2Player(sceneId, selfId,format("提交三番令成功，获得了#G经验%d#cffcf00点",exp), 0, 3)
	end
	local refixtf = AddInherenceExp( sceneId, selfId, 1800) 
  Msg2Player( sceneId, selfId, format( "提交三番令成功，获得#G天赋值%d#cffcf00点", refixtf), 8, 2)      
  Msg2Player( sceneId, selfId, format( "提交三番令成功，获得#G天赋值%d#cffcf00点", refixtf), 8, 3)     
end