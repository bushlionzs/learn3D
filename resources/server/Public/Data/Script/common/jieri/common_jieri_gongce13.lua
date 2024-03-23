--���ܣ���׷ֺ��콱�ű���12��15�մ��� 12��25�ջ 1��1��Ԫ���

x350012_g_ScriptId = 350012
x350012_g_MissionName = "��ȡ��׷ֺ�"
x350012_g_MissionDay = {	{ day=1218,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1225,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=0101,min = 1200,	max = 1320,	flag=3}
												}
x350012_g_MissionDayTest = {	{ day=1218,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1225,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=0101,min = 1200,	max = 1320,	flag=3}
												}
x350012_g_MissionReadme = "\t���ɼ�˼�������꡷����Ƭ��2009��12��18�չ������ԣ���л���ܹ�������һ�յ�֧�֡��ɼ�˼�����������ҳ������Ǹж���ֵ��������Ƭ����֮�ʣ�����10Ԫ�𿨵Ĵ���������������ǵ�һ�����⣬Ϊ������Ϸ֮�ô���������ˣ�\n\t12��18�����8����10��׶������������ִ�������콱��ʹ����ȡ��#R��׷ֺ�#W����\n\t��ʱ����#R60��#W���ϵ���Ҷ����Ի����׷ֺ�𿨺��������׼ʱ��ȡ��"
x350012_g_MissionReadme1 = "\t���ɼ�˼�������꡷����Ƭ��2009��12��18�չ������ԣ���л���ܹ�������һ�յ�֧�֡��ɼ�˼�����������ҳ������Ǹж���ֵ��������Ƭ����֮�ʣ�����10Ԫ�𿨵Ĵ���������������ǵ�һ�����⣬Ϊ������Ϸ֮�ô���������ˣ�\n\t12��18�����8����10��׶������������ִ�������콱��ʹ����ȡ��#R��׷ֺ�#W����\n\t��ʱ����WR60��#W���ϵ���Ҷ����Ի����׷ֺ�𿨺��������׼ʱ��ȡ��"
x350012_g_MissionReadme2 = "\t���8����10��׶������������ִ�������콱��ʹ����ȡ��#R��׷ֺ�#W����\n\t��ʱ����#R60��#W���ϵ���Ҷ����Ի����׷ֺ�𿨺��������׼ʱ��ȡ��"
x350012_g_MissionReadme3 = "\t���Ѿ���ȡ�˽������׷ֺ������\n\t��׷ֺ��ڵ���#G20:00#W��#G22:00#W����ȡ������ֱ�ӻ��#R����ڵĽ𿨷ֺ�#W������׼ʱ��ȡ��"
x350012_g_LevelMin				= 60
--x350012_g_RandomItemBonus		=	 12030421


--Ψһ��ȫ�ֱ���
x350012_g_MD					= MD_FENHONG


function x350012_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if GetTestServerToggle() == 1 then	--���
		if nLevel >= x350012_g_LevelMin then			
			for i,item in x350012_g_MissionDayTest do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	else	--����
		if nLevel >= x350012_g_LevelMin then			
			for i,item in x350012_g_MissionDay do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	end

--	if nLevel >= x350012_g_LevelMin then			
--		for i,item in x350012_g_MissionDay do
--			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
--				return item.flag
--			end
--		end	
--	end
		
	return 0
	
end

function x350012_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350012_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--������ں���

--**********************************

function x350012_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	--check invalid
	local nIndex = x350012_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
			
		local	strInfo1 = x350012_g_MissionReadme
		local	strInfo2 = "\t��ʥ��֮�ʣ������������ѹ�����յĿ��֣����ֵܽ���һ�������ܡ��ɼ�˼�������꡷�����Ǵ��������޻��֣�\n\t���׹�ȥ����Ϊ���ɼ�˼���������������࣬ҲΪ����������������ѫ����Щ���εζ��������μ����ģ�����20Ԫ�𿨵�ʥ�������͸�������л�������ǵ�֧�ֺ͹�����\n\t#G12��25�����8����10��׶�#W�����������ִ�������콱��ʹ����ȡ��#R��׷ֺ�#W����\n\t��ʱ����#R60��#W���ϵ���Ҷ����Ի����׷ֺ�𿨺��������׼ʱ��ȡ��"
		local strInfo3 = "\tԪ���������й��Ĵ�ͳ���գ��ڱ������̻�����ϲ���ϲ��ϲ�������У����ǹ�ͬӭ�ӡ��ɼ�˼��������ĸ���Իͣ�\n\t�������ۣ�����ӭ���µ�һ�꣡�������桶�ɼ�˼������ͬ�ɳ������ٸ���ҹ����Ǹ��ܵ������������еİ��⣬��������м��Ĵ���30Ԫ�𿨵�Ԫ����������������������ͣ������۷壡\n\t1��1�����8����10��׶������������ִ�������콱��ʹ����ȡ��#R��׷ֺ�#W����\n\t��ʱ����#R60��#W���ϵ���Ҷ����Ի����׷ֺ�𿨺��������׼ʱ��ȡ��"
		
		if x350012_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
			if GetTestServerToggle() == 1 then
				-- not get bouns
				if nIndex == 1 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,x350012_g_MissionReadme)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)				
				elseif nIndex == 2 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,strInfo2)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)					
				elseif nIndex == 3 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,strInfo3)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)					
				end
			
			else
				-- not get bouns
				if nIndex == 1 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,x350012_g_MissionReadme)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				elseif nIndex == 2 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,strInfo2)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				elseif nIndex == 3 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,strInfo3)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				end
				
	
			end
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350012_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
		AddQuestText(sceneId,x350012_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350012_CheckMD( sceneId,selfId )

	local nIndex = x350012_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350012_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350012_g_LevelMin then

	if GetTestServerToggle() == 1 then
		for i,item in x350012_g_MissionDayTest do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
					return
				end
			end
		end
	else
		for i,item in x350012_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
	
--		for i,item in x350012_g_MissionDay do
--			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
--				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
--					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
--					return
--				end
--			end
--		end
	end
	
end

--**********************************

--���ȫ�ֱ���

--**********************************

function x350012_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if GetTestServerToggle() == 1 then
		for i,item in x350012_g_MissionDayTest do
			if item.day == nDay then
				return 1
			end
		end
	else
		for i,item in x350012_g_MissionDay do
			if item.day == nDay then
				return 1
			end
		end
	end
	
--	for i,item in x350012_g_MissionDay do
--		if item.day == nDay then
--			return 1
--		end
--	end
	
	return 0

end

--**********************************

--���轱��

--**********************************

function x350012_GiveBonus( sceneId,selfId,flag)

	if flag == 1 then
		--�̶���Ʒ�����	
		AddMoney( sceneId, selfId, 3, 10000,101)	
		Msg2Player( sceneId, selfId, "��ϲ����ô�������Ƭ������10����", 8, 3)
		return 1
				
	elseif flag == 2 then
		
		AddMoney( sceneId, selfId, 3, 20000,101)	
		Msg2Player( sceneId, selfId, "��ϲ�����ʥ��������20����", 8, 3)
		return 1
	elseif flag == 3 then
		
		AddMoney( sceneId, selfId, 3, 30000,101)	
		Msg2Player( sceneId, selfId, "��ϲ�����Ԫ��������30����", 8, 3)
		return 1			

	end
	
	return 0
	
end

--**********************************

--�о��¼�

--**********************************

function x350012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350012_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350012_g_ScriptId, x350012_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--����������

--**********************************

function x350012_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--�����ȷ����
function x350012_ProcAccept( sceneId, selfId, NPCId )

	x350012_CheckMD( sceneId,selfId )
	
end



--**********************************

--����

--**********************************

function x350012_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x350012_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x350012_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x350012_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x350012_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x350012_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
