

------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x310374_g_scriptId 		= 310374


x310374_g_Title			=	"����������"

x310374_g_ItemId 		= 12041097

x310374_g_CostMoney		= 800

x310374_g_MaxCount		= 5

x310374_g_IsEnableId    = 1051
--��Ҫ�ĵȼ�
function x310374_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId,x310374_g_scriptId,x310374_g_Title, 3, 0)
end

function x310374_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
        if GetGameOpenById( x310374_g_IsEnableId) <= 0 then
            Msg2Player( sceneId, selfId, "�˻���첻���ţ����������", 8, 3)
            return
         end
        local daycount, num = x310374_GetDayCount(sceneId, selfId) 
        if num >0 then
		   str = format( "#GС��ʾ��\n\t\����컹���Թ���#R%d��@item_%d��",num, x310374_g_ItemId)
        else
           str =  format( "#GС��ʾ��\n\t\������Ѿ�����#R%d��@item_%d�ˣ������������",x310374_g_MaxCount, x310374_g_ItemId)
        end    
		BeginQuestEvent(sceneId)
	--������Ϣ
		AddQuestText(sceneId,"#Y"..x310374_g_Title)
		AddQuestText(sceneId,format( "\t@item_%d#W�ǲ��ɶ�õľ�����ҩ�����������ˣ���׹�֮��Ч����ֻҪ����һ˿���������������˻ָ�����״̬����@item_%d#W���������淽���������ƶ��ɵġ�\n\t���������������ÿ���������ﹺ��#G5��#W��ÿ�λ���#R800#W�Ľ�/�ֽ���1�������Ƿ�Ҫ����\n\t��@item_%d#W����˲��ظ�20000��������ȫ����ŭ������������ʸ���ӵ���ħ������������ȴʱ��Ϊ�����ӡ���", x310374_g_ItemId, x310374_g_ItemId, x310374_g_ItemId))
        AddQuestText(sceneId,str)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x310374_g_scriptId, -1);

end

function x310374_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

function x310374_CheckExchange(sceneId, selfId)

	local weekDay = GetWeek()
	if weekDay ~= 0 and weekDay ~= 6 then
		Msg2Player( sceneId, selfId, "ֻ��ÿ�����տ��Թ�����������", 8, 3)
		return 0
	end
	
	if x310374_GetDayCount(sceneId, selfId) == 0 then
		Msg2Player( sceneId, selfId, format("������Ѿ������%d���ˣ������������", x310374_g_MaxCount), 8, 3)
		return 0
	end
	
	if GetBagSpace(sceneId, selfId) <= 0 then
		Msg2Player( sceneId, selfId, "��Ʒ���������޷��õ���Ʒ��", 8, 3)
		return 0
	end
	
	return 1
end

function x310374_OnExchange(sceneId, selfId)
    if GetGameOpenById( x310374_g_IsEnableId) <= 0 then      
         return
    end
	local bind = 0
	if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310374_g_CostMoney,316) ~= 1 then
			bind = 1
            if CostMoney(sceneId, selfId, 3, x310374_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310374_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
		bind = 1
        if CostMoney( sceneId, selfId, 3, x310374_g_CostMoney) ~= 1 then
			bind = 0
            if CostMoney(sceneId, selfId, 2, x310374_g_CostMoney,316) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310374_g_CostMoney), 8, 3)
                return 0
            end
        end
    end

	BeginAddItem(sceneId)
	if bind == 1 then
		AddBindItem( sceneId, x310374_g_ItemId, 1 )
	else
		AddItem( sceneId, x310374_g_ItemId, 1 )
	end
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		Msg2Player( sceneId, selfId, "���ɹ�����1����������", 8, 3)
		GamePlayScriptLog(sceneId, selfId, 1691)
		return 1;
	else
		Msg2Player( sceneId, selfId, "��Ʒ���������޷��õ���Ʒ��", 8, 3)
		return 0;
	end
end
----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x310374_ProcAccept( sceneId, selfId )
	local iRet = x310374_CheckExchange(sceneId, selfId)

	if iRet>0 then
		if x310374_OnExchange(sceneId, selfId)>0 then
			x310374_SetDayCount(sceneId, selfId)
		end
	end
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x310374_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DATE[1], MD_DAGUANYUAN_SHOP_DATE[2],MD_DAGUANYUAN_SHOP_DATE[3])
	
	if today ~= lastday then
		return 1, x310374_g_MaxCount
	end
		
	local daycount = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DAYCOUNT[1], MD_DAGUANYUAN_SHOP_DAYCOUNT[2],MD_DAGUANYUAN_SHOP_DAYCOUNT[3])
	if daycount < x310374_g_MaxCount then
		return 1, x310374_g_MaxCount-daycount 
	end
	return 0, 0
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x310374_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DATE[1], MD_DAGUANYUAN_SHOP_DATE[2],MD_DAGUANYUAN_SHOP_DATE[3])

	if today ~= lastday then
		SetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DATE[1], MD_DAGUANYUAN_SHOP_DATE[2], MD_DAGUANYUAN_SHOP_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DAYCOUNT[1], MD_DAGUANYUAN_SHOP_DAYCOUNT[2], MD_DAGUANYUAN_SHOP_DAYCOUNT[3], 1)
	else
		local count = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DAYCOUNT[1], MD_DAGUANYUAN_SHOP_DAYCOUNT[2],MD_DAGUANYUAN_SHOP_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_DAGUANYUAN_SHOP_DAYCOUNT[1], MD_DAGUANYUAN_SHOP_DAYCOUNT[2], MD_DAGUANYUAN_SHOP_DAYCOUNT[3], count+1)
	end
end

