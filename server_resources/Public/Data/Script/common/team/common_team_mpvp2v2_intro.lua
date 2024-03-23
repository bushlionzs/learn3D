--双人战场说明
--ScriptID = 303106

x303106_g_ScriptId 					= 303106

x303106_g_MissionName				= "【跨服双人战场说明】"

x303106_g_Readme1						=	"\n#Y一、报名条件\n#W1、需要先通过#G大都#W或#G天上人间#W的#G跨服双人战场传送人#W进入报名场景。\n2、周一、周四#G20：00~21：00#W及周日#G13：00~15：00#W为跨服双人战场开放时间。\n3、双人战场每5分钟为一轮。周一、周四#G19:55~20:59#W及周日#G12：55~14：59#W随时可以报名参加。\n4、您的队伍人数必须为两人。\n5、您的队伍中所有玩家的等级必须达到40级。\n6、只有队长才能申请参加双人战场。"
x303106_g_Readme2						=	"\n#Y二、双人战场规则\n#W1、每场双人战比赛的战斗时间为4分钟。\n2、双人战比赛中玩家死亡后，无法进行任何复活操作。比赛结束后，系统会自动复活双方玩家。\n3、当成功报名后，系统会在战斗开启时在屏幕右中位置给予玩家提示，点击提示图标，即可进入比赛场地。\n4、玩家如果不在线或已离开报名场景将无法获得邀请。\n5、在双人战场内掉线的玩家，上线时会被传送出战场。\n6、双人战比赛决出胜负后，只有此时仍在双人战场内的玩家才能获得相应的战场积分。"
x303106_g_Readme3						=	"\n#Y三、胜利判定\n#W1、当一方所有玩家死亡，另一方仍有存活玩家，判定有存活玩家的一方获胜。\n2、在双人战场战斗开启后超过1分钟，某一方依然没有玩家进入双人战场。则判定另一方获胜。\n3、当双人战场战斗时间结束，双方剩余队员数不同时，则判定队员多的一方获胜。\n4、当双人战场战斗时间结束，双方剩余队员数相同时，则判定双方平局。"

--**********************************
--点击NPC
--**********************************
function x303106_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x303106_g_ScriptId,x303106_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x303106_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x303106_g_MissionName)
			AddQuestText(sceneId,x303106_g_Readme1)
			AddQuestText(sceneId,x303106_g_Readme2)
			AddQuestText(sceneId,x303106_g_Readme3)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x303106_g_ScriptId, x303106_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x303106_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x303106_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x303106_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x303106_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x303106_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x303106_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x303106_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x303106_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x303106_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



