--生长点：中皮

x540114_g_GrowpointId = 614 --对应生长点ID

x540114_g_AbilitySkillName = "捕捉" --需要的生活技能名称
x540114_g_AbilitySkillType = 13 --需要的生活技能ID
x540114_g_AbilitySkillLevel = 5 --需要的生活技能ID的等级
--x540114_g_AbilitySkillLimit = 0 --需要的生活技能ID的熟练度
x540114_g_AddSkillLimit = 1 --采集成功获得的熟练度点数
x540114_g_SkillLMax_1 =150 --技能1级时熟练度上限
x540114_g_SkillLMax_2 =200 --技能2级时熟练度上限
x540114_g_SkillLMax_3 =250 --技能3级时熟练度上限
x540114_g_SkillLMax_4 =300	--技能4级时熟练度上限
x540114_g_SkillLMax_5 =350 --技能5级时熟练度上限
x540114_g_SkillLMax_6 =400 --技能6级时熟练度上限
x540114_g_SkillLMax_7 =450 --技能7级时熟练度上限
x540114_g_SkillLMax_8 =500 --技能8级时熟练度上限
x540114_g_SkillLMax = 0 --实际当前熟练度上限

x540114_g_CostVigorLow = 4		--采集技能为需要的最低等级时采集成功一次时扣除的活力点数
x540114_g_CostVigorHigh = 5   --采集技能大于需要的最低等级时采集成功一次时扣除的活力点数
x540114_g_CostVigor = 0       --实际扣除的活力点数

x540114_g_ItemNumLow = 1 --刚够级时获得个数，后面有可能性多获得一个物品
x540114_g_ItemNumHigh = 3 --高一级时获得个数，后面有可能性多获得一个物品
x540114_g_ItemNumOver = 4 --高两级以上时获得个数，后面没有可能多获得物品
x540114_g_ItemNum = 0  --实际获得的物品个数

x540114_g_ItemIndex = 11030403 --对应收集物品的ID
x540114_g_ItemName = "吸血蝙蝠" 	--对应收集物品的名称
x540114_g_DoubleItemLow = 700 --有<当前熟练度>/300的可能性多获得一个物品
x540114_g_DoubleItemHigh = 800 --有<当前熟练度>/400的可能性多获得一个物品

x540114_g_SpecialItemSkillLevel = 5   --可以采集到特殊物品的最低生活技能等级，-1表示始终采集不到特殊物品
x540114_g_SpecialItemLowPencent = 5 --每次采集到特殊物品的概率，-1表示无,最大100
x540114_g_SpecialItemHighPencent = 7 --每次采集到特殊物品的概率，-1表示无,最大100
x540114_g_SpecialItemIndex = 11030405 --每次采集的特殊物品的ID，-1表示无,>0为有效数值
x540114_g_SpecialItemName = "七步蛇"  --每次采集的特殊物品的名称，空表示无
x540114_g_SpecialItemNum = 0 --实际获得的特殊物品个数





--生成函数开始************************************************************************
function 	x540114_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x540114_g_GrowpointId, sceneId, 0, x540114_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x540114_OnOpen(sceneId,selfId,targetId)
	--SetPlayerVigor(sceneId,selfId,140)

	local SkillLevel = QueryPlayerAbilityLevel(sceneId,selfId ,x540114_g_AbilitySkillType)
	local SkillBaseLimit= GetAbilityExp(sceneId, selfId, x540114_g_AbilitySkillType)
	local SkillLimit = SkillBaseLimit + QueryItemAffAbility(sceneId,selfId)
	if SkillLevel == nil then
		TipsToPlayer(sceneId,selfId,"#Y你还没有学习#R"..x540114_g_AbilitySkillName)
	else
		if SkillLevel <= 0 then
			TipsToPlayer(sceneId,selfId,"#Y你还没有学习#R"..x540114_g_AbilitySkillName)
		else
			if SkillLevel >= x540114_g_AbilitySkillLevel then
				if SkillLevel == x540114_g_AbilitySkillLevel then
					x540114_g_CostVigor = x540114_g_CostVigorLow
				else
					x540114_g_CostVigor = x540114_g_CostVigorHigh
				end
				if GetPlayerVigor(sceneId,selfId) >=x540114_g_CostVigor then
					return 0
				else
					TipsToPlayer(sceneId,selfId,"#Y活力不足")
				end
			else
				TipsToPlayer(sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.." 等级不足#R"..x540114_g_AbilitySkillLevel.."级")
			end
		end
	end
	return 1
end

--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x540114_OnRecycle(sceneId,selfId,targetId)
   	local SkillLevel = QueryPlayerAbilityLevel(sceneId,selfId ,x540114_g_AbilitySkillType)
	local SkillBaseLimit= GetAbilityExp(sceneId, selfId, x540114_g_AbilitySkillType)
	local SkillLimit = SkillBaseLimit + QueryItemAffAbility(sceneId,selfId)
	if SkillLevel == nil then
		TipsToPlayer(sceneId,selfId,"#Y你还没有学习#R"..x540114_g_AbilitySkillName)
	else
		if SkillLevel <= 0 then
			TipsToPlayer(sceneId,selfId,"#Y你还没有学习#R"..x540114_g_AbilitySkillName)
		else
			if SkillLevel >= x540114_g_AbilitySkillLevel then
				local NowVigor = GetPlayerVigor(sceneId,selfId)
				if SkillLevel == x540114_g_AbilitySkillLevel then
					x540114_g_CostVigor = x540114_g_CostVigorLow
				else
					x540114_g_CostVigor = x540114_g_CostVigorHigh
				end
				if NowVigor >= x540114_g_CostVigor then
					BeginAddItem( sceneId )
						if SkillLevel >= x540114_g_AbilitySkillLevel + 2 then
							x540114_g_ItemNum = x540114_g_ItemNumOver 
						elseif SkillLevel >= x540114_g_AbilitySkillLevel + 1 then
							local x =random(1,x540114_g_DoubleItemHigh)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540114_g_ItemNum = x540114_g_ItemNumHigh + x 
						else
							local x =random(1,x540114_g_DoubleItemLow)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540114_g_ItemNum =x540114_g_ItemNumLow + x 
						end
						AddItem( sceneId, x540114_g_ItemIndex, x540114_g_ItemNum)
						if  SkillLevel == x540114_g_SpecialItemSkillLevel and x540114_g_SpecialItemSkillLevel > 0 then
							if random(1,100) <= x540114_g_SpecialItemLowPencent and x540114_g_SpecialItemIndex > 0 then
								x540114_g_SpecialItemNum = 1
								AddItem( sceneId, x540114_g_SpecialItemIndex, x540114_g_SpecialItemNum )	
							else
								x540114_g_SpecialItemNum = 0
							end
						elseif SkillLevel > x540114_g_SpecialItemSkillLevel and x540114_g_SpecialItemSkillLevel > 0 then
							if random(1,100) <= x540114_g_SpecialItemHighPencent and x540114_g_SpecialItemIndex > 0 then
								x540114_g_SpecialItemNum = 1
								AddItem( sceneId, x540114_g_SpecialItemIndex, x540114_g_SpecialItemNum )	
							else
								x540114_g_SpecialItemNum = 0
							end
						else	
							x540114_g_SpecialItemNum = 0
						end
					if SkillLevel == 1 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_1
					elseif SkillLevel == 2 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_2
					elseif SkillLevel == 3 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_3
					elseif SkillLevel == 4 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_4
					elseif SkillLevel == 5 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_5
					elseif SkillLevel == 6 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_6
					elseif SkillLevel == 7 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_7
					elseif SkillLevel == 8 then 
						x540114_g_SkillLMax = x540114_g_SkillLMax_8
					end
					local ret = EndAddItem( sceneId, selfId )
					if ret > 0 then
						AddItemListToPlayer(sceneId,selfId)
						if x540114_g_SpecialItemIndex > 0 and x540114_g_SpecialItemNum > 0 then
							TipsToPlayer (sceneId,selfId,"#Y获得#G"..x540114_g_ItemNum.."个#Y"..x540114_g_ItemName.."和#G"..x540114_g_SpecialItemNum.."个#Y"..x540114_g_SpecialItemName)
						else
							TipsToPlayer (sceneId,selfId,"#Y获得#G"..x540114_g_ItemNum.."个#Y"..x540114_g_ItemName)
						end
						TipsToPlayer (sceneId,selfId,"#Y消耗#G"..x540114_g_CostVigor.."点#Y活力")
						if SkillLevel < x540114_g_AbilitySkillLevel + 2 then
							if SkillLevel > 8 then 
								SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,SkillBaseLimit + x540114_g_AddSkillLimit)
								TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_AddSkillLimit.."点#Y熟练度")
							elseif SkillLevel > 0 and SkillLevel <= 8 then
								if SkillBaseLimit + x540114_g_AddSkillLimit <= x540114_g_SkillLMax then 
									SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,SkillBaseLimit + x540114_g_AddSkillLimit)
									TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_AddSkillLimit.."点#Y熟练度")
								elseif SkillBaseLimit + x540114_g_AddSkillLimit > x540114_g_SkillLMax and SkillBaseLimit < x540114_g_SkillLMax then
									SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,x540114_g_SkillLMax)
									TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_SkillLMax-SkillBaseLimit.."点#Y熟练度")
								else
									TipsToPlayer (sceneId,selfId,"熟练度已达上限")
								end
							end
						end
						SetPlayerVigor(sceneId,selfId, NowVigor - x540114_g_CostVigor)
						return 1
					else
						BeginAddItem( sceneId )
						if SkillLevel >= x540114_g_AbilitySkillLevel + 2 then
							x540114_g_ItemNum = x540114_g_ItemNumOver 
						elseif SkillLevel >= x540114_g_AbilitySkillLevel + 1 then
							local x =random(1,x540114_g_DoubleItemHigh)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540114_g_ItemNum = x540114_g_ItemNumHigh + x 
						else
							local x =random(1,x540114_g_DoubleItemLow)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540114_g_ItemNum =x540114_g_ItemNumLow + x 
						end
						AddItem( sceneId, x540114_g_ItemIndex, x540114_g_ItemNum)
						local ret = EndAddItem( sceneId, selfId )
						if ret > 0 then
							AddItemListToPlayer(sceneId,selfId)
							TipsToPlayer (sceneId,selfId,"#Y获得#G"..x540114_g_ItemNum.."个#Y"..x540114_g_ItemName)
							TipsToPlayer (sceneId,selfId,"由于背包空间已满,没有得到额外附加物品")
							TipsToPlayer (sceneId,selfId,"#Y消耗#G"..x540114_g_CostVigor.."点#Y活力")
							if SkillLevel < x540114_g_AbilitySkillLevel + 2 then
								if SkillLevel > 8 then 
									SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,SkillBaseLimit + x540114_g_AddSkillLimit)
									TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_AddSkillLimit.."点#Y熟练度")
								elseif SkillLevel > 0 and SkillLevel <= 8 then
									if SkillBaseLimit + x540114_g_AddSkillLimit <= x540114_g_SkillLMax then 
										SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,SkillBaseLimit + x540114_g_AddSkillLimit)
										TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_AddSkillLimit.."点#Y熟练度")
									elseif SkillBaseLimit + x540114_g_AddSkillLimit > x540114_g_SkillLMax and SkillBaseLimit < x540114_g_SkillLMax then
										SetAbilityExp(sceneId,selfId,x540114_g_AbilitySkillType,x540114_g_SkillLMax)
										TipsToPlayer (sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.."获得#G"..x540114_g_SkillLMax-SkillBaseLimit.."点#Y熟练度")
									else
										TipsToPlayer (sceneId,selfId,"熟练度已达上限")
									end
								end
							end
							SetPlayerVigor(sceneId,selfId, NowVigor - x540114_g_CostVigor)
							return 1
						else					
							BeginQuestEvent(sceneId)
								AddQuestText(sceneId,"#Y背包空间不足，无法得到采集物品！")
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
						end
					end
				else
					TipsToPlayer(sceneId,selfId,"#Y活力不足")
				end
			else
				TipsToPlayer(sceneId,selfId,"#Y"..x540114_g_AbilitySkillName.." 等级不足#R"..x540114_g_AbilitySkillLevel.."级")
			end
		end
	end
	return 0       	               
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x540114_OnProcOver(sceneId,selfId,targetId)

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function  TipsToPlayer (sceneId,selfId,str)
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
end