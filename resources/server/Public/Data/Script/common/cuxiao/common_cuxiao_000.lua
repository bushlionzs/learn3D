
x585000_g_ScriptId          		= 585000
x585000_g_BonusItem		       		= 12030424
x585000_g_CostFee								= 50000	--50������
x585000_g_MissionName       		= "������Ǵ����#R(50���ֽ�)"
x585000_g_NoMoney								= "�Բ��������ֽ��㣬�޷�����"
x585000_g_Readme								= "\n\t��#Y���Ǵ����#W��������������#R12��1�տ�ʼ��12��7��#W������\n\t#R�ۼۣ�50���ֽ�#W��\n\t�ڹ����ڼ��ڣ������û���ֻ�ܹ���#Rһ��#W��\n\t���Ǵ����Ϊ#R����Ʒ#W��ʹ���Ҽ�����󣬽����#G������ʯ��2����ԭ����ʯ��1������ˮ��50��#W������õ��߾�Ϊ#R�󶨵���#W��"
x585000_g_DateLimit							= {
																		{y=2009,m=12,d=1},
																		{y=2009,m=12,d=2},
																		{y=2009,m=12,d=3},
																		{y=2009,m=12,d=4},
																		{y=2009,m=12,d=5},
																		{y=2009,m=12,d=6},
																		{y=2009,m=12,d=7},
																	}
x585000_g_GameId								= 2500
----------------------------------------------------------------------------------------------
--����Ƿ���ָ��������
----------------------------------------------------------------------------------------------																	
																																		
function x585000_CheckDateValid()
	
	local y,m,d = GetYearMonthDay()
	for i,item in x585000_g_DateLimit do
		
		if y == item.y and m == item.m and d == item.d then
			return 1
		end
		
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--ȡ�ý�����ǵڼ�����
----------------------------------------------------------------------------------------------
function x585000_GetCurrentWeek()
	
	--ȡ�ý��������
	local nCurrentTime = (GetCurrentTime()+8*3600)/86400 - 5  --�������
	local nWeek = floor(nCurrentTime / 7)		 --�������,��ȡ��
	
	return nWeek
end

----------------------------------------------------------------------------------------------
--ȡ�����һ��
----------------------------------------------------------------------------------------------
function x585000_GetLastWeek( sceneId,selfId)
	return GetQuestData(sceneId,selfId,MD_CUXIAOBAO_12_WEEK[1],MD_CUXIAOBAO_12_WEEK[2],MD_CUXIAOBAO_12_WEEK[3])	
end

----------------------------------------------------------------------------------------------
--�������һ��
----------------------------------------------------------------------------------------------
function x585000_SetLastWeek( sceneId,selfId)
	
	--��ǰ��
	local nCurWeek = x585000_GetCurrentWeek()
	
	--��鵱ǰ���Ƿ������һ��
	if x585000_GetLastWeek(sceneId,selfId ) ~= nCurWeek then
		
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
function x585000_GetLastWeek_WD(sceneId,selfId)
	
	--�������һ��
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	return GetQuestData(sceneId,selfId,item[1],item[2],item[3])
end

----------------------------------------------------------------------------------------------
--�������һ����Ľ������Ϣ
----------------------------------------------------------------------------------------------
function x585000_SetLastWeek_WD(sceneId,selfId)
	
	--�������һ��
	local nWeek = GetWeek()+1
	local item = MD_CUXIAOBAO_12_WEEK_DAY[nWeek]
	SetQuestData(sceneId,selfId,item[1],item[2],item[3],1)
end


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x585000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x585000_g_ScriptId,x585000_g_MissionName,3,-1);
	
end
----------------------------------------------------------------------------------------------
--��Ǯ
----------------------------------------------------------------------------------------------
function x585000_PayMoney(sceneId,selfId,value,OP_Type)

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
function x585000_IsWeekGive( sceneId,selfId )
	
	--��ǰ��
	local nCurWeek = x585000_GetCurrentWeek()
	
	--��鵱ǰ���Ƿ������һ��
	if x585000_GetLastWeek(sceneId,selfId ) == nCurWeek then
		
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
function x585000_GiveBonus( sceneId,selfId )

	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById( 1028 ) == 0 then
		return
	end


		BeginAddItem(sceneId)
			AddBindItem(sceneId,x585000_g_BonusItem,1)	--12030424 ���Ǵ����
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			if x585000_PayMoney(sceneId,selfId,x585000_g_CostFee,308) == 1 then		--308Ϊsupersale�ֽ����ID
		
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("��ϲ�������������ߣ��۳���%d���ֽ�",x585000_g_CostFee/1000))
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddItemListToPlayer(sceneId,selfId)
				GamePlayScriptLog( sceneId, selfId, x585000_g_GameId)
				return 1			
			else
				BeginQuestEvent(sceneId,selfId)
					AddQuestText(sceneId,x585000_g_NoMoney)	--Ǯ����
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
function x585000_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

		if x585000_CheckDateValid() == 0 then
			return
		end

		--����Ѿ����
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x585000_g_MissionName)
		AddQuestText(sceneId,x585000_g_Readme);
		AddQuestItemBonus(sceneId, x585000_g_BonusItem, 1)
	  EndQuestEvent(sceneId)
		DispatchQuestInfoNM(sceneId, selfId, targetId, x585000_g_ScriptId, x585000_g_ScriptId);
		return	
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x585000_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585000_ProcAccept( sceneId, selfId )
	
	if x585000_CheckDateValid() == 0 then
		return
	end
	
	if GetGameOpenById(1028 ) == 0 then
		return
	end
	
	--������Ƿ���Ч
	local nCurWeek = x585000_GetCurrentWeek()
	local nLastWeek = x585000_GetLastWeek(sceneId,selfId )
	local nWeekDay = GetWeek() + 1
	
	if nCurWeek == nLastWeek then
		
		--�����ǰ�ܾ�������콱����
		
		if x585000_GetLastWeek_WD(sceneId,selfId ) == 1 or x585000_IsWeekGive( sceneId,selfId ) == 1 then
			
			--����Ѿ����
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ������˱���������޷����ж�ι���");			
		    EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return	
		else
			--���û�����,ִ���콱����
			if x585000_GiveBonus( sceneId,selfId ) == 1 then
				x585000_SetLastWeek_WD(sceneId,selfId)
			end
			
			return
		end
		
		
		
	elseif nCurWeek > nLastWeek then
		
		--�����ǰ�ܴ������콱����,��ʾ������
		--���û�����,ִ���콱����
		if x585000_GiveBonus( sceneId,selfId ) == 1 then
			x585000_SetLastWeek(sceneId,selfId)
			x585000_SetLastWeek_WD(sceneId,selfId)
		end
		
		return
		
	else
		return
	end
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585000_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x585000_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x585000_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x585000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x585000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x585000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x585000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
