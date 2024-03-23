
x303012_g_ScriptId          		= 303012
x303012_g_Leader_Index      		= 5
x303012_g_MissionName       		="攻击商店"

--BUF列表
x303012_g_BuffList					= {

										{npcGUID=170003,name = "长生天的力量1级（攻击）", msg = "\n提高玩家攻击200点", type=0, levelmin = 10,levelmax = 79,bufId = 7910,price=500, tab={}},
										{npcGUID=170003,name = "长生天的力量2级（攻击）", msg = "\n提高玩家攻击800点", type=0, levelmin = 10,levelmax = 79,bufId = 7911,price=1000,tab={1}},
										{npcGUID=170003,name = "长生天的力量3级（攻击）", msg = "\n提高玩家攻击1200点", type=0, levelmin = 10,levelmax = 79,bufId = 7912,price=1500,tab={1,2}},
										{npcGUID=170003,name = "长生天的力量4级（攻击）", msg = "\n提高玩家攻击1600点",type=0, levelmin = 10,levelmax = 79,bufId = 7913,price=2000,tab={1,2,3}},

										{npcGUID=170003,name = "长生天的力量1级（攻击）", msg = "\n提高玩家攻击350点", type=0, levelmin = 80,levelmax = 99,bufId = 7914,price=500, tab={}},
										{npcGUID=170003,name = "长生天的力量2级（攻击）", msg = "\n提高玩家攻击1400点", type=0, levelmin = 80,levelmax = 99,bufId = 7915,price=1000,tab={5}},
										{npcGUID=170003,name = "长生天的力量3级（攻击）", msg = "\n提高玩家攻击2100点", type=0, levelmin = 80,levelmax = 99,bufId = 7916,price=1500,tab={5,6}},
										{npcGUID=170003,name = "长生天的力量4级（攻击）", msg = "\n提高玩家攻击2800点",type=0, levelmin = 80,levelmax = 99,bufId = 7917,price=2000,tab={5,6,7}},

										{npcGUID=170003,name = "长生天的力量1级（攻击）", msg = "\n提高玩家攻击475点", type=0, levelmin = 100,levelmax = 161,bufId = 7918,price=500, tab={}},
										{npcGUID=170003,name = "长生天的力量2级（攻击）", msg = "\n提高玩家攻击1900点", type=0, levelmin = 100,levelmax = 161,bufId = 7919,price=1000,tab={9}},
										{npcGUID=170003,name = "长生天的力量3级（攻击）", msg = "\n提高玩家攻击2850点", type=0, levelmin = 100,levelmax = 161,bufId = 7920,price=1500,tab={9,10}},
										{npcGUID=170003,name = "长生天的力量4级（攻击）", msg = "\n提高玩家攻击3800点",type=0, levelmin = 100,levelmax = 161,bufId = 7921,price=2000,tab={9,10,11}},

									  }
									  
x303012_g_ShowListFormatEnough		= "%s\n#W需要#G%d#W战场货币"
x303012_g_FirstMessage				= "您要点什么吗?"
x303012_g_BoughtMessage				= "恭喜，您购买成功!"
x303012_g_BoughtMessageFailed		= "\n#R购买失败，您的战场货币不足！"
x303012_g_BoughtMessageBagError		= "\n#R购买失败，您的背包空间不足！"


----------------------------------------------------------------------------------------------
--刷新BUF列表
----------------------------------------------------------------------------------------------
function x303012_RefreshBufList( sceneId,selfId,targetId)
	
	local priceproc = function(sceneId,selfId,index) return (x303012_g_BuffList[index].price - x303012_FixPrice( sceneId,selfId,index )) end

	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
    local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
    for i,itm in x303012_g_BuffList do
    	if nNpcGUID == itm.npcGUID and CallScriptFunction(303006,"CheckLevelRange",sceneId,itm.levelmin,itm.levelmax) == 1 then
	    	if nHaveBattleMoney < priceproc(sceneId,selfId,i) then
    			AddQuestNumText(sceneId,x303012_g_ScriptId,"#R"..itm.name,3,i);
    		else
	    		AddQuestNumText(sceneId,x303012_g_ScriptId,"#Y"..itm.name,3,i);
	    	end
    	end
    end
    
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303012_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
	--必须对场景校验
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--不是有效的场景
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	--显示BUF列表
	AddQuestNumText(sceneId,x303012_g_ScriptId,x303012_g_MissionName,3,x303012_g_ScriptId);
	
end

----------------------------------------------------------------------------------------------
--修正价格
----------------------------------------------------------------------------------------------
function x303012_FixPrice( sceneId,selfId,nIndex )

	local nCount = getn(x303012_g_BuffList)
	if nIndex <= 0 or nIndex > nCount then
		return 0
	end
	
	local item = x303012_g_BuffList[nIndex]
	for i,itm in item.tab do
		if IsHaveSpecificImpact(sceneId,selfId,x303012_g_BuffList[itm].bufId ) == 1 then
			return x303012_g_BuffList[itm].price*0.8
		end
	end
	
	return 0
		
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303012_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

	--必须对场景校验
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--不是有效的场景
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	
	--要显示列表
	if idExt == x303012_g_ScriptId then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x303012_g_FirstMessage);
			x303012_RefreshBufList( sceneId,selfId,targetId)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
		return
	end
	
	if idExt > 100 then
		
		idExt = idExt - 100
		
		--验证NPCGUID
		local nNpcGUID = GetMonsterGUID(sceneId,targetId)
		if nNpcGUID ~= x303012_g_BuffList[idExt].npcGUID then
			return
		end
		
		--验证等级
		if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303012_g_BuffList[idExt].levelmin,x303012_g_BuffList[idExt].levelmax) ~= 1 then
			return
		end
		
		--购买结果
		BeginQuestEvent(sceneId)
			local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
			local nFixedPrice = x303012_g_BuffList[idExt].price - x303012_FixPrice( sceneId,selfId,idExt )
			if nHaveBattleMoney >= nFixedPrice then
			
				if x303012_g_BuffList[idExt].type == 0 then
				
					--给玩家BUF,同时扣除战场货币
					SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x303012_g_BuffList[idExt].bufId,0)
					CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
					
					--购买成功,给出提示
					AddQuestText(sceneId,x303012_g_BoughtMessage);
				elseif x303012_g_BuffList[idExt].type == 1 then
					
					BeginAddItem(sceneId)
					AddBindItem(sceneId,x303012_g_BuffList[idExt].bufId,1)			
					local ret =  EndAddItem(sceneId,selfId)
					if ret > 0 then
						CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
		  				AddItemListToPlayer(sceneId,selfId)
		  				
		  				--购买成功,给出提示
						AddQuestText(sceneId,x303012_g_BoughtMessage);
		  			else
		  				AddQuestText(sceneId, x303012_g_BoughtMessageBagError);
		  			end
				end
				
			else
				--购买失败,给出提示
				AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,x303012_g_BuffList[idExt].price))
				AddQuestText(sceneId, x303012_g_BoughtMessageFailed);		
			end
			
			--刷新BUF列表
			--x303012_RefreshBufList( sceneId,selfId,targetId)
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
	end
	
	--越界了
	local nCount = getn(x303012_g_BuffList)
	if idExt < 1 or idExt > nCount then
		return 
	end
	
	
	--验证NPCGUID
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	if nNpcGUID ~= x303012_g_BuffList[idExt].npcGUID then
		return
	end
	
	--验证等级
	if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303012_g_BuffList[idExt].levelmin,x303012_g_BuffList[idExt].levelmax) ~= 1 then
		return
	end
	
	--购买结果
	BeginQuestEvent(sceneId)
		local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
		local nFixedPrice = x303012_g_BuffList[idExt].price - x303012_FixPrice( sceneId,selfId,idExt )
		if nHaveBattleMoney >= nFixedPrice then
		
			if x303012_g_BuffList[idExt].type == 0 then
		
				AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,nFixedPrice))
				AddQuestText(sceneId,x303012_g_BuffList[idExt].msg);
			else
				AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,nFixedPrice))
				AddQuestText(sceneId,x303012_g_BuffList[idExt].msg);
			end
			AddQuestNumText(sceneId,x303012_g_ScriptId,"确定..",3,idExt + 100 );

		else
			AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,nFixedPrice))
			AddQuestText(sceneId, x303012_g_BoughtMessageFailed);
		end
		
		--刷新BUF列表
		--x303012_RefreshBufList( sceneId,selfId,targetId)
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303012_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303012_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303012_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303012_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303012_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303012_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303012_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303012_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303012_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
