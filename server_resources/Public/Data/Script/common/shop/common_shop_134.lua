--功能：饰品商店

x560134_g_ScriptId = 560134
x560134_g_MissionName="药品制造配方商店"
x560134_g_ShopList={134}
--**********************************

--任务入口函数

--**********************************

function x560134_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560134_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560134_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560134_g_ScriptId, x560134_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560134_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560134_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560134_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560134_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560134_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560134_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560134_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560134_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end