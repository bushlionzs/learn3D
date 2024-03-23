--广播海贼信息

--脚本号
x300552_g_ScriptId = 300552
x300552_g_KillScriptId = 300551
x300552_money = 500000
x300552_g_SceneMonsterCount = 30
x300552_g_MsgFightFail = "王城戍边军统领：很遗憾！英雄们奋力的抵抗未能阻止他们的疯狂进攻，残暴的十字军突破我国的防线，大量的财物被劫掠，国库金钱损失500两"
x300552_g_MsgFightBossFail = "王城戍边军统领：我军浴血奋战，最终让十字军溃军阵亡，但却让罪恶滔天的十字军领袖逃逸！"
x300552_g_MsgFightSucess = "王城戍边军统领：捷报！十字军已经全部被消灭，国家民众士气高涨，英雄们所得战利品不计其数，国库金钱增加500两"

function x300552_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )
	local nCount = getn( HZ_MONSTER_OBJ )
  if nCount == 0 then
  	return
  end
  if sceneId == 50 then
  	local CountryGold = GetCountryResourceEx(sceneId, 0, 2)
  	if HZ_KILL_MONSTERBOSS < 1 then
			local IsHavecommonMonster = 0
			for i=1,nCount do
	    			if HZ_MONSTER_OBJ[i] >= 0 then
	    				DeleteMonster(sceneId, HZ_MONSTER_OBJ[i])
							HZ_MONSTER_OBJ[i] = -1
							IsHavecommonMonster = 1
	    			end
      end
	    if HZ_MONSTER_BOSSOBJ >= 0 then
	    		DeleteMonster(sceneId, HZ_MONSTER_BOSSOBJ)
					HZ_MONSTER_BOSSOBJ = -1
	    end
	    if IsHavecommonMonster > 0 then
					SubCountryResourceEx(sceneId, 0, 2, x300552_money)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 0, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 0, 1, 1)
			else
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 0, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 0, 1, 1)
	    end
		end
  elseif sceneId == 150 then
  	local CountryGold = GetCountryResourceEx(sceneId, 1, 2)
  	if HZ_KILL_MONSTERBOSS < 1 then
  		local IsHavecommonMonster = 0
			for i=1,nCount do
	    			if HZ_MONSTER_OBJ[i] >= 0 then
	    				DeleteMonster(sceneId, HZ_MONSTER_OBJ[i])
							HZ_MONSTER_OBJ[i] = -1
							IsHavecommonMonster = 1
	    			end
      end
      if HZ_MONSTER_BOSSOBJ >= 0 then
	    		DeleteMonster(sceneId, HZ_MONSTER_BOSSOBJ)
					HZ_MONSTER_BOSSOBJ = -1
	    end
	    if IsHavecommonMonster > 0 then
					SubCountryResourceEx(sceneId, 1, 2, x300552_money)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 1, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 1, 1, 1)
			else
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 1, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 1, 1, 1)
	    end
		end
  elseif sceneId == 250 then
  	local CountryGold = GetCountryResourceEx(sceneId, 2, 2)
  	if HZ_KILL_MONSTERBOSS < 1 then
  		local IsHavecommonMonster = 0
			for i=1,nCount do
	    			if HZ_MONSTER_OBJ[i] >= 0 then
	    				DeleteMonster(sceneId, HZ_MONSTER_OBJ[i])
							HZ_MONSTER_OBJ[i] = -1
							IsHavecommonMonster = 1
	    			end
      end
      if HZ_MONSTER_BOSSOBJ >= 0 then
	    		DeleteMonster(sceneId, HZ_MONSTER_BOSSOBJ)
					HZ_MONSTER_BOSSOBJ = -1
	    end
	    if IsHavecommonMonster > 0 then
					SubCountryResourceEx(sceneId, 2, 2, x300552_money)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 2, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 2, 1, 1)
			else
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 2, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 2, 1, 1)
	    end
		end
  elseif sceneId == 350 then
  	local CountryGold = GetCountryResourceEx(sceneId, 3, 2)
		if HZ_KILL_MONSTERBOSS < 1 then
			local IsHavecommonMonster = 0
			for i=1,nCount do
	    			if HZ_MONSTER_OBJ[i] >= 0 then
	    				DeleteMonster(sceneId, HZ_MONSTER_OBJ[i])
							HZ_MONSTER_OBJ[i] = -1
							IsHavecommonMonster = 1
	    			end
     end
     if HZ_MONSTER_BOSSOBJ >= 0 then
	    		DeleteMonster(sceneId, HZ_MONSTER_BOSSOBJ)
					HZ_MONSTER_BOSSOBJ = -1
	   end
	   if IsHavecommonMonster > 0 then
					SubCountryResourceEx(sceneId, 3, 2, x300552_money)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 3, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightFail, 3, 1, 1)
		 else
		 			LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 3, 4, 1)
					LuaAllScenceM2Country(sceneId, x300552_g_MsgFightBossFail, 3, 1, 1)
	   end
		end
  end
end


--活动的Tick
function x300552_ProcTiming( sceneId, actId, uTime )
end