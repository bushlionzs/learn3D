---------------------------------------------------
-- File: 700008_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700008_CSP_FUBENTYPE				= 	0
x700008_CSP_SCRIPTID				=	1
x700008_CSP_TICKCOUNT				= 	2
x700008_CSP_FROMSCENEID				= 	3
x700008_CSP_ISCLOSING				= 	4
x700008_CSP_LEAVECOUNTDOWN			= 	5
x700008_CSP_TEAMID					=	6
x700008_CSP_BACKSCENEX       		=   7
x700008_CSP_BACKSCENEZ      		=   8
x700008_CSP_FUBENLEVEL			=	9

x700008_CSP_KILLCOUNT				=	20
x700008_CSP_CURRENTNPC_ID			=   21
x700008_CSP_CURRENTNPC_INDEX		=   22
x700008_CSP_CURRENTNPC_TICK			=   23
x700008_CSP_FUBENSCENEID			=   24
x700008_CSP_NPC_ID					=	25
x700008_CSP_B_NEED_TALK				=	26

x700008_CSP_B_KILL_FUWANG			=   27
x700008_CSP_AREA_ID					=   30
x700008_CSP_AREA_FLAG				=	31
x700008_CSP_BOSS_ID_START			=	40
x700008_CSP_BOSS_FULL_HP_START		=	50
x700008_CSP_BOSS_LOADMONSTER_START	=   60

x700008_CSP_BOSS_ID					=  80
x700008_CSP_FUBEN_FINISH			=	81
x700008_B_CREATE_RANDOMBOSS			=	230
x700008_CSP_RANDOM_BOSS_ID			=	231
x700008_RANDOMBOSS_FLAG				=	232
x700008_RANDOM_BOSS_ID				=   235
x700008_CSP_XIANJINBOSS				=	239


x700008_CSP_HUMAN_COUNT				=	240
x700008_CSP_OBJID_START				=	241

x700008_CSP_GUID_START              =   248  --空6个
x700008_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700008_CSP_FUBEN_MODE				=   255 

x700008_g_RandomBossRate		=	0.1
------------------------Scene System Setting -----------------------------------

x700008_g_ScriptId 					= 700008
x700008_g_MissionId					=  6608

----------------------------- special for fuben -------------------------------
x700008_g_NpcTalkText			= {
									{"朕乃楚王，你是何人？敢来与我争夺天下！"
									},

									{"八荒一统，六合归一。天下社稷，舍我取谁？"
									},

									{"力拔山兮气盖世，时不利兮骓不逝。"
									},

									{"万里江山，有能者得之，汝能奈我何？"
									},

									{"哈哈哈，三千铁甲开天庭，八方六合尽掌中。"
									},

									{"何言世无英雄，使庶子成名！司马一族，当世称雄。"
									},

									{"人生故当死，岂不一日为帝乎？"
									},

									{"待到秋来九月八，我花开后百花杀。冲天香阵透长安，满城尽带黄金甲。"
									}
								  }	

x700008_g_NpcTalkTime			=	1	
x700008_g_NpcHoldTime			=	2

x700008_NeedKillMonster_Count		=	8		                -- 需要杀几个Boss
-------------------------- For Xianjin fuben start -----------------------------
x700008_g_Item_XJ					= 11990011
x700008_g_ItemCount_XJ				=	0





-------------------------- For Xianjin fuben end   -----------------------------




x700008_g_SubmitNPC                 =   { type =25009,guid= 150509,x = 72, z=74, facedir =0, title="" }



x700008_g_NpcType1                  =   25042                    --NPC ID1
x700008_g_NpcType2                  =   25043                    --NPC ID2
x700008_g_NpcType3                  =   25044                    --NPC ID3
x700008_g_NpcType4                  =   25045                    --NPC ID4
x700008_g_NpcType5                  =   25046                    --NPC ID5
x700008_g_NpcType6                  =   25047                    --NPC ID6
x700008_g_NpcType7                  =   25048                    --NPC ID7
x700008_g_NpcType8                  =   25049                    --NPC ID8

x700008_g_NpcCreate					=	{
											{	type=x700008_g_NpcType1, 	x=61,  z=56,	ai=3,   aiscript=-1,guid = 150005,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType2, 	x=61,  z=62,	ai=3,   aiscript=-1,guid = 150006,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType3, 	x=61,  z=68,	ai=3,   aiscript=-1,guid = 150007,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType4, 	x=61,  z=74,	ai=3,   aiscript=-1,guid = 150008,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType5, 	x=72,  z=56,	ai=3,   aiscript=-1,guid = 150009,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType6, 	x=72,  z=62,	ai=3,   aiscript=-1,guid = 150010,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType7, 	x=72,  z=68,	ai=3,   aiscript=-1,guid = 150011,facedir = 0, title = "" },
                                            {	type=x700008_g_NpcType8, 	x=72,  z=74,	ai=3,   aiscript=-1,guid = 150012,facedir = 0, title = "" },
										}
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700008_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	
end

function x700008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700008_CSP_AREA_ID, zoneId)

	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_FINISH)
		if BossId == 0 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700008_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700008_g_MissionId, x700008_g_ScriptId,1)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700008_g_MissionId, x700008_g_ScriptId)
	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700008_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700008_CSP_AREA_ID, -1)
end
function x700008_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700008_CSP_AREA_ID)
	
	if zoneId == 0 then
		local BossId = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_FINISH)
		--print("BossId",BossId)
		if BossId == 0 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700008_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700008_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700008_g_MissionId, x700008_g_ScriptId)
	elseif zoneId == 1 then
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700008_g_MissionId, x700008_g_ScriptId)
	end
end

function x700008_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700008_ShowTipsToAll(sceneId, str)

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
function x700008_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700008_CSP_XIANJINBOSS, -1 )
	
	SetFubenData_Param(sceneId, x700008_CSP_B_NEED_TALK, 0);
	SetFubenData_Param(sceneId, x700008_CSP_FUBEN_FINISH, 0)
	
	SetFubenData_Param(sceneId, x700008_CSP_B_KILL_FUWANG, 0);

	SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID, -1)
	
	SetFubenData_Param(sceneId, x700008_CSP_AREA_FLAG, 0)

	for i=0, 9 do
		
		SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID_START+i, -1);
	end

	--x700008_ShowTipsToAll(sceneId, "副本说明")

	x700008_CreateNpc( sceneId,0)

	
end

function x700008_GetNpcTextCount(sceneId,nNpcIndex)

	local nTextList = x700008_g_NpcTalkText[nNpcIndex]
	local nCount =0
	for i,item in nTextList do
		nCount = nCount+1
	end

	return nCount
end


function x700008_EnterTick(sceneId,nowTickCount)

	local nNpcIndex = GetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_INDEX);

	local nNpcId = GetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_ID);

	if nNpcId>=0 then
		local nCurrentNpcTick = GetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_TICK)+1;
		SetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_TICK, nCurrentNpcTick)

		local nNpcTextCount = x700008_GetNpcTextCount(sceneId,nNpcIndex)

		if nCurrentNpcTick<=nNpcTextCount then
			
			NpcTalk(sceneId, nNpcId, x700008_g_NpcTalkText[nNpcIndex][nCurrentNpcTick],  -1)
		elseif nCurrentNpcTick==nNpcTextCount+1 then
			
			DeleteMonster( sceneId,nNpcId ) 
			SetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_ID,-2);
			x700008_CreateBoss(sceneId,nNpcIndex-1)
		end
	elseif nNpcId==-2 then
		local nBossId = GetFubenData_Param(sceneId, x700008_CSP_BOSS_ID_START+nNpcIndex-1 )
			
		if nBossId>=0 then
			
			local nCurrentHp = GetHp( sceneId, nBossId )
			local nFullHp = GetFubenData_Param(sceneId, x700008_CSP_BOSS_FULL_HP_START+nNpcIndex-1  )
			local bCreatedSubMonster = GetFubenData_Param(sceneId, x700008_CSP_BOSS_LOADMONSTER_START+nNpcIndex-1  )
			
			if nCurrentHp/nFullHp <0.25 then
				if bCreatedSubMonster<=0 then

					
					SetFubenData_Param(sceneId, x700008_CSP_BOSS_LOADMONSTER_START+nNpcIndex-1,1 )
					if nNpcIndex<x700008_NeedKillMonster_Count then
					x700008_CreateNpc(sceneId,nNpcIndex)
				end
			end
			end
		elseif nBossId == -2 then
			SetFubenData_Param(sceneId, x700008_CSP_BOSS_LOADMONSTER_START+nNpcIndex-1,1 )
			if nNpcIndex<x700008_NeedKillMonster_Count then
					x700008_CreateNpc(sceneId,nNpcIndex)
			
			end
			
		end
	end

	local nSubmitNpcId = GetFubenData_Param(sceneId, x700008_CSP_NPC_ID);
	local bNeedTalk = GetFubenData_Param(sceneId, x700008_CSP_B_NEED_TALK);

	if bNeedTalk>0 then
		SetFubenData_Param(sceneId, x700008_CSP_B_NEED_TALK, 0);
		NpcTalk(sceneId, nSubmitNpcId, "返回王城的大门已经开启！",  -1)
	end
end

---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------

function x700008_CreateBoss(sceneId,index)
	
    local fubenlevel = GetFubenData_Param(sceneId, x700008_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700008_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700008_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700008_g_ScriptId,nIndexFrom,i)
		if idScript == x700008_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count-1 do
                if flag == index then
                    local nRet = 0
					if title~="" then
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1, facedir,  "",title)
					else
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1, facedir)
					
					end
					
					local nFullHp = GetHp( sceneId, nRet )


					SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID_START+index, nRet )
					SetFubenData_Param(sceneId, x700008_CSP_BOSS_FULL_HP_START+index, nFullHp )
					SetFubenData_Param(sceneId, x700008_CSP_BOSS_LOADMONSTER_START+index, 0 )

					x700008_ShowTipsToAll( sceneId, format("第%d个字上帝王影像消失，第%d个字上出现异种怪物！", index+1,index+1))

					return

                end
            end
        end
	end
		
	

end

function x700008_CreateNpc( sceneId,index )

	local nLastStep = GetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_INDEX)

	if nLastStep ~= index then
		return
	end

	if index>=x700008_NeedKillMonster_Count then
		return
	end

    local item = x700008_g_NpcCreate[index + 1]
	local nRet = 0
	if item.title~="" then
		nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.guid,-1,-1, item.facedir,  "",item.title);
	else
		nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.guid,-1,-1, item.facedir);
	
	end
	SetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_ID, nRet)
	SetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_INDEX, index+1)
	SetFubenData_Param(sceneId, x700008_CSP_CURRENTNPC_TICK, 0)

	x700008_ShowTipsToAll( sceneId, format("第%d个字上出现帝王影像", index+1))
end


function x700008_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700008_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700008_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700008_CSP_KILLCOUNT, nDieCount+1);
	

	nDieCount = nDieCount+1;
	--x700008_CreateBoss(sceneId,nDieCount)
	
	for i=0, 9 do
		local nBossId = GetFubenData_Param(sceneId, x700008_CSP_BOSS_ID_START+i )
		if nBossId== selfId then
			SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID_START+i, -2 )
			x700008_ShowTipsToAll( sceneId, format("杀死第%d个字上的异种怪物", i+1))
			if i==7 then
				SetFubenData_Param(sceneId, x700008_CSP_B_KILL_FUWANG, 1 )
			elseif i==8 then
				local bKillFuwang = GetFubenData_Param(sceneId, x700008_CSP_B_KILL_FUWANG);

				if bKillFuwang<=0 then
					CallScriptFunction( 701108, "OnSceneBossDie", sceneId, 1)
				end
			end

			break;
		end
	end
		
	if nDieCount== x700008_NeedKillMonster_Count then
		
		--//--------------------------- 世界喊话 Start--------------------
		--杀死所有 boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700008_CSP_TICKCOUNT)

--		local nowTime = x700008_g_TickTime* nowTickCount;

--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)

			
--		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

		
		
--		LuaAllScenceM2Wrold (sceneId,x700008_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
		

		
		
		--//--------------------------- 世界喊话 end----------------------
		x700008_OnFubenEnd( sceneId) 
	elseif nDieCount< x700008_NeedKillMonster_Count then
		--x700008_CreateNpc(sceneId,nDieCount)
	end
	--local nMonId = GetFubenData_Param(sceneId, x700008_CSP_BOSS_ID)
	--if nMonId == selfId then
		--SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID, -2)
		--x700008_OnFubenEnd( sceneId)
	--end
	
	
	local nRandomBossId = GetFubenData_Param(sceneId, x700008_CSP_RANDOM_BOSS_ID)

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

		local nHorseFlag = GetFubenData_Param(sceneId, x700008_RANDOMBOSS_FLAG);
		local fubenlevel = GetFubenData_Param(sceneId, x700008_CSP_FUBENLEVEL )
		
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



		local strMapName = "和氏璧"
		
		LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
		
		
		--//--------------------------- 世界喊话 end----------------------
	end
	
	
	
end

function x700008_OnAllMonsterDead( sceneId)
	
	x700008_CreateSubmitNpc( sceneId)
	x700008_CreateRandomMonster(sceneId)
	
end

function x700008_CreateSubmitNpc( sceneId)
	 --x700008_ShowTipsToAll( sceneId, "副本完成")
	 local nRet = 0
	 if x700008_g_SubmitNPC.title~="" then
	 	nRet = CreateMonster(sceneId, x700008_g_SubmitNPC.type, x700008_g_SubmitNPC.x, x700008_g_SubmitNPC.z, 3, 0, -1, x700008_g_SubmitNPC.guid, -1,-1,x700008_g_SubmitNPC.facedir, "", x700008_g_SubmitNPC.title)
	 else
	 	nRet = CreateMonster(sceneId, x700008_g_SubmitNPC.type, x700008_g_SubmitNPC.x, x700008_g_SubmitNPC.z, 3, 0, -1, x700008_g_SubmitNPC.guid, -1,-1,x700008_g_SubmitNPC.facedir)
	 
	 end

	 SetFubenData_Param(sceneId, x700008_CSP_NPC_ID, nRet);
	 SetFubenData_Param(sceneId, x700008_CSP_B_NEED_TALK, 1);

	 --// add for 现金副本
	 --x700008_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701107, "OnSceneBossDie", sceneId, 1)

	 

end

function x700008_CreateRandomMonster(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local rate = random(0,100)/100;
	local nStdRate = x700008_g_RandomBossRate
	local nFubenMode = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if rate>= nStdRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700008_CSP_FUBENLEVEL ) ;


	
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700008_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700008_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700008_g_ScriptId,nIndexFrom,i)
		if idScript == x700008_g_ScriptId and monsterFlag == 8+nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1,facedir)
				
				end

				SetFubenData_Param(sceneId, x700008_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700008_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700008_CSP_RANDOM_BOSS_ID, nBossID)
			end

				
		end
	end

	x700008_ShowTipsToAll(sceneId, "战神再现！")

end

function x700008_OnFubenEnd( sceneId)
	x700008_CreateXianJinBoss(sceneId)
	x700008_CreateRandomMonster(sceneId)
	x700008_CreateSubmitNpc( sceneId)
	
	SetFubenData_Param(sceneId, x700008_CSP_FUBEN_FINISH, 1)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,58 )
	end	
	x700008_ShowTipsToAll(sceneId, "成功击杀尾火虎星，副本完成，请退出副本。")
end
--
--function x700008_OnDie(sceneId, selfId, killerId)
--	local nMonId = GetFubenData_Param(sceneId, x700008_CSP_BOSS_ID)
--	if nMonId == selfId then
--		SetFubenData_Param(sceneId, x700008_CSP_BOSS_ID, -2)
--		x700008_OnFubenEnd( sceneId)
--	end
--	
--	
--	local nRandomBossId = GetFubenData_Param(sceneId, x700008_RANDOM_BOSS_ID)
--
--	if nRandomBossId ~= 0 then
--		if nRandomBossId==selfId then
--			--//--------------------------- 世界喊话 Start--------------------
--			--杀死Random boss
--			
--			
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			local nOwnerId = killerId
--			if nKillerType== 3 then
--				nOwnerId = GetOwnerID(sceneId, killerId)
--				
--			end
--			--------- end -------------------------------
--			local strPlayerName = GetName(sceneId, nOwnerId)
--			
--			local nCountry = GetCurCountry( sceneId, nOwnerId )
--			local strCountryName = "";
--			if nCountry==0 then
--				strCountryName = "楼兰"
--			elseif nCountry==1 then
--				strCountryName = "天山"
--			elseif nCountry==2 then
--				strCountryName = "昆仑"
--			elseif nCountry==3 then
--				strCountryName = "敦煌"
--			end
--
--			local strHorseName = ""
--
--			local nHorseFlag = GetFubenData_Param(sceneId, x700008_RANDOMBOSS_FLAG);
--			local fubenlevel = GetFubenData_Param(sceneId, x700008_CSP_FUBENLEVEL )
--			
--			if fubenlevel < 50 then
--				if nHorseFlag==0 then
--					strHorseName = "凶豹"
--				elseif nHorseFlag==1 then
--					strHorseName = "奔羚"
--				elseif nHorseFlag==2 then
--					strHorseName = "天鹅"
--				elseif nHorseFlag==3 then
--					strHorseName = "河马"
--				end
--			elseif fubenlevel < 70 then
--				if nHorseFlag==0 then
--					strHorseName = "烈狮"
--				elseif nHorseFlag==1 then
--					strHorseName = "驯鹿"
--				elseif nHorseFlag==2 then
--					strHorseName = "瑞鹤"
--				elseif nHorseFlag==3 then
--					strHorseName = "铁犀"
--				end
--			elseif fubenlevel < 80 then
--				if nHorseFlag==0 then
--					strHorseName = "剑齿虎"
--				elseif nHorseFlag==1 then
--					strHorseName = "蛮牛"
--				elseif nHorseFlag==2 then
--					strHorseName = "凤凰"
--				elseif nHorseFlag==3 then
--					strHorseName = "猛犸"
--				end
--			elseif fubenlevel < 110 then
--				if nHorseFlag==0 then
--					strHorseName = "虬龙"
--				elseif nHorseFlag==1 then
--					strHorseName = "应龙"
--				elseif nHorseFlag==2 then
--					strHorseName = "暴龙"
--				elseif nHorseFlag==3 then
--				strHorseName = "奎龙"
--				end
--			elseif fubenlevel < 130 then
--				if nHorseFlag==0 then
--					strHorseName = "虬龙"
--				elseif nHorseFlag==1 then
--					strHorseName = "应龙"
--				elseif nHorseFlag==2 then
--					strHorseName = "暴龙"
--				elseif nHorseFlag==3 then
--					strHorseName = "奎龙"
--				end
--			else
--				if nHorseFlag==0 then
--					strHorseName = "虬龙"
--				elseif nHorseFlag==1 then
--					strHorseName = "应龙"
--				elseif nHorseFlag==2 then
--					strHorseName = "暴龙"
--				elseif nHorseFlag==3 then
--					strHorseName = "奎龙"
--				end
--			end
--
--
--
--			local strMapName = "和氏璧"
--			
--			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------
--		end
--	end
--
--	
--	
--	
--end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700008_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700008_CSP_FUBEN_MODE)

	if nFubenMode==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700008_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700008_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700008_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700008_g_ScriptId,nIndexFrom,i)
		if idScript == x700008_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700008_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700008_CSP_XIANJINBOSS, nRet )
		end
	end

	x700008_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end





