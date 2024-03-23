
x310351_g_ScriptId = 310351
x310351_g_MissionName = "开通钱庄帐户"

--点击（NPC）
function x310351_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310351_g_ScriptId,x310351_g_MissionName,3,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x310351_ProcEventEntry( sceneId, selfId, targetId,state,index )	
		
	if index == -1 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y开通钱庄帐户#W\n\t35级以上玩家可在此开通钱庄帐户,开通需要花费#G1#W两现银。\n\t你确定要开通钱庄帐户吗？")
		EndQuestEvent(sceneId)	
		AddQuestNumText(sceneId,x310351_g_ScriptId,"开通钱庄帐户",3,1)
		DispatchQuestEventList(sceneId, selfId, targetId);
		
	elseif index == 1 then
					
		if GetMoney(sceneId, selfId,0) < GetStockRegisterCharge() then
		
			local text = "\t很遗憾，你的现银不足，开通钱庄帐户需要花费#R#{_MONEY"..GetStockRegisterCharge().."}#W现银。"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,text );
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId, selfId, targetId);		
			return
			
		end
	
		if GetMergeDBToggle() == 1 then
		local text = "\t目前本服务器正在与其他服务器进行合并的准备工作，钱庄系统暂时关闭，服务器合并完成后即会开放。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "\t目前本服务器正在进行数据库升级的准备工作，钱庄系统暂时关闭，数据库升级完成后即会开放。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
		
	if IsEnableStockAccount(sceneId, selfId) == 1 then
		local text = "\t您已经开通过钱庄帐户了！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	--等级判断
	if GetLevel(sceneId, selfId) < 35 then
	
		local text = "\t只有35级以上的玩家才能开通钱庄帐户！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);		
		return
		
	end
		
	if GetMoney(sceneId, selfId,0) < GetStockRegisterCharge() then
	
		local text = "\t很遗憾，你的现银不足，开通钱庄帐户需要花费#R#{_MONEY"..GetStockRegisterCharge().."}#W现银#B。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);		
		return
		
	end
	
		RegisterStockAccount( sceneId, selfId )

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t恭喜您成功开通钱庄帐户！您可以进入钱庄进行交易了。\n\t请注意：若您的帐户持续#G30天#W没有进行任何交易操作，将被系统自动删除，帐户内资金直接返还进您的背包中，请记得及时进行交易哦。")
		EndQuestEvent(sceneId)	
		DispatchQuestEventList(sceneId, selfId, targetId);
		
	end
		
end


--判断能否开通
function x310351_OnIsCanRegister( sceneId, selfId )

	if GetMergeDBToggle() == 1 then
		local text = "\t目前本服务器正在与其他服务器进行合并的准备工作，钱庄系统暂时关闭，服务器合并完成后即会开放。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "\t目前本服务器正在进行数据库升级的准备工作，钱庄系统暂时关闭，数据库升级完成后即会开放。"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if IsEnableStockAccount(sceneId, selfId) == 1 then
		local text = "\t您已经开通过钱庄帐户了！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
	end
	
	return 1

end


--开通结果
function x310351_OnRegisterResult( sceneId, selfId,result )
	
	if result == 0 then			--开通失败
		
		local text = "\t开通失败，请稍后在试"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	elseif result == 1 then		--开通成功
		
		local text = "\t恭喜您成功开通钱庄帐户！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		
	end

end



