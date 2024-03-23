

--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x910014_g_ScriptId = 910014

--以上是动态**************************************************************

--任务文本描述
x910014_g_MissionName="60级声望装"


x910014_g_ZhiYeItemBonus1={{id=10014001,num=1},{id=10074001,num=1},{id=10204001,num=1},{id=10214001,num=1},{id=10224001,num=1},{id=10234001,num=1}}
x910014_g_ZhiYeItemBonus2={{id=10244001,num=1},{id=10254001,num=1},{id=10264001,num=1},{id=10274001,num=1},{id=10284001,num=1},{id=10294001,num=1}}

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x910014_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
			local zhiye = GetZhiye(sceneId, selfId)
			
			local ret
			BeginAddItem(sceneId)
				for i, item in x910014_g_ZhiYeItemBonus1 do
					if i < 3 then
						AddItem( sceneId,item.id+10000*zhiye+1, item.num )
					else
						AddItem( sceneId,item.id+10*zhiye+1, item.num )
					end
				end			
			ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				BeginAddItem(sceneId)
					for i, item in x910014_g_ZhiYeItemBonus2 do
						AddItem( sceneId,item.id+10*zhiye+1, item.num )
					end
				ret = EndAddItem(sceneId,selfId)
				--添加职业物品
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					BeginQuestEvent(sceneId)
						local strText = "你获得了一套60级声望装"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					AddQuestText(sceneId,"这是60级声望装，你收好了！")
				else
				--职业物品没有加成功
					BeginQuestEvent(sceneId)
						local strText = "背包空间不足，无法获得全部物品。"
						AddQuestText(sceneId,strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					AddQuestText(sceneId,"这是一部分60级声望装！")
				end	
			else
				BeginQuestEvent(sceneId)
					local strText = "背包空间不足，无法获得物品。"
					AddQuestText(sceneId,strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddQuestText(sceneId,"你整理下背包再来找我领取套装吧！")
			end							
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

--**********************************
--列举事件
--**********************************
function x910014_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x910014_g_ScriptId,x910014_g_MissionName);
end



--**********************************
--接受
--**********************************
function x910014_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x910014_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x910014_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x910014_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x910014_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x910014_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x910014_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x910014_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
