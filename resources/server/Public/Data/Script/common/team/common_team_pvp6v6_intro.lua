--六人战场说明
--ScriptID = 303007

x303007_g_ScriptId 					= 303007

x303007_g_MissionName				= "【六人战场说明】"

x303007_g_Readme1						=	"\n#Y一、报名条件\n#W1、周三晚上#G19：30~19：59#W和周六下午#G13：30~13：59#W为六人战场报名时间。\n2、周三六人战场于#G20：00#W正式开始，周六六人战场于14：00正式开启。\n3、您的等级必须大于或等于60级才能报名。\n4、您可以选择组队报名和个人报名两种方式：\n#G组队报名：#W队伍人数必须大于或等于3人，由队长申请报名，系统会为您的队伍匹配合适的对手；\n#G个人报名：#W必须没有队伍，由个人申请，系统会先为您寻找其他以个人方式报名的队友，再匹配对手。"
x303007_g_Readme2                       =   "\n#Y二、战场提示\n#W1、击败敌方士兵和拆除敌方建筑可获得战场货币，附近友方玩家人数越少，获得货币越多。\n2、战场中靠近九旄大帐的两座箭塔有传送到其他各路的功能。\n3、战场的河道里会不定时地出现神秘的补给品，打开补给品可以获得意外的惊喜。\n4、消灭战场中潜伏的中立怪物，可以获得战场货币奖励，击败终极妖兽——撼地，可获得大量的额外奖励。\n5、击败对方的士兵可以为己方增加士气，当士气积累到一定程度时会得到一定的奖励。"
x303007_g_Readme3						=	"\n#Y三、六人战场规则\n#W1、每场六人战场比赛的战斗时间为60分钟。\n2、六人战场比赛中玩家死亡后，无法进行任何复活操作。系统会自动复活死亡玩家。\n3、当成功报名后，系统会在战斗开启时在屏幕右中位置给予玩家提示，点击提示图标，即可进入比赛场地。\n4、玩家如果不在线将无法获得邀请。\n5、在六人战场赛场内掉线的玩家，上线时仍在战场中，但是要接受1分钟无法行动的惩罚。\n6、六人战场比赛决出胜负后，只有此时仍在六人战场赛场内的玩家才能获得相应的六人战场积分。"
x303007_g_Readme4						=	"\n#Y四、胜利判定\n#W1、摧毁对方九旄主帐。\n2、战场比分优先达到200。\n3、对方玩家在战场中所剩人数为0，持续超过1分钟。\n4、达到战场时限未决胜负，则战场比分高的一方获胜。如果比分一致判和。"

--**********************************
--点击NPC
--**********************************
function x303007_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x303007_g_ScriptId,x303007_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x303007_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x303007_g_MissionName)
			AddQuestText(sceneId,x303007_g_Readme1)
			AddQuestText(sceneId,x303007_g_Readme2)
			AddQuestText(sceneId,x303007_g_Readme3)
			AddQuestText(sceneId,x303007_g_Readme4)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x303007_g_ScriptId, x303007_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x303007_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x303007_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x303007_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x303007_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x303007_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x303007_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x303007_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x303007_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x303007_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



