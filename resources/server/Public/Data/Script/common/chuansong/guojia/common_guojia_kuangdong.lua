
--脚本号
x550404_g_ScriptId = 550404
--任务文本描述
x550404_g_MissionName = "【屠城战】传送"

x550404_g_Bianjing2Midao_Entry_X    = 68
x550404_g_Bianjing2Midao_Entry_Z    = 106
x550404_g_Midao2Wangcheng1_Entry_X  = 128
x550404_g_Midao2Wangcheng1_Entry_Z  = 98
x550404_g_Wangcheng2Midao1_Entry_X  = 20
x550404_g_Wangcheng2Midao1_Entry_Z  = 106
x550404_g_Wangcheng2Midao2_Entry_X  = 70
x550404_g_Wangcheng2Midao2_Entry_Z  = 21
x550404_g_Wangcheng2Midao3_Entry_X  = 100
x550404_g_Wangcheng2Midao3_Entry_Z  = 20

x550404_g_npcId ={
				{npcId = 129711},
				{npcId = 129712},
				{npcId = 129713},
				{npcId = 129747},
				{npcId = 129748},
				{npcId = 129749},
				{npcId = 129721},
				{npcId = 129722},
				{npcId = 129723},
				{npcId = 129725},
				{npcId = 129726},
				{npcId = 129727},
                 }
				 

x550404_g_EnterEnmyWangchengNPC1 = { {191,219},{66,228},{194,214},{74,218}}
x550404_g_EnterEnmyWangchengNPC2 =  { {209,37},{27,25},{213,36},{55,30}}
x550404_g_EnterEnmyWangchengNPC3 = { {66,179},{66,179},{186,73},{186,73}}                   
x550404_g_ReturnSelfBianjin  = { {41,218},{210,200},{39,44},{210,38}}
x550404_g_ReturnSelfWangcheng  = { {127,136},{127,136},{127,116},{127,116}}

x550404_g_Gdao2DigongNpc1   = { {164,122},{194,165},{194,107},{191,96}}
x550404_g_Gdao2DigongNpc2   = { {75,182},{70,159},{116,54},{104,57}}
x550404_g_Gdao2DigongNpc3   = { {65,66},{200,103},{65,155},{68,202}}
x550404_g_Time				= { min = 2000,max = 2059 }	--时间限制

function x550404_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    local npcId = GetMonsterGUID( sceneId, targetId)
    local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
	for i,itm in x550404_g_npcId do
		if npcId == itm.npcId and camp > 0 then
			if GetLevel( sceneId, selfId) >= 40 then
				AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国迷宫", 3, 1)
			end
		end
	end
	
	local hour,minute,sec =GetHourMinSec(); --检查时间是否正确
	local now = hour *100 + minute
	if now < x550404_g_Time.min or now > x550404_g_Time.max then
		return
	end	
		if npcId == 129715 and camp >0 and GetLevel( sceneId, selfId) >= 40 then
			AddQuestNumText( sceneId, x550404_g_ScriptId, "进入敌国古道", 3, 3)
		elseif npcId == 129716 and camp >0 and GetLevel( sceneId, selfId) >= 40 then
			AddQuestNumText( sceneId, x550404_g_ScriptId, "进入敌国古道", 3, 4)
		elseif npcId == 129718 and camp >0  and GetLevel( sceneId, selfId) >= 40 then
			AddQuestNumText( sceneId, x550404_g_ScriptId, "进入敌国外城", 3, 8)
		elseif npcId == 129712 and camp >= 0 and GetLevel( sceneId, selfId) >= 40 then
			
			-- 攻方只能从配对的防守方的王城返回密道
			local nCountryID = GetCurCountry( sceneId, selfId)
			local nMatchCountryId = CallScriptFunction(310150,"GetMatchCountry", sceneId,selfId)
						
			-- if camp == 1 and sceneId ~= nCountryID * 100 + 50 and nCountryID == nMatchCountryId then 
				-- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回密道", 3, 5)
			-- end
			
			if camp == 1 and sceneId == nCountryID * 100 + 50 then
				AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国迷宫", 3, 10)
			end
			
		elseif npcId == 129713 and camp >= 0 and GetLevel( sceneId, selfId) >= 40 then
			
			-- 攻方只能从配对的防守方的王城返回密道
			local nCountryID = GetCurCountry( sceneId, selfId)
			local nMatchCountryId = CallScriptFunction(310150,"GetMatchCountry", sceneId,selfId)
						
			-- if camp == 1 and sceneId ~= nCountryID * 100 + 50 and nCountryID == nMatchCountryId then 
				-- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回密道", 3, 6)
			-- end
		elseif npcId == 129717 and camp >= 0 and GetLevel( sceneId, selfId) >= 40 then
			
			-- 攻方只能从配对的防守方的王城返回密道
			local nCountryID = GetCurCountry( sceneId, selfId)
			local nMatchCountryId = CallScriptFunction(310150,"GetMatchCountry", sceneId,selfId)
						
			-- if camp == 1 and sceneId ~= nCountryID * 100 + 50 and nCountryID == nMatchCountryId then 
				-- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回密道", 3, 9)
			-- end
		end
	-- if npcId == 129714 then
        -- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国王城", 3, 7)
    -- elseif npcId == 129715 then
        -- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国王城", 3, 7)
    -- elseif npcId == 129716 then
        -- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国王城", 3, 7)
    -- elseif npcId == 129718 then
    	-- AddQuestNumText( sceneId, x550404_g_ScriptId, "返回本国王城", 3, 7)
    -- end
end

function x550404_ProcEventEntry( sceneId, selfId, targetId, idScript, idExt)
    local name = GetName( sceneId, selfId)
    if idExt == 1 then
        if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_CRASHBOX) > 0 then
            LuaScenceM2Player( sceneId, selfId, "运镖状态不能返回本国迷宫", name, 3, 1)
            return
        end
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then
			local nCountry = GetCurCountry( sceneId, selfId )
			local npcId = GetMonsterGUID( sceneId, targetId)
			if npcId == 129747 then
				local x = x550404_g_Gdao2DigongNpc2[nCountry+1][1] + random(2,4)
				local z = x550404_g_Gdao2DigongNpc2[nCountry+1][2] + random(2,4)
				NewWorld( sceneId, selfId, nCountry * 100 + 104, x, z, 550404 )
			end
			if npcId == 129748 then
				local x = x550404_g_Gdao2DigongNpc3[nCountry+1][1] + random(2,4)
				local z = x550404_g_Gdao2DigongNpc3[nCountry+1][2] + random(2,4)
				NewWorld( sceneId, selfId, nCountry * 100 + 104, x, z, 550404 )
			end
			if npcId == 129749 then
				local x = x550404_g_Gdao2DigongNpc1[nCountry+1][1] + random(2,4)
				local z = x550404_g_Gdao2DigongNpc1[nCountry+1][2] + random(2,4)
				NewWorld( sceneId, selfId, nCountry * 100 + 104, x, z, 550404 )
			end
			
        end
    elseif idExt == 2 then
    	local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
    	--if camp >= 0 then
			local nCountry = GetCurCountry( sceneId, selfId)
			local x = x550404_g_ReturnSelfBianjin[nCountry+1][1] + random(2,4)
			local z = x550404_g_ReturnSelfBianjin[nCountry+1][2] + random(2,4)
        	NewWorld( sceneId, selfId, nCountry * 100 + 51, x , z, 550404 )
        --end
    elseif idExt == 3 then
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 0 then           -- 返回本国王城
            NewWorld( sceneId, selfId, GetCurCountry( sceneId, selfId) * 100 + 50, x550404_g_Midao2Wangcheng1_Entry_X + random( 2, 4), x550404_g_Midao2Wangcheng1_Entry_Z + random( 2, 4), 550404 )
        elseif camp == 1 then       -- 去敌国王城
			local MatchCountry = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
			if MatchCountry < 0 or MatchCountry > 3 then
				return
			end
			
			local x = x550404_g_EnterEnmyWangchengNPC1[MatchCountry+1][1] + random(2,4)
			local z = x550404_g_EnterEnmyWangchengNPC1[MatchCountry+1][2] + random(2,4)
			
			
			if  MatchCountry == 0 then --去楼兰
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z , 550404 )
			elseif  MatchCountry == 1 then -- 去天山
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z, 550404 )
			elseif  MatchCountry == 2 then -- 去昆仑
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x ,z, 550404 )
			elseif  MatchCountry == 3 then -- 去墩煌
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z, 550404 )
			end
        end
    elseif idExt == 4 then
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then     -- 去敌国王城
          local MatchCountry = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
			if MatchCountry < 0 or MatchCountry > 3 then
				return
			end
			
			local x = x550404_g_EnterEnmyWangchengNPC2[MatchCountry+1][1] + random(2,4)
			local z = x550404_g_EnterEnmyWangchengNPC2[MatchCountry+1][2] + random(2,4)
			
			if  MatchCountry == 0 then --去楼兰
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z , 550404 )
			elseif  MatchCountry == 1 then -- 去天山
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z, 550404 )
			elseif  MatchCountry == 2 then -- 去昆仑
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x ,z, 550404 )
			elseif  MatchCountry == 3 then -- 去墩煌
				NewWorld( sceneId, selfId, MatchCountry * 100 + 86, x, z, 550404 )
			end
        end
     elseif idExt == 8 then
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then     -- 去敌国王城
           local MatchCountry = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
			if MatchCountry < 0 or MatchCountry > 3 then
				return
			end
			
			local x = x550404_g_EnterEnmyWangchengNPC3[MatchCountry+1][1] + random(2,4)
			local z = x550404_g_EnterEnmyWangchengNPC3[MatchCountry+1][2] + random(2,4)
			
			if  MatchCountry == 0 then --去楼兰
				NewWorld( sceneId, selfId, MatchCountry * 100 + 58, x, z , 550404 )
			elseif  MatchCountry == 1 then -- 去天山
				NewWorld( sceneId, selfId, MatchCountry * 100 + 58, x, z, 550404 )
			elseif  MatchCountry == 2 then -- 去昆仑
				NewWorld( sceneId, selfId, MatchCountry * 100 + 58, x ,z, 550404 )
			elseif  MatchCountry == 3 then -- 去墩煌
				NewWorld( sceneId, selfId, MatchCountry * 100 + 58, x, z, 550404 )
			end
        end
    elseif idExt == 5 then        -- 返回密道
        if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_CRASHBOX) > 0 then
            LuaScenceM2Player( sceneId, selfId, "运镖状态不能返回本国迷宫", name, 3, 1)
            return
        end
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then       -- 
           local nCountry = GetCurCountry( sceneId, selfId )
			local x = x550404_g_Gdao2DigongNpc2[nCountry+1][1] + random(2,4)
			local z = x550404_g_Gdao2DigongNpc2[nCountry+1][2] + random(2,4)
        	NewWorld( sceneId, selfId, nCountry * 100 + 104, x, z, 550404 )
        end
    elseif idExt == 6 then        -- 返回密道
        if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_CRASHBOX) > 0 then
            LuaScenceM2Player( sceneId, selfId, "运镖状态不能返回本国迷宫", name, 3, 1)
            return
        end
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then       -- 
            local nCountry = GetCurCountry( sceneId, selfId )
			local ChuansongID = x550404_g_Gdao2DigongNpc1
				local x = ChuansongID[nCountry+1][1] + random(2,4)
				local z = ChuansongID[nCountry+1][2] + random(2,4)
				NewWorld( sceneId, selfId, nCountry * 100 + 104, x, z, 550404 )
        end
    elseif idExt == 9 then        -- 返回密道
        if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_CRASHBOX) > 0 then
            LuaScenceM2Player( sceneId, selfId, "运镖状态不能返回本国迷宫", name, 3, 1)
            return
        end
        local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then       -- 
            NewWorld( sceneId, selfId, CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId) * 100 + 104, x550404_g_Wangcheng2Midao3_Entry_X + random( 2, 4), x550404_g_Wangcheng2Midao3_Entry_Z + random( 2, 4), 550404 )
        end
    elseif idExt == 7 then
        
        local nCountryId = GetCurCountry( sceneId,selfId)
        local nTargetSceneId = nCountryId * 100 + 50
        
--        local poslist = {{255,155},{112,109},{259,311}}
--        local nPosIndex = random(1,3)
--        
--        local x = poslist[nPosIndex][1] + random(-1,1)
--        local z = poslist[nPosIndex][2] + random(-1,1)
        
		local x = x550404_g_ReturnSelfWangcheng[nCountryId+1][1] + random(2,4)
		local z = x550404_g_ReturnSelfWangcheng[nCountryId+1][2] + random(2,4)
		NewWorld( sceneId, selfId, nCountryId * 100 + 50, x , z, 550404 )
        
    elseif idExt == 10 then
    	
    	--从本国王城返回本国迷宫
    	local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
        if camp == 1 then
	        	
	    	local nMatchCountryID = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
	    	local nTargetSceneId = nMatchCountryID*100 + 104
	    	local x = x550404_g_Wangcheng2Midao1_Entry_X + random( 2, 4)
	    	local z = x550404_g_Wangcheng2Midao1_Entry_Z + random( 2, 4)
	    	
	    	NewWorld( sceneId, selfId, nTargetSceneId, x, z, 550404 )    	
    	end
    end

    return 1
end

--********************
--检测接受条件
--**********************************
function x550404_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x550404_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x550404_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550404_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550404_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550404_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

