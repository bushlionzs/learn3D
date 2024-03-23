--�����ߡ��ռ�����
--MD_SHOUJI_MATERIAL_DATE						--�ռ����� ����������
--MD_SHOUJI_MATERIAL_COUNT          --�ռ����ϵ��ռ�����
--MD_SHOUJI_MATERIAL_CYCLE					--�ռ����� ����
--MD_SHOUJI_MATERIAL_CYCLECOUNT			--�ռ����� �û�����

--MisDescBegin
x300517_g_ScriptId = 300517
x300517_g_MissionIdPre =-1
x300517_g_MissionId = 8053
x300517_g_LevelLess	= 	30 
x300517_g_Name	={}
x300517_g_MissionName="�����ˡ��ռ�����"	
x300517_g_MissionCompleted="\t�����ˣ��������൱��������������Ӧ�õı��ꡣ"					--�������npc˵���Ļ�
x300517_g_Mis_Count   = 1								--ÿ������Ĵ���
x300517_g_Mis_CollectCount   = 1				--�ռ����ϸ���
x300517_g_MaxSigleCycle_Count   = 4
x300517_g_LevelMod   = 10
x300517_g_BonusMoney1 =0
x300517_g_BonusMoney2 =0
x300517_g_BonusMoney3 =0
x300517_g_BonusMoney4 =0
x300517_g_BonusMoney5 =0
x300517_g_BonusMoney6 =0
x300517_g_BonusItem	=	{}
x300517_g_BonusChoiceItem ={}
x300517_g_ExpBonus = 60
x300517_g_ItemMinBonus = 2
x300517_g_ItemMaxBonus = 4
x300517_g_NpcGUID ={}

x300517_g_MissionHelp = "\t#W������ʮ��Ϊһ�֣�ÿ��ֻ�����һ�֡��������У�Ҳ������ռ��˻�#G��������ռ�ͬһ��Ʒ#W���������������㽫���÷��Ľ�����\n\t#G�������������񣬵����޷��ٴ���ȡ�ռ����������ˡ�"


x300517_g_MissionTable =    {
                                { maxLevel = 40,  item = {11020001,11020002,11030001}},
                                { maxLevel = 50,  item = {11020001,11020002,11030001,11020006,11020007}},
                                { maxLevel = 60,  item = {11020001,11020002,11030001,11020006,11020007,11020010,11020011,11030003}},
                                { maxLevel = 70,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005}},
                                { maxLevel = 80,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 90,  item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 100, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 110, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 120, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 130, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 140, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 150, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},
                                { maxLevel = 160, item = {11020006,11020007,11020010,11020011,11030003,11020014,11020015,11030005,11030007}},                                
                            }     


x300517_g_ItemTable =    {
                                { maxLevel = 45,  item = 11050001},
                                { maxLevel = 66,  item = 11050002},
                                { maxLevel = 160, item = 11050003},                                
                            } 
--MisDescEnd
--**********************************
--�о�����
function x300517_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
			return
	end
	if IsHaveQuestNM(sceneId,selfId, MissionId) <= 0 then
			if GetLevel(sceneId, selfId) >= x300517_g_LevelLess then
					local state = GetQuestStateNM(sceneId,selfId,NPCId,x300517_g_MissionId)
					AddQuestTextNM( sceneId, selfId, NPCId, x300517_g_MissionId, state, -1 )
			end
	else
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x300517_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x300517_g_MissionId, state, -1 )
	end
end

--**********************************
--ѡ������
function x300517_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDoneNM(sceneId, selfId, x300517_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuestNM(sceneId,selfId, MissionId) > 0 then
			if x300517_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
						local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
						local strText = format( "��ȥ�ռ�#G%d#W��#G@itemid_%d#W,�����ģ��һ���㽱�͵ġ�", circlesCount, itemdataId )
						AddQuestText(sceneId,strText)
						AddQuestText( sceneId,"\n#Y��������")
						local itemcount = GetItemCount(sceneId,selfId,itemdataId);
						local MissionTarget = format( "�ռ�#G@itemid_%d#W(%d/%d)", itemdataId , itemcount, circlesCount)
						AddQuestText(sceneId,MissionTarget)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						AddQuestText(sceneId,x300517_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x300517_DispatchMissionInfo( sceneId, selfId, NPCId, 1)
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			end
  else
  		if  IsNpcHaveQuestNM(sceneId, selfId, NPCId, MissionId) == 1 then--�����ж�npc�����Ƿ���������񣬷�����bug
					if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
						AddQuestText(sceneId,"\t����̫�ӵ��������Ĳ����ռ��٣������ռ�����������ȱ�Ĳ��ϡ������Ͻ������߾��з����ʹ͡�\n\t�ţ����������ײ��ϵ���")
						AddQuestText( sceneId,"\n#GС��ʾ��")
						AddQuestText(sceneId,x300517_g_MissionHelp)								
						local level = GetLevel(sceneId, selfId)
						local ExpBonus = x300517_g_ExpBonus*level*2
						AddQuestExpBonus(sceneId, ExpBonus )
		  			EndQuestEvent()
						DispatchQuestInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
					end
			end
  end
end

--**********************************
--ˢ���������
function x300517_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	if MissionId == nil or MissionId < 0 then
		return
	end
	
	if IsHaveQuestNM(sceneId, selfId, MissionId) <= 0 then
		return
	end
	
	local ModNum = x300517_GetModNum(sceneId, selfId);
	local MissionName;
	MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
	local maxcircle = x300517_GetMaxCircleNum(sceneId, selfId);
	local circle = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
	
	MissionName = MissionName.."("..circle;
	MissionName = MissionName.."/"..maxcircle;
	MissionName = MissionName..")";
	
	local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
	local itemcount = GetItemCount(sceneId,selfId,itemdataId);
	
	local MissionTarget = format( "  �ռ�#G@itemid_%d#W(%d/%d)", itemdataId , itemcount, circlesCount)
	if MissionTarget == nil then
		MissionTarget = "";
	end
	
	local MissionNPC = "@npc_138559"
	--MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip
	
	local MissionProcess = format("�����ͨ�����ܵ��˻�����������ҽ��׻��#G@itemid_%d#W", itemdataId)
	local MissionComment = format("\tΪ�˵�����У�������Ҫ����Ĳ��������л������衣ȥ�ռ�#G@itemid_%d#W���Ұɣ��һ���㽱���ġ�", itemdataId)
	x300517_QuestLogRefresh(sceneId, selfId, MissionId, "", MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, x300517_g_MissionHelp);
end

--**********************************
--����Ƿ�ɽ�
function x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel(sceneId,selfId);
	if ( level < x300517_g_LevelLess ) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ĵȼ�������������ȡ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�ɽ�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
		end
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
		if lastday ~= today then
			return 1
		end
		if x300517_IsAbdon(sceneId, selfId) > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������������޷���ȡ�ռ���������");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
		local daycount =  GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3])
		if daycount >= x300517_g_Mis_Count then
			  BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ռ���������һ��ֻ����10��");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId, selfId, "�ռ���������һ��ֻ����10��", 0, 2)
				return 0
		end
		return 1;
	end

end

--**********************************
--������
function x300517_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsHaveQuestNM(sceneId, selfId, MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId, selfId) > 0 then
			return
		end
		
		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,MissionId  )
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
		
		local ret = QuestCheckAcceptNM( sceneId, selfId, NPCId, MissionId ) -- ��ȡ������������Ϣ
		if ret > 0 then -- ������Խ��������
			if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
				if DelQuest(sceneId, selfId, x300517_g_MissionId) > 0 then
						if  IsNpcHaveQuestNM(sceneId, selfId, NPCId, MissionId) == 1 then--�����ж�npc�����Ƿ���������񣬷�����bug
								if x300517_ProcAcceptCheck(sceneId, selfId, NPCId, MissionId) > 0 then
									BeginQuestEvent(sceneId)
						  		local itemdataId = x300517_GetRandItem(sceneId, selfId)
						  		x300517_AcceptThisCycle(sceneId, selfId)
						  		if AddQuest( sceneId, selfId, x300517_g_MissionId, x300517_g_ScriptId, 0, 0, 1) > 0 then
										x300517_SetCurrentItem(sceneId, selfId, itemdataId)
							 			x300517_Msg2toplayer( sceneId, selfId,0)
							  		xx300517_DisplayCircleMessage(sceneId, selfId, MissionId)
										AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
										local strText = format( "\t�ţ��ҿ������������ں���Ҫ#G@itemid_%d#W���ռ����Ұɣ��һ���㽱���ġ�", itemdataId )
										AddQuestText(sceneId,strText)
										AddQuestText( sceneId,"\n#Y����Ŀ�꣺")
										strText = format( "�ռ�һ��#G@itemid_%d#W", itemdataId )
										if strText == nil then
											strText = "";
										end
										AddQuestText( sceneId,strText)
						  			EndQuestEvent()
										DispatchQuestEventList(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
										x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
									end
								end
						end
				end
		 	end                                                                    
	  end
end

--**********************************
function xx300517_DisplayCircleMessage(sceneId, selfId, MissionId)

	local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	local maxcircles = x300517_GetMaxCircleNum( sceneId, selfId )

  local str;
	str = format( "����: %d/%d", circles, maxcircles );

	Msg2Player(sceneId, selfId, str, 0, 3);
	
	if circles == 1 then
		GamePlayScriptLog(sceneId, selfId, 701)
	end
	
	if circles == 5 then
		GamePlayScriptLog(sceneId, selfId, 711)
	end
	
	if circles == 10 then
		GamePlayScriptLog(sceneId, selfId, 721)
	end
end

--**********************************
--����Ƿ���ύ
function x300517_CheckSubmit( sceneId, selfId, NPCId)
		local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		if GetItemCount(sceneId,selfId,itemdataId) >= recycleCount then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
end

--**********************************
--�ύ����
function x300517_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x300517_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x300517_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
  end
	local circlesCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
	local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
	if circlesCount < x300517_g_MaxSigleCycle_Count then
		local randnum = random(1, 100)
 		if randnum > 50 then
 			x300517_GetBonus( sceneId, selfId, NPCId)
 			local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
			SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3],circlesCount+1)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)
	  	DelItem( sceneId,selfId,itemdataId, circlesCount )     
			SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    circlesCount = circlesCount + 1
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300517_g_MissionName)
			local str;
			str = format("\t�յõ�����Ϣ�����Ƕ�#G@itemid_%d#W�������������ˡ�������Ϊ�����ռ�#G%d#W��#G@itemid_%d#W��", itemdataId ,circlesCount,itemdataId);
			AddQuestText(sceneId,str)
			AddQuestText(sceneId,"\n#Y����Ŀ�꣺")
			str = format( "�ռ�#G%d#W��#G@itemid_%d#W", circlesCount, itemdataId )
			AddQuestText(sceneId,str )
			AddQuestText(sceneId,"\n#GС��ʾ:#W")
			str = format( "���Ǳ����ĵ�%d��,������������%d��", circlesCount ,x300517_g_MaxSigleCycle_Count);
			AddQuestText(sceneId,str )
			AddQuestText(sceneId,"\n#Y�������ݣ�")
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			local ExpBonus = x300517_g_ExpBonus*level*2^circlesCount
			str = format( "����ֵ: %d", ExpBonus)
			AddQuestText(sceneId,str )
			EndQuestEvent(sceneId)
			--DispatchQuestTips(sceneId,selfId)
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x300517_g_ScriptId, x300517_g_MissionId);
			x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
			return
		end
  end
  local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
  if DelQuest(sceneId, selfId, x300517_g_MissionId) > 0 then
		x300517_Msg2toplayer( sceneId, selfId,2)
		x300517_GetBonus( sceneId, selfId, NPCId)
		local maxcircles = x300517_GetMaxCircleNum( sceneId, selfId )
		if circles >= maxcircles then
			x300517_SetDayComplete(sceneId, selfId)
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			for i, item in x300517_g_ItemTable do
				if level < item.maxLevel then
					 BeginAddItem(sceneId)
					 local nRandNum = random(x300517_g_ItemMinBonus, x300517_g_ItemMaxBonus)
					 AddItem( sceneId, item.item, nRandNum )
					 local ret = EndAddItem( sceneId, selfId )
					 if ret == 1 then
							AddItemListToPlayer( sceneId, selfId )
							Msg2Player(sceneId, selfId, format("��������Ʒ#R@itemid_%d#Y�Ľ���", item.item),4,3)
							Msg2Player(sceneId, selfId, format("��������Ʒ#R@itemid_%d#Y�Ľ���", item.item),4,2)
					 end
					 break
				end
			end
			GamePlayScriptLog(sceneId, selfId, 722)
		end
		if circles == 1 then
			GamePlayScriptLog(sceneId, selfId, 702)
		end 
		if circles == 5 then
			GamePlayScriptLog(sceneId, selfId, 712)
		end
	  DelItem( sceneId,selfId,itemdataId, circlesCount )
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 0)
	end
end

--**********************************
--��ý���
function x300517_GetBonus( sceneId, selfId,NpcID)
	  if x300517_g_ExpBonus > 0 then
			local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
			--50 * lv * 2^�ظ����
			local level = x300517_GetAcceptLevel(sceneId, selfId)
			local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
			AddExp(sceneId, selfId, ExpBonus);
			Msg2Player(sceneId, selfId, "#Y���#R����"..ExpBonus.."#Y�Ľ���", 0, 2)
  	end
		if x300517_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300517_g_BonusMoney1 )
	  end
		if x300517_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300517_g_BonusMoney2 )
	  end
		if x300517_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300517_g_BonusMoney3 )
		end
		if x300517_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x300517_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x300517_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x300517_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x300517_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x300517_g_BonusMoney6)
		end
end

--**********************************
--����
function x300517_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x300517_g_MissionId) <= 0 then
				return 
		end
		x300517_SetDayComplete( sceneId, selfId)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 1)
		DelQuest(sceneId, selfId, x300517_g_MissionId)
	  x300517_Msg2toplayer( sceneId, selfId,1)
end

function x300517_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x300517_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x300517_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x300517_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x300517_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		x300517_ProcQuestLogRefresh(sceneId, selfId, x300517_g_MissionId)
		local itemdataId = x300517_GetCurrentItem(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		if GetItemCount(sceneId,selfId,itemdataId) >= recycleCount then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,itemdataId))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x300517_g_MissionId)                                                 
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,itemdataId))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x300517_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x300517_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300517_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300517_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300517_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300517_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300517_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

---------------------------------------------------------------------------------------------------
--��������Ʒ
---------------------------------------------------------------------------------------------------
function x300517_GetModNum(sceneId, selfId)
	return 10
end

---------------------------------------------------------------------------------------------------
--��������Ʒ
---------------------------------------------------------------------------------------------------
function x300517_GetRandItem(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	for i, item in x300517_g_MissionTable do
		if level < item.maxLevel then
			local nCount = getn( item.item )
			local nRandNum = random(1, nCount)
			return item.item[nRandNum]
		end
	end
end

---------------------------------------------------------------------------------------------------
--��õ�ǰ��Ʒ
---------------------------------------------------------------------------------------------------
function x300517_GetCurrentItem(sceneId, selfId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300517_g_MissionId );
	local rst = GetQuestParam( sceneId, selfId, misIndex, 5)
	return rst
end

---------------------------------------------------------------------------------------------------
--���õ�ǰ��Ʒ
---------------------------------------------------------------------------------------------------
function x300517_SetCurrentItem(sceneId, selfId, itemId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300517_g_MissionId );
	SetQuestByIndex(sceneId,selfId,misIndex,5,itemId)
end
---------------------------------------------------------------------------------------------------
--���ӽ�����Ϣ
---------------------------------------------------------------------------------------------------
function x300517_DispatchMissionInfo( sceneId, selfId, NPCId ,bContinue)
		if x300517_g_ExpBonus> 0 then
			local level = x300517_GetAcceptLevel(sceneId, selfId)
		  if bContinue > 0 then
				local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
				--50 * lv * 2^�ظ����
				local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
				AddQuestExpBonus(sceneId, ExpBonus )
			else
				AddQuestExpBonus(sceneId, x300517_g_ExpBonus*level*2 )
			end
		end
		if x300517_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300517_g_BonusMoney1 )
		end
		if x300517_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300517_g_BonusMoney2 )
		end
		if x300517_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300517_g_BonusMoney3 )
		end
		if x300517_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300517_g_BonusMoney4 )
		end
		if x300517_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300517_g_BonusMoney5 )
		end
		if x300517_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300517_g_BonusMoney6 )
		end
		for i, item in x300517_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x300517_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end

--**********************************
--��ʾ��Ϣ
function x300517_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x300517_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x300517_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x300517_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x300517_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x300517_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x300517_g_MissionName.."��", 0, 3)
				if x300517_g_ExpBonus > 0 then
					--Msg2Player(sceneId, selfId, "#Y���#R����"..x300517_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x300517_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x300517_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x300517_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x300517_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x300517_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x300517_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x300517_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x300517_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x300517_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x300517_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x300517_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x300517_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

---------------------------------------------------------------------------------------------------
--ȡ�ô����������
---------------------------------------------------------------------------------------------------
function x300517_GetMaxCircleNum(sceneId, selfId)
	return 10;
end

---------------------------------------------------------------------------------------------------
--ȡ�ô��������Ƿ����
---------------------------------------------------------------------------------------------------
function x300517_GetDayComplete(sceneId, selfId)

	if x300517_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--���µ��������
---------------------------------------------------------------------------------------------------
function x300517_SetDayComplete(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3], today)
	end
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3], 1)
end
---------------------------------------------------------------------------------------------------
--���½�����ȼ�
---------------------------------------------------------------------------------------------------
function x300517_GetAcceptLevel(sceneId, selfId)
	local level = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3])
	return level
end

---------------------------------------------------------------------------------------------------
--������Ϣ
---------------------------------------------------------------------------------------------------
function x300517_SetAcceptInfo(sceneId, selfId)
	local today = GetDayOfYear()
	local level = GetLevel(sceneId, selfId)

	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3], today)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_COUNT[1], MD_SHOUJI_MATERIAL_COUNT[2], MD_SHOUJI_MATERIAL_COUNT[3], 0)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3], 1)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 1)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3], level)
	SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 0)
end

---------------------------------------------------------------------------------------------------
--���ܸû�����
---------------------------------------------------------------------------------------------------
function x300517_AcceptThisCycle(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		local circles = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3])
		local level = GetLevel(sceneId, selfId)
		circles = circles + 1
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLE[1], MD_SHOUJI_MATERIAL_CYCLE[2], MD_SHOUJI_MATERIAL_CYCLE[3], circles)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3], 1)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_LEVEL[1], MD_SHOUJI_MATERIAL_LEVEL[2], MD_SHOUJI_MATERIAL_LEVEL[3], level)
		SetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3], 0)
	else
		x300517_SetAcceptInfo(sceneId, selfId)
	end
end

---------------------------------------------------------------------------------------------------
--����Ƿ�����˸�����
---------------------------------------------------------------------------------------------------
function x300517_IsAbdon(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_DATE[1], MD_SHOUJI_MATERIAL_DATE[2], MD_SHOUJI_MATERIAL_DATE[3])
	if lastday == today then
		return GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_ABDON[1], MD_SHOUJI_MATERIAL_ABDON[2], MD_SHOUJI_MATERIAL_ABDON[3])
	else
		return 0
	end
end

---------------------------------------------------------------------------------------------------
--��������׷��
---------------------------------------------------------------------------------------------------
function x300517_QuestLogRefresh(sceneId, selfId, MissionId, MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip)

	if MissionTitle == nil then
		MissionTitle = "";
	end
	if MissionName == nil then
		MissionName = "";
	end
	if MissionTarget == nil then
		MissionTarget = "";
	end
	if MissionNPC == nil then
		MissionNPC = "";
	end
	if MissionProcess == nil then
		MissionProcess = "";
	end
	if MissionComment == nil then
		MissionComment = "";
	end
	if MissionTip == nil then
		MissionTip = "";
	end
	BeginQuestEvent(sceneId);
		local level = x300517_GetAcceptLevel(sceneId, selfId)
		local recycleCount = GetQuestData(sceneId, selfId, MD_SHOUJI_MATERIAL_CYCLECOUNT[1], MD_SHOUJI_MATERIAL_CYCLECOUNT[2], MD_SHOUJI_MATERIAL_CYCLECOUNT[3])
		local ExpBonus = x300517_g_ExpBonus*level*2^recycleCount
		AddQuestExpBonus(sceneId,ExpBonus)
		
		AddQuestLogCustomText(sceneId, MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip);
		
	EndQuestEvent();
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end
