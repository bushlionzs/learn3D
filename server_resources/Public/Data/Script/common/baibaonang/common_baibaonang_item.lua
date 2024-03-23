x300370_g_scriptId = 300370 


function x300370_ProcEventEntry( sceneId, selfId, BagIndex )
    local buff 	=	9011
	local buff1 =	9013	
	local buff2 =	9012	
	local rand = random(1, 3)
	local level = GetLevel(sceneId, selfId)
	local awardMoney = level*300
	if rand == 1 then
		local item1 =11050001
		local item2 = 11050002
		local item3 = 11050003
		local item4 = 11050004
		local itemId;
		if level < 45 then
				itemId =item1
				BeginAddItem( sceneId )
					if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
						AddItem( sceneId, itemId, 3 )
					else
						AddBindItem( sceneId, itemId, 3 )	
					end		
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=45 and level < 60 then
			itemId =item2
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=60 and level < 65 then
			itemId =item2
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >= 65 and level < 85 then
			itemId =item3
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=85 then
			itemId =item4
			BeginAddItem( sceneId )
				if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
				else
					AddBindItem( sceneId, itemId, 3 )
				end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)
				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		end
		
	elseif rand == 2 then
		local item1 =11000200
		local item2 = 11000201
		local item3 = 11000202
		local item4 = 11000203
		local itemId;
		if level < 40 then
			itemId = item1
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=40 and level < 45 then
			itemId = item2
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=45 and level < 60 then
			itemId = item2
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)

				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >=60 and level < 65 then
			itemId = item3
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)
				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		elseif level >= 65 and level < 80 then
			itemId = item3
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)
				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
			elseif level >= 80 then
			itemId = item4
			BeginAddItem( sceneId )
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddItem( sceneId, itemId, 3 )
			else
					AddBindItem( sceneId, itemId, 3 )
			end
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				local message = format("你打开百宝囊，获得了物品：#R#{_ITEM%d}", itemId )
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)
				EraseItem(sceneId, selfId, BagIndex); --删除物品	
			else
				local strText = "背包已满,不能使用此物品"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		end
		
	elseif rand == 3 then
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
					AddMoney( sceneId, selfId,0, awardMoney )
			else
					AddMoney( sceneId, selfId,1, awardMoney )
			end
			
			local message = format( "你打开百宝囊，获得了#R现银#{_MONEY%d}", awardMoney)
			local message1 = format( "你打开百宝囊，获得了#R银卡#{_MONEY%d}", awardMoney)
			BeginQuestEvent(sceneId);
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
				AddQuestText(sceneId, message);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message,4,2)
			else
				AddQuestText(sceneId, message1);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				Msg2Player(sceneId,selfId, message1,4,2)
			end

			EraseItem(sceneId, selfId, BagIndex); --删除物品
	end

end

function x300370_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x300370_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x300370_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300370_OnDeplete( sceneId, selfId )

	return 0
end

function x300370_OnActivateOnce( sceneId, selfId )
end

function x300370_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
