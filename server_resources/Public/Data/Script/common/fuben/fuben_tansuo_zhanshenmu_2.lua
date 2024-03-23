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

x700085_CSP_FUBENTYPE				= 	0
x700085_CSP_SCRIPTID				=	1
x700085_CSP_TICKCOUNT				= 	2
x700085_CSP_FROMSCENEID				= 	3
x700085_CSP_ISCLOSING				= 	4
x700085_CSP_LEAVECOUNTDOWN			= 	5
x700085_CSP_TEAMID					=	6
x700085_CSP_TICKTIME				=	7
x700085_CSP_HOLDTIME				=	8
x700085_CSP_FUBENLEVEL				=	9
								   
x700085_CSP_KILLCOUNT				=	20

x700085_CSP_OBJID_BOSS_START		=	21
x700085_CSP_OBJID_BOSS_END          =   22
x700085_CSP_FULL_HP_BOSS_START		= 	23
x700085_CSP_FULL_HP_BOSS_END        =   24

x700085_CSP_ITEMOBJ_TRAP1           =	25 --����1��itemid
x700085_CSP_ITEMOBJ_TRAP2           =   26 --����2��itemid
x700085_CSP_LAST_TIP_TICKCOUT       =   27 --boss2�ϴ�Ҫ��ɼ����ص�tickcount
x700085_CSP_ITEMOBJ_TRAP_TO_GATHER	=   28 --boss2Ҫ��ɼ��Ļ��ص�itemid
x700085_CSP_GATHER_WRONG			=   29 --�ɼ�ʧ���־
x700085_CSP_AREA_ID					=	30
x700085_CSP_AREA_FLAG				=	31

x700085_CSP_XIANJINBOSS				=	239

x700085_CSP_HUMAN_COUNT				=	240
x700085_CSP_PLAYER_ENTER_START		=	241

x700085_CSP_LAST_TICKOUNT			=	247
x700085_CSP_GUID_START              =   248
x700085_CSP_FUBEN_TYPE				=	254	--�������� 0:��ͨ(����),1:����,2:Ӣ��
x700085_CSP_FUBEN_MODE				=   255


------------------------Scene System Setting -----------------------------------
x700085_g_MissionId					=  6608
x700085_g_ScriptId 					= 700085

x700085_g_BuffId					= 7979
-------------------------fuben data begin-----------------------

x700085_g_GrowpointId_Trap1         = 543  --����1��Ӧ�ɼ���id
x700085_g_GrowpointId_Trap2         = 544  --����2��Ӧ�ɼ���id
x700085_g_Tips_Trap1                = "��ľ.....10����ȥ�ɼ��Ǳߵĺ�ľ,�������Ǿ�����Ѱ��·!"
x700085_g_Tips_Trap2                = "��ľ.....10����ȥ�ɼ��Ǳߵĵ�ľ,�������Ǿ�����Ѱ��·!"
x700085_g_Gether_Tips               = "��ȷ�ɼ����أ������������ū�Ĺ�����" --��ȷ�ɼ����غ���ʾ�û�

x700085_g_GPInterval				= 30000--���ر��ɼ����������ɵ�ʱ�䣨���룩
x700085_g_Tip_Interval              = 2  --boos2��ʾ�ɼ����غ�����Ѫ��ʱ����(������û����ȷ�ɼ�����,��λ:tick=5��)   

x700085_g_SubmitNPC                 =   { type =28508,guid= 150575,x = 92, z=100, facedir =180, title ="" }

-------------------------fuben data end-----------------------


----------------------------------------------------------
--�������Ի�npc���¼�
----------------------------------------------------------
function x700085_ProcEventEntry(sceneId,selfId,targetId)

end

-------------------------------------------------------------------------------
--�����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
-------------------------------------------------------------------------------
function x700085_OnFubenSceneCreated( sceneId )	
	 
	for i = 20,239 do
		SetFubenData_Param(sceneId, i,-1)
	end
							

	SetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1, -1)

	x700085_CreateBoss1(sceneId)
	x700085_CreateMonster( sceneId )									
end

-------------------------------------------------------------------------------
--��������
-------------------------------------------------------------------------------
function x700085_EnterTick(sceneId,nowTickCount)
  
	--��B0SS2Ѫ������90%��ÿ��N+10�����ð��c����ʽ��������Ҫ��ɼ�����1�����2��
	--�����û��������ȷ������ֱ�ӽ���ҵ�Ѫ����100Ѫ
	local nBossId2=GetFubenData_Param(sceneId,x700085_CSP_OBJID_BOSS_START+1)  
	if nBossId2 >=0 then
		local nCurrentHp = GetHp( sceneId, nBossId2 )
		local nFullHp = GetFubenData_Param(sceneId, x700085_CSP_FULL_HP_BOSS_START+1)

		if nCurrentHp < nFullHp*0.9 then
			
			local nLastTipCount = GetFubenData_Param(sceneId, x700085_CSP_LAST_TIP_TICKCOUT)
			local nTrapToGather = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP_TO_GATHER)
			
			ItemBoxId1 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP1)
			ItemBoxId2 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP2)

			if ItemBoxId1 ~= -1 or ItemBoxId2 ~= -1 then
				if nTrapToGather == -1 then --�״���ʾ����Ѫ

					if ItemBoxId1 ~= -1 and ItemBoxId2 ~= -1 then --���������ɼ�����ɲɼ�
						local nTrapTips	= ""
						local nTrapItemId = -1
						
						local rate = random(0,1)--50%�Ļ���
						if rate > 0.5 then							
							nTrapTips = x700085_g_Tips_Trap1
							nTrapItemId = ItemBoxId1
						else
							nTrapTips = x700085_g_Tips_Trap2
							nTrapItemId = ItemBoxId2
						end
										
						NpcTalk(sceneId, nBossId2, nTrapTips, -1)
						SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP_TO_GATHER,nTrapItemId)					
						SetFubenData_Param(sceneId, x700085_CSP_LAST_TIP_TICKCOUT,nowTickCount)
					end

				elseif nowTickCount - nLastTipCount  >= x700085_g_Tip_Interval then					
					--û�а�Ҫ��ɼ�,ֱ�ӽ���ҵ�Ѫ����250Ѫ 
					if ItemBoxId1 == nTrapToGather or ItemBoxId2 == nTrapToGather then
						local nGetherWrong = GetFubenData_Param(sceneId, x700085_CSP_GATHER_WRONG)
						if nGetherWrong <= 0 then
							SetFubenData_Param(sceneId, x700085_CSP_GATHER_WRONG,1)
						end

						x700085_SetPlayersHP(sceneId,250)					 
						SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP_TO_GATHER,-1)						
					end
				end
			end

		end		
	end

end

-------------------------------------------------------------------------------
--����ָ����boss1
-------------------------------------------------------------------------------
function x700085_CreateBoss1(sceneId)

	local nBossId=GetFubenData_Param(sceneId,x700085_CSP_OBJID_BOSS_START)
	if nBossId >=0 then
		return
	end

	x700085_CreateBossByIndex(sceneId,0)
end

-------------------------------------------------------------------------------
--����ָ����boss2
-------------------------------------------------------------------------------
function x700085_CreateBoss2(sceneId)

	local nBossId=GetFubenData_Param(sceneId,x700085_CSP_OBJID_BOSS_START+1)
	if nBossId >=0 then
		return
	end
	x700085_CreateBossByIndex(sceneId,1)
end

-------------------------------------------------------------------------------
--����ָ����boss
-------------------------------------------------------------------------------
function x700085_CreateBossByIndex(sceneId,bossIndex)

	--���boss�±�
    if bossIndex == nil or bossIndex < 0 or (bossIndex + x700085_CSP_OBJID_BOSS_START) > x700085_CSP_OBJID_BOSS_END then
	    return
	end

    local fubenlevel = GetFubenData_Param(sceneId, x700085_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700085_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700085_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700085_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700085_g_ScriptId,nIndexFrom,i)

		if idScript == x700085_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and bossIndex == flag and fuben_type == flag3 then
		    local objid = 0
			if title~="" then
				objid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700085_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				objid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700085_g_ScriptId, -1, 21,-1,facedir)
			
			end										

			if objid >=0 and patrolid>=0 then
				SetPatrolId(sceneId, objid, patrolid)				
			end

		    local nFullHp = GetHp( sceneId, objid )
            if flag == 0 or flag == 1 then
			    SetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+bossIndex, objid)
			    SetFubenData_Param(sceneId, x700085_CSP_FULL_HP_BOSS_START+bossIndex, nFullHp)
			end

        end
	end

end

---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700085_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700085_CSP_FUBENLEVEL )
	local fuben_type = GetFubenData_Param(sceneId, x700085_CSP_FUBEN_TYPE )

	local nIndexFrom = GetFubenDataPosByScriptID(x700085_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700085_g_ScriptId )

	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700085_g_ScriptId,nIndexFrom,i)

		if idScript == x700085_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and fuben_type == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x1 = x + rx
                local rz = random(-r,r)
                local z1 = z + rz

				local objid = 0
				if title~="" then
					objid = CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					objid = CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end

				if objid >=0 and patrolid>=0 then
					SetPatrolId(sceneId, objid, patrolid)				
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------------------------
function x700085_OnDie(sceneId, selfId, killerId)

	local nDieCount = GetFubenData_Param(sceneId, x700085_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700085_CSP_KILLCOUNT, nDieCount+1);
	
	local xianjinboss = GetFubenData_Param(sceneId, x700085_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	local objId1 = GetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START)

	--��ɱBOSS1�����1������2��BOSS2���֡�����ʾBOSS2������淨
	if selfId == objId1 then
	 	SetGrowPointIntervalContainer(sceneId,x700085_g_GrowpointId_Trap1,1)
		SetGrowPointIntervalContainer(sceneId,x700085_g_GrowpointId_Trap2,1)
		x700085_CreateBoss2(sceneId)
		x700085_ShowTipsToAll(sceneId, "������ū����,����Ѫ������90%ʱ���谴������ʾ�ɼ���ȷ����Ʒ��")
		SetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START,-1)		
	
	end

    --ɱ��boss2�����1������2��ʧ����������npc,
	local objId2 = GetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1)
	if selfId == objId2	 then
		local humancount = GetFuben_PlayerCount(sceneId);
			for ii = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, ii);
				CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,54 )
			end	
	
		--x700085_CreateSubmitNpc(sceneId)
		x700085_CreateXianJinBoss(sceneId)
		x700085_ShowTipsToAll(sceneId, "�ɹ���ɱ������ū��������ɡ�") 
		SetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1,-2)
	end

end

function x700085_ShowTipsToAll(sceneId, str)

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
---��������npc
---------------------------------------------------------------------------------------------------
function x700085_CreateSubmitNpc( sceneId)
	x700085_ShowTipsToAll(sceneId, "�������")
	if x700085_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700085_g_SubmitNPC.type, x700085_g_SubmitNPC.x, x700085_g_SubmitNPC.z, 3, 0, -1, x700085_g_SubmitNPC.guid, -1,-1,x700085_g_SubmitNPC.facedir, "", x700085_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700085_g_SubmitNPC.type, x700085_g_SubmitNPC.x, x700085_g_SubmitNPC.z, 3, 0, -1, x700085_g_SubmitNPC.guid, -1,-1,x700085_g_SubmitNPC.facedir)
		
	end

	--// add for �ֽ𸱱�
	 x700085_CreateXianJinBoss(sceneId)
	 --// add end
	 
	CallScriptFunction( 701104, "OnSceneBossDie", sceneId, 0)

	local nGetherWrong = GetFubenData_Param(sceneId, x700085_CSP_GATHER_WRONG)

	if nGetherWrong > 0 then
		CallScriptFunction( 701102, "OnSceneBossDie", sceneId, 0)
	end

end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700085_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700085_CSP_FUBEN_MODE)

	if nFubenMode~=1 and nFubenMode~=2 then
	  return
	end

	local fuben_type = GetFubenData_Param(sceneId, x700085_CSP_FUBEN_TYPE )
	if fuben_type ~= 0 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700085_CSP_FUBENLEVEL )

	local nIndexFrom = GetFubenDataPosByScriptID(x700085_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700085_g_ScriptId )

	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700085_g_ScriptId,nIndexFrom,i)

		if idScript == x700085_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700085_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700085_g_ScriptId, -1, 21,-1,facedir)
				
				end
				SetFubenData_Param(sceneId, x700085_CSP_XIANJINBOSS, nRet )
			end
        end
	end

	x700085_ShowTipsToAll(sceneId, "����������֣�")
end

---------------------------------------------------------------------------------------------------
--���������¼�
---------------------------------------------------------------------------------------------------
function x700085_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700085_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --����
		local BossId = GetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1)
		if BossId ~= -2 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700085_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700085_g_MissionId, x700085_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700085_g_MissionId, x700085_g_ScriptId)
	end
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700085_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700085_CSP_AREA_ID, -1)
end

---------------------------------------------------------------------------------------------------
--����ʱ��,����ʵ��
---------------------------------------------------------------------------------------------------
function x700085_ProcTiming( sceneId, selfId, ScriptId, MissionId )	
	local zoneId = GetFubenData_Param(sceneId, x700085_CSP_AREA_ID)
	
	if zoneId == 0 then
		local BossId = GetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1)
		if BossId ~= -2 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700085_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700085_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700085_g_MissionId, x700085_g_ScriptId)
	elseif zoneId == 1 then
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700085_g_MissionId, x700085_g_ScriptId)
	end
end

---------------------------------------------------------------------------------------------------
--�ɼ��㴴������
---------------------------------------------------------------------------------------------------
function x700085_OnCreate(sceneId,growPointType,x,y)

	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)
	if growPointType == x700085_g_GrowpointId_Trap1 then	
		SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP1,ItemBoxId)

	elseif growPointType == x700085_g_GrowpointId_Trap2	then
		SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP2,ItemBoxId)
    end

	local nItmeBoxId1 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP1)
	local nItemBoxId2 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP2)

	return 0
end

---------------------------------------------------------------------------------------------------
---�ɼ���򿪺���
---------------------------------------------------------------------------------------------------
function x700085_OnOpen(sceneId,selfId,targetId)	
	 return 0
end

---------------------------------------------------------------------------------------------------
---�ɼ�����պ���:return 0 ������գ��������
---------------------------------------------------------------------------------------------------
function x700085_OnRecycle(sceneId,selfId,targetId)
	return 1
end

---------------------------------------------------------------------------------------------------
---�ɼ���򿪺���
---------------------------------------------------------------------------------------------------
function x700085_OnProcOver(sceneId,selfId,targetId)

	
	--�ɼ���N�����زſ��ٴβɼ�����
	local ItemBoxId1 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP1)
	local ItemBoxId2 = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP2)
	local nTrapToGather = GetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP_TO_GATHER)


	if targetId == ItemBoxId1 then
		SetGrowPointIntervalContainer(sceneId,x700085_g_GrowpointId_Trap1,x700085_g_GPInterval)
		SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP1,-1)
	elseif targetId ==	ItemBoxId2	then
		SetGrowPointIntervalContainer(sceneId,x700085_g_GrowpointId_Trap2,x700085_g_GPInterval)
		SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP2,-1)
	end

	local objId2 = GetFubenData_Param(sceneId, x700085_CSP_OBJID_BOSS_START+1)
	if targetId == nTrapToGather and objId2 >= 0 then
		SetFubenData_Param(sceneId, x700085_CSP_ITEMOBJ_TRAP_TO_GATHER,-1)
		x700085_ShowTipsToAll(sceneId, x700085_g_Gether_Tips)
		local humancount = GetFuben_PlayerCount(sceneId);
		for ii = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, ii);
			SendSpecificImpactToUnit( sceneId, humanId, humanId, humanId, x700085_g_BuffId, 0)
		end	
	end

	return 0
end

---------------------------------------------------------------------------------------------------
---ֱ�ӽ�������ҵ�Ѫ����ĳһѪ��
---------------------------------------------------------------------------------------------------
function x700085_SetPlayersHP(sceneId,nToSetHP)

	if nToSetHP <=0 then		
		return
	end

	local humancount = GetFuben_PlayerCount(sceneId)

	for i= 0 ,humancount-1  do
	
		local nPlayerObjId = GetFuben_PlayerObjId(sceneId,i);

		if nPlayerObjId ~= -1 then		
			local ErrorCode = CallScriptFunction( FUBEN_COMMON_SCRIPT_CALL, "IsPlayerErrorState", sceneId, nPlayerObjId)
			if 	ErrorCode == 0 then
				local nCurrentHP = GetHp(sceneId,nPlayerObjId )				
				local nHurt = 0

--				if 	nCurrentHP > nToSetHP then
--					
--					nHurt =  nCurrentHP - nToSetHP
--						
--				else	
--					 nHurt = nCurrentHP
--				end
				nHurt = nCurrentHP / 2
				SetHp(sceneId,nPlayerObjId,-nHurt)

				local strPlayerName = GetName(sceneId, nPlayerObjId)
				nCurrentHP = GetHp(sceneId,nPlayerObjId )
				local str = "���"..strPlayerName.."Ѫ������"..nCurrentHP
				x700085_ShowTipsToAll(sceneId, str)
			end
		end
    end	
end