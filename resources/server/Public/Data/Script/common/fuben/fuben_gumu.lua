---------------------------------------------------
-- File: 700021_fuben_GUMU_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700021_CSP_FUBENTYPE				= 	0
x700021_CSP_SCRIPTID				=	1
x700021_CSP_TICKCOUNT				= 	2
x700021_CSP_FROMSCENEID				= 	3
x700021_CSP_ISCLOSING				= 	4
x700021_CSP_LEAVECOUNTDOWN			= 	5
x700021_CSP_TEAMID					=	6
x700021_CSP_BACKSCENEX       		=   7
x700021_CSP_BACKSCENEZ      		=   8
x700021_CSP_FUBENLEVEL			=	9

x700021_CSP_KILLCOUNT				=	20
x700021_CSP_FINAL_BOSS_ID			=   21
x700021_CSP_FUBEN_SCENE_ID			=	22
x700021_CSP_AREA_TIMER				=	23
x700021_CSP_B_GROWPOINT_SHUAGUAI	=	24
x700021_CSP_B_GROWPOINT_BOSS		=	25
x700021_CSP_FINAL_BOSS2_ID			=	26
x700021_CSP_CAN_KILL_FINAL_BOSS		=	27
x700021_CSP_GROWPOINT_BOSS_ID		=	28
x700021_CSP_GP_BOXID1				=	29
x700021_CSP_GP_BOXID2				=	30

x700021_CSP_BROTHER_FULL_HP_START	=	40
x700021_CSP_BROTHER_TALK_START		=	45

x700021_CSP_GROWPOINT_MONSTER_COUNT	=	50
x700021_CSP_GROWPOINT_MONSTER_START	=	51

x700021_CSP_FINAL_BOSS_BROTHER_COUNT=   60
x700021_CSP_FINAL_BOSS_BROTHER_ID_START=	61
x700021_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START=	70

x700021_CSP_SHUAGUAI_AREA_START		=	100
x700021_CSP_OBJID_AREA				=	120


x700021_CSP_B_GUOYUN_START			=	221
x700021_CSP_B_GATHERED2_START		=	227
x700021_CSP_B_GATHERED_START		=	233

x700021_CSP_B_GROWPOINT_OVER		=	239
x700021_CSP_HUMAN_COUNT				=	240
x700021_CSP_OBJID_START				=	241
x700021_CSP_GUID_START              =   248

x700021_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700021_g_ScriptId 					= 700021

---------------------- special for fuben -----------------------

x700021_g_Buff_Id					=	14110                   --进入第一个区域给予的buff

x700021_g_AreaTimer                 =   2000                    --事件区定时器
x700021_g_RandomMonsterRate			=	0                       --隐藏boss出现几率
x700021_g_Boss_Brother_Relive_Time	=	6*5/2                       --守护npc重生时间

x700021_g_nGrowpointType			=	538                     --boss掉落生长点id
x700021_g_nGrowpointType2			=	537                     --boss掉落生长点id


x700021_g_SubmitNPC                 =   { type =25027,guid= 150527,x = 71, z=28, facedir =0, title="" }



-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700021_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

	
end


function x700021_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700021_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700021_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	local index = x700021_CSP_OBJID_AREA
	for i=index,index+11 do

		SetFubenData_Param(sceneId, i, -1 )
	end

	
	x700021_CreateBoss( sceneId, 0 )
	x700021_CreateBossBrother(sceneId, -1)
	x700021_CreateMonster( sceneId )
	x700021_CreateRandomMonster(sceneId)

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700021_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		--SetFubenData_Param(sceneId, x700021_CSP_OBJID_START+i, humanId);

		local bGuoyun = CountryIsFortuneTime(sceneId,humanId,4)
		SetFubenData_Param(sceneId, x700021_CSP_B_GUOYUN_START+i, 0);--bGuoyun
	end

	SetFubenData_Param(sceneId, x700021_CSP_FUBEN_SCENE_ID,sceneId)


		
end



function x700021_EnterTick(sceneId, nowTickCount)

	x700021_OnAreaTimer( sceneId )

	local bCanKillFinalBoss = GetFubenData_Param(sceneId,x700021_CSP_CAN_KILL_FINAL_BOSS)

	if bCanKillFinalBoss<=0 then
		local nBossBrotherCount = GetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_BROTHER_COUNT )


		if nBossBrotherCount>0 then
			for i=0, nBossBrotherCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_ID_START+i)
				if nMonsterId== -1 then
					local nTickCount = GetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i)+1
					
					SetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, nTickCount)

					if nTickCount == x700021_g_Boss_Brother_Relive_Time then
						x700021_CreateBossBrother(sceneId, i)

						local humancount = GetFuben_PlayerCount(sceneId);
						for	j = 0, humancount - 1 do
							local humanId = GetFuben_PlayerObjId(sceneId, j);
							local str = format("盗墓寻宝师复生！", i);
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, str);
							EndQuestEvent(sceneId);
							DispatchQuestTips(sceneId, humanId);
						end
					end
				elseif nMonsterId>=0 then
					
					--// add in 2009-3-2 for The 2nd Internal Test
					local nCurrentHp = GetHp( sceneId, nMonsterId )
					local nFullHp = GetFubenData_Param(sceneId, x700021_CSP_BROTHER_FULL_HP_START+i )
					local bTalked = GetFubenData_Param(sceneId, x700021_CSP_BROTHER_TALK_START+i )

					if bTalked<=0 then
						if nCurrentHp/nFullHp <=0.5 then
							SetFubenData_Param(sceneId, x700021_CSP_BROTHER_TALK_START+i,1 )
							x700021_BrotherSay(sceneId,nMonsterId)
						end
					end
					--// add end
					

				end


				end
			end
		end
end

function x700021_BrotherSay(sceneId,nMonsterId)
	if nMonsterId<0 then
		return
	end

	local nTextCount = 4;
	
	local listNpcTalkText = {
		"个个击破对我们来说，是徒劳的！",
		"我不是一个人在战斗，我不是一个人！",
		"我们4个是密不可分的整体！",
		"除非你有三头六臂，能同时向我们4人发起攻击！",
	}

	local nIndex = random(1,nTextCount)

	NpcTalk(sceneId, nMonsterId, listNpcTalkText[nIndex],  -1)


end

function x700021_CreateBoss(sceneId, nFlag)


	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local nRet=0;
			if nFlag ==0 then
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, 7, aiscript, x700021_g_ScriptId, -1, -1, -1, facedir,  "",title)  -- 阵营为-1. 一开始打不了
				else
					nRet = CreateMonster(sceneId, type, x, z, 7, aiscript, x700021_g_ScriptId, -1, -1, -1, facedir)  -- 阵营为-1. 一开始打不了
				end

				SetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_ID, nRet )
			else
				
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21, -1, facedir,  "",title)  -- 阵营为-1. 一开始打不了
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21, -1, facedir)  -- 阵营为-1. 一开始打不了
				end

				SetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS2_ID, nRet )
			end
			
			
			break
			
        end
	end

	if nFlag ==1 then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "古察愤怒了！" ;
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end
	end

end

function x700021_CreateRandomMonster(sceneId)



	local rate = random(0,100)/100;
	if rate>= x700021_g_RandomMonsterRate then
		return 0;
	end



	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;


	
	local bCreated =0;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local nRet = 0
				
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir)
				
				end

				if patrolid>=0 then
					SetPatrolId(sceneId, nRet, patrolid)
					
				end
            end
        end
	end

	

end

function x700021_CreateBossBrother(sceneId, nTargetFlag)


	if nTargetFlag == nil then
		nTargetFlag = -1;
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;


	local nCount =0
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			
			
			if nTargetFlag == flag or nTargetFlag == -1 then
				local nRet = 0
				
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1,facedir)
				
				end


				SetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_BROTHER_ID_START+flag, nRet )
				SetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+flag, 0 )
				nCount = nCount +1

				
				--// add in 2009-3-2 for The 2nd Internal Test
				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700021_CSP_BROTHER_FULL_HP_START+flag, nFullHp )
				SetFubenData_Param(sceneId, x700021_CSP_BROTHER_TALK_START+flag, 0 )
				--// add end

			end
			
        end
	end

	if nTargetFlag==-1 then

		SetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_BROTHER_COUNT, nCount )
	end

	

end



---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700021_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir)
				
				end
			end
        end
	end

end

function x700021_CreateAreaMonster(sceneId, areaId)
	
	local bCreated = GetFubenData_Param(sceneId,x700021_CSP_SHUAGUAI_AREA_START+areaId)


	if bCreated>0 then
		return
	end

	SetFubenData_Param(sceneId,x700021_CSP_SHUAGUAI_AREA_START+areaId, 1)

	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            if areaId == flag1 then
				for j=0,count -1 do

					local rx = random(-r,r)
					local x = x + rx
					local rz = random(-r,r)
					local z = z + rz

					if title~="" then
						CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1, facedir,  "",title)
					else
						CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1, facedir)
					
					end
				end
			end
        end
	end

--	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = " ";
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end



end


function x700021_CreateGrowPointMonster(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700021_CSP_B_GROWPOINT_SHUAGUAI)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1, facedir)
				end

				SetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_START+nCount, nRet)
				nCount = nCount +1;

			end
			
        end
	end

	SetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_COUNT, nCount)

	SetFubenData_Param(sceneId,x700021_CSP_B_GROWPOINT_SHUAGUAI, 1)

--	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = " ";
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end
end

function x700021_CreateGrowPointBoss(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700021_CSP_B_GROWPOINT_BOSS)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700021_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_BOSS_ID, nRet)
				nCount = nCount +1;
				break
			end
			
        end
	end



	SetFubenData_Param(sceneId,x700021_CSP_B_GROWPOINT_BOSS, 1)

--	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = " ";
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end
end

function x700021_OnEnterShuaguaiArea(sceneId, selfId, areaId)
	
	
	if areaId<1 or areaId>9 then
		return
	end

	
	local bCreated = GetFubenData_Param(sceneId,x700021_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	x700021_CreateAreaMonster(sceneId, areaId)
end


function x700021_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700021_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700021_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	

	local nGrowPointMonsterCount = GetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_COUNT)

	local bGrowPoint = GetFubenData_Param(sceneId,x700021_CSP_B_GROWPOINT_SHUAGUAI)

	if bGrowPoint>0 then
		if nGrowPointMonsterCount>0 then
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_START+i)
				
				if nMonsterId== selfId then
					SetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_START+i, -1)
				end
			end
			
			local bAllDie=1;
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_START+i)
				if nMonsterId~= -1 then
					bAllDie = 0;
				end
			end

			if bAllDie==1 then
				SetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_MONSTER_COUNT, -1)
				x700021_CreateGrowPointBoss(sceneId)
			end

		end
	end




	local nBossBrotherCount = GetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS_BROTHER_COUNT )
	

	if nBossBrotherCount>0 then
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			
			if nMonsterId== selfId then
				SetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_ID_START+i, -1)
				
				
				SetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, 0)
			end
		end

		local bAllDie=1;
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			if nMonsterId~= -1 then
				bAllDie = 0;
			end
		end

		if bAllDie==1 then
			SetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_BROTHER_COUNT, -1)
			x700021_OnAllFinalBossBrotherDie(sceneId)
		end
	end

	local nFineBoss2Id = GetFubenData_Param(sceneId, x700021_CSP_FINAL_BOSS2_ID )

	if nFineBoss2Id>0 then
		if nFineBoss2Id == selfId then
			x700021_OnZhanShenDead( sceneId)

--			for	i = 0, 6 - 1 do
--				SetFubenData_Param(sceneId, x700021_CSP_B_GATHERED_START+i,0);
--			end
--
--			local x,z =GetWorldPos(sceneId,selfId)
--			SetGrowPointPos(sceneId,x700021_g_nGrowpointType,x,z)
--
--			SetGrowPointIntervalContainer(sceneId,x700021_g_nGrowpointType,1)
--			x700021_ShowTipsToAll(sceneId, "地上出现了一个奇异的箱子！")

--			--//--------------------------- 世界喊话 Start--------------------
--			-- final boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700021_CSP_TICKCOUNT)
--
--			local nowTime = x700021_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--			
--			
--			LuaAllScenceM2Wrold (sceneId,"#R盗墓者头领古察倒下的瞬间还在用贪婪的眼睛望着战神的棺木，#G"..strPlayerName.."#R带领的队伍用了#G"..strKillTime.."#R就让战神古墓恢复了以往的寂静。", 0, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------
		end
	end


	local nGrowPointId = GetFubenData_Param(sceneId,x700021_CSP_GROWPOINT_BOSS_ID)

	if nGrowPointId>0 then
		if nGrowPointId== selfId then
--			for	i = 0, 6 - 1 do
--				SetFubenData_Param(sceneId, x700021_CSP_B_GATHERED2_START+i,0);
--			end
--
--			local x,z =GetWorldPos(sceneId,selfId)
--			SetGrowPointPos(sceneId,x700021_g_nGrowpointType2,x,z)
--
--			SetGrowPointIntervalContainer(sceneId,x700021_g_nGrowpointType2,1)
--			x700021_ShowTipsToAll(sceneId, "地上出现了一个奇异的箱子！")

			--//--------------------------- 世界喊话 Start--------------------
			--死神 boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700021_CSP_TICKCOUNT)

--			local nowTime = x700021_g_TickTime* nowTickCount;

--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)

				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

			
			
--			LuaAllScenceM2Wrold (sceneId,x700021_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end

	
	 
end

function x700021_OnAllFinalBossBrotherDie(sceneId)
	local nBossId = GetFubenData_Param(sceneId,x700021_CSP_FINAL_BOSS_ID)
	
	SetFubenData_Param(sceneId,x700021_CSP_CAN_KILL_FINAL_BOSS, 1)
	DeleteMonster( sceneId,nBossId )
	x700021_CreateBoss(sceneId, 1)

end

function x700021_OnZhanShenDead( sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "战胜古察， 副本完成";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
	x700021_CreateSubmitNpc( sceneId)
end

function x700021_CreateSubmitNpc( sceneId)

	if x700021_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700021_g_SubmitNPC.type, x700021_g_SubmitNPC.x, x700021_g_SubmitNPC.z, 3, 0, -1, x700021_g_SubmitNPC.guid, -1, -1, x700021_g_SubmitNPC.facedir,  "",x700021_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700021_g_SubmitNPC.type, x700021_g_SubmitNPC.x, x700021_g_SubmitNPC.z, 3, 0, -1, x700021_g_SubmitNPC.guid, -1, -1, x700021_g_SubmitNPC.facedir)
		
	end

	--// add for 现金副本
	 --x700021_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700021_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700021_ShowTipsToAll(sceneId, "现金宝箱出现！")
	 end
	 --// add end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700021_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700021_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700021_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700021_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700021_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700021_g_ScriptId,nIndexFrom,i)
		if idScript == x700021_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700021_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end




---------------------------------------------------------------------------------------------------
--进入区域事件
---------------------------------------------------------------------------------------------------



---------------------------------------------------------------------------------------------------
function x700021_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700021_CSP_SCRIPTID);

	if nScriptId~=x700021_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaEntered", sceneId, selfId, zoneId, MissionId)
		return
	end
	--//add end
	
	--x700021_ShowTipsToAll(sceneId, format("ProcAreaEntered zoneId=%d",zoneId))

	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = format(" 进入%d",zoneId);
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end

	 --检查玩家GUID
    local nFind = 1
    local guid = GetPlayerGUID( sceneId,selfId )



    --not player
    if nFind == 0 then
		return
    end

	local index = x700021_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			SetFubenData_Param(sceneId, idx+1, zoneId )

	    	break
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        SetFubenData_Param(sceneId, idx+1, zoneId )
	        break
		end
	end

	

	if zoneId ==0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700021_g_Buff_Id,0 )
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, " ");
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, selfId);
	elseif zoneId >=1 and zoneId<=9 then
		x700021_OnEnterShuaguaiArea(sceneId, selfId, zoneId)
	end

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700021_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700021_CSP_SCRIPTID);

	if nScriptId~=x700021_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaLeaved", sceneId, selfId, zoneId, MissionId)
		return
	end
	--//add end

    local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = " ";
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
	end

	local index = x700021_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneId = GetFubenData_Param(sceneId, idx + 1 )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 )
	        SetFubenData_Param(sceneId, idx+1, -1 )
	    end
	end
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700021_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end



function x700021_OnAreaTimer( sceneId )


--	local bAreaTimer = GetFubenData_Param(sceneId, x700021_CSP_AREA_TIMER)
--	if bAreaTimer == -1 then
--	    return
--	end

	
    local index = x700021_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneid = GetFubenData_Param(sceneId, idx + 1 )

		--x700021_ShowTipsToAll(sceneId, format("objid=%d, zoneId=%d",objid,zoneid))
	    if objid ~= -1 then
			
			if zoneid>=10 and zoneid<=17 then  -- 10-17 area 玩家减血
				--检查玩家是否在线或是玩家是否死亡，如果都不是，那么，执行火烧减血逻辑CZG 2008-12-1
				local ErrorCode = CallScriptFunction( FUBEN_COMMON_SCRIPT_CALL, "IsPlayerErrorState", sceneId, objid)
				
				if ErrorCode == 0 then

					local hurt = 500
				   
					

					local havehp = GetHp( sceneId, objid )

					
					local hp = havehp - hurt
					if hp < 0 then
						hp = havehp -1
						hp = -hp
					else
						hp = -hurt
					end
					
					SetHp(sceneId,objid, hp )
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--定点使用物品任务
---------------------------------------------------------------------------------------------------
function x700021_PositionUseItem( sceneId, selfId, BagIndex, impactId )
end


---------------------------------------------------------------------------------------------------
--采集任务，打开采集点事件
---------------------------------------------------------------------------------------------------
function x700021_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
end





---------------------------------------------------------------------------------------------------
--打开后检查
---------------------------------------------------------------------------------------------------
function x700021_OpenCheck( sceneId, selfId, targetId )
end

function x700021_CloseTimer( sceneId, TimerIndex )
--	if TimerIndex ~= -1 then
--		StopTimer(sceneId, TimerIndex)
--	end
--	SetFubenData_Param(sceneId, x700021_CSP_AREA_TIMER, -1) ;
end

function x700021_OnGrowPoint(sceneId, selfId)
	local nFuben_SceneId = GetFubenData_Param(sceneId, x700021_CSP_FUBEN_SCENE_ID);--副本场景号
	if nFuben_SceneId ~= sceneId then
		return
	end

	x700021_CreateGrowPointMonster(sceneId)

	SetFubenData_Param(sceneId, x700021_CSP_B_GROWPOINT_OVER,1);
end




--------------------------------------------------------------------------------------
-- 生长点脚本
--------------------------------------------------------------------------------------


function x700021_OnCreate(sceneId,growPointType,x,y)
	
--	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)
--
--	if growPointType == x700021_g_nGrowpointType then
--		SetFubenData_Param(sceneId, x700021_CSP_GP_BOXID1, ItemBoxId);
--	elseif growPointType ==x700021_g_nGrowpointType2 then
--		SetFubenData_Param(sceneId, x700021_CSP_GP_BOXID2, ItemBoxId);
--	end
	

end



function x700021_OnOpen(sceneId,selfId,targetId)
	
	--return 0;
	
end

function x700021_OnRecycle(sceneId,selfId,targetId)
	
	--return 0;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700021_g_GrowpointId, x700021_g_ItemIndex )
end



function x700021_OnProcOver(sceneId,selfId,targetId)
	-- 采集完毕
--	
--	
--	
--	local nItemBoxId1 = GetFubenData_Param(sceneId, x700021_CSP_GP_BOXID1);
--	local nItemBoxId2 = GetFubenData_Param(sceneId, x700021_CSP_GP_BOXID2);
--
--	if nItemBoxId1 == targetId then
--		x700021_OnAnwer(sceneId,selfId)
--	elseif nItemBoxId2 == targetId then
--		x700021_OnAnwer2(sceneId,selfId)
--	end
	
	
	
	

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end


function x700021_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--function x700021_OnAnwer(sceneId,selfId)
--
----	BeginQuestEvent(sceneId);
----		AddQuestText(sceneId,"采集扎兰丁之魂掉落完成");
----	EndQuestEvent();
----	DispatchQuestTips(sceneId, selfId);
--
--	local myGuid = GetPlayerGUID( sceneId,selfId )
--	myGuid = format("%u", myGuid)	
--	for i=0, 5 do
--        local paramidx = 248 + i
--        local nGUID = GetFubenData_Param(sceneId, paramidx  )
--		nGUID = format("%u", nGUID)
--        if nGUID == myGuid then
--
--			local bGathered = GetFubenData_Param(sceneId, x700021_CSP_B_GATHERED_START+i);
--			local str ="";
--
--			if bGathered<=0 then
--				
--				
--				local bGuoyun =GetFubenData_Param(sceneId, x700021_CSP_B_GUOYUN_START+i);
--				local nSuccess,nCount = x700021_GetMyItemBonus(sceneId,selfId,bGuoyun,1);
--				
--				
--				if nSuccess==nCount then
--					str = format("奖励%d个龙眼石，成功获得并加入背包",nCount,nSuccess)
--					SetFubenData_Param(sceneId, x700021_CSP_B_GATHERED_START+i,1);
--				else
--					str = "背包空间不足，物品加入背包失败"
--				end
--				
--			else
--				str = "只能获得道具一次"
--			end
--
--			BeginQuestEvent(sceneId);
--				AddQuestText(sceneId,str);
--			EndQuestEvent();
--			DispatchQuestTips(sceneId, selfId);
--			break;
--           
--        end
--    end
--end
--
--function x700021_OnAnwer2(sceneId,selfId)
--
----	BeginQuestEvent(sceneId);
----		AddQuestText(sceneId,"采集恶灵王掉落完成");
----	EndQuestEvent();
----	DispatchQuestTips(sceneId, selfId);
--
--	local myGuid = GetPlayerGUID( sceneId,selfId )
--	myGuid = format("%u", myGuid)
--	for i=0, 5 do
--        local paramidx = 248 + i
--        local nGUID = GetFubenData_Param(sceneId, paramidx  )
--				nGUID = format("%u", nGUID)
--        if nGUID == myGuid then
--
--			local bGathered = GetFubenData_Param(sceneId, x700021_CSP_B_GATHERED2_START+i);
--			
--			local str ="";
--
--			if bGathered<=0 then
--				
--				
--				local bGuoyun =GetFubenData_Param(sceneId, x700021_CSP_B_GUOYUN_START+i);
--				local nSuccess,nCount = x700021_GetMyItemBonus(sceneId,selfId,bGuoyun,2);
--				
--				if nSuccess==nCount then
--					str = format("奖励%d个龙眼石，成功获得并加入背包",nCount,nSuccess)
--					SetFubenData_Param(sceneId, x700021_CSP_B_GATHERED2_START+i,1);
--				else
--					str = "背包空间不足，物品加入背包失败"
--				end
--				
--				
--				
--			else
--				str = "只能获得道具一次"
--			end
--
--			BeginQuestEvent(sceneId);
--				AddQuestText(sceneId,str);
--			EndQuestEvent();
--			DispatchQuestTips(sceneId, selfId);
--			break;
--           
--        end
--    end
--end
--
--function x700021_GetMyItemBonus(sceneId,selfId,bGuoyun, nType)
--
--	local nLevel = GetLevel(sceneId,selfId)
--
--	local nCount = 2;
--
--	if nType==1 then
--		nCount = 2
--	elseif nType==2 then
--		nCount = 1
--	else
--		return
--	end
--
--	local itemId = 0;
--
--	if nType==1 then
--
--		if nLevel>=30 and nLevel <=50 then
--			itemId = 11050001
--		elseif nLevel>=51 and nLevel <=70 then
--			itemId = 11050002
--		elseif nLevel>=71 and nLevel <=100 then
--			itemId = 11050003
--		else
--			return
--		end
--	elseif nType==2 then
--		if nLevel>=30 and nLevel <=50 then
--			itemId = 11050001
--		elseif nLevel>=51 and nLevel <=70 then
--			itemId = 11050002
--		elseif nLevel>=71 and nLevel <=100 then
--			itemId = 11050003
--		else
--			return
--		end
--	end
--
--	if bGuoyun==1 then
--		nCount = nCount*3
--	end
--
--
--	if nType==1 then
--		nCount = nCount + random(-1,1)
--	end
--	
--	local nSuccess = 0;
--
--	--for i=1, nCount do
--		BeginAddItem(sceneId)
--		AddItem( sceneId, itemId, nCount )
--		local ret = EndAddItem(sceneId,selfId)
--		if ret > 0 then
--			AddItemListToPlayer(sceneId,selfId)
--			nSuccess = nCount
--		end
--	--end
--	
--	
--
--
--	return nSuccess,nCount;
--end
