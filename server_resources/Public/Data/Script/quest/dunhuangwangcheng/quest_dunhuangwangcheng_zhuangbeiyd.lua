x256217_g_scriptId = 256217 
x256217_g_MissionId1 = {3093,4224,4225,4226,4227}
x256217_g_MissionId2 = {3094,4232,4233,4234,4235}
x256217_g_MissionId3 = {3095,4236,4237,4238,4239}
x256217_g_MissionId4 = {2632,2633,2634,2635}

function x256217_ProcEventEntry(mapId, playerId, equipBadIndex, opType)
	local itemindex	=	GetItemTableIndexByIndex(mapId, playerId, equipBadIndex)
	
	for i, item in x256217_g_MissionId1 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then  --是否有引导任务
			
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 3,0,itemindex) --取玩家身上装备的星级，0表示为星。1标示为孔 2表示为宝石。
			local bag	=	GetBagItemCountByLess(mapId, playerId, 3,0,itemindex)   --取玩家包裹中装备的星级，最后一位表示为3星
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--如果大于三星，任务置为完成状态
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 27,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 28,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 30,0 )
	    	end
	   	break
	  end 
	end
	
	--if IsHaveQuestNM(mapId,playerId,x256217_g_MissionId2) == 1 then  --是否有引导任务
	 	for i, item in x256217_g_MissionId2 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then 
		--if 	optype		==	2 then	--2,打星，3，打孔 4，镶嵌
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --取得装备有几星
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 1,1,itemindex) --取玩家身上装备的星级，0表示为星。1标示为孔 2表示为宝石。
			local bag	=	GetBagItemCountByLess(mapId, playerId, 1,1,itemindex)   --取玩家包裹中装备的星级，最后一位表示为3星
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--如果大于三星，任务置为完成状态
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 34,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 47,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 35,0 )
	    	end
	   --end
	  end
	end
	
	for i, item in x256217_g_MissionId3 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then 
	--if IsHaveQuestNM(mapId,playerId,x256217_g_MissionId3) == 1 then  --是否有引导任务
	 
		--if 	optype		==	2 then	--2,打星，3，打孔 4，镶嵌
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --取得装备有几星
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 1,2,itemindex) --取玩家身上装备的星级，0表示为星。1标示为孔 2表示为宝石。
			local bag	=	GetBagItemCountByLess(mapId, playerId, 1,2,itemindex)   --取玩家包裹中装备的星级，最后一位表示为3星
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--如果大于三星，任务置为完成状态
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 36,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 48,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 37,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 38,0 )
	    	end
	   --end
	   
	end
	
	for i, item in x256217_g_MissionId4 do
	if IsHaveQuestNM(mapId,playerId,item) == 1 then  --是否有引导任务
	 
		--if 	optype		==	2 then	--2,打星，3，打孔 4，镶嵌
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --取得装备有几星
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 5,0,itemindex) --取玩家身上装备的星级，0表示为星。1标示为孔 2表示为宝石。
			local bag	=	GetBagItemCountByLess(mapId, playerId, 5,0,itemindex)   --取玩家包裹中装备的星级，最后一位表示为3星
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--如果大于五星，任务置为完成状态
	    	end
	  end
	   --end
	  end
	end
	
end

function x256217_IsSkillLikeScript( mapId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x256217_CancelImpacts( mapId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end


function x256217_OnConditionCheck( mapId, selfId )
	return 0
end

function x256217_OnDeplete( mapId, selfId )

	return 0
end

function x256217_OnActivateOnce( mapId, selfId )
end

function x256217_OnActivateEachTick( mapId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
