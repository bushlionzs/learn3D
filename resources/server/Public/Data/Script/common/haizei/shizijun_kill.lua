x300561_g_BonusHonor = 10
x300561_g_BossBonusHonor = 200
x300561_g_KillNum = 0
x300561_money = 500000
x300561_g_SceneMonsterCount = 30
x300561_g_MsgFightSucess = "�ݱ�!�ڽ�������ֵ�ʮ�־��Ѿ����ҹ���ʿ���𣬹�������ʿ�����ǣ�Ӣ��������ս��Ʒ���������������Ǯ����500����"
x300561_g_MsgBossMerge	=	"���������µ�ʮ�־�֮���������˽������128��128�����������ʱ��ֹ��������������룡"
x300561_g_SceneMonsterType = 3061
x300561_g_KillScriptId = 300561
x300561_BossPos = {x=128,	z=128}

function x300561_OnDie ( sceneId , selfId , idkill )
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
						nShengWang = nShengWang + x300561_g_BonusHonor
						SetShengWang( sceneId, teamOther, nShengWang )
						Msg2Player(sceneId, teamOther, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BonusHonor),4,2)
						Msg2Player(sceneId, teamOther, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BonusHonor),4,3)
					end
				end
			end
		else
			if idkill >= 0 then
					if GetHp(sceneId, idkill) > 0 then
						local nShengWang = GetShengWang( sceneId, idkill )
						nShengWang = nShengWang + x300561_g_BonusHonor
						SetShengWang( sceneId, idkill, nShengWang )
						Msg2Player(sceneId, idkill, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BonusHonor),4,2)
						Msg2Player(sceneId, idkill, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BonusHonor),4,3)
					end
			end
		end
		if HZ_KILL_COUNT >= x300561_g_SceneMonsterCount then
			local monsterObj, monsterGuid = CreateMonster(sceneId,x300561_g_SceneMonsterType, x300561_BossPos.x,x300561_BossPos.z, 1,-1, x300561_g_KillScriptId,-1,21, 1800*1000);
			HZ_MONSTER_BOSSOBJ = monsterObj
			if sceneId == 19 then
				LuaAllScenceM2Wrold(sceneId, x300561_g_MsgBossMerge, 4, 1)
				LuaAllScenceM2Wrold(sceneId, x300561_g_MsgBossMerge, 1, 1)
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
						nShengWang = nShengWang + x300561_g_BossBonusHonor
						SetShengWang( sceneId, teamOther, nShengWang )
						Msg2Player(sceneId, teamOther, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BossBonusHonor),4,2)
						Msg2Player(sceneId, teamOther, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BossBonusHonor),4,3)
					end
				end
			end
		else
			if idkill >= 0 then
					if GetHp(sceneId, idkill) > 0 then
						local nShengWang = GetShengWang( sceneId, idkill )
						nShengWang = nShengWang + x300561_g_BossBonusHonor
						SetShengWang( sceneId, idkill, nShengWang )
						Msg2Player(sceneId, idkill, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BossBonusHonor),4,2)
						Msg2Player(sceneId, idkill, format("#Y���#R����%d��#Y�Ľ���", x300561_g_BossBonusHonor),4,3)
					end
			end
		end
		if sceneId == 19 then
		  if idkill >= 0 then
				local nCountry = GetCurCountry(sceneId, idkill)
				local str = ""
				if nCountry == 0 then
					str = "¥������"
				elseif nCountry == 1 then
					str = "��ɽ����"
				elseif nCountry == 2 then
				  str = "��������"
				elseif nCountry == 3 then
				  str = "�ػ�����"
				end
				local strText = format( "�ڽ�������ֵ�ʮ�־��Ѿ���%s��ʿ����,������Ǯ����500����", str )
				LuaAllScenceM2Wrold(sceneId, strText, 4, 1)
				LuaAllScenceM2Wrold(sceneId, strText, 1, 1)
				AddCountryResourceEx(sceneId, nCountry, 2, x300561_money)
			end
		end
		GamePlayScriptLog(sceneId, idkill, 492)
		HZ_KILL_MONSTERBOSS = 1
		HZ_MONSTER_BOSSOBJ  = -1
	end

	for i=1,x300561_g_SceneMonsterCount do
	    if HZ_MONSTER_OBJ[i] == selfId then
	    	HZ_MONSTER_OBJ[i] = -1
	    end
  end
end

function x300561_getKillNum ( )
	return HZ_KILL_COUNT
end

function x300561_clearKillNum ( )
	HZ_KILL_COUNT = 0
	HZ_MONSTER_BOSSOBJ = -1
	for i=1,x300561_g_SceneMonsterCount do
	    HZ_MONSTER_OBJ[i] = -1
  end
end