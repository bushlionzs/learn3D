---------------------------------------------------
-- File: 700206_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700206_CSP_FUBENTYPE				= 	0
x700206_CSP_SCRIPTID				=	1
x700206_CSP_TICKCOUNT				= 	2
x700206_CSP_FROMSCENEID				= 	3
x700206_CSP_ISCLOSING				= 	4
x700206_CSP_LEAVECOUNTDOWN			= 	5
x700206_CSP_TEAMID					=	6
x700206_CSP_BACKSCENEX       		=   7
x700206_CSP_BACKSCENEZ      		=   8
x700206_CSP_FUBENLEVEL			=	9

x700206_CSP_KILLCOUNT				=	20
x700206_CSP_SPECIALMONSTER1			=   21
x700206_CSP_BOSS1					=   22
x700206_CSP_BOSS2					=   23
x700206_CSP_BOSS3					=   24
x700206_CSP_BOSS4					=   25
x700206_CSP_BOSS_COUNT				=   26

x700206_CSP_FUBEN_SCENE_ID			=	27

x700206_CSP_HUMAN_COUNT				=	240
x700206_CSP_OBJID_START				=	241
x700206_CSP_NEXT_SCENE				=   248
x700206_CSP_GUID_START              =   248

------------------------Scene System Setting -----------------------------------

x700206_g_ScriptId 					= 700206                    --脚本号
x700206_g_FubenName					= "【试练】景教堂"


x700206_g_SubmitNPC                 =   { type =25031,guid= 150531,x = 96, z=15, facedir =0, title="" }

--BOSS类型
x700206_g_BossCreate				=	{
                                            {levelmin =40, levelmax=100, name ="勃鲁合",   type= 27754,  x=96, z=15,  r=0,  ai=18, aiscript=576, flag = 0, count=1, facedir = 0, title = "大巫师"},
                                           

                                            {levelmin =40, levelmax=100, name ="米底亚大酋长",   type= 27751,  x=20, z=26,  r=0,  ai=9, aiscript=-1, flag = 1, count=1, facedir = 0, title = ""},
                                            

                                            {levelmin =40, levelmax=100, name ="灰袍巫师",   type= 27752,  x=52, z=109,  r=0,  ai=9, aiscript=574, flag = 2, count=1, facedir = 0, title = "落魄王子"},
                                           

										}
										
										
x700206_g_BossCreate2				=	{
                                            {levelmin =40, levelmax=100, name ="白袍道夫",        type= 27753,  x=52, z=109,  r=0,  ai=9, aiscript=575,count=1, facedir = 0, title = "落魄王子"},
                                           
										}


x700206_g_MonsterCreate            =    {
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=15.77 , z=66.24 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=19.97 , z=69.3  ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=15.97 , z=73.06 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=19.89 , z=31.52 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=15.82 , z=25    ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=24.05 , z=24.97 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=20.01 , z=19.22 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=60.58 , z=18.13 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=61.08 , z=34.95 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=52.12 , z=59.28 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=51.81 , z=67.02 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=52.08 , z=75.36 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=52.12 , z=83.25 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=52.15 , z=91.21 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=44.07 , z=105.27,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=60.04 , z=105.3 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=44.15 , z=113.24,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=59.96 , z=113.16,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=72.94 , z=107.22,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=73.09 , z=113.12,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=85.09 , z=106.99,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=84.99 , z=113.01,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=96.93 , z=113.25,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=97.06 , z=107.06,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=24    , z=31    ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=108.91, z=113.31,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=108.91, z=107.26,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=75.82 , z=89.99 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=76.16 , z=98.12 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=115.13, z=89.78 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=114.7 , z=98.28 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=77.69 , z=68.9  ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=86.15 , z=69    ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=108.01, z=68.95 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=115.79, z=69.09 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=89.07 , z=52.25 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=105.37, z=52.18 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=86.9  , z=34.55 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=87.16 , z=42    ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=107   , z=34.04 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=106.89, z=41.98 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=81.04 , z=11.29 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=77.13 , z=14.86 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=81.01 , z=15.12 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=112.94, z=11.35 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=112.95, z=15.08 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=116.99, z=14.91 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=75.75 , z=94.27 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=114.63, z=94.27 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 27750,  x=51.76 , z=50.98 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},

                                           
                                        }


-- 随机怪
x700206_g_RandomMonsterCreate            =    {
                                            
                                            {levelmin =40, levelmax=100, name ="隐藏boss5",   type= 25132,  x=97,  z=60,   r=0,  ai=9, aiscript=636, count=1, facedir = 0, title = "", patrolid =0},
                                           
                                           

                                        }


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700206_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700206_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700206_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700206_CSP_OBJID_START+i, humanId);
	end
	
	SetFubenData_Param(sceneId, x700206_CSP_BOSS4, -1);

    x700206_CreateMonster( sceneId )
	x700206_CreateBoss( sceneId )
	x700206_CreateRandomMonster(sceneId)
		
end




-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700206_EnterTick(sceneId, nowTickCount)

end


function x700206_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700206_CSP_FUBENLEVEL ) ;
	SetFubenData_Param(sceneId, x700206_CSP_BOSS_COUNT, 0 )


	for i, item in x700206_g_BossCreate do  --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0;
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700206_g_ScriptId, -1, 21,-1,item.facedir,"",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700206_g_ScriptId, -1, 21,-1,item.facedir)
			end

			if item.flag == 2 then
				SetFubenData_Param(sceneId, x700206_CSP_SPECIALMONSTER1, nRet )
			end

			if item.flag==0 then
				SetFubenData_Param(sceneId, x700206_CSP_BOSS1, nRet )
			elseif item.flag==1 then
				SetFubenData_Param(sceneId, x700206_CSP_BOSS2, nRet )
			elseif item.flag==2 then
				SetFubenData_Param(sceneId, x700206_CSP_BOSS3, nRet )
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700206_CreateBoss2(sceneId,x,z)

	local copyscenelevel = GetFubenData_Param(sceneId, x700206_CSP_FUBENLEVEL ) ;

	for i, item in x700206_g_BossCreate2 do  --创建变身boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0;
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700206_g_ScriptId, -1, 21,-1,item.facedir,"",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700206_g_ScriptId, -1, 21,-1,item.facedir)
			end
			SetFubenData_Param(sceneId, x700206_CSP_BOSS4, nRet )
        end
	end

end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700206_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700206_CSP_FUBENLEVEL ) ;

	for i, item in x700206_g_MonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then  --创建普通怪
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end
            end
        end
	end

end

function x700206_CreateRandomMonster(sceneId)



	local rate = random(0,100)/100;
	if rate>= x700206_g_RandomMonsterRate then
		return 0;
	end



	local copyscenelevel = GetFubenData_Param(sceneId, x700206_CSP_FUBENLEVEL ) ;


	
	local bCreated =0;
	
	for i, item in x700206_g_RandomMonsterCreate do  --创建随机怪
		if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        
				local nRet = 0;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21, -1,item.facedir, "", item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21, -1,item.facedir)
				end

				
				if item.patrolid>=0 then
					SetPatrolId(sceneId, nRet, item.patrolid)
					
				end
            end
        end
	end

	

end


function x700206_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700206_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700206_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	if nDieCount== x700206_NeedKillMonster_Count then
		--x700206_OnAllMonsterDead( sceneId) 
	end

	local objId1 = GetFubenData_Param(sceneId, x700206_CSP_SPECIALMONSTER1)
	local objId2 = GetFubenData_Param(sceneId, x700206_CSP_BOSS1)
	local objId3 = GetFubenData_Param(sceneId, x700206_CSP_BOSS2)
	local objId4 = GetFubenData_Param(sceneId, x700206_CSP_BOSS3)
	local objId5 = GetFubenData_Param(sceneId, x700206_CSP_BOSS4)

--	--//--------------------------- 世界喊话 Start--------------------
--	
--	local nowTickCount = GetFubenData_Param(sceneId, x700206_CSP_TICKCOUNT)
--
--	local nowTime = x700206_g_TickTime* nowTickCount;
--
--	local nMinute = floor(nowTime/60)
--	local nSec = mod(nowTime,60)
--
--		
--	local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--	-------- if killed by pet -----------------
--	local nKillerType = GetObjType(sceneId, killerId)
--	
--	if nKillerType== 3 then
--		local nOwnerId = GetOwnerID(sceneId, killerId)
--		strPlayerName = GetName(sceneId, nOwnerId)
--	end
--	--------- end -------------------------------
--	
--	local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--	local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--	
--	if selfId == objId2 then -- boss flag=0
--		----LuaAllScenceM2Wrold (sceneId,"#R“不，我是天命之人，我是神的使者，这不可能！”勃鲁合怎么也没有想到勇士#G"..strPlayerName.."#R带领着队友仅用了#G"..strKillTime.."#R就将自己多年苦心经营的计划全盘毁掉。", 0, 1)
--	end
--
--	if selfId == objId3 then -- boss flag=1
--		--LuaAllScenceM2Wrold (sceneId,x700206_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId4 then -- boss flag=2
--		--LuaAllScenceM2Wrold (sceneId,x700206_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId5 then -- boss flag= 变身后的boss
--		--LuaAllScenceM2Wrold (sceneId,x700206_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end
	
	
	--//--------------------------- 世界喊话 end----------------------

	
	if objId1 == selfId then		
		local x,z = GetWorldPos(sceneId,objId1)
		x700206_CreateBoss2(sceneId,x,z)
	end

	if selfId ==objId2 or selfId ==objId3 or selfId ==objId4 or selfId ==objId5 then
		local nCurrentBossCount = GetFubenData_Param(sceneId, x700206_CSP_BOSS_COUNT)
		SetFubenData_Param(sceneId, x700206_CSP_BOSS_COUNT, nCurrentBossCount+1 )
		nCurrentBossCount = nCurrentBossCount +1
		if nCurrentBossCount>=4 then
			x700206_CreateSubmitNpc( sceneId)
		end
	end
end

function x700206_OnAllMonsterDead( sceneId)
	x700206_CreateSubmitNpc( sceneId)
end

function x700206_CreateSubmitNpc( sceneId)
	 if x700206_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700206_g_SubmitNPC.type, x700206_g_SubmitNPC.x, x700206_g_SubmitNPC.z, 3, 0, -1, x700206_g_SubmitNPC.guid, -1,-1,x700206_g_SubmitNPC.facedir,  "", x700206_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700206_g_SubmitNPC.type, x700206_g_SubmitNPC.x, x700206_g_SubmitNPC.z, 3, 0, -1, x700206_g_SubmitNPC.guid, -1,-1,x700206_g_SubmitNPC.facedir)
	 end
	 
end




--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700206_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700206_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end

