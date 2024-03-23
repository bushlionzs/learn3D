--七夕节日介绍
--ScriptID = 350002


x350002_g_ScriptId 					= 350002


x350002_g_MissionName				= "七夕的来历"

x350002_g_Readme1						=	"\t民间俗语说：“#Y今日人间七月七，天上牛郎会织女。#W”农历七月初七，俗称“#G七夕#W”，相传是天上牛郎织女一年一度相会的时刻，又叫“#G乞巧节#W”。 \n\t这一天，我们古人总会望着银河两岸的牵牛星与织女星，想象着他们一年仅一夕的相会，该是如何的让人断肠。关于七夕的诗，最为经久传唱的，应该是那首《#Y鹊桥仙#W》: \n\t#G纤云弄巧，飞星传恨，银汉迢迢暗度。金风玉露一相逢，便胜却人间无数。 \n\t柔情似水，佳期如梦，忍顾鹊桥归路。两情若是久长时，又岂在朝朝暮暮！#W"

--**********************************
--点击NPC
--**********************************
function x350002_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350002_g_ScriptId,x350002_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x350002_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x350002_g_MissionName)
			AddQuestText(sceneId,x350002_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x350002_g_ScriptId, x350002_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x350002_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x350002_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x350002_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x350002_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x350002_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x350002_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x350002_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x350002_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x350002_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



