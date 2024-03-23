
x800053_g_ScriptId = 800053
x800053_g_MissionName = "购买现金"

--点击（NPC）
function x800053_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,800053,x800053_g_MissionName,0,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x800053_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	--向GL请求现金商店列表
	GetWorldShopMerchandiseInfo(sceneId, selfId,0)
	
end


--判断能否购买现金
function x800053_OnIsCanBuy( sceneId, selfId,price )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "你还处于安全保护时间内，不能这样做！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end

	if GetMoney(sceneId, selfId,0) < price then
		
		local text = "你的现银不足#{_MONEY"..price.."},购买不成功"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0

	end

	return 1

end


--现金购买结果
function x800053_OnBuyResult( sceneId, selfId,shopId,price,result )
	
	if result == 3 then			--购买成功
		
		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "某人在现金寄售NPC处花费了#{_MONEY"..price.."}现银，购买了#{_MONEY"..gold.."}现金！"
		LuaAllScenceM2Wrold(sceneId,text,2,1)	

		--邮件给买方
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "您于"..year.."年"..monty.."月"..day.."日"..hour.."："
		if min < 10 then
			szMail = szMail.."0"..min.."花费了#{_MONEY"..price.."}现银，购买了#{_MONEY"..gold.."}现金"	
		else
			szMail = szMail..min.."花费了#{_MONEY"..price.."}现银，购买了#{_MONEY"..gold.."}现金"	
		end

		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	elseif result == 4 then		--购买失败
		
		local text = "该金票已发生变动，购买不成功，请重新选择"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--重新请求现金商店列表
		GetWorldShopMerchandiseInfo(sceneId, selfId,shopId)

	elseif result == 5 then		--银行满

		local text = "银行已满，购买失败"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)	
	end

end

--点击（确定）
function x800053_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--接受
--**********************************
function x800053_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x800053_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x800053_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x800053_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x800053_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x800053_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x800053_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x800053_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end