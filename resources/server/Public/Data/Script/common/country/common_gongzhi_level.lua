
--点击（NPC）
function x300656_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300656,"【活动】领取测试费",3,1)--增加按钮:领取测试费	
end

--点击（按钮）点击该任务后执行此脚本
function x300656_ProcEventEntry( sceneId, selfId, targetId,state,index)
	local x300656Readme = ""
	local Readme_0 = "#Y【活动】领取测试费#W#r"
	local Readme_3 = "#W\t当您的等级为20级~69级之间时，您可以通过我领取相应的测试费，等级低于20级将不能领取测试费，如果您忘记了领取并超过了相应的等级，我会一次性补偿您错过的测试费。#r#R注：测试费的货币类型为（金卡） #r"
	local Readme_4  = "#G\t 等级	         测试费#W"
	local Readme_6  = "#r\t20~29级		    2两"
	local Readme_7  = "#r\t30~39级		    4两"
	local Readme_8  = "#r\t40~49级		    8两"
	local Readme_9  = "#r\t50~59级		   18两"
	local Readme_10 = "#r\t60~69级		   36两"
	local Readme_6_1  = "#r#d\t20~29级   已领取   2两#W"
	local Readme_7_1  = "#r#d\t30~39级   已领取   4两#W"
	local Readme_8_1  = "#r#d\t40~49级   已领取   8两#W"
	local Readme_9_1  = "#r#d\t50~59级   已领取  18两#W"
	local Readme_10_1 = "#r#d\t60~69级   已领取  36两#W"
	local level_1 = GetQuestData(sceneId, selfId, MD_LEVELUP_LEVEL[1], MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3])
	if level_1 < 2 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10
	elseif level_1 == 2 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7..Readme_8..Readme_9..Readme_10
	elseif level_1 == 3 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8..Readme_9..Readme_10
	elseif level_1 == 4 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9..Readme_10
	elseif level_1 == 5 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10
	elseif level_1 == 6 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10_1
	elseif level_1 > 6 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10_1
	end						
	BeginQuestEvent(sceneId);AddQuestText(sceneId,x300656Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300656, -1)

end

--点击（确定）
function x300656_ProcAcceptCheck( sceneId, selfId, NPCId )
	--081217(齐亮)处于PK模式或PK值大于0不能领取测试费
	local pkMode = GetPlayerPKMode( sceneId, selfId)
	local pkValue = GetPKValue( sceneId, selfId)
	if pkMode == 2 then
		BeginQuestEvent( sceneId);AddQuestText( sceneId, "很抱歉，您已开启了PK模式或您的PK值过高，无法使用此功能" );EndQuestEvent();DispatchQuestTips( sceneId, selfId)
		return
	end

	--领取测试费正文
		local x300656gongzhi2 = 0
		local level = GetLevel(sceneId,selfId)
		local level_3 = GetQuestData(sceneId, selfId, MD_LEVELUP_LEVEL[1], MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3])
		
		if level < 20 then		
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"测试费领取失败");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"很抱歉，您的等级小于20级，无法领取测试费！",8,2)
			return			
		else
			if level_3 == 0 then--从未领取过
				if level >= 20 and level <= 29 then
					x300656gongzhi2 = 2	
				elseif level >= 30 and level <= 39 then
					x300656gongzhi2 = 2 + 4
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 2 + 4 + 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 2 + 4 + 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 2 + 4 + 8 + 18 + 36
				end
			elseif level_3 == 2 then--20~29级领取过
				if level >= 20 and level <= 29 then
					Msg2Player(sceneId,selfId,"很抱歉，您已经领取过当前等级的测试费！",8,2)
					return
				elseif level >= 30 and level <= 39 then
					x300656gongzhi2 = 4
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 4 + 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 4 + 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 4 + 8 + 18 + 36
				end		
			elseif level_3 == 3 then--30~39级领取过
				if level >= 20 and level <= 39 then
					Msg2Player(sceneId,selfId,"很抱歉，您已经领取过当前等级的测试费！",8,2)
					return
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 8 + 18 + 36
				end
			elseif level_3 == 4 then--40~49级领取过
				if level >= 20 and level <= 49 then
					Msg2Player(sceneId,selfId,"很抱歉，您已经领取过当前等级的测试费！",8,2)	
					return
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 18
				elseif level >= 60 then
					x300656gongzhi2 = 18 + 36
				end									
			elseif level_3 == 5 then--50~59级领取过
				if level >= 20 and level <= 59 then
					Msg2Player(sceneId,selfId,"很抱歉，您已经领取过当前等级的测试费！",8,2)
					return	
				elseif level >= 60 then
					x300656gongzhi2 = 36
				end
			elseif level_3 >= 6 then
					Msg2Player(sceneId,selfId,"您已经领取过全部等级的测试费！",8,2)
					return
			end
			
			AddMoney(sceneId,selfId,3,x300656gongzhi2*1000, 100)--给钱
			local level_2 = floor ( ( GetLevel ( sceneId , selfId ) ) / 10 )
			SetQuestData(sceneId,selfId,MD_LEVELUP_LEVEL[1],MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3], level_2)--记录成功领取测试费的等级段
			Msg2Player(sceneId,selfId,"恭喜您，您获得了测试费：#r金卡：#R"..x300656gongzhi2.."两。",8,2)--给与提示
		end			

end




--**********************************
--接受
--**********************************
function x300656_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300656_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300656_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300656_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300656_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300656_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300656_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300656_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



