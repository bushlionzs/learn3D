----------------------------------------------------
-- �����3����Ƕ����
----------------------------------------------------

x570023_g_ScriptId 					= 570023

x570023_g_LevelMin					= 60
x570023_g_LevelMax					= 160
x570023_g_DayCountUntil				= 1

x570023_g_ItemId					= 11990115
x570023_g_NeedItemCount				= 1	
x570023_g_BonusItemId				= 11990113
x570023_CSP_CURRENT_STEP			= 22
x570023_G_STEP						= 10
x570023_g_md_date					= MD_EQUIP_EXCHANGE3_DAY
x570023_g_md_daycount				= MD_EQUIP_EXCHANGE3_DAYCOUNT

x570023_g_MissionName				= "��ʮ�ֶһ�[��ʯԭʯ]"
x570023_g_EnterInfo					= "\t1��#Gԭ����ʯ��#W�һ�1��#G��ʯԭʯ#W��\n\t#Rÿ�ֽ��ܶһ�һ�Σ�������ѡ��һ���Ʒ��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570023_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x570023_g_LevelMin then
       return
    end

    if level > x570023_g_LevelMax then
		 return
    end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570023_CSP_CURRENT_STEP )
	
	if x570023_IsExchanged(sceneId, selfId) == 0  and x570023_G_STEP <= nCurrentGameStep then
		AddQuestNumText(sceneId, x570023_g_ScriptId, x570023_g_MissionName,3,1);
	end
	
end

function x570023_IsExchanged(sceneId, selfId)

	if( x570023_g_DayCountUntil > 0 ) then
		
		if x570023_GetDayCount(sceneId, selfId) >= x570023_g_DayCountUntil then

			return 1;
		end
	end
	return 0
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570023_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x570023_g_MissionName)
		AddQuestText(sceneId,x570023_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570023_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570023_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570023_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570023_ProcAccept( sceneId, selfId )

	x570023_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570023_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570023_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570023_OnRequestSubmit(sceneId, selfId)

	local iRet = x570023_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570023_OnApproveRequest(sceneId, selfId)
	end
end

function x570023_CheckRequest(sceneId, selfId)

	if( x570023_g_DayCountUntil > 0 ) then
		
		if x570023_GetDayCount(sceneId, selfId) >= x570023_g_DayCountUntil then

			local str = format("���ֽ��ܶһ�%d��",x570023_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

--	local nCurrentGameStep = GetFubenData_Param(sceneId, x570023_CSP_CURRENT_STEP )
--	
--	if nCurrentGameStep~=x570023_G_STEP then
--		local str = format("��ǰ�������ǵ�%d��",x570023_G_STEP)
--
--		BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--		EndQuestEvent();
--		DispatchQuestTips(sceneId, selfId);
--		return 0;
--	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570023_g_ItemId )

	if ItemCnt<x570023_g_NeedItemCount then
		local str = format("����������߲���%d��",x570023_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x570023_OnApproveRequest(sceneId, selfId)
	
	if x570023_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570023_g_ItemId,x570023_g_NeedItemCount)

	
		
		x570023_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x570023_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570023_g_BonusItemId, 1 )
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�һ��ɹ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1;
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ���������޷��õ���Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x570023_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570023_g_md_date[1], x570023_g_md_date[2],x570023_g_md_date[3] );
	
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, x570023_g_md_daycount[1], x570023_g_md_daycount[2],x570023_g_md_daycount[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x570023_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570023_g_md_date[1], x570023_g_md_date[2], x570023_g_md_date[3])

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, selfId, x570023_g_md_date[1], x570023_g_md_date[2], x570023_g_md_date[3], today)
		SetQuestData(sceneId, selfId, x570023_g_md_daycount[1], x570023_g_md_daycount[2], x570023_g_md_daycount[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, x570023_g_md_daycount[1], x570023_g_md_daycount[2], x570023_g_md_daycount[3])
		SetQuestData(sceneId, selfId, x570023_g_md_daycount[1], x570023_g_md_daycount[2], x570023_g_md_daycount[3], daycount+1)
	end
	
	
	
end