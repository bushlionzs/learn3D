
--MisDescBegin
x300827_g_ScriptId		=	300827
x300827_g_MissionName	=	"����᡿��ľ"
x300827_g_MissionTarget	=	"���ռ�#G��ľ#W"
x300827_g_MissionInfo	=	"\t���Ű������չ��������Ҫ���߼���ľ����������������������������#R������ͼ#W�ĵ�ľ��һ�������ľͷ�����겻������ȴ������ïʢ����˵�����Ƕ����������������������˹ȵĶ��㣬���㣬�Ĳ����㣬��������������ĵ�ľ��������������Σ�գ���Ը�������ڴ��������ľô�������������ռ���ʱ2Сʱ�ڻظ�����ɻ�÷������������飬�ﹱ����2��ʹ���㣡"
x300827_g_MissionHelp	=	"\t#G��ľ#Wֻ�����ڵ���#R������ͼ#W@npc_37000��@npc_38000��@npc_39000����������ϡ�١����������ڰ��ȼ�����ߣ����õĽ���Ҳ����Ӧ���ӡ�"
x300827_g_MissionRuse	=	"\t���㵽��#R������ͼ#W�������ռ�#G��ľ#Wʱ������ܵ����������޷��ռ��ɹ�������Խ�����䣬����Χ�Ĺ���ɱ�����ٽ����ռ���#R������ͼ#W�Ĺ���Ƚ��ܼ�������ú���ӽ����ռ���"
x300827_g_MissionCompleted = "����Ҫ�ĵ�ľ�����Ѿ��ҵ��ˣ�̫��л�ˣ������ˣ����Ǹ���ĳ�л��"
x300827_g_SubmitNPCGUID	=	123723
x300827_g_GroupPoint	=	{ {type=10,id =124,target = "��ľ"}}

x300827_g_NPCName		= "@npc_123723"

x300827_g_ExtTarget		=	{ {type=20,n=10,target="��"} }
x300827_g_LevelLess		= 	40 
--x300827_g_BonusMoney8	=   100
--MisDescEnd
x300827_g_BonusMoney8	=   50
x300827_g_GuildExpBonus =	1
--x300827_g_BangExp 		=   1
x300827_g_Mis_Count		= 1
x300827_g_Leader_Index	= 5
x300827_g_PreMissionId	= 7006


function x300827_IsHavePreMission(sceneId, selfId)
	local MissionId1  = 7006 
		if IsHaveQuestNM( sceneId, selfId, MissionId1 ) > 0 then	-- ������������
			return 1
		end
	return -1
end
                    
function x300827_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if x300827_IsHavePreMission(sceneId, selfId) > 0 then
		return 0
	end

	if GetGuildID( sceneId, selfId ) == -1 then
 		--���ڰ����
		return
	end
	
	 local level = GetLevel(sceneId,selfId)
	if level < 40  then
		return
	end

  	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local state = GetQuestStateNM( sceneId, selfId, targetId, MissionId);
		AddQuestNumText( sceneId, MissionId, x300827_g_MissionName ,8,state)	
		--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300827_g_ScriptId,MissionId,"OnCallBackEnumerate",targetId)
		return 
	end

end


--ѡ������
function x300827_ProcEventEntry( sceneId, selfId, targetId, MissionId )
--local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--�õ���������(�ȼ�) 
	--if 	GuildLevel == 2 then		     	
		if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������
			local bDone = x300827_CheckSubmit(sceneId, selfId,targetId, MissionId);
			if(bDone > 0) then
				x300827_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId) --���������ʾ
			else
				x300827_DispatchContinueInfo( sceneId, selfId, targetId,MissionId ) --δ���������ʾ
			end
		else
			x300827_DispatchMissionInfo( sceneId, selfId, targetId,MissionId )		--������Ϣ��ʾ
		end
	--end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300827_CheckSubmit(sceneId, selfId,targetId,MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local state = GetQuestStateNM(sceneId,selfId,targetId,MissionId)
	AddQuestNumText( sceneId, MissionId,x300827_g_MissionName, 7,state ) 
	return GetQuestParam(sceneId, selfId, misIndex, 7);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300827_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300827_g_MissionName)
		AddQuestText(sceneId,x300827_g_MissionCompleted)
		AddQuestText(sceneId," ")
		--AddQuestText(sceneId,"��Ṧ�£�1�� ")
		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (100 * 3 * level * 20*1*1 )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		--2 �﹩
		if x300827_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300827_g_BonusMoney8)
		end
		--3 ��ᾭ��
		-- if x300827_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300827_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300827_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300827_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300827_g_MissionName)
		AddQuestText(sceneId,format("%s", x300827_g_MissionInfo))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y��������")
		AddQuestText(sceneId, "δ���");

		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (100 * 3 * level * 20*1*1 )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus> 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		--2 �﹩
		if x300827_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300827_g_BonusMoney8)
		end
		--3 ��ᾭ��
		-- if x300827_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300827_g_GuildExpBonus)
		-- end
		--AddQuestText(sceneId,"��Ṧ�£�1�� ")
	--������ʾ��Ϣ
	EndQuestEvent(sceneId)
	DispatchQuestDemandInfo(sceneId, selfId, targetId, x300827_g_ScriptId, MissionId,0);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300827_DispatchMissionInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x300827_g_MissionName)
		AddQuestText(sceneId,format("%s", x300827_g_MissionInfo))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y����Ŀ�꣺")
		AddQuestText( sceneId,format("%s", x300827_g_MissionTarget))
		AddQuestText( sceneId," ")

		--��ʾ��Ϣ
		if x300827_g_MissionHelp ~= "" then
			AddQuestText(sceneId,"#Y������ʾ��")
			AddQuestText(sceneId,format("%s", x300827_g_MissionHelp))
			AddQuestText(sceneId," ")
		end
			
		--1������
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (100 * 3 * level * 20*1*1 )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		--2 �﹩
		if x300827_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300827_g_BonusMoney8)
		end
		--3 ��ᾭ��
		-- if x300827_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300827_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300827_g_ScriptId, MissionId);
end


---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300827_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
 
	local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	x300827_GetBonus( sceneId,selfId, isMultiple )
end

function x300827_GetBonus( sceneId, selfId, isMultiple )

	--��������
	local level = GetLevel(sceneId, selfId)
	--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
	local ExpBonus = ceil (100 * 3 * level * 20*1*1 )
	ExpBonus =floor(ExpBonus+0.5)
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--�õ���������(�ȼ�) 
    if ExpBonus > 0 then
    		local text1 = "����������񣺡���᡿�ռ���ľ"
			local text2 = "���#R����"..ExpBonus.."��#o�Ľ���"
			--local text3 = "���#R��Ṧ��1��#o�Ľ���"
			--AddGuildMerit(sceneId, selfId,1);
			AddExp(sceneId, selfId, ExpBonus);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, text1);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, text2);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId, text3);
			-- EndQuestEvent(sceneId)
			-- DispatchQuestTips(sceneId,selfId)
	  		Msg2Player(sceneId,selfId,text1,8,2)
	  		Msg2Player(sceneId,selfId,text2,8,2)
			--Msg2Player(sceneId,selfId,text3,8,2)
		if isMultiple == 1 then
			local ExpBonus1 = ceil (100 * 3 * level * 20*1*1 *3)
			local Exp3 = ceil (100 * 3 * level * 20*1*1*3 )
			local ExpBonus2 = ceil (100 * 3 * level * 20*1*1 *2)
			local pos = GetGuildOfficial(sceneId, selfId)
			local text3 = "���#Rʹ����2��#o�Ľ���"
				AddGuildShiMing(sceneId, selfId,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, text3);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,text3,8,2)
			if pos == 5 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "����ְλֻ����ȡһ���ռ����");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"����ְλֻ����ȡһ���ռ����",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus1);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..Exp3.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"���౶���������#R����"..Exp3.."��#o�Ľ���",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			elseif pos == 4 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������ְλֻ����ȡһ���ռ����");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"������ְλֻ����ȡһ���ռ����",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus2);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..ExpBonus2.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"���౶���������#R����"..ExpBonus2.."��#o�Ľ���",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			else
				AddExp(sceneId, selfId, ExpBonus);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������#R����"..ExpBonus.."��#o�Ľ���");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"���౶���������#R����"..ExpBonus.."��#o�Ľ���",8,2)
			end
		end
		if 	GuildLevel == 2 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*0.25*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"���ȼ�2��������#R����"..exp.."��#o�Ľ���",8,2)
		end
		if 	GuildLevel == 3 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*0.5*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"���ȼ�3��������#R����"..exp.."��#o�Ľ���",8,2)
		end
		if 	GuildLevel == 4 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*0.75*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"���ȼ�4��������#R����"..exp.."��#o�Ľ���",8,2)
		end
		if 	GuildLevel == 5 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 20*1*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"���ȼ�5��������#R����"..exp.."��#o�Ľ���",8,2)
		end
	end
--�����ﹱ
    if x300827_g_BonusMoney8 > 0 then
		    AddGuildUserPoint(sceneId,selfId,x300827_g_BonusMoney8)	--���Ӱﹱ
			local BonusMoney8 = x300827_g_BonusMoney8
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R�ﹱ"..BonusMoney8.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("���#R�ﹱ"..BonusMoney8.."��#o�Ľ���", x300827_g_BonusMoney8),8,2)
			if isMultiple == 1 then
			local pos = GetGuildOfficial(sceneId, selfId)
				if pos == 5 then
					local guildid =GetGuildID(sceneId, selfId)
					if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "����ְλֻ����ȡһ���ռ����");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
						Msg2Player(sceneId,selfId,"����ְλֻ����ȡһ���ռ����",8,2)
					else
						AddGuildUserPoint(sceneId,selfId,150)	--���Ӱﹱ
						local BonusMoney8 = x300827_g_BonusMoney8
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "������#R�ﹱ150��#o�Ľ���");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ150��#o�Ľ���",8,2)
						SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
					end
				elseif pos == 4 then
					local guildid =GetGuildID(sceneId, selfId)
					if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "������ְλֻ����ȡһ���ռ����");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
						Msg2Player(sceneId,selfId,"������ְλֻ����ȡһ���ռ����",8,2)
					else
						AddGuildUserPoint(sceneId,selfId,100)	--���Ӱﹱ
						local BonusMoney8 = x300827_g_BonusMoney8
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "������#R�ﹱ100��#o�Ľ���");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ100��#o�Ľ���",8,2)
						SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
					end
				else
					AddGuildUserPoint(sceneId,selfId,50)	--���Ӱﹱ
					local BonusMoney8 = x300827_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R�ﹱ"..BonusMoney8.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���౶���������#R�ﹱ"..BonusMoney8.."��#o�Ľ���", x300827_g_BonusMoney8),8,2)
				end
			end
	end
	-- ������ᾭ��
	-- local bangExp = x300827_g_BangExp 
	-- if bangExp > 0 then
		-- local gongde = GetGuildMerit(sceneId, selfId)
		-- if 	gongde >= 5 then
			-- AddGuildExp(sceneId,selfId,bangExp)
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId, "���#R��ᾭ��"..bangExp.."��#o�Ľ���");
			-- EndQuestEvent(sceneId)
			-- DispatchQuestTips(sceneId,selfId)			
			-- Msg2Player(sceneId,selfId,format("���#R��ᾭ��"..bangExp.."��#o�Ľ���"),8,2)
		-- else
			-- BeginQuestEvent(sceneId)
			-- AddQuestText( sceneId, "�ܱ�Ǹ����Ṧ�µ���5�㣬���ܻ�ð�ᾭ�顣" )
			-- EndQuestEvent( sceneId )
			-- DispatchQuestTips( sceneId, memberId )
			-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ����Ṧ�µ���5�㣬���ܻ�ð�ᾭ�顣",8,2)
		-- end
	-- end

end


--**********************************
--����
--**********************************
function x300827_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ɽ�������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if GetGuildID( sceneId, selfId ) == -1 then
		--���ڰ����
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�㲻�ǰ���Ա");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�㲻�ǰ���Ա",8,2)
		return
	end
	local guildid = GetGuildID( sceneId, selfId )
	local GuildLevel = GetGuildSimpleData(guildid)--�õ���������(�ȼ�)
	if 	GuildLevel < 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ȼ�����2���ſ��Խ�ȡ����᡿��ľ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ȼ�����2���ſ��Խ�ȡ����᡿��ľ����",8,2)
	return 
	end

 	local level = GetLevel(sceneId,selfId)
	if level < x300827_g_LevelLess then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��40���Ժ���ܽ�ȡ����᡿��ľ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ��40���Ժ���ܽ�ȡ����᡿��ľ����"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end
		

	if x300827_GetDayCount(sceneId, selfId) >= x300827_g_Mis_Count then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "������Ѿ���ȡ������᡿��ľ�ˣ������������ɣ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "������Ѿ���ȡ������᡿��ľ�ˣ������������ɣ�"
		Msg2Player(sceneId,selfId,Readme,8,2)
		DispatchQuestTips(sceneId,selfId)
		--DispatchQuestEventList(sceneId, selfId, -1)
		return
	end
	
   --GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_GATHER_ISSUE_TIME, x300827_g_ScriptId,MissionId,"OnReturn")
   
   --���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end

	if AddQuestNM( sceneId, selfId,MissionId) == 1 then
		
		--������д��־
		GamePlayScriptLog(sceneId,selfId,124)

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "����������񣺡���᡿�ռ���ľ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "����������񣺡���᡿�ռ���ľ"
		Msg2Player(sceneId,selfId,Readme,8,2)
		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		--SetPlayerAbilityLevel(sceneId, selfId, 26, 1)
	end

      
end


--�������
--����1����ɹ���0��������ʧ��
function x300827_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
     
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end
	
	if DelQuestNM( sceneId, selfId, MissionId) < 1 then
		return 
	end

	

--	local level = GetLevel(sceneId, selfId)
--	local ExpBonus = ceil (1000 * 0.3 * level * 20 )
--	BeginQuestEvent(sceneId)
--	AddQuestText(sceneId, "���ɫ��������ռ���ľ���������ˣ�#r���飺#R"..ExpBonus.."#o��#r�ﹱ��#R%d#W#o��");
--	EndQuestEvent(sceneId)
--	DispatchQuestTips(sceneId,selfId)
				
	--������д��־
	GamePlayScriptLog(sceneId,selfId,102)

	x300827_SetDayCount(sceneId, selfId)
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_HEIMU, x300827_g_ScriptId,MissionId,"OnReturn1",targetId)
	
	-- local GuildUser = 50
	-- AddGuildUserPoint(sceneId, selfId, GuildUser)
	--AddGuildUserPoint(sceneId,selfId,40)	--���Ӱﹱ
	return 0
end


function x300827_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end

	if npcGuid == x300827_g_SubmitNPCGUID then
		local state = GetQuestStateNM(sceneId,selfId,npcId,MissionId)
		AddQuestNumText(sceneId, MissionId, x300827_g_MissionName,7,state);
	end

end

 
--********************************************************************
--����
--********************************************************************
function x300827_ProcQuestAbandon( sceneId, selfId,MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
	DelQuestNM( sceneId, selfId, MissionId)
	local Readme = "����������񣺡���᡿�ռ���ľ"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
    EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)
	x300827_SetDayCount(sceneId, selfId)
end


function x300827_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()						--��ǰʱ��(��)

	if MissionData == CurDaytime then					--�ϴη�����ʱ���ǽ���
 		--����������
 			--��ֹ��Ҳ���ɼ��������,playertemplate���ƺ󣬿��Բ���Ҫ�˶�
	--else
	    --BeginQuestEvent(sceneId)
		--AddQuestText(sceneId, "�����컹û�з���������")
		--EndQuestEvent(sceneId)
		--DispatchQuestTips(sceneId,selfId)
		--local Readme = "�����컹û�з���������"
		--Msg2Player(sceneId,selfId,Readme,8,2)
		--DispatchQuestTips(sceneId,selfId)
	end
	
--	DispatchQuestEventList(sceneId, selfId, -1)

end


--********************************************************************
--����
--********************************************************************
function x300827_ProcAccept( sceneId, selfId )

end

--��Ʒ�ı�
function x300827_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType )

    if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end

						   --����ID, �Լ���ID, ��Ʒ�ú�,  ����ID
  	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if nChangeType ==1 then
		--ɾ������
		local itemNum = GetItemCount( sceneId, selfId, itemdataId )
		if itemNum < NeedNum then
	       		SetQuestByIndex( sceneId, selfId, misIndex, 0, itemNum )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			x300827_QuestLogRefresh( sceneId, selfId, MissionId );
		end

		return

	end
	
	if NeedNum > 0 then
      	local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum and Num > 0 then --��û���������
			BeginQuestEvent(sceneId)
			local strText = format("�ѵõ�@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			x300827_QuestLogRefresh( sceneId, selfId, MissionId );
  		elseif Num == NeedNum then
			--�Ѿ��������
			BeginQuestEvent(sceneId)
			local strText = format( "�ѵõ��㹻��@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			x300827_QuestLogRefresh( sceneId, selfId, MissionId );


		end
	end

end



---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300827_QuestLogRefresh( sceneId, selfId, MissionId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
	if bHaveMission > 0 then
	
		BeginQuestEvent(sceneId)
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (100 * 3 * level * 20*1*1*1)
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus > 0 then
		AddQuestExpBonus(sceneId, ExpBonus);		
		end
		if x300827_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300827_g_BonusMoney8 )	--���Ӱﹱ
		end
		--3 ��ᾭ��
		-- if x300827_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300827_g_GuildExpBonus)
		-- end

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		local num = GetQuestParam(sceneId, selfId,misIndex,0)
		local text = format("(%d/%d)",num,5)

		AddQuestLogCustomText( sceneId,
								"",								-- ����
								x300827_g_MissionName,			-- ��������
								x300827_g_MissionTarget..text,	--����Ŀ��
								x300827_g_NPCName,				--����NPC
								x300827_g_MissionRuse,			--������
								x300827_g_MissionInfo,			--��������
								""								--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	end

end

function x300827_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300827_QuestLogRefresh( sceneId, selfId, MissionId );
end


---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x300827_GetDayCount(sceneId, selfId)

	if x300827_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_GUILD_GATHER_DATE[1], MD_GUILD_GATHER_DATE[2], MD_GUILD_GATHER_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_GUILD_GATHER_COUNT[1], MD_GUILD_GATHER_COUNT[2], MD_GUILD_GATHER_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300827_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_GATHER_DATE[1], MD_GUILD_GATHER_DATE[2], MD_GUILD_GATHER_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_GUILD_GATHER_DATE[1], MD_GUILD_GATHER_DATE[2], MD_GUILD_GATHER_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_GATHER_COUNT[1], MD_GUILD_GATHER_COUNT[2], MD_GUILD_GATHER_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_GUILD_GATHER_COUNT[1], MD_GUILD_GATHER_COUNT[2], MD_GUILD_GATHER_COUNT[3])
		SetQuestData(sceneId, selfId, MD_GUILD_GATHER_COUNT[1], MD_GUILD_GATHER_COUNT[2], MD_GUILD_GATHER_COUNT[3], daycount+1)
	end
end