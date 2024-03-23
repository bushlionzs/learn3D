--功能：战车的默认脚本
--帮会镖车发布

x300872_g_ScriptId = 300872
x300872_g_MissionName = "创建镖车"

--无敌impact在表中的索引,玩家进入BUS后获得一个无敌impact,
x300872_g_GodIndex = 1210
x300872_g_Carinfo = {CarType = 4,BaseAI = 3,AIScript = 3,Script = 300872 }

x300872_g_CostMoney = 10000
--**********************************

--任务入口函数

--**********************************

function x300872_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

end

--**********************************

--列举事件

--**********************************
function x300872_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--AddQuestNumText(sceneId, x300872_g_ScriptId, x300872_g_MissionName);
end


function x300872_OnCreateBus( sceneId, selfId,MissionId )

  local PosX,PosZ = GetWorldPos(sceneId, selfId)
	local ObjID = CreateBus(sceneId, x300872_g_Carinfo.CarType, PosX, PosZ, x300872_g_Carinfo.BaseAI, x300872_g_Carinfo.AIScript, x300872_g_Carinfo.Script, selfId, x300872_g_GodIndex,MissionId,-1)
end

--创建busd成功处理
function x300872_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)	

		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)
		
		--镖车与主人的绑定关系未建立成功前的安全状态
		SetBusCurCamp(sceneId, busId,20)
end


function x300872_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x300872_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经在护送神兽中");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"这神兽已经有人护送了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end


function x300872_OnIntoBusAfter(sceneId, selfId,BusID)
	AcceptGuildConvoy( sceneId, selfId,BusID )
	local CarName = GetName( sceneId, selfId ).."的神兽"
	SetBusTitle(sceneId , BusID, CarName)
	local GuildId = GetGuildID(sceneId, selfId)
	local Guildname = GetGuildName(GuildId)
	local msg = format(""..Guildname.."帮主成功领取神兽！")
	LuaThisScenceM2Guild(sceneId,msg,GuildId,5,1)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--玩家离开BUS
--selfId：玩家ID
function x300872_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在护送神兽，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
end


function x300872_OnTime(sceneId,BusId)

end

function x300872_OnLifeTimeOut(sceneId,BusId)

	AbandonGuildConvoyQuest(sceneId, BusId,7)
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--当前时间(天)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	DeleteBus(sceneId, BusId,1)
end

function x300872_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x300872_OnWaitTimeOut(sceneId,BusId)
	
	AbandonGuildConvoyQuest(sceneId, BusId,6)	
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--当前时间(天)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	DeleteBus(sceneId, BusId,1)
	
end

function x300872_OnDie(sceneId,BusId,idKiller)

	AbandonGuildConvoyQuest(sceneId, BusId,5)
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--当前时间(天)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)

	if idKiller == -1 then
		--自死亡，目前只用于将玩家投入监狱前删除镖车
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "您护送的神兽被杀死"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "神兽被被杀死！");DispatchQuestTips(sceneId,OwnerID);EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--无效OBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "您护送的神兽被杀死"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "神兽被杀死!");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)

	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			--状态不正常
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
				local Readme = "您护送的神兽被杀死"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "神兽被杀死!");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --被玩家杀死 
		local OwnerCountry = GetBusCountryID(sceneId,BusId)
		local KillerCountry = GetCurCountry(sceneId,idKiller)
		if OwnerCountry == KillerCountry then

			--PK惩罚
			local IsPunish = 0
			local OwnerId = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerId ~= -1 then
				local IsPunish = CallScriptFunction( SCENE_SCRIPT_ID, "CashboxComputePKPunish", sceneId, OwnerId, idKiller )
				if IsKing( sceneId, idKiller ) ~= 1 and IsPunish == 1 then
					--非国王并且PK惩罚值大于0
					CallScriptFunction( SCENE_SCRIPT_ID, "KillerEnterPrison", sceneId, idKiller )
					IsPunish = 1
				else
					IsPunish = 0
				end
			end
			
			if IsPunish==1 then
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的神兽，您的PK值增加了");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"您击杀了本国的神兽，您的PK值增加了",8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了本国的神兽");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"您击杀了本国的神兽",8,2)			
			end			

		else
	        AddMoney(sceneId,idKiller,0,x300872_g_CostMoney)
		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "您击杀了敌国的神兽，并获得了奖励！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("您击杀了敌国的神兽，并获得了现银#{_MONEY%d}。", x300872_g_CostMoney),8,2)	
		end 
	
		local Country = "楼兰王国"
		if KillerCountry == 0 then
			Country = "楼兰王国"
		elseif KillerCountry == 1 then
			Country = "天山王国"
		elseif KillerCountry == 2 then
			Country = "昆仑王国"
		elseif KillerCountry == 3 then
			Country = "敦煌王国"
		else
			return
		end

		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then		
			
			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local GuildTitle1 = GetGuildTitle(sceneId,OwnerID)
			local killerName = GetName(sceneId,idKiller)
			local Readme = "神兽被"..Country..GuildTitle.."的玩家"..killerName.."摧毁，全体护送成员任务失败！"
			msg1 = "天山王国"..GuildTitle1.."的神兽被"..Country..GuildTitle.."的"..killerName.."击杀"
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "神兽被"..HIDE_NAME.."摧毁，全体护送成员任务失败！"
			end
			
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "神兽被摧毁！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,6,1)
		end
	else			--被怪物杀死
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "神兽被怪物杀死，全体护送成员任务失败！"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "神兽被杀死！");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,6,1)		
		end

	end
	
end

