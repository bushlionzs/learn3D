

------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x310374_g_scriptId 		= 310374


x310374_g_Title			=	"购买生命琼浆"

x310374_g_ItemId 		= 12041097

x310374_g_CostMoney		= 800

x310374_g_MaxCount		= 5

x310374_g_IsEnableId    = 1051
--需要的等级
function x310374_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId,x310374_g_scriptId,x310374_g_Title, 3, 0)
end

function x310374_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
        if GetGameOpenById( x310374_g_IsEnableId) <= 0 then
            Msg2Player( sceneId, selfId, "此活动今天不开放，请改天再来", 8, 3)
            return
         end
        local daycount, num = x310374_GetDayCount(sceneId, selfId) 
        if num >0 then
		   str = format( "#G小提示：\n\t\你今天还可以购买#R%d个@item_%d。",num, x310374_g_ItemId)
        else
           str =  format( "#G小提示：\n\t\你今天已经购买#R%d个@item_%d了，请改天再来。",x310374_g_MaxCount, x310374_g_ItemId)
        end    
		BeginQuestEvent(sceneId)
	--任务信息
		AddQuestText(sceneId,"#Y"..x310374_g_Title)
		AddQuestText(sceneId,format( "\t@item_%d#W是不可多得的绝世灵药，虽无起死人，肉白骨之功效，但只要尚有一丝生气，就足以令人恢复健康状态。这@item_%d#W是我依照祖方，精心研制而成的。\n\t你可以周六、周日每天在我这里购买#G5个#W，每次花费#R800#W文金卡/现金购买1个，你是否要购买？\n\t（@item_%d#W可以瞬间回复20000点生命和全部的怒气、能量、箭矢、子弹、魔法、灵力。冷却时间为三分钟。）", x310374_g_ItemId, x310374_g_ItemId, x310374_g_ItemId))
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
		Msg2Player( sceneId, selfId, "只有每六，日可以购买生命琼浆！", 8, 3)
		return 0
	end
	
	if x310374_GetDayCount(sceneId, selfId) == 0 then
		Msg2Player( sceneId, selfId, format("你今天已经购买过%d次了，请改日再来！", x310374_g_MaxCount), 8, 3)
		return 0
	end
	
	if GetBagSpace(sceneId, selfId) <= 0 then
		Msg2Player( sceneId, selfId, "物品栏已满，无法得到物品！", 8, 3)
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
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310374_g_CostMoney), 8, 3)
                return 0
            end
        end
    else
		bind = 1
        if CostMoney( sceneId, selfId, 3, x310374_g_CostMoney) ~= 1 then
			bind = 0
            if CostMoney(sceneId, selfId, 2, x310374_g_CostMoney,316) ~= 1 then
                Msg2Player( sceneId, selfId, format( "你身上的金卡/现金不足#R%d#cffcc00文", x310374_g_CostMoney), 8, 3)
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
		Msg2Player( sceneId, selfId, "您成功购买1个生命琼浆！", 8, 3)
		GamePlayScriptLog(sceneId, selfId, 1691)
		return 1;
	else
		Msg2Player( sceneId, selfId, "物品栏已满，无法得到物品！", 8, 3)
		return 0;
	end
end
----------------------------------------------------------------------------------------------
--点确定后
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
--取得当前次数
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
--设置当天次数
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

