--���ܣ��칫���콱�ű�

x350001_g_ScriptId = 350001
x350001_g_MissionName = "��ȡ�칫�����"
x350001_g_MissionDay = {	{ day=718,min = 1200,	max = 1320,	flag = 1},--20*60 22*60
													{ day=719,min = 1200,	max = 1320,	flag = 2},--20*60 22*60
													{ day=720,min = 1200,	max = 1320,	flag = 3},
													{ day=721,min = 1200,	max = 1320,	flag = 4},
													{ day=722,min = 1200,	max = 1320,	flag = 5},
													{ day=723,min = 1200,	max = 1320,	flag = 6},
													{ day=724,min = 1200,	max = 1320,	flag = 7},
													{ day=725,min = 1200,	max = 1320,	flag = 8},
													{ day=726,min = 1200,	max = 1320,	flag = 9},
													{ day=727,min = 1200,	max = 1320,	flag = 10},
													{ day=728,min = 1200,	max = 1320,	flag = 11},
													{ day=729,min = 1200,	max = 1320,	flag = 12},
													{ day=730,min = 1200,	max = 1320,	flag = 13},
													{ day=731,min = 1200,	max = 1320,	flag = 14},
													{ day=801,min = 1200,	max = 1320,	flag = 15},
													{ day=802,min = 1200,	max = 1320,	flag = 16},
													{ day=803,min = 1200,	max = 1320,	flag = 17}
												}
x350001_g_MissionReadme1 = "\t���ɼ�˼��������7��17�ս��빫�����Խ׶Σ�Ϊ�˻�ӭ�����ҽ�����Ϸ�����������������������ף���⿪ʼһ�ܵ�ʱ���ÿ�����8����10��׶ζ��������ִ�������콱��ʹ����ȡ��ӭ�����������\n\t��ʱ����20�����ϵ���Ҷ����Ի��һ������ľ��齱����ͬʱҲ�л������̳ǵ��ߣ�\n\t���˶�࣬��Ī��ʧ������"
x350001_g_MissionReadme2 = "\t���ɼ�˼�����칫�������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ��ʱ������������ȡ��һֻ�������ʱ����20�����ϵ���Ҷ����Ի��һ������ľ��齱����ͬʱҲ�л������̳ǵ��ߣ�����׼ʱ��ȡ��"
x350001_g_MissionReadme3 = "\t���Ѿ���ȡ�˽�����칫�������\n\t���ɼ�˼�����칫�������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ��ʱ������������ȡ��һֻ�������ʱ����20�����ϵ���Ҷ����Ի��һ������ľ��齱����ͬʱҲ�л������̳ǵ��ߣ�����׼ʱ��ȡ��"
x350001_g_ItemBonus1			=	{{zhiye=-1,id=12030327,num=1}}
x350001_g_ItemBonus2			=	{{zhiye=-1,id=12030327,num=1}}
x350001_g_LevelMin			= 20


function x350001_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if nLevel >= x350001_g_LevelMin then			
		for i,item in x350001_g_MissionDay do
			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
				return item.flag
			end
		end	
	end
		
	return 0
	
end

function x350001_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in MD_GONGCE02_DATE do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--������ں���

--**********************************

function x350001_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	--check invalid
	local nIndex = x350001_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350001_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
		
			-- not get bouns
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350001_g_MissionName)
				AddQuestText(sceneId,x350001_g_MissionReadme1)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x350001_g_ScriptId, x350001_g_ScriptId)
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350001_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350001_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350001_CheckMD( sceneId,selfId )

	local nIndex = x350001_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in MD_GONGCE02_DATE do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350001_g_LevelMin then
		for i,item in x350001_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350001_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,MD_GONGCE02_DATE[item.flag][1],MD_GONGCE02_DATE[item.flag][2],MD_GONGCE02_DATE[item.flag][3],1)
					return
				end
			end
		end
	end
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350001_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day
	
	for i,item in x350001_g_MissionDay do
		if item.day == nDay then
			return 1
		end
	end
	
	return 0

end

--**********************************

--���轱��

--**********************************

function x350001_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 or flag == 9 or flag == 11 or flag == 13 or flag == 15 or flag ==17 then
		
		BeginAddItem( sceneId )
			for i,itm in x350001_g_ItemBonus1 do
				AddBindItem( sceneId, itm.id, itm.num )	
			end
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350001_g_MissionName)
				AddQuestText(sceneId,x350001_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350001_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 or flag == 10 or flag == 12 or flag == 14 or flag == 16 then
		
		BeginAddItem( sceneId )
			for i,itm in x350001_g_ItemBonus2 do
				AddBindItem( sceneId, itm.id, itm.num )	
			end
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350001_g_MissionName)
				AddQuestText(sceneId,x350001_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350001_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--�о��¼�

--**********************************

function x350001_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		if x350001_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350001_g_ScriptId, x350001_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--����������

--**********************************

function x350001_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--�����ȷ����
function x350001_ProcAccept( sceneId, selfId, NPCId )

	x350001_CheckMD( sceneId,selfId )
	
end



--**********************************

--����

--**********************************

function x350001_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x350001_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x350001_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x350001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x350001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x350001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end