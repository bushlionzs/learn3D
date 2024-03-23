---------------------------------------------------
-- File: 700007_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700007_CSP_FUBENTYPE				= 	0
x700007_CSP_SCRIPTID				=	1
x700007_CSP_TICKCOUNT				= 	2
x700007_CSP_FROMSCENEID				= 	3
x700007_CSP_ISCLOSING				= 	4
x700007_CSP_LEAVECOUNTDOWN			= 	5
x700007_CSP_TEAMID					=	6
x700007_CSP_BACKSCENEX       		=   7
x700007_CSP_BACKSCENEZ      		=   8
x700007_CSP_FUBENLEVEL			=	9

x700007_CSP_KILLCOUNT				=	20
x700007_CSP_HP_BOSS1				= 	21
x700007_CSP_OBJID_BOSS1				=   22
x700007_CSP_FIND_NPC				=	23    --// 设是否找到范文虎 NPC
x700007_CSP_CREATEFLAG              =   24
x700007_CSP_AREA_TIMER				=	25
x700007_CSP_MONSTERCREATE			= 	26
x700007_CSP_BOSS2_ID				=	27
x700007_CSP_BOSS3_ID				=	28
x700007_CSP_BOSS4_ID				=	29
x700007_CSP_FUBEN_SCENE_ID			=	30

x700007_CSP_RANDBOSS_ID				=	31

x700007_CSP_OBJID_AREA				=	40


x700007_CSP_B_GETBUFF_START			=	234
x700007_CSP_HUMAN_COUNT				=	240
x700007_CSP_OBJID_START				=	241
x700007_CSP_GUID_START              =   248


x700007_CSP_FUBEN_MODE				=   255 




------------------------Scene System Setting -----------------------------------

x700007_g_ScriptId 					= 700007
---------------------------- specail for fuben ------------
x700007_g_Buff1						=	13500 					--火防
x700007_g_Buff2						=	13501                   --恝性半小时

x700007_g_BuffImpact1				=	450                     --火伤害减少
x700007_g_AreaTimer                 =   3*1000                    --事件区定时器

x700007_g_RandomBossRate			=	0



x700007_g_SubmitNPC                 =   { type =25029,guid= 150529,x = 44, z=55, facedir =0, title="" }

--BOSS类型




x700007_g_NpcType					=   25050					--范文虎

x700007_g_NpcCreate					=	{
											{	hash=1, type=x700007_g_NpcType,	 	x=69,	z=97,	ai=3, aiscript=-1,objid = 150004,campid = -1,facedir =0, title="" },
										}


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700007_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
	
end


function x700007_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700007_ShowTipsToAll(sceneId, str)

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
function x700007_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	local index = x700007_CSP_OBJID_AREA
	for i=index,index+11 do

		SetFubenData_Param(sceneId, i, -1 )
	end
	SetFubenData_Param(sceneId, x700007_CSP_RANDBOSS_ID, -1 )
	
	local nCreateFlag = GetFubenData_Param(sceneId, x700007_CSP_CREATEFLAG )
    
	if nCreateFlag == 0 then

		x700007_CreateBoss( sceneId )
		x700007_CreateMonster( sceneId )
		x700007_CreateNpc( sceneId )

		SetFubenData_Param(sceneId, x700007_CSP_CREATEFLAG,1 )

	end

	
	
		
end

function x700007_EnterTick(sceneId, nowTickCount)

	x700007_OnAreaTimer( sceneId )
	local humancount = GetFuben_PlayerCount(sceneId);

	
	--检查BOSS1是否半血
	local MonsterCreated = GetFubenData_Param(sceneId,x700007_CSP_MONSTERCREATE)
	if MonsterCreated == 0 then
		local nHalfHP = GetFubenData_Param(sceneId, x700007_CSP_HP_BOSS1 )
		local nObjId = GetFubenData_Param(sceneId, x700007_CSP_OBJID_BOSS1 )
		nHalfHP = nHalfHP / 2
		local nMonsterCount = GetMonsterCount( sceneId )

		
		for i=0,nMonsterCount -1 do
			local objId = GetMonsterObjID( sceneId, i )
			if objId == nObjId then
				local hp = GetHp( sceneId, objId )

				--x700007_ShowTipsToAll(sceneId, format("hp=%d,nHalfHP=%d",hp,nHalfHP))
				if hp < nHalfHP then
					local x,z = GetMonsterPosition(sceneId,objId)
					x700007_CreateMonster2(sceneId,x,z)
					SetFubenData_Param(sceneId,x700007_CSP_MONSTERCREATE,1)
				end

			end
		end
	else
		local nHalfHP = GetFubenData_Param(sceneId, x700007_CSP_HP_BOSS1 )
		local nObjId = GetFubenData_Param(sceneId, x700007_CSP_OBJID_BOSS1 )
		nHalfHP = nHalfHP / 2
		local nMonsterCount = GetMonsterCount( sceneId )
		for i=0,nMonsterCount -1 do
			local objId = GetMonsterObjID( sceneId, i )
			if objId == nObjId then
				local hp = GetHp( sceneId, objId )
				if hp > nHalfHP then
					SetFubenData_Param(sceneId,x700007_CSP_MONSTERCREATE,0)
				end

			end
		end
	end


		
end
---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x700007_CreateBoss(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700007_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700007_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700007_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700007_g_ScriptId,nIndexFrom,i)
		if idScript == x700007_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local objid = 0
			if title~="" then
				objid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700007_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				objid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700007_g_ScriptId, -1, 21,-1,facedir)
			
			end
			if patrolid>=0 then
				SetPatrolId(sceneId, objid, patrolid)
				
			end

            if flag == 0  then
			    local nFullHp = GetHp( sceneId, objid )
			    SetFubenData_Param(sceneId, x700007_CSP_HP_BOSS1, nFullHp)
			    SetFubenData_Param(sceneId, x700007_CSP_OBJID_BOSS1, objid)
		    elseif flag == 1  then
				 SetFubenData_Param(sceneId, x700007_CSP_BOSS2_ID, objid)
		    elseif flag == 2  then
				 SetFubenData_Param(sceneId, x700007_CSP_BOSS3_ID, objid)
		    elseif flag == 3  then
				 SetFubenData_Param(sceneId, x700007_CSP_BOSS4_ID, objid)
			end

        end
	end

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700007_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700007_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700007_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700007_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700007_g_ScriptId,nIndexFrom,i)
		if idScript == x700007_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x1 = x + rx
                local rz = random(-r,r)
                local z1 = z + rz

				if title~="" then
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

end


---------------------------------------------------------------------------------------------------
--创建Monster2
---------------------------------------------------------------------------------------------------
function x700007_CreateMonster2(sceneId,x,z)  --创建召唤小怪

	--x700007_ShowTipsToAll(sceneId, format("x700007_CreateMonster2",hp,nHalfHP))

    local fubenlevel = GetFubenData_Param(sceneId, x700007_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700007_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700007_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700007_g_ScriptId,nIndexFrom,i)
		if idScript == x700007_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

end

function x700007_CreateNpc( sceneId )
	for i, item in x700007_g_NpcCreate do
		if item.title~="" then
			CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid,-1,-1,item.facedir,  "",item.title);
		else
			CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid,-1,-1,item.facedir);
		
		end
	end
end


function x700007_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700007_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700007_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	


	local objId2 = GetFubenData_Param(sceneId, x700007_CSP_BOSS2_ID)
	local objId4 = GetFubenData_Param(sceneId, x700007_CSP_BOSS4_ID)

	if objId2 == selfId then
		SetFubenData_Param(sceneId, x700007_CSP_BOSS2_ID, -1)
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700007_g_Buff1,0 )
			
		end
	end

	if objId4 == selfId then
		--x700007_CreateSubmitNpc( sceneId)
		SetFubenData_Param(sceneId, x700007_CSP_BOSS4_ID, -1)
		local bCreateRandom = x700007_CreateRandomBoss(sceneId)
		if bCreateRandom==0 then
			x700007_OnGameCompleted(sceneId)
		end

--		--//--------------------------- 世界喊话 Start--------------------
--			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700007_CSP_TICKCOUNT)
--
--			local nowTime = x700007_g_TickTime* nowTickCount;
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
--			LuaAllScenceM2Wrold (sceneId,"#R武林震惊，#G"..strPlayerName.."#R带领的队伍仅用了#G"..strKillTime.."#R就击败了黄河坞中的各路武林人士，见到了传说中的“财宝”！", 0, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------
	end

	local objRandomBossId = GetFubenData_Param(sceneId, x700007_CSP_RANDBOSS_ID ) ; 

	if objRandomBossId>=0 then
		if objRandomBossId== selfId then
			SetFubenData_Param(sceneId, x700007_CSP_RANDBOSS_ID, -1 )
			x700007_OnGameCompleted(sceneId)
		end
	end



	
end

function x700007_OnGameCompleted(sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for	j = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, j);
		local str = "勇士们，你们获得了最终的胜利！回到王城接受大家赞许的目光吧！";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	x700007_CreateSubmitNpc( sceneId)
end

function x700007_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700007_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700007_CSP_FUBENLEVEL ) ;


	
	local bCreated =0;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700007_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700007_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700007_g_ScriptId,nIndexFrom,i)
		if idScript == x700007_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				
				local nRet = 0
				
				if title~="" then
					nRet = CreateMonster(sceneId, type, x,z, ai, aiscript, x700007_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x,z, ai, aiscript, x700007_g_ScriptId, -1, 21,-1,facedir)
				
				end

				SetFubenData_Param(sceneId, x700007_CSP_RANDBOSS_ID, nRet ) ; 
				bCreated = 1;
			end
		end
	end

	if bCreated>0 then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "隐藏Boss出现";
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end
	end

	return bCreated;

end

function x700007_OnAllMonsterDead( sceneId)
	x700007_CreateSubmitNpc( sceneId)
end

function x700007_CreateSubmitNpc( sceneId)
	if x700007_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700007_g_SubmitNPC.type, x700007_g_SubmitNPC.x, x700007_g_SubmitNPC.z, 3, -1, -1, x700007_g_SubmitNPC.guid, -1,-1,x700007_g_SubmitNPC.facedir,  "",x700007_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700007_g_SubmitNPC.type, x700007_g_SubmitNPC.x, x700007_g_SubmitNPC.z, 3, -1, -1, x700007_g_SubmitNPC.guid, -1,-1,x700007_g_SubmitNPC.facedir)
	
	end

	--// add for 现金副本
	 --x700007_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700007_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700007_ShowTipsToAll(sceneId, "现金宝箱出现！")
	 end
	 --// add end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700007_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700007_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700007_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700007_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700007_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700007_g_ScriptId,nIndexFrom,i)
		if idScript == x700007_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700007_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end




---------------------------------------------------------------------------------------------------
--进入区域事件
---------------------------------------------------------------------------------------------------


---------------------------------------------------------------------------------------------------
function x700007_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700007_CSP_SCRIPTID);

	if nScriptId~=x700007_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaEntered", sceneId, selfId, zoneId, MissionId)
		return
	end
	--//add end

     --检查玩家GUID
    local nFind = 1
    local guid = GetPlayerGUID( sceneId,selfId )

    --SetFubenData_Param(sceneId,x700007_CSP_GUID_START+6,guid)
    --guid = GetFubenData_Param(sceneId,x700007_CSP_GUID_START+6)

   -- for n=0, 5 do
    --    local paramidx = x700007_CSP_GUID_START + n
    --    local nGUID = GetFubenData_Param(sceneId, paramidx  )
--
     --   if nGUID == guid then
      --      nFind = 1
      --      break
     --   end
    --end


    --not player
    if nFind == 0 then
        return
    end



	local index = x700007_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			SetFubenData_Param(sceneId, idx+1, zoneId )

	    	return
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        SetFubenData_Param(sceneId, idx+1, zoneId )
	        return
	    end
	end

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700007_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700007_CSP_SCRIPTID);

	if nScriptId~=x700007_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaLeaved", sceneId, selfId, ScriptId, MissionId)
		return
	end
	--//add end
    local index = x700007_CSP_OBJID_AREA
	for i=0,5 do
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
function x700007_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end



function x700007_OnAreaTimer( sceneId )

--	local ct = GetCurrentTime()
-- 	if ct - x700007_g_PROTECTINFO.StartTime >= 1000  then
-- 	    x700007_g_PROTECTINFO.StartTime  = ct
-- 	else
-- 	    return
-- 	end

	

--	local bAreaTimer = GetFubenData_Param(sceneId, x700007_CSP_AREA_TIMER)
--	if bAreaTimer == -1 then
--	    return
--	end

	

    local index = x700007_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneid = GetFubenData_Param(sceneId, idx + 1 )
		
	    if objid ~= -1 then

            --检查玩家是否在线或是玩家是否死亡，如果都不是，那么，执行火烧减血逻辑CZG 2008-12-1
            local ErrorCode = CallScriptFunction( FUBEN_COMMON_SCRIPT_CALL, "IsPlayerErrorState", sceneId, objid)
            if ErrorCode == 0 then

				local nLevel  = GetLevel( sceneId, objid )
                local hurt = 200
				if nLevel>=60 then
					hurt =400
				end
                if zoneid ~= 0 then
					
                    hurt = 500

					if nLevel>=60 then
						hurt =1000
					end
                end

                local haveImpact = IsHaveSpecificImpact( sceneId, objid, x700007_g_Buff1 )
				
                if haveImpact == 1 then
                    --hurt = hurt - x700007_g_BuffImpact1
					hurt = floor(hurt*0.1)	
                end

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


---------------------------------------------------------------------------------------------------
--定点使用物品任务
---------------------------------------------------------------------------------------------------
function x700007_PositionUseItem( sceneId, selfId, BagIndex, impactId )
end


---------------------------------------------------------------------------------------------------
--采集任务，打开采集点事件
---------------------------------------------------------------------------------------------------
function x700007_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
end

---------------------------------------------------------------------------------------------------
--回收
---------------------------------------------------------------------------------------------------
function x700007_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
end

---------------------------------------------------------------------------------------------------
--打开
---------------------------------------------------------------------------------------------------
function x700007_OnProcOver( sceneId, selfId, targetId )
end

---------------------------------------------------------------------------------------------------
--打开后检查
---------------------------------------------------------------------------------------------------
function x700007_OpenCheck( sceneId, selfId, targetId )
end

function x700007_CloseTimer( sceneId, TimerIndex )
--	if TimerIndex ~= -1 then
--		StopTimer(sceneId, TimerIndex)
--	end
--	SetFubenData_Param(sceneId, x700007_CSP_AREA_TIMER, -1) ;
end







