
x800054_g_ScriptId = 800054
x800054_g_MissionName = "寄售现金"

--点击（NPC）
function x800054_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800054_g_ScriptId,x800054_g_MissionName,0,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x800054_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if GetMergeDBToggle() == 1 then
		local text = "为配合并服，现金寄售暂时关闭，并服完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "为配合数据库升级，现金寄售暂时关闭，升级完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	if GetWorldGoldShopToggle() == 0 then
		local text = "现金寄售功能已关闭"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	--通知客户端弹出寄售界面
	OpenWorldShopSell(sceneId, selfId,0)
	
end


--判断能否出售
function x800054_OnIsCanSell( sceneId, selfId,shopId )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你还处于安全保护时间内，不能这样做！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end

	if GetMergeDBToggle() == 1 then
		local text = "为配合并服，现金寄售暂时关闭，并服完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "为配合数据库升级，现金寄售暂时关闭，升级完成后即可正常使用"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetWorldGoldShopToggle() == 0 then
		local text = "现金寄售功能已关闭"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end

	--根据商店ID得到寄售的现金和手续费
	local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)
	local costGold = gold + charge

	if costGold <= 0 or gold <=0 or charge <=0 then
		--不应该出现的情况
		return 0
	end
	
	if GetMoney(sceneId, selfId,2) < costGold then
		
		local text = "你的现金不足#{_MONEY"..costGold.."},寄售不成功"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0

	end

	return 1

end


--寄售上架操作结果
function x800054_OnSellResult( sceneId, selfId,shopId,price,result )
	
	if result == 0 then			--商店满
		
		local text = "寄售列表已满，请你过一段时间再来寄售现金"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	elseif result == 1 then		--玩家已超过寄售数量
		
		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "你已经有"..num.."笔寄售还在等待成交中，不能再寄售"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		
	elseif result == 2 then		--寄售成功

		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "某人在现金寄售NPC处寄售了#{_MONEY"..gold.."}现金，标价为#{_MONEY"..price.."}现银。需要的朋友，快去抢购吧！"
		LuaAllScenceM2Wrold(sceneId,text,2,1)
		
		--邮件给卖方
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "您于"..year.."年"..monty.."月"..day.."日"..hour.."："
		if min < 10 then
			--分钟不足10，前面补一个0，显示用
			szMail = szMail.."0"..min.."寄售了#{_MONEY"..gold.."}现金，标价为#{_MONEY"..price.."}现银"
		else
			szMail = szMail..min.."寄售了#{_MONEY"..gold.."}现金，标价为#{_MONEY"..price.."}现银"
		end
		
		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	elseif result == 5 then		--银行满

		local text = "银行已满，请你过一段时间再来寄售或购买现金"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
	end

end

--点击（确定）
function x800054_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--接受
--**********************************
function x800054_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800054_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x800054_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x800054_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x800054_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x800054_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x800054_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x800054_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end