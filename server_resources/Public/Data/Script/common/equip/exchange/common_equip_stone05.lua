----------------------------------------------------
-- �һ���ʯ����
----------------------------------------------------

x570014_g_ScriptId 					= 570014

x570014_g_LevelMin					= 60
x570014_g_LevelMax					= 100


x570014_g_ItemId					= 11990113
x570014_g_NeedItemCount				= 2	
x570014_g_ExtraType					=	4 --1: ������ 2�� ������ 3�������� 4���ﹱ   
x570014_g_EXCItemName       = "��ʯԭʯ"
x570014_g_ExtraCount				=	2000 -- ����ﹱ
x570014_g_BonusItemId				= 11000218



x570014_g_MissionName				= "���һ���������ʯ"
x570014_g_EnterInfo					= "\n\t����Ҫ2��#G��ʯԭʯ#W��2000#G�ﹱ#W�һ�1��#G������ʯ#W��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570014_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
    
  AddQuestNumText(sceneId, x570014_g_ScriptId, x570014_g_MissionName,3,1);
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570014_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
	
		AddQuestText(sceneId,"#Y"..x570014_g_MissionName)
		
		AddQuestText(sceneId,x570014_g_EnterInfo) 
		
		local suipiannum = GetItemCount(sceneId, selfId, x570014_g_ItemId) 
		local banggongnum = GetGuildUserPoint( sceneId, selfId )                    
		local strText1 = format("\n\t��������#R%d��#W#G%s#W��",suipiannum,x570014_g_EXCItemName)  
		local strText2 = format("\n\t��������#R%d#W��#G�ﹱ#W��",banggongnum) 
		--AddQuestText(sceneId,"#Y"..x570014_g_MissionName)                                    
		AddQuestText(sceneId,strText1)
		AddQuestText(sceneId,strText2)                                      		                 		
    AddQuestItemBonus(sceneId, x570014_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570014_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570014_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570014_ProcAccept( sceneId, selfId )

	x570014_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570014_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570014_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570014_OnRequestSubmit(sceneId, selfId)

	local iRet = x570014_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570014_OnApproveRequest(sceneId, selfId)
	end
end

function x570014_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570014_g_ItemId )

	if ItemCnt<x570014_g_NeedItemCount then
		local str =  format("ԭʯ����%d����",x570014_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570014_g_ExtraType==1 then		--����
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570014_g_ExtraType==2 then	--����
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570014_g_ExtraType==3 then  --����
        nExtraCount = GetMoney( sceneId, selfId, 0 )
    elseif x570014_g_ExtraType==4 then  --�ﹱ
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570014_g_ExtraCount then
		local str = ""

		if x570014_g_ExtraType==1 then		--����
			str = format("����������%d��",x570014_g_ExtraCount)
		elseif x570014_g_ExtraType==2 then	--����
			str = format("����������%d��",x570014_g_ExtraCount)
		elseif x570014_g_ExtraType==3 then  --����
			str = format("����������%d����",x570014_g_ExtraCount/1000)
        elseif x570014_g_ExtraType==4 then  --�ﹱ
   			str = format("���ﹱ����%d��",x570014_g_ExtraCount)
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

function x570014_OnApproveRequest(sceneId, selfId)

	if x570014_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570014_g_ItemId,x570014_g_NeedItemCount)


		local nExtraCount;
		local iRet=-1;
		if x570014_g_ExtraType==1 then		--����
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570014_g_ExtraCount)
		elseif x570014_g_ExtraType==2 then	--����
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570014_g_ExtraCount)
		elseif x570014_g_ExtraType==3 then  --����
            nExtraCount = GetMoney(sceneId, selfId, 0 )
            CostMoney(sceneId, selfId, 0, x570014_g_ExtraCount)            
        elseif x570014_g_ExtraType==4 then  --�ﹱ
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570014_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570014_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570014_g_BonusItemId, 1 )
	
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

