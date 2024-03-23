----------------------------------------------------
-- �����3����Ƕ����
----------------------------------------------------

x570020_g_ScriptId 					= 570020

x570020_g_LevelMin					= 40
x570020_g_LevelMax					= 100
x570020_g_DayCountUntil				= 1

x570020_g_ItemId					= 11990114
x570020_g_NeedItemCount				= 1	
x570020_g_BonusItemId				= 11990112
x570020_CSP_CURRENT_STEP			= 22
x570020_G_STEP						= 8
x570020_g_md_date					= MD_EQUIP_EXCHANGE2_DAY
x570020_g_md_daycount				= MD_EQUIP_EXCHANGE2_DAYCOUNT

x570020_g_MissionName				= "�ڰ��ֶһ�[������ʯ��Ƭ]"
x570020_g_EnterInfo					= "\t1��#G������ʯ��Ƭ��#W�һ�1��#G������ʯ��Ƭ#W��\n\t#Rÿ�ֽ��ܶһ�һ�Σ�������ѡ��һ���Ʒ��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570020_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x570020_g_LevelMin then
       return
    end

    if level > x570020_g_LevelMax then
		 return
    end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570020_CSP_CURRENT_STEP )
	
	if nCurrentGameStep==x570020_G_STEP then
		AddQuestNumText(sceneId, x570020_g_ScriptId, x570020_g_MissionName,3,1);
	end
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570020_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x570020_g_MissionName)
		AddQuestText(sceneId,x570020_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570020_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570020_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570020_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570020_ProcAccept( sceneId, selfId )

	x570020_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570020_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570020_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570020_OnRequestSubmit(sceneId, selfId)

	local iRet = x570020_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570020_OnApproveRequest(sceneId, selfId)
	end
end

function x570020_CheckRequest(sceneId, selfId)

	if( x570020_g_DayCountUntil > 0 ) then
		
		if x570020_GetDayCount(sceneId, selfId) >= x570020_g_DayCountUntil then

			local str = format("���ֽ��ܶһ�%d��",x570020_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570020_CSP_CURRENT_STEP )
	
	if nCurrentGameStep~=x570020_G_STEP then
		local str = format("��ǰ�������ǵ�%d��",x570020_G_STEP)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570020_g_ItemId )

	if ItemCnt<x570020_g_NeedItemCount then
		local str = format("����������߲���%d��",x570020_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x570020_OnApproveRequest(sceneId, selfId)

	if x570020_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570020_g_ItemId,x570020_g_NeedItemCount)

	
		x570020_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x570020_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570020_g_BonusItemId, 1 )
	
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
function x570020_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570020_g_md_date[1], x570020_g_md_date[2],x570020_g_md_date[3] );
	
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, x570020_g_md_daycount[1], x570020_g_md_daycount[2],x570020_g_md_daycount[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x570020_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570020_g_md_date[1], x570020_g_md_date[2], x570020_g_md_date[3])

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, selfId, x570020_g_md_date[1], x570020_g_md_date[2], x570020_g_md_date[3], today)
		SetQuestData(sceneId, selfId, x570020_g_md_daycount[1], x570020_g_md_daycount[2], x570020_g_md_daycount[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, x570020_g_md_daycount[1], x570020_g_md_daycount[2], x570020_g_md_daycount[3])
		SetQuestData(sceneId, selfId, x570020_g_md_daycount[1], x570020_g_md_daycount[2], x570020_g_md_daycount[3], daycount+1)
	end
	
	
	
end