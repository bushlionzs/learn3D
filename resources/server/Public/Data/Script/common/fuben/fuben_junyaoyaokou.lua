---------------------------------------------------
-- File: 700001_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700001_CSP_FUBENTYPE				= 	0
x700001_CSP_SCRIPTID				=	1
x700001_CSP_TICKCOUNT				= 	2
x700001_CSP_FROMSCENEID				= 	3
x700001_CSP_ISCLOSING				= 	4
x700001_CSP_LEAVECOUNTDOWN			= 	5
x700001_CSP_TEAMID					=	6
x700001_CSP_BACKSCENEX       		=   7
x700001_CSP_BACKSCENEZ      		=   8
x700001_CSP_FUBENLEVEL				=	9

x700001_CSP_KILLCOUNT				=	20
x700001_CSP_BOSS_ID					=   21
x700001_CSP_CURRENT_STEP			=   22
x700001_CSP_CURRENT_SUB_STEP		=	23
x700001_CSP_B_FIGTHING				=	24
x700001_CSP_FUBEN_SCENE_ID			=	25
x700001_CSP_NPC_ID					=	26
x700001_CSP_B_MISSION_FAILED		=	27

x700001_CSP_BOSS_FLAG1_ID			=	30
x700001_CSP_BOSS_FLAG2_ID			=	31
x700001_CSP_BOSS_FLAG3_ID			=	32
x700001_CSP_BOSS_FLAG4_ID			=	33
x700001_CSP_BOSS_FLAG5_ID			=	34
x700001_CSP_BOSS_FLAG6_ID			=	35
x700001_CSP_BOSS_FLAG7_ID			=	36
x700001_CSP_BOSS_FLAG8_ID			=	37
x700001_CSP_BOSS_FLAG9_ID			=	38
x700001_CSP_BOSS_FLAG10_ID			=	39

x700001_CSP_KILLCOUNT_SUB1			=	40
x700001_CSP_KILLCOUNT_SUB2			=	41
x700001_CSP_KILLCOUNT_SUB3			=	42
x700001_CSP_KILLCOUNT_SUB4			=	43
x700001_CSP_KILLCOUNT_SUB5			=	44
x700001_CSP_KILLCOUNT_SUB6			=	45
x700001_CSP_KILLCOUNT_SUB7			=	46
x700001_CSP_KILLCOUNT_SUB8			=	47
x700001_CSP_KILLCOUNT_SUB9			=	48
x700001_CSP_KILLCOUNT_SUB10			=	49


x700001_CSP_BOSS1_FULL_HP			=   50
x700001_CSP_BOSS1_TRANS_HUMAN		=   60

x700001_CSP_B_GETBONUS_START		=	220 
x700001_CSP_HUMAN_TALKPARAM_START	=	230
x700001_CSP_HUMAN_COUNT				=	240
x700001_CSP_OBJID_START				=	241
x700001_CSP_LAST_TICKOUNT			=	247
x700001_CSP_GUID_START              =   248  --空6个


-------------------------全局变量 Start ---------------------------
x700001_g_ScriptId 					= 700001
x700001_NeedKillMonster_CountList	=	{9,9,9,9,9,9,9,9,9,9}; -- 10波怪怪物总数

x700001_g_Buff_Id					=	13502                   --玩家被传送后获得buffid
x700001_MAX_TOTAL_STEP				=	10                      --最大波数
x700001_g_Npc_Yaogong                 =   { type =25039,guid= 150539,x = 119, z=122, facedir =0, title = "" }
-------------------------全局变量 End ---------------------------



--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
function x700001_OnFubenSceneCreated( sceneId )
	
	x700001_CreateBoss(sceneId)
	x700001_CreateYaogongNpc( sceneId)
	
	local weekIndex = GetWeekIndex()
	local nHumanCount = GetScenePlayerCount( sceneId)
	if nHumanCount > 0 then
	    for i = 0, nHumanCount do
	        local objId = GetScenePlayerObjId( sceneId,i)
	        if objId >= 0 then
	        	local week = GetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3])
	        	SetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3], weekIndex)
	        	if week ~= weekIndex then
	        		SetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_FLAG[1], MD_FUBEN_XIAOQIAN_FLAG[2], MD_FUBEN_XIAOQIAN_FLAG[3], 0)
	        	end
	        end
		end
	end
end

function x700001_EnterTick(sceneId, nowTickCount)
	local bFighting = GetFubenData_Param(sceneId, x700001_CSP_B_FIGTHING )

	if bFighting>0 then
		 local nCurrentSubStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP )
		 if nCurrentSubStep==8 then
			x700001_CreateBoss2(sceneId)
		 elseif nCurrentSubStep<8 then
			x700001_CreateMonster( sceneId )
		 end


		local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )

		

		 local nBossId = GetFubenData_Param(sceneId, x700001_CSP_BOSS_FLAG1_ID+ nCurrentGameStep)
	
		if nBossId>0 then
			local humancount = GetFuben_PlayerCount(sceneId)
			if humancount>0 then   -- 现在副本机制，怪物Unload 了， Timer 还跑
				local nCurrentHp = GetHp( sceneId, nBossId )
				local nFullHp = GetFubenData_Param(sceneId, x700001_CSP_BOSS1_FULL_HP+nCurrentGameStep )
				local bTransHuman = GetFubenData_Param(sceneId, x700001_CSP_BOSS1_TRANS_HUMAN+nCurrentGameStep )
				
				if nCurrentHp/nFullHp <0.5 then
					if bTransHuman<=0 then
						SetFubenData_Param(sceneId, x700001_CSP_BOSS1_TRANS_HUMAN+nCurrentGameStep, 1)
						x700001_TransferHuman(sceneId)
					end
				end
			end
		end
	end
end


function x700001_TransferHuman(sceneId)

	local humancount = GetFuben_PlayerCount(sceneId);
	local nObj = random(0, humancount-1)
	local n = random(1,8)

	local posList = {
		{x=127,  z=54},
		{x=179,  z=75}, 
		{x=202, z=127}, 
		{x=179, z=177}, 
		{x=128, z=200}, 
		{x=76,  z=178}, 
		{x=54,  z=126}, 
		{x=75,  z=75}
	 }  
	
	local humanId = GetFuben_PlayerObjId(sceneId, nObj);

	SetPos(sceneId,humanId,posList[n].x,posList[n].z)
	SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700001_g_Buff_Id,0 )


	local strHumanName = GetName( sceneId, humanId )
	local str = strHumanName.."突然被一群烈焰卷入了钧窑深处"
	
	for i=0, humancount-1 do
		
		humanId = GetFuben_PlayerObjId(sceneId, i);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
	
end

function x700001_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700001_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
		if idScript == x700001_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, guid, camp,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, guid, camp,-1,facedir)
			end

			SetFubenData_Param(sceneId, x700001_CSP_BOSS_ID, nRet  )

			local humancount = GetFuben_PlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, i);
 				local str = "陶录好像有些事要跟你说！";
  				BeginQuestEvent(sceneId);
  				AddQuestText(sceneId, str);
  				EndQuestEvent(sceneId);
  				DispatchQuestTips(sceneId, humanId);
			end
        end
		
	end
end

function x700001_CreateBoss2(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700001_CSP_FUBENLEVEL ) ;
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )
	local nCurrentSubStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP)

	if nCurrentSubStep~= 8 then
		return
	end
	
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
		if idScript == x700001_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nCurrentGameStep then
				local nCurrentBossFlag = 0;
				if flag== 0 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG1_ID
				elseif flag== 1 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG2_ID
				elseif flag== 2 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG3_ID
				elseif flag== 3 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG4_ID
				elseif flag== 4 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG5_ID
				elseif flag== 5 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG6_ID
				elseif flag== 6 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG7_ID
				elseif flag== 7 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG8_ID
				elseif flag== 8 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG9_ID
				elseif flag== 9 then
					nCurrentBossFlag = x700001_CSP_BOSS_FLAG10_ID
				end

				if nCurrentBossFlag<=0 then
					return
				end

				local nBossId = GetFubenData_Param(sceneId, nCurrentBossFlag ) ;

				if nBossId>0 then
					return
				end

				local nRet = 0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
				end

				SetPatrolId(sceneId, nRet, 0)
				
				SetFubenData_Param(sceneId, nCurrentBossFlag, nRet  )

				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700001_CSP_BOSS1_FULL_HP+nCurrentGameStep, nFullHp )
				SetFubenData_Param(sceneId, x700001_CSP_BOSS1_TRANS_HUMAN+nCurrentGameStep, 0 )

				local humancount = GetFuben_PlayerCount(sceneId);
				for	i = 0, humancount - 1 do
					local humanId = GetFuben_PlayerObjId(sceneId, i);
					local str = format("一个强大的妖魔出现了!", nCurrentGameStep+1);
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, str);
					EndQuestEvent(sceneId);
					DispatchQuestTips(sceneId, humanId);
				end
			end
        end
	end
	
	nCurrentSubStep = nCurrentSubStep+1;
	SetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP, nCurrentSubStep )

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700001_CreateMonster(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700001_CSP_FUBENLEVEL ) ;

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )
	local nCurrentSubStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP )

	if nCurrentGameStep>=x700001_MAX_TOTAL_STEP then
		return
	end

	if nCurrentSubStep>=8 then
		return
	end

	local r1 = random(1,4)
    local r2 = random(5,8)

    if nCurrentGameStep==0 then
    	
	    local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						end
						
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	
	elseif nCurrentGameStep==1 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==2 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==3 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==4 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==5 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==6 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 8 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==7 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 9 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==8 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 10 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
					end
				end
			end
		end
	elseif nCurrentGameStep==9 then
		local nIndexFrom = GetFubenDataPosByScriptID(x700001_g_ScriptId)
		local nDataCount = GetFubenDataCountByScriptID( x700001_g_ScriptId )
		
		for i = 0,nDataCount-1 do
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700001_g_ScriptId,nIndexFrom,i)
			if idScript == x700001_g_ScriptId and monsterFlag == 11 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				if nCurrentSubStep== flag then
					for j=0,count -1 do

						local rx = random(-r,r)
						local x = x + rx
						local rz = random(-r,r)
						local z = z + rz
						local monsterid= 0
						if title~="" then
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir,  "",title)
						else
							monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700001_g_ScriptId, -1, camp,-1,facedir)
						
						end
						SetPatrolId(sceneId, monsterid, 0)
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

	nCurrentSubStep = nCurrentSubStep+1;
	SetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP, nCurrentSubStep )
end

function x700001_OnProtectedFailed(sceneId)
	SetFubenData_Param(sceneId, x700001_CSP_B_MISSION_FAILED,1)
	SetFubenData_Param(sceneId, x700001_CSP_BOSS_ID, -1);
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "炼妖壶碎裂了，妖魔化作一团黑气直冲九霄， 副本失败！"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700001_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700001_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700001_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local objId1 = GetFubenData_Param(sceneId, x700001_CSP_BOSS_ID);

	if objId1 == selfId then
		x700001_OnProtectedFailed(sceneId)
		return
	end

	for i=0, 9 do
		local nBossId_sub = GetFubenData_Param(sceneId, x700001_CSP_BOSS_FLAG1_ID+i)
		if nBossId_sub == selfId then
			SetFubenData_Param(sceneId, x700001_CSP_BOSS_FLAG1_ID+i,-1)
			break;
		end
	end
	

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )
	local nCurrentSub_Macro = x700001_CSP_KILLCOUNT_SUB1 + nCurrentGameStep;
	
	local nDieCount_Sub = GetFubenData_Param(sceneId, nCurrentSub_Macro)
	nDieCount_Sub = nDieCount_Sub+1
	SetFubenData_Param(sceneId, nCurrentSub_Macro, nDieCount_Sub)

--	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = " ";
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end
	
	if nDieCount_Sub == x700001_NeedKillMonster_CountList[nCurrentGameStep+1] then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = format("你们成功抵挡住了第%d波妖魔！", nCurrentGameStep+1);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end

		SetFubenData_Param(sceneId, x700001_CSP_B_FIGTHING, 0)
		SetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP,nCurrentGameStep+1 )
		SetFubenData_Param(sceneId, x700001_CSP_CURRENT_SUB_STEP,0 )

		nCurrentGameStep = nCurrentGameStep+1

		if nCurrentGameStep>=x700001_MAX_TOTAL_STEP then
			local nYaogongNpcId = GetFubenData_Param(sceneId, x700001_CSP_NPC_ID)
		
			NpcTalk(sceneId, nYaogongNpcId, "感谢你们的帮助！我带你们离开这里吧！",  -1)
			
			x700001_ShowTipsToAll(sceneId, "副本完成，请退出副本。")

--			--//--------------------------- 世界喊话 Start--------------------
--			--完成副本
--			local nowTickCount = GetFubenData_Param(sceneId, x700001_CSP_TICKCOUNT)
--
--			local nowTime = x700001_g_TickTime* nowTickCount;
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
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--			
--			
--			LuaAllScenceM2Wrold (sceneId,"#R在#G"..strPlayerName.."#R所领导的队伍凌厉攻势下，仅#G"..strKillTime.."#R，怒炎之锤就在绝望的怒吼声中，丢下手中的巨锤，将自己的身体化作一团炙热的火焰，整个钧窑顿时陷入一片火海之中。熊熊烈焰中传出了陶录老人哀伤的声音：世间再无钧窑矣……", 0, 1)
--			
--			--//--------------------------- 世界喊话 end----------------------
		end
	end		
end

--通知所有玩家
function x700001_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId)

	for i = 0, humancount - 1 do
	
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		Msg2Player(sceneId, humanId, str, 8, 3)
	end
end

function x700001_OnAllMonsterDead( sceneId)
	--x700001_CreateYaogongNpc( sceneId)
end

function x700001_CreateYaogongNpc( sceneId)
	local nRet = 0
	if x700001_g_Npc_Yaogong.title~="" then
		nRet = CreateMonster(sceneId, x700001_g_Npc_Yaogong.type, x700001_g_Npc_Yaogong.x, x700001_g_Npc_Yaogong.z, 3, 0, -1, x700001_g_Npc_Yaogong.guid, -1,-1,x700001_g_Npc_Yaogong.facedir, "", x700001_g_Npc_Yaogong.title)
	else
		nRet = CreateMonster(sceneId, x700001_g_Npc_Yaogong.type, x700001_g_Npc_Yaogong.x, x700001_g_Npc_Yaogong.z, 3, 0, -1, x700001_g_Npc_Yaogong.guid, -1,-1,x700001_g_Npc_Yaogong.facedir)
		
	end
	SetFubenData_Param(sceneId, x700001_CSP_NPC_ID,nRet )
end

--------------------------------------------------------------------------------------------------
-- use for npc talk script( Script 700040)
--------------------------------------------------------------------------------------------------
function x700001_OnNpcTalk(sceneId, selfId, nParam)

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )

	if nParam == nCurrentGameStep then

		x700001_OnStartPlay(sceneId, selfId, nCurrentGameStep)
	else
		
		local str = " "
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, selfId);
	end
	
	
end

function x700001_OnStartPlay(sceneId, selfId, nCurrentGameStep)

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700001_CSP_CURRENT_STEP )
	local bFighting = GetFubenData_Param(sceneId, x700001_CSP_B_FIGTHING )
	local bFailed = GetFubenData_Param(sceneId, x700001_CSP_B_MISSION_FAILED )

	if bFailed>0 then
		local str = "副本已经失败，不能继续"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, selfId);
		return
		
	end

	if bFighting>0 then
		local str = "已经开始保护炼妖壶了"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, selfId);
		return
	end

	if nCurrentGameStep>=x700001_MAX_TOTAL_STEP then
		return
	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("开始第%d波任务!", nCurrentGameStep+1);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	SetFubenData_Param(sceneId, x700001_CSP_B_FIGTHING, 1 )
	x700001_CreateMonster(sceneId);
end

function x700001_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end
