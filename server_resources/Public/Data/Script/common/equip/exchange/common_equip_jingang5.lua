----------------------------------------------------
-- �һ��̺����
----------------------------------------------------

x570069_g_ScriptId 					= 570069

x570069_g_LevelMin					= 75
x570069_g_LevelMax					= 100


x570069_g_ItemId1					= 11000218
x570069_g_NeedItemCount1				= 1	
x570069_g_ItemId2					= 11010014
x570069_g_NeedItemCount2				= 1	
x570069_g_BonusItemId				= 11000226



x570069_g_MissionName				= "���һ����̺����"
x570069_g_EnterInfo					= "\n\t1��#G������ʯ#W��1��#Gҹ����#W�һ�1��#G�̺����#W��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570069_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570069_g_ScriptId, x570069_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570069_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		local suipiannum = GetItemCount(sceneId, selfId, x570069_g_ItemId1)       
		local yemingzhu = GetItemCount(sceneId, selfId, x570069_g_ItemId2)              
		local strText1 = format("\n\t��������#R%d��#W#G������ʯ#W��",suipiannum) 
		local strText2 = format("\n\t��������#R%d��#W#Gҹ����#W��",yemingzhu)     
		
		AddQuestText(sceneId,"#Y"..x570069_g_MissionName)
		AddQuestText(sceneId,x570069_g_EnterInfo)
		
		AddQuestText(sceneId,strText1)
		AddQuestText(sceneId,strText2) 
		
        AddQuestItemBonus(sceneId, x570069_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570069_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570069_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570069_ProcAccept( sceneId, selfId )

	x570069_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570069_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570069_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570069_OnRequestSubmit(sceneId, selfId)

	local iRet = x570069_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570069_OnApproveRequest(sceneId, selfId)
	end
end

function x570069_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570069_g_ItemId1 )

	if ItemCnt<x570069_g_NeedItemCount1 then
		local str =  format("������ʯ����%d����",x570069_g_NeedItemCount1)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570069_g_ItemId2 )

	if ItemCnt<x570069_g_NeedItemCount2 then
		local str =  format("ҹ���鲻��%d����",x570069_g_NeedItemCount2)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	

	return 1;
	
end

function x570069_OnApproveRequest(sceneId, selfId)

	if x570069_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570069_g_ItemId1,x570069_g_NeedItemCount1)
    local iRet = DelItem(sceneId, selfId,x570069_g_ItemId2,x570069_g_NeedItemCount2)

	end
		
	
	
end


function x570069_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570069_g_BonusItemId, 1 )
	
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

