
--脚本号
x310400_g_ScriptId = 310400

--任务文本描述
x310400_g_MissionName="抢滩东瀛岛传入"

--x310400_g_MD_AcceptTime = MD_YAOXIE_DIGONG_TIME

x310400_g_MaxHuman = 100
x310400_g_MaxHumanOther = 200

x310400_g_BuffId = 7061
x310400_g_ItemId = 12030030
x310400_g_MissionId = 9400

function x310400_IsOpenedTime()
	local minute = GetMinOfDay();
	if (minute >=7*60 and minute<=7*60+4) or ( minute>=11*60 and minute<=11*60+4 ) or (minute>=15*60 and minute<=15*60+4) or 
		(minute >=19*60 and minute<=19*60+4) or (minute >=22*60+30 and minute<=22*60+4+30) then
		return 1
	end

	return -1

end

function x310400_HaveAccepted(sceneId, selfId)
	
	local lastDay = GetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3])
	if lastDay == GetDayOfYear() then
		return 1
	end
	return -1
end

function x310400_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetLevel(sceneId, selfId) < 75 then
		return
	end
    AddQuestNumText(sceneId,x310400_g_ScriptId,"抢滩东瀛岛(75级)",14,-1)
     
end


function x310400_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )
	
		BeginQuestEvent(sceneId)
		  local Readme_1 = "#Y【抢滩东瀛岛】#r"
		  local Readme_2 = "#W\t每天的#G7:00#W，#G11:00#W，#G15:00#W，#G19:00#W和#G22:30#W，大元水师会对东瀛周边小岛开始抢滩作战。"
		  local Readme_3 = "#W\n\t在那时，我可以给持有#G勇武之证#W的勇士们加持#G勇武之力#W，极大地提升勇士们的力量和勇气。然而，长时间的加持勇武之力会给人带来永久的伤害，所以，每人#R每天只有#W一次#R加持的机会#W。"
		  local Readme_4 = "#W\n\t\n\t由于过多勇士的聚集可能并不利于战斗，通常只会选拔#R一百位#W勇士前往东瀛岛。但是如果你拥有#G混沌之星#W，我可以将你破例送到超过100人的岛上，这样东瀛岛上将最多可以有#R两百人#W同时作战。\n\t#G（请注意：抢滩登陆和妖邪地宫共享任务次数）"
		  local Readme = Readme_1..Readme_2..Readme_3..Readme_4
			AddQuestText(sceneId,Readme)
			EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId,selfId,targetId,x310400_g_ScriptId,-1)

	return 

end

--********************
--检测接受条件
--**********************************
function x310400_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x310400_IsGameTime()
	local minute = GetMinOfDay();
	if (minute >=7*60 and minute<=7*60+20) or ( minute>=11*60 and minute<=11*60+20 ) or (minute>=15*60 and minute<=15*60+20) or 
		(minute >=19*60 and minute<=19*60+20) or (minute >=22*60+30 and minute<=22*60+20+30) then
		return 1
	end
	return -1
end

--**********************************
--接受
--**********************************
function x310400_ProcAccept( sceneId, selfId )
	
	if GetLevel( sceneId, selfId ) < 75 then
	
		Msg2Player(sceneId,selfId,"等级不够，无法进入",8,3)		
		Msg2Player(sceneId,selfId,"等级不够，无法进入",8,2)
		return
	end

	if x310400_IsGameTime() < 0 then
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,3)		
			Msg2Player(sceneId,selfId,"不是在活动时间内",8,2)
			return
	end
	
	local bHave = 0
	if GetItemCount(sceneId, selfId, 11990100)  > 0 then
		bHave = 1
	end

	if x310400_HaveAccepted(sceneId, selfId) > 0 then
		
		Msg2Player(sceneId,selfId,"一天只能进入一次东瀛岛，或者妖邪地宫",8,3)		
		Msg2Player(sceneId,selfId,"一天只能进入一次东瀛岛，或者妖邪地宫",8,2)
		return 
	end

	if bHave == 0 then
		if GetItemCount(sceneId, selfId, x310400_g_ItemId)  == 0 then
			Msg2Player(sceneId,selfId,"你没有勇武之证，但拥有混沌之星，也可以进入",8,3)		
			Msg2Player(sceneId,selfId,"你没有勇武之证，但拥有混沌之星，也可以进入",8,2)
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
		curNum = QT_LOULAN_HUMAN_NUM 
	elseif countryId == 1 then
		curNum = QT_LAIYIN_HUMAN_NUM
	elseif countryId == 2 then
		curNum = QT_KUNLUN_HUMAN_NUM 
	elseif countryId == 3 then
		curNum = QT_DUNHUANG_HUMAN_NUM 
	end
	local sign = 0;
	
	if curNum < x310400_g_MaxHuman then
		
			if GetItemCount(sceneId, selfId, x310400_g_ItemId)  > 0 then
				sign = 1
			else
				if bHave > 0 then
					sign =2;
				end
			end
		
	elseif curNum >= x310400_g_MaxHuman and curNum < x310400_g_MaxHumanOther then
		
		if bHave  > 0 then
			sign =2;	
		else	
			Msg2Player(sceneId,selfId,"东瀛岛已超过百人，无法进入",8,3)	
			Msg2Player(sceneId,selfId,"东瀛岛已超过百人，无法进入",8,2)
			return
		end

	 
	else	
		Msg2Player(sceneId,selfId,"东瀛岛已达二百人，无法进入",8,3)	
		Msg2Player(sceneId,selfId,"东瀛岛已达二百人，无法进入",8,2)
		return

	end

	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3], GetDayOfYear())
	SetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_MINUTE[1], MD_YAOXIE_DIGONG_MINUTE[2], MD_YAOXIE_DIGONG_MINUTE[3], GetMinOfDay())


	if sign == 0 then
		return
	elseif sign == 1 then
		DelItem(sceneId, selfId, x310400_g_ItemId, 1)
	elseif sign == 2 then
		DelItem(sceneId, selfId, 11990100, 1)
	end
	

	local NewSceneId;
	if countryId == 0 then
		NewSceneId = QT_LOULAN_SCENE_ID
		QT_LOULAN_HUMAN_NUM = QT_LOULAN_HUMAN_NUM + 1
	elseif countryId == 1 then
		NewSceneId = QT_LAIYIN_SCENE_ID
		QT_LAIYIN_HUMAN_NUM = QT_LAIYIN_HUMAN_NUM + 1
	elseif countryId == 2 then
		NewSceneId = QT_KUNLUN_SCENE_ID
		QT_KUNLUN_HUMAN_NUM = QT_KUNLUN_HUMAN_NUM + 1
	elseif countryId == 3 then
		NewSceneId = QT_DUNHUANG_SCENE_ID
		QT_DUNHUANG_HUMAN_NUM = QT_DUNHUANG_HUMAN_NUM + 1
	end

	local PosX = 70
	local PosZ = 128
	
	NewWorld(sceneId, selfId, NewSceneId,PosX ,PosZ, 310400 )
end
function x310400_CanEnter(sceneId, selfId)

	local lastDay = GetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_DAY[1], MD_YAOXIE_DIGONG_DAY[2], MD_YAOXIE_DIGONG_DAY[3])
	local minute = GetQuestData(sceneId, selfId, MD_YAOXIE_DIGONG_MINUTE[1], MD_YAOXIE_DIGONG_MINUTE[2], MD_YAOXIE_DIGONG_MINUTE[3])

	if lastDay ~= GetDayOfYear() then
		return -1
	end
	
	local curMin = GetMinOfDay()
	if (minute >=7*60 and minute<=7*60+20) then
		if curMin > 7*60+20 then
			return -1
		end
	elseif( minute>=11*60 and minute<=11*60+20 ) then
		if curMin > 11*60+20 then
			return -1
		end
	elseif (minute>=15*60 and minute<=15*60+20) then
		if curMin > 15*60+20 then
			return -1
		end
	elseif (minute>=19*60 and minute<=19*60+20) then
		if curMin > 19*60+20 then
			return -1
		end
	elseif (minute>=22*60+30 and minute<=22*60+20+30) then
		if curMin > 22*60+20+30 then
			return -1
		end
		
	end

	return 1
end


function x310400_EnterScene(sceneId, selfId)
	
	if sceneId == QT_LOULAN_SCENE_ID or 
		sceneId == QT_LAIYIN_SCENE_ID or
		sceneId == QT_KUNLUN_SCENE_ID or
		sceneId == QT_DUNHUANG_SCENE_ID then
		local countryId = GetCurCountry(sceneId, selfId)
		local PosX = 150
		local PosZ = 181
		
		if x310400_CanEnter(sceneId, selfId) < 0 then
			NewWorld(sceneId, selfId, 15,PosX ,PosZ, 310400 )
		end
		if IsHaveQuestNM( sceneId, selfId, x310400_g_MissionId ) == 0 then
			local ret = AddQuestNM( sceneId, selfId, x310400_g_MissionId ) -- 给玩家添加任务
		end

		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x310400_g_BuffId, 0)
		GamePlayScriptLog(sceneId, selfId, 531)

	end

end



