
x300633_g_ScriptId = 300633

--任务文本描述
x300633_g_MissionName="【帮会】帮贡建设"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300633_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	if GetGuildOfficial(sceneId, selfId) ~= -1 then--判断是否加入帮会
	
		local localexp = floor( (GetLevel( sceneId, selfId ))  * 200 )

		local Readme_1 = "#Y【帮会】帮贡建设#r#W"
		
		local Readme_2 = "\t您可以通过#G25点帮贡#W来提升#G1点帮会经验#W，同时您也将获得#G"..localexp.."点个人经验#W。"
		
		local Readme_3 = "#W#r#Y您是否要建设帮会？"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x300633_g_ScriptId, -1 );

	end
	
end

--**********************************
--列举事件
--**********************************
function x300633_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestNumText(sceneId,x300633_g_ScriptId,x300633_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x300633_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300633_ProcAccept( sceneId, selfId )

	if GetGuildOfficial(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "建设帮会失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您不是帮会成员，无法进行帮会建设。",8,2)
		return
	end
	
	if GetGuildUserPoint(sceneId, selfId) < 25 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "建设帮会失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您所拥有的帮贡不够帮贡建设需求，建设帮会失败！",8,2)
		return
	end
	
	-- 判断帮会的帮贡建设次数是否满了
	GuildCanExpBuild(sceneId, selfId, x300633_g_ScriptId, "OnGuildScript_Callback" )
	
end

-- 回调函数
function x300633_OnGuildScript_Callback( sceneId, selfId, param1, param2, param3, param4 )

	if param1==1 then	-- 成功
				
		local localexp = floor ((GetLevel( sceneId, selfId ))  * 200)
					
		SubGuildUserPoint(sceneId, selfId, 25)				--扣除个人帮贡
		Msg2Player(sceneId,selfId,"【帮会】帮贡建设:扣除帮贡25点",8,2)
		
		AddExp(sceneId, selfId, localexp)					--个人经验
		Msg2Player(sceneId,selfId,"【帮会】帮贡建设:获得#R经验"..localexp.."点#o的奖励",8,2)
		Msg2Player(sceneId,selfId,"获得#R经验"..localexp.."点#o的奖励",8,3)		
		AddGuildExp(sceneId, selfId, 1)				--帮会经验
		
		--AddGuildMerit(sceneId, selfId, 1)         --帮会功德
		--Msg2Player(sceneId,selfId,"【帮会】帮贡建设:获得帮会功德1点",8,2)
		Msg2Player( sceneId, selfId, (GetName(sceneId, selfId)).."慷慨捐助了25点帮贡，使帮会经验提高了1点。", 6 )		--帮会广播
		
	else	--失败
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "建设帮会失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您所在的帮会每天只能进行" .. param2 .. "次帮贡建设，请明日再来！",8,2)	
	end
end

--**********************************
--放弃
--**********************************
function x300633_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300633_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300633_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300633_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300633_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300633_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300633_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
