----------------------------------------------------
-- �����3����Ƕ����
----------------------------------------------------

x570026_g_ScriptId 					= 570026

x570026_g_LevelMin					= 60
x570026_g_LevelMax					= 160
x570026_g_DayCountUntil				= 1

x570026_g_ItemId					= 11990114
x570026_g_NeedItemCount				= 1	
x570026_g_BonusItemId				= 11990113
x570026_CSP_CURRENT_STEP			= 22
x570026_G_STEP						= 7
x570026_g_md_date					= MD_EQUIP_EXCHANGE4_DAY
x570026_g_md_daycount				= MD_EQUIP_EXCHANGE4_DAYCOUNT

x570026_g_MissionName				= "�����ֶһ�[��ʯԭʯ]"
x570026_g_EnterInfo					= "\t1��#G������ʯ��#W�һ�1��#G��ʯԭʯ#W��\n\t#Rÿ�ֽ��ܶһ�һ�Σ�������ѡ��һ���Ʒ��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570026_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x570026_g_LevelMin then
       return
    end

    if level > x570026_g_LevelMax then
		 return
    end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570026_CSP_CURRENT_STEP )
	
	if x570026_IsExchanged(sceneId, selfId) == 0  and x570026_G_STEP <= nCurrentGameStep then
		AddQuestNumText(sceneId, x570026_g_ScriptId, x570026_g_MissionName,3,1);
	end

	
end

function x570026_IsExchanged(sceneId, selfId)

	if( x570026_g_DayCountUntil > 0 ) then
		
		if x570026_GetDayCount(sceneId, selfId) >= x570026_g_DayCountUntil then

			return 1;
		end
	end
	return 0
	
end
---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570026_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x570026_g_MissionName)
		AddQuestText(sceneId,x570026_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570026_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570026_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570026_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570026_ProcAccept( sceneId, selfId )

	x570026_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570026_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570026_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570026_OnRequestSubmit(sceneId, selfId)

	local iRet = x570026_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570026_OnApproveRequest(sceneId, selfId)
	end
end

function x570026_CheckRequest(sceneId, selfId)

	if( x570026_g_DayCountUntil > 0 ) then
		
		if x570026_GetDayCount(sceneId, selfId) >= x570026_g_DayCountUntil then

			local str = format("���ֽ��ܶһ�%d��",x570026_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

--	local nCurrentGameStep = GetFubenData_Param(sceneId, x570026_CSP_CURRENT_STEP )
--	
--	if nCurrentGameStep~=x570026_G_STEP then
--		local str = format("��ǰ�������ǵ�%d��",x570026_G_STEP)
--
--		BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--		EndQuestEvent();
--		DispatchQuestTips(sceneId, selfId);
--		return 0;
--	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570026_g_ItemId )

	if ItemCnt<x570026_g_NeedItemCount then
		local str = format("����������߲���%d��",x570026_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x570026_OnApproveRequest(sceneId, selfId)

	if x570026_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570026_g_ItemId,x570026_g_NeedItemCount)

	
		x570026_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x570026_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570026_g_BonusItemId, 1 )
	
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
function x570026_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570026_g_md_date[1], x570026_g_md_date[2],x570026_g_md_date[3] );
	
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, x570026_g_md_daycount[1], x570026_g_md_daycount[2],x570026_g_md_daycount[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x570026_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570026_g_md_date[1], x570026_g_md_date[2], x570026_g_md_date[3])

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, selfId, x570026_g_md_date[1], x570026_g_md_date[2], x570026_g_md_date[3], today)
		SetQuestData(sceneId, selfId, x570026_g_md_daycount[1], x570026_g_md_daycount[2], x570026_g_md_daycount[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, x570026_g_md_daycount[1], x570026_g_md_daycount[2], x570026_g_md_daycount[3])
		SetQuestData(sceneId, selfId, x570026_g_md_daycount[1], x570026_g_md_daycount[2], x570026_g_md_daycount[3], daycount+1)
	end
	
	
	
end