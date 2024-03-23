x300836_g_ScriptId = 300836
x300836_g_MissionName = "����᡿���񷢲�"
x300836_g_MissionInfo = {
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_HUSHOU,
								name="����᡿������",
								Readme="#Y����᡿���񷢲�#r#W\t��������᡿��������ݰ��ȼ���ͬ��Ҫ����������ͬ��#Y����Ǯ#W�������ȷ����������᡿������޶౶������������г�Ա��#R2Сʱ��#W��ɵ��졾��᡿�����������ʱ��������#G2������Ͱﹱ#W���������#G4������Ͱﹱ#W�����������#G3������Ͱﹱ#W��#r",
								money = {1120000,1490000,1860000,2790000,3130000,3130000,3130000,3130000,3130000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_HEIMU,
								name="����᡿ͼ����",
								Readme="#Y����᡿���񷢲�#r#W\t��������᡿ͼ������ݰ��ȼ���ͬ��Ҫ����������ͬ��#Y����Ǯ#W�������ȷ����������᡿���ͼ�ڶ౶������������г�Ա��#R2Сʱ��#W��ɵ��졾��᡿���ͼ������ʱ��������#G2������Ͱﹱ#W���������#G4������Ͱﹱ#W�����������#G3������Ͱﹱ#W��#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_ANZHAN,
								name="����᡿��ս��",
								Readme="#Y����᡿���񷢲�#r#W\t��������᡿��ᰵս����ݰ��ȼ���ͬ��Ҫ����������ͬ��#Y����Ǯ#W�������ȷ����������᡿��ᰵս�౶������������г�Ա��#R2Сʱ��#W��ɵ��졾��᡿��ᰵս����ʱ��������#G2������Ͱﹱ#W���������#G4������Ͱﹱ#W�����������#G3������Ͱﹱ#W��#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_CHUYAO,
								name="����᡿��ħ��",
								Readme="#Y����᡿���񷢲�#r#W\t��������᡿��ħ����ݰ��ȼ���ͬ��Ҫ����������ͬ��#Y����Ǯ#W�������ȷ����������᡿����ħ�౶������������г�Ա��#R2Сʱ��#W��ɵ��졾��᡿����ħ����ʱ��������#G2������Ͱﹱ#W���������#G4������Ͱﹱ#W�����������#G3������Ͱﹱ#W��#r",
								money = {896000,1192000,1488000,2232000,2504000,2504000,2504000,2504000,2504000,}
							},
							
							{ 
								id=GD_GUILD_INDEX_MULTI_MISSION_MUJI,
								name="����᡿ļ����",
								Readme="#Y����᡿���񷢲�#r#W\t��������᡿ļ������ݰ��ȼ���ͬ��Ҫ����������ͬ��#Y����Ǯ#W�������ȷ����������᡿���ļ���౶������������г�Ա��#R2Сʱ��#W�ύ����᡿���ļ��ʱ��������#G2������Ͱﹱ#W���������#G4������Ͱﹱ#W�����������#G3������Ͱﹱ#W��#r",
								money = {560000,745000,930000,1395000,1565000,1565000,1565000,1565000,1565000,}
							},
						}


x300836_g_ElapseTime = 2*60*60	--�౶�������ʱ�䣬2 Сʱ

--�����NPC��
function x300836_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGuildID( sceneId, selfId ) == -1 then
 		--���ڰ����
		return
	end
	
	AddQuestNumText(sceneId,300836,x300836_g_MissionName,8,0)


end

--�������ť������������ִ�д˽ű�
function x300836_ProcEventEntry( sceneId, selfId, targetId,state,index)

	if index == 0 then
		local Readme = "#Y����᡿���񷢲�#r#W\t�𾴵İ�������#G3�����#W���ϰ��������������﷢����������#Gÿ����22��ǰ#Wֻ�ܽ���#Gһ��#W���񷢲���������ѡ�����°�ť���������౶����"
		local guildid = GetGuildID(sceneId,selfId)
		BeginQuestEvent(sceneId);
		for i,item in x300836_g_MissionInfo do
			if GetGuildCacheFreeParam(guildid,item.id) == -1 then
				AddQuestNumText(sceneId,300836,item.name.."(δ����)",3,item.id)
			else
				AddQuestNumText(sceneId,300836,item.name.."(�ѷ���)",3,item.id)
			end
		end	
		AddQuestText(sceneId,Readme);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif index < 100 then
		for i,item in x300836_g_MissionInfo do
			if item.id == index then
				 Readme = item.Readme			
				break
			end
		end
		
		local money = x300836_GetDeductMoneyNum(sceneId, selfId,index)
		local ding = floor( money / (1000*1000) )
		local liang = floor( mod(money,1000*1000)/ 1000 )
		local wen = mod(money,1000)
		
		local str = format("#Y��Ҫ���İ���Ǯ��%d��%d��%d��",ding,liang,wen)		
		BeginQuestEvent(sceneId);
		AddQuestNumText(sceneId,300836,"ȷ��..",3,index+100)
		AddQuestText(sceneId,Readme);
		AddQuestText(sceneId,str);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	else
		if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ��ֻ�а����������������ܷ�����������");
				DispatchQuestTips(sceneId,selfId)	
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ�а����������������ܷ�����������",8,2)
			return
		end
		local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--�õ���������(�ȼ�) 
		if GuildLevel <3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����İ��ȼ�����3����");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����İ��ȼ�����3����",8,2)
			return
		end
		local hour,minute,second = GetHourMinSec()
		if ( hour < 22) then
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ������22��00ǰ������������");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ������22��00ǰ������������",8,2)
			return 
		end
			
		-- �ж�Ǯ�Ƿ��㹻
		local op = index - 100
		GetGuildQuestData(sceneId,selfId,GD_GUILD_INDEX_MULTI_MISSION_TODAY,x300836_g_ScriptId,op,"OnReturn1")
	end
	
end

function x300836_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	local op = MissionId
	if MissionData~=-1 then 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����ѷ�����һ�������������ٷ���");
		DispatchQuestTips(sceneId,selfId)	
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������ѷ�����һ�������������ٷ���",8,2)
		return	
	end
	
	GetGuildQuestData(sceneId,selfId,op,x300836_g_ScriptId,op,"OnReturn2")		
	
end

function x300836_OnReturn2(sceneId, selfId,MissionData,MissionId,targetId)
	if MissionData ~= -1 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ѷ�����������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)		
		return
	end
	local op = MissionId
	local money = x300836_GetDeductMoneyNum(sceneId, selfId,op)
		if GetGuildMoney(sceneId, selfId) < money then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��������ڵİ���Ǯ���㣡");
			DispatchQuestTips(sceneId,selfId)	
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ڵİ���Ǯ���㣡",8,2)
			return
		end
	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	local guildid = GetGuildID(sceneId,selfId)
	SetGuildQuestData(sceneId,guildid,op,GetCurrentTime())
	SetGuildQuestData(sceneId,guildid,GD_GUILD_INDEX_MULTI_MISSION_TODAY,op)
	local Readme = ""
	BeginQuestEvent(sceneId)

	for i,item in x300836_g_MissionInfo do
		if item.id == op then
		Readme = item.name			
		break
		end
	end

	AddQuestText(sceneId, "���ɹ�������"..Readme.."�౶����");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	Msg2Player(sceneId,selfId,"��������������������"..Readme.."�౶����2Сʱ�ڻظ�������˫��������",6,2)
	SubGuildMoney(sceneId, selfId,money)
end

function x300836_GetDeductMoneyNum(sceneId,selfId,MissionType)

	local GuildLevel,xx1,xx2 = GetGuildSimpleData(GetGuildID(sceneId, selfId))
	for i,item in x300836_g_MissionInfo do
		if item.id == MissionType then
			return item.money[GuildLevel];
		end
	end
	
	
	return -1;
end


--�����ȷ����
function x300836_ProcQuestAccept( sceneId, selfId, targetId )
	
end

--**********************************
--����
--**********************************
function x300836_ProcAccept( sceneId, selfId )
	
	if GetGuildOfficial(sceneId, selfId) ~= 5 and GetGuildOfficial(sceneId, selfId) ~= 4 then
		return
	end
	
	GetGuildQuestData(sceneId, selfId,-1,x300836_g_ScriptId)
end

--**********************************
--����
--**********************************
function x300836_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300836_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300836_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300836_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300836_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300836_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300836_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end