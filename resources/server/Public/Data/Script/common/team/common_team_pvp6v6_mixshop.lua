
x303010_g_ScriptId          		= 303010
x303010_g_Leader_Index      		= 5
x303010_g_MissionName       		="�ϳ��̵�"

--BUF�б�
x303010_g_BuffList					= {
										--NPC1
										{npcGUID=170005,name = "�����·�1�����ϳɣ�", msg = "\n��Ҫ�����������1������������ػ�1����������ıӻ�1�����ϳɺ�������·�1���汸��������1�����Ե�Ч����", levelmin = 10,levelmax = 79,buffrom={7910,7922,7934},bufto = 7958,price=1000},
										{npcGUID=170005,name = "�����·�2�����ϳɣ�", msg = "\n��Ҫ�����������2������������ػ�2����������ıӻ�2�����ϳɺ�������·�2���汸��������2�����Ե�Ч����", levelmin = 10,levelmax = 79,buffrom={7911,7923,7935},bufto = 7959,price=2000},
										{npcGUID=170005,name = "�����·�3�����ϳɣ�", msg = "\n��Ҫ�����������3������������ػ�3����������ıӻ�3�����ϳɺ�������·�3���汸��������3�����Ե�Ч����", levelmin = 10,levelmax = 79,buffrom={7912,7924,7936},bufto = 7960,price=3000},
										{npcGUID=170005,name = "�����·�4�����ϳɣ�", msg = "\n��Ҫ�����������4������������ػ�4����������ıӻ�4�����ϳɺ�������·�4���汸��������4�����Ե�Ч����", levelmin = 10,levelmax = 79,buffrom={7913,7925,7937},bufto = 7961,price=4000},

										{npcGUID=170005,name = "�����·�1�����ϳɣ�", msg = "\n��Ҫ�����������1������������ػ�1����������ıӻ�1�����ϳɺ�������·�1���汸��������1�����Ե�Ч����", levelmin = 80,levelmax = 99,buffrom={7914,7926,7938},bufto = 7962,price=1000},
										{npcGUID=170005,name = "�����·�2�����ϳɣ�", msg = "\n��Ҫ�����������2������������ػ�2����������ıӻ�2�����ϳɺ�������·�2���汸��������2�����Ե�Ч����", levelmin = 80,levelmax = 99,buffrom={7915,7927,7939},bufto = 7963,price=2000},
										{npcGUID=170005,name = "�����·�3�����ϳɣ�", msg = "\n��Ҫ�����������3������������ػ�3����������ıӻ�3�����ϳɺ�������·�3���汸��������3�����Ե�Ч����", levelmin = 80,levelmax = 99,buffrom={7916,7928,7940},bufto = 7964,price=3000},
										{npcGUID=170005,name = "�����·�4�����ϳɣ�", msg = "\n��Ҫ�����������4������������ػ�4����������ıӻ�4�����ϳɺ�������·�4���汸��������4�����Ե�Ч����", levelmin = 80,levelmax = 99,buffrom={7917,7929,7941},bufto = 7965,price=4000},

										{npcGUID=170005,name = "�����·�1�����ϳɣ�", msg = "\n��Ҫ�����������1������������ػ�1����������ıӻ�1�����ϳɺ�������·�1���汸��������1�����Ե�Ч����", levelmin = 100,levelmax = 161,buffrom={7918,7930,7942},bufto = 7966,price=1000},
										{npcGUID=170005,name = "�����·�2�����ϳɣ�", msg = "\n��Ҫ�����������2������������ػ�2����������ıӻ�2�����ϳɺ�������·�2���汸��������2�����Ե�Ч����", levelmin = 100,levelmax = 161,buffrom={7919,7931,7943},bufto = 7967,price=2000},
										{npcGUID=170005,name = "�����·�3�����ϳɣ�", msg = "\n��Ҫ�����������3������������ػ�3����������ıӻ�3�����ϳɺ�������·�3���汸��������3�����Ե�Ч����", levelmin = 100,levelmax = 161,buffrom={7920,7932,7944},bufto = 7968,price=3000},
										{npcGUID=170005,name = "�����·�4�����ϳɣ�", msg = "\n��Ҫ�����������4������������ػ�4����������ıӻ�4�����ϳɺ�������·�4���汸��������4�����Ե�Ч����", levelmin = 100,levelmax = 161,buffrom={7921,7933,7945},bufto = 7969,price=4000},

									  }
									  
x303010_g_ShowListFormatEnough		= "%s\n#W��Ҫ#G%d#Wս������"
x303010_g_ShowListFormatNotEnough	= "#cFF0000%s"
x303010_g_FirstMessage				= "��Ҫ�ϳ���"
x303010_g_BoughtMessage				= "��ϲ�����ϳɳɹ���"
x303010_g_BoughtMessageFailed		= "#cFF0000\n\n�ϳ�ʧ��,�ϳ����������㣡"

----------------------------------------------------------------------------------------------
--�������Ƿ�ӵ��BUF�б������е�BUF
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
--���BUF
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
--�����BUF
----------------------------------------------------------------------------------------------
function x303010_GivePlayerBuf(sceneId,selfId,buf)
	SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,buf,0)
end

----------------------------------------------------------------------------------------------
--ˢ��BUF�б�
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
--ö��
----------------------------------------------------------------------------------------------
function x303010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
	--����Գ���У��
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--������Ч�ĳ���
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	--��ʾBUF�б�
	AddQuestNumText(sceneId,x303010_g_ScriptId,x303010_g_MissionName,3,x303010_g_ScriptId);
	
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303010_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

	--����Գ���У��
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--������Ч�ĳ���
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	
	--Ҫ��ʾ�б�
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
		
		--��֤NPCGUID
		local nNpcGUID = GetMonsterGUID(sceneId,targetId)
		if nNpcGUID ~= x303010_g_BuffList[idExt].npcGUID then
			return
		end
		--��֤�ȼ�
		if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303010_g_BuffList[idExt].levelmin,x303010_g_BuffList[idExt].levelmax) ~= 1 then
			return
		end
		

		
		--������
		BeginQuestEvent(sceneId)
			local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
			local nFixedPrice = x303010_g_BuffList[idExt].price
			if nHaveBattleMoney >= nFixedPrice then
			
				
				--�����BUF,ͬʱ�۳�ս������
				x303010_ClearBufList(sceneId,selfId,x303010_g_BuffList[idExt].buffrom )
				SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x303010_g_BuffList[idExt].bufto,0)
				CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
				
				--����ɹ�,������ʾ
				AddQuestText(sceneId,x303010_g_BoughtMessage);
			else
				--����ʧ��,������ʾ
				AddQuestText(sceneId,format(x303010_g_ShowListFormatEnough,x303010_g_BuffList[idExt].name,x303010_g_BuffList[idExt].price))
				AddQuestText(sceneId, x303010_g_BoughtMessageFailed);		
			end
			
			--ˢ��BUF�б�
			--x303010_RefreshBufList( sceneId,selfId,targetId)
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
	end
	
	--Խ����
	local nCount = getn(x303010_g_BuffList)
	if idExt < 1 or idExt > nCount then
		return 
	end
	
	--��֤NPCGUID
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	if nNpcGUID ~= x303010_g_BuffList[idExt].npcGUID then
			return
	end
	
	--��֤�ȼ�
	if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303010_g_BuffList[idExt].levelmin,x303010_g_BuffList[idExt].levelmax) ~= 1 then

		return
	end
	
	--������
	BeginQuestEvent(sceneId)
		local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
		AddQuestText(sceneId,format(x303010_g_ShowListFormatEnough,x303010_g_BuffList[idExt].name,x303010_g_BuffList[idExt].price))
		AddQuestText(sceneId,x303010_g_BuffList[idExt].msg);

		if nHaveBattleMoney >= x303010_g_BuffList[idExt].price and x303010_IsHaveAllBufInList(sceneId,selfId,x303010_g_BuffList[idExt].buffrom) == 1 then
			
			AddQuestNumText(sceneId,x303010_g_ScriptId,"ȷ��..",3,idExt + 100 );
		else
			AddQuestText(sceneId,"\n#R�ϳ�ʧ�ܣ�������ϳ�������");	
		end
		
		--ˢ��BUF�б�
		--x303010_RefreshBufList( sceneId,selfId,targetId)
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303010_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303010_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303010_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303010_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303010_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303010_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303010_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303010_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303010_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
