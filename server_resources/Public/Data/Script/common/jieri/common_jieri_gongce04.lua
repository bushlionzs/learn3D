--七夕节日介绍
--ScriptID = 350003


x350003_g_ScriptId 					= 350003


x350003_g_MissionName				= "七夕活动介绍"

x350003_g_Readme1						=	"一、迎接七夕开放“#G情人服#W”。\n\t8月21日，独具情人节气氛的“情人服”，届时欢迎广大玩家入驻！\n二、“#G玫瑰物语#W”向心爱的#RTA#W表白\n\t从2009年8月25日0:00开始，玩家可以在金币商店内购买到娇艳欲滴的玫瑰花送给心上人， #Y送人玫瑰，手留余香#W，届时全世界玩家都将看到您爱的宣言，用这一份大胆的表白赢得您的爱情吧！\n三、“#G浓情金婚#W”有情人终成眷属\n\t“#Y千里姻缘一线牵，月老免费送金婚#W”，七夕当日所有玩家结婚都将免费，赶快与您倾心已久的玩家携手跨入婚姻的殿堂吧！！\n四、“#G爱的馈赠#W”\n\t珍贵的情人首饰盒，内含#R限量发售#W的三大系列六款极品首饰，期待送给爱人尊贵大礼的玩家千万不要错过！\n五、“#G鹊桥相伴#W”\n\t30级全能型坐骑-喜鹊降世符，玩家购买后将获得成年喜鹊一只，售价仅有9两900文，逾期不售，渴望收藏全新坐骑的玩家欲购从速哦！\n六、“#G情侣喜鹊坐骑卡#W”大礼包隆重推出\n\t价值400元的情侣喜鹊坐骑卡大礼包，内含情人节时装以及喜鹊坐骑！\n七、“#GQQ情侣徽章大放送#W”\n\t七夕期间注册或登陆成吉思汗帐号，回答简单的五道问题即可获得QQ情侣徽章中的一枚，全套为情侣版，共两枚。 赠送给梦中情人的表白大礼！"

--**********************************
--点击NPC
--**********************************
function x350003_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x350003_g_ScriptId,x350003_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x350003_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x350003_g_MissionName)
			AddQuestText(sceneId,x350003_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x350003_g_ScriptId, x350003_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x350003_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x350003_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x350003_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x350003_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x350003_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x350003_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x350003_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x350003_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x350003_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



