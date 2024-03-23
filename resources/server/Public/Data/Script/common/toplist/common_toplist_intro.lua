--双人战场说明
--ScriptID = 310603

x310603_g_ScriptId 					= 310603

x310603_g_MissionName				= "【排行榜挑战赛说明】"

x310603_g_Readme1						=	"\n#Y一、赛事规则：\n#W1、每周都会进行一场挑战赛，挑战赛时间从#G周一0：00至周日24：00#W。非比赛时间内的玩家行为，将不会对相关排行榜造成影响。\n2、每周日24：00后会保存并清空此周排行榜，玩家可以按下“G”键打开排行榜，在排行榜中通过查看“上周排行榜”，来查询自己的排名。\n3、可以从活动追踪的月历中查看每周进行的赛事。"
x310603_g_Readme2						=	"\n#Y二、领奖方法：\n#W1、#G周一1：00至周六23：00#W为上周赛事领奖时间。\n2、每周赛事相应的排行榜前100名均可以领取奖励，会有#G高额经验#W、#G超炫称号#W、#G超强属性#W等等奖励！"
x310603_g_Readme3						=	"\n#Y三、赛程安排：\n#G排行榜挑战赛每周仅进行一个排行榜的名次争夺，按照以下顺序进行：\n#W囚龙岛排行榜\n屠龙排行榜\n和氏璧排行榜\n小喇叭排行榜\n赤血号排行榜\n杀敌排行榜\n祝家庄排行榜\n战场等级排行榜\n夏王墓排行榜\n放烟花排行榜\n印度河排行榜\n智力竞赛排行榜\n轮回台排行榜\n玫瑰排行榜\n大教堂排行榜\n神龙宝藏排行榜"

--**********************************
--点击NPC
--**********************************
function x310603_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310603_g_ScriptId,x310603_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x310603_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310603_g_MissionName)
			AddQuestText(sceneId,x310603_g_Readme1)
			AddQuestText(sceneId,x310603_g_Readme2)
			AddQuestText(sceneId,x310603_g_Readme3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310603_g_ScriptId, x310603_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x310603_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x310603_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x310603_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x310603_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x310603_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x310603_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x310603_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x310603_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x310603_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



