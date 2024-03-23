--国家大臣脚本
x310101_g_scriptId 				= 310101					--本脚本
x310101_g_minsterGuid			= 129720					--国家大臣GUID
x310101_g_Time					= { min = 1930,max = 2259 }	--时间限制
--x310101_g_guardGuid 			= {129721,129722,129723,129724,129725}
--x310101_g_DieMessage			= "#Y战神之旗#R轰然倒下，长生天震怒，万民哗变，国王被剥夺了王位！"		--国家大臣被杀提示
x310101_g_DieLog				= "Minister = 310101, sceneId=%d,Country = %d,kingGUID=%X ,killerGUID=%X"
x310101_g_PreTime				=  0						
x310101_g_AreaTipsInterval		=  2						--区域事件间隔
x310101_g_AreaTips				= "#R警报！警报！本国的#Y战神之旗#R#aB{goto_%d,%d,%d}(%d,%d)#aE正在遭受敌国的攻击，如果被敌国成功击倒旗帜，国王将会被剥夺王位，请全体国民火速前往增援！"	--进入区域提示
x310101_g_EnterDay					=	{1,2,3,4,5,6};


----------------------------------------------------------------------------------------------
--检查本周是否已经杀过了
----------------------------------------------------------------------------------------------
function x310101_CheckWeekValid( nPreTime )

	if nPreTime> 0 then
		local nTime = GetCurrentTime()/86400
		nTime = nTime - nPreTime
		if nTime < 7 then
			return 0
		end
		
		local bFind = -1
		local weekDay = GetWeek()
		
		for i, item in x310101_g_EnterDay do
			if weekDay==item then
				bFind = 1
				break;
			end
		end
		
		
		if bFind == -1 then
			return 0
		end
		
		return 1
	else
		
		local bFind = -1
		local weekDay = GetWeek()
		for i, item in x310101_g_EnterDay do
			if weekDay==item then
				bFind = 1
				break;
			end
		end
		
		
		if bFind == -1 then
			return 0
		end
		
		return 1
	end
	
end


function x310101_GetCountryParam( nSelfCountry )
	
	return CD_INDEX_MINSTER_KILLDATE
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310101_ProcEventEntry( sceneId ,selfId, npcId )
end


function x310101_ProcTiming( sceneId,now)
end

function x310101_OnDie( sceneId,selfId,killerId )

	--玩法没有开放
	if GetGameOpenById(1026) <= 0 then
		return
	end

	--检查类型
	local ObjType = GetObjType(sceneId, killerId)	
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
	--检查Killer的有效性
	if IsPlayerStateNormal(sceneId,killerId)~=1 then
		return
	end
	


	--检查时间
--	local hour,minute,sec =GetHourMinSec();
--	local now = hour *100 + minute
--	if now < x310101_g_Time.min or now > x310101_g_Time.max then
--		return
--	end

	--取得国家信息	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	

	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,killerId)
		local msg = "很遗憾，目前"..kingCountryName.."没有国王"
		LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		LuaScenceM2Player(sceneId,killerId,msg,name,3,1)
		return
	end

	--如果是同国,退出
	if nCountry == GetCurCountry(sceneId,killerId) then
		return
	end	
	
	--检查是否是这几个NPC死亡
	-- local bAllDie = 0
	-- local npcGUID = GetMonsterGUID(sceneId,selfId)
	-- for i,item in x310101_g_guardGuid do
		-- local objId = FindMonsterByGUID(sceneId,item)
		-- if IsObjValid(sceneId,objId ) ~= 1 or GetHp(sceneId,objId) <= 0 then
			-- bAllDie = bAllDie + 1
		-- end
	-- end
	
	-- if bAllDie < getn(x310101_g_guardGuid) then
		
		-- local name = GetName(sceneId,killerId)
		-- local msg = "很遗憾，您必须将朵尔只的卫士全部杀死后，击杀朵尔只才会颠覆该国国王的统治。"
		-- local msg6="#R未清除全部守卫！"
		-- LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		-- LuaScenceM2Player(sceneId,killerId,msg6,name,3,1)
		
		-- return
	-- end

	--查询今天有没有杀过
	local playerGUID = GetPlayerGUID(sceneId,killerId)
	if playerGUID == nil then
		playerGUID = -1
	end
	
	local playerCP = x310101_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310101_g_scriptId,-1,"OnReturn",1)
end

function x310101_OnReturn( sceneId, selfId,MissionData,MissionId )

	--玩法没有开放
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	--检查Killer的有效性
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end
	
	--检查次数
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	if x310101_CheckWeekValid(MissionData) ~= 1 then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,selfId)
		local msg = "#R一周之内摧毁#Y战神之旗#R只能导致"..kingCountryName.."国王下台一次，并且#G周日#R击杀无效。"
		local msg5="#R击杀无效！"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg5,name,3,1)
		return
	end
	
	

	--检查时间
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		local kingCountryName = GetCountryName(nCountry)
		local name = GetName(sceneId,selfId)
		local msg = "#R在19：30-23：00期间摧毁#Y战神之旗#R才能剥夺"..kingCountryName.."国王的王位。"
		local msg4= "#R时间错误！"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg4,name,3,1)
		return
	end
	
	
	
	--取得国家信息	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	--如果是同国,退出
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end
	
	--检查minster是否活着
	local misterId = FindMonsterByGUID(sceneId,x310101_g_minsterGuid)
	if IsObjValid(sceneId,misterId ) ~= 1 or GetHp(sceneId,misterId) <= 0 then
	
		local nTime = GetCurrentTime()/86400 	--这样是消除今天已经过的时间,让时间判断以日期为准
	
		--设置已经打过
		local playerCP = x310101_GetCountryParam(nCountry)
		SetCountryQuestData(sceneId,nCountry,playerCP,nTime,0)
		SetGuildQuestData(sceneId,GetCountryKingGuildIdNM(nCountry),GD_GUILD_INDEX_MINISTER_GUILD_DATE,nTime,0)
		
		--取消国王
		CancelKing(sceneId,selfId,nKingGUID,nCountry)
		
		--记日志
		local msg = format(x310101_g_DieLog,sceneId,nCountry,nKingGUID,GetPlayerGUID(sceneId,selfId) )
		WriteLog(1,msg);
	
		--提示
		local kingCountryName = GetCountryName(nCountry)
		local killerCountryName = GetCountryName(GetCurCountry( sceneId, selfId))
		local killerName = GetName( sceneId, selfId)
		local msg1 = format("#R%s的战神之旗已被%s#R的%s摧毁，国王被剥夺了王位！",kingCountryName,killerCountryName,killerName)
		local msg2 ="#R战神之旗被摧毁，国王被剥夺了王位！"
		LuaAllScenceM2Country( sceneId,x310101_g_DieMessage,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg2,nCountry, 2,1)
		LuaAllScenceM2Wrold(sceneId, msg1, 5, 1)
		
		--记录玩法日志
		GamePlayScriptLog(sceneId,selfId,1312)

	end
	
end

---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x310101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	

	--玩法没有开放
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	
	--检查Killer的有效性
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end
	
	
	--检查时间
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		return
	end

	
	--取得国家信息	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	
	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	
	
	
	--如果是同国进入区域,退出
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end
	
	

	
	--检查上一次提醒时间
	local nCurMin = GetMinOfYear()
	local nInterval = nCurMin - x310101_g_PreTime
	if nInterval < x310101_g_AreaTipsInterval then
		return	
	end
	
	

	
	--查询今天有没有杀过
	local playerGUID = GetPlayerGUID(sceneId,selfId)
	if playerGUID == nil then
		playerGUID = -1
	end
	local playerCP = x310101_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310101_g_scriptId,-1,"OnReturn2",1)
	
	
	--GetCountryQuestData(sceneId,selfId,playerCP, x310101_g_scriptId,-1,"OnReturn2",1)
end


function x310101_OnReturn2( sceneId, selfId,MissionData,MissionId )

	
	--玩法没有开放
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	
	--检查Killer的有效性
	if IsPlayerStateNormal(sceneId,selfId)~=1 then
		return
	end

	
	--检查时间
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310101_g_Time.min or now > x310101_g_Time.max then
		return
	end
	

	--检查本周是否已经杀过了
	if x310101_CheckWeekValid(MissionData) ~= 1 then
		return
	end
	
	
	
	--取得国家信息	
	local nCountry = -1
	if sceneId == 50 then
		nCountry = 0
	elseif sceneId == 150 then
		nCountry = 1
	elseif sceneId == 250 then
		nCountry = 2
	elseif sceneId == 350 then
		nCountry = 3
	else
		return
	end
	
	
	
	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		return
	end
	
	
	
	--如果是同国进入区域,退出
	if nCountry == GetCurCountry(sceneId,selfId) then
		return
	end	
	
	
	
	--检查上一次提醒时间
	local nCurMin = GetMinOfYear()
	local nInterval = nCurMin - x310101_g_PreTime
	if nInterval < x310101_g_AreaTipsInterval then
		return	
	end
	

	
	--保存时间
	x310101_g_PreTime = nCurMin
	
	--检查minster是否活着
	local misterId = FindMonsterByGUID(sceneId,x310101_g_minsterGuid)
	if IsObjValid(sceneId,misterId ) == 1 and GetHp(sceneId,misterId) > 0 then
	
		local msg = format( x310101_g_AreaTips,sceneId,284,189,284,189)
		local msg3 ="#R战神之旗受到敌国袭击！"
		
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
	
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x310101_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end