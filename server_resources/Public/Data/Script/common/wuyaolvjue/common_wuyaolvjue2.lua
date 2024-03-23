x310022_g_ScriptId = 310022
--x310022_g_MD_AcceptTime = 240

x310022_g_MD_ItemMission = {  {itemId=13013301, mission=8006}, {itemId=13013302, mission=8007}, {itemId=13013303, mission=8008}, {itemId=13013304, mission=8009} }
x310022_g_MissionCommentId = 1103

x310022_g_ItemUsePosition = {	{id=13013300, buff=7053, r=10, x1=75, z1=60, x2=59, z2=54, x3=63, z3=56, find1=42002, find2=42003, find3=42004, sceneName="���˹�һ��", mission=8005, usedItem ="ʼҫ�ᾧ" ,destItem="��ҫ�ᾧ", scene=7 }, 
								{id=13013301, buff=7054, r=10, x1=74, z1=24, x2=106, z2=98, x3=101, z3=69, find1=43001, find2=43002, find3=43003, sceneName="�����˹ȶ���", mission=8006, usedItem ="��ҫ�ᾧ" ,destItem="��ҫ�ᾧ", scene=8  },
								{id=13013302, buff=7055, r=10, x1=103, z1=49, x2=36, z2=95, x3=48, z3=45, find1=44003, find2=44004, find3=44005, sceneName="���˹�����", mission=8007, usedItem ="��ҫ�ᾧ" ,destItem="��ҫ�ᾧ", scene=9  },
								{id=13013303, buff=7056, r=10, x1=34, z1=37, x2=72, z2=58, x3=72, z3=15, find1=45003, find2=45004, find3=45005, sceneName="���˹��Ĳ�", mission=8008, usedItem ="��ҫ�ᾧ" ,destItem="��ҫ�ᾧ", scene=10  },
								{id=13013304, buff=7057, r=10, x1=20, z1=84, x2=20, z2=84, x3=20, z3=84, find1=46004, find2=46004, find3=46004, sceneName="���˹����", mission=8009, usedItem ="��ҫ�ᾧ" ,destItem="" , scene=11 }
								}

x310022_g_MissionScene = { {mission=8005, scene=7 }, 
							{mission=8006, scene=8},
							{mission=8007, scene=9},
							{mission=8008, scene=10} 
							}

x310022_g_AwardItemId = 12030027
x310022_g_AbandonMessage	= "�����������%s"
x310022_g_AcceptMessage		= "�����������%s"
x310022_g_CompleteMessage	= "�����������%s"

function x310022_HaveAccepted(sceneId, selfId)

	local day = GetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3])
	if day > 0 then
		return 1
	end
	return -1
end

function x310022_ResetMission( sceneId, selfId, itemId, MissionId )
	for i, item in x310022_g_MD_ItemMission do
		if item.itemId == itemId then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 
					
			DelQuestNM( sceneId, selfId, MissionId )
			
			--���ǰ������
			local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, item.mission )
			if FrontMissiontId1 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
					return 0--���ǰ������û��ֱ�ӷ���
				end
			end
			if FrontMissiontId2 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
					return 0--���ǰ������û��ֱ�ӷ���
				end
			end
			if FrontMissiontId3 ~= -1 then
				if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
					return 0--���ǰ������û��ֱ�ӷ���
				end
			end
			
			--PrintNum(itemId)
			local ret = AddQuestNM( sceneId, selfId, item.mission)
			if ret < 1 then
				if ret == -2 then
					local strText = "�����������������ʧ��"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				elseif ret == -1 then
					local strText = "��������,�������ʧ��"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				else
					local strText = "�������ʧ��"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
				end
				
			else
				
				if item.mission == 8006 then
					SetQuestParam( sceneId, selfId, 8006, MP_CIRCLE, 1 )
				elseif item.mission == 8007 then
					SetQuestParam( sceneId, selfId, 8007, MP_CIRCLE, 2 )
				elseif item.mission == 8008 then
					SetQuestParam( sceneId, selfId, 8008, MP_CIRCLE, 3 )
				elseif item.mission == 8009 then
					SetQuestParam( sceneId, selfId, 8009, MP_CIRCLE, 4 )
				end
				misIndex = GetQuestIndexByID( sceneId, selfId, item.mission )
				SetQuestByIndex( sceneId, selfId, misIndex, 2, level )

				x310022_SetRandPosition(sceneId, selfId, item.mission)
			end

			return
		end
	end	
end

function x310022_NextDayRest(sceneId, selfId)
	--local lastDay = LuaGetThatDayTime(lasttime)
	local lastDay = GetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3])

	local today = GetDayOfYear()
	if today ~= lastDay then 
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], 0)
	end
end

function x310022_SetRandPosition(sceneId, selfId, MissionId)
	local rp = random(1, 3)
	SetQuestParam( sceneId, selfId, MissionId, 5, rp )		
end

function x310022_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--if x310022_HaveAccepted(sceneId, selfId) > 0 then
		--return
	--end
	if IsHaveQuestNM( sceneId, selfId, 8005 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8006 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8007 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8008 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8009 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8000 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8001 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8002 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8003 ) > 0 then
		return 0
	elseif IsHaveQuestNM( sceneId, selfId, 8004 ) > 0 then
		return 0
	end
	
	if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then
		AddQuestTextNM(sceneId, selfId, targetId, x310022_g_MissionCommentId, 13, -1)
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
		AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
		return 1
	end
    
	return 0
end

function x310022_ProcEventEntry( sceneId, selfId, targetId, MissionId, selectId )

	if MissionId == x310022_g_MissionCommentId then
		local str;
		local contentStr = "";
		
		if selectId == -1 then
			contentStr = "\t�ڱ���������һ������#G���˹ȵĵط�#W����˵����һλ���������￪������һ�����ɽ�Ȳ���ÿһ�������һ�������#G���#W���Ӷ����ճ��ɣ���ɽ�����������"
		elseif selectId == 0 then
			contentStr = "\t���Ǻ�������������������˸��ָ����������ޣ������ڴ˾ۼ�����û�к���������ʱ������ƣ�����ħͷҲ������������Ҹ���ռ���˵��̣����˹ȴӴ�����������Ϊ��һ������������һ���˼��ɾ������һ���������ĵ�����"
		elseif selectId == 1 then
			contentStr = "\t�����ͷ���ҫ�������������Ƴ����������˵�̫ƽ��������Ҳ֪��#G��ҫ�ᾧ#W�����飬���������ͬ��Ҫ��#G��ҫ�ᾧ#W����������ҵ��飬��������˹ȵ����֮�У�Ҳ�ֱ��Ӧ����ҫ��������������������һ��ʼҫ�ᾧ����һ����ʹ������������ʼҫ������������ʱӵ��ȫ����ҫ��ת����ħ��֣���������ҫ��ת���ֳ���ҫ�����ԣ����˳���Ļ���������Щ���ｫ���ü�����ҫ�Ľᾧ�����һ����ֱ���㵽�����˹���㣬������ҫ֮�������ܷ���#G��ҫ�ɾ�#W��ʹ���˹��е�����һ������"
		elseif selectId == 2 then
			contentStr = "\t��Ϊ��ʦ�ĵ��ӣ��ұ�Ӧ�߾�ȫ�����������ħ��������е�������ֻ�Ǻܲ������ҷ������ޣ�ʵ�����ԶԸ�������ħ��"
		end
		
		local MissionName;
		if MissionId > 0 then
			MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
		end
		local str = "#Y";
		str = str..MissionName;
		str = str.."#W\n\n"..contentStr;
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		if selectId < 2 then
			AddQuestNumText(sceneId, MissionId, "����", 0, selectId+1)
		end
		DispatchQuestEventList(sceneId, selfId, targetId);
		
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		x310022_NextDayRest(sceneId, selfId)
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- ������Խ��������
				AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			else
				local strText = "δ֪�����޷����µ�����"
				if ret == -1 then
					strText = "�ȼ����㣬�޷����µ�����"
				elseif ret == -2 then
					strText = "�ȼ����ߣ��޷����µ�����"
				elseif ret == -3 then
					strText = "��Ǯ���㣬�޷����µ�����"
				elseif ret == -4 then
					strText = "�㲻�Ǳ�����ң��޷����µ�����"
				elseif ret == -5 then
					strText = "ְҵ���Ͳ������޷����µ�����"
				elseif ret == -6 then
					strText = "��Ӫ�������޷����µ�����"
				elseif ret == -7 then
					strText = "�����޴�����"
				end
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
	end
end

function x310022_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if x310022_HaveAccepted(sceneId, selfId) > 0 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�����Ѿ��ӹ����񣬲����ٽӡ�");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�����Ѿ��ӹ����񣬲����ٽӡ�",8,2)
			return 
	end

	if GetLevel(sceneId, selfId) < 65 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ȼ�����65���뵽�߾���ҫ�ɾ������˴���ȡ����");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ȼ�����65���뵽�߾���ҫ�ɾ������˴���ȡ����",8,2)
		return
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--���ǰ������û��ֱ�ӷ���
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- ��ȡ������������Ϣ
	if ret > 0 then -- ������Խ��������
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
		if ret > 0 then
			SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			
			SetQuestByIndex( sceneId, selfId, misIndex, 2, GetLevel(sceneId, selfId) )
			
			x310022_SetRandPosition(sceneId, selfId, MissionId)

			local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
			local message = format(x310022_g_AcceptMessage, MissionName);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, message);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId, message, 4, 2)
			GamePlayScriptLog(sceneId, selfId, 521)

		elseif ret == 0 then
			local strText = "�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "��������,�����������������"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -2 then
			local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	
	end
end

--�������
function x310022_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x310022_g_AbandonMessage, MissionName);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId, message, 8,2)
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())
	end
end

function x310022_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return
	end
	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
	if guid ~= -1 then --�����������ɵ�NPC
		if guid == npcGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
			AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
		end
	else
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	end
end

--����1����ɹ���0��������ʧ��
function x310022_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 

	local ret = CallScriptFunction( MISSION_SCRIPT, "ProcQuestSubmit", sceneId, selfId, targetId, selectId, MissionId )

	if ret >0 then
		SetQuestData(sceneId, selfId, MD_WUYAO_LVJUE_DATE[1], MD_WUYAO_LVJUE_DATE[2], MD_WUYAO_LVJUE_DATE[3], GetDayOfYear())

		GamePlayScriptLog(sceneId, selfId, 522)
	end
end

--��Ʒ�ı�
function x310022_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	
	return 0
end


function x310022_GetRand(sceneId, selfId)
	local level = GetLevel( sceneId, selfId )
	local rand =0;
	if level >= 40 and level <= 49 then
		rand = 90;
	elseif level >=50 and level <=59 then
		rand = 70;
	elseif level >=60 and level <=64 then
		rand = 50;
	elseif level >=65 and level <=74 then
		rand = 80;
	elseif level >=75 and level <=84 then
		rand = 70;
	elseif level >=85 then
		rand = 40;
	end
	return rand;
end
--ɱ������
function x310022_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	local bSign=0;

	for i, item in x310022_g_MissionScene do
		if item.mission == MissionId then
			if item.scene == sceneId then
				bSign = 1;
				break
			end
		end
	end
	
	if bSign == 0 then
		return
	end
	
	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID

		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if GetHp(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
							local rand=0;
							local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
							if GetQuestParam( sceneId, humanObjId, misIndex, 0 ) == 1 then
								rand = x310022_GetRand(sceneId, humanObjId)
							end

							local InstIndex = 1
							ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
							local dropRand = random(1, 100);
							
							if rand ~= 0 and dropRand <= rand then
							--Ҫ�ռ��ĸ�������ƷID�������ʣ�һ��������
								if HaveItem( sceneId, humanObjId, ItemID ) <= 0 then --���û�������Ʒ 
									if GetBagSpace(sceneId, humanObjId) > 0 then
										BeginQuestEvent(sceneId)
										local strText = format( "������#G@itemid_%d", ItemID)
										if strText == nil then
											strText = "";
										end
										AddQuestText( sceneId, strText )
										EndQuestEvent( sceneId )
										DispatchQuestTips( sceneId, humanObjId )
										x310022_ResetMission( sceneId, humanObjId, ItemID, MissionId )
									else
										local strText = "��������,�����������ɱ��"
										BeginQuestEvent(sceneId)
										AddQuestText(sceneId, strText);
										EndQuestEvent(sceneId)
										DispatchQuestTips(sceneId,humanObjId)
									end
								 end
							end
										

						end

					end--end
				end
			end
		end

end

--����ʹ����Ʒ����
function x310022_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--����������Ѿ����ֱ���˳�
	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --�õ���ƷID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--û���ҵ��������
		return 0
	end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	--if scene == -1 or sceneId ~= scene then --û���ҵ����������Ϣ
		--return 0
	--end
	local offset = -1;

	if IsHaveQuestNM( sceneId, selfId, 8005 ) > 0 then
		offset = 1;
	elseif IsHaveQuestNM( sceneId, selfId, 8006 ) > 0 then
		offset = 2;
	elseif IsHaveQuestNM( sceneId, selfId, 8007 ) > 0 then
		offset = 3;
	elseif IsHaveQuestNM( sceneId, selfId, 8008 ) > 0 then
		offset = 4;
	elseif IsHaveQuestNM( sceneId, selfId, 8009 ) > 0 then
		offset = 5;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local rp = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local rFind = 0;
	for i, item in x310022_g_ItemUsePosition do
		if item.id == ItemID then
			local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
			local rPositionx = 0
			local rPositionz =0
			
			if rp == 1 then
				rPositionx = item.x1
				rPositionz = item.z1
				rFind	= item.find1
			elseif rp == 2 then
				rPositionx = item.x2
				rPositionz = item.z2
				rFind	= item.find2
			elseif rp == 3 then
				rPositionx = item.x3
				rPositionz = item.z3
				rFind	= item.find3
			end

			scene = item.scene

		if scene == -1 or sceneId ~= scene then
			if offset ~= -1 then
				local strText = format("��Ӧ����%s(@npc_%d)ʹ�ô���Ʒ��", x310022_g_ItemUsePosition[offset].sceneName, rFind)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText)
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)
			end
			
			
			return 0
		end 

			local distanceRet = item.r * item.r - (rPositionx - PlayerPosX) * (rPositionx - PlayerPosX) - (rPositionz - PlayerPosZ) * (rPositionz - PlayerPosZ)

			if distanceRet <=0 then
				if offset ~= -1 then
					local strText = format("��Ӧ����%s(@npc_%d)ʹ�ô���Ʒ��", x310022_g_ItemUsePosition[offset].sceneName, rFind )
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText)
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId, selfId)
				end
				return 0
			else
				
				if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
					return 0
				end

				--ɾ����Ʒ
				EraseItem(sceneId, selfId, BagIndex)

				--������ʾ
				SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )

				BeginQuestEvent(sceneId)
				--AddQuestText(sceneId, dispStr)
				AddQuestText( sceneId, otherStr )
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId, selfId)

				if MissionId == 8009 then
					SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )         --by zheng
				end

				x310022_ProcQuestLogRefresh( sceneId, selfId, MissionId)
				--����Ч��
				
				impactId = item.buff;
				
				if impactId ~= -1 then
					SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
				end
				return 1
			end
		
		end
	end

	if posx > 0 then --��Ҫ���ص�
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
			local strText = format("��Ӧ����@sceneid_%d(@npc_%d)ʹ�ô���Ʒ��", scene, rFind )
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId, selfId)
			return 0
		end
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
		return 0
	end

	--ɾ����Ʒ
	EraseItem(sceneId, selfId, BagIndex)

	--������ʾ
	SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, dispStr)
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, selfId)

	--����Ч��
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end
	return 1
end


function x310022_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )	
	local str;
	str = GetQuestNameNM(sceneId, selfId, MissionId);
	--local maxcircle = GetQuestParam( sceneId, selfId, misIndex, MP_MAXCIRCLE )
	local circle;
	
	if MissionId == 8009 then
		local inst = GetQuestParam( sceneId, selfId, misIndex, 0 )
		if inst == 1 then
			circle = 5
		else
			circle= GetQuestParam( sceneId, selfId, misIndex, MP_CIRCLE )
		end
	else
		circle= GetQuestParam( sceneId, selfId, misIndex, MP_CIRCLE )
	end
	
	if circle ~= nil then
		str = str.."("..circle;
		str = str.."/".."5";
		str = str..")";
	end

	local rp = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local instData1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local instData2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local instDataStr1 = ""
	local instDataStr2 = ""

	if instData1 ~= nil and instData2 ~= nil then
		 instDataStr1 = format("(%d/1)", instData1 )
		 instDataStr2 = format("(%d/1)", instData2 )
	end

	local str_target="";
	local str_proc="";
	local str_tip="";
	local posfind;
	for i, item in x310022_g_ItemUsePosition do
		if MissionId == item.mission then
			local posText="";--ʹ��λ��
			if rp == 1 then
				posfind = item.find1;
			elseif rp == 2 then
				posfind = item.find2;
			elseif rp == 3 then
				posfind = item.find3;
			end

			if posfind ~= nil then
				posText = format("(@npc_%d)", posfind )
			end

			local sceneName = item.sceneName;--��������
			local usedItem = item.usedItem --��ʹ�õ���Ʒ����
			local destItem = item.destItem --ҪѰ�ҵ���Ʒ������
			str_proc = "\t��"..sceneName..posText.."ʹ��#G"..usedItem

			if posfind ~= nil then
				str_target = "  ��@npcsp_ָ���ص�_"..posfind.."ʹ��#G"..usedItem.."#W"..instDataStr1
			end
			if MissionId ~= 8009 then
				if instData1 > 0 then
					str_target = "  #W���#G"..destItem.."#W"..instDataStr2
					str_proc = "\t��#G"..sceneName.."#W���ܵ��ˣ����#G"..destItem
				end
			else
				if instData1 > 0 then
					str_target = ""
					str_proc = ""
				end
			end

	 		str_tip = "����"..sceneName..posText.."����ʹ��"..usedItem.."���ڽᾧ�ķ����ı�������ɱ�ֿ��Ի�ü�����һ��ҫ�ǵĽᾧ��"
			break
		end
	end

    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- ����
                                "",                 -- ��������
                                str_target,               --����Ŀ��
                                "",                         --����NPC
                                str_proc,                   --������
                                "",                --��������
                                str_tip        --����С��ʾ
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end