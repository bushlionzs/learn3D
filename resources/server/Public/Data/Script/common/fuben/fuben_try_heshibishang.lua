---------------------------------------------------
-- File: 700208_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700208_CSP_FUBENTYPE				= 	0
x700208_CSP_SCRIPTID				=	1
x700208_CSP_TICKCOUNT				= 	2
x700208_CSP_FROMSCENEID				= 	3
x700208_CSP_ISCLOSING				= 	4
x700208_CSP_LEAVECOUNTDOWN			= 	5
x700208_CSP_TEAMID					=	6
x700208_CSP_BACKSCENEX       		=   7
x700208_CSP_BACKSCENEZ      		=   8
x700208_CSP_FUBENLEVEL			=	9
x700208_CSP_KILLCOUNT				=	20
x700208_CSP_CURRENTNPC_ID			=   21
x700208_CSP_CURRENTNPC_INDEX		=   22
x700208_CSP_CURRENTNPC_TICK			=   23
x700208_CSP_FUBENSCENEID			=   24
x700208_CSP_NPC_ID					=	25
x700208_CSP_B_NEED_TALK				=	26

x700208_CSP_BOSS_ID_START			=	40
x700208_CSP_BOSS_FULL_HP_START		=	50
x700208_CSP_BOSS_LOADMONSTER_START	=   60

x700208_CSP_HUMAN_COUNT				=	240
x700208_CSP_OBJID_START				=	241
x700208_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700208_g_ScriptId 					= 700208

----------------------------- special for fuben -------------------------------
x700208_NeedKillMonster_Count		=	8		                -- ��Ҫɱ����Boss

x700208_g_NpcTalkText			= {
									{"���˳��������Ǻ��ˣ����������������£�"
									},

									{"�˻�һͳ�����Ϲ�һ��������𢣬����ȡ˭��"
									},

									{"����ɽ����������ʱ���������š�"
									},

									{"���ｭɽ�������ߵ�֮���������ҺΣ�"
									},

									{"����������ǧ���׿���ͥ���˷����Ͼ����С�"
									},

									{"��������Ӣ�ۣ�ʹ���ӳ�����˾��һ�壬�������ۡ�"
									},

									{"�����ʵ�������һ��Ϊ�ۺ���"
									},

									{"�����������°ˣ��һ�����ٻ�ɱ����������͸���������Ǿ����ƽ�ס�"
									}
								  }	

x700208_g_NpcTalkTime			=	1	
x700208_g_NpcHoldTime			=	2

------------------------- list -----------------------------------------

x700208_g_SubmitNPC                 =   { type =25009,guid= 150547,x = 72, z=74, facedir =0, title="" }

--BOSS����
x700208_g_BossCreate				=	{
											{levelmin =20, levelmax=100, name ="��ľ����",   type= 27786,  x=61, z=56, r=0,  ai=9, aiscript=535, count=1, facedir = 0, title = "",flag=0},
											
											{levelmin =20, levelmax=100, name ="��ľ����",   type= 27787,  x=61, z=62, r=0,  ai=9, aiscript=536, count=1, facedir = 0, title = "",flag=1},
											
											{levelmin =20, levelmax=100, name ="��������",   type= 27788,  x=61, z=68, r=0,  ai=9, aiscript=537, count=1, facedir = 0, title = "",flag=2},
											
											{levelmin =20, levelmax=100, name ="�������",   type= 27789,  x=61, z=74, r=0,  ai=9, aiscript=538, count=1, facedir = 0, title = "",flag=3},
											
											{levelmin =20, levelmax=100, name ="θ������",   type= 27790,  x=72, z=56, r=0,  ai=9, aiscript=539, count=1, facedir = 0, title = "",flag=4},
											
											{levelmin =20, levelmax=100, name ="Ů������",   type= 27791,  x=72, z=62, r=0,  ai=9, aiscript=540, count=1, facedir = 0, title = "",flag=5},

											{levelmin =20, levelmax=100, name ="�������",   type= 27792,  x=72, z=68, r=0,  ai=9, aiscript=541, count=1, facedir = 0, title = "",flag=6},
											
											{levelmin =20, levelmax=100, name ="β����",   type= 27793,  x=72, z=74, r=0,  ai=9, aiscript=542, count=1, facedir = 0, title = "",flag=7},
											
										}

x700208_g_NpcType1                  =   25042                    --NPC ID1
x700208_g_NpcType2                  =   25043                    --NPC ID2
x700208_g_NpcType3                  =   25044                    --NPC ID3
x700208_g_NpcType4                  =   25045                    --NPC ID4
x700208_g_NpcType5                  =   25046                    --NPC ID5
x700208_g_NpcType6                  =   25047                    --NPC ID6
x700208_g_NpcType7                  =   25048                    --NPC ID7
x700208_g_NpcType8                  =   25049                    --NPC ID8

x700208_g_NpcCreate					=	{
											{	type=x700208_g_NpcType1, 	x=61,  z=56,	ai=3,   aiscript=-1,guid = 150005,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType2, 	x=61,  z=62,	ai=3,   aiscript=-1,guid = 150006,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType3, 	x=61,  z=68,	ai=3,   aiscript=-1,guid = 150007,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType4, 	x=61,  z=74,	ai=3,   aiscript=-1,guid = 150008,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType5, 	x=72,  z=56,	ai=3,   aiscript=-1,guid = 150009,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType6, 	x=72,  z=62,	ai=3,   aiscript=-1,guid = 150010,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType7, 	x=72,  z=68,	ai=3,   aiscript=-1,guid = 150011,facedir = 0, title = "" },
                                            {	type=x700208_g_NpcType8, 	x=72,  z=74,	ai=3,   aiscript=-1,guid = 150012,facedir = 0, title = "" },
	
										}
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------
function x700208_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700208_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	SetFubenData_Param(sceneId, x700208_CSP_B_NEED_TALK, 0);

	for i=0, 9 do
		
		SetFubenData_Param(sceneId, x700208_CSP_BOSS_ID_START+i, -1);
	end

	x700208_CreateNpc( sceneId,0)

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700208_CSP_HUMAN_COUNT, humancount);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700208_CSP_OBJID_START+i, humanId);
	end
end





function x700208_GetNpcTextCount(sceneId,nNpcIndex)

	local nTextList = x700208_g_NpcTalkText[nNpcIndex]
	local nCount =0
	for i,item in nTextList do
		nCount = nCount+1
	end

	return nCount
end

-----------------------------------------------------------
--*********************************************************
--EnterTick  :  ��������
--*********************************************************
-----------------------------------------------------------
function x700208_EnterTick(sceneId,nowTickCount)
	local nNpcIndex = GetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_INDEX);

	local nNpcId = GetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_ID);

	if nNpcId>=0 then
		local nCurrentNpcTick = GetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_TICK)+1;
		SetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_TICK, nCurrentNpcTick)

		local nNpcTextCount = x700208_GetNpcTextCount(sceneId,nNpcIndex)

		if nCurrentNpcTick<=nNpcTextCount then
			
			NpcTalk(sceneId, nNpcId, x700208_g_NpcTalkText[nNpcIndex][nCurrentNpcTick],  -1)
		elseif nCurrentNpcTick==nNpcTextCount+1 then
			
			DeleteMonster( sceneId,nNpcId ) 
			SetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_ID,-2);
			x700208_CreateBoss(sceneId,nNpcIndex-1)
		end
	elseif nNpcId==-2 then
		local nBossId = GetFubenData_Param(sceneId, x700208_CSP_BOSS_ID_START+nNpcIndex-1 )
			
		if nBossId>=0 then
			
			local nCurrentHp = GetHp( sceneId, nBossId )
			local nFullHp = GetFubenData_Param(sceneId, x700208_CSP_BOSS_FULL_HP_START+nNpcIndex-1  )
			local bCreatedSubMonster = GetFubenData_Param(sceneId, x700208_CSP_BOSS_LOADMONSTER_START+nNpcIndex-1  )
			
			if nCurrentHp/nFullHp <0.25 then
				if bCreatedSubMonster<=0 then

					
					SetFubenData_Param(sceneId, x700208_CSP_BOSS_LOADMONSTER_START+nNpcIndex-1,1 )
					if nNpcIndex<x700208_NeedKillMonster_Count then
					x700208_CreateNpc(sceneId,nNpcIndex)
				end
			end
			end
			
		end
	end

	local nSubmitNpcId = GetFubenData_Param(sceneId, x700208_CSP_NPC_ID);
	local bNeedTalk = GetFubenData_Param(sceneId, x700208_CSP_B_NEED_TALK);

	if bNeedTalk>0 then
		SetFubenData_Param(sceneId, x700208_CSP_B_NEED_TALK, 0);
		NpcTalk(sceneId, nSubmitNpcId, "���ǵ�֮���Ѿ�������",  -1)
	end
end


---------------------------------------------------------------------------------------------------
--����BOSS
---------------------------------------------------------------------------------------------------
function x700208_CreateBoss(sceneId,index)

	
    local copyscenelevel = GetFubenData_Param(sceneId, x700208_CSP_FUBENLEVEL ) ;

	for i, item in x700208_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count-1 do
                if item.flag == index then
                    local nRet = 0
					if item.title~="" then
						nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700208_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
					else
						nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700208_g_ScriptId, -1, 21,-1, item.facedir)
					
					end
					
					local nFullHp = GetHp( sceneId, nRet )


					SetFubenData_Param(sceneId, x700208_CSP_BOSS_ID_START+index, nRet )
					SetFubenData_Param(sceneId, x700208_CSP_BOSS_FULL_HP_START+index, nFullHp )
					SetFubenData_Param(sceneId, x700208_CSP_BOSS_LOADMONSTER_START+index, 0 )

					x700208_ShowTipsToAll( sceneId, format("��%d�����ϵ���Ӱ����ʧ����%d�����ϳ������ֹ��", index+1,index+1))

					return

                end
            end
        end
	end
		
	

end

function x700208_CreateNpc( sceneId,index )

	local nLastStep = GetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_INDEX)

	if nLastStep ~= index then
		return
	end

	if index>=x700208_NeedKillMonster_Count then
		return
	end

    local item = x700208_g_NpcCreate[index + 1]
	local nRet = 0
	if item.title~="" then
		nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.guid,-1,-1, item.facedir,  "",item.title);
	else
		nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.guid,-1,-1, item.facedir);
	
	end
	SetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_ID, nRet)
	SetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_INDEX, index+1)
	SetFubenData_Param(sceneId, x700208_CSP_CURRENTNPC_TICK, 0)

	x700208_ShowTipsToAll( sceneId, format("��%d�����ϳ��ֵ���Ӱ��", index+1))
end


function x700208_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700208_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700208_CSP_KILLCOUNT, nDieCount+1);

	

	nDieCount = nDieCount+1;
	--x700208_CreateBoss(sceneId,nDieCount)
	
	for i=0, 9 do
		local nBossId = GetFubenData_Param(sceneId, x700208_CSP_BOSS_ID_START+i )
		if nBossId== selfId then
			SetFubenData_Param(sceneId, x700208_CSP_BOSS_ID_START+i, -1 )
			x700208_ShowTipsToAll( sceneId, format("ɱ����%d�����ϵ����ֹ���", i+1))
			break;
		end
	end
		
	
	if nDieCount== x700208_NeedKillMonster_Count then
		
		--//--------------------------- ���纰�� Start--------------------
		--ɱ������ boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700208_CSP_TICKCOUNT)

--		local nowTime = x700208_g_TickTime* nowTickCount;

--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)

			
--		local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�

		
		
--		--LuaAllScenceM2Wrold (sceneId,x700208_g_FubenName.."���"..strPlayerName.."��"..strKillTime.."ɱ��"..strBossName, 0, 1)
		

		
		
		--//--------------------------- ���纰�� end----------------------
		x700208_OnAllMonsterDead( sceneId) 
	elseif nDieCount< x700208_NeedKillMonster_Count then
		x700208_CreateNpc(sceneId,nDieCount)
	end
end

function x700208_OnAllMonsterDead( sceneId)
	
	x700208_CreateSubmitNpc( sceneId)

	
end

function x700208_CreateSubmitNpc( sceneId)
	 x700208_ShowTipsToAll( sceneId, "������ɣ� ����npc�������ǵ�֮�ţ�")
	 local nRet = 0
	 if x700208_g_SubmitNPC.title~="" then
	 	nRet = CreateMonster(sceneId, x700208_g_SubmitNPC.type, x700208_g_SubmitNPC.x, x700208_g_SubmitNPC.z, 3, 0, -1, x700208_g_SubmitNPC.guid, -1,-1,x700208_g_SubmitNPC.facedir, "", x700208_g_SubmitNPC.title)
	 else
	 	nRet = CreateMonster(sceneId, x700208_g_SubmitNPC.type, x700208_g_SubmitNPC.x, x700208_g_SubmitNPC.z, 3, 0, -1, x700208_g_SubmitNPC.guid, -1,-1,x700208_g_SubmitNPC.facedir)
	 
	 end

	 SetFubenData_Param(sceneId, x700208_CSP_NPC_ID, nRet);
	 SetFubenData_Param(sceneId, x700208_CSP_B_NEED_TALK, 1);
end


function x700208_ShowTipsToAll( sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x700208_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700208_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





