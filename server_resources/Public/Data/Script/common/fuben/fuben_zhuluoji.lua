---------------------------------------------------
-- File: 700027_fuben_ZHULUOJI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700027_CSP_FUBENTYPE				= 	0
x700027_CSP_SCRIPTID				=	1
x700027_CSP_TICKCOUNT				= 	2
x700027_CSP_FROMSCENEID				= 	3
x700027_CSP_ISCLOSING				= 	4
x700027_CSP_LEAVECOUNTDOWN			= 	5
x700027_CSP_TEAMID					=	6
x700027_CSP_BACKSCENEX       		=   7
x700027_CSP_BACKSCENEZ      		=   8
x700027_CSP_FUBENLEVEL			=	9

x700027_CSP_KILLCOUNT				=	20
x700027_CSP_FUBEN_SCENE_ID			=	21
x700027_CSP_BOSS1_ID				=	22

x700027_B_CREATE_RANDOMBOSS			=	230
x700027_CSP_RANDOM_BOSS_ID			=	231
x700027_RANDOMBOSS_FLAG				=	232

x700027_CSP_XIANJINBOSS				=	239

x700027_CSP_HUMAN_COUNT				=	240
x700027_CSP_OBJID_START				=	241
x700027_CSP_GUID_START              =   248  --��6��
x700027_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������

x700027_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700027_g_ScriptId 					= 700027
----------------------------- special for this Fuben --------------------
x700027_g_RandomBossRate			=   1--0.5

x700027_g_RandomMonsterRate			=	0.05

x700027_g_SubmitNPC                 =   { type =25041,guid= 150541,x = 23, z=68, facedir =0, title ="" }



x700027_g_Boss_Random_Pos			={
										{x=75,z=110 },
										{x=106,z=106},
										{x=71,z=70  },
										{x=96,z=35  },
										{x=66,z=31  },
										{x=80,z=92  }
									 }







-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700027_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	
end



function x700027_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700027_ShowTipsToAll(sceneId, str)

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
function x700027_OnFubenSceneCreated( sceneId )
	
	SetFubenData_Param(sceneId, x700027_CSP_XIANJINBOSS, -1 )
	x700027_CreateBoss( sceneId )
	x700027_CreateRandomBoss( sceneId )
    x700027_CreateMonster( sceneId )

	
		
end

function x700027_EnterTick(sceneId,nowTickCount)
end


function x700027_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
		
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title ~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1, facedir)
			
			end
			
			SetFubenData_Param(sceneId, x700027_CSP_BOSS1_ID, nRet )
			break;
				
        end
	end

end

function x700027_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700027_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)

	local nLen =0;
	for i, item in x700027_g_Boss_Random_Pos do
		nLen = nLen+1
	end

	local n = random(1,nLen)
	
	local x=x700027_g_Boss_Random_Pos[n].x;
	local z=x700027_g_Boss_Random_Pos[n].z;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			if flag == nFlag then
				if title ~="" then
					CreateMonster(sceneId, type, x,z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x,z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
		end
	end

	--x700027_ShowTipsToAll( sceneId, format("����boss�����ˣ���λ��x=%d,z=%d",x,z))

end





---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700027_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
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

function x700027_CreateRandomMonster(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	local rate = random(0,100)/100;
	local nStdRate = x700027_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	if rate>= nStdRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;


	
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir)
				
				end

				SetFubenData_Param(sceneId, x700027_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700027_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700027_CSP_RANDOM_BOSS_ID, nBossID)


			end
		end
	end

	x700027_ShowTipsToAll(sceneId, "ս�����֣�")

end



function x700027_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700027_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700027_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700027_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	local objId1 = GetFubenData_Param(sceneId, x700027_CSP_BOSS1_ID)

	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700027_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700027_CSP_RANDOM_BOSS_ID)
		if nRandomBossId==selfId then
			--//--------------------------- ���纰�� Start--------------------
			--ɱ��Random boss
			
			
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
				strCountryName = "¥��"
			elseif nCountry==1 then
				strCountryName = "��ɽ"
			elseif nCountry==2 then
				strCountryName = "����"
			elseif nCountry==3 then
				strCountryName = "�ػ�"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700027_RANDOMBOSS_FLAG)
			local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "�ױ�"
				elseif nHorseFlag==1 then
					strHorseName = "����"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "��ʨ"
				elseif nHorseFlag==1 then
					strHorseName = "ѱ¹"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "��Ϭ"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "���ݻ�"
				elseif nHorseFlag==1 then
					strHorseName = "��ţ"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 110 then
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
				strHorseName = "����"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			end



			local strMapName = "٪�޼�"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
		end
	end
	--//add end
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700027_CSP_BOSS1_ID, -1)
		
		x700027_CreateSubmitNpc( sceneId)

		x700027_CreateRandomMonster(sceneId)

--		--//--------------------------- ���纰�� Start--------------------
--			--ɱ��boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700027_CSP_TICKCOUNT)
--
--			local nowTime = x700027_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
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
--			local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--
--			
--			
--			LuaAllScenceM2Wrold (sceneId,"#R��ʿ����#G"..strPlayerName.."#R�Ĵ����½�����#G"..strKillTime.."#R���òб���"..strBossName.."��Ȼ���£�������������һ��˽�ɽ���񺣡�", 0, 1)
--			
--			
--			--//--------------------------- ���纰�� end----------------------
	end
end

function x700027_OnAllMonsterDead( sceneId)
	--x700027_CreateSubmitNpc( sceneId)
end

function x700027_CreateSubmitNpc( sceneId)
	 x700027_ShowTipsToAll( sceneId, "�������")
	if x700027_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700027_g_SubmitNPC.type, x700027_g_SubmitNPC.x, x700027_g_SubmitNPC.z, 3, 0, -1, x700027_g_SubmitNPC.guid, -1,-1,x700027_g_SubmitNPC.facedir, "", x700027_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700027_g_SubmitNPC.type, x700027_g_SubmitNPC.x, x700027_g_SubmitNPC.z, 3, 0, -1, x700027_g_SubmitNPC.guid, -1,-1,x700027_g_SubmitNPC.facedir)
		
	end

	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	
	CallScriptFunction( 701113, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction( 701114, "OnSceneBossDie", sceneId, 2)

	--// add for �ֽ𸱱�
	 x700027_CreateXianJinBoss(sceneId)
	 --// add end
end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700027_CreateXianJinBoss(sceneId)
	
	local nFubenType = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700027_CSP_FUBEN_MODE)

	if nFubenMode == 0  then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700027_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700027_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700027_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700027_g_ScriptId,nIndexFrom,i)
		if idScript == x700027_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700027_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700027_CSP_XIANJINBOSS, nRet )
		end
	end

	x700027_ShowTipsToAll(sceneId, "����������֣�")
end





