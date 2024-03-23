---------------------------------------------------
-- File: 700029_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700029_CSP_FUBENTYPE				= 	0
x700029_CSP_SCRIPTID				=	1
x700029_CSP_TICKCOUNT				= 	2
x700029_CSP_FROMSCENEID				= 	3
x700029_CSP_ISCLOSING				= 	4
x700029_CSP_LEAVECOUNTDOWN			= 	5
x700029_CSP_TEAMID					=	6
x700029_CSP_BACKSCENEX       		=   7
x700029_CSP_BACKSCENEZ      		=   8
x700029_CSP_FUBENLEVEL			=	9

x700029_CSP_KILLCOUNT				=	20

x700029_CSP_FUBEN_SCENE_ID			=	21

x700029_CSP_BOSS1_ID				=	22
x700029_CSP_BOSS2_ID				=	23
x700029_CSP_BOSS2_FINAL_ID			=	24
x700029_CSP_BOSS2_STATUS			=	25

x700029_CSP_OBJID_AREA				=	40
x700029_CSP_MONSTER_START			=	50	--最多20个怪物
x700029_CSP_CAPTIVE_MONSTER_START	=	70	--最多20*3怪物， 到130
x700029_CSP_FREE_MONSTER_START		=	130	--最多20*3怪物，到190

x700029_CSP_HUMAN_COUNT				=	240
x700029_CSP_OBJID_START				=	241
x700029_CSP_NEXT_SCENE				=   248
x700029_CSP_GUID_START              =   248

x700029_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700029_g_ScriptId 					= 700029  

x700029_g_SubmitNPC                 =   { type =25075,guid= 150543,x = 57, z=101, facedir =0, title="" }


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700029_OnFubenSceneCreated( sceneId )
	
	--//初始化
	for	i = 30, 180 do
		
		SetFubenData_Param(sceneId, i, -1);
	end
	
	SetFubenData_Param(sceneId, x700029_CSP_BOSS2_FINAL_ID, -1);
	

    x700029_CreateMonster( sceneId )
	x700029_CreateBoss( sceneId )
		
end

function x700029_EnterTick(sceneId, nowTickCount)
	
	--// 解放的monster 说话
	for i=0, 60-1 do
		local nFlag = GetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+i);

		if nFlag<0 then
			local nMonsterId = GetFubenData_Param(sceneId, x700029_CSP_FREE_MONSTER_START+i);
			if nMonsterId>=0 then	
				if nFlag==-1 then
					
					
					NpcTalk(sceneId, nMonsterId, "谢谢你的帮助，我们终于自由了！",  -1)
					SetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+i, -2);
					
				elseif nFlag==-2 then
					DeleteMonster( sceneId,nMonsterId )
					SetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+i, -3);
					SetFubenData_Param(sceneId, x700029_CSP_FREE_MONSTER_START+i,-1);
				end
			end
		end
		
	end
	--//解放的end

	--//激怒的boss2说话
	local nBoss2Status = GetFubenData_Param(sceneId, x700029_CSP_BOSS2_STATUS)
	if nBoss2Status ==1 then
		local nBoss2Id = GetFubenData_Param(sceneId, x700029_CSP_BOSS2_ID )
		DeleteMonster( sceneId,nBoss2Id )
		SetFubenData_Param(sceneId, x700029_CSP_BOSS2_STATUS, 2)

		x700029_CreateBoss2(sceneId,1)
	end
	--//xx end
	
end

function x700029_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700029_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )

	for i = 0,nDataCount-1 do
		   
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,i)
		if idScript == x700029_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then


			if flag==0 then --boss1
				local nRet = 0;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
				SetFubenData_Param(sceneId, x700029_CSP_BOSS1_ID, nRet )
			elseif flag==1 then  --boss2, 首先阵营为20
				local nRet = 0;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 20,-1,facedir,"",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 20,-1,facedir)
				end

				SetFubenData_Param(sceneId, x700029_CSP_BOSS2_STATUS, 0)
				SetFubenData_Param(sceneId, x700029_CSP_BOSS2_ID, nRet )
			end

			
        end
	end

end

function x700029_CreateBoss2(sceneId,nFlag)


	local fubenlevel = GetFubenData_Param(sceneId, x700029_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,i)
		if idScript == x700029_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
		   

			if flag==nFlag then --boss1
				local nRet = 0;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir,"",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir)
				end
				SetFubenData_Param(sceneId, x700029_CSP_BOSS2_FINAL_ID, nRet )
				break;
			
			end

			
        end
	end

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------

function x700029_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700029_CSP_FUBENLEVEL ) ;

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,i)
		if idScript == x700029_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz

				local nRet;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir)
				end

				SetFubenData_Param(sceneId, x700029_CSP_MONSTER_START+nCount, nRet )
				

				--//create captive monster
				
				
				for k = 0,nDataCount-1 do
					local x1,z1;
					idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,k)
					if idScript == x700029_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
						local nCount2 = 0
						for l=1, 3 do
							local tx = x+ random(-1,1)
							local tz = z+ random(-1,1)
							
							if title~="" then
								nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir, "",title)
							else
								nRet = CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700029_g_ScriptId, -1, 21,-1,facedir)
							end

							SetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+nCount*3+nCount2, nRet )

							nCount2 = nCount2 + 1
						end
					end
				end
				
				--//create end

				nCount = nCount+1
            end
        end
	end

	local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,i)
		if idScript == x700029_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz

				local nRet;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
			end

        end
	end

	

end



function x700029_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700029_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700029_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	for i= 0, 20-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700029_CSP_MONSTER_START+i)

		if nMonsterId== selfId then
			SetFubenData_Param(sceneId, x700029_CSP_MONSTER_START+i,-1)
			x700029_OnCaptainMonsterDie(sceneId,i)
			
		end
	end

	for i= 0, 60-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+i)

		if nMonsterId== selfId then
			SetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+i,-1)
			
		end
	end

	local nFinalBossId = GetFubenData_Param(sceneId, x700029_CSP_BOSS2_FINAL_ID )

	if nFinalBossId == selfId then
		SetFubenData_Param(sceneId, x700029_CSP_BOSS2_FINAL_ID, -1 )
		x700029_CreateSubmitNpc( sceneId)

		--//--------------------------- 世界喊话 Start--------------------
		--杀死所有 boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700029_CSP_TICKCOUNT)
--
--		local nowTime = x700029_g_TickTime* nowTickCount;
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
--		LuaAllScenceM2Wrold (sceneId,"#R耶律秦：我要感谢#G"..strPlayerName.."#R和他朋友们！经过#G"..strKillTime.."#R的奋斗，妄图在千佛窟盗取佛祖舍利的察合台汗国败类们终于被赶跑了！", 0, 1)
--		
--
--		
--		
--		--//--------------------------- 世界喊话 end----------------------
	end


	
end

function x700029_OnCaptainMonsterDie(sceneId,iIndex)

	for i=0, 3-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+iIndex*3+i)
		if nMonsterId>=0 and IsObjValid(sceneId,nMonsterId) == 1 then
			local x,z =GetWorldPos(sceneId,nMonsterId)
			DeleteMonster( sceneId,nMonsterId )
			SetFubenData_Param(sceneId, x700029_CSP_CAPTIVE_MONSTER_START+iIndex*3+i, -1)

			local fubenlevel = GetFubenData_Param(sceneId, x700029_CSP_FUBENLEVEL ) ;
			--//create captive monster
			local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
			local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )
			for k = 0,nDataCount-1 do
				local x1,z1;
				local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,k)
				if idScript == x700029_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
					
					local nRet =0
					if title~="" then
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 20,-1,facedir, "",title)
					else
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 20,-1,facedir)
					end

					SetFubenData_Param(sceneId, x700029_CSP_FREE_MONSTER_START+iIndex*3+i, nRet)
					break;
						
				end
			end
				
			--//create end
		end
	end
end

function x700029_OnAllMonsterDead( sceneId)
	x700029_CreateSubmitNpc( sceneId)
end

function x700029_CreateSubmitNpc( sceneId)
	 if x700029_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700029_g_SubmitNPC.type, x700029_g_SubmitNPC.x, x700029_g_SubmitNPC.z, 3, 0, -1, x700029_g_SubmitNPC.guid, -1,-1,x700029_g_SubmitNPC.facedir,  "", x700029_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700029_g_SubmitNPC.type, x700029_g_SubmitNPC.x, x700029_g_SubmitNPC.z, 3, 0, -1, x700029_g_SubmitNPC.guid, -1,-1,x700029_g_SubmitNPC.facedir)
	 end

     --// add for 现金副本
	 --x700029_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700029_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700029_ShowTipsToAll(sceneId, "现金宝箱出现！")
	 end
	 --// add end
	 
end


----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700029_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700029_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700029_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700029_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700029_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700029_g_ScriptId,nIndexFrom,i)

        if idScript == x700029_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700029_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700029_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	--PrintStr("x700029_ProcAreaEntered")
	
	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700029_CSP_SCRIPTID);

	if nScriptId~=x700029_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaEntered", sceneId, selfId, zoneId, MissionId)
		return
	end
	--//add end

	
	--//add in 2009-3-25
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local bFind = 0;
	for i=0, 5 do
        local paramidx = x700029_CSP_GUID_START + i
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

	local index = x700029_CSP_OBJID_AREA
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
		x700029_OnTooMuchPlayerEnterArea(sceneId);
	end
end




function x700029_OnTooMuchPlayerEnterArea(sceneId)
	local nBoss2Status = GetFubenData_Param(sceneId, x700029_CSP_BOSS2_STATUS)

	if nBoss2Status==0 then
		SetFubenData_Param(sceneId, x700029_CSP_BOSS2_STATUS, 1)
		local nBoss2Id = GetFubenData_Param(sceneId, x700029_CSP_BOSS2_ID )

		NpcTalk(sceneId, nBoss2Id, "你们这些愚蠢的凡人，接受我的惩罚吧！",  -1)
	end


end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700029_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, x700029_CSP_SCRIPTID);

	if nScriptId~=x700029_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaLeaved", sceneId, selfId, ScriptId, MissionId)
		return
	end
	--//add end

	local index = x700029_CSP_OBJID_AREA
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
function x700029_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end
--//add end

function x700029_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700029_ShowTipsToAll(sceneId, str)

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

function x700029_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nIndex)
end

