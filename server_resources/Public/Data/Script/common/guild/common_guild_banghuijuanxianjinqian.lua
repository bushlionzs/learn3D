
x300634_g_ScriptId = 300634


--�����ı�����
x300634_g_MissionName="����᡿���ļ��"




--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300634_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	if GetGuildOfficial(sceneId, selfId) ~= -1 then--�ж��Ƿ������
	
		local level = GetLevel( sceneId, selfId )	
		local localexp = 0
			if  level < 70 then
				 localexp = level * 20000
			elseif level >= 70 and level < 80 then
				 localexp = level * 36000
			elseif level >= 80 and level < 90 then
				 localexp = level * 36000*2
			elseif level >= 90 and level < 200 then
				 localexp = level * 36000*2.6
			end
		local Readme_1 = "#Y����᡿���ļ��#W#r"
		
		local Readme_2 = "\t������ͨ������һ��".."#Gļ��ȯ".."#W".."������".."#G2���ᾭ�飬20������Ǯ".."#Wͬʱ��Ҳ������".."#G"..localexp.."�㾭��#W��#G100��ﹱ#W��#G1��ʹ����#W������������#Gļ����#Wʱ2Сʱ�ھ���ļ��ȯ�ɻ�÷���������"
		
		local Readme_3 = "#r#Y���Ƿ�Ҫ������ļ��?"
		
		local Readme = Readme_1 .. Readme_2..Readme_3
				
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x300634_g_ScriptId, -1 );
	
	end

end

--**********************************
--�о��¼�
--**********************************
function x300634_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--����������
--**********************************
function x300634_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300634_ProcAccept( sceneId, selfId )

	if GetGuildOfficial(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ļ��ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ǰ���Ա���޷����а��ļ����",8,2)
		return
	end
	
	if  GetItemCount( sceneId, selfId, 11990110 ) < 1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ļ��ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������û��ļ��ȯ�����ļ��ʧ�ܣ�",8,2)		
		return
	end
	
	if x300634_CanCashBuild(sceneId,selfId)==0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ļ��ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ÿ��ֻ�ܽ���1�ΰ��ļ����������������",8,2)			
		return
	end
		
	-- ͨ����֤����ʼ�߼�����
	DelItem( sceneId, selfId, 11990110 ,1)			--���ֽ�
	Msg2Player(sceneId,selfId,"����᡿���ļ��:�۳�һ��ļ��ȯ",8,2)
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_MUJI, x300634_g_ScriptId,-1,"OnReturn1",-1)

    -- ���ӻ�Ծ��
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM4) )
    end
end
-- ����Ƿ�౶
function x300634_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	x300634_GetBonus( sceneId,selfId, isMultiple )
end
-- ������
function x300634_GetBonus( sceneId, selfId, isMultiple )
		local level =  GetLevel ( sceneId , selfId )
		local localexp = 0
			if  level < 70 then
				 localexp = level * 20000
			elseif level >= 70 and level < 80 then
				 localexp = level * 36000
			elseif level >= 80 and level < 90 then
				 localexp = level * 36000*2
			elseif level >= 90 and level < 200 then
				 localexp = level * 36000*2.6
			end
			AddExp ( sceneId , selfId , localexp )			--�Ӹ��˾���
			AddGuildExp(sceneId, selfId, 2)			--�Ӱ�ᾭ��
			AddGuildUserPoint(sceneId, selfId, 100 )		--���Ӹ��˰ﹱ
			AddGuildShiMing(sceneId, selfId, 1 ) --��ʹ����
			--AddGuildMerit (sceneId, selfId, 4 )  --�Ӱ�Ṧ��
			AddGuildMoney (sceneId, selfId, 20000 ) --�Ӱ���Ǯ
			Msg2Player(sceneId,selfId,"����᡿���ļ��:���#R����"..localexp.."��#o�Ľ���",8,2)
			Msg2Player(sceneId,selfId,"����᡿���ļ��:���#R�ﹱ100��#o�Ľ���",8,2)
			Msg2Player(sceneId,selfId,"���#R����"..localexp.."��#o�Ľ���",8,3)
			Msg2Player(sceneId,selfId,"���#R�ﹱ100��#o�Ľ���",8,3)				
			--Msg2Player(sceneId,selfId,"����᡿���ļ��:��ð�Ṧ��4��",8,2)	
			Msg2Player( sceneId, selfId, (GetName(sceneId, selfId)).."����������һ��ļ��ȯ��ʹ��ᾭ�������2�㣬���ʹ���������1�㣬����Ǯ����20����", 6 )		--���㲥
	if isMultiple == 1 then
	    local level = GetLevel ( sceneId , selfId )
		local pos = GetGuildOfficial(sceneId, selfId)
		local localexp1 = localexp*3
		local exp = localexp*2
		local exp1 = localexp*1
		local guildid =GetGuildID(sceneId, selfId)
		if pos ==5 then
			if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "����ְλֻ����ȡһ��ļ�����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"����ְλֻ����ȡһ��ļ�����",8,2)
				return
			end		
			
			AddExp ( sceneId , selfId , localexp1 )
			AddGuildUserPoint(sceneId, selfId, 300 )
			Msg2Player(sceneId,selfId,"����᡿���ļ��:���౶������#R����"..localexp1.."��#o#r����᡿���ļ��:���౶������#R�ﹱ300��#o",8,2)
			SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
		
		elseif pos ==4 then
			if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "������ְλֻ����ȡһ��ļ�����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"������ְλֻ����ȡһ��ļ�����",8,2)
				return
			end		
			
			AddExp ( sceneId , selfId , exp )
			AddGuildUserPoint(sceneId, selfId, 200 )
			Msg2Player(sceneId,selfId,"����᡿���ļ��:���౶������#R����"..exp.."#o��#r����᡿���ļ��:���౶������#R�ﹱ200��#o",8,2)
			SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
		
		else
		AddExp ( sceneId , selfId , exp1 )
		AddGuildUserPoint(sceneId, selfId, 100 )
		Msg2Player(sceneId,selfId,"����᡿���ļ��:���౶������#R����"..exp1.."��#o#r����᡿���ļ��:���౶������#R�ﹱ100��#o",8,2)
		end
	end
end

--**********************************
--����
--**********************************
function x300634_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300634_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300634_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300634_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300634_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300634_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300634_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


--**********************************
--�ж��Ƿ��ܹ������ֽ���
--**********************************
function x300634_CanCashBuild( sceneId, selfId )
	
	local bSuc = 0
	local day_human
	local count_human
	local day_cur = GetDayTime()

	-- ȡ����
	day_human,count_human = GuildGetCashBuildTimes(sceneId, selfId)
	
	if day_cur ~= day_human then
		count_human = 1
		bSuc = 1
	elseif count_human < 1 then
		count_human = count_human + 1
		bSuc = 1
	else
		bSuc = 0
	end
	
	-- ����ˢ��ȥ
	if bSuc==1 then
		GuildSetCashBuildTimes(sceneId, selfId, day_cur, count_human )
	end
	
	return bSuc
	
end
