

------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x310391_g_scriptId 		= 310391


x310391_g_Title			=	"金龙印兑换"

x310391_g_ItemId 		= 11000597

-- 花费价格
x310391_g_CostMoney             = 500

--需要的等级
function x310391_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId,x310391_g_scriptId,x310391_g_Title, 3, 1)
	
end

function x310391_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

		BeginQuestEvent(sceneId)
	--任务信息
		AddQuestText(sceneId,"#Y"..x310391_g_Title)
		AddQuestText(sceneId,format( "\t@item_%d#W是时装纹龙的必备道具。只要本周进行过副本倩女幽魂或钧窑绝迹，就能在我这里兑换一个@item_%d。\n\t#W是否花费#R500#W文金卡/现金换取一个@item_%d#W？", x310391_g_ItemId, x310391_g_ItemId , x310391_g_ItemId))
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
			AddQuestText(sceneId,"只有周六日才能兑换！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
	local weekIndex = GetWeekIndex()
	local week = GetQuestData(sceneId, selfId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3])
	if weekIndex == week then
		if GetQuestData(sceneId, selfId, MD_FUBEN_XIAOQIAN_FLAG[1], MD_FUBEN_XIAOQIAN_FLAG[2], MD_FUBEN_XIAOQIAN_FLAG[3]) == 1 then
			Msg2Player( sceneId, selfId, "你本周已经兑换过一次，不能再次兑换", 8, 3)
			return 0
		end
	else 
		Msg2Player( sceneId, selfId, "你本周没有完成副本倩女幽魂或钧窑绝迹，不能兑换", 8, 3)
		return 0
	end
	--end
	
	if GetBagSpace(sceneId, selfId) <= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到物品！")
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
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310391_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
            if CostMoney(sceneId, selfId, 3, x310391_g_CostMoney) ~= 1 then
            if CostMoney(sceneId, selfId, 2, x310391_g_CostMoney,315) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310391_g_CostMoney), 8, 3)
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
			AddQuestText(sceneId,"兑换成功！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1;
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品栏已满，无法得到物品！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
end
----------------------------------------------------------------------------------------------
--点确定后
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
