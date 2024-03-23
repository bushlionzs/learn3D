---------------------------------------------------
-- File: 700228_fuben_qiulongdao_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700228_CSP_FUBENTYPE				= 	0
x700228_CSP_SCRIPTID				=	1
x700228_CSP_TICKCOUNT				= 	2
x700228_CSP_FROMSCENEID				= 	3
x700228_CSP_ISCLOSING				= 	4
x700228_CSP_LEAVECOUNTDOWN			= 	5
x700228_CSP_TEAMID					=	6
x700228_CSP_BACKSCENEX       		=   7
x700228_CSP_BACKSCENEZ      		=   8
x700228_CSP_FUBENLEVEL			=	9

x700228_CSP_KILLCOUNT				=	20
x700228_CSP_FUBEN_SCENE_ID			=	21
x700228_CSP_BOSS_ID					=	22
x700228_CSP_BOSS_FULL_HP			=   23
x700228_CSP_BOSS_LOADMONSTER_START	=   24

x700228_CSP_HUMAN_COUNT				=	240
x700228_CSP_OBJID_START				=	241
x700228_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------
x700228_g_ScriptId 					= 700228
x700228_g_SubmitNPC                 =   { type =25001,guid= 150544,x = 72, z=48, facedir =0, title = "" }

--BOSS类型
x700228_g_BossCreate				=	{
                                            {levelmin =20, levelmax=100, name ="囚龙岛boss",   type= 27728,  x=64,  z=60,  ai=9, aiscript=583,  facedir = 0, title = ""},
                                            


										}
-- Random 怪物



--Monster类型
x700228_g_MonsterCreate				=	{

                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=34,  z=86,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=39,  z=91,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=41,  z=84,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=46,  z=86,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=40,  z=80,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=43,  z=83,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=45,  z=76,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=50,  z=81,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=50,  z=77,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=50,  z=71,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪1",   type= 27726,  x=56,  z=76,  r=0, count=1, ai=9, aiscript=581,  facedir = 24, title = ""},
                                                                       
                                                     
                                                                       
										}                              
                                                                       
                                                                       
                                                                       
x700228_g_Sub_MonsterCreate				= {                            
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=64,  z=46,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=78,  z=58,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=53,  z=50,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=51,  z=63,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=66,  z=73,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="囚龙岛小怪2",   type= 27727,  x=76,  z=68,  r=1,  ai=9, aiscript=581,  count=1,  facedir = 0, title = ""},
                                                                       
                                           
											
                                          }

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700228_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700228_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
    x700228_CreateMonster( sceneId )
	x700228_CreateBoss( sceneId )
		
end


-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700228_EnterTick(sceneId, nowTickCount)
	if nowTickCount >= 2 then
		local nBoss2 = GetFubenData_Param(sceneId, x700228_CSP_BOSS_ID )

				
		if nBoss2>0 then
			local humancount = GetFuben_PlayerCount(sceneId);
			if humancount>0 then
				local nCurrentHp = GetHp( sceneId, nBoss2 )
				local nFullHp = GetFubenData_Param(sceneId, x700228_CSP_BOSS_FULL_HP )


				if nCurrentHp/nFullHp <0.2 then
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+0 )
					if bCreatedSubMonster<=0 then
						x700228_CreateSubMonster(sceneId,0)
						
					end
				elseif nCurrentHp/nFullHp <0.5 then
					
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+1)
					if bCreatedSubMonster<=0 then
						x700228_CreateSubMonster(sceneId,1)
						
					end
				elseif nCurrentHp/nFullHp <0.8 then
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+2 )
					if bCreatedSubMonster<=0 then
						x700228_CreateSubMonster(sceneId,2)
						
					end
				end
			end
		end
	end
		
end

function x700228_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700228_CSP_FUBENLEVEL ) ;

	
	for i, item in x700228_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700228_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700228_g_ScriptId, -1, 21,-1, item.facedir)
			
			end

			
				
			SetFubenData_Param(sceneId, x700228_CSP_BOSS_ID, nRet )
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700228_CSP_BOSS_FULL_HP, nFullHp )

			for j=0, 5-1 do
				SetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+j, 0 )
			end
			
			break;
			
        end
	end

end


function x700228_CreateSubMonster(sceneId, iIndex)

	
	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+iIndex )

	if bCreatedSubMonster>0 then
		return 0;
	end

	SetFubenData_Param(sceneId, x700228_CSP_BOSS_LOADMONSTER_START+iIndex, 1 )

	
	local copyscenelevel = GetFubenData_Param(sceneId, x700228_CSP_FUBENLEVEL ) ;

	for i, item in x700228_g_Sub_MonsterCreate do  --创建召唤怪
		if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			 for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
            end
        end
	end

	local strPercent= ""

	if iIndex==0 then
		strPercent= "20%"
	elseif iIndex==1 then
		strPercent= "50%"
	elseif iIndex==2 then
		strPercent= "80%"
	end

	

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("起来！我的勇士们！",strPercent);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end

	
end



---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700228_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700228_CSP_FUBENLEVEL ) ;

	for i, item in x700228_g_MonsterCreate do -- 创建普通怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end


end




function x700228_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700228_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700228_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	local objId2 = GetFubenData_Param(sceneId, x700228_CSP_BOSS_ID)
	
	if objId2 == selfId then
		SetFubenData_Param(sceneId, x700228_CSP_BOSS_ID, -1)
		x700228_OnAllMonsterDead( sceneId)
	
		--//--------------------------- 世界喊话 Start--------------------
			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700228_CSP_TICKCOUNT)

--			local nowTime = x700228_g_TickTime* nowTickCount;

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

			
			
--			--LuaAllScenceM2Wrold (sceneId,x700228_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			

			
			
			--//--------------------------- 世界喊话 end----------------------
	end
end

function x700228_OnAllMonsterDead( sceneId)
	x700228_CreateSubmitNpc( sceneId)
end

function x700228_CreateSubmitNpc( sceneId)
	if x700228_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700228_g_SubmitNPC.type, x700228_g_SubmitNPC.x, x700228_g_SubmitNPC.z, 3, 0, -1, x700228_g_SubmitNPC.guid, -1,-1,x700228_g_SubmitNPC.facedir,  "",x700228_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700228_g_SubmitNPC.type, x700228_g_SubmitNPC.x, x700228_g_SubmitNPC.z, 3, 0, -1, x700228_g_SubmitNPC.guid, -1,-1,x700228_g_SubmitNPC.facedir)
	
	end
end






