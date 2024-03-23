--########################################
--##�Թ������ܻ��ű����� by rj 2010-9-6 ##
--########################################

--***********************
--Const
--***********************
x562000_g_ScriptId 					= 562000          				--�ű� ID
x562000_g_MissionId 				= 9502            				--���� ID
x562000_g_CurScriptCountry			= 0								--��ǰ�ű�������� 0 - 3
x562000_g_SubmitNpcGUID				= 101650						--�ύ���� NPC���� Obj_List.tab ����Ҫ���ã��� Obj_Quest.tab �������������
x562000_g_MissionItem 				= 13040040						--��������������
x562000_g_MissionItemNum 			= 60								--��������ռ�����		
x562000_g_MissionItemDropRate 		= 100                            --������ߵ����漴��		
x562000_g_MissionItemDropMaxNum 	= 1								--������ߵ����������		
x562000_g_MissionRingNum 			= 10								--������������ 5 λ MD����� 31 ��
x562000_g_AcceptMinLevel 			= 35							--��ȡ������С�ȼ���ע�⣺Obj_List.tab �е���С����������С������ֻ�ɫ̾�ŵ�ȴ�ɽӵ����
x562000_g_AcceptMaxLevel 			= 49							--��ȡ�������ȼ���ע�⣺ͬ��
x562000_g_AcceptLevelDataIdx		= 1								--����ʱ�Ľ�ɫ�ȼ�����������������

x562000_g_AllBonusItemList 			= 								--����һ�ֽ�����Ʒ�б�����û��������ü���Χ����ʾ��������Ӷ����ᴦ��
{{id = 11050001, num = 40, minlevel = 35, maxlevel = 39}, {id = 11050002, num = 40, minlevel = 40, maxlevel = 44}, {id = 11050002, num = 40, minlevel = 45, maxlevel = 49}}

x562000_g_KillMonsterList 			= 								--�û��ȼ���ɱ������б���Ҽ��𲻹����ﲻ����е���
{{name = "����֮��", sceneid = 90066, typeid = 6901, minlevel = 35, maxlevel = 39},
{name = "����֮��", sceneid = 90067, typeid = 6902, minlevel = 40, maxlevel = 44}, 
{name = "����֮��", sceneid = 90068, typeid = 6903, minlevel = 45, maxlevel = 49}}

x562000_g_MissionName				= 								--��������
"�����ˡ��Թ�����"
x562000_g_AcceptDesc				= 								--��������(npc)
"\t�����Թ��еĸ��ֹ���������ж��꣬������ʿ��ͼ�������ǣ�������������ڴˡ�\n\t���һλ���ε����ߵ㲥��������֮���������ռ���������׹Ǿ۶���֮���÷ٹ�֮�̳���Թ����������̼ȱС�\n\t��Ը������ռ����׹ǵļ��������"		
x562000_g_CompleteDesc	 			= 								--�����������(npc)
"\t��˵������������պ͵�ʶ��ʵ���ף���������ھ��ز������°�!"	
x562000_g_UnCompleteDesc			= 								--δ�����������(npc)
"\t�㻹û���ռ��㹻�����׹ǣ�����ʲô���Ѿ�ֱ�Ӹ����ң��Ҳ���Ϊ����ġ�"	
x562000_g_MissionFmtName			= x562000_g_MissionName	.. 		--�����ʽ������(player & npc)
"(%d/%d)"
x562000_g_TargetFmtDesc	 			= 								--����Ŀ��(player)
"����@npc_%d�ռ�@item_%d#W(%d/%d)"	
x562000_g_BookDesc	 				= 								--������(player)
"����@npc_%d�ռ�@item_%d#W(%d/%d)"
x562000_g_TipDesc	 				= 								--������ʾ����(player)
"\t���������ɣ����������Ҳ��������������ٶȡ�"
x562000_g_LevelErrTip				= 								--���𲻶��޷�����������ʾ���㿪NPC���������ı߽籣����
"\���ļ����ʺϽ��ܴ�����!"	
x562000_g_TodayErrTip				= 								--�����Ѿ�������л�����������ʾ
"�����Ѿ��޷���ȡ���������������ɣ�"	
x562000_g_MisFullErrTip				= 								--������������������ʧ����ʾ
"�����������������ʧ��"	
x562000_g_BagFullErrTip1			= 								--���������Ʒ��������ʾ
"��Ʒ���������޷��õ�������Ʒ��"	
x562000_g_BagFullErrTip2			= 								--��ӽ�����Ʒ��������ʾ
"��Ʒ���������޷��õ�������Ʒ�������ύʧ�ܣ�"	
x562000_g_GiveupErrTip         		= 								--����������ʾ
"������������" .. x562000_g_MissionName
x562000_g_AcceptOkTip         		= 								--��������ɹ���ʾ
"������������" .. x562000_g_MissionName
x562000_g_FinishTip         		= 								--��������ɹ���ʾ
"�����������" .. x562000_g_MissionName
x562000_g_GetExpFmtTip         		= 								--��������þ�����ʾ
"��ɱ���������%d����"
---------------------------------------------------------------------------------------------------------------------------------

--**********************************
--��ý���ʱ�ȼ���Ϊ�Ƿ�ֵ������Ӧ
--**********************************
function x562000_GetAcceptLevel(sceneId, selfId)

	acceptLevel = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), x562000_g_AcceptLevelDataIdx)
	
	--Ϊ�滻�ű����д�����û�н���λ���ݵ������Ӧֵ
	if acceptLevel == 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x562000_g_MissionId)
		selfLevel = GetLevel(sceneId, selfId)

		if selfLevel > x562000_g_AcceptMaxLevel then
			SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, x562000_g_AcceptMaxLevel)
			return x562000_g_AcceptMaxLevel
		else
			SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, selfLevel)
			return selfLevel			
		end
	end
	
	return acceptLevel
end

--**********************************
--��õ�ǰ������Ϊ�Ƿ�ֵ������Ӧ
--**********************************
function x562000_GetCurRing(sceneId, selfId)

	local curRingIdx = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3])
	
	--�Ƿ�ֵ�ж���������ӦΪ��һ�����������
	if curRingIdx < 0 then
		WriteLog(2, format("minggongchue GGetCurRing: GetQuestData curRingIdx(%d)", curRingIdx))
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], 0)
		return 0
	end
	
	--�������С�ܻ������û���ǰ�������ܻ������������õ�ǰ����Ϊ�µ������
	if curRingIdx >= x562000_g_MissionRingNum then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], x562000_g_MissionRingNum - 1)
		return x562000_g_MissionRingNum - 1
	end
	
	return curRingIdx
end

--**********************************
--������㹫ʽ�����������ɫ����
--**********************************
function x562000_GetThisTimeExp(sceneId, selfId, selfLevel)
	return selfLevel * 220 * (x562000_GetCurRing(sceneId, selfId) + 11) + 46200
end

--**********************************
--���ܼ���������ʱ��ʾ�� NPC �Ի�����
--**********************************
function x562000_ShowNpcContext(sceneId, selfId, npcId, showMainText, isAccept)
	
	local curRingIdx = x562000_GetCurRing(sceneId, selfId)
	
	BeginQuestEvent(sceneId)

	--������Ϣ
	AddQuestText(sceneId, "#Y" .. x562000_g_MissionName)
	AddQuestText(sceneId, showMainText)
	
	--���ݽ��ܼ�������ͬȡ�õ���ҵȼ���ʽ�ǲ�ͬ�ģ�����Ҫ���µģ�����ǰ��ʾʱ��û�м�¼ԭʼ�ȼ�������������Ҫԭʼ��
	local selfLevel = 0
	if isAccept == 1 then
		selfLevel = GetLevel(sceneId, selfId)
	else
		selfLevel = x562000_GetAcceptLevel(sceneId, selfId)
	end
	
	--��ʾ���齱��
	local getExp = x562000_GetThisTimeExp(sceneId, selfId, selfLevel, curRingIdx)
	if getExp > 0 then
		AddQuestExpBonus(sceneId, getExp)
	end

	--��ʾ���һ��������Ʒ
	if curRingIdx + 1 == x562000_g_MissionRingNum then
		for i, item in x562000_g_AllBonusItemList do
		   	if selfLevel >= item.minlevel and selfLevel <= item.maxlevel then
		   		AddQuestItemBonus(sceneId, item.id, item.num)
		   	end
	    end
	end

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, npcId, x562000_g_ScriptId, x562000_g_MissionId)
end

--**********************************
--������־ˢ��
--**********************************
function x562000_QuestLogRefresh(sceneId, humanId)

    if IsHaveQuest(sceneId, humanId, x562000_g_MissionId) == 0 then
        return
    end

	local curRingIdx = x562000_GetCurRing(sceneId, humanId)
	
	BeginQuestEvent(sceneId)
   
   	local rawLevel = x562000_GetAcceptLevel(sceneId, humanId)
	local getExp = x562000_GetThisTimeExp(sceneId, humanId, rawLevel, curRingIdx)

	--��ʾ���齱��
	if getExp > 0 then
		AddQuestExpBonus(sceneId, getExp)
	end
	
	--��ʾ���һ��������Ʒ
	if curRingIdx + 1 == x562000_g_MissionRingNum then
		for i, item in x562000_g_AllBonusItemList do
		   	if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
		   		AddQuestItemBonus(sceneId, item.id, item.num)
		   	end
	    end
	end
	
	local itemNumOnPlayer = GetItemCount(sceneId, humanId, x562000_g_MissionItem)
	local chkFind = 0
	local monsterSceneId = 0
	
	--����ɱ�Ĺ��Ƿ����ԭʼ�����Ҫ��
	for i, item in x562000_g_KillMonsterList do
		if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
			monsterSceneId = item.sceneid
			chkFind = 1
			break
		end
	end
	
	--���û�к��ʵĵȼ���Ӧ���ҵ����ȼ�����Ĺ���id��Ȼ�����������£�Ŀǰ��¼ԭʼ�ȼ��ķ�ʽֻҪ�������ô���Ͳ�����֣�
	if chkFind == 0 then
		local maxLevel = 0
		for i, item in x562000_g_KillMonsterList do
			if maxLevel < item.maxlevel then
				maxLevel = item.maxlevel
				monsterSceneId = item.sceneid
			end
		end
	end
			
			--�������������־��������ʾ
			AddQuestLogCustomText
						(
							sceneId,
		"", 																												--�������
							format(x562000_g_MissionFmtName, curRingIdx + 1, x562000_g_MissionRingNum), 										--��������
		format(x562000_g_TargetFmtDesc, monsterSceneId, x562000_g_MissionItem, itemNumOnPlayer, x562000_g_MissionItemNum), 	--����Ŀ��
							format("@npc_%d", x562000_g_SubmitNpcGUID),	 																		--�����ύ NPC                     
		format(x562000_g_BookDesc, monsterSceneId, x562000_g_MissionItem, itemNumOnPlayer, x562000_g_MissionItemNum),		--������
							x562000_g_AcceptDesc, 																								--��������
							x562000_g_TipDesc 																									--����С��ʾ
						 )
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, humanId, x562000_g_MissionId)
end

--**********************************
--�о��¼�������ύ NPC ����ܲ�ͬ���ύʱ�������
--**********************************
function x562000_ProcEnumEvent(sceneId, selfId, npcId, misId)

	--�����ж�
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	local curRingIdx = x562000_GetCurRing(sceneId, selfId)

	--������ȡ�����ж�
	local selfLevel = GetLevel(sceneId, selfId)
	if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
		 return
	end

    if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 0 then
        local curState = GetQuestStateNM(sceneId, selfId, npcId, x562000_g_MissionId)
        AddQuestNumText(sceneId, x562000_g_MissionId, x562000_g_MissionName, curState, 0);
    end
end

--**********************************
--��������¼�
--**********************************
function x562000_ProcEventEntry(sceneId, selfId, npcId, misId, selIndex)
	
	--�����ж�
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end
	
	--�ر�ע�ⲻ���� C++ �������� == �ж�
	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then 
		local isFinish = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), 0)

		--���������δ���������ʾ
		if isFinish == 1 then        
	        x562000_ShowNpcContext(sceneId, selfId, npcId, x562000_g_CompleteDesc, 0)
		elseif isFinish == 0 then
			BeginQuestEvent(sceneId)                                                                
			AddQuestText(sceneId, x562000_g_UnCompleteDesc)                  
			EndQuestEvent()                                                                         
			DispatchQuestEventList(sceneId, selfId, npcId, x562000_g_ScriptId, x562000_g_MissionId)
		end
	else
		--������ȡ�����ж�����ֹ��һ���Ի����ɫ��������������ɽӵ����ύ����������̣�
		local selfLevel = GetLevel(sceneId, selfId)
		if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
	        Msg2Player(sceneId, selfId, selfLevel, x562000_g_LevelErrTip, 8, 3)		
			return
		end

		x562000_ShowNpcContext(sceneId, selfId, npcId, x562000_g_AcceptDesc, 1)
	end
end

--**********************************
--�ű��������ߡ�ÿ�δ�����򼰵������������¼���������������
--**********************************
function x562000_ProcQuestLogRefresh(sceneId, selfId, misId)
    x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)
end

--**********************************
--��/���������¼�
--**********************************
function x562000_ProcQuestAccept(sceneId, selfId, npcId, misId)

	--�����ж�
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	local dayOfYear = GetDayOfYear()

	--����ϴν��������ʱ��ͱ��ղ���������ѱ����������� MD ����Ϊ 0
	local lastDate = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3])
	if lastDate ~= dayOfYear then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], 0)	
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3], dayOfYear)
	end
	
	local curRingIdx = x562000_GetCurRing(sceneId, selfId)
		
	local todayRingNum = GetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3])
	if todayRingNum < 0 then
		WriteLog(2, format("minggongchue ProcQuestAccept: GetQuestData todayRingNum(%d)", todayRingNum))
		return
	end
	
	--Ϊ�޸ĺ���ܻ�������Ӧ�Ե���
	if todayRingNum > x562000_g_MissionRingNum then
		SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], x562000_g_MissionRingNum)
		todayRingNum = x562000_g_MissionRingNum
	end

	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 0 then
	local selfLevel = GetLevel(sceneId, selfId)
	
		--������ȡ�����ж�����ֹ��һ���Ի����ɫ���������
		if selfLevel < x562000_g_AcceptMinLevel or selfLevel > x562000_g_AcceptMaxLevel then
			Msg2Player(sceneId, selfId, x562000_g_LevelErrTip, 8, 3)
			return
		end

		--�����Ƿ��Ѿ��������ж�
		if todayRingNum >= x562000_g_MissionRingNum then
			Msg2Player(sceneId, selfId, x562000_g_TodayErrTip, 8, 3)
			return
		end

		local retOpt = AddQuest(sceneId, selfId, x562000_g_MissionId, x562000_g_ScriptId, 1, 0, 1, 1)
    	
    	--����������������ʾ
    	if retOpt == 0 then
            Msg2Player(sceneId, selfId, x562000_g_MisFullErrTip, 8, 3)
    		return
    	end
    	
    	--���½������������ MD
    	SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_ACCEPTDATE[1], MD_QUEST_MIGONGCHUE_ACCEPTDATE[2], MD_QUEST_MIGONGCHUE_ACCEPTDATE[3], dayOfYear)
 	
        -- ����������ɱ��
        local misIndex = GetQuestIndexByID( sceneId, selfId, x562000_g_MissionId)
        SetQuestByIndex(sceneId, selfId, misIndex, 0, 0)

        -- ��ʾ��ʾ��Ϣ
        Msg2Player(sceneId, selfId, x562000_g_AcceptOkTip, 8, 2)
        Msg2Player(sceneId, selfId, x562000_g_AcceptOkTip, 8, 3)
        
        --��������������ʾ
        x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)
		SetQuestByIndex(sceneId, selfId, misIndex, x562000_g_AcceptLevelDataIdx, selfLevel)
    else
		local isFinish = GetQuestParam(sceneId, selfId, GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId), 0)
		local rawLevel = x562000_GetAcceptLevel(sceneId, selfId)
		
		if isFinish == 1 then

			--���һ��������Ʒ
			if curRingIdx + 1 == x562000_g_MissionRingNum then
				for i, item in x562000_g_AllBonusItemList do
				   	if rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
					   	BeginAddItem(sceneId)
		                AddBindItem(sceneId, item.id, item.num)
		                
		                if EndAddItem(sceneId, selfId) > 0 then
		                    AddItemListToPlayer(sceneId, selfId)
		                else
	   					 	Msg2Player(sceneId, selfId, x562000_g_BagFullErrTip2, 8, 3)		
	   					 	return --�޷�������Ʒ�������������
		                end
		            end
			    end
			end

			--������������
			local getExp = x562000_GetThisTimeExp(sceneId, selfId, rawLevel, curRingIdx)
			
			--���µ�ǰ�����뱾���������� MD
			curRingIdx = curRingIdx + 1
			todayRingNum = todayRingNum + 1
			SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], mod(curRingIdx, x562000_g_MissionRingNum))
			SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], todayRingNum)			

			DelQuest(sceneId, selfId, x562000_g_MissionId)
			
			--ɾ��������Ʒ
			local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
			if itemNumOnPlayer > 0 then
				DelItem(sceneId, selfId, x562000_g_MissionItem, itemNumOnPlayer)
			end

	   	 	if getExp > 0 then
	   	 		AddExp(sceneId, selfId, getExp)
	    		Msg2Player(sceneId, selfId, format(x562000_g_GetExpFmtTip, getExp), 8 ,2)
	    	end

            Msg2Player(sceneId, selfId, x562000_g_FinishTip, 8, 2)
            Msg2Player(sceneId, selfId, x562000_g_FinishTip, 8, 3)
		end
	end
end

--**********************************
--���������¼�
--**********************************
function x562000_ProcQuestAbandon(sceneId, selfId, misId)

	if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then
		DelQuest(sceneId, selfId, x562000_g_MissionId)
		
		--ɾ��������Ʒ
		local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
		if itemNumOnPlayer > 0 then
			DelItem(sceneId, selfId, x562000_g_MissionItem, itemNumOnPlayer)
		end
        
        Msg2Player(sceneId, selfId, x562000_g_GiveupErrTip, 8, 2)
        Msg2Player(sceneId, selfId, x562000_g_GiveupErrTip, 8, 3)
        
        --��������ʹ�ñ�������������ǰ��������
        SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_TODAYRING[1], MD_QUEST_MIGONGCHUE_TODAYRING[2], MD_QUEST_MIGONGCHUE_TODAYRING[3], x562000_g_MissionRingNum)	
        SetQuestData(sceneId, selfId, MD_QUEST_MIGONGCHUE_CURRING[1], MD_QUEST_MIGONGCHUE_CURRING[2], MD_QUEST_MIGONGCHUE_CURRING[3], 0)
	end
end

--**********************************
--����NPC�¼�
--**********************************
function x562000_ProcQuestAttach(sceneId, selfId, npcId, npcId, misIndex, misId)
	
	--�����ж�
	if x562000_g_CurScriptCountry ~= GetCurCountry(sceneId, selfId) then
		return
	end

	--���ۼ���������ͨ�����������ύ����
	if npcId == x562000_g_SubmitNpcGUID then
		if IsHaveQuestNM(sceneId, selfId, x562000_g_MissionId) == 1 then
			local curState = GetQuestStateNM(sceneId, selfId, npcId, x562000_g_MissionId)
			local curRingIdx = x562000_GetCurRing(sceneId, selfId)
			
			AddQuestNumText(sceneId, x562000_g_MissionId, x562000_g_MissionName, curState, 0);
		end
	end
end

--**********************************
--������Ʒ����¼�
--**********************************
function x562000_ProcQuestItemChanged(sceneId, selfId, itemId, misId)

	if itemId ~= x562000_g_MissionItem then
		return
	end

    x562000_QuestLogRefresh(sceneId, selfId, x562000_g_MissionId)

    --��������Ƿ����
	local itemNumOnPlayer = GetItemCount(sceneId, selfId, x562000_g_MissionItem)
    local misIndex = GetQuestIndexByID(sceneId, selfId, x562000_g_MissionId)
    
    --����������ɼ�⣨0��7������Ӧʵ�ʹ�����!?��ʾ���֣�
	if itemNumOnPlayer >= x562000_g_MissionItemNum then
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 1)
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 1)
	else
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 0)
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0)
	end
end

--**********************************
--ɱ�������¼���ע�⣺����(û�и�����)ɱ��Ҳ�����Լ��� selfId ����
--**********************************
function x562000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, misId)
		
	--ȡ�������������ӵ�з���Ȩ�������������Զ�������������������룩�޷���õ����
	local numKilled = GetMonsterOwnerCount(sceneId, objId)
	
	for i = 0, numKilled - 1 do
	 	
	 	--ȡ��ӵ�з���Ȩ���˵� objId
		local humanId = GetMonsterOwnerID(sceneId, objId, i)
		
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			local rawLevel = x562000_GetAcceptLevel(sceneId, humanId)
			local chkPass = 0
			
			--����ɱ�Ĺ��Ƿ���Ͻ��������¼��ԭʼ�����Ҫ��
			for j, item in x562000_g_KillMonsterList do
		   		if objdataId == item.typeid and rawLevel >= item.minlevel and rawLevel <= item.maxlevel then
			   		chkPass = 1
			   		break
		   		end
	    	end
	    	
	        if humanId ~= -1 and chkPass == 1 then         
	        	
	        	--��������ӵ������
	            if IsHaveQuestNM(sceneId, humanId, x562000_g_MissionId) == 1 then
	                
	                --���ó������÷Ƿ�
	                if x562000_g_MissionItemNum <= 0 or x562000_g_MissionItemDropMaxNum <= 0 then 
	                	return
	                end
	
	                local itemNumOnPlayer = GetItemCount(sceneId, humanId, x562000_g_MissionItem)
	                if itemNumOnPlayer < x562000_g_MissionItemNum then
		                --�����ʴ���
		                local dropRand = random(100)
		                if dropRand <= x562000_g_MissionItemDropRate then
		
			                --�����������
			                local dropNum = random(x562000_g_MissionItemDropMaxNum)
			                if dropNum == 0 then
			                    dropNum = 1
			                end
			                
			                --�����û���ǰӵ�е������������ε��������
			                if dropNum > x562000_g_MissionItemNum - itemNumOnPlayer then
			                    dropNum = x562000_g_MissionItemNum - itemNumOnPlayer
			                end
			                
			                BeginAddItem(sceneId)
			                AddBindItem(sceneId, x562000_g_MissionItem, dropNum)
			                
			                if EndAddItem(sceneId, humanId) > 0 then
			                    AddItemListToPlayer(sceneId, humanId)
			                    x562000_QuestLogRefresh(sceneId, humanId, x562000_g_MissionId)
			                else
	       					 	Msg2Player(sceneId, humanId, x562000_g_BagFullErrTip1, 8, 3)		   
			                end
			            end
					end
	            end
	        end
	    end
	end
end


--ÿ��������8��INT���ս�������ʱ��ʼֵ����0�����е�һ�������һ��������ϵͳ��Ҫ������ʶ�����Ƿ���ɵĹ̶��ֶΣ�����������ġ�
--ʣ��6�������������������������ԣ�����Ҫ�ռ���ʹ�õ���ƷID��Ҫ����Ĺ���ID�������ȵȣ����������ʱ�ѵ�һ�������һ��QuestParam����Ϊ1��
--ϵͳ���������״̬����ȥ������NPC�����Կ���NPCͷ���ʺ�״̬�Զ���ɻ�ɫ��

--���������AddQuest�ĺ��ĸ����������������ͼ����¼��Ƿ�ص�����������0��ʾ��������1��ʾ���������������Ϊ��������ǣ����Ϊ1���ú��
--ɫÿ��ɱ��һ������ʱ����ص�����ű���ProcQuestObjectKilled����������������Ϊ1���ú��ɫ����ָ������ʱ���ص�����ű���ProcAreaEntered���������߸�����Ϊ
--1���ú��ɫ���ϻ򱳰������Ʒ�����仯ʱ���ص�����ű���ProcQuestItemChanged"���������һ������Ϊ1���ú��ɫÿ�ε��NPCʱ���ص�����ű���ProcQuestAttach������