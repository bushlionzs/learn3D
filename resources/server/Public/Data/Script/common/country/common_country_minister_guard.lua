--国家大臣警卫脚本
x310102_g_scriptId 		= 310102
x310102_g_guardGuid 	= {129721,129722,129723,129724,129725}
x310102_g_minsterGuid	= 129720
x310102_g_Time			= { min = 1200,max = 2359 }
x310102_g_DieMessage	= "#R敌方人多势众，御前护卫已经战死，#Y朵尔只殿下#R#aB{goto_%d,%d,%d}(%d,%d)#aE危在旦夕！殿下遇害国王将会被解除职务，请全体国民火速前往增援！"
--x310102_g_AllDieMessage	= "所有警卫死亡"



----------------------------------------------------------------------------------------------
--检查本周是否已经杀过了
----------------------------------------------------------------------------------------------
function x310102_CheckWeekValid( nPreTime )
	
	if nPreTime < 0 then
		return 1
	end
	
	local nTime = GetCurrentTime()
	local nTime = nTime - nPreTime
	if nTime >= 7*24*3600 then
		return 1
	end
	
	return 0
end

function x310102_GetCountryParam( nSelfCountry )
	
	return CD_INDEX_MINSTER_KILLDATE
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310102_ProcEventEntry( sceneId ,selfId, npcId )
end


function x310102_OnDie( sceneId,selfId,killerId )

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
--	if now < x310102_g_Time.min or now > x310102_g_Time.max then
		
--		return
--	end
	
	--取得国家信息	
	local nCountry = -1
	if sceneId == 51 then
		nCountry = 0
	elseif sceneId == 151 then
		nCountry = 1
	elseif sceneId == 251 then
		nCountry = 2
	elseif sceneId == 351 then
		nCountry = 3
	else
		return
	end
	
	
	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local name = GetName(sceneId,killerId)
		local msg = "很遗憾，目前该国没有国王。"
		LuaScenceM2Player(sceneId,killerId,msg,name,2,1)
		LuaScenceM2Player(sceneId,killerId,msg,name,3,1)
		return
	end
	

	--查询今天有没有杀过
	local playerGUID = GetPlayerGUID(sceneId,killerId)
	if playerGUID == nil then
		playerGUID = -1
	end
	local playerCountry = GetCurCountry(sceneId,killerId)
	local playerCP = x310102_GetCountryParam(nCountry)
	GetCountryQuestDataNM(sceneId,playerGUID,nCountry, playerCP, x310102_g_scriptId,-1,"OnReturn",1)
	
end

function x310102_OnReturn( sceneId, selfId,MissionData,MissionId )

	--玩法没有开放
	if GetGameOpenById(1026) <= 0 then
		return
	end
	
	--检查次数
	if x310102_CheckWeekValid(MissionData ) ~= 1 then
		
		local name = GetName(sceneId,selfId)
		local msg = "#R一周之内击杀#Y朵尔只#R只能导致该国国王下台一次。"
		local msg3 ="#R击杀无效！"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg3,name,3,1)
		
		return
	end
	
	--检查时间
	local hour,minute,sec =GetHourMinSec();
	local now = hour *100 + minute
	if now < x310102_g_Time.min or now > x310102_g_Time.max then
		
		local name = GetName(sceneId,selfId)
		local msg = "#R在12：00-0：00期间击杀#Y朵尔只#R才会导致该国国王下台。"
		local msg2 ="#R时间错误！"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg2,name,3,1)
		
		return
	end
	

	--取得国家信息	
	local nCountry = -1
	if sceneId == 51 then
		nCountry = 0
	elseif sceneId == 151 then
		nCountry = 1
	elseif sceneId == 251 then
		nCountry = 2
	elseif sceneId == 351 then
		nCountry = 3
	else
		return
	end
	
	
	--检查是否有国王
	local nKingGUID = CountryGetKingGUID(nCountry)
	if nKingGUID == -1 then
		local name = GetName(sceneId,selfId)
		local msg = "很遗憾，目前该国没有国王。"
		LuaScenceM2Player(sceneId,selfId,msg,name,2,1)
		LuaScenceM2Player(sceneId,selfId,msg,name,3,1)
		return
	end
	
	
	--检查minster是否活着
--	local misterId = FindMonsterByGUID(sceneId,x310102_g_minsterGuid)
--	if IsObjValid(sceneId,misterId) ~= 1 or GetHp(sceneId,misterId) <= 0 then
--		return
--	end
	
	
	
	--检查是否是这几个NPC死亡
--	local bAllDie = 0
--	local npcGUID = GetMonsterGUID(sceneId,selfId)
--	for i,item in x310102_g_guardGuid do
--		local objId = FindMonsterByGUID(sceneId,item)
--		if IsObjValid(sceneId,objId ) ~= 1 or GetHp(sceneId,objId) <= 0 then
--			bAllDie = bAllDie + 1
--		end
--	end
	
	
	--如果是这几个NPC死亡,检查其他NPC是否死亡,并发出警报
	local msg = format(x310102_g_DieMessage,sceneId,96,100,96,100)
	local msg1 ="#R御前护卫战死！"
	
	LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
	LuaAllScenceM2Country( sceneId,msg1,nCountry, 3,1)
	
	--记录玩法日志
	GamePlayScriptLog(sceneId,selfId,1311)
						
	
end
