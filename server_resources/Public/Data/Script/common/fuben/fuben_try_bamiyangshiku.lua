---------------------------------------------------
-- File: 700229_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700229_CSP_FUBENTYPE				= 	0
x700229_CSP_SCRIPTID				=	1
x700229_CSP_TICKCOUNT				= 	2
x700229_CSP_FROMSCENEID				= 	3
x700229_CSP_ISCLOSING				= 	4
x700229_CSP_LEAVECOUNTDOWN			= 	5
x700229_CSP_TEAMID					=	6
x700229_CSP_BACKSCENEX       		=   7
x700229_CSP_BACKSCENEZ      		=   8
x700229_CSP_FUBENLEVEL			=	9
x700229_CSP_KILLCOUNT				=	20

x700229_CSP_FUBEN_SCENE_ID			=	21

x700229_CSP_BOSS1_ID				=	22
x700229_CSP_BOSS2_ID				=	23
x700229_CSP_BOSS2_FINAL_ID			=	24
x700229_CSP_BOSS2_STATUS			=	25

x700229_CSP_OBJID_AREA				=	40
x700229_CSP_MONSTER_START			=	50	--最多20个怪物
x700229_CSP_CAPTIVE_MONSTER_START	=	70	--最多20*3怪物， 到130
x700229_CSP_FREE_MONSTER_START		=	130	--最多20*3怪物，到190

x700229_CSP_HUMAN_COUNT				=	240
x700229_CSP_OBJID_START				=	241
x700229_CSP_NEXT_SCENE				=   248
x700229_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700229_g_ScriptId 					= 700229                    --脚本号

x700229_g_SubmitNPC                 =   { type =25075,guid= 150543,x = 52, z=101, facedir =0, title="" }

--BOSS类型
x700229_g_BossCreate				=	{

                                            {levelmin =20, levelmax=100, name ="狼人布鲁斯",   type= 27813,  x=76, z=26,  r=0,  ai=9, aiscript=643, flag = 0, count=1, facedir = 27, title = ""},                                           

                                            {levelmin =20, levelmax=100, name ="噬灵",   type= 27814,  x=52, z=101,  r=0,  ai=18, aiscript=644, flag = 1, count=1, facedir = 21, title = ""},

										}
--普通小怪										
x700229_g_NormalMonsterCreate      =    {
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=15.78 , z=103.9 , r=0,  ai=9, aiscript=640,count=1, facedir = 9 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=15.07 , z=84.97 , r=0,  ai=9, aiscript=640,count=1, facedir = 9 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=15.26 , z=50.8  , r=0,  ai=9, aiscript=640,count=1, facedir = 9 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=32.3  , z=23.36 , r=0,  ai=9, aiscript=640,count=1, facedir = 33, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=15.1  , z=23.34 , r=0,  ai=9, aiscript=640,count=1, facedir = 33, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=52.92 , z=15.1  , r=0,  ai=9, aiscript=640,count=1, facedir = 25, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=51.83 , z=41.52 , r=0,  ai=9, aiscript=640,count=1, facedir = 25, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=53.64 , z=59.4  , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=64.92 , z=47.55 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            


                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=15.78 , z=103.9 , r=2,  ai=9, aiscript=641,count=3, facedir = 9 , title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=15.07 , z=84.97 , r=2,  ai=9, aiscript=641,count=3, facedir = 9 , title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=15.26 , z=50.8  , r=2,  ai=9, aiscript=641,count=3, facedir = 9 , title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=32.3  , z=23.36 , r=2,  ai=9, aiscript=641,count=3, facedir = 33, title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=15.1  , z=23.34 , r=2,  ai=9, aiscript=641,count=3, facedir = 33, title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=52.92 , z=15.1  , r=2,  ai=9, aiscript=641,count=3, facedir = 25, title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=51.83 , z=41.52 , r=2,  ai=9, aiscript=641,count=3, facedir = 25, title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=53.64 , z=59.4  , r=2,  ai=9, aiscript=641,count=3, facedir = 7 , title = "被侵蚀的"}, 
                                            {levelmin = 20, levelmax=100, name ="无法挽救的村民",   type= 27811,  x=64.92 , z=47.55 , r=2,  ai=9, aiscript=641,count=3, facedir = 7 , title = "被侵蚀的"}, 
                                           


                                        }

-- 地主小怪
x700229_g_MonsterCreate            =    {

                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=82.35 , z=48.67 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=82.71 , z=64.74 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=83.14 , z=80.4  , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=82.58 , z=102.08, r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=91.4  , z=115.17, r=0,  ai=9, aiscript=640,count=1, facedir = 0 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=107.68, z=113.66, r=0,  ai=9, aiscript=640,count=1, facedir = 4 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=112.68, z=102.09, r=0,  ai=9, aiscript=640,count=1, facedir = 12, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=108.57, z=85.59 , r=0,  ai=9, aiscript=640,count=1, facedir = 9 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=117.78, z=42.06 , r=0,  ai=9, aiscript=640,count=1, facedir = 14, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=106.35, z=42.33 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=37.96 , z=102.77, r=0,  ai=9, aiscript=640,count=1, facedir = 18, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=24.48 , z=36.16 , r=0,  ai=9, aiscript=640,count=1, facedir = 14, title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=41.46 , z=34.92 , r=0,  ai=9, aiscript=640,count=1, facedir = 2 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=57.22 , z=59.87 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                            {levelmin = 20, levelmax=100, name ="盗佛者",   type= 27810,  x=48.13 , z=24.56 , r=0,  ai=9, aiscript=640,count=1, facedir = 7 , title = ""}, 
                                           
                                            
                                        }

x700229_g_CaptiveMonster           =    {
                                            
                                            {levelmin = 20, levelmax=100, name ="被胁迫的村民",   type= 27811,  ai=9, aiscript=641, facedir = 9 , title = "被奴役的"},
                                            
                                           
                                        }


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700229_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700229_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700229_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700229_CSP_OBJID_START+i, humanId);
	end
	
	--//初始化
	for	i = 30, 180 do
		
		SetFubenData_Param(sceneId, i, -1);
	end
	
	SetFubenData_Param(sceneId, x700229_CSP_BOSS2_FINAL_ID, -1);
	

    x700229_CreateMonster( sceneId )
	x700229_CreateBoss( sceneId )
	
		
end



function x700229_OnTooMuchPlayerEnterArea(sceneId)
	local nBoss2Status = GetFubenData_Param(sceneId, x700229_CSP_BOSS2_STATUS)

	if nBoss2Status==0 then
		SetFubenData_Param(sceneId, x700229_CSP_BOSS2_STATUS, 1)
		local nBoss2Id = GetFubenData_Param(sceneId, x700229_CSP_BOSS2_ID )

		NpcTalk(sceneId, nBoss2Id, "你们这些愚蠢的凡人，接受我的惩罚吧！",  -1)
	end


end

function x700229_EnterTick(sceneId, nowTickCount)
	
	--// 解放的monster 说话
	for i=0, 60-1 do
		local nFlag = GetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+i);

		if nFlag<0 then
			local nMonsterId = GetFubenData_Param(sceneId, x700229_CSP_FREE_MONSTER_START+i);
			if nMonsterId>=0 then	
				if nFlag==-1 then
					
					
					NpcTalk(sceneId, nMonsterId, "谢谢你的帮助，我们终于自由了！",  -1)
					SetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+i, -2);
					
				elseif nFlag==-2 then
					DeleteMonster( sceneId,nMonsterId )
					SetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+i, -3);
					SetFubenData_Param(sceneId, x700229_CSP_FREE_MONSTER_START+i,-1);
				end
			end
		end
		
	end
	--//解放的end

	--//激怒的boss2说话
	local nBoss2Status = GetFubenData_Param(sceneId, x700229_CSP_BOSS2_STATUS)
	if nBoss2Status ==1 then
		local nBoss2Id = GetFubenData_Param(sceneId, x700229_CSP_BOSS2_ID )
		DeleteMonster( sceneId,nBoss2Id )
		SetFubenData_Param(sceneId, x700229_CSP_BOSS2_STATUS, 2)

		x700229_CreateBoss2(sceneId,1)
	end
	--//xx end
	
end



function x700229_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700229_CSP_FUBENLEVEL ) ;
	
	for i, item in x700229_g_BossCreate do  --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		   

			if item.flag==0 then --boss1
				local nRet = 0;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,"",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end
				SetFubenData_Param(sceneId, x700229_CSP_BOSS1_ID, nRet )
			elseif item.flag==1 then  --boss2, 首先阵营为20
				local nRet = 0;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 20,-1,item.facedir,"",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 20,-1,item.facedir)
				end

				SetFubenData_Param(sceneId, x700229_CSP_BOSS2_STATUS, 0)
				SetFubenData_Param(sceneId, x700229_CSP_BOSS2_ID, nRet )
			end

			
        end
	end

end

function x700229_CreateBoss2(sceneId,nFlag)


	local copyscenelevel = GetFubenData_Param(sceneId, x700229_CSP_FUBENLEVEL ) ;
	
	for i, item in x700229_g_BossCreate do  --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		   

			if item.flag==nFlag then --boss1
				local nRet = 0;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700229_g_ScriptId, -1, 21,-1,item.facedir,"",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700229_g_ScriptId, -1, 21,-1,item.facedir)
				end
				SetFubenData_Param(sceneId, x700229_CSP_BOSS2_FINAL_ID, nRet )
				break;
			
			end

			
        end
	end

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------

function x700229_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700229_CSP_FUBENLEVEL ) ;

	local nCount = 0;

	for i, item in x700229_g_MonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then  --创建地主怪
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				local nRet;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700229_g_ScriptId, -1, 21,-1,item.facedir, "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700229_g_ScriptId, -1, 21,-1,item.facedir)
				end

				SetFubenData_Param(sceneId, x700229_CSP_MONSTER_START+nCount, nRet )
				

				--//create captive monster
				for k, item2 in x700229_g_CaptiveMonster do
					if item2.levelmin <= copyscenelevel and item2.levelmax >= copyscenelevel then  --创建被俘虏怪
						local nCount2 = 0
						for l=1, 3 do
							local tx = x+ random(-1,1)
							local tz = z+ random(-1,1)
							
							if item2.title~="" then
								nRet = CreateMonster(sceneId, item2.type, tx, tz, item2.ai, item2.aiscript, x700229_g_ScriptId, -1, 21,-1,item2.facedir, "",item2.title)
							else
								nRet = CreateMonster(sceneId, item2.type, tx, tz, item2.ai, item2.aiscript, x700229_g_ScriptId, -1, 21,-1,item2.facedir)
							end

							SetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+nCount*3+nCount2, nRet )

							nCount2 = nCount2 + 1
						end
					end
				end
				
				--//create end

				nCount = nCount+1
            end
        end
	end

	for i, item in x700229_g_NormalMonsterCreate do
		if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then  --创建普通怪
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				local nRet;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end
			end

        end
	end

	

end



function x700229_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700229_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700229_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	for i= 0, 20-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700229_CSP_MONSTER_START+i)

		if nMonsterId== selfId then
			SetFubenData_Param(sceneId, x700229_CSP_MONSTER_START+i,-1)
			x700229_OnCaptainMonsterDie(sceneId,i)
			
		end
	end

	for i= 0, 60-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+i)

		if nMonsterId== selfId then
			SetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+i,-1)
			
		end
	end

	local nFinalBossId = GetFubenData_Param(sceneId, x700229_CSP_BOSS2_FINAL_ID )

	if nFinalBossId == selfId then
		SetFubenData_Param(sceneId, x700229_CSP_BOSS2_FINAL_ID, -1 )
		x700229_CreateSubmitNpc( sceneId)

--		--//--------------------------- 世界喊话 Start--------------------
--		--杀死所有 boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700229_CSP_TICKCOUNT)
--
--		local nowTime = x700229_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--			
--		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--		-------- if killed by pet -----------------
--		local nKillerType = GetObjType(sceneId, killerId)
--		--PrintStr(nKillerType)
--		if nKillerType== 3 then
--			local nOwnerId = GetOwnerID(sceneId, killerId)
--			strPlayerName = GetName(sceneId, nOwnerId)
--		end
--		--------- end -------------------------------
--
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--		
--		
--		----LuaAllScenceM2Wrold (sceneId,"#R耶律秦：我要感谢#G"..strPlayerName.."#R和他朋友们！经过#G"..strKillTime.."#R的奋斗，妄图在千佛窟盗取佛祖舍利的察合台汗国败类们终于被赶跑了！", 0, 1)
--		
--
--		
--		
--		--//--------------------------- 世界喊话 end----------------------
	end


	
end

function x700229_OnCaptainMonsterDie(sceneId,iIndex)

	for i=0, 3-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+iIndex*3+i)
		if nMonsterId>=0 and IsObjValid(sceneId,nMonsterId) == 1 then
			local x,z =GetWorldPos(sceneId,nMonsterId)
			DeleteMonster( sceneId,nMonsterId )
			SetFubenData_Param(sceneId, x700229_CSP_CAPTIVE_MONSTER_START+iIndex*3+i, -1)

			local copyscenelevel = GetFubenData_Param(sceneId, x700229_CSP_FUBENLEVEL ) ;
			--//create captive monster
			for k, item in x700229_g_CaptiveMonster do
				if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then  --创建被俘虏怪
					
					local nRet
					if item.title~="" then
						nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 20,-1,item.facedir, "",item.title)
					else
						nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 20,-1,item.facedir)
					end

					SetFubenData_Param(sceneId, x700229_CSP_FREE_MONSTER_START+iIndex*3+i, nRet)
					break;
						
				end
			end
				
			--//create end
		end
	end
end

function x700229_OnAllMonsterDead( sceneId)
	x700229_CreateSubmitNpc( sceneId)
end

function x700229_CreateSubmitNpc( sceneId)
	 if x700229_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700229_g_SubmitNPC.type, x700229_g_SubmitNPC.x, x700229_g_SubmitNPC.z, 3, 0, -1, x700229_g_SubmitNPC.guid, -1,-1,x700229_g_SubmitNPC.facedir,  "", x700229_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700229_g_SubmitNPC.type, x700229_g_SubmitNPC.x, x700229_g_SubmitNPC.z, 3, 0, -1, x700229_g_SubmitNPC.guid, -1,-1,x700229_g_SubmitNPC.facedir)
	 end
	 
end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700229_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )


	--//add in 2009-3-25
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local bFind = 0;
	for i=0, 5 do
        local paramidx = x700229_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

            bFind = 1
            break
        end
    end


	
	if bFind<=0 then
		return
	end
	--//add end

	local index = x700229_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			break;
	    	--return
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        break;
	        --return
	    end
	end


	local nCount=0

	for i=0,5 do
		local nObjId = GetFubenData_Param(sceneId, index+i)
		if nObjId>=0 then
			nCount = nCount +1
		end
	end

	

	if nCount>=1 then
		x700229_OnTooMuchPlayerEnterArea(sceneId);
	end
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700229_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
	 local index = x700229_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 ) 
	    end
	end
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700229_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end
--//add end

