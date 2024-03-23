--���ܣ������������ͻ�콱�ű����ж��� 09 1125-1127

x350006_g_ScriptId = 350006
x350006_g_MissionName = "��ȡ�������"
x350006_g_MissionDay = {	{ day=1125,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1126,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=1127,min = 1200,	max = 1320,	flag=3}
												}
x350006_g_MissionDayTest = {	{ day=1121,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1122,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=1123,min = 1200,	max = 1320,	flag=3}
												}
x350006_g_MissionReadme = "\t�ڸж����ڼ䣬Ϊ���Թ����ҵĸ�л��ף�����ж����ڼ䡾��11��21����11��23�ա�ÿ�����8����10��׶ζ��������ִ�������콱��ʹ����ȡ�������������\n\t��ʱ����30�����ϵ���Ҷ����Ի�ý������1��������׼ʱ��ȡ��\n\t���˶�࣬��Ī��ʧ������"
x350006_g_MissionReadme1 = "\t�ڸж����ڼ䣬Ϊ���Թ����ҵĸ�л��ף�����ж����ڼ䡾��11��25����11��27�ա�ÿ�����8����10��׶ζ��������ִ�������콱��ʹ����ȡ�������������\n\t��ʱ����30�����ϵ���Ҷ����Ի�ý������1��������׼ʱ��ȡ��\n\t���˶�࣬��Ī��ʧ������"
x350006_g_MissionReadme2 = "\t���������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ��ʱ������������ȡ��1���������������׼ʱ��ȡ��"
x350006_g_MissionReadme3 = "\t���Ѿ���ȡ�˽���Ľ��������\n\t���������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ��ʱ������������ȡ��1���������������׼ʱ��ȡ��"
x350006_g_LevelMin				= 30
x350006_g_RandomItemBonus		=	 12030421


--Ψһ��ȫ�ֱ���
x350006_g_MD					= MD_GANEN


function x350006_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if GetTestServerToggle() == 1 then	--���
		if nLevel >= x350006_g_LevelMin then			
			for i,item in x350006_g_MissionDayTest do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	else	--����
		if nLevel >= x350006_g_LevelMin then			
			for i,item in x350006_g_MissionDay do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	end

--	if nLevel >= x350006_g_LevelMin then			
--		for i,item in x350006_g_MissionDay do
--			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
--				return item.flag
--			end
--		end	
--	end
		
	return 0
	
end

function x350006_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350006_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--������ں���

--**********************************

function x350006_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	--check invalid
	local nIndex = x350006_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350006_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
			if GetTestServerToggle() == 1 then
				-- not get bouns
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
					AddQuestText(sceneId,x350006_g_MissionReadme)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350006_g_ScriptId, x350006_g_ScriptId)			
			else
				-- not get bouns
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
					AddQuestText(sceneId,x350006_g_MissionReadme1)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350006_g_ScriptId, x350006_g_ScriptId)			
			end
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350006_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350006_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350006_CheckMD( sceneId,selfId )

	local nIndex = x350006_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350006_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350006_g_LevelMin then

	if GetTestServerToggle() == 1 then
		for i,item in x350006_g_MissionDayTest do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
					return
				end
			end
		end
	else
		for i,item in x350006_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
	
--		for i,item in x350006_g_MissionDay do
--			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
--				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
--					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
--					return
--				end
--			end
--		end
	end
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350006_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if GetTestServerToggle() == 1 then
		for i,item in x350006_g_MissionDayTest do
			if item.day == nDay then
				return 1
			end
		end
	else
		for i,item in x350006_g_MissionDay do
			if item.day == nDay then
				return 1
			end
		end
	end
	
--	for i,item in x350006_g_MissionDay do
--		if item.day == nDay then
--			return 1
--		end
--	end
	
	return 0

end

--**********************************

--���轱��

--**********************************

function x350006_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 then
		--�̶���Ʒ�����		
		BeginAddItem( sceneId )
			AddBindItem( sceneId,x350006_g_RandomItemBonus, 1 )	
			
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
				AddQuestText(sceneId,x350006_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350006_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 then
		
		BeginAddItem( sceneId )
		--�̶���Ʒ�����		
			AddBindItem( sceneId,x350006_g_RandomItemBonus, 1 )	

		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
				AddQuestText(sceneId,x350006_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350006_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--�о��¼�

--**********************************

function x350006_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350006_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350006_g_ScriptId, x350006_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--����������

--**********************************

function x350006_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--�����ȷ����
function x350006_ProcAccept( sceneId, selfId, NPCId )

	x350006_CheckMD( sceneId,selfId )
	
end



--**********************************

--����

--**********************************

function x350006_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x350006_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x350006_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x350006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x350006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x350006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
