
--MisDescBegin
x300680_g_ScriptId 					= 	300680                  --�ű�ID
x300680_g_MissionKind 				= 	1                       --��������
x300680_g_MissionName				= 	"����᡿������վ"      --��������(512)

x300680_g_MissionCompleted			= 	"\t���޾�����Ϣ�����������ˣ���������վ�����Ľ�����"  --���������Ϣ
x300680_g_MissionInfo				= 	"\tÿ����Ụ������ʱ�����������������������Ϣ��ͬʱ�ڰ�����ߵİ��ڻ��þ��齱����������ɻ�����������ʱҲ���þ��齱���ӳɡ�"  	

--MisDescEnd

--����
x300680_g_BonusMoney8               =   100  --�������ﹱ
x300680_g_GuildExpBonus				=	1
x300680_g_Leader_Index = 5					--�����ڰ��ְ���е�����
x300680_g_Exp = 100*3*25*1*1*0.4
x300680_g_LogId = 111
x300680_g_RingMissionIndex = 1				--���������������е�λ��

x300680_g_CountryList = {
							{ countryId = 0 , submitNpcGuid = 124534, misId = 7024, misEndId = 7002 },
							{ countryId = 1 , submitNpcGuid = 127540, misId = 7705, misEndId = 7023 },
							{ countryId = 2 , submitNpcGuid = 130531, misId = 7706, misEndId = 7022 },
							{ countryId = 3 , submitNpcGuid = 133501, misId = 7707, misEndId = 7021 },							
						}

--�����NPC��
function x300680_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300680_g_Leader_Index then			--���ǰ���
  		return 0
 	end
	
	local misId = 0
	local misEndId = 0

	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			misEndId = itm.misEndId
			break
		end
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, misEndId); 
	local isFinishing = GetQuestParam( sceneId, selfId,misIndex,x300680_g_RingMissionIndex )
	if isFinishing == 1 then
		return
	end
	
	if IsHaveQuestNM(sceneId, selfId, misId) <= 0 then
		--return
	end
		
	AddQuestNumText(sceneId,misId,x300680_g_MissionName,8)
	
end



--�������ť������������ִ�д˽ű�
function x300680_ProcEventEntry( sceneId, selfId, NPCId,state,nExtIdx)	

	local misId = 0
	local submitNpcGuid = -1

	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			submitNpcGuid = itm.submitNpcGuid
			break
		end
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, misId);
	if(bHaveMission > 0) then
		local npcGuid = GetMonsterGUID(sceneId,NPCId)
		if submitNpcGuid == npcGuid then
			x300680_DispatchCompletedInfo( sceneId, selfId, NPCId,misId) --���������ʾ			
		end

	else
		if nExtIdx ~= x300680_g_ScriptId then
			x300680_DispatchMissionInfo( sceneId, selfId, NPCId, misId )	--������Ϣ��ʾ		
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��û����������")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,NPCId);			
		end

	end
		
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300680_DispatchCompletedInfo( sceneId, selfId, NPCId, misId )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300680_g_MissionName)
		AddQuestText(sceneId,x300680_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--��������Ϣ

		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300680_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end

		--2���ﹱ
		-- if x300680_g_BonusMoney8 > 0 then
			-- AddQuestMoneyBonus8(sceneId, x300680_g_BonusMoney8 )
		-- end	
		--��ᾭ��
		-- if x300680_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300680_g_GuildExpBonus)
		-- end

	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300680_g_ScriptId, misId);

end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300680_DispatchMissionInfo( sceneId, selfId, NPCId, misId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x300680_g_MissionName)
		AddQuestText(sceneId,format("%s", x300680_g_MissionInfo))
		AddQuestText(sceneId," ")

		--��������Ϣ
		AddQuestText(sceneId,"\n#Y�������ݣ�")
		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300680_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"����ֵ��"..ExpBonus.."��")
			--AddQuestExpBonus(sceneId,  ExpBonus);
		end
		
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 300)
			local str = format("�츳ֵ��%d��", refixInhExp)
			AddQuestText(sceneId, str)
		end
		--2���ﹱ
		-- if x300680_g_BonusMoney8 > 0 then
			-- AddQuestMoneyBonus8(sceneId, x300680_g_BonusMoney8 )
		-- end	
		--��ᾭ��
		-- if x300680_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300680_g_GuildExpBonus)
		-- end
		
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300680_g_ScriptId,misId);
	
end


function x300680_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	--�ж��Ƿ����
	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300680_g_Leader_Index then			
  	
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ǹ�������ǰ�����û��Ȩ����ȡ������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "��Ǹ�������ǰ�����û��Ȩ����ȡ������"
		Msg2Player(sceneId,selfId,Readme,8,2)
  		return 0
  		
 	end
 	
 	 --�ж��Ƿ��л�������
	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
	
	if IsHaveQuestNM( sceneId, selfId, misEndId ) == 0 then	
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ǹ����û�н��ܻ�������û��Ȩ����ȡ������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "��Ǹ����û�н��ܻ�������û��Ȩ����ȡ������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
  	--�ж������Ƿ�����Ч������
	local valid = IsValidGuildBus(sceneId, selfId)
	if valid == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������ڳ���Զ���޷��ύ������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o�������ڳ���Զ���޷��ύ������������" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
 	--�жϵ����Ƿ��Ѿ���ȡ��
 	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME, x300680_g_ScriptId,misEndId,"OnReturn")

end

function x300680_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	--�ж��Ƿ��Ѿ���ȡ��
	if MissionData == 0 then					--�Ѿ���ȡ����

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���ˣ�����������ɣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ�����Ѿ���ȡ���ˣ�����������ɣ�" 
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return
		
	end

	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
	local misIndex = GetQuestIndexByID(sceneId, selfId, misEndId) 
	local isFinishing = GetQuestParam( sceneId, selfId,misIndex,x300680_g_RingMissionIndex )
	if isFinishing == 1 then
		return
	end
	SetQuestByIndex(sceneId, selfId, misIndex, x300680_g_RingMissionIndex, 1);	
	
	--��¼��ȡ״̬	
	local GuildID = GetGuildID(sceneId,selfId)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME, 1)
	
 	--��������Ч�����ڵİ��ڵý���
	local x,z = GetWorldPos(sceneId,selfId)
	local playerCount =  GetNearCountryCount(sceneId, selfId,x,z,25)  

	for i = 0, playerCount-1 do

		--�ж��Ƿ�ͬ��
		local humanObjId = GetNearCountryMember(sceneId, selfId,i) 
		if GetGuildID(sceneId, humanObjId) == GuildID then

			--�ж��Ƿ��л�������
			if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	
				--��ȡ����
				x300680_GetBonus( sceneId,humanObjId, membercount )
			end

		end

	end

end

function x300680_GetBonus( sceneId, selfId, membercount )	

	--��������
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = x300680_g_Exp * level
	ExpBonus =floor(ExpBonus+0.5)
    if ExpBonus > 0 then
		if GetHp(sceneId, selfId) > 0 then
			AddExp(sceneId, selfId, ExpBonus);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R����"..ExpBonus.."��#o�Ľ���" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"���#R����"..ExpBonus.."��#o�Ľ���",8,2)	
		end
	end
	if GetLevel(sceneId,selfId) >= 80 then
		local refixInhExp = AddInherenceExp(sceneId,selfId,300)
		local str = format("���#R�츳ֵ%d��#o�Ľ���", refixInhExp)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,str,8,2)
	end
	--�����ﹱ
    -- if x300680_g_BonusMoney8 > 0 then
		-- AddGuildUserPoint(sceneId,selfId,x300680_g_BonusMoney8)	--���Ӱﹱ
		-- local BonusMoney8 = x300680_g_BonusMoney8
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "���#R�ﹱ"..BonusMoney8.."��#o�Ľ���" );
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- Msg2Player(sceneId,selfId,format("���#R�ﹱ"..BonusMoney8.."��#o�Ľ���", x300680_g_BonusMoney8),8,2)
	-- end

	-- ������ᾭ��
	-- local bangExp = x300680_g_GuildExpBonus
	-- if bangExp > 0 then
		-- local pos = GetGuildOfficial(sceneId, selfId)
		-- if pos == x300680_g_Leader_Index then
			-- AddGuildExp(sceneId, selfId,100)
			-- Msg2Player(sceneId,selfId,format("�����#R��ᾭ��100��#G�Ľ���"),6,2)
		-- end
			-- AddGuildExp(sceneId,selfId,bangExp)
			-- Msg2Player(sceneId,selfId,format("���#R��ᾭ��"..bangExp.."��#o�Ľ���"),8,2)
	-- end

	--������д��־
	GamePlayScriptLog(sceneId,selfId,x300680_g_LogId)	
	
	--�޸Ļ������־
	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
		
end


