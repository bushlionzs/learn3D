--���ܣ������������ͻ�콱�ű�

x350004_g_ScriptId = 350004
x350004_g_MissionName = "��ȡ�������"
x350004_g_MissionDay = {	{ day=1001,min = 1200,	max = 1320,	flag=1},--20*60 22*60
							{ day=1002,min = 1200,	max = 1320,	flag=2},--20*60 22*60
							{ day=1003,min = 1200,	max = 1320,	flag=3},
							{ day=1004,min = 1200,	max = 1320,	flag=4},
							{ day=1005,min = 1200,	max = 1320,	flag=5},
							{ day=1006,min = 1200,	max = 1320,	flag=6},
							{ day=1007,min = 1200,	max = 1320,	flag=7},
							{ day=1008,min = 1200,	max = 1320,	flag=8}
						}
x350004_g_MissionReadme1 = "\t����ʮ�������ϡ��Ϲ�ʯ�������̡�����ѽ����ҹ��Ĵ�ͳ���գ��±���Ϊ�������ʳ֮һ�������źϼ���Բ�������Ҹ���Ϊ���Թ����ҵĸ�л��ף������������ڼ䡾��10��1����10��8�ա�ÿ�����8����10��׶ζ��������ִ�������콱��ʹ����ȡ�������������\n\t��ʱ����30�����ϵ���Ҷ����Ի��һ���������±���ͬʱҲ�л������̳ǵ��ߣ�����׼ʱ��ȡ��\n\t���˶�࣬��Ī��ʧ������"
x350004_g_MissionReadme2 = "\t���ɼ�˼�������������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ��ʱ������������ȡ��һֻ�������ʱ����30�����ϵ���Ҷ����Ի��һ���������±���ͬʱҲ�л������̳ǵ��ߣ�����׼ʱ��ȡ��"
x350004_g_MissionReadme3 = "\t���Ѿ���ȡ�˽�������������\n\t���ɼ�˼�������������ÿ��#G20:00#W��#G22:00#W����ȡ��ÿ������������ȡ��һֻ�������ʱ����30�����ϵ���Ҷ����Ի��һ���������±���ͬʱҲ�л������̳ǵ��ߣ�����׼ʱ��ȡ��"

x350004_g_LevelMin				= 30
x350004_g_RandomItemBonus		=	{
										{id=12030201,rnd=10,num=1},
										{id=12041101,rnd=30,num=1},
										{id=11970021,rnd=20,num=1},
										{id=12054300,rnd=20,num=1},
										{id=12030209,rnd=5,num=1},
										{id=12010020,rnd=5,num=1},
										{id=12041103,rnd=5,num=1},
										{id=12030200,rnd=5,num=1},
									}


--Ψһ��ȫ�ֱ���
x350004_g_MD					= MD_ZHONGQIU


function x350004_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if nLevel >= x350004_g_LevelMin then			
		for i,item in x350004_g_MissionDay do
			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
				return item.flag
			end
		end	
	end
		
	return 0
	
end

function x350004_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350004_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--���̶���Ʒ

--**********************************
function x350004_Yuebing(sceneId,selfId)
	
	local nLevel = GetLevel(sceneId,selfId)
	local yuebing = -1
	if nLevel < 40  then
		yuebing = 12030251
	elseif nLevel >=40 and nLevel < 50 then
		yuebing = 12030252
	elseif nLevel >=50 and nLevel < 60 then	
		yuebing = 12030253
	elseif nLevel >=60 and nLevel < 70 then
		yuebing = 12030254
	elseif nLevel >=70 and nLevel < 80 then
		yuebing = 12030255
	elseif nLevel >=80 and nLevel < 90 then
		yuebing = 12030256
	elseif nLevel >=90 and nLevel < 100 then
		yuebing = 12030257
	end
	
	return yuebing

end

--**********************************

--�������Ʒ

--**********************************
function x350004_GetRandomBonus()
	
	local nMaxRandom = -1
	local nCurIndex = -1
	for i,item in x350004_g_RandomItemBonus do
		
		local rnd = random(1,item.rnd)
		
		if rnd > nMaxRandom then
			nMaxRandom = rnd
			nCurIndex = i
		end
	end
	
	--���ʧ�ܵ����,��Ը�������,������
	if nCurIndex == -1 then
		return -1
	end
	
	local n = getn(x350004_g_RandomItemBonus)
	if nCurIndex < 1 or nCurIndex > n then
		return -1
	end
	
	--�����ȷ�����
	return x350004_g_RandomItemBonus[nCurIndex].id,x350004_g_RandomItemBonus[nCurIndex].num
	
end

--**********************************

--������ں���

--**********************************

function x350004_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	--check invalid
	local nIndex = x350004_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350004_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then

			-- not get bouns
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme1)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x350004_g_ScriptId, x350004_g_ScriptId)
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350004_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350004_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350004_CheckMD( sceneId,selfId )

	local nIndex = x350004_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350004_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350004_g_LevelMin then
		for i,item in x350004_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350004_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350004_g_MD[item.flag][1],x350004_g_MD[item.flag][2],x350004_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350004_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day
	
	for i,item in x350004_g_MissionDay do
		if item.day == nDay then
			return 1
		end
	end
	
	return 0

end

--**********************************

--���轱��

--**********************************

function x350004_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 then
		
		BeginAddItem( sceneId )
		
		--�����Ʒ�����
		local nRandItem,nRandItemNum = x350004_GetRandomBonus()
		if nRandItem ~= -1 then
			AddBindItem( sceneId,nRandItem, nRandItemNum )	
		end
		
		--�̶���Ʒ�����
		local yuebing = x350004_Yuebing(sceneId,selfId)	
		if yuebing ~= -1 then
			AddBindItem( sceneId,yuebing, random(2,4) )	
		end		
				
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350004_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 then
		
		BeginAddItem( sceneId )

		--�����Ʒ�����
		local nRandItem,nRandItemNum = x350004_GetRandomBonus()
		if nRandItem ~= -1 then
			AddBindItem( sceneId,nRandItem, nRandItemNum )	
		end
		
		--�̶���Ʒ�����
		local yuebing = x350004_Yuebing(sceneId,selfId)	
		if yuebing ~= -1 then
			AddBindItem( sceneId,yuebing, random(2,4) )	
		end		
		
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350004_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--�о��¼�

--**********************************

function x350004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350004_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350004_g_ScriptId, x350004_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--����������

--**********************************

function x350004_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--�����ȷ����
function x350004_ProcAccept( sceneId, selfId, NPCId )

	x350004_CheckMD( sceneId,selfId )
	
end



--**********************************

--����

--**********************************

function x350004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x350004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x350004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x350004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x350004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x350004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
