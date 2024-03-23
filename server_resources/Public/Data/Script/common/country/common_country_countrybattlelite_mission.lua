--����ս����ű�

x310155_g_ScriptId = 310155
x310155_g_BonusScriptId = 310151
x310155_g_MissionId = 7559
x310155_g_LevelLess	= 	40 
x310155_g_MissionName="�����ҡ�����ս"
x310155_g_TickBuf	= 8727
x310155_g_BufID = {8719,8720,8721,8722,8723,8724,8725,8726,8727}--���BUFID,����ҽ�������սʱ,���Ӵ˱��ȡBUFID,�˱�˳��Ϊ:¥��,����,����,�ػ�


----------------------------------------------------------
--ö��
----------------------------------------------------------
function x310155_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    
    --���𲻹�
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end
    
    local str = "�����ҡ��μ�����ս"
    
    --�д���������ʾ��ضԻ���
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--�ǽ���ӵ�����
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		
		if nDay == nCurDayTime then
			str = "�����ҡ�����ս������ȡ"
		end 
	end    
    
    --����ս����ť
    local state = GetQuestStateNM(sceneId,selfId,NPCId,x310155_g_MissionId)
    AddQuestNumText( sceneId, x310155_g_MissionId, str, state );  
end

----------------------------------------------------------
--��ʾ������Ϣ
----------------------------------------------------------
function x310155_DispatchMissionInfo( sceneId, selfId, NPCId )
end

----------------------------------------------------------
--Ĭ�϶Ի���
----------------------------------------------------------
function x310155_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	
    
    --���𲻹�
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end
    
    if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--�ǽ���ӵ�����
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		
		if nDay == nCurDayTime then
			--����Ƿ���������
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) ~= 1 then
				if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)  >= 0 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y�����ҡ�����ս������ȡ#W#r\tֻ���ڵ��졾����ս������֮���21��00-21��20��������ս��ǰ����10��������ȡ������")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
			else
				
				if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y�����ҡ�����ս������ȡ#W#r\t�������Ĺ�����ǰ����������ս����ֻ���ڽ���֮���10��������ȡ������")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
				
			end
			
			local nCheckResult = CallScriptFunction(x310155_g_BonusScriptId,"CheckValid",sceneId,selfId)
			if nCheckResult ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y�����ҡ�����ս������ȡ#W#r\tֻ���ڵ��졾����ս������֮���21��00-21��20��ȡ������")
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,NPCId)
				return	
			end
	
	    	--����ս�Ƿ���
		    
	    	--��������
	    	CallScriptFunction(x310155_g_BonusScriptId,"ProcEventEntry",sceneId,selfId,NPCId,x310155_g_BonusScriptId,-1 )	    
		    
		    return
		else
			
				--�Ϸ�����
		    if GetMergeDBToggle() == 1 then
		        return
		    end
		    
		    --�������ݿ⿪��
				local UpdateDBflag = GetUpdateDBBeforeToggle()
				if UpdateDBflag==1 then
					return
				end
		    
		    --���Է�����
		    --if GetTestServerToggle() == 0 then
		    --    return
		    --end
		
		    --ս���Լ��Ŀ���
		    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
		        return
		    end
		    
		    --ս����û�д�
		    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) < 0 then
		    	BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ڻ����ܲμӡ����ҡ�����ս��")
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,NPCId)
		    	return
		    end
		    
		    --�д���������ʾ��ضԻ���
			if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
				
				--�ǽ���ӵ�����
				local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
				local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
				local nCurDayTime = GetDayOfYear()
				if nDay == nCurDayTime then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���Ѿ��μӹ������ҡ�����ս�ˣ�")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
			end
	    	
	    	--��ʾ��������Ϣ��NPC��������)���������NPC���������ǻ��Ǳ߾�
	    	BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y�����ҡ��μ�����ս#W#r\t�����ҡ�����ս�Ѿ������ˣ�Ҫ�μ�����ֻ��������ս���������#G20��00-20��20#W֮��μ�����ս���μ�����ս���������Ҫ�뿪#G���˸����Ĺ������ǣ��߾��͹ŵ�#W����������#R��������ս����#W���ſ��Խ��д��͡�")
			EndQuestEvent(sceneId)
			DispatchQuestInfoNM(sceneId,selfId,NPCId,x310155_g_ScriptId,x310155_g_MissionId)
			
		end 
	end    
	
	
	--Ĭ�ϴ���
		--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    --ս����û�д�
    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) < 0 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y�����ҡ��μ�����ս#W#r\t�����ڻ����ܲμӡ����ҡ�����ս��")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,NPCId)
    	return
    end
    
    --�д���������ʾ��ضԻ���
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
		
		--�ǽ���ӵ�����
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId)
		local nDay = GetQuestParam( sceneId,selfId,misIndex,4 ) - 100
		local nCurDayTime = GetDayOfYear()
		if nDay == nCurDayTime then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y�����ҡ��μ�����ս#W#r\t���Ѿ��μӹ������ҡ�����ս�ˣ�")
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
	end
	
	--��ʾ��������Ϣ��NPC��������)���������NPC���������ǻ��Ǳ߾�
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y�����ҡ��μ�����ս#W#r\t�����ҡ�����ս�Ѿ������ˣ�Ҫ�μ�����ֻ��������ս���������#G20��00-20��20#W֮��μ�����ս���μ�����ս��������뿪#G���˸����Ĺ������ǣ��߾��͹ŵ�#W����������#R��������ս����#W���ſ��Խ��д��͡���")
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId,selfId,NPCId,x310155_g_ScriptId,x310155_g_MissionId)
end


----------------------------------------------------------
--������
----------------------------------------------------------
function x310155_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

----------------------------------------------------------
--��齻����
----------------------------------------------------------
function x310155_CheckSubmit( sceneId, selfId, NPCId)
	return 1
end

----------------------------------------------------------
--���������񣬽������NPCֻ�������ǻ��Ǳ߾�
----------------------------------------------------------
function x310155_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )

		--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end
    
    
    --���𲻹�
    if GetLevel(sceneId,selfId) < x310155_g_LevelLess then
    	return
    end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end

	--����Ƿ���״̬
	local campFlag = CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp", sceneId, selfId)
	local nMatchCountry= CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_MatchCountry", sceneId, selfId)
	
	if campFlag < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����ҡ�����սû�п�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	--�������Ƿ��Ѿ��ӹ�
	if x310155_IsMissionCanAccept( sceneId,selfId ) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�������Ѿ��μӹ������ҡ�����ս�ˣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local minTime = GetMinOfDay()
    
    --�ڲ���ʱ�����
    local nFrom = 20*60 + 0
    local nTo   = 20*60 + 20

    if minTime < nFrom or minTime > nTo then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�μӡ����ҡ�����սʱ���ѹ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
        return
    end
    
    --����״̬���ܲμ�����ս
    if IsHideName(sceneId,selfId) ~= 0 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"����״̬���ܲμӡ����ҡ�����ս��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    	return
    end
	
	--���û�нӹ����Ժ�Ϊ����������
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) == 0 then
		
		--��������
		if IsQuestFullNM(sceneId,selfId)==1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���������Ѿ����ˣ��޷��μӡ����ҡ�����ս��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 
		end
		
		if sceneId == 89 or sceneId == 189 or sceneId == 289 or sceneId == 389 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�˳������ܽӡ����ҡ�����ս����")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
		--����������
		if AddQuest(sceneId,selfId,x310155_g_MissionId,x310155_g_ScriptId,0,0,0,1) ~= 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�μӡ����ҡ�����սʧ�ܣ��޷�����������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
	end
	
	
	GamePlayScriptLog( sceneId, selfId, 1511)
	
	local nCurDayTime = GetDayOfYear()
	
	--������������
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
	
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,3,0)					--�趨�������
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,4,nCurDayTime+100)		--�趨����
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,5,campFlag)				--�趨��Ӫ
	SetQuestParam( sceneId,selfId,x310155_g_MissionId,6,nMatchCountry)		--�趨�жԹ���
	
	--���ý���������
	x310155_SetMissionAcceptDate(sceneId,selfId)
	
	--��������BUFID
	local nCountry = GetCurCountry(sceneId,selfId)
	local nBufID = x310155_g_BufID[nCountry*2+1]
	if nBufID ~= -1 then
		if GetSex(sceneId,selfId) == 0 then
			nBufID = nBufID + 1
		end
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,nBufID,0)
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x310155_g_TickBuf,0)
	end
	
	--����ˢ������
	x310155_ProcQuestLogRefresh	( sceneId,selfId,x310155_g_MissionId)
	
	--���������ʾ
	x310155_Msg2toplayer( sceneId, selfId,0)
    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "<ErrorName>"
    end

    local nCountry = GetCurCountry( sceneId,selfId)
    local strMsg = format("CBL:<Info>CountryBattleLiteChangeScene sceneId = %d,name = %s Country = %d,nMatchCountry = %d campFlag = %d",sceneId, name,nCountry,nMatchCountry,campFlag )
    WriteLog( 1, strMsg ) 
	     
end

----------------------------------------------------------
--ɾ��BUF
----------------------------------------------------------
function x310155_CancelBufId( sceneId,selfId )

	for i,item in x310155_g_BufID do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end

end

----------------------------------------------------------
--��������
----------------------------------------------------------
function x310155_ProcQuestAbandon(sceneId, selfId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) <= 0 then
		return 
	end
	DelQuest(sceneId, selfId, x310155_g_MissionId)
  	x310155_Msg2toplayer( sceneId, selfId,1)
  	x310155_CancelBufId( sceneId,selfId )
  	
  	GamePlayScriptLog( sceneId, selfId, 1513)			
end

----------------------------------------------------------
--������
----------------------------------------------------------
function x310155_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
end

----------------------------------------------------------
--��Ϣ�¼�
----------------------------------------------------------
function x310155_Msg2toplayer( sceneId, selfId,type)
		
	if type == 0 then
		--�������񣬸��������ʾ
		Msg2Player(sceneId, selfId, "���μ���"..x310155_g_MissionName.."��", 0, 2)
	  	Msg2Player(sceneId, selfId, "���μ���"..x310155_g_MissionName.."��", 0, 3)
	elseif type == 1 then
		--�������񣬸��������ʾ
		Msg2Player(sceneId, selfId, "���˳���"..x310155_g_MissionName.."��", 0, 2)
		Msg2Player(sceneId, selfId, "���˳���"..x310155_g_MissionName.."��", 0, 3)
	elseif type == 2 then
		--�������û������ύ
	end
end

----------------------------------------------------------
--ɱ��������¼�
----------------------------------------------------------
function x310155_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

----------------------------------------------------------
--���������¼�
----------------------------------------------------------
function x310155_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------
--��ʱ���¼�
----------------------------------------------------------
function x310155_ProcTiming(sceneId, selfId, ScriptId, MissionId)
end

----------------------------------------------------------
--�뿪�����¼�
----------------------------------------------------------
function x310155_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

----------------------------------------------------------
--��Ʒ�ı��¼�
----------------------------------------------------------
function x310155_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

----------------------------------------------------------
--��NPC��������ӿ�
----------------------------------------------------------
function x310155_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
--	local bFind  = 0
--    for i ,item in x310155_g_NpcGUID do
--        if item.guid == npcGuid then
--            bFind = 1
--            break
--        end
--    end
--    
--    if bFind == 0 then
--        return
--    end
--    
--    --�����������²Ž�����Ӧ
--	if IsHaveQuest(sceneId,selfId, x310155_g_MissionId) > 0 then
--				
--		--û�������쳣���������ʾ������Ի���
--		local state = GetQuestStateNM(sceneId,selfId,npcId,x310155_g_MissionId)
--		AddQuestTextNM( sceneId, selfId, npcId, x310155_g_MissionId, state, 999 )
--	end
end

----------------------------------------------------------
--�������
----------------------------------------------------------
function x310155_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
end

----------------------------------------------------------
--����ʹ����Ʒ
----------------------------------------------------------
function x310155_PositionUseItem( sceneId, selfId, BagIndex, impactId )
end

----------------------------------------------------------
--������
----------------------------------------------------------
function x310155_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
end

----------------------------------------------------------
--������Ʒ
----------------------------------------------------------
function x310155_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
end

----------------------------------------------------------
--�ɼ�
----------------------------------------------------------
function x310155_OnProcOver( sceneId, selfId, targetId )
end

----------------------------------------------------------
--�ɼ�
----------------------------------------------------------
function x310155_OpenCheck( sceneId, selfId, targetId )
end

----------------------------------------------------------
--����ˢ��
----------------------------------------------------------
function x310155_ProcQuestLogRefresh( sceneId,selfId,MissionId)

	if sceneId ~= 3 and 
	   sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 68 and sceneId ~= 168 and sceneId ~= 268 and sceneId ~= 368 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and 
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and 
	   sceneId ~= 104 and sceneId ~= 204 and sceneId ~= 304 and sceneId ~= 404 and
	   sceneId ~= 105 and sceneId ~= 205 and sceneId ~= 305 and sceneId ~= 405 and
	   sceneId ~= 106 and sceneId ~= 206 and sceneId ~= 306 and sceneId ~= 406 and
	   sceneId ~= 107 and sceneId ~= 207 and sceneId ~= 307 and sceneId ~= 407 and
	   sceneId ~= 108 and sceneId ~= 208 and sceneId ~= 308 and sceneId ~= 408 and
	   sceneId ~= 109 and sceneId ~= 209 and sceneId ~= 309 and sceneId ~= 409 and
	   sceneId ~= 110 and sceneId ~= 210 and sceneId ~= 310 and sceneId ~= 410 and
	   sceneId ~= 111 and sceneId ~= 211 and sceneId ~= 311 and sceneId ~= 411 and
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 then 
	   return
	end

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x310155_g_MissionId );
	if bHaveMission <= 0 then
		return
	end
		
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
	local nFinished = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local nDay = GetQuestParam( sceneId, selfId, misIndex, 4 ) - 100
	local nCampFlag = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local nMatchCountry = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	--�������
	local nCurDayTime = GetDayOfYear()
	local str = ""
	local nCountryID = GetCurCountry( sceneId, selfId)
	if nCountryID == 0 then
		str ="@npc_123724"
	elseif nCountryID == 1 then
		str ="@npc_126021"
	elseif nCountryID == 2 then
		str ="@npc_129021"
	elseif nCountryID == 3 then
		str ="@npc_132021"
	end
	if nCurDayTime ~= nDay then
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--����
								"",      					--��������
								"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",			--����Ŀ��
								str,							--����NPC
								"", 	     				--������
								"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",				--��������
								""							--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		return		
	else
		
		--����Ƿ���������
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
		
			
			--����Ƿ�����콱
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--����
										"",      					--��������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ���������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս״̬��ɺ��10�����ڻ�21��00-21��20֮�䣩",			--����Ŀ��
										str,							--����NPC
										"", 	     				--������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ���������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս״̬��ɺ��10�����ڻ�21��00-21��20֮�䣩",				--��������
										""							--����С��ʾ
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return
			else
				--����Ѿ����������ǲ�û���ڣ���ֱ����ʾ�콱���
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--����
										"",      					--��������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ����������10������ǰ��#R���ҹ���Ա#W����ȡ������",			--����Ŀ��
										str,							--����NPC
										"", 	     				--������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ����������10������ǰ��#R���ҹ���Ա#W����ȡ������",				--��������
										""							--����С��ʾ
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return 
			end
			
		else
			--���ڵ��죬�����ڲ����콱ʱ�����
			local nFrom = 21*60 + 1
			local nTo   = 21*60 + 20
			local minTime = GetMinOfDay()
		
			if minTime > nTo then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--����
										"",      					--��������
										"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",			--����Ŀ��
										str,							--����NPC
										"", 	     				--������
										"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",				--��������
										""							--����С��ʾ
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return		
			end
		end
	end
	
	
	--��������¼��û�н�������ôȥ��GLServerȷ��
	if nFinished == 0 then
		
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
			
			--����Ƿ�����콱
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--����
										"",      					--��������
										"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",			--����Ŀ��
										str,							--����NPC
										"", 	     				--������
										"#Y�����ҡ�����ս#W�Ѿ����������ź���������콱ʱ�䣬�޷���ȡ���������콱ʱ��Ϊ����ս�����21��00-21��20��",				--��������
										""							--����С��ʾ
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return
			else
				--����Ѿ����������ǲ�û���ڣ���ֱ����ʾ�콱���
				BeginQuestEvent(sceneId)
				AddQuestLogCustomText( sceneId,
										"",							--����
										"",      					--��������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ����������10������ǰ��#R���ҹ���Ա#W����ȡ������",			--����Ŀ��
										str,							--����NPC
										"", 	     				--������
										"#Y�����ҡ�����ս#W�Ѿ���ǰ����������10������ǰ��#R���ҹ���Ա#W����ȡ������",				--��������
										""							--����С��ʾ
										)
				EndQuestEvent(sceneId)
				DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
				return 
			end
		end
		
		if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_CountryCamp",sceneId,selfId) ~= -1 then
	
			--GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_FINISHED, x310155_g_ScriptId,-1,"ProcQuestLogRefresh_Finished")
			
			
			--����ˢ������
			local nFinished = CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsBattleFinished",sceneId,selfId)
			if nFinished == 1 then
				nFinished = 0
			elseif nFinished == 0 then
				nFinished = 1
			end
			x310155_ProcQuestLogRefresh_Finished( sceneId, selfId,nFinished,x310155_g_MissionId )
			
		else
			--����Ѿ����������ǲ�û���ڣ���ֱ����ʾ�콱���
			BeginQuestEvent(sceneId)
			AddQuestLogCustomText( sceneId,
									"",							--����
									"",      					--��������
									"#Y�����ҡ�����ս#W�Ѿ����������ڱ���21��00-21��20����#R���ҹ���Ա#W����ȡ������",			--����Ŀ��
									str,							--����NPC
									"", 	     				--������
									"#Y�����ҡ�����ս#W�Ѿ����������ڱ���21��00-21��20����#R���ҹ���Ա#W����ȡ������",				--��������
									""							--����С��ʾ
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		end
				
	else
		
		--����Ѿ����������ǲ�û���ڣ���ֱ����ʾ�콱���
		BeginQuestEvent(sceneId)
		AddQuestLogCustomText( sceneId,
								"",							--����
								"",      					--��������
								"#Y�����ҡ�����ս#W�Ѿ����������ڱ���20��00-21��20����#R���ҹ���Ա#W����ȡ������",			--����Ŀ��
								str,							--����NPC
								"", 	     				--������
								"#Y�����ҡ�����ս#W�Ѿ����������ڱ���20��00-21��20����#R���ҹ���Ա#W����ȡ������",				--��������
								""							--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		
	end
end

----------------------------------------------------------
--ȡ��������ɱ��
----------------------------------------------------------
function x310155_ProcQuestLogRefresh_Finished( sceneId, selfId,MissionData,MissionId )

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x310155_g_MissionId );
	if bHaveMission <= 0 then
		return
	end

	local str = ""	
	local nCountryID = GetCurCountry( sceneId, selfId)
	if nCountryID == 0 then
		str ="@npc_123724"
	elseif nCountryID == 1 then
		str ="@npc_126021"
	elseif nCountryID == 2 then
		str ="@npc_129021"
	elseif nCountryID == 3 then
		str ="@npc_132021"
	end
	
	if MissionData ~= 1 then		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
		SetQuestParam( sceneId, selfId, misIndex, 3, 1 )
		--����Ѿ����������ǲ�û���ڣ���ֱ����ʾ�콱���
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--����
								"",      					--��������
								"\t�����ҡ�����ս�Ѿ����������ڱ���21��00-21��20���ڱ���#R���ҹ���Ա#W����ȡ������",			--����Ŀ��
								str,							--����NPC
								"", 	     				--������
								"�����ҡ�����ս�Ѿ����������ڱ���21��00-21��20���ڱ���#R���ҹ���Ա#W����ȡ������",				--��������
								""							--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId)
		
	else
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, x310155_g_MissionId )
		local nFinished = GetQuestParam( sceneId, selfId, misIndex, 3 )
		local nDay = GetQuestParam( sceneId, selfId, misIndex, 4 ) - 100
		local nCampFlag = GetQuestParam( sceneId, selfId, misIndex, 5 )
		local nMatchCountry = GetQuestParam( sceneId, selfId, misIndex, 6 )
		
		--ȡ�õжԹ���
		local strMatchCountry = nil
		if nMatchCountry == 0 then
			strMatchCountry = "¥��"
		elseif nMatchCountry == 1 then
			strMatchCountry = "��ɽ"
		elseif nMatchCountry == 2 then
			strMatchCountry = "����"
		elseif nMatchCountry == 3 then
			strMatchCountry = "�ػ�"
		end
		
		--����Ŀ�꣬����������������
		local strTarg,strDesc,strTips
		
		if nCampFlag == 0 then
			
			strTarg = format("\t���Ĺ��ҽ��촦��#G���ط�#W������Ҫ����#R%s����#W�������ߣ�����������#G���Ҿ���#W��",strMatchCountry)
			strDesc = "���˿���ͨ���߾��ص�ֱ�ӽ����ҹ��߾������ǻ�����ͨ���ܵ������ҹ��ŵ������������͵Ϯ��������߾��裬��ֹ����͵Ϯ�������ڹŵ������#R�����ټ�#W��������ѡ��#Y������ս�������ټ���#W��ť���Ա���#G40��#W���Ϲ�������ٻ����ù���������ս�ڼ��ܹ�����ʹ��ʹ��3�Ρ�"
			strTips = "#G�μ�����ս����ֻ����#R���˸����Ĺ������ǣ��Թ����ŵ��ͱ߾�#G���������ڻ�������ǰ��#R��������#G�����뽫�������#G�ſ��Խ��д��� #G�����Ҳ����ٴβμ�����ս���ͨ��#R�����ټ�#G���ܿ���Ѹ�ټ���������������ӭͷʹ�����������ܵı������������ڵĹ��Ҿ����������ø��ཱ����"
			
		else
			
			strTarg = format("\t���Ĺ��ҽ��촦�ڽ�����������Ҫ����#R%s����#W�ݻ����ǵ�#G���Ҿ���#W��",strMatchCountry)
			strDesc = "������ͨ���߾��߾��ص�ֱ�ӽ���й��߾�����Ҳ����ͨ�������Թ�һ��#R����ս����ʯ#W����й��ŵ�2����ͬ�ص����ǡ�������#R����ս����ʯ#W��������ѡ��#Y������ս�������ټ���#W��ť���Ա���#G40��#W���Ϲ�������ٻ����ù���������ս�ڼ��ܹ�����ʹ��ʹ��3�Ρ�"
			strTips = "#G�μ�����ս����ֻ����#R���˸����Ĺ������ǣ��Թ����ŵ��ͱ߾�#G���������ڻ�������ǰ��#R��������#G�����뽫�������#G�ſ��Խ��д��� #G�����Ҳ����ٴβμ�����ս����й��������кܶ������������ܿ����ǣ�������ν�������������Դ�#R�����Թ�����ս����ʯ#G����й����Ǵ�����ˡ��������ܵı������������ڵĹ��Ҿ����������ø��ཱ����"		
			
		end	
		
		--�������Ŀ����Ϊ�գ���ô�˳�
		if strTarg == nil then
			return
		end
		BeginQuestEvent(sceneId)
	    AddQuestLogCustomText( sceneId,
								"",							--����
								"",      					--��������
								strTarg,					--����Ŀ��
								str,						--����NPC
								"",		      				--������
								strDesc,					--��������
								strTips						--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x310155_g_MissionId);
		
	end
	
end

----------------------------------------------------------
--��������Ƿ�ɽ�
----------------------------------------------------------
function x310155_IsMissionCanAccept( sceneId, selfId )
	local nDate   = GetQuestData(sceneId,selfId,MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		return 0
	end

	return 1
end

----------------------------------------------------------
--���ý���������
----------------------------------------------------------
function x310155_SetMissionAcceptDate( sceneId, selfId )
	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3], nCurDay )
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_RONGYU[1], MD_COUNTRYBATTLELITE_RONGYU[2], MD_COUNTRYBATTLELITE_RONGYU[3], 0 )
end