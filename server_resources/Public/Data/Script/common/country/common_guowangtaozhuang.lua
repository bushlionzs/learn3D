
x300657_g_ScriptId = 300657


--任务文本描述
x300657_g_MissionName="【国家】领取王者套装"

--王者套装ID
x300657_g_King_Suit = 10300100

--**********************************
--任务入口函数
--**********************************
function x300657_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 and CountryGetOfficial(sceneId,selfId)~=7 then
		return
	end
	AddQuestNumText(sceneId,x300657_g_ScriptId,x300657_g_MissionName,3)
end
function x300657_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本	
	
	local Readme_1 = "#Y【国家】领取王者套装#r"	
	local Readme_2 = "#W尊敬的#R"..GetName(sceneId, selfId).."#W您好：#r"	
	local Readme_3 = "\t大祭司为您精心打造了一件举世无双的王者套装，现在已经完工，并存放在我这里。#r"	
	local Readme_4 = "\t点击确定您就可以将其拿走。#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4			
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x300657_g_ScriptId, -1 )
	
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x300657_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--接受
--**********************************
function x300657_ProcAccept( sceneId, selfId )

	--再次检查是否是国王，王后
	local official = CountryGetOfficial(sceneId,selfId)
	if official~=8 and official~=7 then
		Msg2Player( sceneId,selfId, "很抱歉，您还不是国王或王后，无法领取王者套装。", 8, 2 )
		return
	end
	
	--再次检查是否领取过
	-- if CountryCanDrawBonus(sceneId,selfId,1) == 0 then
		-- Msg2Player( sceneId,selfId, "很抱歉，您已经领取过王者套装。", 8, 2 )
		-- return
	-- end
	
	--检查有没有王者套装
	if HaveItem(sceneId, selfId,x300657_g_King_Suit)>0 then
		Msg2Player( sceneId,selfId, "很抱歉，您已经领取过王者套装。", 8, 2 )
		return
	end
	
	--开始加物品
	BeginAddItem(sceneId)
	AddItem(sceneId,x300657_g_King_Suit,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret==1 then
		AddItemListToPlayer(sceneId,selfId)
		CountryDrawBonus(sceneId,selfId,1)	--置领取标志
		Msg2Player( sceneId,selfId, "恭喜您，您已经成功获得了王者套装。", 8, 2 )
	else
		Msg2Player( sceneId,selfId, "很抱歉，您的包裹已满，无法领取王者套装。", 8, 2 )
	end
	
end

--**********************************
--放弃
--**********************************
function x300657_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--继续
--**********************************
function x300657_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300657_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300657_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300657_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300657_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300657_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
