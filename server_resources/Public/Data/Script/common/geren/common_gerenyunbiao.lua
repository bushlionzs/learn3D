--MisDescBegin
x300622_g_ScriptId 	  = 300622
x300622_g_MissionKind 				= 	1                       --��������
x300622_g_Mis_Count   = 1--ÿ������Ĵ���
x300622_g_LevelLess					= 	50 
--��������
x300622_g_MissionName = "�����ˡ��ٸ�Ѻ��"
-- NPCĬ�϶Ի�
x300622_g_NPCDialog = "\t���ǹٸ������Ŀ�����������������Ļƽ����������ء�������������̫�ң��ж���������ͨ�������������ǵĻƽ��ҿ���̨��������ܷ���������ͻƽ�"
-- ������Ϣ
x300622_g_MissionInfo = "\t������ͨ��������������������#G10������#W�Ϳ�����ȡһ��#G��#W������������ȫ���͵�ָ���ص㣬ϵͳ���������#G��������#W��\n"
-- ������ʾ
x300622_g_MissionHelp = "\t#G����;��������뿪����Զ��������ʶ��Σ�ն�ֹͣǰ����\n\t#G������ܵ�Ϯ������������������ʧ�ܣ�ͬʱѺ�𽫱����ߡ�\n\t#G�����뿪��һ��ʱ�����ߣ�������ʧ����ʱ����ʧ�ܡ�"
-- ����Ŀ��
x300622_g_MissionTarget = "  ��������@npc_129325"
x300622_g_NPCName = "@npc_129325"
x300622_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300622_g_MissionCompleted = "���Ѿ����ٸ�������������ȫ���͵����ˣ������¹ٸ������Ľ�����"
--MisDescEnd

-- �����ȡ����ϵ��1
x300622_g_coef1 = 1000
-- �����ȡ����ϵ��2
x300622_g_coef2 = 0.3
-- �����ȡ����ϵ��3
x300622_g_coef3 = 20
x300622_g_coef4 =1 --��ͨ���鱶��
x300622_g_coef5 = 2 -- ���˾��鱶��
-- ���ռ��㹫ʽΪ x = x300622_g_coef1 * x300622_g_coef2 * x300622_g_coef3 * ��ҵȼ���

-- Ѻ��
x300622_g_yajin = 10000
x300622_g_BusScriptId = 300623
-- ����ID
x300622_g_MissionID = 7010;
-- ����������Ҫ����С�ȼ�
x300622_g_MinLevel = 50
-- ����������Ҫ�����ȼ�
x300622_g_MaxLevel = 100
x300622_g_BusIndex = 3


function x300622_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
  	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then		-- ���û���������
		
		local playerLevel = GetLevel( sceneId, selfId);
		if( playerLevel >= x300622_g_MinLevel and playerLevel <= x300622_g_MaxLevel) then
			local state = GetQuestStateNM( sceneId, selfId, targetId, x300622_g_MissionID);
			AddQuestText(sceneId, x300622_g_NPCDialog );
			AddQuestNumText( sceneId, x300622_g_MissionID, x300622_g_MissionName, 5);
		end
		
	end

	return 0
end


--��ʾ������Ϣ
function x300622_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300622_g_MissionName);
		AddQuestText(sceneId, x300622_g_MissionInfo)

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x300622_g_MissionTarget)
		--��ʾ��Ϣ
		if x300622_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y������ʾ��")
			AddQuestText(sceneId, x300622_g_MissionHelp )
		end
		
		--������Ϣ
		
		--�����ҵ�ǰ�ȼ�
		local playerLevel = GetLevel( sceneId, selfId);
		--��ȡ����
		local experience = x300622_g_coef1 * x300622_g_coef2 * playerLevel * x300622_g_coef3;
		AddQuestExpBonus( sceneId, experience);
		--��ȡ��Ǯ
		--AddQuestMoneyBonus2( sceneId, x300622_g_yajin);
	EndQuestEvent(sceneId);
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300622_g_ScriptId, x300622_g_MissionID);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300622_DispatchCompletedInfo( sceneId, selfId, targetId )
	
	BeginQuestEvent(sceneId)

	--���������Ϣ
	AddQuestText(sceneId,"#Y"..x300622_g_MissionName)
	AddQuestText(sceneId,x300622_g_MissionCompleted)
	AddQuestText(sceneId," ")

	--1������
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = ceil ( (1000 * 0.3 * level * 20 ) )
	if ExpBonus> 0 then
		AddQuestExpBonus(sceneId, ExpBonus )
	end
			
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300622_g_ScriptId , x300622_g_MissionID);

end

--�������ť������������ִ�д˽ű�
function x300622_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ���û���������
		x300622_DispatchCompletedInfo( sceneId, selfId, targetId) 	--���������ʾ
	else
		local BusID = IsBusMember(sceneId, selfId);
		if(BusID ~= 1) then
			if nExtIdx ~= x300622_g_ScriptId then
				x300622_DispatchMissionInfo( sceneId, selfId, targetId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�д�����")
				EndQuestEvent()
				DispatchQuestEventList(sceneId,selfId,targetId);
			end
		else
				local strText = "���Ѵ��ڻ���״̬���޷���ȡ�µĻ�������"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				local Readme = "���Ѵ��ڻ���״̬���޷���ȡ�µĻ�������"
				Msg2Player(sceneId,selfId,Readme,8,2)
		end			
	end
		  
end


--**********************************
--����
--**********************************
function x300622_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ɽ�������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if x300622_GetDayCount(sceneId, selfId) >= x300622_g_Mis_Count then
		local Readme = "�ܱ�Ǹ����������������������������������ɣ�" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ӹ���״̬�²����Խӻ�������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "��Ӹ���״̬�²����Խӻ�������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
		
	local CurrMoney = GetMoney(sceneId , selfId ,0)
	if CurrMoney < x300622_g_yajin then
		local Readme = "�ܱ�Ǹ���������е���������֧��Ѻ���޷���ȡ����" 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end			
	CallScriptFunction( x300622_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionId,x300622_g_BusIndex)
	
	
	
end


--**********************************
--����
--**********************************
function x300622_ProcAccept( sceneId, selfId )
	
end

--�������
--����1����ɹ���0��������ʧ��
function x300622_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	--�ڳ��Ƿ�����Ч����
	local valid = IsValidMyselfBus(sceneId, selfId,MissionId)

	if valid == 0 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����͵�������̫Զ�ˣ��޷��ύ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����͵�������̫Զ�ˣ��޷��ύ����"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
   
	--������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
		local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
		if ret > 0 then -- ����������
		local ret = DelQuestNM( sceneId, selfId, MissionId ) 
		if ret == 1 then -- ����ɹ����

			--������д��־
			GamePlayScriptLog(sceneId,selfId,72)

			x300622_SetDayCount(sceneId, selfId)

			local ret = CountryIsFortuneTime(sceneId,selfId,0)
			if ret == 1  then   -- �����ڼ�
				local level = GetLevel(sceneId,selfId)
				local exp = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef5 ))
				AddExp(sceneId, selfId,exp)	
				local level = GetLevel(sceneId,selfId)
				local exp1 = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef4 ))
				local Readme = "����������񣺡����ˡ��ٸ�Ѻ��#r���#R����"..exp1.."��#o�Ľ���#r���˶�����#R����"..exp1.."��#o�Ľ���"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "����������񣺡����ˡ��ٸ�Ѻ��");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "���#R����"..exp1.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "���˶�����#R����"..exp1.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,Readme,8,2)
			
			else
				local level = GetLevel(sceneId,selfId)
				local exp = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3*x300622_g_coef4 ))
				AddExp(sceneId, selfId,exp)	
				local Readme =  "����������񣺡����ˡ��ٸ�Ѻ��#r���#R����"..exp.."��#o�Ľ���"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "����������񣺡����ˡ��ٸ�Ѻ��");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "���#R����"..exp.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,Readme,8,2)
			end         
			
			local BusID  =  GetBusId(sceneId, selfId)
		  	if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
		  	    
				if GetBusQuestID(sceneId, BusID) == MissionId then
					--���BUS������
					DeleteBus(sceneId, BusID,1)
				end
		  	end     
		end
	end

	return 0
	
end


--********************************************************************
--����
--********************************************************************
function x300622_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end

	if IsBusMember(sceneId, selfId) == 1 then
		local BusID  =  GetBusId(sceneId, selfId)
		if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
			--���BUS������
			if GetBusQuestID(sceneId, BusID) == MissionId then
				DeleteBus(sceneId, BusID,1)
			end
		else
			local Readme = "�ܱ�Ǹ���������Ļ���Ŀ����ͬһ�������ܷ������������ҵ����Ļ���Ŀ����ѡ�������"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���ڲ��ܷ�������");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			return
		end				
	end

	DelQuestNM( sceneId, selfId, MissionId)
	local Readme = "�����������񣺡����ˡ��ٸ�Ѻ��"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
    EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	x300622_SetDayCount(sceneId, selfId)
  	
end


function x300622_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	if npcGuid == submitGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		AddQuestTextNM( sceneId, selfId, -1, MissionId, 7, x300622_g_ScriptId ) -- ��ʾ������Ϣ
	end
end



---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300622_QuestLogRefresh( sceneId, selfId, MissionId)

		local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = ceil (( x300622_g_coef1 * x300622_g_coef2 * level * x300622_g_coef3 ))
		    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,ExpBonus);
			end
		    AddQuestLogCustomText( sceneId,
									"",							-- ����
									x300622_g_MissionName,      -- ��������
									x300622_g_MissionTarget,	--����Ŀ��
									x300622_g_NPCName,			--����NPC
									x300622_g_MissionHelp,      --������
									x300622_g_MissionInfo,		--��������
									""							--����С��ʾ
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		end
end

function x300622_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300622_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x300622_GetDayCount(sceneId, selfId)

	if x300622_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300622_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3])
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], daycount+1)
	end
end

