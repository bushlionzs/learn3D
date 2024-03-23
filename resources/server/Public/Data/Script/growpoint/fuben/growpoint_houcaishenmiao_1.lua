                                                                                                                --生长点


--脚本号 301022




--动态变量初始化方法

x301022_g_MissionId 	= 6602
x301022_g_ItemId 		= 12030006
x301022_g_ScriptId 		= 700003


--生成函数开始************************************************************************

function 		x301022_OnCreate(sceneId,growPointType,x,y)

	--创建
	local ItemBoxId = ItemBoxEnterScene(x,y,30,sceneId,0,x301022_g_ItemId)


end






--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301022_OnOpen(sceneId,selfId,targetId)
 	if IsHaveQuest(sceneId,selfId, x301022_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x301022_g_ItemId) < 10 then
			return 0
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您无法这样做")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有这个任务")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301022_OnRecycle(sceneId,selfId,targetId)
    return CallScriptFunction( x301022_g_ScriptId, "OnGetHuoPaoDan", sceneId, selfId )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301022_OnProcOver(sceneId,selfId,targetId)

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301022_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
