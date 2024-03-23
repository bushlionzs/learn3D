
x800055_g_ScriptId = 800055
x800055_g_MissionName = "取回现金/现银"

--点击（NPC）
function x800055_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,800055,x800055_g_MissionName,0,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x800055_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	--向GL请求取款
	WorldBankRetakMoney(sceneId, selfId)

end

--领取结果
function x800055_OnRetakeResult( sceneId, selfId, gold,goldNum,siller,sillerNum )
		
	if goldNum >0 then

		local text = "您已经成功领取了寄售返回的"..goldNum.."笔现金，总计#{_MONEY"..gold.."}现金"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--邮件通知
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "您于"..year.."年"..monty.."月"..day.."日"..hour.."："
		if min < 10 then
			szMail = szMail.."0"..min.."成功领取了寄售退回的"..goldNum.."笔现金，总计#{_MONEY"..gold.."}现金"
		else
			szMail = szMail..min.."成功领取了寄售退回的"..goldNum.."笔现金，总计#{_MONEY"..gold.."}现金"
		end
		
		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	end

	if sillerNum >0 then

		local text = "您寄售的"..sillerNum.."笔现金已成功售出，总计获得现银#{_MONEY"..siller.."}"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--邮件通知
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "您于"..year.."年"..monty.."月"..day.."日"..hour.."："
		if min < 10 then
			szMail = szMail.."0"..min.."成功领取了因售出"..sillerNum.."笔现金获得的收益，总计#{_MONEY"..siller.."}现银"
		else
			szMail = szMail..min.."成功领取了因售出"..sillerNum.."笔现金获得的收益，总计#{_MONEY"..siller.."}现银"
		end

		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	end

	if goldNum<=0 and sillerNum<=0 then
	
		local text = "您没有现银或是退回的现金可领取。"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	end

	return 1

end


--点击（确定）
function x800055_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--接受
--**********************************
function x800055_ProcAccept( sceneId, selfId )

end


--**********************************
--放弃
--**********************************
function x800055_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x800055_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x800055_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x800055_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x800055_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x800055_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x800055_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end