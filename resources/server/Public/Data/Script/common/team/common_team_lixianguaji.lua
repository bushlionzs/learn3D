--***********************
--Const
--***********************
x310401_g_ScriptId 				= 310401

--������ʾ�ı�
x310401_g_NoMoneyErrText		= 
"���Ľ�Ǯ���㣬�޷���ȡ"
x310401_g_GetExpLevelErrText	= 
"���ĵȼ�����#R%d��#o���޷���ȡ�õ��ε����߾���"
x310401_g_OfflineLevelErrText	= 
"���ĵȼ�����#R%d��#o���޷����ߴ���"
x310401_g_TimeMaxErrText		= 
"�����ۻ�ʱ���ѵ������ޣ�����ȡ���߾�����ٿ������ߴ���"
x310401_g_TimeZeroErrText		= 
"�������ߴ����ۻ�ʱ��Ϊ0��û�п���ȡ�����߾���"
x310401_g_ShowDemoText			= 
"\tֻ�в�����#G40#W������Ҳſ���ʹ�����ߴ�����\n\t��ʼ���ߴ������������ߴ���ʱ�佫�ۻ����㵽���´�����Ϊֹ��֮�����ɻ���һ���Ľ�Ǯ��ȡ��Ӧ�����߾��飬���ߴ���ʱ�������ۻ�7�졣\n"
x310401_g_CurTrainTimeText		= 
"\t����ǰ�����ߴ����ۻ�ʱ��Ϊ#G%d��%dСʱ%d��#W��\n"
x310401_g_OfflineAcceptText		= 
"\tѡ��ȷ�Ϻ������Դ���״̬���ߣ�����ʼ�ۻ����ߴ���ʱ�䣬�Ƿ�������ʼ���ߴ�����"
x310401_g_GetExpText			= 
"\t��ѡ����Ҫ��ȡ�����߾��鵵�Σ���ͬ�ĵ�����Ҫ���Ѳ�ͬ�����Ľ�Ǯ��\n"..
"\t#G�͵�#W����ͨ����Ч�ʣ���Ҫ����#G����#W��#G%d#W����ʹ��\n"..
"\t#G�е�#W��˫������Ч�ʣ���Ҫ����#G���#W��#G%d#W����ʹ��\n"..
"\t#G�ߵ�#W����������Ч�ʣ���Ҫ����#G���#W��#G%d#W����ʹ��"
x310401_g_GetExpAcceptText	= 
"#Y���ߴ���#W\n\t����ǰ�����ߴ����ۻ�ʱ��Ϊ#G%d��%dСʱ%d��#W��\n\t��ѡ�����ȡ���߾��鵵��Ϊ#G%s#W\n\t�����Ի�þ���ֵ#G%d��#W\n\t��Ҫ����#G%s#{_MONEY%d}#W\n\t�Ƿ�������ȡ��"
x310401_g_GetExpTipText			= 
"�����%d����"

--��������ߴ���ʱ�� 7 * 24 * 60
x310401_g_MaxTrainTime   		= 10080

--AddQuestNumText��֧
x310401_g_SwitchLogout 			= 1
x310401_g_SwitchGetExp 			= 2
x310401_g_SwitchLow 			= 3
x310401_g_SwitchMiddle 			= 4
x310401_g_SwitchHigh 			= 5

--�����������ѵ�Ǯ���� 0 ���� 1 ����
x310401_g_LowCostType	 		= 0
x310401_g_MiddleCostType		= 1
x310401_g_HighCostType	 		= 1

--��ȡ��ͬ�ȼ�����ʱ��Ӧ���˵ȼ�
x310401_g_LowRoleLevel	 		= 40
x310401_g_MiddleRoleLevel 		= 60
x310401_g_HighRoleLevel 		= 70

--***********************
--Variable
--***********************

--����������ѵĽ�Ǯ����õľ���
x310401_g_curGetExpTbl = {}
x310401_g_curNeedMoneyTbl = {}
--��ǰ��ѡ��Ľ���ҳ�� 0 �����ؽű���ʧ��1 ��ȡȷ�ϣ�2 ����ȷ��
x310401_g_curAcceptTypeTbl = {}
--�������͵���ת����
x310401_g_curCostTypeTbl = {}

function x310401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x310401_g_ScriptId, "���ߴ���", 3, x310401_g_SwitchLogout)
 	AddQuestNumText(sceneId, x310401_g_ScriptId, "��ȡ���ߴ�������", 3, x310401_g_SwitchGetExp)
end

function x310401_ProcEventEntry(sceneId, selfId, targetId, idScript, idExt)

	--��ֹ��ˢ��ʧ���ݣ�������ȫ�ֱ������浱ǰ����ʱ��
	local selfTrainTime = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3])

	if selfTrainTime < 0 or selfTrainTime > x310401_g_MaxTrainTime then
		WriteLog(2, format("OfflineTrain ProcEventEntry: GetQuestData Exception TimeValue(%d)", selfTrainTime))
		return
	end

	if idExt == x310401_g_SwitchLogout then
		--����ʱ��ﵽ���ޣ��޷����ߴ�����ʾ
		if selfTrainTime >= x310401_g_MaxTrainTime then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_TimeMaxErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
   		
		--��������ȷ�Ͻ���ҳ��������ת����
		x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] = 2

   		--��ʾ��������ȷ�Ͻ�����ʾ����
       	BeginQuestEvent(sceneId)
       	AddQuestText(sceneId, "#Y���ߴ���#W\n")
 		AddQuestText(sceneId, format(x310401_g_ShowDemoText .. x310401_g_CurTrainTimeText .. x310401_g_OfflineAcceptText, selfTrainTime / 60 / 24, 
 			mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60)))
   	 	EndQuestEvent()
   		DispatchQuestInfo(sceneId, selfId, targetId, x310401_g_ScriptId, -1)  
   		 		
	elseif idExt == x310401_g_SwitchGetExp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��ȡ���ߴ�������#W\n")
		AddQuestText(sceneId, format(x310401_g_CurTrainTimeText .. x310401_g_GetExpText, selfTrainTime / 60 / 24, 
			mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60), x310401_g_LowRoleLevel, x310401_g_MiddleRoleLevel, x310401_g_HighRoleLevel))
        AddQuestNumText(sceneId, x310401_g_ScriptId, "�͵���40�����ϣ�", 3, x310401_g_SwitchLow)
        AddQuestNumText(sceneId, x310401_g_ScriptId, "�е���60�����ϣ�", 3, x310401_g_SwitchMiddle)
        AddQuestNumText(sceneId, x310401_g_ScriptId, "�ߵ���70�����ϣ�", 3, x310401_g_SwitchHigh)
        EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId) 
         
   elseif idExt == x310401_g_SwitchLow or idExt == x310401_g_SwitchMiddle or idExt == x310401_g_SwitchHigh then	
		--�޴���ʱ��Ĵ�����ʾ
		if selfTrainTime == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_TimeZeroErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end

   		local selLevel = ""
   		local roleLevel = GetLevel(sceneId, selfId)
   		local errRoleLevel = 0
   		
   		--�Ե�ǰѡ�񵵴ν����������ж�
   		if idExt == x310401_g_SwitchLow then
   			if roleLevel < x310401_g_LowRoleLevel then
   				errRoleLevel = x310401_g_LowRoleLevel
   			end
   			selLevel = "�͵�"
   		elseif idExt == x310401_g_SwitchMiddle then
   			if roleLevel < x310401_g_MiddleRoleLevel then
   				errRoleLevel = x310401_g_MiddleRoleLevel
   			end
   			selLevel = "�е�"
   		elseif idExt == x310401_g_SwitchHigh then
   			if roleLevel < x310401_g_HighRoleLevel then
   				errRoleLevel = x310401_g_HighRoleLevel
   			end
   			selLevel = "�ߵ�"
		end

		if errRoleLevel ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, format(x310401_g_GetExpLevelErrText, errRoleLevel))
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
	
   		--���ѹ�ʽ������ѡ�񵵴μ�����ȼ��Ĳ�ͬ�����ȡ����Ȩ��---------------------------------
   		local numPower = 0
   		if idExt == x310401_g_SwitchLow then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_LowCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 313 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 135
   			else
   				numPower = 75
   			end
   		elseif idExt == x310401_g_SwitchMiddle then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_MiddleCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 9 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 270
   			else
   				numPower = 150
   			end
   		elseif idExt == x310401_g_SwitchHigh then
   			x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] = x310401_g_HighCostType
   			x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] = 17 * selfTrainTime
   			
   			if roleLevel >= x310401_g_HighRoleLevel then
   				numPower = 405
   			else
   				numPower = 225
   			end
		end
   		
   		x310401_g_curGetExpTbl[GetName(sceneId, selfId)] = roleLevel * numPower * selfTrainTime
		-----------------------------------------------------------------------------------------
		
		--���û�ȡ�������ҳ��������ת����
		x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] = 1
		
		-- ���ݵ�ǰѡ�񵵴�����Ӧ�Ļ�������������ʾ�Ļ���������������
   		local curCostString = ""
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] == 1 then
			curCostString = "���"
		else
			curCostString = "����"
		end

   		--��ʾ���Ļ�ȡ���������ʾ����
       	BeginQuestEvent(sceneId)
    	AddQuestText(sceneId, format(x310401_g_GetExpAcceptText, selfTrainTime / 60 / 24, mod(selfTrainTime / 60, 24), mod(selfTrainTime, 60), 
    		selLevel, x310401_g_curGetExpTbl[GetName(sceneId, selfId)], curCostString, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)]))
   	 	EndQuestEvent()
   		DispatchQuestInfo(sceneId, selfId, targetId, x310401_g_ScriptId, -1)
    end
end

function x310401_ProcAcceptCheck(sceneId, selfId, targetId)

	--������ת������ȷ���Ǿ����ȡȷ�ϻ�����ȷ��ҳ�棬���������ؽű�����������������Ӱ�죨������ν��ܣ�
	if 	x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] == 1 then
	
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] ~= 0 and x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] ~= 1 then
			return
		end

		--���ݻ��������ó�������󶨵����ֻ�����Ŀ
		local freeMoney = GetMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2)
		local bindMoney = GetMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1)
	
		--��Ӧ���ѽ����
		if freeMoney + bindMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x310401_g_NoMoneyErrText)
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end
		
		local payType = 0 --0 �󶨿� 1 �ֽ�
		if x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] == 0 then
			payType = GetSillerMode(sceneId, selfId)
		else
			payType = GetGoldMode(sceneId, selfId)
		end
		
	    if payType == 1 then
	    	--����ֽ𲻹�����ſ۰󶨿���Ǯ
	    	if freeMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, freeMoney, 309)
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] - freeMoney, 309)
	    	else
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], 309)
	    	end
	    else
	    	--����󶨿���������ſ��ֽ��Ǯ
	    	if bindMoney < x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] then
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, bindMoney, 309)
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)] - bindMoney, 309)
	    	else
	    		CostMoney(sceneId, selfId, x310401_g_curCostTypeTbl[GetName(sceneId, selfId)] * 2 + 1, x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], 309)
	    	end
	    end
		
		--�Ӿ��鲢������ߴ���ʱ��
	    AddExp(sceneId, selfId, x310401_g_curGetExpTbl[GetName(sceneId, selfId)])
	    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3], 0)
	    
	    --�ڿͻ������·���ʾ�����ȡ��ʾ
	    Msg2Player(sceneId, selfId, format(x310401_g_GetExpTipText, x310401_g_curGetExpTbl[GetName(sceneId, selfId)]), 8 ,2)
	    --д������־
	    WriteLog(1, format("OfflineTrain ProcAcceptCheck GetExp OK: Name(%s) GUID(%d) NeedMoney(%d) GetExp(%d)", 
	    	GetName(sceneId, selfId), GetGUID(sceneId, selfId), x310401_g_curNeedMoneyTbl[GetName(sceneId, selfId)], x310401_g_curGetExpTbl[GetName(sceneId, selfId)]))		    	
	
	elseif 	x310401_g_curAcceptTypeTbl[GetName(sceneId, selfId)] == 2 then
		
		--���߹һ���Ӧ��ɫ�ȼ����
		if GetLevel(sceneId, selfId) < x310401_g_LowRoleLevel then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, format(x310401_g_OfflineLevelErrText, x310401_g_LowRoleLevel))
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			return
		end

		--�������ߴ�����־����ʾ����
    	SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3], 1)
   	 	KickPlayer(sceneId, selfId, 1)

    	--д������־
	    WriteLog(1, format("OfflineTrain ProcEventEntry Offline OK: Name(%s) GUID(%d)", GetName(sceneId, selfId), GetGUID(sceneId, selfId)))
	end
end

function x310401_ProcMapPlayerNewConnectEnter(sceneId, selfId)
	
	local lastLogoutTime = GetLastLogoutTime(sceneId, selfId)

	--�Լܷ������ϴ�����ʱ����Ҫ�������н��в���
	--lastLogoutTime = GetCurrentTime() - 4444

	if lastLogoutTime <= 0 then
		return
	end
	
	--ȡ���Լ�֮ǰ�����ߴ���ʱ��ͱ�־
	local selfTrainTime = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3])
	local selfTrainFlag = GetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3])

	if selfTrainTime < 0 or selfTrainTime > x310401_g_MaxTrainTime or (selfTrainFlag ~= 0 and selfTrainFlag ~= 1) then
		WriteLog(2, format("OfflineTrain ProcMapPlayerNewConnectEnter: GetQuestData Exception TimeValue(%d) FlagValue(%d)", selfTrainTime, selfTrainFlag))
		return
	end

	--���ϴ������ߴ�����־�������ߴ���ʱ�����
	if selfTrainFlag == 1 then
		--ȡ�ñ������ߺ�Ĵ���ʱ�䣬��λ��
		local thisTrainTime = GetCurrentTime() - lastLogoutTime
		
		--ʱ���ݴ��ж�����ֹ����ʱ��ǰ�޸����ڵ��µ� thisTrainTime Ϊ�������
		if thisTrainTime > 0 then
   			selfTrainTime = selfTrainTime + thisTrainTime / 60
			
		    if selfTrainTime > x310401_g_MaxTrainTime then
		    	selfTrainTime = x310401_g_MaxTrainTime
		    end
		
			--�����Լ������ߴ���ʱ��
		    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_MIN[1], MD_OFFLINE_TRAIN_MIN[2], MD_OFFLINE_TRAIN_MIN[3], selfTrainTime)
    	else
			WriteLog(2, format("OfflineTrain ProcMapPlayerNewConnectEnter: get this traintime error for modify system time"))    		
    	end
    	
    	--������ߴ�����־
	    SetQuestData(sceneId, selfId, MD_OFFLINE_TRAIN_FLAG[1], MD_OFFLINE_TRAIN_FLAG[2], MD_OFFLINE_TRAIN_FLAG[3], 0)
	end
end
