----------------------------------------------------
-- �һ���ʯ����
----------------------------------------------------

x570015_g_ScriptId 					= 570015

x570015_g_LevelMin					= 60
x570015_g_LevelMax					= 100


x570015_g_ItemId					= 11990113
x570015_g_NeedItemCount				= 1	
x570015_g_ExtraType					=	1 --1: ������ 2�� ������ 3�������� 4���ﹱ
x570015_g_ExtraCount				=	6000 -- ��������ֵ
x570015_g_BonusItemId				= 11000219



x570015_g_MissionName				= "���һ���ˮ����ʯ"
x570015_g_EnterInfo					= "\n\t1��#G��ʯԭʯ#W��6000#G����#W�һ�1��#Gˮ����ʯ#W��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570015_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570015_g_ScriptId, x570015_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570015_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		local suipiannum = GetItemCount(sceneId, selfId, x570015_g_ItemId)                        
		local rongyunum = GetHonor(sceneId, selfId)                                 
		local strText1 = format("\n\t��������#R%d��#W#G��ʯԭʯ#W��",suipiannum)  
		local strText2 = format("\n\t��������#R%d#W��#G����#W��",rongyunum)                     
		--AddQuestText(sceneId,"#Y"..x570015_g_MissionName) 
		  AddQuestText(sceneId,"#Y"..x570015_g_MissionName) 
		  AddQuestText(sceneId,x570015_g_EnterInfo)                                     
		  AddQuestText(sceneId,strText1)                                                           
		  AddQuestText(sceneId,strText2)                                      		                 
			
        AddQuestItemBonus(sceneId, x570015_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570015_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570015_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570015_ProcAccept( sceneId, selfId )

	x570015_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570015_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570015_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570015_OnRequestSubmit(sceneId, selfId)

	local iRet = x570015_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570015_OnApproveRequest(sceneId, selfId)
	end
end

function x570015_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570015_g_ItemId )

	if ItemCnt<x570015_g_NeedItemCount then
		local str =  format("ԭʯ����%d����",x570015_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570015_g_ExtraType==1 then		--����
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570015_g_ExtraType==2 then	--����
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570015_g_ExtraType==3 then  --����
        nExtraCount = GetMoney( sceneId, selfId, 0 )
    elseif x570015_g_ExtraType==4 then  --�ﹱ
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570015_g_ExtraCount then
		local str = ""

		if x570015_g_ExtraType==1 then		--����
			str = format("����������%d��",x570015_g_ExtraCount)
		elseif x570015_g_ExtraType==2 then	--����
			str = format("����������%d��",x570015_g_ExtraCount)
		elseif x570015_g_ExtraType==3 then  --����
			str = format("����������%d����",x570015_g_ExtraCount/1000)
        elseif x570015_g_ExtraType==4 then  --�ﹱ
   			str = format("���ﹱ����%d��",x570015_g_ExtraCount)
        else
			return 0;
		end

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	

	return 1;
	
end

function x570015_OnApproveRequest(sceneId, selfId)

	if x570015_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570015_g_ItemId,x570015_g_NeedItemCount)

	
		local nExtraCount;
		local iRet=-1;
		if x570015_g_ExtraType==1 then		--����
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570015_g_ExtraCount)
		elseif x570015_g_ExtraType==2 then	--����
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570015_g_ExtraCount)
		elseif x570015_g_ExtraType==3 then  --����
            nExtraCount = GetMoney(sceneId, selfId, 0 )
            CostMoney(sceneId, selfId, 0, x570015_g_ExtraCount)            
        elseif x570015_g_ExtraType==4 then  --�ﹱ
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570015_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570015_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570015_g_BonusItemId, 1 )
	
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

