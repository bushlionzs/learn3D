
--MisDescBegin
x300867_g_ScriptId 					= 	300867                  --�ű�ID

x300867_g_MissionKind 				= 	1                       --��������
x300867_g_LevelLess					= 	20                      --������С�ȼ�  <=0 ��ʾ������
x300867_g_MissionName				= 	"����᡿�������"           --��������(512)

x300867_g_MissionTarget				= 	"  �������޾���@npc_133501��ת�󵽴�@npc_134516��"          --����Ŀ��
x300867_g_MissionInfo				= 	"\t�����������Ա��ÿ��������ǲμ�һ�Ρ���᡿�����������\n\t������Ҫ�ڰ�����񷢲��˴�����#G10������#W���ܽ��ܴ����񡣰���Աֻ���ʱ�ڰ�����Χ������Զ��ӵ����񣬽��뻤������״̬��\n\t�ڻ������޹����У�����ֻ��������ƶ�������������޹�Զ�����޻�#Gֹͣǰ��#W����������ܵ�Ϯ����������������#GѺ��#W�����Է����ߣ�ȫ���Ա#G����ʧ��#W��\n\t�����뿪����һ��ʱ�����ߣ�������ʧ��������#G����ʧ��#W��\n\t����·;ңԶ��������;��Ҫ��Ϣ��������@npc_133501�����#R������վ#W��Ť����ǰ����վ��Χ�İ��ڶ����þ��齱���������������ɻ�������ʱ�����þ���ӳɵĽ�����\n\t˳���������޵���ָ���ص㣬�����ɵõ�������Ѻ���#G�޶��#W�����뻤�͵İ���Ա�õ�#G�޶��#W��\n\t��������ָ���ص��ύ���񣬴�ʱֻ�а�����Χ�����Ѿ����뻤�͵İ���Ա����������񲢻��#G�޶��#W��ͬʱ�������100���ᾭ��#W������������#G������#Wʱ2Сʱ�ڻظ�����ɻ�÷������������飬�ﹱ����2��ʹ���㣡"            --������Ϣ
x300867_g_MissionCompleted			= 	"��ϲ��˳���������������Ӧ�õĽ����������£�"  --���������Ϣ
x300867_g_MissionHelp				=	"\t��������󣬻��ڰ�����Ļ���·����ָ���ͼ�꣺#R��\�³�#W�ͻ���#G��Ա�б�����ͨ���б��߳����ڳ�Ա������令������״̬���������ύ����ʱ����Χ���뻤�͵İ���Խ�࣬������õĽ���Ҳ����ࡣ���������ڰ��ȼ�����ߣ����õĽ���Ҳ����Ӧ���ӡ�"          --������ʾ��Ϣ
x300867_g_ExtTarget		=	{ {type=20,n=1,target="��������"}} --Ŀ��
 
--MisDescEnd


--����
x300867_g_BonusMoney8               =   150  --�������ﹱ
x300867_g_GuildExpBonus				=	1
--x300867_g_BangExp 					=	2
x300867_SubmitNPCGUID				= 134516 --������NPC GUID
x300867_g_BusScriptId = 300868
x300867_g_Leader_Index = 5		--�����ڰ��ְ���е�����
x300867_g_MissionId  = 7021
x300867_g_CostMoney = 10000
x300867_g_Exp = 100*3*25*1*1*0.4            
x300867_g_RingMissionIndex = 1	--���������������е�λ��

function x300867_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--��ʼ��ȫ�ֱ���
	--RD_GUILDCONTEND_KILL_GOLD = 1
	SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_GOLD,1)	


	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, x300867_g_MissionId ) == 0 then	-- ���û���������
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300867_g_MissionId)
		AddQuestNumText(sceneId,x300867_g_MissionId,x300867_g_MissionName,8);
		return 1
	end
	return 0
end


--ѡ������
function x300867_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExtIdx )

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then

		local npcGuid = GetMonsterGUID(sceneId,NPCId)
		if x300867_SubmitNPCGUID == npcGuid then
			x300867_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ			
		end

	else
		if nExtIdx ~= x300867_g_ScriptId then
			x300867_DispatchMissionInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ	
			--RD_GUILDCONTEND_KILL_GOLD = 2
			SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_GOLD,2)
			
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��û�д�����")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,NPCId);			
		end

	end

end


--**********************************
--����
--**********************************
function x300867_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end
	
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ǹ������״̬���ܽӴ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ɽ�������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300867_g_Leader_Index then			--���ǰ���
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ǹ�������ǰ�����û��Ȩ�����������ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o��Ǹ�������ǰ�����û��Ȩ�����������ޣ�"
		Msg2Player(sceneId,selfId,Readme,8,2)
  		return 0
 	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ӹ���״̬�²����ԽӰ�Ụ������!");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o��Ӹ���״̬�²����ԽӰ�Ụ������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	local BusID = IsBusMember(sceneId, selfId);
	if(BusID == 1) then
		local strText = "���Ѵ��ڻ���״̬���޷���ȡ�µĻ�������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o���Ѵ��ڻ���״̬���޷���ȡ�µĻ�������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
			
 	local level = GetLevel(sceneId,selfId)
	if level < x300867_g_LevelLess then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��30���Ժ���ܽ��ܡ���᡿�����������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o�ܱ�Ǹ��30���Ժ���ܽ��ܡ���᡿�����������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	--if RD_GUILDCONTEND_KILL_GOLD == 3 then
		if GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_GOLD) == 3 then
	 		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, x300867_g_ScriptId,MissionId,"OnReturn")
	 	end

	--if RD_GUILDCONTEND_KILL_GOLD == 2 then	
		if GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_GOLD) == 2 then
			BeginQuestEvent(sceneId)
					--RD_GUILDCONTEND_KILL_GOLD = 3
					SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_GOLD,3)
					AddQuestText(sceneId,"#Y����᡿�������#W\n  \n\t������ȡ����ʱ������Ա����������߲ſɽ��յ������������ʾ�������������ʱ��ֻ��������ߵİ���Ա������������ý�����\n \n#G��ȷ��Ҫ��ȡ���������?")
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x300867_g_ScriptId, x300867_g_MissionId)
		end
	
	
	

 	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, x300867_g_ScriptId,MissionId,"OnReturn")

end
function x300867_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end
	
 local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	local membercount = MissionId
	local raingMisFinishing = targetId
	x300867_GetBonus( sceneId,selfId, isMultiple, membercount,raingMisFinishing )
end

---------------------------------------------------------------------------------------------------
function x300867_GetBonus( sceneId, selfId, isMultiple, membercount, raingMisFinishing)	
--��������
	
	local exExp = 1
	if raingMisFinishing == 1 then
		exExp = 1.6
	else 
		exExp = 1
	end
	local level = GetLevel(sceneId, selfId)
	--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
	local ExpBonus = x300867_g_Exp * level* exExp
	ExpBonus =floor(ExpBonus+0.5)
	local GuildLevel = GetGuildSimpleData( GetGuildID( sceneId, selfId ) )--�õ���������(�ȼ�) 
    if ExpBonus > 0 then
		if GetHp(sceneId, selfId) > 0 then
			AddExp(sceneId, selfId, ExpBonus);
			--AddGuildMerit(sceneId, selfId,1)
	  		local Readme = "����������񣺡���᡿�������#r���#R����"..ExpBonus.."��#o�Ľ���" 
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "����������񣺡���᡿�������" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R����"..ExpBonus.."��#o�Ľ���" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			DispatchQuestTips(sceneId,selfId)
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId, "���#R��Ṧ��1��#o�Ľ���" );
			-- EndQuestEvent(sceneId)
			-- DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)	
			if GetLevel(sceneId,selfId) >= 80 then
				local refixInhExp = AddInherenceExp(sceneId,selfId,400)
				local str = format("���#R�츳ֵ%d��#o�Ľ���", refixInhExp)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, str );
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,str,8,2)
			end
		end
		if isMultiple == 1 then
			local ExpBonus1 = ceil (x300867_g_Exp * level*3)* exExp
			local Exp3 = ceil (x300867_g_Exp * level*3 )* exExp
			local ExpBonus2 = ceil (x300867_g_Exp * level*2)* exExp
			local pos = GetGuildOfficial(sceneId, selfId)
			local text3 = "���#Rʹ����2��#o�Ľ���"
				AddGuildShiMing(sceneId, selfId,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, text3);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,text3,8,2)
			if pos == 5 then
				AddExp(sceneId, selfId, ExpBonus1);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..Exp3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"���౶���������#R����"..Exp3.."��#o�Ľ���",8,2)
			elseif pos == 4 then
				AddExp(sceneId, selfId, ExpBonus2);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus2.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"���౶���������#R����"..ExpBonus2.."��#o�Ľ���",8,2)
			else
				AddExp(sceneId, selfId, ExpBonus);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"���౶���������#R����"..ExpBonus.."��#o�Ľ���",8,2)
			end
		end
		if GuildLevel == 1 then
				if membercount >= 1  then
					if membercount>=30 then
						membercount=30
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
		end
		if 	GuildLevel == 2 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp* level *0.25 )
			if membercount >= 1  then
					if membercount>=40 then
						membercount=40
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�2��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
		if 	GuildLevel == 3 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp* level *0.5 )
			if membercount >= 1  then
					if membercount>=50 then
						membercount=50
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�3��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
		if 	GuildLevel == 4 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp* level *0.75 )
			if membercount >= 1  then
					if membercount>=60 then
						membercount=60
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�4��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
		if 	GuildLevel == 5 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp * level*1 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�5��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
		if 	GuildLevel == 6 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp * level *1.25 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�6��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
		if 	GuildLevel == 7 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300867_g_Exp * level *1.5 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus3.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("�����������Ӷ�����#R����"..ExpBonus3.."��#o�Ľ���"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���ȼ�7��������#R����"..exp.."��#o�Ľ���"),8,2)
		end
	end

	
	--�����ﹱ
    if x300867_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x300867_g_BonusMoney8)	--���Ӱﹱ
		local BonusMoney8 = x300867_g_BonusMoney8
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���#R�ﹱ"..BonusMoney8.."��#o�Ľ���" );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,format("���#R�ﹱ"..BonusMoney8.."��#o�Ľ���", x300867_g_BonusMoney8),8,2)
		if isMultiple == 1 then
			local pos = GetGuildOfficial(sceneId, selfId)
				if pos == 5 then
					AddGuildUserPoint(sceneId,selfId,450)	--���Ӱﹱ
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R�ﹱ450��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ450��#o�Ľ���",8,2)
				elseif pos == 4 then
					AddGuildUserPoint(sceneId,selfId,300)	--���Ӱﹱ
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R�ﹱ300��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ300��#o�Ľ���",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,150)	--���Ӱﹱ
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R�ﹱ150��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���౶���������#R�ﹱ150��#o�Ľ���", x300621_g_BonusMoney8),8,2)
				end
		end
	end
	-- ������ᾭ��
	local bangExp = x300867_g_GuildExpBonus
	if bangExp > 0 then
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos == x300867_g_Leader_Index then
			AddGuildExp(sceneId, selfId,100)
			Msg2Player(sceneId,selfId,format("���޳ɹ��������#R��ᾭ��100��#G�Ľ���"),6,2)
		end
		--local gongde = GetGuildMerit(sceneId, selfId)
		--if 	gongde >= 5 then
			AddGuildExp(sceneId,selfId,bangExp)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R��ᾭ��"..bangExp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)			
			Msg2Player(sceneId,selfId,format("���#R��ᾭ��"..bangExp.."��#o�Ľ���"),8,2)
		--else
			-- BeginQuestEvent(sceneId)
			-- AddQuestText( sceneId, "�ܱ�Ǹ����Ṧ�µ���5�㣬���ܻ�ð�ᾭ�顣" )
			-- EndQuestEvent( sceneId )
			-- DispatchQuestTips( sceneId, selfId )
			-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ����Ṧ�µ���5�㣬���ܻ�ð�ᾭ�顣",8,2)
		-- end
	end
--����Ѻ��
	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos == x300867_g_Leader_Index then			--�ǰ���
		if x300867_g_CostMoney > 0 then
			AddMoney( sceneId , selfId ,0, x300867_g_CostMoney )
			local readme="���#R����Ѻ��10��#o"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R����Ѻ��10��#o" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player( sceneId,selfId,readme,8,2 )
		end 
 	end
	--������д��־
	GamePlayScriptLog(sceneId,selfId,12)
	
	CallScriptFunction( 300638, "SaveGuildYunBiaoMD", sceneId,selfId )	
end


--�������
--����1����ɹ���0��������ʧ��
function x300867_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end

	-- local pos = GetGuildOfficial(sceneId, selfId)
  	-- if pos ~= x300867_g_Leader_Index then			--���ǰ���
  		-- return 0
 	-- end
 	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

    local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300867_g_Leader_Index then			--���ǰ���
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����ǰ����޷��ظ�����᡿�����������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o�����ǰ����޷��ظ�����᡿�����������" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
 	end

    --�ڳ��Ƿ����
	local valid = IsValidGuildBus(sceneId, selfId)
	if valid == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������ڳ���Զ���޷��ύ����᡿�����������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o�������ڳ���Զ���޷��ύ����᡿�����������" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	SubmitGuildConvoyQuest(sceneId, selfId)
 	local GuildID = GetGuildID(sceneId,selfId)
	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)

	return 0
end


function x300867_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if IsHaveQuestNM( sceneId, selfId, x300867_g_MissionId ) == 0 then	-- ���û���������
		return
	end

	if npcGuid == x300867_SubmitNPCGUID then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		local state = GetQuestStateNM(sceneId,selfId,npcId,x300867_g_MissionId)
		AddQuestNumText( sceneId, x300867_g_MissionId,x300867_g_MissionName, 7,x300867_g_ScriptId ) -- ��ʾ������Ϣ
	end
end


--********************************************************************
--�����Ụ����������
--********************************************************************
function x300867_OnGuildConvoyClearMemberQuest( sceneId, selfId,state )

	if IsHaveQuestNM( sceneId, selfId, x300867_g_MissionId ) == 0 then	-- ���û���������
		return
	end

	local str = "������ˡ���᡿���������������ʧ��!"

	if state == 0 then				--����Ա��������
		str = "������ˡ���᡿���������������ʧ��!"
	elseif state == 1 then			--��������
		str = "���ڰ��������߳��˻������޶��飬����᡿�����������ʧ��!"
	elseif state == 2 then			--��������
		str = "���ڰ��������ˡ���᡿���������������ʧ��!"
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos == x300867_g_Leader_Index then			--�ǰ���
			local GuildID = GetGuildID(sceneId,selfId)
			local CurDaytime = GetDayTime()						--��ǰʱ��(��)
			SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
		end
	elseif state == 3 then			--����
		str = "���ڰ���������ְλ������᡿�����������ʧ��!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--��ǰʱ��(��)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	elseif state == 4 then			--����ɢ
		str = "���ڰ�ᱻ��ɢ������᡿�����������ʧ��!"
	elseif state == 5 then			--BUS����
		str = "������������������᡿�����������ʧ��!"
	elseif state == 6 then			--BUS�ȴ���ʱ
		str = "���ڰ����뿪����Ŀ��ʱ����ã�����Ŀ����ʧ������ʧ�ܣ�"
	elseif state == 7 then			--BUS������ʱ
		str = "��������������ʱ������᡿�����������ʧ��!"
	elseif state == 11 then			--������ʱ���ڳ�̫Զ
		str = "�������뿪����̫Զ�����޷���ý���!"
	elseif state == 17 then			--����������
		str = "���ڵ��������ɹ�������λ�÷����仯������᡿�����������ʧ��!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--��ǰʱ��(��)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	elseif state == 18 then			--����ɾ���ڳ�
		str = "������������������᡿�����������ʧ��!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--��ǰʱ��(��)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	end

	if state>=0 and state<=7 or state == 11 or state ==17 or state ==18 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,str,8,2)
	end

	local ret = DelQuest( sceneId, selfId, x300867_g_MissionId  )
	if ret == 1 then
		--Msg2Player( sceneId, selfId, "#R���Ѿ�����["..MissionName.."]����", MSG2PLAYER_PARA )
	else
		--�۳�������Ʒʧ�ܴ���
	end
	
end     


--********************************************************************
--�ύ��Ұ�Ụ�����񣺸�����
--********************************************************************
function x300867_OnGuildConvoySubmitQuest( sceneId, selfId )

	local misIndex = GetQuestIndexByID(sceneId, selfId, x300867_g_MissionId); 
	
	--�õ�������״̬
	local raingMisFinishing = GetQuestParam( sceneId, selfId,misIndex,x300867_g_RingMissionIndex )

	--�����������  
	--GetQuestNameNM( sceneId, selfId, MissionId )
	if DelQuest( sceneId, selfId, x300867_g_MissionId  ) < 1 then
		return 
	end

    -- ���ӻ�Ծ��
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM5) )
    end

	CallScriptFunction( 256267, "Finishhss", sceneId, selfId)
	local membercount = GetBusEscortMemberNum(sceneId,selfId)
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_HUSHOU, x300867_g_ScriptId,membercount,"OnReturn1",raingMisFinishing)
end


--********************************************************************
--����
--********************************************************************
function x300867_ProcQuestAbandon( sceneId, selfId, MissionId )

	AbandonGuildConvoyQuest(sceneId, selfId,0)
	
--	local pos = GetGuildOfficial(sceneId, selfId)
--  	if pos == x300867_g_Leader_Index then			--�ǰ���
--  		local GuildID = GetGuildID(sceneId,selfId)
--		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_STATE, -1)
-- 	end
 	
end

function x300867_ClearBusMission( sceneId, selfId )
	AbandonGuildConvoyQuest(sceneId, selfId, 18)
end

function x300867_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
		
	if MissionData == CurDaytime then					--�ϴη�����ʱ���ǽ���
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���������İ���ѻ��͹������ˣ�����������ɣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o�ܱ�Ǹ���������İ���ѻ��͹������ˣ�����������ɣ�" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		--DispatchQuestEventList(sceneId, selfId, -1)
	else
		local CurrMoney = GetMoney(sceneId , selfId ,0)
		if CurrMoney < x300867_g_CostMoney then
		    BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�����ϵ��������㣡");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "#o�ܱ�Ǹ���������е���������֧��Ѻ���޷���ȡ����" 
			Msg2Player(sceneId,selfId,Readme,8,2)
			return
		end

	
	    local BusID = CallScriptFunction( x300867_g_BusScriptId, "OnCreateBus", sceneId, selfId,MissionId )
		--if BusID ~= -1 then
		--	AcceptGuildConvoy( sceneId, selfId,BusID )
		--end
		
	end
	
	--DispatchQuestEventList(sceneId, selfId, -1)

end


--********************************************************************
--����
--********************************************************************
function x300867_ProcAccept( sceneId, selfId )

	if GetGuildID(sceneId, selfId) == -1 then
		--δ������
		return 0
	end

	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos == x300867_g_Leader_Index then			--�ǰ���
		
		local num = CostMoney( sceneId , selfId ,0, x300867_g_CostMoney,301 )--�ɹ�����1 ʧ�ܷ���-1
		if num == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "��ȡ����ʧ�ܣ�");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "#o�ܱ�Ǹ���������е���������֧��Ѻ���޷���ȡ����" 
			Msg2Player(sceneId,selfId,Readme,8,2)
			return
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�����������񣺡���᡿�������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "�����������񣺡���᡿�������#r�۳���#R10#W#o��������ΪѺ��" 
			Msg2Player(sceneId,selfId,Readme,8,2)
		end

 	end

	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
	local ret = AddQuest( sceneId, selfId,x300867_g_MissionId , x300867_g_ScriptId,0,0,0,1 ) -- ������������
	
	if ret == 1 then

		--������д��־
		GamePlayScriptLog(sceneId,selfId,11)

		x300867_QuestLogRefresh( sceneId, selfId, x300867_g_MissionId)
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		-- local Readme = "���ѽ��ܻ������ޣ�"
		-- Msg2Player(sceneId,selfId,Readme,8,2)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300867_g_MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);

		--�������ʼ��
		SetQuestByIndex(sceneId, selfId, misIndex, x300867_g_RingMissionIndex, 0);		

  		--AddDispatchQuestInfoNM( sceneId, selfId, -1, x300867_g_MissionId )
  		local pos = GetGuildOfficial(sceneId, selfId)
  		if pos == x300867_g_Leader_Index then			--�ǰ���
  			local GuildID = GetGuildID(sceneId,selfId)
  			SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME , CurDaytime)		
  			SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME , 0)	  				
  		end
	end

end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300867_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x300867_g_MissionName)
		AddQuestText(sceneId,format("%s", x300867_g_MissionInfo))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y����Ŀ�꣺")
		AddQuestText( sceneId,format("%s", x300867_g_MissionTarget))
		AddQuestText( sceneId," ")

		--��ʾ��Ϣ
		if x300867_g_MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y������ʾ��")
			AddQuestText(sceneId,format("%s", x300867_g_MissionHelp))
			AddQuestText(sceneId," ")
		end
		-- if level >= 80 then
			-- AddQuestText(sceneId,"�츳ֵ��400��")
		-- end
		--��������Ϣ
			AddQuestText(sceneId,"\n#Y�������ݣ�")	
		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300867_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"����ֵ��"..ExpBonus.."��")	
		end

		--2���ﹱ
		if x300867_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300867_g_BonusMoney8 )
			AddQuestText(sceneId,"�ﹱ��150��")	
			
		end	
		--��ᾭ��
		if x300867_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300867_g_GuildExpBonus)
			AddQuestText(sceneId,"��ᾭ�飺1��")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("�츳ֵ��%d��", refixInhExp)
			AddQuestText(sceneId, str)
		end
		

	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300867_g_ScriptId, x300867_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300867_DispatchContinueInfo( sceneId, selfId, NPCId )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300867_g_MissionName)
		AddQuestText(sceneId,format("%s", x300867_g_MissionInfo))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y��������")
		AddQuestText(sceneId, "δ���\n");
		AddQuestText(sceneId, "#Y�������ݣ�");
  		--��������Ϣ

   		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300867_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"����ֵ��"..ExpBonus.."��")	
		end

		--2���ﹱ
		if x300867_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300867_g_BonusMoney8 )
			AddQuestText(sceneId,"�ﹱ��150��")	
			
		end	
		--��ᾭ��
		if x300867_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300867_g_GuildExpBonus)
			AddQuestText(sceneId,"��ᾭ�飺1��")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("�츳ֵ��%d��", refixInhExp)
			AddQuestText(sceneId, str)
		end
	    --������ʾ��Ϣ
	EndQuestEvent()
	--DispatchQuestEventList(sceneId,selfId,NPCId);
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300867_g_ScriptId, x300867_g_MissionId,0);

end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300867_DispatchCompletedInfo( sceneId, selfId, NPCId )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300867_g_MissionName)
		AddQuestText(sceneId,x300867_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--��������Ϣ
		AddQuestText(sceneId,"\n#Y�������ݣ�")	
		--1������
		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300867_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"����ֵ��"..ExpBonus.."��")	
		end

		--2���ﹱ
		if x300867_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300867_g_BonusMoney8 )
			AddQuestText(sceneId,"�ﹱ��150��")	
			
		end	
		--��ᾭ��
		if x300867_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300867_g_GuildExpBonus)
			AddQuestText(sceneId,"��ᾭ�飺1��")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("�츳ֵ��%d��", refixInhExp)
			AddQuestText(sceneId, str)
		end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300867_g_ScriptId, x300867_g_MissionId);
  CallScriptFunction( 256267, "Finishhss", sceneId, selfId)
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300867_QuestLogRefresh( sceneId, selfId, MissionId)
 BeginQuestEvent(sceneId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
	if bHaveMission > 0 then
		BeginQuestEvent(sceneId)	
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300867_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end
		if x300867_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300867_g_BonusMoney8 )
		end	
		--��ᾭ��
		if x300867_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300867_g_GuildExpBonus)
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			AddQuestInherenceExpBonus(sceneId,refixInhExp)
		end
		AddQuestLogCustomText( sceneId,
								"",						-- ����
								x300867_g_MissionName,        -- ��������
								x300867_g_MissionTarget,		--����Ŀ��
								"",					--����NPC
								"�����ް�ȫ���͵��߾�����@npc_134516",                 --������
								x300867_g_MissionInfo,	--��������
								""					--����С��ʾ
								)
	end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end

function x300867_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300867_QuestLogRefresh( sceneId, selfId, x300867_g_MissionId)
end


function x300867_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end


--��Ա�������ͷ�Χ�Ĵ���
function x300867_OnMeberOffline(sceneId,selfId)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "���Ѿ��������޹�Զ�����޸е���һ˿Σ�գ��뾡�췵�أ�")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,"#cEFC800���Ѿ��������޹�Զ�����޸е���һ˿Σ�գ��뾡�췵�أ�", 8,2)
	
end