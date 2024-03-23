--���Ҹ���
--MisDescBegin
--����ID
x260012_g_MissionId = 3144
--�ű���
x260012_g_ScriptId = 260012

--��һ�������ID
--g_MissionIdPre =

--�����ı�����


x260012_g_MissionName="�����ҡ�Ϊ��Ч��<��>"

x260012_g_ReplyNpcId = 131502
x260012_g_LevelLess	= 50
x260012_g_NeedLevel = 50
x260012_g_NeedExploit = 14
x260012_g_BonusItem	=	{{item=11990110,n=3}}
x260012_g_MissionTarget ="   ���14�㹦ѫ"
x260012_g_MissionMethod = "��ѫ����14"              --������
x260012_g_MissionText = "\t#G14��#W��ѫֵ������Ӧ�ò���ܴ����ս��\n\tÿ���ڷ����������ڼ�ɹ�#G��ɳ�����������#W������һ���Ĺ�ѫֵ��\n\t�����ܹ�#G14��#W��ѫֵ��ʱ���������Ұɡ�"					--��������
x260012_g_MissionCompleted = "\t��Ĺ�ѫֵ���㣡ֻ��ÿ���ڷ����������ڼ�#G�ɹ���ɳ�������#W���Ż��ù�ѫֵ��"
x260012_g_MissionEnd = "\t�������ȡ��ѫ���ٶ���Խ��Խ���ˣ� \n\t���ҿ�����������������Ҫ����#G�Ž�һ��#W��#G��������#W��"
x260012_g_MissionHelp = "\tֻ��ÿ���ڷ���#G�������ڼ�#W�ɹ���ɳ������񣬲Ż��ù�ѫֵ��"					--����С��ʾ

function x260012_ShowTips(sceneId, selfId, tip)
	BeginQuestEvent(sceneId)
    AddQuestText(sceneId, tip)
    EndQuestEvent()
    DispatchQuestTips(sceneId, selfId)
end
--MisDescEnd

--**********************************
--������ں���
--**********************************
function x260012_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
		local MissionName = x260012_g_MissionName
	if MissionId ~= x260012_g_MissionId then
		if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
			return 
		end
	else
		if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
			return 
		end
	
	end	
		if GetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3] ) == 1 then
			return
		end
		
		if GetLevel(sceneId, selfId) >= x260012_g_NeedLevel then
			local state = GetQuestStateNM(sceneId, selfId, targetId, x260012_g_MissionId);
			AddQuestNumText(sceneId, x260012_g_MissionId, MissionName,state,5);

		end
end

function x260012_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	if IsHaveQuestNM( sceneId, selfId, x260012_g_MissionId ) > 0 then	-- ������������
			local bDone = x260012_CheckSubmit(sceneId, selfId,targetId, x260012_g_MissionId);
	        if (bDone > 0) then
				x260012_DispatchCompletedInfo( sceneId, selfId, targetId,x260012_g_MissionId) --���������ʾ
			else
			x260012_DispatchContinueInfo( sceneId, selfId, targetId,x260012_g_MissionId ) --δ���������ʾ
			end
	else
			x260012_DispatchMissionInfo( sceneId, selfId, targetId,x260012_g_MissionId )		--������Ϣ��ʾ
	end
end

--**********************************
--�о��¼�
--**********************************

--**********************************
--����������
--**********************************
function x260012_ProcAcceptCheck( sceneId, selfId, NPCId )
	local MissionId = x260012_g_MissionId
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		x260012_ShowTips(sceneId, selfId, "���Ѿ���ȡ�˸�����������ɵ�ǰ����")
		return 0;
	end 
	return 1
end

function x260012_ProcQuestAccept( sceneId, selfId, NPCId, MissionId)
    --local MissionId = x260012_g_MissionId
    local ScriptId = x260012_g_ScriptId
    local MissionName = x260012_g_MissionName
    
    if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 
    end
    if IsQuestFullNM(sceneId,selfId)==1 then
        x260012_ShowTips(sceneId, selfId, "�ɽ�������������")
        return 
    end
		
    if x260012_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, MissionId, ScriptId, 0, 0, 0,1)
    
        if retmiss  > 0 then
			Msg2Player(sceneId,selfId,"������������"..MissionName,8,2)
			if GetExploit(sceneId, selfId) >= x260012_g_NeedExploit then
					local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
		            SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		            SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		           
			end
        else
			Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
		end
    end
end

--**********************************
--����
--**********************************
function x260012_ProcAccept( sceneId, selfId )
	return 1
end

--**********************************
--����
--**********************************
function x260012_ProcQuestAbandon( sceneId, selfId, MissionId )
	local MissionId = x260012_g_MissionId
    local MissionName = x260012_g_MissionName
    
	if IsHaveQuest(sceneId,selfId, MissionId) <= 0 then
		return 
	end
	DelQuest(sceneId, selfId, MissionId)
	Msg2Player(sceneId,selfId,"������������"..MissionName.."��",8,2)
end

--**********************************
--����
--**********************************
function x260012_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x260012_CheckSubmit( sceneId, selfId, targetId,MissionId) 
	local misIndex = GetQuestIndexByID(sceneId, selfId, x260012_g_MissionId)
	local state = GetQuestStateNM(sceneId, selfId, targetId, x260012_g_MissionId)
	AddQuestNumText( sceneId, x260012_g_MissionId,x260012_g_MissionName, 7,state ) 
	return GetQuestParam(sceneId, selfId, misIndex, 7);
end

--**********************************
--�ύ
--**********************************
function x260012_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )

	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,x260012_g_MissionEnd)
		AddQuestText(sceneId," ")
		
		AddQuestText( sceneId,"#Y��������")
		AddQuestText(sceneId, "�����");

		--1������
		for i, item in x260012_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		--2 �﹩
		-- if x260012_g_BonusMoney8>0 then
			-- AddQuestMoneyBonus8(sceneId,x260012_g_BonusMoney8)
		-- end
		--3 ��ᾭ��
		-- if x260012_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x260012_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x260012_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x260012_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
	BeginQuestEvent(sceneId)
		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,format("%s", x260012_g_MissionCompleted))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y��������")
		AddQuestText(sceneId, "δ���#r");
		AddQuestText(sceneId, "��Ҫ��ѫֵ��14��");

		-- for i, item in x260012_g_BonusItem do
		   	-- AddQuestItemBonus(sceneId, item.item, item.n)
	 	-- end

	--������ʾ��Ϣ
	EndQuestEvent(sceneId)
	DispatchQuestDemandInfo(sceneId, selfId, targetId, x260012_g_ScriptId, MissionId,0);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x260012_DispatchMissionInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,format("%s", x260012_g_MissionText))
		AddQuestText(sceneId," ")

		--����Ŀ��
		--AddQuestText( sceneId,x260012_g_MissionText)
		--AddQuestText( sceneId,format("%s", x260012_g_MissionTarget))
		--AddQuestText( sceneId," ")

		--��ʾ��Ϣ
		if x260012_g_MissionHelp ~= "" then

			--AddQuestText(sceneId,x260012_g_MissionTarget)
			AddQuestText(sceneId,format("%s", x260012_g_MissionHelp))
			AddQuestText(sceneId," ")
		end

		--1������
		for i, item in x260012_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		--2 �﹩
		-- if x260012_g_BonusMoney8>0 then
			-- AddQuestMoneyBonus8(sceneId,x260012_g_BonusMoney8)
		-- end
		--3 ��ᾭ��
		-- if x260012_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x260012_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x260012_g_ScriptId, MissionId);
end

function x260012_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end
    local MissionName = x260012_g_MissionName

    if GetExploit(sceneId, selfId) < x260012_g_NeedExploit then
        --x260012_ShowTips(sceneId,selfId,"��Ĺ�ѫ��������Ҫ"..x260012_g_NeedExploit)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ĺ�ѫ��������Ҫ"..x260012_g_NeedExploit.."�������ȡ������ ");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	  	Msg2Player(sceneId,selfId,"��Ĺ�ѫ��������Ҫ"..x260012_g_NeedExploit.."�������ȡ������ ",8,2)
    else
		BeginAddItem(sceneId)                                                    
        for i, item in x260012_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        
        if EndAddItem(sceneId,selfId) > 0 then
			if DelQuest(sceneId, selfId, MissionId) > 0 then
				AddItemListToPlayer(sceneId,selfId) 
				QuestCom(sceneId, selfId, x260012_g_MissionId)
				Msg2Player(sceneId,selfId,"�����������"..MissionName.."��",8,2)
				SetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3], 1 ) 
			end
			if DelQuestNM( sceneId, selfId, MissionId) < 1 then
				return 
			end
        else
            BeginQuestEvent(sceneId)
            local strText = "�����ռ䲻�㣬�޷������Ʒ��"
            AddQuestText(sceneId,strText);
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
        end
   end
end

-----------------------------------
function x260012_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, x260012_g_MissionId) == 0 then	-- ���û���������
		return
	end
	local state = GetQuestStateNM(sceneId, selfId, npcId, x260012_g_MissionId);
	if npcGuid == x260012_g_ReplyNpcId then
		if GetExploit(sceneId, selfId) < x260012_g_NeedExploit then
			AddQuestNumText(sceneId, x260012_g_MissionId, x260012_g_MissionName,6,state);
			else
			 AddQuestNumText(sceneId, x260012_g_MissionId, x260012_g_MissionName,7,state);
		end
	end
end
--**********************************
--ɱ����������
--**********************************
function x260012_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--���������¼�
--**********************************
function x260012_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x260012_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x260012_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	--local myMissionId = x300797_GetMissionId( sceneId, selfId )
	local ScriptId = x260012_g_ScriptId
	local MissionName = x260012_g_MissionName
	local target =  x260012_g_MissionTarget

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							MissionName,        -- ��������
							target,		--����Ŀ��
							"@npc_"..x260012_g_ReplyNpcId,			--����NPC
							x260012_g_MissionMethod,             --������
							x260012_g_MissionText,					--��������
							x260012_g_MissionHelp					--����С��ʾ
							)
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x260012_OnExploitChanged(sceneId,selfId, exploit)
	local MissionId = x260012_g_MissionId
    
    
	if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, MissionId) <= 0 then
		return
	end
	if GetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3] ) == 1 then
		return
	end
	if GetExploit(sceneId, selfId) >= x260012_g_NeedExploit then
			local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
            SetQuestByIndex(sceneId,selfId,misIndex,0,1)
            SetQuestByIndex(sceneId,selfId,misIndex,7,1)
    else
			local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
            SetQuestByIndex(sceneId,selfId,misIndex,0,0)
            SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	end
end

