
--脚本号
x310034_g_ScriptId = 310034

--任务文本描述
x310034_g_MissionName="圣山地宫传入1"

x310034_g_MaxHuman = 100
x310034_g_MaxHumanOther = 200

x310034_g_ItemId = 12030027

function x310034_IsOpenedTime()
	local minute = GetMinOfDay();
	if (minute >=2*60 and minute<=2*60+4) or ( minute>=6*60 and minute<=6*60+4 ) or (minute>=10*60 and minute<=10*60+4) or 
		(minute >=14*60 and minute<=14*60+4) or (minute >=18*60 and minute<=18*60+4) or (minute >=22*60 and minute<=22*60+4) then
		return 1
	end

	return -1
end


function x310034_HaveAccepted(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3])

	if lastDay == GetDayOfYear() then
		return 1
	end
	return -1
end

function x310034_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetLevel(sceneId, selfId) < 60 then
		return
	end
    AddQuestNumText(sceneId,x310034_g_ScriptId,"圣山地宫(60级)",14,-1)
     
end


function x310034_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	BeginQuestEvent(sceneId)
	  local Readme_1 = "#Y【圣山地宫】#r"
	  local Readme_2 = "#W\t每天的#G02:00#W，#G06:00#W，#G10:00#W，#G14:00#W，#G18:00#W和#G22:00#W，圣山地宫的入口会打开#R5分钟#W，如果你拥有#G混沌之星#W，那么在圣山地宫开放的任意时间里都可以进入。"
	  local Readme_3 = "#W\n\t在那时，我可以给持有#G五耀之证#W或者#G混沌之星#W的勇士们加持#G五耀之力#W，这样他们就有了足够的能力铲除妖魔。然而，五耀之力是一种非常霸道的力量，普通人的身体#R一天#W只能加持#R一次#W。"
	  local Readme_4 = "#W\n\t同时，聚集过多的五耀之力可能会造成不可预知的问题，因此圣山地宫中最多只能有#R一百人#W同时进行战斗。但是如果你拥有#G混沌之星#W，就可以大大减少五耀之力的散发，这样圣山地宫将可以有#R两百人#W同时进行战斗。"
	  local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId,Readme)
		EndQuestEvent(sceneId)	
	DispatchQuestInfo(sceneId,selfId,targetId,x310034_g_ScriptId,-1)

	return 
end

--********************
--检测接受条件
--**********************************
function x310034_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x310034_IsGameTime()
	local minute = GetMinOfDay();
	if (minute >=2*60 and minute<=2*60+20) or ( minute>=6*60 and minute<=6*60+20 ) or (minute>=10*60 and minute<=10*60+20) or 
		(minute >=14*60 and minute<=14*60+20) or (minute >=18*60 and minute<=18*60+20) or (minute >=22*60 and minute<=22*60+20) then
		return 1
	end
	return -1
end

--**********************************
--接受
--**********************************
function x310034_ProcAccept( sceneId, selfId )
	
	if GetLevel( sceneId, selfId ) < 60 then
	
		Msg2Player(sceneId,selfId,"等级不够，无法进入",8,3)		
		Msg2Player(sceneId,selfId,"等级不够，无法进入",8,2)
		return
	end

	if x310034_IsGameTime() < 0 then
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,3)		
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,2)
			return
	end

	local bHave = 0
	if GetItemCount(sceneId, selfId, 11990100)  > 0 then
		bHave = 1
	end

	if bHave == 0 then
		if x310034_IsOpenedTime() < 0 then
			Msg2Player(sceneId,selfId,"不是在活动时间内，但拥有混沌之星，也可进入",8,3)		
			Msg2Player(sceneId,selfId,"不是在活动时间内，但拥有混沌之星，也可进入",8,2)
			return
		end
	else
		if x310034_IsGameTime() < 0 then
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,3)		
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,2)
			return
		end
	end

	if x310034_HaveAccepted(sceneId, selfId) > 0 then
		
		Msg2Player(sceneId,selfId,"一天只能进入一次圣山地宫",8,3)		
		Msg2Player(sceneId,selfId,"一天只能进入一次圣山地宫",8,2)
		return 
	end

	if bHave == 0 then
		if GetItemCount(sceneId, selfId, x310034_g_ItemId)  == 0 then
			Msg2Player(sceneId,selfId,"你没有五耀之证，但拥有混沌之星，也可以进入",8,3)		
			Msg2Player(sceneId,selfId,"你没有五耀之证，但拥有混沌之星，也可以进入",8,2)
			return
		end
	end
	

	if IsBusMember(sceneId, selfId) > 0 then
		Msg2Player(sceneId,selfId,"护送状态，无法进入",8,3)		
		Msg2Player(sceneId,selfId,"护送状态，无法进入",8,2)
		return
	end

	local countryId = GetCurCountry(sceneId, selfId)
	
	local curNum = 0
	if countryId == 0 then
		curNum = YX_LOULAN_HUMAN_NUM2 
	elseif countryId == 1 then
		curNum = YX_LAIYIN_HUMAN_NUM2 
	elseif countryId == 2 then
		curNum = YX_KUNLUN_HUMAN_NUM2 
	elseif countryId == 3 then
		curNum = YX_DUNHUANG_HUMAN_NUM2 
	end
	local sign = 0;

	--if curNum < x310034_g_MaxHuman then
		if x310034_IsOpenedTime() > 0 then
			if GetItemCount(sceneId, selfId, x310034_g_ItemId)  > 0 then
				sign = 1
			else
				if bHave > 0 then
					sign =2;
				end
			end
		else
			if bHave > 0 then
				sign =2;
			end
		end
	--elseif curNum >= x310034_g_MaxHuman and curNum < x310034_g_MaxHumanOther then
		
		--if bHave  > 0 then
		--	sign =2;	
		--else	
		--	Msg2Player(sceneId,selfId,"圣山地宫已超过百人，无法进入",8,3)	
		--	Msg2Player(sceneId,selfId,"圣山地宫已超过百人，无法进入",8,2)
		--	return
		--end

	 
	--else	
	--	Msg2Player(sceneId,selfId,"圣山地宫已达二百人，无法进入",8,3)	
	--	Msg2Player(sceneId,selfId,"圣山地宫已达二百人，无法进入",8,2)
	--	return

	--end

	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3], GetDayOfYear())
	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_MINUTE[1], MD_YAOXIE_DIGONG_MINUTE[2], MD_YAOXIE_DIGONG_MINUTE[3], GetMinOfDay())
	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_COUNT[1], MD_YAOXIE_DIGONG_COUNT[2], MD_YAOXIE_DIGONG_COUNT[3], 1)


	if sign == 0 then
		return
	elseif sign == 1 then
		DelItem(sceneId, selfId, x310034_g_ItemId, 1)
	elseif sign == 2 then
		DelItem(sceneId, selfId, 11990100, 1)
	end
	

	local NewSceneId;

	if countryId == 0 then
		NewSceneId = YX_LOULAN_SCENE_ID2
		YX_LOULAN_HUMAN_NUM2 = YX_LOULAN_HUMAN_NUM2 + 1
	elseif countryId == 1 then
		NewSceneId = YX_LAIYIN_SCENE_ID2
		YX_LAIYIN_HUMAN_NUM2 = YX_LAIYIN_HUMAN_NUM2 + 1
	elseif countryId == 2 then
		NewSceneId = YX_KUNLUN_SCENE_ID2
		YX_KUNLUN_HUMAN_NUM2 = YX_KUNLUN_HUMAN_NUM2 + 1
	elseif countryId == 3 then
		NewSceneId = YX_DUNHUANG_SCENE_ID2
		YX_DUNHUANG_HUMAN_NUM2 = YX_DUNHUANG_HUMAN_NUM2 + 1
	end
	local PosX = 67
	local PosZ = 63
	
	NewWorld(sceneId, selfId, NewSceneId,PosX ,PosZ, 310034 )

end



