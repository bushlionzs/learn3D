
x300660_g_ScriptId = 300660

--任务文本描述
x300660_g_MissionName="【国家】领取王者坐骑"

--王者骑乘ID
x300660_g_King_QiCheng = 12050300

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300660_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 and CountryGetOfficial(sceneId,selfId)~=7 then
		return
	end
	AddQuestNumText(sceneId,x300660_g_ScriptId,x300660_g_MissionName,3)
end

function x300660_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本	

	local Readme_1 = "#Y【国家】领取王者坐骑#W#r #r"	
	local Readme_2 = "\t渥洼龙种雪霜同，毛骨天生胆气雄。#r #r"
	local Readme_3 = "\t梦魂犹在龙门镇，百战沙场战群雄。#r #r"
	local Readme_4 = "\t巡过玉楼金辔响，一声嘶断落花风。#r #r"
	local Readme_5 = "\t昔令吾将连年寻，现持宝骑献名王。#r #r"
	local Readme_6 = "#W我尊敬的#R"..GetName(sceneId, selfId).."#W，功夫不负有心人，我们终于给您找到了诗句中的宝骑，点击确定您就可以一睹其风采。#r"	
	local Readme = Readme_1 .. Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x300660_g_ScriptId, -1 )
	
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x300660_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--接受
--**********************************
function x300660_ProcAccept( sceneId, selfId )
	
	--再次检查是否是国王，王后
	local official = CountryGetOfficial(sceneId,selfId)
	if official~=8 and official~=7 then
		Msg2Player( sceneId,selfId, "很抱歉，您还不是国王或王后，无法领取王者坐骑。", 8, 2 )
		return
	end
	
	--再次检查是否领取过
	if CountryCanDrawBonus(sceneId,selfId,2) == 0 then
		Msg2Player( sceneId,selfId, "很抱歉，您已经领取过王者坐骑。", 8, 2 )
		return
	end
	
	--检查有没有王者坐骑，如果有，就已经领取过了
	if HaveItem(sceneId, selfId,x300660_g_King_QiCheng)>0 or IsHaveHorse(sceneId, selfId,3004)>0 then
		Msg2Player( sceneId,selfId, "很抱歉，您已经领取过王者坐骑。", 8, 2 )
		return
	end	
	
	--开始加物品
	BeginAddItem(sceneId)
	AddItem(sceneId,x300660_g_King_QiCheng,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret==1 then
		AddItemListToPlayer(sceneId,selfId)
		CountryDrawBonus(sceneId,selfId,2)	--置领取标志
		Msg2Player( sceneId,selfId, "恭喜您，您已经成功获得了王者坐骑。", 8, 2 )
	else
		Msg2Player( sceneId,selfId, "很抱歉，您的包裹已满，无法领取王者坐骑。", 8, 2 )
	end
	
end

--**********************************
--放弃
--**********************************
function x300660_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300660_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300660_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300660_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300660_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300660_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300660_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
