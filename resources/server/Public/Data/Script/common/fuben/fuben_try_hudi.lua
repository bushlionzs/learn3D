---------------------------------------------------
-- File: 700224_fuben_HUDI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700224_CSP_FUBENTYPE				= 	0
x700224_CSP_SCRIPTID				=	1
x700224_CSP_TICKCOUNT				= 	2
x700224_CSP_FROMSCENEID				= 	3
x700224_CSP_ISCLOSING				= 	4
x700224_CSP_LEAVECOUNTDOWN			= 	5
x700224_CSP_TEAMID					=	6
x700224_CSP_BACKSCENEX       		=   7
x700224_CSP_BACKSCENEZ      		=   8
x700224_CSP_FUBENLEVEL			=	9
x700224_CSP_KILLCOUNT				=	20
x700224_CSP_BOSS_ID					=   21
x700224_CSP_BOSS_FULL_HP			=   22
x700224_CSP_FUBEN_SCENE_ID			=	23
x700224_CSP_MONSTER_KILL_COUNT		=	24


x700224_CSP_MONSTER_COUNT			=	39
x700224_CSP_MONSTER_ID_START		=	40
x700224_CSP_SHARK_COUNT				=	99
x700224_CSP_SHARK_ID_START			=	100
x700224_CSP_MODEL_COUNT				=	109
x700224_CSP_MODEL_ID_START			=	110



x700224_CSP_HUMAN_COUNT				=	240
x700224_CSP_OBJID_START				=	241
x700224_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700224_g_ScriptId 					= 700224

------------------------- list -----------------------------------------

x700224_g_SubmitNPC                 =   { type =25007,guid= 150546,x = 54, z=71, facedir =0, title="" }

--BOSS����
x700224_g_BossCreate				=	{
                                            {levelmin =20, levelmax=100, name ="�����",   type= 27785,   x=59, z=66,  ai=18, aiscript=519, facedir = 0, title = ""},
                                         

										}
										
										
x700224_g_Shark_FinalX					=	55
x700224_g_Shark_FinalZ					=	60

x700224_g_ModelCreate           = {
                                            {levelmin =20, levelmax=100, name ="С����ģ��",   type= 27784,  x=x700224_g_Shark_FinalX,  z=x700224_g_Shark_FinalZ,   r=3,  ai=7, count = 1, aiscript=0, facedir = 0, title = ""},
                                           
                                        }


x700224_g_SharkMonsterCreate           = {
                                            {levelmin =20, levelmax=100, name ="С����",   type= 27784,  x=24,  z=38,   r=0,  ai=7, aiscript=-1, count=1, facedir = 0, title = ""},
                                          
                                        }

x700224_g_MonsterCreate     =    {

                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=18,  z=62,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=24,  z=64,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=22,  z=72,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=21,  z=77,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=20,  z=92,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=25,  z=93,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=22,  z=105, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=26,  z=101, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=28,  z=106, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=43,  z=107, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=44,  z=111, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=56,  z=110, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=52,  z=18,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=57,  z=22,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=53,  z=23,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=69,  z=108, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=71,  z=111, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=76,  z=108, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=101, z=102, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����1",   type= 27782,  x=106, z=103, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=106, z=108, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=101, z=107, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=104, z=90,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=109, z=91,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=108, z=82,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=108, z=76,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=111, z=68,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=109, z=62,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=106, z=34,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=100, z=36,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=104, z=28,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=99,  z=29,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=88,  z=20,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=85,  z=24,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=73,  z=18,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=71,  z=21,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=81,  z=109, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=86,  z=110, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=91,  z=110, r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=107, z=55,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                            {levelmin =20, levelmax=100, name ="ˮ����2",   type= 27783,  x=106, z=49,  r=1,  ai=9, aiscript=518, count=1, facedir = 0, title = ""},
                                           

                                        }	

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700224_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700224_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	x700224_CreateBoss( sceneId )
    x700224_CreateMonster( sceneId )

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700224_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700224_CSP_OBJID_START+i, humanId);
	end
		
end



function x700224_EnterTick(sceneId, nowTickCount)

	local nSharkCount = GetFubenData_Param(sceneId, x700224_CSP_SHARK_COUNT ) ;
	
	for i=0, nSharkCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700224_CSP_SHARK_ID_START+i );
		if nObjMonsterId>0 and IsObjValid(sceneId,nObjMonsterId) == 1  then
			local x,z = GetWorldPos(sceneId,nObjMonsterId)
			
			if x==x700224_g_Shark_FinalX and z==x700224_g_Shark_FinalZ then
				
				DeleteMonster( sceneId,nObjMonsterId )
				SetFubenData_Param(sceneId, x700224_CSP_SHARK_ID_START+i, -1)
				x700224_CreateModel(sceneId)
			end
		end
	end


	if mod(nowTickCount,1) ==0 then  --5 ��һ��
		local nBossId = GetFubenData_Param(sceneId, x700224_CSP_BOSS_ID ) ;

		if nBossId>=0 then
			local nCurrentBossHp = GetHp( sceneId, nBossId )
			local nFullBossHp = GetFubenData_Param(sceneId, x700224_CSP_BOSS_FULL_HP )
			if nCurrentBossHp/nFullBossHp<0.5 then
				

				local nModelCount = GetFubenData_Param(sceneId, x700224_CSP_MODEL_COUNT );
				
				for i=0, nModelCount-1 do
					local nModelId = GetFubenData_Param(sceneId, x700224_CSP_MODEL_ID_START+i ) ;
					
					if nModelId>0 then
						DeleteMonster( sceneId,nModelId )
						SetFubenData_Param(sceneId, x700224_CSP_MODEL_ID_START+i, -1)

						SetHp(sceneId,nBossId, nFullBossHp*0.2 )
						
						local humancount = GetFuben_PlayerCount(sceneId);
						for	j = 0, humancount - 1 do
							local humanId = GetFuben_PlayerObjId(sceneId, j);
							local str = "�������һ��С���㣬Ϊ�Լ�����������"
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, str);
							EndQuestEvent(sceneId);
							DispatchQuestTips(sceneId, humanId);
						end
						break;
					end
				end
			end
			
			
		end
	end
			
            
	
end


function x700224_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700224_CSP_FUBENLEVEL ) ;

	
	for i, item in x700224_g_BossCreate do --����Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1,item.facedir)
			
			end
			SetFubenData_Param(sceneId, x700224_CSP_BOSS_ID, nRet ) ;
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700224_CSP_BOSS_FULL_HP, nFullHp )
			
        end
	end

end




---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700224_CreateMonster(sceneId) --����С��


    local copyscenelevel = GetFubenData_Param(sceneId, x700224_CSP_FUBENLEVEL ) ;

	local nCount = 0

	for i, item in x700224_g_MonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700224_CSP_MONSTER_ID_START+nCount, nRet ) ;
				nCount = nCount+1
            end
        end
	end

	SetFubenData_Param(sceneId, x700224_CSP_MONSTER_COUNT, nCount ) ;
	SetFubenData_Param(sceneId, x700224_CSP_MONSTER_KILL_COUNT, 0 )

end



function x700224_CreateModel(sceneId)
	local copyscenelevel = GetFubenData_Param(sceneId, x700224_CSP_FUBENLEVEL ) ;

	local nCount = GetFubenData_Param(sceneId, x700224_CSP_MODEL_COUNT )

	for i, item in x700224_g_ModelCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			
			for j=0,item.count -1 do

				local rx = random(-item.r,item.r)
				local x = item.x + rx
				local rz = random(-item.r,item.r)
				local z = item.z + rz
				local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, -1,-1, item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, -1,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700224_CSP_MODEL_ID_START+nCount, nRet ) ;
				nCount = nCount+1
			end
			
        end
	end

	local nModelCount =  nCount;
	SetFubenData_Param(sceneId, x700224_CSP_MODEL_COUNT,nModelCount )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("%dֻ�����ܵ�����ıӻ���",nModelCount);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700224_CreateSharkMonster(sceneId, nCurrentKillCount)
	local copyscenelevel = GetFubenData_Param(sceneId, x700224_CSP_FUBENLEVEL ) ;

	local nCount = GetFubenData_Param(sceneId, x700224_CSP_SHARK_COUNT )

	for i, item in x700224_g_SharkMonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			
			for j=0,item.count -1 do

				local rx = random(-item.r,item.r)
				local x = item.x + rx
				local rz = random(-item.r,item.r)
				local z = item.z + rz
				local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700224_g_ScriptId, -1, 21,-1, item.facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
				SetFubenData_Param(sceneId, x700224_CSP_SHARK_ID_START+nCount, nRet ) ;
				nCount = nCount+1
			end
			
        end
	end

	local nSharkCount =  nCount;
	SetFubenData_Param(sceneId, x700224_CSP_SHARK_COUNT,nSharkCount )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("ɱ��С��%d��, ��%d������ˢ��",nCurrentKillCount,nSharkCount );
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end


function x700224_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700224_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700224_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	

	local objId1 = GetFubenData_Param(sceneId, x700224_CSP_BOSS_ID)

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700224_CSP_BOSS_ID,-1)
		x700224_CreateSubmitNpc( sceneId)

		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "�����ʯͷ���֣�";
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);

			------------------- ��������Ʒ----------
			local nRandom = random(1,100)
			if nRandom<=20 then
				BeginAddItem(sceneId)
				AddItem( sceneId, 11990101, 1 )
				local ret = EndAddItem(sceneId,humanId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,humanId)
					str = "��ϲ�����˺����"
				else
					str = "���ź�����ı��������޷���ú����"
				end

				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId, humanId);
			end
			------------------ ��������Ʒend-------------
		end

			--//--------------------------- ���纰�� Start--------------------
			--ɱ��boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700224_CSP_TICKCOUNT)

--			local nowTime = x700224_g_TickTime* nowTickCount;

--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)

				
--			local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�

			
			
--			--LuaAllScenceM2Wrold (sceneId,x700224_g_FubenName.."���"..strPlayerName.."��"..strKillTime.."ɱ��"..strBossName, 0, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
	end

	
	
		
	
	local nMonsterCount = GetFubenData_Param(sceneId, x700224_CSP_MONSTER_COUNT ) ;
	for i=0, nMonsterCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700224_CSP_MONSTER_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700224_CSP_MONSTER_ID_START+i, -1 );
				local nCurrentKillCount = GetFubenData_Param(sceneId, x700224_CSP_MONSTER_KILL_COUNT )+1 ;

				
				SetFubenData_Param(sceneId, x700224_CSP_MONSTER_KILL_COUNT,nCurrentKillCount ) ;
			
				if mod(nCurrentKillCount, 6) ==0 then
					x700224_CreateSharkMonster(sceneId,nCurrentKillCount)
				end
			end
		end
	end

	local nSharkCount = GetFubenData_Param(sceneId, x700224_CSP_SHARK_COUNT ) ;
	for i=0, nSharkCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700224_CSP_SHARK_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700224_CSP_SHARK_ID_START+i, -1 );
				
			end
		end
	end


	local nModelCount = GetFubenData_Param(sceneId, x700224_CSP_MODEL_COUNT );
	for i=0, nModelCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700224_CSP_MODEL_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700224_CSP_MODEL_ID_START+i, -1 );
				
			end
		end
	end

	

				





end

function x700224_OnAllMonsterDead( sceneId)
	--x700224_CreateSubmitNpc( sceneId)
end

function x700224_CreateSubmitNpc( sceneId)
	if x700224_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700224_g_SubmitNPC.type, x700224_g_SubmitNPC.x, x700224_g_SubmitNPC.z, 3, 0, -1, x700224_g_SubmitNPC.guid, -1,-1,x700224_g_SubmitNPC.facedir,  "",x700224_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700224_g_SubmitNPC.type, x700224_g_SubmitNPC.x, x700224_g_SubmitNPC.z, 3, 0, -1, x700224_g_SubmitNPC.guid, -1,-1,x700224_g_SubmitNPC.facedir)
	
	end
end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x700224_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700224_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





