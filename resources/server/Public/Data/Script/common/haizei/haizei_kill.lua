x300551_g_BonusHonor = 10
x300551_g_BossBonusHonor = 200
x300551_g_KillNum = 0
x300551_money = 500000
x300551_g_SceneMonsterCount = 30
x300551_g_MsgFightSucess = "王城戍边军统领：捷报！十字军已经全部被消灭，国家民众士气高涨，英雄们所得战利品不计其数，国库金钱增加500两"
x300551_g_MsgBossMerge	=	"王城戍边军统领：警报！可怕的十字军领袖出现了，他正在指挥残余部队疯狂地向王城冲来，如果不及时阻止他，后果不堪设想！"
x300551_g_SceneMonsterType = 3061
x300551_g_KillScriptId = 300551
x300551_BossPos = {x=85,	z=314}

function x300551_OnDie ( sceneId , selfId , idkill )
	local isInTeam = HasTeam(sceneId , idkill)
	if selfId ~= HZ_MONSTER_BOSSOBJ then
		HZ_KILL_COUNT = HZ_KILL_COUNT + 1
		if isInTeam > 0 then
			local teamCount = GetNearTeamCount(sceneId , idkill)
			for i=0, teamCount-1 do
				local teamOther = GetNearTeamMember(sceneId , idkill, i)
				if teamOther >= 0 then
					if GetHp(sceneId, teamOther) > 0 then
						local nShengWang = GetShengWang( sceneId, teamOther )
						nShengWang = nShengWang + x300551_g_BonusHonor
						SetShengWang( sceneId, teamOther, nShengWang )
						Msg2Player(sceneId, teamOther, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BonusHonor),4,2)
						Msg2Player(sceneId, teamOther, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BonusHonor),4,3)
					end
				end
			end
		else
			if idkill >= 0 then
					if GetHp(sceneId, idkill) > 0 then
						local nShengWang = GetShengWang( sceneId, idkill )
						nShengWang = nShengWang + x300551_g_BonusHonor
						SetShengWang( sceneId, idkill, nShengWang )
						Msg2Player(sceneId, idkill, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BonusHonor),4,2)
						Msg2Player(sceneId, idkill, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BonusHonor),4,3)
					end
			end
		end
		if HZ_KILL_COUNT >= x300551_g_SceneMonsterCount then
			local monsterObj, monsterGuid = CreateMonster(sceneId,x300551_g_SceneMonsterType, x300551_BossPos.x,x300551_BossPos.z, 1,-1, x300551_g_KillScriptId,-1,21,1800*1000);
			HZ_MONSTER_BOSSOBJ = monsterObj
			if sceneId == 50 then
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 0, 4, 1)
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 0, 1, 1)
			elseif sceneId == 150 then
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 1, 4, 1)
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 1, 1, 1)
			elseif sceneId == 250 then
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 2, 4, 1)
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 2, 1, 1)
			elseif sceneId == 350 then
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 3, 4, 1)
				LuaAllScenceM2Country(sceneId, x300551_g_MsgBossMerge, 3, 1, 1)
			end
		end 
	else
		if isInTeam > 0 then
			local teamCount = GetNearTeamCount(sceneId , idkill)
			for i=0, teamCount-1 do
				local teamOther = GetNearTeamMember(sceneId , idkill, i)
				if teamOther >= 0 then
					if GetHp(sceneId, teamOther) > 0 then
						local nShengWang = GetShengWang( sceneId, teamOther )
						nShengWang = nShengWang + x300551_g_BossBonusHonor
						SetShengWang( sceneId, teamOther, nShengWang )
						Msg2Player(sceneId, teamOther, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BossBonusHonor),4,2)
						Msg2Player(sceneId, teamOther, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BossBonusHonor),4,3)
					end
				end
			end
		else
			if idkill >= 0 then
					if GetHp(sceneId, idkill) > 0 then
						local nShengWang = GetShengWang( sceneId, idkill )
						nShengWang = nShengWang + x300551_g_BossBonusHonor
						SetShengWang( sceneId, idkill, nShengWang )
						Msg2Player(sceneId, idkill, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BossBonusHonor),4,2)
						Msg2Player(sceneId, idkill, format("#Y获得#R声望%d点#Y的奖励", x300551_g_BossBonusHonor),4,3)
					end
			end
		end
		if sceneId == 50 then
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 0, 4, 1)
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 0, 1, 1)
			AddCountryResourceEx(sceneId, 0, 2, x300551_money)
		elseif sceneId == 150 then
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 1, 4, 1)
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 1, 1, 1)
			AddCountryResourceEx(sceneId, 1, 2, x300551_money)
		elseif sceneId == 250 then
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 2, 4, 1)
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 2, 1, 1)
			AddCountryResourceEx(sceneId, 2, 2, x300551_money)
		elseif sceneId == 350 then
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 3, 4, 1)
			LuaAllScenceM2Country(sceneId, x300551_g_MsgFightSucess, 3, 1, 1)
			AddCountryResourceEx(sceneId, 3, 2, x300551_money)
		end
		GamePlayScriptLog(sceneId, idkill, 492)
		HZ_KILL_MONSTERBOSS = 1
		HZ_MONSTER_BOSSOBJ  = -1
	end

	for i=1,x300551_g_SceneMonsterCount do
	    if HZ_MONSTER_OBJ[i] == selfId then
	    	HZ_MONSTER_OBJ[i] = -1
	    end
  end
end

function x300551_getKillNum ( )
	return HZ_KILL_COUNT
end

function x300551_clearKillNum ( )
	HZ_KILL_COUNT = 0
	HZ_MONSTER_BOSSOBJ = -1
	for i=1,x300551_g_SceneMonsterCount do
	    HZ_MONSTER_OBJ[i] = -1
  end
end