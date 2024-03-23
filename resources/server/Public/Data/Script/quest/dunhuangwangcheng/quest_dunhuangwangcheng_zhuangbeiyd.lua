x256217_g_scriptId = 256217 
x256217_g_MissionId1 = {3093,4224,4225,4226,4227}
x256217_g_MissionId2 = {3094,4232,4233,4234,4235}
x256217_g_MissionId3 = {3095,4236,4237,4238,4239}
x256217_g_MissionId4 = {2632,2633,2634,2635}

function x256217_ProcEventEntry(mapId, playerId, equipBadIndex, opType)
	local itemindex	=	GetItemTableIndexByIndex(mapId, playerId, equipBadIndex)
	
	for i, item in x256217_g_MissionId1 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then  --�Ƿ�����������
			
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 3,0,itemindex) --ȡ�������װ�����Ǽ���0��ʾΪ�ǡ�1��ʾΪ�� 2��ʾΪ��ʯ��
			local bag	=	GetBagItemCountByLess(mapId, playerId, 3,0,itemindex)   --ȡ��Ұ�����װ�����Ǽ������һλ��ʾΪ3��
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--����������ǣ�������Ϊ���״̬
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 27,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 28,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 30,0 )
	    	end
	   	break
	  end 
	end
	
	--if IsHaveQuestNM(mapId,playerId,x256217_g_MissionId2) == 1 then  --�Ƿ�����������
	 	for i, item in x256217_g_MissionId2 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then 
		--if 	optype		==	2 then	--2,���ǣ�3����� 4����Ƕ
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --ȡ��װ���м���
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 1,1,itemindex) --ȡ�������װ�����Ǽ���0��ʾΪ�ǡ�1��ʾΪ�� 2��ʾΪ��ʯ��
			local bag	=	GetBagItemCountByLess(mapId, playerId, 1,1,itemindex)   --ȡ��Ұ�����װ�����Ǽ������һλ��ʾΪ3��
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--����������ǣ�������Ϊ���״̬
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 34,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 47,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 35,0 )
	    	end
	   --end
	  end
	end
	
	for i, item in x256217_g_MissionId3 do
		if IsHaveQuestNM(mapId,playerId,item) == 1 then 
	--if IsHaveQuestNM(mapId,playerId,x256217_g_MissionId3) == 1 then  --�Ƿ�����������
	 
		--if 	optype		==	2 then	--2,���ǣ�3����� 4����Ƕ
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --ȡ��װ���м���
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 1,2,itemindex) --ȡ�������װ�����Ǽ���0��ʾΪ�ǡ�1��ʾΪ�� 2��ʾΪ��ʯ��
			local bag	=	GetBagItemCountByLess(mapId, playerId, 1,2,itemindex)   --ȡ��Ұ�����װ�����Ǽ������һλ��ʾΪ3��
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--����������ǣ�������Ϊ���״̬
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 36,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 48,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 37,0 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", mapId, playerId, 38,0 )
	    	end
	   --end
	   
	end
	
	for i, item in x256217_g_MissionId4 do
	if IsHaveQuestNM(mapId,playerId,item) == 1 then  --�Ƿ�����������
	 
		--if 	optype		==	2 then	--2,���ǣ�3����� 4����Ƕ
		 --local xing	= GetEquipLevel(mapId,playerId,equipIndex)  --ȡ��װ���м���
		  
		  
	   		--if xing >=3 then 
	   		local equip	=	GetEquipItemCountByLess(mapId, playerId, 5,0,itemindex) --ȡ�������װ�����Ǽ���0��ʾΪ�ǡ�1��ʾΪ�� 2��ʾΪ��ʯ��
			local bag	=	GetBagItemCountByLess(mapId, playerId, 5,0,itemindex)   --ȡ��Ұ�����װ�����Ǽ������һλ��ʾΪ3��
			if equip >= 1 or bag >=1 then
	  			local 	misIndex = GetQuestIndexByID(mapId,playerId,item)                                                  
	    		SetQuestByIndex(mapId,playerId,misIndex,7,1)		--����������ǣ�������Ϊ���״̬
	    	end
	  end
	   --end
	  end
	end
	
end

function x256217_IsSkillLikeScript( mapId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x256217_CancelImpacts( mapId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
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
	return 1; --���������Խű�, ֻ�����պ���.
end
