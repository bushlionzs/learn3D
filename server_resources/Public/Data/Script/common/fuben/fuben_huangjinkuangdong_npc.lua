x700104_g_ScriptId 		= 700104

x700104_g_MaxCount		= 5

x700104_g_SubmitItem	= 11990015

x700104_g_TitleInfo		= "������������òر���һ�һЩ���߲��ϡ����һ�һ�ν�����һ���ٴν���ر����Ļ��ᡣ"

x700104_g_SelectOpt		= {
							{"�ر���һ�ˮ��",11001}, 
							{"�ر���һ�����ʯ",11002}, 
							{"�ر���һ�����",11003}, 
							{"�ر���һ�����",11004}, 
							{"�ر���һ�����ܲ���",11005}
						}
						
x700104_g_SelectPane1	= {
							{"����ˮ��", 11011, 11000200, 20, 9},
							{"����ˮ��", 11012, 11000201, 40, 9},
							{"��ˮ��", 11013, 11000202, 60, 9},
							{"�촫ˮ��", 11014, 11000203, 80, 9}
						}
						
x700104_g_SelectPane2	= {
							{"��������ʯ", 11021, 11050001, 20, 9},
							{"�м�����ʯ", 11022, 11050002, 40, 9},
							{"�߼�����ʯ", 11023, 11050003, 60, 9},
							{"��֮����ʯ", 11024, 11050004, 80, 9},
							{"��ڤ֮����ʯ",11025,11050005, 100,9}
						}
						
x700104_g_SelectPane5	= {
							{"�ݱ�����", 11051, 11020501},
							{"�߲���", 11052, 11030405},
							{"�ۻ�ʯ", 11053, 11030501}
						}
						
x700104_g_RandItem = {11010100, 11010101, 11010102}
				
function x700104_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--����������ִ�д˽ű�

	if idExt == 11000 then
		x700104_Opt( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[1][2] then
		x700104_ShowPane1( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[2][2] then
		x700104_ShowPane2( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[3][2] then
		x700104_ShowPane3( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[4][2] then
		x700104_ShowPane4( sceneId, selfId, NPCId )
	elseif idExt == x700104_g_SelectOpt[5][2] then
		x700104_ShowPane5( sceneId, selfId, NPCId )
	elseif idExt >= 11010 and idExt <= 11100 then
		x700104_ShowOpt( sceneId, selfId, NPCId, idExt )
	else
		x700104_ShowInit( sceneId, selfId, NPCId )
	end
end

--�о��¼�
function x700104_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	x700104_ShowInit( sceneId, selfId, NPCId )
end

function x700104_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--��ȷ����
function x700104_ProcAccept( sceneId, selfId )
end

function x700104_ShowOpt( sceneId, selfId, NPCId, idExt )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, idExt)
		
	BeginQuestEvent(sceneId)
		local count = 1
		local name = ""
		if idExt >= x700104_g_SelectPane1[1][2] and idExt <= x700104_g_SelectPane1[4][2] then
			local idx = idExt-11010
			name = x700104_g_SelectPane1[idx][1]
			count = x700104_g_SelectPane1[idx][5]
		elseif idExt >= x700104_g_SelectPane2[1][2] and idExt <= x700104_g_SelectPane2[5][2] then
			local idx = idExt-11020
			name = x700104_g_SelectPane2[idx][1]
			count = x700104_g_SelectPane2[idx][5]
		elseif idExt >= x700104_g_SelectPane5[1][2] and idExt <= x700104_g_SelectPane5[3][2] then
			local idx = idExt-11050
			name = x700104_g_SelectPane5[idx][1]
			
			local level = GetLevel(sceneId, selfId)
			if level >= 70 then
				count =35
			elseif level >= 60 then
				count =30
			elseif level >= 50 then
				count =15
			end
		end
		
		local str = format("��ȷ��Ҫ�òر���һ�%d��%s", count, name)
		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"ȷ��",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

function x700104_Opt( sceneId, selfId, NPCId )

	if x700104_GetDayCount(sceneId, selfId) >= x700104_g_MaxCount then
		return
	end
		
	local opt = GetPlayerRuntimeData(sceneId,selfId,RD_HUANGJINKUANGDONG_OPT)
	
	if opt == x700104_g_SelectOpt[3][2] then
		
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 3)
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
			
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		local nadd = 620*(bQingjian+1)
		local nShengWang = GetShengWang( sceneId, selfId ) + nadd
		SetShengWang( sceneId, selfId, nShengWang )
		
		if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
			local index = random(1,3)
			if index < 1 then index = 1 end
			if index > 3 then index = 3 end
			local rndItemid = x700104_g_RandItem[index]
			
			BeginAddItem( sceneId )
			AddItem( sceneId, rndItemid, 1)
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				
				local str = format("#Y������#G1��#Y#{_ITEM%d}", rndItemid)
				Msg2Player(sceneId, selfId, str, 8, 3)
				--Msg2Player(sceneId, selfId, str, 8, 2)
			end
		end
		
		str = format("���#R����%d#o�Ľ���", nadd)
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
		
	elseif opt == x700104_g_SelectOpt[4][2] then
		
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 3)
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		if bQingjian > 0 then
                        local nadd_yinbi_1 = GetLevel(sceneId, selfId)*200
                        local nadd_yinka_1 = GetLevel(sceneId, selfId)*400

			AddMoney(sceneId, selfId, 0, nadd_yinbi_1)
			AddMoney(sceneId, selfId, 1, nadd_yinka_1)
			
			Msg2Player(sceneId,selfId,format("���#{_MONEY%d}������#{_MONEY%d}����",nadd_yinbi_1,nadd_yinka_1),8,3)
		else
                        local nadd_yinka = GetLevel(sceneId, selfId)*600
			AddMoney(sceneId, selfId, 1, nadd_yinka)
			Msg2Player(sceneId,selfId,format("���#{_MONEY%d}������",nadd_yinka),8,3)
		end
		
		if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
			local index = random(1,3)
			if index < 1 then index = 1 end
			if index > 3 then index = 3 end
			local rndItemid = x700104_g_RandItem[index]
			
			BeginAddItem( sceneId )
			AddItem( sceneId, rndItemid, 1)
			local ret = EndAddItem( sceneId, selfId )
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				
				local str = format("#Y������#G1��#Y#{_ITEM%d}", rndItemid)
				Msg2Player(sceneId, selfId, str, 8, 3)
				--Msg2Player(sceneId, selfId, str, 8, 2)
			end
		end
	
	elseif opt >= x700104_g_SelectPane1[1][2] and opt <= x700104_g_SelectPane1[4][2] then
		local idx = opt-11010
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane1[idx][1], x700104_g_SelectPane1[idx][3], x700104_g_SelectPane1[idx][5])
	elseif opt >= x700104_g_SelectPane2[1][2] and opt <= x700104_g_SelectPane2[5][2] then
		local idx = opt-11020
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane2[idx][1], x700104_g_SelectPane2[idx][3], x700104_g_SelectPane2[idx][5])
	elseif opt >= x700104_g_SelectPane5[1][2] and opt <= x700104_g_SelectPane5[3][2] then
		local idx = opt-11050
		local count = 1
		local level = GetLevel(sceneId, selfId)
		if level >= 70 then
			count =35
		elseif level >= 60 then
			count =30
		elseif level >= 50 then
			count =15
		end
		
		x700104_AddItem(sceneId, selfId, NPCId, x700104_g_SelectPane5[idx][1], x700104_g_SelectPane5[idx][3],count)
	end
	
	x700104_ShowInit( sceneId, selfId, NPCId )
end

-- ��ʾ��ʼ����
function x700104_ShowInit( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		-- ������
		local daycount = x700104_GetDayCount(sceneId, selfId)
		if daycount < x700104_g_MaxCount then
			for i, item in x700104_g_SelectOpt do
				if i ~= 3 then
					AddQuestNumText(sceneId,x700104_g_ScriptId,item[1],3,item[2])
				end
			end
		else
			AddQuestText(sceneId,"����ر����Ĵ��������޷��һ�")
		end
	EndQuestEvent()
	--DispatchQuestInfo(sceneId, selfId, NPCId, x700104_g_ScriptId, -1)
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--�ر���һ�ˮ��
function x700104_ShowPane1( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		for i, item in x700104_g_SelectPane1 do
			if level >= item[4] then
				AddQuestNumText(sceneId,x700104_g_ScriptId,"�ر���һ�"..item[1],3,item[2])
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--�ر���һ�����ʯ
function x700104_ShowPane2( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		for i, item in x700104_g_SelectPane2 do
			if level >= item[4] then
				AddQuestNumText(sceneId,x700104_g_ScriptId,"�ر���һ�"..item[1],3,item[2])
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end
--�ر���һ�����
function x700104_ShowPane3( sceneId, selfId, NPCId )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, x700104_g_SelectOpt[3][2])
		
	BeginQuestEvent(sceneId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)
		local nadd = 620*(bQingjian+1)
		
		local str = format("��ȷ��Ҫ�òر���һ�%d��������", nadd)
		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"ȷ��",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end
--�ر���һ�����
function x700104_ShowPane4( sceneId, selfId, NPCId )
	SetPlayerRuntimeData(sceneId, selfId, RD_HUANGJINKUANGDONG_OPT, x700104_g_SelectOpt[4][2])
	
	BeginQuestEvent(sceneId)
		
		local bQingjian = x700104_CheckQingjian(sceneId, selfId)

		local str = ""
		if bQingjian == 1 then
                        local nadd_yinbi_1 = GetLevel(sceneId, selfId)*200
                        local nadd_yinka_1 = GetLevel(sceneId, selfId)*400		
			str = format("��ȷ��Ҫ�òر���һ�%d��������%d��������", nadd_yinbi_1, nadd_yinka_1)
		else
                        local nadd_yinka  =  GetLevel(sceneId, selfId)*600
			str = format("��ȷ��Ҫ�òر���һ�%d��������", nadd_yinka)
		end

		AddQuestText(sceneId,str)
		
		AddQuestNumText(sceneId,x700104_g_ScriptId,"ȷ��",3,11000)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

--�ر���һ�����ܲ���
function x700104_ShowPane5( sceneId, selfId, NPCId )
	local level = GetLevel(sceneId, selfId)
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700104_g_TitleInfo)
		
		if level < 50 then
			AddQuestText(sceneId,"\n\t�������50���Ժ�ſ��Զһ�����ܲ��ϡ�")
		else
			for i, item in x700104_g_SelectPane5 do
				if level >= 50 then
					AddQuestNumText(sceneId,x700104_g_ScriptId,"�ر���һ�"..item[1],3,item[2])
				end
			end
		end
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)
end

-- �жϽ������
function x700104_CheckQingjian(sceneId, selfId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011 )>0 or IsHaveSpecificImpact( sceneId, selfId, 9013 ) > 0  or IsHaveSpecificImpact( sceneId, selfId, 9012 ) > 0 then
        return 1
    end
    return 0
end

-- �����Ʒ
function x700104_AddItem( sceneId, selfId, NPCId, itemname, itemid, count )
	BeginAddItem( sceneId )
	AddItem( sceneId, itemid, count)
	
	local rndItemid = -1
	if GetLevel(sceneId, selfId) >= 80 and random(1, 100) <= 5 then
		local index = random(1,3)
		if index < 1 then index = 1 end
		if index > 3 then index = 3 end
		rndItemid = x700104_g_RandItem[index]
		AddItem( sceneId, rndItemid, 1)
	end
	
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		if DelItem( sceneId, selfId, x700104_g_SubmitItem, 1) == 0 then
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 3)
		    Msg2Player( sceneId, selfId, "û�вر��", 8, 2)
		    
		    x700104_ShowInit( sceneId, selfId, NPCId )
		    return
		end
		x700104_SetDayCount(sceneId, selfId)
		
		AddItemListToPlayer(sceneId,selfId)
		
		local str = "#Y���#G"..count.."��#Y"..itemname
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
		
		if rndItemid ~= -1 then
			local str = format("#Y������#G1��#Y#{_ITEM%d}", rndItemid)
			Msg2Player(sceneId, selfId, str, 8, 3)
			--Msg2Player(sceneId, selfId, str, 8, 2)
		end
	else
		local str = "#Y�����ռ䲻�㣬�������������ԣ�"
		Msg2Player(sceneId, selfId, str, 8, 3)
		Msg2Player(sceneId, selfId, str, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x700104_GetDayCount(sceneId, selfId)
	if x700104_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x700104_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DATE[1], MD_FUBEN_HUANGJINKUANGDONG_DATE[2], MD_FUBEN_HUANGJINKUANGDONG_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[1], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[2], MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT[3], daycount+1)
	end
end
