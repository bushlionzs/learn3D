---------------------------------------------------
-- File: 700032_fuben_ZHUJIAZHUANG3_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700032_CSP_FUBENTYPE				= 	0
x700032_CSP_SCRIPTID				=	1
x700032_CSP_TICKCOUNT				= 	2
x700032_CSP_FROMSCENEID				= 	3
x700032_CSP_ISCLOSING				= 	4
x700032_CSP_LEAVECOUNTDOWN			= 	5
x700032_CSP_TEAMID					=	6
x700032_CSP_BACKSCENEX       		=   7
x700032_CSP_BACKSCENEZ      		=   8
x700032_CSP_FUBENLEVEL				=	9

x700032_CSP_KILLCOUNT				=	20
x700032_CSP_FUBEN_SCENE_ID			=	21

x700032_CSP_BIG_BOSS_ID				=	22
x700032_CSP_BOSS1_ID				=	23
x700032_CSP_BOSS2_ID				=	24
x700032_CSP_BOSS3_ID				=	25

x700032_CSP_GAME_STEP				=	26
x700032_B_CREATE_RANDOMBOSS			=	27
x700032_RANDOMBOSS_FLAG				=	28
x700032_CSP_RANDOM_BOSS_ID			=	29
x700032_CSP_BIG_BOSS_FULLHP			=	30
x700032_CSP_B_SUB_MONSTER			=	31
x700032_CSP_MONSTER_RUN_COUNT		=	32


x700032_CSP_TALK_NPC1_ID			=	33
x700032_CSP_TALK_NPC1_STEP			=	34
x700032_CSP_TALK_NPC2_ID			=	35
x700032_CSP_TALK_NPC2_STEP			=	36

x700032_CSP_OBJID_AREA				=	37

x700032_CSP_MONSTER_ID_COUNT		=	49
x700032_CSP_MONSTER_ID_START		=	50
x700032_CSP_MONSTER_FULLHP_START	=	110
x700032_CSP_MONSTER_B_RUN_START		=	170







x700032_CSP_XIANJINBOSS				=	239
x700032_CSP_HUMAN_COUNT				=	240
x700032_CSP_OBJID_START				=	241

x700032_CSP_GUID_START              =   248  --空6个
x700032_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700032_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700032_g_ScriptId 					= 700032
----------------------------- special for this Fuben --------------------
x700032_g_RandomMonsterRate		=	{0.035,0.045,0.055,0.065}



x700032_g_SubmitNPC                 =   { type =25081,guid= 150555,x = 129, z=23, facedir =0, title ="" }

x700032_g_TalkNPCList					= {
											{ type =25091,x = 146, z=204,	facedir =178, flag =0, title ="黑旋风" },
											{ type =25090,x = 0,	z=0,	facedir =178, flag =1, title ="矮脚虎" },
										  }




-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700032_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)
	
end

function x700032_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700032_ShowTipsToAll(sceneId, str)

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
function x700032_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	
	for i=20,239 do

		SetFubenData_Param(sceneId, i, -1 )
	end

	SetFubenData_Param(sceneId, x700032_CSP_GAME_STEP, 0 )
	

	x700032_CreateMonsterNormal(sceneId)

	x700032_CreateTalkNpc( sceneId, 0 )
	x700032_CreateBoss( sceneId )

    x700032_CreateMonster( sceneId )
		
end

function x700032_EnterTick(sceneId,nowTickCount)

	

	local nBossId = GetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_ID )

	if nBossId>=0 then

		local bCreated = GetFubenData_Param(sceneId, x700032_CSP_B_SUB_MONSTER )
		if bCreated<=0 then
			local nBossFullHp = GetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_FULLHP )
			local nHp = GetHp(sceneId, nBossId)

			--x700032_ShowTipsToAll( sceneId, format("%d,%d",nHp, nBossFullHp))
			if (nHp/nBossFullHp)<=0.5 then
				
				local nMonsterRunCount = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_RUN_COUNT )

				local x,z =GetWorldPos(sceneId,nBossId)

				x700032_CreateSubMonster(sceneId, x,z, nMonsterRunCount)
			end
		end
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_COUNT )

	local nRunCount =0 

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_START+i )
		if nMonsterId>=0 then
			local bRun = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_B_RUN_START+i )
			if bRun<=0 then --如果还没跑
				local nFullHp = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_FULLHP_START+i )
				local nHp = GetHp(sceneId,nMonsterId)
				if (nHp/nFullHp)<=0.5 then
					SetMonsterAIType(sceneId,nMonsterId,7)
					SetPatrolId(sceneId, nMonsterId, 1)
					SetFubenData_Param(sceneId, x700032_CSP_MONSTER_B_RUN_START+i, 1 )
				end
			elseif bRun==1 then--如果跑了
				local area = {125,84,136,90}
				local x,z = GetWorldPos(sceneId,nMonsterId)
				if x>=area[1] and x<=area[3] then
					if z>=area[2] and z<=area[4] then
						if x700032_OnOneMonsterInArea(sceneId,i)>0 then
							nRunCount= nRunCount+1
						end
					end
				end
			end

			
		end
	end


	local nRunOverCount = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_RUN_COUNT )+nRunCount
	SetFubenData_Param(sceneId, x700032_CSP_MONSTER_RUN_COUNT, nRunOverCount )


				
	--// add for talk npc
	local nTalkStep1 = GetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_STEP )
	local nTalkStep2 = GetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_STEP )

	if nTalkStep1>0 then
		local nTalkNpc1 = GetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_ID )
			
		local talklen =2
		local talklist = {"众家兄弟，神行太保戴宗送来了公明哥哥的口信，祝家勾结官府，欺压百姓！","今日梁山就要替天行道！"};

		if nTalkStep1<= talklen then
			NpcTalk(sceneId, nTalkNpc1, talklist[nTalkStep1],  -1)
			SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_STEP, nTalkStep1+1 )
		else
			if nTalkNpc1>=0 then
				DeleteMonster( sceneId,nTalkNpc1 )
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_ID, -1 )
			end
			SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_STEP, -1 )
		end
	end

	if nTalkStep2>0 then
		local nTalkNpc2 = GetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_ID )
		local talklen =1
		local talklist = {"小娘子，随我回山去，我一定请公明哥哥做媒，娶你为妻！"};

		if nTalkStep2<= talklen then
			NpcTalk(sceneId, nTalkNpc2, talklist[nTalkStep2],  -1)
			SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_STEP, nTalkStep2+1 )
		else
			if nTalkNpc2>=0 then
				DeleteMonster( sceneId,nTalkNpc2 )
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_ID, -1 )
			end
			SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_STEP, -1 )
		end
	end
	--//add end


				
				


end

function x700032_OnOneMonsterInArea(sceneId, iIndex)
	local nMonsterId = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_START+iIndex )
	local bRun = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_B_RUN_START+iIndex )

	if nMonsterId<0 then
		return 0
	end

	if bRun~=1 then
		return 0
	end

	DeleteMonster( sceneId,nMonsterId )

	x700032_DeleteOneMonterData(sceneId, iIndex)

--	x700032_ShowTipsToAll( sceneId, "一个monster跑掉了")

	return 1

	


end

function x700032_CreateTalkNpc( sceneId, nFlag, x1,z1 )
	for i, item in x700032_g_TalkNPCList do

		if item.flag == nFlag then

			local nRet = 0
			
				


			if item.flag==0 then
				if item.title ~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, 7, -1, -1, -1, -1,-1, item.facedir,  "",item.title)
					
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, 7, -1, -1, item.guid, -1,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_ID, nRet )
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC1_STEP, 1 )
					
			elseif item.flag==1 then
				local nRandom1 = random(-2,2)
				local nRandom2 = random(-2,2)
				if item.title ~="" then
					nRet = CreateMonster(sceneId, item.type, x1+nRandom1, z1+nRandom2, 7, -1, -1, -1, -1,-1, item.facedir,  "",item.title)
					
				else
					nRet = CreateMonster(sceneId, item.type, x1+nRandom1, z1+nRandom2, 7, -1, -1, item.guid, -1,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_ID, nRet )
				SetFubenData_Param(sceneId, x700032_CSP_TALK_NPC2_STEP, 1 )
			
			end
		end
	end
end



function x700032_CreateSubMonster(sceneId, x,z, nRunCount)

	local bCreated = GetFubenData_Param(sceneId, x700032_CSP_B_SUB_MONSTER )

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )
	local nRunCount = 0
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,nRunCount -1 do

				if title ~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				nRunCount = nRunCount + 1
			end
        end
	end

	if nRunCount>0 then
		x700032_ShowTipsToAll( sceneId, format("召集%d个逃跑怪",nRunCount))
	end

	SetFubenData_Param(sceneId, x700032_CSP_B_SUB_MONSTER, 1 )
end

function x700032_CreateBoss(sceneId)
 	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
                local nObjId = -1
				if title ~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir)
				
				end
				if nObjId >= 0 then
					if flag==0 then
						SetFubenData_Param(sceneId, x700032_CSP_BOSS1_ID, nObjId )
					elseif flag==1 then
						SetFubenData_Param(sceneId, x700032_CSP_BOSS2_ID, nObjId )
					elseif flag==2 then
						SetFubenData_Param(sceneId, x700032_CSP_BOSS3_ID, nObjId )
					elseif flag==3 then
						SetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_ID, nObjId )
						local nFullHp = GetHp( sceneId, nObjId )
						SetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_FULLHP, nFullHp )
					end

					break
				end
			end
        end
	end
	
	


end



---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700032_CreateMonster(sceneId)
	

 	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )

	
	local nCount =0

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
                local nRet =0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_START+nCount, nRet )
				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700032_CSP_MONSTER_FULLHP_START+nCount, nFullHp )
					

				nCount = nCount+1
			end
        end
	end
	
	SetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_COUNT, nCount )

end


---------------------------------------------------------------------------------------------------
--创建普通不逃跑的Monster
---------------------------------------------------------------------------------------------------
function x700032_CreateMonsterNormal(sceneId)
	

	

    local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title ~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

	

end


function x700032_OnDie(sceneId, selfId, killerId)
	
	local nDieCount = GetFubenData_Param(sceneId, x700032_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700032_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	local objId1 = GetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_ID)
	local objId2 = GetFubenData_Param(sceneId, x700032_CSP_BOSS1_ID)
	local objId3 = GetFubenData_Param(sceneId, x700032_CSP_BOSS2_ID)
	local objId4 = GetFubenData_Param(sceneId, x700032_CSP_BOSS3_ID)

	local xianjinboss = GetFubenData_Param(sceneId, x700032_CSP_XIANJINBOSS)
	
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700032_CSP_BIG_BOSS_ID, -1)

			--//--------------------------- 世界喊话 Start--------------------
--		--杀死boss1
--		local nowTickCount = GetFubenData_Param(sceneId, x700032_CSP_TICKCOUNT)
--
--		local nowTime = x700032_g_TickTime* nowTickCount;
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
--		LuaAllScenceM2Wrold (sceneId,"#R“zhujiazhuang成吉思汗当年都不能使我屈服，何况你们这些蝼蚁！下一次，我决不会重蹈覆辙！”在#G"..strPlayerName.."#R等人猛烈的攻势下，扎兰丁仅仅支撑了#G"..strKillTime.."#R，就怒吼着又一次进入了沉睡。", 0, 1)
--		
--		
--		--//--------------------------- 世界喊话 end----------------------
		
		x700032_OnBigBossDie(sceneId, selfId)
		
		local x,z = GetWorldPos(sceneId,objId1)
		
		x700032_CreateTalkNpc( sceneId, 1,x,z )
		
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)

		CallScriptFunction( 701119, "OnSceneBossDie", sceneId, 1)
		
		if objId2>=0 and objId3>=0 and objId4>=0 then
			CallScriptFunction( 701120, "OnSceneBossDie", sceneId, 1)
		end
		x700032_ShowTipsToAll(sceneId, "成功击杀扈三娘，副本完成，请退出副本。")
		
	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700032_CSP_BOSS1_ID, -1)
		
	elseif objId3 == selfId then
		SetFubenData_Param(sceneId, x700032_CSP_BOSS2_ID, -1)
	
	elseif objId4 == selfId then
		SetFubenData_Param(sceneId, x700032_CSP_BOSS3_ID, -1)
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_COUNT )

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_START+i )
		if nMonsterId == selfId then
			x700032_DeleteOneMonterData(sceneId, i)
			
--			x700032_ShowTipsToAll( sceneId, "一个monster挂了")
			break;
		end
	end


	--// add for random boss event, add in 2009-9-7
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700032_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700032_CSP_RANDOM_BOSS_ID)
		if nRandomBossId==selfId then
			--//--------------------------- 世界喊话 Start--------------------
			--杀死Random boss
			
			
			-------- if killed by pet -----------------
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType== 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)
				
			end
			--------- end -------------------------------
			local strPlayerName = GetName(sceneId, nOwnerId)
			
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

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700032_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
			
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



			local strMapName = "祝家庄"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end
	--//add end
end

function x700032_DeleteOneMonterData(sceneId, iIndex)
	local iLen = GetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_COUNT )

	
	local paramStart = x700032_CSP_MONSTER_ID_START
	
	for i=iIndex+1, iLen-1 do
		local nValue = GetFubenData_Param(sceneId, paramStart+i )
		SetFubenData_Param(sceneId, paramStart+i-1, nValue )
	end
	SetFubenData_Param(sceneId, paramStart+iLen-1, -1 )


	paramStart = x700032_CSP_MONSTER_FULLHP_START
	for i=iIndex+1, iLen-1 do
		local nValue = GetFubenData_Param(sceneId, paramStart+i )
		SetFubenData_Param(sceneId, paramStart+i-1, nValue )
	end
	SetFubenData_Param(sceneId, paramStart+iLen-1, -1 )

	paramStart = x700032_CSP_MONSTER_B_RUN_START
	for i=iIndex+1, iLen-1 do
		local nValue = GetFubenData_Param(sceneId, paramStart+i )
		SetFubenData_Param(sceneId, paramStart+i-1, nValue )
	end
	SetFubenData_Param(sceneId, paramStart+iLen-1, -1 )

	SetFubenData_Param(sceneId, x700032_CSP_MONSTER_ID_COUNT, iLen-1 )
	
end

---------------------------------------------------------------------------------------------------
--创建坐骑boss
---------------------------------------------------------------------------------------------------
function x700032_CreateRandomMonster(sceneId,nCount)

	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE )
	if nFubenType ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700032_g_RandomMonsterRate[nCount+1]
	local nFubenMode = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_MODE)
	if nFubenMode ==1 or nFubenMode == 2 then
		nStdRate = nStdRate*3
	end

	if rate>= nStdRate then
		return 0;
	end

	local nFlag = random(0,3)

	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL ) ;


	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				local nBossID = -1
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir)
				
				end

				if nBossID >= 0 then

					SetFubenData_Param(sceneId, x700032_B_CREATE_RANDOMBOSS, 1)
					SetFubenData_Param(sceneId, x700032_RANDOMBOSS_FLAG, nFlag)

					SetFubenData_Param(sceneId, x700032_CSP_RANDOM_BOSS_ID, nBossID)

					break
				end
			end

				
		end
	end


	x700032_ShowTipsToAll(sceneId, "战神再现！")

end
-------------------------------------------------------------------------------
--创建bonusmonter
------------------------------------------------------------------------------
function x700032_CreateBonusMonster(sceneId,nFlag)

	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE )
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == nFlag and nFubenType == flag3 then
            for j=0,count -1 do

				local nObjId = -1
				if title ~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end

				if nObjId >=0 then
					return
				end

			end
        end
	end
end


function x700032_OnAllMonsterDead( sceneId)
	--x700032_CreateSubmitNpc( sceneId)
end

function x700032_OnBigBossDie(sceneId,selfId)
--	x700032_ShowTipsToAll( sceneId, "bigboss挂了")
	
	local objId1 = GetFubenData_Param(sceneId, x700032_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700032_CSP_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700032_CSP_BOSS3_ID)

	local nCount =0
	
	if objId1>=0 then
		DeleteMonster( sceneId,objId1 )
		nCount = nCount+1
	end
	if objId2>=0 then
		nCount = nCount+1
		DeleteMonster( sceneId,objId2 )
	end
	if objId3>=0 then
		nCount = nCount+1
		DeleteMonster( sceneId,objId3 )
	end

	x700032_CreateBonusMonster(sceneId,nCount)

	x700032_CreateRandomMonster(sceneId,nCount)


	x700032_CreateSubmitNpc( sceneId)


	
end


function x700032_CreateSubmitNpc( sceneId)
	--x700032_ShowTipsToAll( sceneId, "副本完成")
	if x700032_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700032_g_SubmitNPC.type, x700032_g_SubmitNPC.x, x700032_g_SubmitNPC.z, 3, 0, -1, x700032_g_SubmitNPC.guid, -1,-1,x700032_g_SubmitNPC.facedir, "", x700032_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700032_g_SubmitNPC.type, x700032_g_SubmitNPC.x, x700032_g_SubmitNPC.z, 3, 0, -1, x700032_g_SubmitNPC.guid, -1,-1,x700032_g_SubmitNPC.facedir)
		
	end

	--// add for 现金副本
	 x700032_CreateXianJinBoss(sceneId)
	 --// add end

	
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700032_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	
	local nFubenMode = GetFubenData_Param(sceneId, x700032_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700032_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700032_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700032_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700032_g_ScriptId,nIndexFrom,i)
		if idScript == x700032_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700032_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700032_CSP_XIANJINBOSS, nRet )
		end
	end

	x700032_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
function x700032_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBENTYPE);

	if nFubenType~=x700032_g_FubenType then
		return
	end


	

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700032_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )

	local nFubenType = GetFubenData_Param(sceneId, x700032_CSP_FUBENTYPE);

	if nFubenType~=x700032_g_FubenType then
		return
	end

  
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700032_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end


