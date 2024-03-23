---------------------------------------------------
-- File; 700004_fuben_dawushi_scene.lua
-- Author; ZP Wang
-- Created; 2008-12-19
-- Version; 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700004_CSP_FUBENTYPE				= 	0
x700004_CSP_SCRIPTID				=	1
x700004_CSP_TICKCOUNT				= 	2
x700004_CSP_FROMSCENEID				= 	3
x700004_CSP_ISCLOSING				= 	4
x700004_CSP_LEAVECOUNTDOWN			= 	5
x700004_CSP_TEAMID					=	6
x700004_CSP_BACKSCENEX       		=   7
x700004_CSP_BACKSCENEZ      		=   8
x700004_CSP_FUBENLEVEL			=	9

x700004_CSP_KILLCOUNT				=	20
x700004_CSP_FINALBOSS_OBJID			=   21
x700004_CSP_RELIVE_COUNT1			=   22
x700004_CSP_RELIVE_COUNT2			=   23
x700004_CSP_RELIVE_COUNT3			=   24
x700004_CSP_RELIVE_COUNT4			=   25
x700004_CSP_RELIVE_COUNT5			=   26
x700004_CSP_RELIVE_COUNT6			=   27

x700004_CSP_RELIVE_START1			=   40
x700004_CSP_RELIVE_START2			=   50
x700004_CSP_RELIVE_START3			=   60
x700004_CSP_RELIVE_START4			=   70
x700004_CSP_RELIVE_START5			=   80
x700004_CSP_RELIVE_START6			=   90

x700004_B_CREATE_RANDOMBOSS			=	230
x700004_CSP_RANDOM_BOSS_ID			=	231
x700004_RANDOMBOSS_FLAG				=	232
x700004_CSP_GUID_START              =   248  --��6��
x700004_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������
x700004_CSP_FUBEN_MODE				=   255 
------------------------Scene System Setting -----------------------------------

x700004_g_ScriptId 					= 700004
-------------------------- special for this fuben -----------------
x700004_RefreshTime					= 360		                --�����ָ���ʱ��
x700004_g_RandomBossRate			= 0                         --����boss���ּ���
x700004_g_RandomMonsterRate			= 0.1                       --����boss���ּ���
x700004_g_EnterBuffId				= 14309                     --���븱�������buff



x700004_g_SubmitNPC                 =   { type =25005,guid= 150505,x = 27, z=100, facedir = 0, title = "" }

--BOSS����
x700004_g_NpcType1                  =   25005                    --NPC ID
x700004_g_NpcGroup                  =   {
											{   hash = 1,type = x700004_g_NpcType1,x=23,z=22,ai=3,aiscript = 0, guid= 150002, facedir=0, title=""  },
										}



---------  ���boss 
x700004_g_Random_Boss_Type_Count = 4

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700004_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


function x700004_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700004_ShowTipsToAll(sceneId, str)

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
--OnFubenSceneCreated  ;  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700004_OnFubenSceneCreated( sceneId )
	-- @Param sceneId;  ��������id

	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1,0);
	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2,0);
	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3,0);
	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4,0);
	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5,0);
	SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6,0);
	

	x700004_CreateBoss( sceneId )
	x700004_CreateRandomBoss( sceneId )
    x700004_CreateMonster( sceneId )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		 x700004_AddPlayerBuff(sceneId, humanId,1)
	end
		
end

function x700004_AddPlayerBuff(sceneId, selfId, nFlag)
	local haveImpact = IsHaveSpecificImpact( sceneId, selfId, x700004_g_EnterBuffId )
	if haveImpact == 1 then
		
		if nFlag == 1 then
			return
		end
		CancelSpecificImpact(sceneId, selfId, x700004_g_EnterBuffId);
		
	end

	

	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700004_g_EnterBuffId,0 )
end

function x700004_RemovePlayerBuff(sceneId, selfId)
	local haveImpact = IsHaveSpecificImpact( sceneId, selfId, x700004_g_EnterBuffId )
	if haveImpact == 1 then

		CancelSpecificImpact(sceneId, selfId, x700004_g_EnterBuffId);
	end
end

function x700004_EnterTick(sceneId, nowTickCount)
	if nowTickCount > 6 then
	   if mod(nowTickCount, x700004_RefreshTime) == 0 then
			x700004_CheckReliveMonster(sceneId)
	   end 
	end
end


function x700004_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
			end

			if flag ==1 then
				SetFubenData_Param(sceneId, x700004_CSP_FINALBOSS_OBJID, nRet ) ;
			end
        end
	end

end

function x700004_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700004_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,3)

	local nType = random(0,x700004_g_Random_Boss_Type_Count-1)

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;


	
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		
		if nType == flag then
			if idScript == x700004_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
				local x,z;
				if nFlag==0 then
					x = 32
					z = 68
				else
					x = 91
					z = 80
				end
				if title~="" then
					CreateMonster(sceneId, type, x,z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x,z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
			end
		end
		
	end

end




---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700004_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local monsterid = 0
				if title~="" then
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end

				SetPatrolId(sceneId, monsterid, 0)
            end
        end
	end

	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local monsterid = 0;
				if title ~="" then
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end

				SetPatrolId(sceneId, monsterid, 1)
            end
        end
	end

	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local monsterid = 0
				if title~="" then
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
				SetPatrolId(sceneId, monsterid, 2)
            end
        end
	end

	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 8 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then
           
			if title~="" then
				CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
			else
				CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
        end
	end

	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel  and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz

		        local nRet = 0;
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir, "", title);
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir);
				end

				if flag == 0 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1+nCount+1, nRet);
				elseif flag ==1 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2+nCount+1, nRet);
				elseif flag==2 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3+nCount+1, nRet);
				elseif flag==3 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4+nCount+1, nRet);
				elseif flag==4 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5+nCount+1, nRet);
				elseif flag==5 then
					local nCount = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6);
		
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6,nCount+1);
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6+nCount+1, nRet);
				end
				
				
            end
        end
	end

end

function x700004_ReliveMonster( sceneId, index, index2)  --�����ָ���

	
	 local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if index == flag then
				 local rx = random(-r,r)
				 local x = x + rx
				 local rz = random(-r,r)
				 local z = z + rz	

				 local nRet = 0
				 if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21,  "",title)
				 else
				 	nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700004_g_ScriptId, -1, 21)
				 end

				 if index ==0 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1+index2, nRet);
				 elseif index==1 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2+index2, nRet);
				 elseif index==2 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3+index2, nRet);
				 elseif index==3 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4+index2, nRet);
				 elseif index==4 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5+index2, nRet);
				 elseif index==5 then
					SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6+index2, nRet);
				 end
				 
				 return 1;
			end
		end
	end
end

function x700004_CheckReliveMonster(sceneId)
	local n1 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1);
	local n2 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2);
	local n3 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3);
	local n4 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4);
	local n5 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5);
	local n6 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6);

	

	for i=1, n1 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1+i);
		
		if nObjId == -1 then
			
			x700004_ReliveMonster( sceneId, 0, i);
			
		end
	end

	for i=1, n2 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2+i);
		
		if nObjId == -1 then
			
			x700004_ReliveMonster( sceneId, 1,i);
			
		end
	end

	for i=1, n3 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3+i);
		if nObjId == -1 then
			x700004_ReliveMonster( sceneId, 2,i);
			
		end
	end

	for i=1, n4 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4+i);
		if nObjId == -1 then
			x700004_ReliveMonster( sceneId, 3,i);
			
		end
	end

	for i=1, n5 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5+i);
		if nObjId == -1 then
			x700004_ReliveMonster( sceneId, 4,i);
			
		end
	end

	for i=1, n6 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6+i);
		
		if nObjId == -1 then
			x700004_ReliveMonster( sceneId, 5,i);
			
		end
	end
end

---------------------------------------------------------------------------------------------------
--����NPC
---------------------------------------------------------------------------------------------------
function x700004_CreateNpc(sceneId )

  	for i, item in x700004_g_NpcGroup do
  		if title~="" then
			CreateMonster( sceneId,type,x,z,ai,aiscript,-1,guid,-1,-1, facedir, "", title)
		else
			CreateMonster( sceneId,type,x,z,ai,aiscript,-1,guid,-1,-1, itme.facedir)
		end
	end
end



function x700004_CreateRandomMonster(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local rate = random(0,100)/100;
	local nStdRate = x700004_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	if rate>= nStdRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;


	
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if flag == nFlag then
		
		
			if idScript == x700004_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700004_g_ScriptId, -1, 21,-1,facedir)
				
				end

				SetFubenData_Param(sceneId, x700004_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700004_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700004_CSP_RANDOM_BOSS_ID, nBossID)
			end
		end
	end

	x700004_ShowTipsToAll(sceneId, "ս�����֣�")

end

function x700004_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700004_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700004_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700004_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700004_CSP_RANDOM_BOSS_ID)
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

			local nHorseFlag = GetFubenData_Param(sceneId, x700004_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL )
			
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

		


			local strMapName = "��Ѩ"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
		end
	end
	--//add end

	local objId1 = GetFubenData_Param(sceneId, x700004_CSP_FINALBOSS_OBJID ) ;

--	--//--------------------------- ���纰�� Start--------------------
--	
--	local nowTickCount = GetFubenData_Param(sceneId, x700004_CSP_TICKCOUNT)
--
--	local nowTime = x700004_g_TickTime* nowTickCount;
--
--	local nMinute = floor(nowTime/60)
--	local nSec = mod(nowTime,60)
--
--		
--	local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
--	-------- if killed by pet -----------------
--	local nKillerType = GetObjType(sceneId, killerId)
--	--PrintStr(nKillerType)
--	if nKillerType== 3 then
--		local nOwnerId = GetOwnerID(sceneId, killerId)
--		strPlayerName = GetName(sceneId, nOwnerId)
--	end
--	--------- end -------------------------------
--	
--	local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--	local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--	
--	
--	if selfId == objId1 then -- boss flag=0
--		LuaAllScenceM2Wrold (sceneId,"#R��ͷ������������������һ�ڶ񶾵Ļ��棬�����ر������۾�������ôҲ�벻�������������ɹž��񲿶ӵ�������#G"..strPlayerName.."#R����Ķ��������#G"..strKillTime.."#R�ͳ��׵ش���ˡ�", 0, 1)
--	end
--
--	
	
	--//--------------------------- ���纰�� end----------------------

	if objId1>=0 then
		if objId1== selfId then
			SetFubenData_Param(sceneId, x700004_CSP_FINALBOSS_OBJID,-1 )
			x700004_CreateSubmitNpc( sceneId)

			x700004_CreateRandomMonster(sceneId)
		end
	end

	local n1 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1);
	local n2 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2);
	local n3 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3);
	local n4 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4);
	local n5 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5);
	local n6 = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6);

	

	for i=1, n1 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START1+i, -1);
			return 1;
		end
	end

	for i=1, n2 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START2+i, -1);
			return 1;
		end
	end

	for i=1, n3 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START3+i, -1);
			return 1;
		end
	end

	for i=1, n4 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START4+i, -1);
			return 1;
		end
	end

	

	for i=1, n5 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5+i);
		
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START5+i, -1);
			return 1;
		end
	end

	for i=1, n6 do
		local nObjId = GetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700004_CSP_RELIVE_START6+i, -1);
			return 1;
		end
	end
	
				
end

function x700004_OnAllMonsterDead( sceneId)
	
	--x700004_CreateMonster3( sceneId )
	--x700004_CreateNpc( sceneId )
	x700004_CreateSubmitNpc( sceneId)
end

function x700004_CreateSubmitNpc( sceneId)
	if x700004_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700004_g_SubmitNPC.type, x700004_g_SubmitNPC.x, x700004_g_SubmitNPC.z, 3, 0, -1, x700004_g_SubmitNPC.guid, -1,-1,x700004_g_SubmitNPC.facedir, "", x700004_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700004_g_SubmitNPC.type, x700004_g_SubmitNPC.x, x700004_g_SubmitNPC.z, 3, 0, -1, x700004_g_SubmitNPC.guid, -1,-1,x700004_g_SubmitNPC.facedir)
		
	end

	--// add for �ֽ𸱱�
	 x700004_CreateXianJinBoss(sceneId)
	 --// add end
	
	CallScriptFunction( 701101, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction( 701102, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700004_CreateXianJinBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700004_CSP_FUBEN_MODE)

	if nFubenMode ==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700004_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700004_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700004_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700004_g_ScriptId,nIndexFrom,i)
		if idScript == x700004_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
			end
			
		end
	end

	x700004_ShowTipsToAll(sceneId, "����������֣�")
end






