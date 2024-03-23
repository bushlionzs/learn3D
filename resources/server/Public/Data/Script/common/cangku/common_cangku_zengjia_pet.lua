--增加仓库空间
--MisDescBegin
--脚本号
x561005_g_ScriptId = 561005

--**************************************************************

--任务文本描述
x561005_g_MainName="增加骑乘仓库扩展空间说明"
x561005_g_MissionName="增加骑乘仓库扩展空间"
x561005_g_Readme = "\t增加骑乘仓库扩展空间的花费如下：\n\t第二格  #G200两#W银子\n\t第三格  #G600两#W银子\n\t第四格  #G1.5锭#W银子\n\t第五格  #G3锭#W银子\n"
x561005_g_Opt_Fail = "\t您的银子不足！无法完成增加扩展骑乘仓库操作！"
x561005_g_Opt_Succ = "\t操作成功！已增加了骑乘仓库的扩展空间！"

x561005_g_NeedMoney1 = 200000
x561005_g_NeedMoney2 = 600000
x561005_g_NeedMoney3 = 1500000
x561005_g_NeedMoney4 = 3000000


--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x561005_ProcEventEntry( sceneId, selfId, targetId,scriptid,extid )	--点击该任务后执行此脚本

		local activeBankPetSlot = LuaGetActiveBankPetSlot(sceneId,selfId)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561005_g_MainName)
			AddQuestText(sceneId,x561005_g_Readme);
			AddQuestText(sceneId,"\t您当前的激活格数为 #G"..activeBankPetSlot)
			AddQuestText(sceneId,"\n\t#W您确定要扩展骑乘仓库吗？")
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	
end

--**********************************
--列举事件
--**********************************
function x561005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId, x561005_g_ScriptId, x561005_g_MissionName,3,1)

end

--**********************************
--检测接受条件
--**********************************
function x561005_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

---------------------------------------------------------------------------------------------------
--得到玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------

function x561005_GetSelected(sceneId, selfId)
end

---------------------------------------------------------------------------------------------------
--设置玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x561005_SetSelected(sceneId, selfId, flag)
end

function x561005_ActiveBankPetSlot( sceneId, selfId, needmoney )

		if IsEnoughMoney( sceneId, selfId, needmoney ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561005_g_Opt_Fail)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else
			--激活坐骑格 
			local bRet = LuaActiveBankPetSlot(sceneId,selfId)
			if 1 == bRet then
				SpendMoney( sceneId, selfId, needmoney )
				--BeginQuestEvent(sceneId,selfId)
				--	AddQuestText(sceneId,x561005_g_Opt_Succ)
				--EndQuestEvent()
				--DispatchQuestTips(sceneId,selfId)
			end
		end

end

--**********************************
--接受
--**********************************
function x561005_ProcAccept( sceneId, selfId )

		local activeBankPetSlot = LuaGetActiveBankPetSlot(sceneId,selfId)
		if 1==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney1)
		elseif 2==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney2)
		elseif 3==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney3)
		elseif 4==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney4)
		elseif 5==activeBankPetSlot then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,"骑乘仓库已达上限，无法激活！")
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
		
end

--**********************************
--放弃
--**********************************
function x561005_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x561005_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x561005_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x561005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x561005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x561005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x561005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
