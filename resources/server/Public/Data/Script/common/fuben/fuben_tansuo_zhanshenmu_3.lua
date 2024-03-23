---------------------------------------------------
-- File: 
-- Author: Peng Lin
-- Created: 2010-03-18
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700086_CSP_FUBENTYPE				= 	0
x700086_CSP_SCRIPTID				=	1
x700086_CSP_TICKCOUNT				= 	2
x700086_CSP_FROMSCENEID				= 	3
x700086_CSP_ISCLOSING				= 	4
x700086_CSP_LEAVECOUNTDOWN			= 	5
x700086_CSP_TEAMID					=	6
x700086_CSP_TICKTIME				=	7
x700086_CSP_HOLDTIME				=	8
x700086_CSP_FUBENLEVEL				=	9

x700086_CSP_KILLCOUNT				=	20
x700086_CSP_FINAL_BOSS_ID			=   21
x700086_CSP_FUBEN_SCENE_ID			=	22
x700086_CSP_AREA_TIMER				=	23
x700086_CSP_B_GROWPOINT_SHUAGUAI	=	24
x700086_CSP_B_GROWPOINT_BOSS		=	25
x700086_CSP_FINAL_BOSS2_ID			=	26
x700086_CSP_CAN_KILL_FINAL_BOSS		=	27
x700086_CSP_GROWPOINT_BOSS_ID		=	28
x700086_CSP_GP_BOXID1				=	29
x700086_CSP_GP_BOXID2				=	30

x700086_CSP_BROTHER_FULL_HP_START	=	40
x700086_CSP_BROTHER_TALK_START		=	45

x700086_CSP_GROWPOINT_MONSTER_COUNT	=	50
x700086_CSP_GROWPOINT_MONSTER_START	=	51
x700086_CSP_GROWPOINT_MONSTER_END   =   59--最多刷9只怪

x700086_CSP_FINAL_BOSS_BROTHER_COUNT=   60
x700086_CSP_FINAL_BOSS_BROTHER_ID_START=	61
x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START=	70

x700086_CSP_AREA_ID					=   98
x700086_CSP_AREA_FLAG				=	99
x700086_CSP_SHUAGUAI_AREA_START		=	100
x700086_CSP_OBJID_AREA				=	120
x700086_CSP_XIANJINBOSS			= 121
x700086_CSP_BOSS1_SUB_MONSTER_FLAG				=	140
x700086_CSP_BOSS1_ID							=	141
x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT		=	142
x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT		=	143
x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT		=	144
x700086_CSP_BOSS1_SUB_MONSTER_ID_START			=	145	--目前共生成12个小怪
x700086_CSP_BOSS1_SUB_MONSTER_ID_END            =	156
x700086_CSP_RANDOM_BOSS_ID						=   157	--九旄战神
x700086_RANDOM_BOSS_FLAG                        =   158	--九旄战神 坐骑标识

x700086_CSP_B_GROWPOINT_OVER		=	239  -- 这个下标不能修改

x700086_CSP_HUMAN_COUNT				=	240
x700086_CSP_PLAYER_ENTER_START		=	241

x700086_CSP_LAST_TICKOUNT			=	247
x700086_CSP_GUID_START              =   248
x700086_CSP_FUBEN_TYPE				=	254	--三种类型 0:普通(队伍),1:试练,2:英雄

x700086_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700086_g_ScriptId 					= 700086
x700086_g_MissionId					= 6608
-------------------------fuben data begin-----------------------

x700086_g_Buff_Id					=	14110                   --进入第一个区域给予的buff

x700086_g_AreaTimer                 =   2000                    --事件区定时器
x700086_g_RandomMonsterRateList		=	{	--九旄战神出现几率
											0.05,   --普通模式
											0.15,  --三番模式
											0.67,  --黄金三番模式
										}
x700086_g_Boss_Brother_Relive_Time	=	6*8/2                       --守护npc重生时间

x700086_g_GrowpointId				=   500                     --生长点
x700086_g_nGrowpointType			=	538                     --boss掉落生长点id
x700086_g_nGrowpointType2			=	537                     --boss掉落生长点id

x700086_g_listBrotherSayText = {
								"个个击破对我们来说，是徒劳的！",
								"我不是一个人在战斗，我不是一个人！",
								"我们4个是密不可分的整体！",
								"除非你有三头六臂，能同时向我们4人发起攻击！",
								}

x700086_g_SubmitNPC                 =   { type =28509,guid= 150576,x = 71, z=28, facedir =0, title="" }
-------------------------fuben data end-----------------------


----------------------------------------------------------
--处理点击对话npc的事件
----------------------------------------------------------
function x700086_ProcEventEntry(sceneId,selfId,targetId)

end


-------------------------------------------------------------------------------
--当副本创建成功时， 开始刷怪和npc
-------------------------------------------------------------------------------
function x700086_OnFubenSceneCreated( sceneId )
	
	for i=20,239 do
		SetFubenData_Param(sceneId, i, -1 )
	end
	
	x700086_CreateMonster( sceneId )              --monsterFlag = 0和1
	x700086_CreateBoss1(sceneId)	              --monsterFlag =  3
	x700086_CreateBoss(sceneId, 0 )	              --final boss monsterFlag =  4
	x700086_CreateBossBrother(sceneId, -1)		  --monsterFlag =  5


	SetFubenData_Param(sceneId, x700086_CSP_FUBEN_SCENE_ID,sceneId)
		
end


-------------------------------------------------------------------------------
--副本心跳
-------------------------------------------------------------------------------
function x700086_EnterTick(sceneId, nowTickCount)

	x700086_OnAreaTimer( sceneId )

	local bCanKillFinalBoss = GetFubenData_Param(sceneId,x700086_CSP_CAN_KILL_FINAL_BOSS)

	if bCanKillFinalBoss<=0 then
		local nBossBrotherCount = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT )


		if nBossBrotherCount>0 then
			for i=0, nBossBrotherCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
				if nMonsterId== -1 then
					local nTickCount = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i)+1
					
					SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, nTickCount)

					if nTickCount == x700086_g_Boss_Brother_Relive_Time then
						x700086_CreateBossBrother(sceneId, i)

						local humancount = GetFuben_PlayerCount(sceneId);
						for	j = 0, humancount - 1 do
							local humanId = GetFuben_PlayerObjId(sceneId, j);
							local str = format("金王蛮守复生！", i);
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, str);
							EndQuestEvent(sceneId);
							DispatchQuestTips(sceneId, humanId);
						end
					end
				elseif nMonsterId>=0 then
					
					--// add in 2009-3-2 for The 2nd Internal Test
					local nCurrentHp = GetHp( sceneId, nMonsterId )
					local nFullHp = GetFubenData_Param(sceneId, x700086_CSP_BROTHER_FULL_HP_START+i )
					local bTalked = GetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+i )

					if bTalked<=0 then
						if nCurrentHp/nFullHp <=0.5 then
							SetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+i,1 )
							x700086_BrotherSay(sceneId,nMonsterId)
						end
					end
					--// add end
					

				end


				end
			end
		end

		--进入Area17后BOSS每十秒刷新2个小怪，共刷新12个小怪
		local bSubMonster = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_FLAG)
		if bSubMonster > 0 then
			local nBoss1ID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID)
			if nBoss1ID >= 0 then
				local nSubMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)
				local nSubMonsterLoopCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT)
				local nSubMonsterTickCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT)
				local nTickPassed = nowTickCount - nSubMonsterTickCount
				local nMaxNumber = 	x700086_CSP_BOSS1_SUB_MONSTER_ID_END - x700086_CSP_BOSS1_SUB_MONSTER_ID_START + 1
				if nSubMonsterCount < nMaxNumber then
					if nSubMonsterTickCount == 0 or nTickPassed == 2 then				
						x700086_CreateBoss1SubMonster(sceneId, nSubMonsterLoopCount)
						nSubMonsterLoopCount = nSubMonsterLoopCount + 1
						SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT,nSubMonsterCount )
						SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT,nowTickCount )
					end
				end
			end
		end

end

-------------------------------------------------------------------------------
--创建指定的boss
-------------------------------------------------------------------------------
function x700086_CreateBoss(sceneId, nFlag)


	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
		    local nObjId=0;
			if nFlag ==0 then
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, 7, aiscript, x700086_g_ScriptId, -1, -1, -1, facedir,  "",title)  -- 阵营为-1. 一开始打不了
				else
					nObjId = CreateMonster(sceneId, type, x, z, 7, aiscript, x700086_g_ScriptId, -1, -1, -1, facedir)  -- 阵营为-1. 一开始打不了
				end

				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_ID, nObjId )
			else
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1, facedir,  "",title)  -- 阵营为-1. 一开始打不了
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1, facedir)  -- 阵营为-1. 一开始打不了
				end

				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID, nObjId )
			end
			
			
			break
			
        end
	end

	if nFlag ==1 then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "完颜洪烈愤怒了！" ;
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end
	end

end
-------------------------------------------------------------------------------
--创建指定的brother boss
-------------------------------------------------------------------------------
function x700086_CreateBossBrother(sceneId, nTargetFlag)


	if nTargetFlag == nil then
		nTargetFlag = -1;
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount =0
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)

		if idScript == x700086_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
						
			if nTargetFlag == flag or nTargetFlag == -1 then
				local nObjId = 0
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1,facedir)
				
				end


				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_ID_START+flag, nObjId )
				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+flag, 0 )
				nCount = nCount +1

				local nFullHp = GetHp( sceneId, nObjId )
				SetFubenData_Param(sceneId, x700086_CSP_BROTHER_FULL_HP_START+flag, nFullHp )
				SetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+flag, 0 )

			end
			
        end
	end

	if nTargetFlag==-1 then

		SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT, nCount )
	end	

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700086_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and (monsterFlag == 1 or monsterFlag == 2) and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
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

---------------------------------------------------------------------------------------------------
--进入区域创建Monster
---------------------------------------------------------------------------------------------------
function x700086_CreateAreaMonster(sceneId, areaId)
	
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	SetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId, 1)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 10 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
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

end

---------------------------------------------------------------------------------------------------
--创建释放小怪的boss
---------------------------------------------------------------------------------------------------
function x700086_CreateBoss1(sceneId)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local bCreated =0;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then

		        local nObjId = -1
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
				
				end

				if patrolid>=0 then
					SetPatrolId(sceneId, nObjId, patrolid)
				end

			if nObjId >= 0 then
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_ID, nObjId)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT, 0)
			end

		end
	end	
end

---------------------------------------------------------------------------------------------------
--创建释放小怪的boss
---------------------------------------------------------------------------------------------------
function x700086_CreateBoss1SubMonster(sceneId,Index)



	local nCreateTotal = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)
	local nMaxCount    = x700086_CSP_BOSS1_SUB_MONSTER_ID_END - x700086_CSP_BOSS1_SUB_MONSTER_ID_START +1
	if nCreateTotal >= nMaxCount  then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	 
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)

		if idScript == x700086_g_ScriptId and monsterFlag == 3 and flag == Index and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
			for j=0,count -1 do

				local nTmpTotal = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)

				if nTmpTotal >= nMaxCount then
					return
				end

				local nObjId = -1
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
			
				end
				
				if nObjId >= 0 and patrolid >= 0 then
					SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_ID_START + nTmpTotal, nObjId)
					nTmpTotal = nTmpTotal + 1
					SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT,nTmpTotal)
					SetPatrolId(sceneId, nObjId, patrolid)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--brother说话
---------------------------------------------------------------------------------------------------
function x700086_BrotherSay(sceneId,nMonsterId)
	if nMonsterId<0 then
		return
	end

	local nTextCount = 4;
	

	local nIndex = random(1,nTextCount)

	NpcTalk(sceneId, nMonsterId, x700086_g_listBrotherSayText[nIndex],  -1)


end

---------------------------------------------------------------------------------------------------
--打开采集点后创建的怪	monsterFlag == 8
---------------------------------------------------------------------------------------------------
function x700086_CreateGrowPointMonster(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	local nMaxcount = x700086_CSP_GROWPOINT_MONSTER_END - x700086_CSP_GROWPOINT_MONSTER_START + 1

	for i = 0,nDataCount-1 do
		
		if nCount >= nMaxcount then
			break
		end

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 8 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            
			for j=0,count -1 do

				if nCount >= nMaxcount then
					break
				end

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nObjId = 0
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir)
				end

				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+nCount, nObjId)
				nCount = nCount +1;

			end
			
        end
	end

	SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT, nCount)

	SetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI, 1)

end

---------------------------------------------------------------------------------------------------
--创建采集点触发的隐藏boss
---------------------------------------------------------------------------------------------------
function x700086_CreateGrowPointBoss(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_BOSS)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 9 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nObjId = 0
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_BOSS_ID, nObjId)
				nCount = nCount +1;
				break
			end
			
        end
	end

	SetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_BOSS, 1)

end

---------------------------------------------------------------------------------------------------
--创建随机隐藏怪
---------------------------------------------------------------------------------------------------
function x700086_CreateRandomMonster(sceneId)

	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	if fuben_type ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700086_g_RandomMonsterRateList[1]
	local nFubenMode = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = x700086_g_RandomMonsterRateList[2]
	elseif nFubenMode ==2	then
		nStdRate = x700086_g_RandomMonsterRateList[3]
	end
	

	if rate >= nStdRate then
		return
	end
	
	local nFlag = random(0,3)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
			
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 and nFlag == flag then
		
			local rx = random(-r,r)
			local x = x1 + rx
			local rz = random(-r,r)
			local z = z1 + rz
			local nObjId = -1
			
			if title~="" then
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
			else
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
			
			end

			if nObjId >=0 then

				SetFubenData_Param(sceneId,x700086_CSP_RANDOM_BOSS_ID,nObjId)
				SetFubenData_Param(sceneId, x700086_RANDOM_BOSS_FLAG, nFlag)

				if patrolid>=0 then
					SetPatrolId(sceneId, nObjId, patrolid)	
				end
				x700086_ShowTipsToAll(sceneId, "战神再现！")
				return
			end

        end
	end

end

function x700086_ShowTipsToAll(sceneId, str)

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
---------------------------------------------------------------------------------------------------
--怪死处理事件
---------------------------------------------------------------------------------------------------
function x700086_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700086_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700086_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700086_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local nGrowPointMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT)

	local bGrowPoint = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI)

	if bGrowPoint>0 then
		if nGrowPointMonsterCount>0 then
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i)
				
				if nMonsterId== selfId then
					SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i, -1)
				end
			end
			
			local bAllDie=1;
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i)
				if nMonsterId >= 0 then
					bAllDie = 0;
				end
			end

			if bAllDie==1 then
				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT, -1)
				x700086_CreateGrowPointBoss(sceneId)
			end

		end
	end

	local nBossBrotherCount = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT )
	

	if nBossBrotherCount>0 then
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			
			if nMonsterId== selfId then
				SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i, -1)
				
				
				SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, 0)
			end
		end

		local bAllDie=1;
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			if nMonsterId~= -1 then
				bAllDie = 0;
			end
		end

		if bAllDie==1 then
			SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_COUNT, -1)
			x700086_OnAllFinalBossBrotherDie(sceneId)
		end
	end

	local nFineBoss2Id = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID )

	if nFineBoss2Id>=0 then
		if nFineBoss2Id == selfId then
			SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID, -2 )
			local humancount = GetFuben_PlayerCount(sceneId);
			for ii = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, ii);
				CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,55 )
			end	
		
				
			x700086_OnZhanShenDead( sceneId)

		end
	end


	local nGrowPointId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_BOSS_ID)

	if nGrowPointId>0 then
		if nGrowPointId== selfId then
		end
	end

	local nBoss1ID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID)
	if nBoss1ID>0 then
		if nBoss1ID == selfId then
			SetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID, -1)
			SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 0)
			local nSubMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)

			for i = 0, nSubMonsterCount -1 do
				local nSubMonsterID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i)
				if nSubMonsterID > 0 then

					DeleteMonster( sceneId,nSubMonsterID )		
				end
			end
		end
	end

	local nSubMonsterCount = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT )

	if nSubMonsterCount>0 then
		for i = 0, nSubMonsterCount - 1 do
			local nSubMonsterID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i)
			
			if nSubMonsterID == selfId then
				SetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i, -1)
			end
		end
	end

	x700086_OnRandomBossDie(sceneId, selfId, killerId)
end

---------------------------------------------------------------------------------------------------
--最后boss的所有brother死后处理
---------------------------------------------------------------------------------------------------
function x700086_OnAllFinalBossBrotherDie(sceneId)
	local nBossId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_ID)
	
	SetFubenData_Param(sceneId,x700086_CSP_CAN_KILL_FINAL_BOSS, 1)
	DeleteMonster( sceneId,nBossId )
	x700086_CreateBoss(sceneId, 1)

end

---------------------------------------------------------------------------------------------------
--最后的boss死后的处理
---------------------------------------------------------------------------------------------------
function x700086_OnZhanShenDead( sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "战胜完颜洪烈， 副本完成，请退出副本。";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	x700086_CreateRandomMonster(sceneId)

	x700086_CreateXianJinBoss(sceneId)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	
	--x700086_ShowTipsToAll(sceneId, "副本完成，请退出副本。")
	--x700086_CreateSubmitNpc( sceneId)
end

---------------------------------------------------------------------------------------------------
--创建任务完成npc
---------------------------------------------------------------------------------------------------
function x700086_CreateSubmitNpc( sceneId)

	if x700086_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700086_g_SubmitNPC.type, x700086_g_SubmitNPC.x, x700086_g_SubmitNPC.z, 3, 0, -1, x700086_g_SubmitNPC.guid, -1, -1, x700086_g_SubmitNPC.facedir,  "",x700086_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700086_g_SubmitNPC.type, x700086_g_SubmitNPC.x, x700086_g_SubmitNPC.z, 3, 0, -1, x700086_g_SubmitNPC.guid, -1, -1, x700086_g_SubmitNPC.facedir)
		
	end

	x700086_CreateXianJinBoss(sceneId)
		
	CallScriptFunction( 701104, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction( 701105, "OnSceneBossDie", sceneId, 2)
	
end

---------------------------------------------------------------------------------------------------
--创建现金boss
---------------------------------------------------------------------------------------------------

function x700086_CreateXianJinBoss(sceneId)

	local nFubenMode = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_MODE)

	if nFubenMode ~=1 and nFubenMode ~= 2 then
	  return
	end

	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	if fuben_type ~= 0 then
		return
	end

    local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
				
				end
				SetFubenData_Param(sceneId, x700086_CSP_XIANJINBOSS, nRet )
			end
        end
	end

	x700086_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end


---------------------------------------------------------------------------------------------------
--进入区域事件
---------------------------------------------------------------------------------------------------
function x700086_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700086_CSP_AREA_ID, zoneId)
	if zoneId == 18 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID)
		if BossId ~= -2 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700086_g_MissionId, x700086_g_ScriptId,1)
		
	elseif zoneId == 19 then 
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 1, x700086_g_MissionId, x700086_g_ScriptId)
	end
	local nScriptId = GetFubenData_Param(sceneId, x700086_CSP_SCRIPTID);

	if nScriptId~=x700086_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaEntered", sceneId, selfId, zoneId, MissionId)
		return
	end

	local humancount = GetFuben_PlayerCount(sceneId);

	local index = x700086_CSP_OBJID_AREA
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
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700086_g_Buff_Id,0 )
	elseif zoneId >=1 and zoneId<=9 then
		x700086_OnEnterShuaguaiArea(sceneId, selfId, zoneId)
	elseif zoneId == 17 then
		SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 1)
	end

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700086_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	local index = x700086_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneId = GetFubenData_Param(sceneId, idx + 1 )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 )
	        SetFubenData_Param(sceneId, idx+1, -1 )
	    end
	end
	SetFubenData_Param(sceneId, x700086_CSP_AREA_ID, -1)
end

---------------------------------------------------------------------------------------------------
--区域定时器,必需实现
---------------------------------------------------------------------------------------------------
function x700086_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700086_CSP_AREA_ID)
	if zoneId == 18 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID)
		if BossId ~= -2 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700086_g_MissionId, x700086_g_ScriptId,1)
		
	elseif zoneId == 19 then 
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 1, x700086_g_MissionId, x700086_g_ScriptId)
	end
end

---------------------------------------------------------------------------------------------------
--进入双怪区域的处理
---------------------------------------------------------------------------------------------------
function x700086_OnEnterShuaguaiArea(sceneId, selfId, areaId)
	
	
	if areaId<1 or areaId>9 then
		return
	end
	
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	x700086_CreateAreaMonster(sceneId, areaId)
end

---------------------------------------------------------------------------------------------------
--每个tick处理区域的逻辑
---------------------------------------------------------------------------------------------------
function x700086_OnAreaTimer( sceneId )
	
    local index = x700086_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneid = GetFubenData_Param(sceneId, idx + 1 )

	    if objid ~= -1 then
			
			if zoneid>=10 and zoneid<=16 then  -- 10-17 area 玩家减血
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
--采集点创建函数
---------------------------------------------------------------------------------------------------

function x700086_OnCreate(sceneId,growPointType,x,y)

	return 0

end


---------------------------------------------------------------------------------------------------
---采集点打开后函数
---------------------------------------------------------------------------------------------------
function x700086_OnProcOver(sceneId,selfId,targetId)

	return 0

end


---------------------------------------------------------------------------------------------------
---采集点打开函数
---------------------------------------------------------------------------------------------------
function x700086_OnOpen(sceneId,selfId,targetId)
	
	return 0

end

---------------------------------------------------------------------------------------------------
---采集点回收函数
---------------------------------------------------------------------------------------------------
function x700086_OnRecycle(sceneId,selfId,targetId)

	return 1

end

---------------------------------------------------------------------------------------------------
---打开采集点500的处理，由700080脚本回调
---------------------------------------------------------------------------------------------------
function x700086_OnGrowPoint(sceneId, selfId)

	local nFuben_SceneId = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_SCENE_ID);--副本场景号
	if nFuben_SceneId ~= sceneId then
		return
	end

	x700086_CreateGrowPointMonster(sceneId)

	SetFubenData_Param(sceneId, x700086_CSP_B_GROWPOINT_OVER,1)

end

---------------------------------------------------------------------------------------------------
---九旄战神死了之后处理，
---------------------------------------------------------------------------------------------------
function x700086_OnRandomBossDie(sceneId, selfId, killerId)

	local nRandomBossID = GetFubenData_Param(sceneId,x700086_CSP_RANDOM_BOSS_ID)

	if nRandomBossID >= 0 then
		if nRandomBossID == selfId then

			----------------------------- 世界喊话 Start--------------------

			--获取角色名称
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType == 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)				
			end
			local strPlayerName = GetName(sceneId, nOwnerId)

			--获取角色所在国家
			local nCountry = GetCurCountry( sceneId, nOwnerId )
			local strCountryName = "";
			if nCountry==0 then
				strCountryName = "楼兰"
			elseif nCountry==1 then
				strCountryName = "天山"
			elseif nCountry==2 then
				strCountryName = "昆仑"
			elseif nCountry==3 then
				strCountryName = "敦煌"
			end

			--获取九旄战神坐骑名称
			local nHorseFlag = GetFubenData_Param(sceneId, x700086_RANDOM_BOSS_FLAG)
			local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "凶豹"
				elseif nHorseFlag==1 then
					strHorseName = "奔羚"
				elseif nHorseFlag==2 then
					strHorseName = "天鹅"
				elseif nHorseFlag==3 then
					strHorseName = "河马"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "烈狮"
				elseif nHorseFlag==1 then
					strHorseName = "驯鹿"
				elseif nHorseFlag==2 then
					strHorseName = "瑞鹤"
				elseif nHorseFlag==3 then
					strHorseName = "铁犀"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "剑齿虎"
				elseif nHorseFlag==1 then
					strHorseName = "蛮牛"
				elseif nHorseFlag==2 then
					strHorseName = "凤凰"
				elseif nHorseFlag==3 then
					strHorseName = "猛犸"
				end
			elseif fubenlevel < 95 then
				if nHorseFlag==0 then
					strHorseName = "虬龙"
				elseif nHorseFlag==1 then
					strHorseName = "应龙"
				elseif nHorseFlag==2 then
					strHorseName = "暴龙"
				elseif nHorseFlag==3 then
				strHorseName = "奎龙"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			end

			--地图名称
			local strMapName = "夏王墓"
			
			--喊话
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)		
			----------------------------- 世界喊话 End--------------------
		end
	end
end
