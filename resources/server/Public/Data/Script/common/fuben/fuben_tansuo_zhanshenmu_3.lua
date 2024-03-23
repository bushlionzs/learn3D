---------------------------------------------------
-- File: 
-- Author: Peng Lin
-- Created: 2010-03-18
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700086_CSP_FUBENTYPE				= 	0
x700086_CSP_SCRIPTID				=	1
x700086_CSP_TICKCOUNT				= 	2
x700086_CSP_FROMSCENEID				= 	3
x700086_CSP_ISCLOSING				= 	4
x700086_CSP_LEAVECOUNTDOWN			= 	5
x700086_CSP_TEAMID					=	6
x700086_CSP_TICKTIME				=	7
x700086_CSP_HOLDTIME				=	8
x700086_CSP_FUBENLEVEL				=	9

x700086_CSP_KILLCOUNT				=	20
x700086_CSP_FINAL_BOSS_ID			=   21
x700086_CSP_FUBEN_SCENE_ID			=	22
x700086_CSP_AREA_TIMER				=	23
x700086_CSP_B_GROWPOINT_SHUAGUAI	=	24
x700086_CSP_B_GROWPOINT_BOSS		=	25
x700086_CSP_FINAL_BOSS2_ID			=	26
x700086_CSP_CAN_KILL_FINAL_BOSS		=	27
x700086_CSP_GROWPOINT_BOSS_ID		=	28
x700086_CSP_GP_BOXID1				=	29
x700086_CSP_GP_BOXID2				=	30

x700086_CSP_BROTHER_FULL_HP_START	=	40
x700086_CSP_BROTHER_TALK_START		=	45

x700086_CSP_GROWPOINT_MONSTER_COUNT	=	50
x700086_CSP_GROWPOINT_MONSTER_START	=	51
x700086_CSP_GROWPOINT_MONSTER_END   =   59--���ˢ9ֻ��

x700086_CSP_FINAL_BOSS_BROTHER_COUNT=   60
x700086_CSP_FINAL_BOSS_BROTHER_ID_START=	61
x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START=	70

x700086_CSP_AREA_ID					=   98
x700086_CSP_AREA_FLAG				=	99
x700086_CSP_SHUAGUAI_AREA_START		=	100
x700086_CSP_OBJID_AREA				=	120
x700086_CSP_XIANJINBOSS			= 121
x700086_CSP_BOSS1_SUB_MONSTER_FLAG				=	140
x700086_CSP_BOSS1_ID							=	141
x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT		=	142
x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT		=	143
x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT		=	144
x700086_CSP_BOSS1_SUB_MONSTER_ID_START			=	145	--Ŀǰ������12��С��
x700086_CSP_BOSS1_SUB_MONSTER_ID_END            =	156
x700086_CSP_RANDOM_BOSS_ID						=   157	--���ս��
x700086_RANDOM_BOSS_FLAG                        =   158	--���ս�� �����ʶ

x700086_CSP_B_GROWPOINT_OVER		=	239  -- ����±겻���޸�

x700086_CSP_HUMAN_COUNT				=	240
x700086_CSP_PLAYER_ENTER_START		=	241

x700086_CSP_LAST_TICKOUNT			=	247
x700086_CSP_GUID_START              =   248
x700086_CSP_FUBEN_TYPE				=	254	--�������� 0:��ͨ(����),1:����,2:Ӣ��

x700086_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700086_g_ScriptId 					= 700086
x700086_g_MissionId					= 6608
-------------------------fuben data begin-----------------------

x700086_g_Buff_Id					=	14110                   --�����һ����������buff

x700086_g_AreaTimer                 =   2000                    --�¼�����ʱ��
x700086_g_RandomMonsterRateList		=	{	--���ս����ּ���
											0.05,   --��ͨģʽ
											0.15,  --����ģʽ
											0.67,  --�ƽ�����ģʽ
										}
x700086_g_Boss_Brother_Relive_Time	=	6*8/2                       --�ػ�npc����ʱ��

x700086_g_GrowpointId				=   500                     --������
x700086_g_nGrowpointType			=	538                     --boss����������id
x700086_g_nGrowpointType2			=	537                     --boss����������id

x700086_g_listBrotherSayText = {
								"�������ƶ�������˵����ͽ�͵ģ�",
								"�Ҳ���һ������ս�����Ҳ���һ���ˣ�",
								"����4�����ܲ��ɷֵ����壡",
								"����������ͷ���ۣ���ͬʱ������4�˷��𹥻���",
								}

x700086_g_SubmitNPC                 =   { type =28509,guid= 150576,x = 71, z=28, facedir =0, title="" }
-------------------------fuben data end-----------------------


----------------------------------------------------------
--�������Ի�npc���¼�
----------------------------------------------------------
function x700086_ProcEventEntry(sceneId,selfId,targetId)

end


-------------------------------------------------------------------------------
--�����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
-------------------------------------------------------------------------------
function x700086_OnFubenSceneCreated( sceneId )
	
	for i=20,239 do
		SetFubenData_Param(sceneId, i, -1 )
	end
	
	x700086_CreateMonster( sceneId )              --monsterFlag = 0��1
	x700086_CreateBoss1(sceneId)	              --monsterFlag =  3
	x700086_CreateBoss(sceneId, 0 )	              --final boss monsterFlag =  4
	x700086_CreateBossBrother(sceneId, -1)		  --monsterFlag =  5


	SetFubenData_Param(sceneId, x700086_CSP_FUBEN_SCENE_ID,sceneId)
		
end


-------------------------------------------------------------------------------
--��������
-------------------------------------------------------------------------------
function x700086_EnterTick(sceneId, nowTickCount)

	x700086_OnAreaTimer( sceneId )

	local bCanKillFinalBoss = GetFubenData_Param(sceneId,x700086_CSP_CAN_KILL_FINAL_BOSS)

	if bCanKillFinalBoss<=0 then
		local nBossBrotherCount = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT )


		if nBossBrotherCount>0 then
			for i=0, nBossBrotherCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
				if nMonsterId== -1 then
					local nTickCount = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i)+1
					
					SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, nTickCount)

					if nTickCount == x700086_g_Boss_Brother_Relive_Time then
						x700086_CreateBossBrother(sceneId, i)

						local humancount = GetFuben_PlayerCount(sceneId);
						for	j = 0, humancount - 1 do
							local humanId = GetFuben_PlayerObjId(sceneId, j);
							local str = format("�������ظ�����", i);
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, str);
							EndQuestEvent(sceneId);
							DispatchQuestTips(sceneId, humanId);
						end
					end
				elseif nMonsterId>=0 then
					
					--// add in 2009-3-2 for The 2nd Internal Test
					local nCurrentHp = GetHp( sceneId, nMonsterId )
					local nFullHp = GetFubenData_Param(sceneId, x700086_CSP_BROTHER_FULL_HP_START+i )
					local bTalked = GetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+i )

					if bTalked<=0 then
						if nCurrentHp/nFullHp <=0.5 then
							SetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+i,1 )
							x700086_BrotherSay(sceneId,nMonsterId)
						end
					end
					--// add end
					

				end


				end
			end
		end

		--����Area17��BOSSÿʮ��ˢ��2��С�֣���ˢ��12��С��
		local bSubMonster = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_FLAG)
		if bSubMonster > 0 then
			local nBoss1ID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID)
			if nBoss1ID >= 0 then
				local nSubMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)
				local nSubMonsterLoopCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT)
				local nSubMonsterTickCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT)
				local nTickPassed = nowTickCount - nSubMonsterTickCount
				local nMaxNumber = 	x700086_CSP_BOSS1_SUB_MONSTER_ID_END - x700086_CSP_BOSS1_SUB_MONSTER_ID_START + 1
				if nSubMonsterCount < nMaxNumber then
					if nSubMonsterTickCount == 0 or nTickPassed == 2 then				
						x700086_CreateBoss1SubMonster(sceneId, nSubMonsterLoopCount)
						nSubMonsterLoopCount = nSubMonsterLoopCount + 1
						SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT,nSubMonsterCount )
						SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT,nowTickCount )
					end
				end
			end
		end

end

-------------------------------------------------------------------------------
--����ָ����boss
-------------------------------------------------------------------------------
function x700086_CreateBoss(sceneId, nFlag)


	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
		    local nObjId=0;
			if nFlag ==0 then
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, 7, aiscript, x700086_g_ScriptId, -1, -1, -1, facedir,  "",title)  -- ��ӪΪ-1. һ��ʼ����
				else
					nObjId = CreateMonster(sceneId, type, x, z, 7, aiscript, x700086_g_ScriptId, -1, -1, -1, facedir)  -- ��ӪΪ-1. һ��ʼ����
				end

				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_ID, nObjId )
			else
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1, facedir,  "",title)  -- ��ӪΪ-1. һ��ʼ����
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1, facedir)  -- ��ӪΪ-1. һ��ʼ����
				end

				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID, nObjId )
			end
			
			
			break
			
        end
	end

	if nFlag ==1 then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "���պ��ҷ�ŭ�ˣ�" ;
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end
	end

end
-------------------------------------------------------------------------------
--����ָ����brother boss
-------------------------------------------------------------------------------
function x700086_CreateBossBrother(sceneId, nTargetFlag)


	if nTargetFlag == nil then
		nTargetFlag = -1;
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount =0
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)

		if idScript == x700086_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
						
			if nTargetFlag == flag or nTargetFlag == -1 then
				local nObjId = 0
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1,facedir)
				
				end


				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_ID_START+flag, nObjId )
				SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+flag, 0 )
				nCount = nCount +1

				local nFullHp = GetHp( sceneId, nObjId )
				SetFubenData_Param(sceneId, x700086_CSP_BROTHER_FULL_HP_START+flag, nFullHp )
				SetFubenData_Param(sceneId, x700086_CSP_BROTHER_TALK_START+flag, 0 )

			end
			
        end
	end

	if nTargetFlag==-1 then

		SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT, nCount )
	end	

end

---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700086_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and (monsterFlag == 1 or monsterFlag == 2) and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir)
				
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--�������򴴽�Monster
---------------------------------------------------------------------------------------------------
function x700086_CreateAreaMonster(sceneId, areaId)
	
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	SetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId, 1)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 10 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            if areaId == flag1 then
				for j=0,count -1 do

					local rx = random(-r,r)
					local x = x + rx
					local rz = random(-r,r)
					local z = z + rz

					if title~="" then
						CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1, facedir,  "",title)
					else
						CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1, facedir)
					
					end
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--�����ͷ�С�ֵ�boss
---------------------------------------------------------------------------------------------------
function x700086_CreateBoss1(sceneId)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local bCreated =0;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then

		        local nObjId = -1
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
				
				end

				if patrolid>=0 then
					SetPatrolId(sceneId, nObjId, patrolid)
				end

			if nObjId >= 0 then
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_ID, nObjId)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_LOOP_COUNT, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT, 0)
				SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TICK_COUNT, 0)
			end

		end
	end	
end

---------------------------------------------------------------------------------------------------
--�����ͷ�С�ֵ�boss
---------------------------------------------------------------------------------------------------
function x700086_CreateBoss1SubMonster(sceneId,Index)



	local nCreateTotal = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)
	local nMaxCount    = x700086_CSP_BOSS1_SUB_MONSTER_ID_END - x700086_CSP_BOSS1_SUB_MONSTER_ID_START +1
	if nCreateTotal >= nMaxCount  then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	 
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)

		if idScript == x700086_g_ScriptId and monsterFlag == 3 and flag == Index and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
			for j=0,count -1 do

				local nTmpTotal = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)

				if nTmpTotal >= nMaxCount then
					return
				end

				local nObjId = -1
				
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
			
				end
				
				if nObjId >= 0 and patrolid >= 0 then
					SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_ID_START + nTmpTotal, nObjId)
					nTmpTotal = nTmpTotal + 1
					SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT,nTmpTotal)
					SetPatrolId(sceneId, nObjId, patrolid)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--brother˵��
---------------------------------------------------------------------------------------------------
function x700086_BrotherSay(sceneId,nMonsterId)
	if nMonsterId<0 then
		return
	end

	local nTextCount = 4;
	

	local nIndex = random(1,nTextCount)

	NpcTalk(sceneId, nMonsterId, x700086_g_listBrotherSayText[nIndex],  -1)


end

---------------------------------------------------------------------------------------------------
--�򿪲ɼ���󴴽��Ĺ�	monsterFlag == 8
---------------------------------------------------------------------------------------------------
function x700086_CreateGrowPointMonster(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	local nMaxcount = x700086_CSP_GROWPOINT_MONSTER_END - x700086_CSP_GROWPOINT_MONSTER_START + 1

	for i = 0,nDataCount-1 do
		
		if nCount >= nMaxcount then
			break
		end

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 8 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            
			for j=0,count -1 do

				if nCount >= nMaxcount then
					break
				end

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nObjId = 0
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir)
				end

				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+nCount, nObjId)
				nCount = nCount +1;

			end
			
        end
	end

	SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT, nCount)

	SetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI, 1)

end

---------------------------------------------------------------------------------------------------
--�����ɼ��㴥��������boss
---------------------------------------------------------------------------------------------------
function x700086_CreateGrowPointBoss(sceneId)
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_BOSS)

	if bCreated>0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )

	local nCount = 0;

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )

	for i = 0,nDataCount-1 do
			
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 9 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x1 + rx
				local rz = random(-r,r)
				local z = z1 + rz
				local nObjId = 0
				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_BOSS_ID, nObjId)
				nCount = nCount +1;
				break
			end
			
        end
	end

	SetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_BOSS, 1)

end

---------------------------------------------------------------------------------------------------
--����������ع�
---------------------------------------------------------------------------------------------------
function x700086_CreateRandomMonster(sceneId)

	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	if fuben_type ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700086_g_RandomMonsterRateList[1]
	local nFubenMode = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = x700086_g_RandomMonsterRateList[2]
	elseif nFubenMode ==2	then
		nStdRate = x700086_g_RandomMonsterRateList[3]
	end
	

	if rate >= nStdRate then
		return
	end
	
	local nFlag = random(0,3)

	local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
			
	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 and nFlag == flag then
		
			local rx = random(-r,r)
			local x = x1 + rx
			local rz = random(-r,r)
			local z = z1 + rz
			local nObjId = -1
			
			if title~="" then
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
			else
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
			
			end

			if nObjId >=0 then

				SetFubenData_Param(sceneId,x700086_CSP_RANDOM_BOSS_ID,nObjId)
				SetFubenData_Param(sceneId, x700086_RANDOM_BOSS_FLAG, nFlag)

				if patrolid>=0 then
					SetPatrolId(sceneId, nObjId, patrolid)	
				end
				x700086_ShowTipsToAll(sceneId, "ս�����֣�")
				return
			end

        end
	end

end

function x700086_ShowTipsToAll(sceneId, str)

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
---------------------------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------------------------
function x700086_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700086_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700086_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700086_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local nGrowPointMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT)

	local bGrowPoint = GetFubenData_Param(sceneId,x700086_CSP_B_GROWPOINT_SHUAGUAI)

	if bGrowPoint>0 then
		if nGrowPointMonsterCount>0 then
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i)
				
				if nMonsterId== selfId then
					SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i, -1)
				end
			end
			
			local bAllDie=1;
			for i=0, nGrowPointMonsterCount-1 do
				local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_START+i)
				if nMonsterId >= 0 then
					bAllDie = 0;
				end
			end

			if bAllDie==1 then
				SetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_MONSTER_COUNT, -1)
				x700086_CreateGrowPointBoss(sceneId)
			end

		end
	end

	local nBossBrotherCount = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS_BROTHER_COUNT )
	

	if nBossBrotherCount>0 then
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			
			if nMonsterId== selfId then
				SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i, -1)
				
				
				SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_TICKCOUNT_START+i, 0)
			end
		end

		local bAllDie=1;
		for i=0, nBossBrotherCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_ID_START+i)
			if nMonsterId~= -1 then
				bAllDie = 0;
			end
		end

		if bAllDie==1 then
			SetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_BROTHER_COUNT, -1)
			x700086_OnAllFinalBossBrotherDie(sceneId)
		end
	end

	local nFineBoss2Id = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID )

	if nFineBoss2Id>=0 then
		if nFineBoss2Id == selfId then
			SetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID, -2 )
			local humancount = GetFuben_PlayerCount(sceneId);
			for ii = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, ii);
				CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,55 )
			end	
		
				
			x700086_OnZhanShenDead( sceneId)

		end
	end


	local nGrowPointId = GetFubenData_Param(sceneId,x700086_CSP_GROWPOINT_BOSS_ID)

	if nGrowPointId>0 then
		if nGrowPointId== selfId then
		end
	end

	local nBoss1ID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID)
	if nBoss1ID>0 then
		if nBoss1ID == selfId then
			SetFubenData_Param(sceneId,x700086_CSP_BOSS1_ID, -1)
			SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 0)
			local nSubMonsterCount = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT)

			for i = 0, nSubMonsterCount -1 do
				local nSubMonsterID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i)
				if nSubMonsterID > 0 then

					DeleteMonster( sceneId,nSubMonsterID )		
				end
			end
		end
	end

	local nSubMonsterCount = GetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_TOTAL_COUNT )

	if nSubMonsterCount>0 then
		for i = 0, nSubMonsterCount - 1 do
			local nSubMonsterID = GetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i)
			
			if nSubMonsterID == selfId then
				SetFubenData_Param(sceneId,x700086_CSP_BOSS1_SUB_MONSTER_ID_START + i, -1)
			end
		end
	end

	x700086_OnRandomBossDie(sceneId, selfId, killerId)
end

---------------------------------------------------------------------------------------------------
--���boss������brother������
---------------------------------------------------------------------------------------------------
function x700086_OnAllFinalBossBrotherDie(sceneId)
	local nBossId = GetFubenData_Param(sceneId,x700086_CSP_FINAL_BOSS_ID)
	
	SetFubenData_Param(sceneId,x700086_CSP_CAN_KILL_FINAL_BOSS, 1)
	DeleteMonster( sceneId,nBossId )
	x700086_CreateBoss(sceneId, 1)

end

---------------------------------------------------------------------------------------------------
--����boss����Ĵ���
---------------------------------------------------------------------------------------------------
function x700086_OnZhanShenDead( sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "սʤ���պ��ң� ������ɣ����˳�������";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	x700086_CreateRandomMonster(sceneId)

	x700086_CreateXianJinBoss(sceneId)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	
	--x700086_ShowTipsToAll(sceneId, "������ɣ����˳�������")
	--x700086_CreateSubmitNpc( sceneId)
end

---------------------------------------------------------------------------------------------------
--�����������npc
---------------------------------------------------------------------------------------------------
function x700086_CreateSubmitNpc( sceneId)

	if x700086_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700086_g_SubmitNPC.type, x700086_g_SubmitNPC.x, x700086_g_SubmitNPC.z, 3, 0, -1, x700086_g_SubmitNPC.guid, -1, -1, x700086_g_SubmitNPC.facedir,  "",x700086_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700086_g_SubmitNPC.type, x700086_g_SubmitNPC.x, x700086_g_SubmitNPC.z, 3, 0, -1, x700086_g_SubmitNPC.guid, -1, -1, x700086_g_SubmitNPC.facedir)
		
	end

	x700086_CreateXianJinBoss(sceneId)
		
	CallScriptFunction( 701104, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction( 701105, "OnSceneBossDie", sceneId, 2)
	
end

---------------------------------------------------------------------------------------------------
--�����ֽ�boss
---------------------------------------------------------------------------------------------------

function x700086_CreateXianJinBoss(sceneId)

	local nFubenMode = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_MODE)

	if nFubenMode ~=1 and nFubenMode ~= 2 then
	  return
	end

	local fuben_type = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_TYPE )
	if fuben_type ~= 0 then
		return
	end

    local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL ) 

	local nIndexFrom = GetFubenDataPosByScriptID(x700086_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700086_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700086_g_ScriptId,nIndexFrom,i)
		if idScript == x700086_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir, "", title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700086_g_ScriptId, -1, 21, -1,facedir)
				
				end
				SetFubenData_Param(sceneId, x700086_CSP_XIANJINBOSS, nRet )
			end
        end
	end

	x700086_ShowTipsToAll(sceneId, "����������֣�")
end


---------------------------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------------------------
function x700086_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700086_CSP_AREA_ID, zoneId)
	if zoneId == 18 then  --����
		local BossId = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID)
		if BossId ~= -2 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700086_g_MissionId, x700086_g_ScriptId,1)
		
	elseif zoneId == 19 then 
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 1, x700086_g_MissionId, x700086_g_ScriptId)
	end
	local nScriptId = GetFubenData_Param(sceneId, x700086_CSP_SCRIPTID);

	if nScriptId~=x700086_g_ScriptId then
		CallScriptFunction( nScriptId, "ProcAreaEntered", sceneId, selfId, zoneId, MissionId)
		return
	end

	local humancount = GetFuben_PlayerCount(sceneId);

	local index = x700086_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			SetFubenData_Param(sceneId, idx+1, zoneId )

	    	break
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        SetFubenData_Param(sceneId, idx+1, zoneId )
	        break
		end
	end	

	if zoneId ==0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700086_g_Buff_Id,0 )
	elseif zoneId >=1 and zoneId<=9 then
		x700086_OnEnterShuaguaiArea(sceneId, selfId, zoneId)
	elseif zoneId == 17 then
		SetFubenData_Param(sceneId, x700086_CSP_BOSS1_SUB_MONSTER_FLAG, 1)
	end

end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700086_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	local index = x700086_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneId = GetFubenData_Param(sceneId, idx + 1 )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 )
	        SetFubenData_Param(sceneId, idx+1, -1 )
	    end
	end
	SetFubenData_Param(sceneId, x700086_CSP_AREA_ID, -1)
end

---------------------------------------------------------------------------------------------------
--����ʱ��,����ʵ��
---------------------------------------------------------------------------------------------------
function x700086_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700086_CSP_AREA_ID)
	if zoneId == 18 then  --����
		local BossId = GetFubenData_Param(sceneId, x700086_CSP_FINAL_BOSS2_ID)
		if BossId ~= -2 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700086_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 0, x700086_g_MissionId, x700086_g_ScriptId,1)
		
	elseif zoneId == 19 then 
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, 1, x700086_g_MissionId, x700086_g_ScriptId)
	end
end

---------------------------------------------------------------------------------------------------
--����˫������Ĵ���
---------------------------------------------------------------------------------------------------
function x700086_OnEnterShuaguaiArea(sceneId, selfId, areaId)
	
	
	if areaId<1 or areaId>9 then
		return
	end
	
	local bCreated = GetFubenData_Param(sceneId,x700086_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	x700086_CreateAreaMonster(sceneId, areaId)
end

---------------------------------------------------------------------------------------------------
--ÿ��tick����������߼�
---------------------------------------------------------------------------------------------------
function x700086_OnAreaTimer( sceneId )
	
    local index = x700086_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneid = GetFubenData_Param(sceneId, idx + 1 )

	    if objid ~= -1 then
			
			if zoneid>=10 and zoneid<=16 then  -- 10-17 area ��Ҽ�Ѫ
				--�������Ƿ����߻�������Ƿ���������������ǣ���ô��ִ�л��ռ�Ѫ�߼�CZG 2008-12-1
				local ErrorCode = CallScriptFunction( FUBEN_COMMON_SCRIPT_CALL, "IsPlayerErrorState", sceneId, objid)
				
				if ErrorCode == 0 then

					local hurt = 500				  					

					local havehp = GetHp( sceneId, objid )

					
					local hp = havehp - hurt
					if hp < 0 then
						hp = havehp -1
						hp = -hp
					else
						hp = -hurt
					end
					
					SetHp(sceneId,objid, hp )
				end
			end
        end
	end
end



---------------------------------------------------------------------------------------------------
--�ɼ��㴴������
---------------------------------------------------------------------------------------------------

function x700086_OnCreate(sceneId,growPointType,x,y)

	return 0

end


---------------------------------------------------------------------------------------------------
---�ɼ���򿪺���
---------------------------------------------------------------------------------------------------
function x700086_OnProcOver(sceneId,selfId,targetId)

	return 0

end


---------------------------------------------------------------------------------------------------
---�ɼ���򿪺���
---------------------------------------------------------------------------------------------------
function x700086_OnOpen(sceneId,selfId,targetId)
	
	return 0

end

---------------------------------------------------------------------------------------------------
---�ɼ�����պ���
---------------------------------------------------------------------------------------------------
function x700086_OnRecycle(sceneId,selfId,targetId)

	return 1

end

---------------------------------------------------------------------------------------------------
---�򿪲ɼ���500�Ĵ�����700080�ű��ص�
---------------------------------------------------------------------------------------------------
function x700086_OnGrowPoint(sceneId, selfId)

	local nFuben_SceneId = GetFubenData_Param(sceneId, x700086_CSP_FUBEN_SCENE_ID);--����������
	if nFuben_SceneId ~= sceneId then
		return
	end

	x700086_CreateGrowPointMonster(sceneId)

	SetFubenData_Param(sceneId, x700086_CSP_B_GROWPOINT_OVER,1)

end

---------------------------------------------------------------------------------------------------
---���ս������֮����
---------------------------------------------------------------------------------------------------
function x700086_OnRandomBossDie(sceneId, selfId, killerId)

	local nRandomBossID = GetFubenData_Param(sceneId,x700086_CSP_RANDOM_BOSS_ID)

	if nRandomBossID >= 0 then
		if nRandomBossID == selfId then

			----------------------------- ���纰�� Start--------------------

			--��ȡ��ɫ����
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType == 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)				
			end
			local strPlayerName = GetName(sceneId, nOwnerId)

			--��ȡ��ɫ���ڹ���
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

			--��ȡ���ս����������
			local nHorseFlag = GetFubenData_Param(sceneId, x700086_RANDOM_BOSS_FLAG)
			local fubenlevel = GetFubenData_Param(sceneId, x700086_CSP_FUBENLEVEL )
			
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
			elseif fubenlevel < 95 then
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
					strHorseName = "��"
				elseif nHorseFlag==1 then
					strHorseName = "�Ϸ�"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "��"
				elseif nHorseFlag==1 then
					strHorseName = "�Ϸ�"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			end

			--��ͼ����
			local strMapName = "����Ĺ"
			
			--����
			LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)		
			----------------------------- ���纰�� End--------------------
		end
	end
end
