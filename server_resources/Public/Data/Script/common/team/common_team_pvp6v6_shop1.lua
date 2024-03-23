
x303012_g_ScriptId          		= 303012
x303012_g_Leader_Index      		= 5
x303012_g_MissionName       		="�����̵�"

--BUF�б�
x303012_g_BuffList					= {

										{npcGUID=170003,name = "�����������1����������", msg = "\n�����ҹ���200��", type=0, levelmin = 10,levelmax = 79,bufId = 7910,price=500, tab={}},
										{npcGUID=170003,name = "�����������2����������", msg = "\n�����ҹ���800��", type=0, levelmin = 10,levelmax = 79,bufId = 7911,price=1000,tab={1}},
										{npcGUID=170003,name = "�����������3����������", msg = "\n�����ҹ���1200��", type=0, levelmin = 10,levelmax = 79,bufId = 7912,price=1500,tab={1,2}},
										{npcGUID=170003,name = "�����������4����������", msg = "\n�����ҹ���1600��",type=0, levelmin = 10,levelmax = 79,bufId = 7913,price=2000,tab={1,2,3}},

										{npcGUID=170003,name = "�����������1����������", msg = "\n�����ҹ���350��", type=0, levelmin = 80,levelmax = 99,bufId = 7914,price=500, tab={}},
										{npcGUID=170003,name = "�����������2����������", msg = "\n�����ҹ���1400��", type=0, levelmin = 80,levelmax = 99,bufId = 7915,price=1000,tab={5}},
										{npcGUID=170003,name = "�����������3����������", msg = "\n�����ҹ���2100��", type=0, levelmin = 80,levelmax = 99,bufId = 7916,price=1500,tab={5,6}},
										{npcGUID=170003,name = "�����������4����������", msg = "\n�����ҹ���2800��",type=0, levelmin = 80,levelmax = 99,bufId = 7917,price=2000,tab={5,6,7}},

										{npcGUID=170003,name = "�����������1����������", msg = "\n�����ҹ���475��", type=0, levelmin = 100,levelmax = 161,bufId = 7918,price=500, tab={}},
										{npcGUID=170003,name = "�����������2����������", msg = "\n�����ҹ���1900��", type=0, levelmin = 100,levelmax = 161,bufId = 7919,price=1000,tab={9}},
										{npcGUID=170003,name = "�����������3����������", msg = "\n�����ҹ���2850��", type=0, levelmin = 100,levelmax = 161,bufId = 7920,price=1500,tab={9,10}},
										{npcGUID=170003,name = "�����������4����������", msg = "\n�����ҹ���3800��",type=0, levelmin = 100,levelmax = 161,bufId = 7921,price=2000,tab={9,10,11}},

									  }
									  
x303012_g_ShowListFormatEnough		= "%s\n#W��Ҫ#G%d#Wս������"
x303012_g_FirstMessage				= "��Ҫ��ʲô��?"
x303012_g_BoughtMessage				= "��ϲ��������ɹ�!"
x303012_g_BoughtMessageFailed		= "\n#R����ʧ�ܣ�����ս�����Ҳ��㣡"
x303012_g_BoughtMessageBagError		= "\n#R����ʧ�ܣ����ı����ռ䲻�㣡"


----------------------------------------------------------------------------------------------
--ˢ��BUF�б�
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
--ö��
----------------------------------------------------------------------------------------------
function x303012_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
	AddQuestNumText(sceneId,x303012_g_ScriptId,x303012_g_MissionName,3,x303012_g_ScriptId);
	
end

----------------------------------------------------------------------------------------------
--�����۸�
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
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303012_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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
		
		--��֤NPCGUID
		local nNpcGUID = GetMonsterGUID(sceneId,targetId)
		if nNpcGUID ~= x303012_g_BuffList[idExt].npcGUID then
			return
		end
		
		--��֤�ȼ�
		if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303012_g_BuffList[idExt].levelmin,x303012_g_BuffList[idExt].levelmax) ~= 1 then
			return
		end
		
		--������
		BeginQuestEvent(sceneId)
			local nHaveBattleMoney = CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleMoney",sceneId,selfId)
			local nFixedPrice = x303012_g_BuffList[idExt].price - x303012_FixPrice( sceneId,selfId,idExt )
			if nHaveBattleMoney >= nFixedPrice then
			
				if x303012_g_BuffList[idExt].type == 0 then
				
					--�����BUF,ͬʱ�۳�ս������
					SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x303012_g_BuffList[idExt].bufId,0)
					CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
					
					--����ɹ�,������ʾ
					AddQuestText(sceneId,x303012_g_BoughtMessage);
				elseif x303012_g_BuffList[idExt].type == 1 then
					
					BeginAddItem(sceneId)
					AddBindItem(sceneId,x303012_g_BuffList[idExt].bufId,1)			
					local ret =  EndAddItem(sceneId,selfId)
					if ret > 0 then
						CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"SubBattleMoney",sceneId,selfId,nFixedPrice)
		  				AddItemListToPlayer(sceneId,selfId)
		  				
		  				--����ɹ�,������ʾ
						AddQuestText(sceneId,x303012_g_BoughtMessage);
		  			else
		  				AddQuestText(sceneId, x303012_g_BoughtMessageBagError);
		  			end
				end
				
			else
				--����ʧ��,������ʾ
				AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,x303012_g_BuffList[idExt].price))
				AddQuestText(sceneId, x303012_g_BoughtMessageFailed);		
			end
			
			--ˢ��BUF�б�
			--x303012_RefreshBufList( sceneId,selfId,targetId)
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return
	end
	
	--Խ����
	local nCount = getn(x303012_g_BuffList)
	if idExt < 1 or idExt > nCount then
		return 
	end
	
	
	--��֤NPCGUID
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	if nNpcGUID ~= x303012_g_BuffList[idExt].npcGUID then
		return
	end
	
	--��֤�ȼ�
	if CallScriptFunction(303006,"CheckLevelRange",sceneId,x303012_g_BuffList[idExt].levelmin,x303012_g_BuffList[idExt].levelmax) ~= 1 then
		return
	end
	
	--������
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
			AddQuestNumText(sceneId,x303012_g_ScriptId,"ȷ��..",3,idExt + 100 );

		else
			AddQuestText(sceneId,format(x303012_g_ShowListFormatEnough,x303012_g_BuffList[idExt].name,nFixedPrice))
			AddQuestText(sceneId, x303012_g_BoughtMessageFailed);
		end
		
		--ˢ��BUF�б�
		--x303012_RefreshBufList( sceneId,selfId,targetId)
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303012_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303012_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303012_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303012_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303012_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303012_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303012_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303012_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303012_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
