--������˽ű�

x300675_g_ScriptId = 300675
x300675_g_MissionId = 7028

-- NPC guid
x300675_g_GUID_Normal_Npcs = {
								129180,		-- ����������
								129181,		-- ��֥��������
								129182,		-- �̺�������
							}
x300675_g_GUID_Special_Npc = 129183			-- ��������

-- ˢ��ʱ�䣬5����
x300675_g_RefreshTime = 60*5*1000

-- ����NPC��ť���ʱ��
x300675_g_SpecialNpc_Interval = 300
x300675_g_SpecialNpc_Times = {0,0,0,0,0,0}

--�۸��׼��
x300675_g_Price_BenchMark = {
								{3384,2270,1154},	----  20-50�� (�ߣ��У���)
								{3384,2270,1154},	----  50-70��
								{3384,2270,1154}	----  70������
							}
--�۸񸡶�ֵ ����50
x300675_g_Price_Refix = 100

--ʵ�ʼ۸�ֵ
x300675_g_Price = 	{
						--normal npc1
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[1],	-- npc guid����������
							AllPrices = { {}, {}, {} },					-- �۸�洢�ռ䣬��������
							priceflag = {1,1,2,2,3,3},					-- ��Ʒ�۸�ȼ���1Ϊ�߼ۣ�2Ϊ�мۣ�3Ϊ�ͼ�
						},
						--normal npc2
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[2], 
							AllPrices = { {}, {}, {} },
							priceflag = {3,3,1,1,2,2},
						},
						--normal npc3
						{ 
							npcguid = x300675_g_GUID_Normal_Npcs[3], 
							AllPrices = { {}, {}, {} },
							priceflag = {2,2,3,3,1,1},
						},
						--special npc
						{ 
							npcguid = x300675_g_GUID_Special_Npc, 
							AllPrices = { {}, {}, {} },
							priceflag = {1,1,1,1,1,1},
						},
					}

--��Ʒ��Ϣ
x300675_Item_Goods = { 13030122, 13030123, 13030124, 13030125, 13030126, 13030127 }
x300675_Item_GoodsName = { "��������", "����ɺ��", "��˹��", "��������", "����ɽ��", "������֥", }
x300675_Item_Money = 13030128

x300675_g_FirstActive = 1

--�����NPC��
function x300675_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, x300675_g_MissionId ) ~= 1 then
		return
	end
	
	local NpcGUID = GetMonsterGUID(sceneId,targetId)

	if NpcGUID ~= x300675_g_GUID_Special_Npc then		--��ͨ����
		for i,item in x300675_Item_Goods do
			if HaveItem(sceneId,selfId,item)>0 then
				AddQuestNumText(sceneId,300675,"��������̡�"..x300675_Item_GoodsName[i],3,i)
			end
		end
	else		-- ��������
		local curTime = GetCurrentTime()
		for i,item in x300675_Item_Goods do
			if curTime - x300675_g_SpecialNpc_Times[i] >= x300675_g_SpecialNpc_Interval then
				if HaveItem(sceneId,selfId,item)>0 then
					AddQuestNumText(sceneId,300675,"��������̡�"..x300675_Item_GoodsName[i],3,i)
				end
			end
		end		
	end
	
	if x300675_g_FirstActive == 1 then
		x300675_g_FirstActive = 0
		SetTimer(sceneId, selfId, 300675, "OnSceneTimer", x300675_g_RefreshTime )
		x300675_Refresh_Price(sceneId)
	end
end

--�������ť������������ִ�д˽ű�
function x300675_ProcEventEntry( sceneId, selfId, targetId,state,index)

	
	if IsHaveQuestNM( sceneId, selfId, x300675_g_MissionId ) ~= 1 then
		return
	end
	
	if index < 10 then
		local Readme = "����Ʒ:"..x300675_Item_GoodsName[index]..",�۸�:"..x300675_GetPrice(sceneId, selfId, targetId,index)
		BeginQuestEvent(sceneId);
		AddQuestNumText(sceneId,300675,"ȷ��",3,index + 10 )
		AddQuestText(sceneId,Readme);
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif index > 10 then
	
		local op = index - 10
		
		if GetMonsterGUID(sceneId,targetId) == x300675_g_GUID_Special_Npc then
			if GetCurrentTime() - x300675_g_SpecialNpc_Times[op] < x300675_g_SpecialNpc_Interval then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId,"����ʧ��#r�ղ���������֮ǰ���۹����������ˡ�");
				EndQuestEvent(sceneId);
				DispatchQuestEventList(sceneId, selfId, targetId)	
				return
			end
		end
		
		if x300675_SaleItem(sceneId, selfId, targetId,op) == 1 then
		
			local bAllSaled = 1
			local bFailed = 0
			for i,item in x300675_Item_Goods do
				if HaveItem(sceneId, selfId,item)>0 then
					bAllSaled = 0
					break
				end
			end
			if bAllSaled == 1 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
				local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
				if nMoney < 10000 then
					bFailed = 1
				end			
			end

			BeginQuestEvent(sceneId);
			if bFailed==0 then
				AddQuestText(sceneId,"\t�ðɣ�����ﲻ����Ը���չ���");
			else
				AddQuestText(sceneId,"\t����������еİ�������õ��Ľ�Ǯ#G�������������#W��ȥ������񷢲��˴�#G������ȡ����#W�ɡ�");
			end
			EndQuestEvent(sceneId);
			DispatchQuestEventList(sceneId, selfId, targetId)	

			if bFailed == 1 then			
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
				--SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
				SetQuestByIndex( sceneId, selfId, misIndex, 6, 1)
				CallScriptFunction( 300678, "ProcQuestLogRefresh", sceneId, selfId, x300675_g_MissionId )	
			else 
				local price = x300675_GetPrice(sceneId, selfId, targetId, op)
			    local goodsname = x300675_Item_GoodsName[op]
				local salemsg = format("�������#G%s#cffcf00�������Ʊ�еĽ��������#G%s#cffcf00��",goodsname,price)
				Msg2Player(sceneId, selfId, salemsg, 8, 3);
				Msg2Player(sceneId, selfId, salemsg, 8, 2);
			end
			
			if GetMonsterGUID(sceneId,targetId) == x300675_g_GUID_Special_Npc then
				x300675_g_SpecialNpc_Times[op] = GetCurrentTime()
			end
			
		end
		
	end

end

--�����ȷ����
function x300675_ProcAcceptCheck( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x300675_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300675_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300675_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300675_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300675_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300675_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300675_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300675_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


function x300675_OnSceneTimer( sceneId )
	x300675_Refresh_Price(sceneId)
end

function x300675_Refresh_Price(sceneId)

	for i1,item1 in x300675_g_Price do					-- NPCѭ��
		for i2,item2 in item1.AllPrices do				-- �۸�ѭ��1��������ȼ�
			for i3,item3 in item1.priceflag do			-- �۸�ѭ��2�����۸�ߵ�
				item2[i3] = x300675_g_Price_BenchMark[i2][item3] + random(1,x300675_g_Price_Refix) - x300675_g_Price_Refix/2
			end
		end		
	end
	
end

function x300675_GetPrice( sceneId, selfId, targetId, itemIndex )

	local price = 0
	local NpcGUID = GetMonsterGUID(sceneId,targetId)
	for i,item in x300675_g_Price do
		if item.npcguid == NpcGUID then
			local level = GetLevel(sceneId, selfId)
			if level>=70 then
				price = item.AllPrices[3][itemIndex]
			elseif level>=50 then
				price = item.AllPrices[2][itemIndex]
			elseif level>=20 then
				price = item.AllPrices[1][itemIndex]
			end
			break
		end
	end
	
	return floor( price)

end

function x300675_SaleItem(sceneId, selfId, targetId, itemIndex )

	if HaveItem(sceneId,selfId,x300675_Item_Goods[itemIndex])<=0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,"\t���ƺ���û���������");
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
	end
	
	if HaveItem(sceneId,selfId,x300675_Item_Money)<=0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,"\t��û�а����Ʊ���޷����ס�");
		EndQuestEvent(sceneId);
		DispatchQuestEventList(sceneId, selfId, targetId)		
		return 0
	end	
	
	local price = x300675_GetPrice(sceneId, selfId, targetId,itemIndex)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300675_g_MissionId)
	local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)		

	SetQuestByIndex( sceneId, selfId, misIndex, 0, nMoney+price)
	DelItem(sceneId, selfId, x300675_Item_Goods[itemIndex], 1)
	
	CallScriptFunction( 300678, "ProcQuestLogRefresh", sceneId, selfId, x300675_g_MissionId )	
	
	return 1

end