

------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x310391_g_scriptId 		= 310391


x310391_g_Title			=	"����ӡ�һ�"

x310391_g_ItemId 		= 11000597

-- ���Ѽ۸�
x310391_g_CostMoney             = 500

--��Ҫ�ĵȼ�
function x310391_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId,x310391_g_scriptId,x310391_g_Title, 3, 1)
	
end

function x310391_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

		BeginQuestEvent(sceneId)
	--������Ϣ
		AddQuestText(sceneId,"#Y"..x310391_g_Title)
		AddQuestText(sceneId,format( "\t@item_%d#W��ʱװ�����ıر����ߡ�ֻҪ���ܽ��й�����ٻŮ�Ļ���Ҥ������������������һ�һ��@item_%d��\n\t#W�Ƿ񻨷�#R500#W�Ľ�/�ֽ�ȡһ��@item_%d#W��", x310391_g_ItemId, x310391_g_ItemId , x310391_g_ItemId))
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x310391_g_scriptId, -1);

end

function x310391_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

function x310391_CheckExchange(sceneId, selfId)
	
	local weekDay = GetWeek()
	if weekDay  ~= 6 and weekDay ~= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ֻ�������ղ��ܶһ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
	local weekIndex = GetWeekIndex()
	local week = GetQuestData(sceneId, selfId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3])
	if weekIndex == week then
		if GetQuestData(sceneId, selfId, MD_FUBEN_XIAOQIAN_FLAG[1], MD_FUBEN_XIAOQIAN_FLAG[2], MD_FUBEN_XIAOQIAN_FLAG[3]) == 1 then
			Msg2Player( sceneId, selfId, "�㱾���Ѿ��һ���һ�Σ������ٴζһ�", 8, 3)
			return 0
		end
	else 
		Msg2Player( sceneId, selfId, "�㱾��û����ɸ���ٻŮ�Ļ���Ҥ���������ܶһ�", 8, 3)
		return 0
	end
	--end
	
	if GetBagSpace(sceneId, selfId) <= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��Ʒ���������޷��õ���Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
    
    return 1
	
end

function x310391_OnExchange(sceneId, selfId)

	if GetGoldMode( sceneId, selfId) == 1 then
        if CostMoney( sceneId, selfId, 2, x310391_g_CostMoney,315) ~= 1 then
            if CostMoney(sceneId, selfId, 3, x310391_g_CostMoney) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310391_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
            if CostMoney(sceneId, selfId, 3, x310391_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310391_g_CostMoney,315) ~= 1 then
                Msg2Player( sceneId, selfId, format( "�����ϵĽ�/�ֽ���#R%d#cffcc00��", x310391_g_CostMoney), 8, 3)
                return 0
            end
        end
    end
    
    
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x310391_g_ItemId, 1 )
	
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
----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x310391_ProcAccept( sceneId, selfId )
	local iRet = x310391_CheckExchange(sceneId, selfId)

	if iRet>0 then
		if x310391_OnExchange(sceneId, selfId)>0 then
			--local iRet = DelItem(sceneId, selfId, x310391_g_ItemId,1)
			SetQuestData(sceneId, selfId, MD_FUBEN_XIAOQIAN_FLAG[1], MD_FUBEN_XIAOQIAN_FLAG[2], MD_FUBEN_XIAOQIAN_FLAG[3], 1)
		end
	end
end
