---------------------------------------------------
-- File: fuben_huangjinkuangdong.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1
-- modified by shangy:2010-03-22

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700012_CSP_FUBENTYPE				= 	0
x700012_CSP_SCRIPTID				=	1
x700012_CSP_TICKCOUNT				= 	2
x700012_CSP_FROMSCENEID				= 	3
x700012_CSP_ISCLOSING				= 	4
x700012_CSP_LEAVECOUNTDOWN			= 	5
x700012_CSP_TEAMID				=	6
x700012_CSP_BACKSCENEX       			=	7
x700012_CSP_BACKSCENEZ      			=	8
x700012_CSP_FUBENLEVEL				=	9

x700012_CSP_KILLCOUNT				=	20
x700012_CSP_FUBEN_SCENE_ID			=	21

x700012_CSP_BOSS1_ID				=	22
x700012_CSP_BOSS1_FULL_HP			=	23
x700012_CSP_BOSS1_APPOINT			=	24

x700012_CSP_BOSS2_ID				=	25
x700012_CSP_BOSS2_FULL_HP			=	26
x700012_CSP_BOSS2_LOADMONSTER			=	27
x700012_CSP_BOSS2_EATMONSTER			=	28

x700012_CSP_BOSS3_ID				=	29

x700012_CSP_NPC_ID				=	30
x700012_CSP_NPC_STATUS				=	31

x700012_CSP_BOSS_XJ_ID				=	32

x700012_CSP_B_GUOYUN_START			=	228
x700012_CSP_B_GATHERED_START			=	234
x700012_CSP_HUMAN_COUNT				=	240
x700012_CSP_OBJID_START				=	241
x700012_CSP_GUID_START				=	248

x700012_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������
x700012_CSP_FUBEN_MODE				=	255 



------------------------Scene System Setting -----------------------------------

x700012_g_ScriptId 				=	700012

----------------------------- special for this Fuben --------------------

x700012_g_RandomBossRate			=	0                       --����boss���ּ���
x700012_g_nGrowpointType			=	535			--boss����������id

x700012_g_RandomBoss1SkillRate			=	200                     --Boss1ʹ�õ������ܼ���

-------------------------- For Xianjin fuben start -----------------------------

x700012_g_Item_XJ				=	11990012
x700012_g_ItemCount_XJ				=	1

-------------------------- For Xianjin fuben end   -----------------------------

x700012_g_SubmitNPC				=	{ type =28511,guid= 150578,x = 77, z=18, facedir =0, title="" }

x700012_g_RedeemNPC				=	{ type =28511,guid= 150585,x = 78, z=18, facedir =0, title="" }

-------------------------- For test start   -----------------------------
x700012_g_BossCreate				=	{

								{levelmin =20, levelmax=100, name ="����",   type= 27733,  x=68,  z=25,  r=0,  ai=18, aiscript=580,  count=1,  facedir = 0, title = "", flag =2},
											
							}


-------------------------- For test end   ----------------------------- 

-------------------------- For grow point start  -----------------------------

x700012_g_GrowPoints				=	{831,832,833,834}
x700012_g_ItemID				=	{11020030, 11020051, 11030003, 11020040, 11020062, 11020063}

-------------------------- For grow point end  -----------------------------

-------------------------- For skill and effect start  -----------------------------

x700012_g_PlayerDetonate_EffectID		=	7906

x700012_g_EatMonster_EffectID			=	5091

-------------------------- For skill and effect end  -----------------------------


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700012_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end



function x700012_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700012_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
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
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700012_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700012_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		--SetFubenData_Param(sceneId, x700012_CSP_OBJID_START+i, humanId);

		local bGuoyun = CountryIsFortuneTime(sceneId,humanId,2)
		SetFubenData_Param(sceneId, x700012_CSP_B_GUOYUN_START+i, 0); --bGuoyun
	end
	
	x700012_CreateBoss( sceneId )
	x700012_CreateRandomBoss( sceneId )
	x700012_CreateMonster( sceneId )

		
end

function x700012_EnterTick(sceneId, nowTickCount)
	if nowTickCount >= 2 then
		local humancount = GetFuben_PlayerCount(sceneId);
		if humancount>0 then
			local nBoss1 = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID )
			if nBoss1>0 then
				local nCurrentHp = GetHp( sceneId, nBoss1 )
				local nFullHp = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_FULL_HP )
				local nAppoint = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_APPOINT )
				if nCurrentHp/nFullHp <0.8 then
					if nAppoint == 0 then
						local rate = random(0,100)/100;
						if rate < x700012_g_RandomBoss1SkillRate then
							x700012_AppointPlayerToDetonate(sceneId)
						end
					end
				end

				if nCurrentHp/nFullHp <0.5 then
					if nAppoint == 0 or nAppoint == 1 then
						local rate = random(0,100)/100;
						if rate < x700012_g_RandomBoss1SkillRate then
							x700012_AppointPlayerToDetonate(sceneId)
						end
					end
				end

			end

			local nBoss2 = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID )
		
			if nBoss2>0 then
				local nCurrentHp = GetHp( sceneId, nBoss2 )
				local nFullHp = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_FULL_HP )
				--local bCreatedSubMonster = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_LOADMONSTER )
				
				--if nCurrentHp/nFullHp <0.3 then
					--if bCreatedSubMonster<=0 then
						--x700012_CreateSubMonster(sceneId)
					--end
				--end
				local nEatMonster = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_EATMONSTER )
			
				if nCurrentHp/nFullHp <0.8 then
					if nEatMonster == 0 then
						x700012_EatMonster(sceneId)
					end
				end
				
				if nCurrentHp/nFullHp <0.5 then
					if nEatMonster == 1 then
						x700012_EatMonster(sceneId)
					end
				end


			end
		end
	end

	if nowTickCount>=6 then
		local npcStatus = GetFubenData_Param(sceneId, x700012_CSP_NPC_STATUS )

		if npcStatus==1 then
			local npcId = GetFubenData_Param(sceneId, x700012_CSP_NPC_ID )
			NpcTalk(sceneId, npcId, "��л���ǳ��������󶴵Ķ�ħ�����������ǻ��ǸϽ���ȥ�ɡ�",  -1)
			SetFubenData_Param(sceneId, x700012_CSP_NPC_STATUS,  2 )
		end
	end



end

function x700012_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700012_CSP_FUBENLEVEL ) ;
	
	local nRandomNum = random(0,2)

	local nIndexFrom = GetFubenDataPosByScriptID(x700012_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700012_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 1 and flag1 == nRandomNum and levelmin <= fubenlevel and levelmax >= fubenlevel then
		    local nMonsterID = -1
			
			if title~="" then
				nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1, facedir)
			
			end
			
			if flag == 0 then
				SetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID, nMonsterID )
				SetPatrolId(sceneId, nMonsterID, -1)
				local nFullHp = GetHp( sceneId, nMonsterID )
				SetFubenData_Param(sceneId, x700012_CSP_BOSS1_FULL_HP, nFullHp )
				SetFubenData_Param(sceneId, x700012_CSP_BOSS1_APPOINT, 0 )

			elseif flag == 1 then				
				SetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID, nMonsterID )
				local nFullHp = GetHp( sceneId, nMonsterID )
				SetFubenData_Param(sceneId, x700012_CSP_BOSS2_FULL_HP, nFullHp )
				SetFubenData_Param(sceneId, x700012_CSP_BOSS2_LOADMONSTER, 0 )

			elseif flag == 2 then
				SetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID, nMonsterID ) ;
			end
		end
	end

	--for j, item in x700012_g_BossCreate do

		--if item.levelmin <= fubenlevel and item.levelmax >= fubenlevel then
		    --local nMonsterID = -1
			--if item.title~="" then
				--nMonsterID = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700012_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			--else
				--nMonsterID = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700012_g_ScriptId, -1, 21,-1,item.facedir)
			
			--end
			--SetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID, nMonsterID ) ;
			--if flag == 2 then

			--end
			--SetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG, 1 ) ;
			--break;
		--end
	--end


end

function x700012_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700012_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	local fubenlevel = GetFubenData_Param(sceneId, x700012_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700012_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700012_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				if title~="" then
					CreateMonster(sceneId, type, x,z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x,z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir)
				
				end
			end
		end
	end

end

function x700012_CreateSubMonster(sceneId)
	local nBoss2 = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID )
	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_LOADMONSTER )

	if bCreatedSubMonster>0 then
		return 0;
	end

	local x,z = GetWorldPos(sceneId,nBoss2)
		
	local nStep =0.2 ; 
	local fubenlevel = GetFubenData_Param(sceneId, x700012_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700012_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700012_g_ScriptId )

	local j =0;
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			j = j+1;
			local tx = x + random(-1*(j+1)*nStep, (j+1)*nStep);
			local tz = z + random(-1*(j+1)*nStep, (j+1)*nStep);


			if title~="" then
				CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir, "", title)
			else
				CreateMonster(sceneId, type, tx, tz, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir)
			
			end
		end
	end

	

	SetFubenData_Param(sceneId, x700012_CSP_BOSS2_LOADMONSTER, 1 )

	
end



---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700012_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700012_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700012_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700012_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title ~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir)
				
				end
			end
        end
	end


	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nMonsterID = -1
				if title~="" then
					nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetPatrolId(sceneId, nMonsterID, 1)
            end
        end
	end

end




function x700012_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700012_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700012_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	----------------------------------- �ܿ� ----------------------------------

	local buffId1 =9011
	local buffId1_1 = 9013
	local buffId2 =9012

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		local bHaveImpact1 = IsHaveSpecificImpact( sceneId, humanId, buffId1 )
		local bHaveImpact1_1 = IsHaveSpecificImpact( sceneId, humanId, buffId1_1 )
		local bHaveImpact2 = IsHaveSpecificImpact( sceneId, humanId, buffId2 )
			
		local nLevel = GetLevel(sceneId, humanId)

		--//add for xianjin boss
		local nXjBossId = GetFubenData_Param(sceneId, x700012_CSP_BOSS_XJ_ID )
		--//add end
		if bHaveImpact1>0 or bHaveImpact1_1 > 0 then
			local nMoney = nLevel*4

			if nXjBossId==selfId then
				nMoney = nLevel*4*50*4
				SetFubenData_Param(sceneId, x700012_CSP_BOSS_XJ_ID, -1 )
			end

			local strMoney = x700012_GetMoneyName(sceneId,nMoney)
			local str = format("�������ʹ��������%s������",strMoney)
			AddMoney(sceneId, humanId, 0, nMoney)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		end

		if bHaveImpact2>0 then
			local nMoney = nLevel*2

			if nXjBossId==selfId then
				nMoney = nLevel*4*50*4
				SetFubenData_Param(sceneId, x700012_CSP_BOSS_XJ_ID, -1 )
			end

			local strMoney = x700012_GetMoneyName(sceneId,nMoney)
			local str = format("���г�͢������%s������",strMoney)
			AddMoney(sceneId, humanId, 1, nMoney)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		end
		
	end

	----------------------------------- �ܿ�end ----------------------------------
	

	
	local objId1 = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID)
	if objId1 == selfId then
		
		
		SetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID, -1)
		
		NpcTalk(sceneId, selfId, "#R�⡭���ⲻ���ܡ����ҡ�����û��ʹ��ȫ������", -1)
		

		--//--------------------------- ���纰�� Start--------------------
		--ɱ��boss1
--		local nowTickCount = GetFubenData_Param(sceneId, x700012_CSP_TICKCOUNT)

--		local nowTime = x700012_g_TickTime* nowTickCount;

--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)

			
--		local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�

		
		
--		LuaAllScenceM2Wrold (sceneId,"#Rʮ�����˳Ծ�����ɨ��󶴽���#G"..strKillTime.."#Rʱ����Ŷӣ�����#G"..strPlayerName.."#RΪ���ĵĶ��飡", 0, 1)
		
		
		--//--------------------------- ���纰�� end----------------------

	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID, -1)

		NpcTalk(sceneId, selfId, "#R�һᡭ���ٻ����ġ���", -1)
	
		for	i = 0, 6 - 1 do
			SetFubenData_Param(sceneId, x700012_CSP_B_GATHERED_START+i,0);
		end

--		--//--------------------------- ���纰�� Start--------------------
--		--ɱ��boss2
--		local nowTickCount = GetFubenData_Param(sceneId, x700012_CSP_TICKCOUNT)
--
--		local nowTime = x700012_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--			
--		local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
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
--		local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--
--		
--		
--		LuaAllScenceM2Wrold (sceneId,"#R����ڵĵ�Ѩ�־�ħ��һ�������ذ����е��£�#G"..strPlayerName.."#R������Ķ�������#G"..strKillTime.."#Rʱ�������������ֲ���ħͷ������˱����Ŀ󹤣�", 0, 1)
--		
--		
--		--//--------------------------- ���纰�� end----------------------

	elseif objId3 == selfId then
		SetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID, -1)

		for j,item in x700012_g_GrowPoints do
			SetGrowPointIntervalContainer(sceneId,item,1)
		end
		
		--x700012_ShowTipsToAll(sceneId, "���ϳ�����һ����������ӣ�")

		x700012_CreateSubmitNpc( sceneId)
	end
end


function x700012_OnAllMonsterDead( sceneId)
	x700012_CreateSubmitNpc( sceneId)
end

function x700012_CreateSubmitNpc( sceneId)
	local humancount = GetFuben_PlayerCount(sceneId)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
			CallScriptFunction( 203805, "FinishChanchufuben", sceneId, humanId)
			CallScriptFunction( 203806, "FinishChanchufuben", sceneId, humanId)
			CallScriptFunction( 203807, "FinishChanchufuben", sceneId, humanId)
			CallScriptFunction( 203808, "FinishChanchufuben", sceneId, humanId)
	end


	local nSubmitNpc = -1
	if x700012_g_SubmitNPC.title~="" then
		nSubmitNpc = CreateMonster(sceneId, x700012_g_SubmitNPC.type, x700012_g_SubmitNPC.x, x700012_g_SubmitNPC.z, 3, 0, -1, x700012_g_SubmitNPC.guid, -1,-1,x700012_g_SubmitNPC.facedir,  "",x700012_g_SubmitNPC.title)
	else
		nSubmitNpc = CreateMonster(sceneId, x700012_g_SubmitNPC.type, x700012_g_SubmitNPC.x, x700012_g_SubmitNPC.z, 3, 0, -1, x700012_g_SubmitNPC.guid, -1,-1,x700012_g_SubmitNPC.facedir)
	
	end

	SetFubenData_Param(sceneId, x700012_CSP_NPC_ID, nSubmitNpc )
	SetFubenData_Param(sceneId, x700012_CSP_NPC_STATUS, 1 )

	--// add for �ֽ𸱱�
	 --x700012_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700012_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700012_ShowTipsToAll(sceneId, "�ֽ�����֣�")
	 end
	 --// add end
	 
	x700012_CreateRedeemNpc(sceneId)
end

function x700012_CreateRedeemNpc(sceneId)
	local fubentype = GetFubenData_Param(sceneId, x700012_CSP_FUBEN_TYPE )
	if fubentype == 0 then
		if x700012_g_RedeemNPC.title~="" then
			CreateMonster(sceneId, x700012_g_RedeemNPC.type, x700012_g_RedeemNPC.x, x700012_g_RedeemNPC.z, 3, 0, -1, x700012_g_RedeemNPC.guid,-1,-1,x700012_g_RedeemNPC.facedir,"",x700012_g_RedeemNPC.title)
		else
			CreateMonster(sceneId, x700012_g_RedeemNPC.type, x700012_g_RedeemNPC.x, x700012_g_RedeemNPC.z, 3, 0, -1, x700012_g_RedeemNPC.guid,-1,-1,x700012_g_RedeemNPC.facedir)
		end
	end
end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700012_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700012_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700012_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700012_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700012_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700012_g_ScriptId,nIndexFrom,i)
		if idScript == x700012_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nMonsterID = -1
			if title~="" then
				nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nMonsterID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700012_g_ScriptId, -1, 21,-1,facedir)
			end

			SetFubenData_Param(sceneId, x700012_CSP_BOSS_XJ_ID, nMonsterID )
			
		end
	end

	x700012_ShowTipsToAll(sceneId, "����������֣�")
end

--------------------------------------------------------------------------------------
-- ������ű�
--------------------------------------------------------------------------------------


function x700012_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1,60000)

	SetGrowPointIntervalContainer(sceneId,growPointType,2147483648)

end

function x700012_OnOpen(sceneId,selfId,targetId)
	
	return 0;
	
end

function x700012_OnRecycle(sceneId,selfId,targetId)
	
	return 1;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700012_g_GrowpointId, x700012_g_ItemIndex )
end



function x700012_OnProcOver(sceneId,selfId,targetId)
	-- �ɼ����

	--x700012_OnAnwer(sceneId,selfId)

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
	local nItemIndex = random(1,6)

	BeginAddItem(sceneId)
	AddItem( sceneId, x700012_g_ItemID[nItemIndex], 1 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00ݶ�õ��ߣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00��Ʒ���������޷��õ�������Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,humanObjId)
		return 1
	end


end


function x700012_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--function x700012_OnAnwer(sceneId,selfId)

	--local myGuid = GetPlayerGUID( sceneId,selfId )
	--myGuid = format("%u", myGuid)

	

	--for i=0, 5 do
        --local paramidx = 248 + i
        --local nGUID = GetFubenData_Param(sceneId, paramidx  )
		--nGUID = format("%u", nGUID)
		
		

        --if nGUID == myGuid then

			--local bGathered = GetFubenaDta_Param(sceneId, x700012_CSP_B_GATHERED_START+i);
			
			--local str = ""

			--if bGathered<=0 then
				--SetFubenData_Param(sceneId, x700012_CSP_B_GATHERED_START+i,1);
				
				--local bGuoyun =GetFubenData_Param(sceneId, x700012_CSP_B_GUOYUN_START+i);
				--local nMoney = x700012_GetMyMoneyBonus(sceneId,selfId,bGuoyun);
				
				
				--local strMoney = x700012_GetMoneyName(sceneId,nMoney)
				--str = format("���%s������",strMoney)
				
				--AddMoney(sceneId, selfId, 1, nMoney)
			--else
				--str = "��ֻ�ܲɼ�һ�Σ�"
			--end

			--BeginQuestEvent(sceneId);
				--AddQuestText(sceneId,str);
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			--break;
           
       --end
    --end
--end


--function x700012_GetMyMoneyBonus(sceneId,selfId,bGuoyun)

	--local nLevel = GetLevel(sceneId,selfId)

	--local nCount = nLevel*400

	--local nFubenMode = GetFubenData_Param(sceneId, x700012_CSP_FUBEN_MODE)

	--if nFubenMode==1 then
		--nCount = nLevel*400*5
	--end


--	if bGuoyun==1 then
--		nCount = nLevel*(80*3+random(-10,10))
--	end

	
	--return nCount;
--end


function x700012_GetMoneyName(sceneId,nMoney)
	local ding = floor(nMoney/(1000*1000))
	local liang = floor((nMoney-ding*1000*1000)/1000)
	local wen = nMoney-(ding*1000*1000+liang*1000)

	local str=""
	if ding>0 then
		str = str..format("%d��",ding)
	end

	if liang>0 then
		str = str..format("%d��",liang)
	end

	if wen>0 then
		str = str..format("%d��",wen)
	end

	return str;
	
end

---------------------------------------------------------------------------------------------------
--�����������Buff������10�룬ÿ��ȼ����Χ�����Լ�Ѫ����5%���˺�
---------------------------------------------------------------------------------------------------
function x700012_AppointPlayerToDetonate(sceneId)
	local nBoss1 = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID )
	local nAppoint = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_APPOINT )

	if nAppoint>1 then
		return 0;
	end

	local x,z = GetWorldPos(sceneId,nBoss1)
	local Num =  GetNearPlayerCountForMonster(sceneId, nBoss1,x,z,50)

	if Num > 0 then
		local RandomIndex = random(0,Num-1);
		
		local humanObjId = GetNearPlayerMemberForMonster(sceneId, nBoss1,RandomIndex);
		if humanObjId ~= -1 then
			local humanObjName = GetName(sceneId, humanObjId)
			local nRet = SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, x700012_g_PlayerDetonate_EffectID, 0)
			if nRet == 1 then
				NpcTalk(sceneId, nBoss1, format("#R"..humanObjName.."�Ѿ��������䣬���ǻ���Ϊ���ܵ��˺���"), -1)
			end
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "���Ѿ���������~���Զ����Ķ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, humanObjId);
		end
	end


	--x700012_ShowTipsToAll(sceneId,"������Ч")

	nAppoint = nAppoint + 1
	SetFubenData_Param(sceneId, x700012_CSP_BOSS1_APPOINT, nAppoint )

	
end

function x700012_EatMonster(sceneId)
	local nBoss2 = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_ID )
	local nEatMonster = GetFubenData_Param(sceneId, x700012_CSP_BOSS2_EATMONSTER )

	if nEatMonster>1 then
		return 0;
	end

	--local x,z = GetWorldPos(sceneId,nBoss2)
	local nEatMonsterID = FindNearestTeammate(sceneId,nBoss2,20)

	if nEatMonsterID >= 0 and nEatMonsterID ~= nBoss2 then
		--local x,z = GetWorldPos(sceneId,nEatMonsterID)
		--UnitUseSkill(sceneId,nBoss2,201,nEatMonsterID,x,z,9,1)
		local nRet = DeleteMonster(sceneId,nEatMonsterID)
		if nRet == 1 then
			SendSpecificImpactToUnit(sceneId,nBoss2,nBoss2,nBoss2,x700012_g_EatMonster_EffectID,2)

			local nBoss1 = GetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID)
			local nBoss3 = GetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID)

			if nEatMonsterID == nBoss1 then
				SetFubenData_Param(sceneId, x700012_CSP_BOSS1_ID, -1)
			elseif nEatMonsterID == nBoss3	then
				SetFubenData_Param(sceneId, x700012_CSP_BOSS3_ID, -1)
			end
		end
	end
		
	nEatMonster = nEatMonster + 1
	SetFubenData_Param(sceneId, x700012_CSP_BOSS2_EATMONSTER, nEatMonster )

	
end





