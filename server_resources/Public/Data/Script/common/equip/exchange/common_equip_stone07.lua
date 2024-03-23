----------------------------------------------------
-- �һ���ʯ����
----------------------------------------------------

x570016_g_ScriptId 					= 570016

x570016_g_LevelMin					= 60
x570016_g_LevelMax					= 100


x570016_g_ItemId					= 11990113
x570016_g_NeedItemCount				= 4	
x570016_g_ExtraType					=	2     --1: ������ 2�� ������ 3�������� 4���ﹱ
x570016_g_ExtraCount				=	15000 --��������ֵ
x570016_g_BonusItemId				= 11000220



x570016_g_MissionName				= "���һ����ι���ʯ"
x570016_g_EnterInfo					= "\n\t4��#G��ʯԭʯ#W��15000#G����#W�һ�1��#G�ι���ʯ#W��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570016_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570016_g_ScriptId, x570016_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570016_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
    local suipiannum = GetItemCount(sceneId, selfId, x570016_g_ItemId)         
    local shengwangnum = GetShengWang( sceneId, selfId )                               		
    local strText1 = format("\n\t��������#R%d��#W#G��ʯԭʯ#W��",suipiannum)   		
    local strText2 = format("\n\t��������#R%d#W��#G����#W��",shengwangnum)        		
		
		AddQuestText(sceneId,"#Y"..x570016_g_MissionName)
		AddQuestText(sceneId,x570016_g_EnterInfo)
		  AddQuestText(sceneId,strText1)
      AddQuestText(sceneId,strText2)   
       AddQuestItemBonus(sceneId, x570016_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570016_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570016_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570016_ProcAccept( sceneId, selfId )

	x570016_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570016_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570016_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570016_OnRequestSubmit(sceneId, selfId)

	local iRet = x570016_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570016_OnApproveRequest(sceneId, selfId)
	end
end

function x570016_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570016_g_ItemId )

	if ItemCnt<x570016_g_NeedItemCount then
		local str =  format("ԭʯ����%d����",x570016_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570016_g_ExtraType==1 then		--����
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570016_g_ExtraType==2 then	--����
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570016_g_ExtraType==3 then  --����
        nExtraCount = GetMoney( sceneId, selfId, 0 )
    elseif x570016_g_ExtraType==4 then  --�ﹱ
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570016_g_ExtraCount then
		local str = ""

		if x570016_g_ExtraType==1 then		--����
			str = format("����������%d��",x570016_g_ExtraCount)
		elseif x570016_g_ExtraType==2 then	--����
			str = format("����������%d��",x570016_g_ExtraCount)
		elseif x570016_g_ExtraType==3 then  --����
			str = format("����������%d����",x570016_g_ExtraCount/1000)
        elseif x570016_g_ExtraType==4 then  --�ﹱ
   			str = format("���ﹱ����%d��",x570016_g_ExtraCount)
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

function x570016_OnApproveRequest(sceneId, selfId)

	if x570016_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570016_g_ItemId,x570016_g_NeedItemCount)

	
		local nExtraCount;
		local iRet=-1;
		if x570016_g_ExtraType==1 then		--����
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570016_g_ExtraCount)
		elseif x570016_g_ExtraType==2 then	--����
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570016_g_ExtraCount)
		elseif x570016_g_ExtraType==3 then  --����
            nExtraCount = GetMoney(sceneId, selfId, 0 )
            CostMoney(sceneId, selfId, 0, x570016_g_ExtraCount)            
        elseif x570016_g_ExtraType==4 then  --�ﹱ
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570016_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570016_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570016_g_BonusItemId, 1 )
	
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

