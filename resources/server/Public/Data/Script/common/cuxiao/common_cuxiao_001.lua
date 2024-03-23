
x585001_g_ScriptId          		= 585001
x585001_g_BonusItem		       		= 12030425
x585001_g_CostFee								= 55000	--55������
x585001_g_MissionName       		= "�������ϴ����#R(55���ֽ�)"
x585001_g_NoMoney								= "�Բ��������ֽ��㣬�޷�����"
x585001_g_Readme								= "\n\t��#Y���ϴ����#W��������������#R12��8�տ�ʼ��12��14��#W������\n\t#R�ۼۣ�55���ֽ�#W��\n\t�ڹ����ڼ��ڣ������û���ֻ�ܹ���#Rһ��#W��\n\t���ϴ����Ϊ#R����Ʒ#W��ʹ���Ҽ�����󣬽����#G��ʯԭʯ4������̴ľ̿20��#W������õ��߾�Ϊ#R�󶨵���#W��"
x585001_g_DateLimit							= {
																		{y=2009,m=12,d=8},
																		{y=2009,m=12,d=9},
																		{y=2009,m=12,d=10},
																		{y=2009,m=12,d=11},
																		{y=2009,m=12,d=12},
																		{y=2009,m=12,d=13},
																		{y=2009,m=12,d=14},
																	}
x585001_g_GameId								= 2500
----------------------------------------------------------------------------------------------
--����Ƿ���ָ��������
----------------------------------------------------------------------------------------------																	
																																		
function x585001_CheckDateValid()
	
	local y,m,d = GetYearMonthDay()
	for i,item in x585001_g_DateLimit do
		
		if y == item.y and m == item.m and d == item.d then
			return 1
		end
		
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--ȡ�ý�����ǵڼ�����
----------------------------------------------------------------------------------------------
function x585001_GetCurrentWeek()
	
	--ȡ�ý��������
	local nCurrentTime = (GetCurrentTime()+8*3600)/86400 - 5  --�������
	local nWeek = floor(nCurrentTime / 7)		 --�������,��ȡ��
	
	return nWeek
end

----------------------------------------------------------------------------------------------
--ȡ�����һ��
----------------------------------------------------------------------------------------------
function x585001_GetLastWeek( sceneId,selfId)
	return GetQuestData(sceneId,selfId,MD_CUXIAOBAO_12_WEEK[1],MD_CUXIAOBAO_12_WEEK[2],MD_CUXIAOBAO_12_WEEK[3])	
end

----------------------------------------------------------------------------------------------
--�������һ��
----------------------------------------------------------------------------------------------
function x585001_SetLastWeek( sceneId,selfId)
	
	--��ǰ��
	local nCurWeek = x585001_GetCurrentWeek()
	
	--��鵱ǰ���Ƿ������һ��
	if x585001_GetLastWeek(sceneId,selfId ) ~= nCurWeek then
		
		--����������һ��,����������,�����������
		SetQuestData(sceneId,selfId,MD_CUXIAOBAO_12_WEEK[1],MD_CUXIAOBAO_12_WEEK[2],MD_CUXIAOBAO_12_WEEK[3],nCurWeek)
		
		--��յ�ǰ����
		for i,item in MD_CUXIAOBAO_12_WEEK_DAY do
			SetQuestData(sceneId,selfId,item[1],item[2],item[3],0)
		end
	end	
end

----------------------------------------------------------------------------------------------
--ȡ�����һ����Ľ������Ϣ
----------------------------------------------------------------------------------------------
function x585001_GetLastWeek_WD(sceneId,selfId)
	
	--�������һ��
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	return GetQuestData(sceneId,selfId,item[1],item[2],item[3])
end

----------------------------------------------------------------------------------------------
--�������һ����Ľ������Ϣ
----------------------------------------------------------------------------------------------
function x585001_SetLastWeek_WD(sceneId,selfId)
	
	--�������һ��
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	SetQuestData(sceneId,selfId,item[1],item[2],item[3],1)
end


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x585001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x585001_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x585001_g_ScriptId,x585001_g_MissionName,3,-1);
	
end
----------------------------------------------------------------------------------------------
--��Ǯ
----------------------------------------------------------------------------------------------
function x585001_PayMoney(sceneId,selfId,value,OP_Type)

	local nGoldMode = GetGoldMode( sceneId,selfId )
	
	if nGoldMode == 1 then		--�����ֽ����
		if CostMoney(sceneId, selfId, 2, value,OP_Type) == -1 then
			return 0
		end
	
	elseif nGoldMode == 0 then	--���Ƚ𿨽���
--		if CostMoney(sceneId, selfId, 3, value,OP_Type) == -1 then
			if CostMoney(sceneId, selfId, 2, value,OP_Type) == -1 then
				return 0
--			end
		end
	else
		return 0
	end	
	
	return 1

end

----------------------------------------------------------------------------------------------
--�����Ƿ��Ѿ�����
----------------------------------------------------------------------------------------------
function x585001_IsWeekGive( sceneId,selfId )
	
	--��ǰ��
	local nCurWeek = x585001_GetCurrentWeek()
	
	--��鵱ǰ���Ƿ������һ��
	if x585001_GetLastWeek(sceneId,selfId ) == nCurWeek then
		
		--��ѯ�Ƿ��Ѿ�����
		for i,item in MD_CUXIAOBAO_12_WEEK_DAY do
			if GetQuestData(sceneId,selfId,item[1],item[2],item[3]) == 1 then
				return 1
			end
		end
	end	
	
	--�������������û�д����
	return 0;
	
end

----------------------------------------------------------------------------------------------
--������
----------------------------------------------------------------------------------------------
function x585001_GiveBonus( sceneId,selfId )

	if x585001_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById( 1028 ) == 0 then
		return
	end


		BeginAddItem(sceneId)
			AddBindItem(sceneId,x585001_g_BonusItem,1)	--12030425 ���ϴ����
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			if x585001_PayMoney(sceneId,selfId,x585001_g_CostFee,308) == 1 then		--308Ϊsupersale�ֽ����ID
		
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("��ϲ�������������ߣ��۳���%d���ֽ�",x585001_g_CostFee/1000))
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddItemListToPlayer(sceneId,selfId)
				GamePlayScriptLog( sceneId, selfId, x585001_g_GameId)
				return 1			
			else
				BeginQuestEvent(sceneId,selfId)
					AddQuestText(sceneId,x585001_g_NoMoney)	--Ǯ����
				EndQuestEvent()
				DispatchQuestTips(sceneId,selfId)
			end		

		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end	


end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x585001_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

		if x585001_CheckDateValid() == 0 then
			return
		end

		--����Ѿ����
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x585001_g_MissionName)
		AddQuestText(sceneId,x585001_g_Readme);
		AddQuestItemBonus(sceneId, x585001_g_BonusItem, 1)
	  EndQuestEvent(sceneId)
		DispatchQuestInfoNM(sceneId, selfId, targetId, x585001_g_ScriptId, x585001_g_ScriptId);
		return	
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x585001_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585001_ProcAccept( sceneId, selfId )
	
	if x585001_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end
	
	--������Ƿ���Ч
	local nCurWeek = x585001_GetCurrentWeek()
	local nLastWeek = x585001_GetLastWeek(sceneId,selfId )
	
	if nCurWeek == nLastWeek then
		
		--�����ǰ�ܾ�������콱����
		
		if x585001_GetLastWeek_WD(sceneId,selfId ) == 1 or x585001_IsWeekGive( sceneId,selfId ) == 1 then
			
			--����Ѿ����
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ������˱���������޷����ж�ι���");			
		    EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return	
		else
			
			--���û�����,ִ���콱����
			if x585001_GiveBonus( sceneId,selfId ) == 1 then
				x585001_SetLastWeek_WD(sceneId,selfId)
			end
			
			return
		end
		
		
		
	elseif nCurWeek > nLastWeek then
		
		--�����ǰ�ܴ������콱����,��ʾ������
		--���û�����,ִ���콱����
		if x585001_GiveBonus( sceneId,selfId ) == 1 then
			x585001_SetLastWeek(sceneId,selfId)
			x585001_SetLastWeek_WD(sceneId,selfId)
		end
		
		return
		
	else
		return
	end
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585001_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585001_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x585001_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x585001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x585001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x585001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x585001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
