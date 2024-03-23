--�����һ�ڤ������ʯ

x570042_g_ScriptId 					= 570042

x570042_g_LevelMin					= 1
x570042_g_LevelMax					= 100


x570042_g_ItemId					= 11000203
x570042_g_NeedItemCount				= 1	
x570042_g_ExtraType					=	2 --1: ������ 2�� ������ 3�������� 4���ﹱ
x570042_g_ExtraCount				=	5000 -- ��������/����ֵ
x570042_g_BonusItemId				= 11000508



x570042_g_MissionName				= "���һ���ڤ������ʯ"
x570042_g_EnterInfo					= "\n\t#G1#W��#G�촫ˮ��#W��#G5000����#W�һ�1��#Gڤ������ʯ#W��"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570042_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570042_g_ScriptId, x570042_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x570042_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--������Ϣ
    local suipiannum = GetItemCount(sceneId, selfId, x570042_g_ItemId)         
    local shengwangnum = GetShengWang( sceneId, selfId )                               		
    local strText1 = format("\n\t��������#R%d#W��#G�촫ˮ��#W��",suipiannum)   		
    local strText2 = format("\n\t��������#R%d#W��#G����#W��",shengwangnum)        		
		
		AddQuestText(sceneId,"#Y"..x570042_g_MissionName)
		AddQuestText(sceneId,x570042_g_EnterInfo)
		  AddQuestText(sceneId,strText1)
      AddQuestText(sceneId,strText2)   
       AddQuestItemBonus(sceneId, x570042_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570042_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x570042_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x570042_ProcAccept( sceneId, selfId )

	x570042_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570042_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570042_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570042_OnRequestSubmit(sceneId, selfId)

	local iRet = x570042_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570042_OnApproveRequest(sceneId, selfId)
	end
end

function x570042_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570042_g_ItemId )

	if ItemCnt<x570042_g_NeedItemCount then
		local str =  format("�촫ˮ������%d����",x570042_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570042_g_ExtraType==1 then		--����
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570042_g_ExtraType==2 then	--����
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570042_g_ExtraType==3 then  --����
        nExtraCount = GetPlayerGoodBadValue( sceneId, selfId )
    elseif x570042_g_ExtraType==4 then  --�ﹱ
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570042_g_ExtraCount then
		local str = ""

		if x570042_g_ExtraType==1 then		--����
			str = format("����������%d��",x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==2 then	--����
			str = format("����������%d��",x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==3 then  --����
			str = format("����������%d��",x570042_g_ExtraCount)
        elseif x570042_g_ExtraType==4 then  --�ﹱ
   			str = format("���ﹱ����%d��",x570042_g_ExtraCount)
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

function x570042_OnApproveRequest(sceneId, selfId)

	if x570042_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570042_g_ItemId,x570042_g_NeedItemCount)

	
		local nExtraCount;
		local iRet=-1;
		if x570042_g_ExtraType==1 then		--����
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==2 then	--����
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==3 then  --����
            nExtraCount = GetPlayerGoodBadValue(sceneId, selfId)
            SetPlayerGoodBadValue(sceneId, selfId, nExtraCount-x570042_g_ExtraCount)            
        elseif x570042_g_ExtraType==4 then  --�ﹱ
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570042_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570042_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570042_g_BonusItemId, 1 )
	
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

