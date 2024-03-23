
x303008_g_ScriptId          		= 303008
x303008_g_Leader_Index      		= 5
x303008_g_MissionName       		="�����̵�"

--BUF�б�
x303008_g_BuffList					= {

										{npcGUID=170004,name = "�о���",msg = "\n�����ָ����8000��Ѫ��������30�롣�ܵ��˺����ټ����ָ���",type=1,levelmin = 10,levelmax = 161,bufId = 12041200,price=100, tab={}},

									  }
									  
x303008_g_ShowListFormatEnough		= "%s\n#W��Ҫ#G%d#Wս������"
x303008_g_FirstMessage				= "��Ҫ��ʲô��?"
x303008_g_BoughtMessage				= "��ϲ��������ɹ�!"
x303008_g_BoughtMessageFailed		= "\n#R����ʧ�ܣ�����ս�����Ҳ��㣡"
x303008_g_BoughtMessageBagError		= "\n#R����ʧ�ܣ����ı����ռ䲻�㣡"

----------------------------------------------------------------------------------------------
--ˢ��BUF�б�
----------------------------------------------------------------------------------------------
function x303008_RefreshBufList( sceneId,selfId,targetId)
	
	local priceproc = function(sceneId,selfId,index) return (x303008_g_BuffList[index].price - x303008_FixPrice( sceneId,selfId,index )) end
	
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
    local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
    for i,itm in x303008_g_BuffList do
    	if nNpcGUID == itm.npcGUID and CallScriptFunction(303006,"CheckLevelRange",sceneId,itm.levelmin,itm.levelmax) == 1 then
	    	if nHaveBattleMoney < priceproc(sceneId,selfId,i) then
    			AddQuestNumText(sceneId,x303008_g_ScriptId,"#R"..itm.name,3,i);
    		else
	    		AddQuestNumText(sceneId,x303008_g_ScriptId,"#Y"..itm.name,3,i);
	    	end
    	end
    end
    
end

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303008_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
	AddQuestNumText(sceneId,x303008_g_ScriptId,x303008_g_MissionName,3,x303008_g_ScriptId);
	
end

----------------------------------------------------------------------------------------------
--�����۸�
----------------------------------------------------------------------------------------------
function x303008_FixPrice( sceneId,selfId,nIndex )

	local nCount = getn(x303008_g_BuffList)
	if nIndex <= 0 or nIndex > nCount then
		return 0
	end
	
	local item = x303008_g_BuffList[nIndex]
	for i,itm in item.tab do
		if IsHaveSpecificImpact(sceneId,selfId,x303008_g_BuffList[itm].bufId ) == 1 then
			return x303008_g_BuffList[itm].price*0.8
		end
	end
	
	return 0
		
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303008_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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
	if idExt == x303008_g_ScriptId then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x303008_g_FirstMessage);
			x303008_RefreshBufList( sceneId,selfId,targetId)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
		return
	end
	
	if idExt > 100 then
		
		idExt = idExt - 100
		
		--��֤NPCGUID
		local nNpcGUID = GetMonsterGUID(sceneId,targetId)
		if nNpcGUID ~= x303008_g_BuffList[idExt].npcGUID then
			return
		end

		--��֤�ȼ�
		if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303008_g_BuffList[idExt].levelmin,x303008_g_BuffList[idExt].levelmax) ~= 1 then
			return
		end
		

		
		--������
		BeginQuestEvent(sceneId)
			local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
			local nFixedPrice = x303008_g_BuffList[idExt].price - x303008_FixPrice( sceneId,selfId,idExt )
			if nHaveBattleMoney >= nFixedPrice then
			
				if x303008_g_BuffList[idExt].type == 0 then
				
					--�����BUF,ͬʱ�۳�ս������
					SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x303008_g_BuffList[idExt].bufId,0)
					CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
					
					--����ɹ�,������ʾ
					AddQuestText(sceneId,x303008_g_BoughtMessage);
				elseif x303008_g_BuffList[idExt].type == 1 then
					
					BeginAddItem(sceneId)
					AddBindItem(sceneId,x303008_g_BuffList[idExt].bufId,1)			
					local ret =  EndAddItem(sceneId,selfId)
					if ret > 0 then
						CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
		  				AddItemListToPlayer(sceneId,selfId)
		  				
		  				--����ɹ�,������ʾ
						AddQuestText(sceneId,x303008_g_BoughtMessage);
		  			else
		  				AddQuestText(sceneId, x303008_g_BoughtMessageBagError);
		  			end
				end
				
			else
				--����ʧ��,������ʾ
				AddQuestText(sceneId,format(x303008_g_ShowListFormatEnough,x303008_g_BuffList[idExt].name,x303008_g_BuffList[idExt].price))
				AddQuestText(sceneId, x303008_g_BoughtMessageFailed);		
			end
			
			--ˢ��BUF�б�
			--x303008_RefreshBufList( sceneId,selfId,targetId)
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
	end
	
	--Խ����
	local nCount = getn(x303008_g_BuffList)
	if idExt < 1 or idExt > nCount then
		return 
	end
	
	
	--��֤NPCGUID
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	if nNpcGUID ~= x303008_g_BuffList[idExt].npcGUID then
			return
	end
	
	--��֤�ȼ�
	if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303008_g_BuffList[idExt].levelmin,x303008_g_BuffList[idExt].levelmax) ~= 1 then

		return
	end
	
	--������
	BeginQuestEvent(sceneId)
		local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
		local nFixedPrice = x303008_g_BuffList[idExt].price - x303008_FixPrice( sceneId,selfId,idExt )
		if nHaveBattleMoney >= nFixedPrice then
		
			if x303008_g_BuffList[idExt].type == 0 then
		
				AddQuestText(sceneId,format(x303008_g_ShowListFormatEnough,x303008_g_BuffList[idExt].name,nFixedPrice))
				AddQuestText(sceneId,x303008_g_BuffList[idExt].msg);
			else
				AddQuestText(sceneId,format(x303008_g_ShowListFormatEnough,x303008_g_BuffList[idExt].name,nFixedPrice))
				AddQuestText(sceneId,x303008_g_BuffList[idExt].msg);
			end
			AddQuestNumText(sceneId,x303008_g_ScriptId,"ȷ��..",3,idExt + 100 );

		else
			AddQuestText(sceneId,format(x303008_g_ShowListFormatEnough,x303008_g_BuffList[idExt].name,nFixedPrice))
			AddQuestText(sceneId, x303008_g_BoughtMessageFailed);
		end
		
		--ˢ��BUF�б�
		--x303008_RefreshBufList( sceneId,selfId,targetId)
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303008_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303008_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303008_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303008_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303008_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303008_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303008_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303008_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303008_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
