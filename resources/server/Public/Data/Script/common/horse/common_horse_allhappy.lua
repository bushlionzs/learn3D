--功能：中心医生
--NPC：中心医生

x800048_g_ScriptId = 800048
x800048_g_MissionName="骑乘恢复"
x800048_g_MissionInfo="恢复所有骑乘的生命值，\n需要花费银卡"
x800048_g_MissionSuccess="所有骑乘的生命值都恢复了！"
x800048_g_NotNeed="没有骑乘需要恢复生命值。"

--**********************************

--任务入口函数

--**********************************

function x800048_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local money = GetAllHorseHappyMoney(sceneId, selfId)
	--local liang = floor(money /1000);
	--local wen = mod(money, 1000);
	local bNeed = 1;
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y"..x800048_g_MissionName.."\n")
		if(money == 0) then
			AddQuestText(sceneId, x800048_g_NotNeed)
			bNeed = 0
		else
			local str = format("%s#{_MONEY%d}", x800048_g_MissionInfo, money);
			AddQuestText(sceneId, str)
		end
	EndQuestEvent(sceneId)
	if(bNeed > 0) then
		DispatchQuestInfo(sceneId, selfId, targetId, x800048_g_ScriptId,-1)
	else
		DispatchQuestInfo(sceneId, selfId, targetId, x800048_g_ScriptId,-1,1)
	end

end



--**********************************

--列举事件

--**********************************

function x800048_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x800048_g_ScriptId, x800048_g_MissionName , 3 )
end



--**********************************

--检测接受条件

--**********************************

function x800048_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--接受

--**********************************

function x800048_ProcAccept(sceneId, selfId)
	if( 0 < AllHorseHappy(sceneId, selfId)) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x800048_g_MissionSuccess)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	end
end



--**********************************

--放弃

--**********************************

function x800048_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800048_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x800048_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800048_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800048_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x800048_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end