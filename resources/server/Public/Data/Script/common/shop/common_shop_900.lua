--功能：七夕商店

x560900_g_ScriptId = 560900
x560900_g_MissionName="七夕姻缘店"
x560900_g_ShopList={900,900,900,900,900,900}
x560900_g_MissionDay = 812


--**********************************

--任务入口函数

--**********************************

function x560900_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

		DispatchShopItem( sceneId, selfId, targetId, x560900_g_ShopList[1] )


end



--**********************************

--列举事件

--**********************************

function x560900_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if x560900_CheckDay( sceneId,selfId ) == 1 then
		AddQuestNumText(sceneId, x560900_g_ScriptId, x560900_g_MissionName,10)
	else 
		return
	end

end



--**********************************

--检测接受条件

--**********************************

function x560900_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560900_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560900_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560900_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560900_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560900_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560900_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560900_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

--**********************************

--检查日期

--**********************************
function x560900_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if x560900_g_MissionDay == nDay then
		return 1
	end

	return 0

end