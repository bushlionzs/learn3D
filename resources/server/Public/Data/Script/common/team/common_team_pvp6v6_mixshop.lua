
x303010_g_ScriptId          		= 303010
x303010_g_Leader_Index      		= 5
x303010_g_MissionName       		="合成商店"

--BUF列表
x303010_g_BuffList					= {
										--NPC1
										{npcGUID=170005,name = "天神下凡1级（合成）", msg = "\n需要长生天的力量1级、长生天的守护1级、长生天的庇护1级。合成后的天神下凡1级兼备以上三个1级属性的效果！", levelmin = 10,levelmax = 79,buffrom={7910,7922,7934},bufto = 7958,price=1000},
										{npcGUID=170005,name = "天神下凡2级（合成）", msg = "\n需要长生天的力量2级、长生天的守护2级、长生天的庇护2级。合成后的天神下凡2级兼备以上三个2级属性的效果！", levelmin = 10,levelmax = 79,buffrom={7911,7923,7935},bufto = 7959,price=2000},
										{npcGUID=170005,name = "天神下凡3级（合成）", msg = "\n需要长生天的力量3级、长生天的守护3级、长生天的庇护3级。合成后的天神下凡3级兼备以上三个3级属性的效果！", levelmin = 10,levelmax = 79,buffrom={7912,7924,7936},bufto = 7960,price=3000},
										{npcGUID=170005,name = "天神下凡4级（合成）", msg = "\n需要长生天的力量4级、长生天的守护4级、长生天的庇护4级。合成后的天神下凡4级兼备以上三个4级属性的效果！", levelmin = 10,levelmax = 79,buffrom={7913,7925,7937},bufto = 7961,price=4000},

										{npcGUID=170005,name = "天神下凡1级（合成）", msg = "\n需要长生天的力量1级、长生天的守护1级、长生天的庇护1级。合成后的天神下凡1级兼备以上三个1级属性的效果！", levelmin = 80,levelmax = 99,buffrom={7914,7926,7938},bufto = 7962,price=1000},
										{npcGUID=170005,name = "天神下凡2级（合成）", msg = "\n需要长生天的力量2级、长生天的守护2级、长生天的庇护2级。合成后的天神下凡2级兼备以上三个2级属性的效果！", levelmin = 80,levelmax = 99,buffrom={7915,7927,7939},bufto = 7963,price=2000},
										{npcGUID=170005,name = "天神下凡3级（合成）", msg = "\n需要长生天的力量3级、长生天的守护3级、长生天的庇护3级。合成后的天神下凡3级兼备以上三个3级属性的效果！", levelmin = 80,levelmax = 99,buffrom={7916,7928,7940},bufto = 7964,price=3000},
										{npcGUID=170005,name = "天神下凡4级（合成）", msg = "\n需要长生天的力量4级、长生天的守护4级、长生天的庇护4级。合成后的天神下凡4级兼备以上三个4级属性的效果！", levelmin = 80,levelmax = 99,buffrom={7917,7929,7941},bufto = 7965,price=4000},

										{npcGUID=170005,name = "天神下凡1级（合成）", msg = "\n需要长生天的力量1级、长生天的守护1级、长生天的庇护1级。合成后的天神下凡1级兼备以上三个1级属性的效果！", levelmin = 100,levelmax = 161,buffrom={7918,7930,7942},bufto = 7966,price=1000},
										{npcGUID=170005,name = "天神下凡2级（合成）", msg = "\n需要长生天的力量2级、长生天的守护2级、长生天的庇护2级。合成后的天神下凡2级兼备以上三个2级属性的效果！", levelmin = 100,levelmax = 161,buffrom={7919,7931,7943},bufto = 7967,price=2000},
										{npcGUID=170005,name = "天神下凡3级（合成）", msg = "\n需要长生天的力量3级、长生天的守护3级、长生天的庇护3级。合成后的天神下凡3级兼备以上三个3级属性的效果！", levelmin = 100,levelmax = 161,buffrom={7920,7932,7944},bufto = 7968,price=3000},
										{npcGUID=170005,name = "天神下凡4级（合成）", msg = "\n需要长生天的力量4级、长生天的守护4级、长生天的庇护4级。合成后的天神下凡4级兼备以上三个4级属性的效果！", levelmin = 100,levelmax = 161,buffrom={7921,7933,7945},bufto = 7969,price=4000},

									  }
									  
x303010_g_ShowListFormatEnough		= "%s\n#W需要#G%d#W战场货币"
x303010_g_ShowListFormatNotEnough	= "#cFF0000%s"
x303010_g_FirstMessage				= "您要合成吗？"
x303010_g_BoughtMessage				= "恭喜您，合成成功！"
x303010_g_BoughtMessageFailed		= "#cFF0000\n\n合成失败,合成条件不满足！"

----------------------------------------------------------------------------------------------
--检查玩家是否拥有BUF列表中所有的BUF
----------------------------------------------------------------------------------------------
function x303010_IsHaveAllBufInList(sceneId,selfId,buflist)
	
	if buflist == nil then
		return 0
	end
	
	for i,itm in buflist do
		if IsHaveSpecificImpact(sceneId,selfId,itm) == 0 then
			return 0
		end
	end
	
	return 1
	
end

----------------------------------------------------------------------------------------------
--清空BUF
----------------------------------------------------------------------------------------------
function x303010_ClearBufList(sceneId,selfId,buflist )
	
	if buflist == nil then
		return 
	end
	
	for i,itm in buflist do
		if IsHaveSpecificImpact(sceneId,selfId,itm) == 1 then
			CancelSpecificImpact(sceneId,selfId,itm)			
		end
	end
end

----------------------------------------------------------------------------------------------
--给玩家BUF
----------------------------------------------------------------------------------------------
function x303010_GivePlayerBuf(sceneId,selfId,buf)
	SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,buf,0)
end

----------------------------------------------------------------------------------------------
--刷新BUF列表
----------------------------------------------------------------------------------------------
function x303010_RefreshBufList( sceneId,selfId,targetId)
	
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
    local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
    for i,itm in x303010_g_BuffList do
    	if nNpcGUID == itm.npcGUID and CallScriptFunction(303006,"CheckLevelRange",sceneId,itm.levelmin,itm.levelmax) == 1 then
    		if nHaveBattleMoney >= itm.price and x303010_IsHaveAllBufInList(sceneId,selfId,itm.buffrom) == 1 then
	    		AddQuestNumText(sceneId,x303010_g_ScriptId,"#Y"..itm.name,3,i);
    		else
	    		AddQuestNumText(sceneId,x303010_g_ScriptId,"#R"..itm.name,3,i);
	    	end
    	end
    end
    
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
	AddQuestNumText(sceneId,x303010_g_ScriptId,x303010_g_MissionName,3,x303010_g_ScriptId);
	
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303010_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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
	if idExt == x303010_g_ScriptId then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x303010_g_FirstMessage);
			x303010_RefreshBufList( sceneId,selfId,targetId)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
		return
	end
	
	if idExt > 100 then
		
		idExt = idExt - 100
		
		--验证NPCGUID
		local nNpcGUID = GetMonsterGUID(sceneId,targetId)
		if nNpcGUID ~= x303010_g_BuffList[idExt].npcGUID then
			return
		end
		--验证等级
		if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303010_g_BuffList[idExt].levelmin,x303010_g_BuffList[idExt].levelmax) ~= 1 then
			return
		end
		

		
		--购买结果
		BeginQuestEvent(sceneId)
			local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
			local nFixedPrice = x303010_g_BuffList[idExt].price
			if nHaveBattleMoney >= nFixedPrice then
			
				
				--给玩家BUF,同时扣除战场货币
				x303010_ClearBufList(sceneId,selfId,x303010_g_BuffList[idExt].buffrom )
				SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x303010_g_BuffList[idExt].bufto,0)
				CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
				
				--购买成功,给出提示
				AddQuestText(sceneId,x303010_g_BoughtMessage);
			else
				--购买失败,给出提示
				AddQuestText(sceneId,format(x303010_g_ShowListFormatEnough,x303010_g_BuffList[idExt].name,x303010_g_BuffList[idExt].price))
				AddQuestText(sceneId, x303010_g_BoughtMessageFailed);		
			end
			
			--刷新BUF列表
			--x303010_RefreshBufList( sceneId,selfId,targetId)
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
	end
	
	--越界了
	local nCount = getn(x303010_g_BuffList)
	if idExt < 1 or idExt > nCount then
		return 
	end
	
	--验证NPCGUID
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	if nNpcGUID ~= x303010_g_BuffList[idExt].npcGUID then
			return
	end
	
	--验证等级
	if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303010_g_BuffList[idExt].levelmin,x303010_g_BuffList[idExt].levelmax) ~= 1 then

		return
	end
	
	--购买结果
	BeginQuestEvent(sceneId)
		local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
		AddQuestText(sceneId,format(x303010_g_ShowListFormatEnough,x303010_g_BuffList[idExt].name,x303010_g_BuffList[idExt].price))
		AddQuestText(sceneId,x303010_g_BuffList[idExt].msg);

		if nHaveBattleMoney >= x303010_g_BuffList[idExt].price and x303010_IsHaveAllBufInList(sceneId,selfId,x303010_g_BuffList[idExt].buffrom) == 1 then
			
			AddQuestNumText(sceneId,x303010_g_ScriptId,"确定..",3,idExt + 100 );
		else
			AddQuestText(sceneId,"\n#R合成失败，不满足合成条件！");	
		end
		
		--刷新BUF列表
		--x303010_RefreshBufList( sceneId,selfId,targetId)
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303010_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303010_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303010_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303010_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303010_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303010_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303010_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303010_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303010_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
