--������������ add by ������090114��

--MisDescBegin

x300519_g_ScriptId = 300519
-- ��������ID
x300519_g_EscortMissionID           = 6450
x300519_g_EscortMissionID_End       = 6461
-- ��������
x300519_g_MissionName = "�����ˡ���������"
-- ����Ŀ���������(����)
x300519_g_EscortTarget0  = "�ҵ�@npc_%s"
-- ����Ŀ���������(����)
x300519_g_EscortTarget1  = "��%s��ȫ���͵�@npc_%d���"
-- ����δ���ʱNPC�Ի�����
x300519_g_MissionContinue   = "\t�㻹û��%s���͵�@npc_%d���أ�"

--MisDescEnd
-- ������ɱ��
-- ���������ź���
x300519_g_IsComplete        = 0 -- ��ɱ��
x300519_g_SubMission        = 1 -- ���������ţ�x300519_g_EscortTable������
x300519_g_Phase             = 2 -- ����׶Σ�0��Ѱ��������NPC��1����ʼ���Ͳ���������Ŀ��NPC����2��������ɣ��ص��������񷢲��˴�������
-- 
x300519_OneRoundCount	= 10
x300519_HighBonusCircleCount = 10		--ÿ�ռ����߽�
x300519_LevelToCapital	= 300		--������Ŀ�ʼ�ȼ�
-- �ھ�Ŀ�������
x300519_g_EscortTable     = 
{
                            { missionId=6450, escortType = 10,	npcGuid = 138505,	name = "������",
                            	targetGuid = 138109,	targetname = "��ͼ",	missionName = "��ƥ",
                            	finish = "\tлл�㣬�����������ˣ�����Ҫ������ȥ���ء�",
                            	getmiss = "\t������̫���ˣ�#Y@myname#W������Уξ��ͼ��Ҫһƥ����ս���������ǳ���ܹ�Ϊ����ʱ�ṩ�̺���ȵص�ս������������������ںܽ��ţ�ֻ��������Ұ���ƥ��ȫ���͵��������������Уξ@npc_138109����ȥ�ˣ���Ը��������æô��",
                            	intro = "\t��˷�ֳ��ʦ@npc_138505��Ҫ��ս���������أ���ȥ������������ʲô��Ҫ���æ�ġ�"
                            }, 
                            { missionId=6451, escortType = 11, npcGuid = 138270, name = "��ľ��", 
                            	targetGuid = 138263, targetname = "��ة�º�", missionName = "����",
                            	finish = "\t������һ���������ǳ���л�㣡", 
                            	getmiss = "\t�ղ�@npc_138263���������ߴ�������ʳ�ˣ��������ʵ�����Ѳ��������ܰ��Ұ��⳵��ʳ�͵�������ȥô��", 
                            	intro = "\t��֥��������ʳ���ҹ���������Ҫ��Դ����ȥũ����@npc_138270���￴����ʲô��Ҫ���æ�ġ�" 
                            }, 
                            { missionId=6452, escortType = 12, npcGuid = 138075, name = "Ү�ɷ�",
                            	targetGuid = 138055, targetname = "��ɭ",   missionName = "����",
                            	finish = "\t��������˭�ҵĺ����߶��ˣ��õģ��һ�����ҵ���ĸ�ģ�", 
                            	getmiss = "\t���������ã�#Y@myname#W���һ�����Ϊ��ô�������·��С�һ��ͻؼҶ������أ��ҵ���ʹ��ˣ��Ƚ�Ҳ���ã�����ɽ�������㣬�������鷳����Ұ����С���͵���������Уξ@npc_138055����ȥ����֪����һ������ܾ���", 
                            	intro = "\t��˵��ͻ�������峤@npc_138075������һЩ�鷳����ȥ��������û����Ҫ�����ġ�" 
                            }, 
                            { missionId=6453, escortType = 13, npcGuid = 138182, name = "�������������", 
                            	targetGuid = 138721, targetname = "��ʯ��վ",   missionName = "��",
                            	finish = "\t��л���ܼ�ʱ������͹������������������ء�", 
                            	getmiss = "\t#Y@myname#W�����������ã�@npc_138721���Ｑ����Щ��ʯ����Ҳ֪�������һ������̫��ȫ��������˵���㲻�������ǿ�����������ĳ����⳵��ʯ������˵Ӧ�ò���ʲô�鷳�ɣ�", 
                            	intro = "\t@npc_138182��������ȱ�����֣�����ȥ�Ǳ߰�æ��" 
                            }, 
                            { missionId=6454, escortType = 14, npcGuid = 138110, name = "׿��",
                            	targetGuid = 138114, targetname = "��ľ��", missionName = "����",
                            	finish = "\t����лл�㣬�������ǽ������ͻ�ܷ�ʢ��", 
                            	getmiss = "\t��������ĺ������Ƕ���������Ľ�������������ﲻ�����ϴ�ˮ����峤@npc_138114������һЩ����������������ֽ��ţ����鷳�������ȥô��", 
                            	intro = "\t����������ﺣ���ḻ����ȥ@npc_138110�Ǳ߿�����ʲô���԰���ϵġ�" 
                            }, 
                            { missionId=6455, escortType = 15, npcGuid = 138518, name = "��ͺ³",
                            	targetGuid = 138058, targetname = "������ͼ",   missionName = "��͢ʥ��", 
                            	finish = "\t������ô�����������ˡ�", 
                            	getmiss = "\t�⳵��װ���ǳ�͢��ʥ�̫�ӵ�����ɫ�˺ܾòž������㵣���������Ҫ��ְ�����ܵؽ����͵�@npc_138058���ǧ��Ҫ��©��������˽�Բ𿪲鿴����֪�������ȵĺ�������ʱ���Ǻ�Σ�յġ�", 
                            	intro = "\t�ҽӵ�һ�����񣬵���ϧ�鲻���������ɷ��������������������أ�ȥ��@npc_138518�ɣ�������������ġ�" 
                            }, 
                            
                            { missionId=6456, escortType = 10,	npcGuid = 139069,	name = "��ȫ",
                            	targetGuid = 139406,	targetname = "Ŭ������",	missionName = "��ƥ",
                            	finish = "\t��ȫ�����Ŀ����ܺá�",
                            	getmiss = "\t������̫���ˣ�#Y@myname#W���Ұ�����@npc_139406������ɫ��һƥ��������������ⷱæ��һʱ�Ѳ��������ܰ��ҽ��⿥���͸�����",
                            	intro = "\t������������˼��ܴ�ʦ@npc_139069��Ҫ�˰�æ���㲻��ȥ�����￴����"
                            }, 
                            { missionId=6457, escortType = 11, npcGuid = 140900, name = "����", 
                            	targetGuid = 139807, targetname = "��ң", missionName = "����",
                            	finish = "\t����ʳ���ĺ���ʱ�򣬷ǳ���л�㣡", 
                            	getmiss = "\t�ղ��������������ߴ�������ʳ�ˣ��������ʵ�����Ѳ��������ܰ��Ұ��⳵��ʳ�͵�@npcsp_������̳_139807��", 
                            	intro = "\t��@npcsp_�׼�����_140900����ƺ�����һ��ʶ������㲻��ȥ�����￴����" 
                            }, 
                            { missionId=6458, escortType = 41, npcGuid = 140902, name = "���޵���",
                            	targetGuid = 140400, targetname = "��ɽ����",   missionName = "Ů���",
                            	finish = "\t�����������֮�ˣ���ƶ����ϸ����һ����", 
                            	getmiss = "\t���������ã�#Y@myname#W������һλŮ���ǰ�����ԣ��������޷���͸�������������ܰ��������ҵ�ʦ����ɽ��������ȥô��", 
                            	intro = "\t��˵@npc_140902������ͨ��������������Ÿ������㲻��ȥ�����￴����" 
                            }, 
                            { missionId=6459, escortType = 13, npcGuid = 140550, name = "�ж�����", 
                            	targetGuid = 140200, targetname = "���Ļ�",   missionName = "��",
                            	finish = "\t��л���ܼ�ʱ������͹������������������ء�", 
                            	getmiss = "\t#Y@myname#W�����������ã�������ͭ���Ǹ�@npcsp_����Ӫ_140200����������л������ã������ҹ������ֻ���鷳������һ���ˡ�", 
                            	intro = "\t���@npc_140550����������һ����ͭ��׼��������Ӫ��ȥ����ȥ�����￴����û��ʲô�����æ�ġ�" 
                            }, 
                            { missionId=6460, escortType = 14, npcGuid = 140903, name = "��С��",
                            	targetGuid = 140007, targetname = "��ʿ��", missionName = "����",
                            	finish = "\t����лл�㣬����һ������ΰ����Ĵ�������⡣", 
                            	getmiss = "\t��������ĺ������Ƕ���������Ľ�������������ﲻ�����ΰｭ������@npc_140007������һЩ����������������ֽ��ţ����鷳�������ȥô��", 
                            	intro = "\t���������@npcsp_������_140903��������˴����ĺ�������ȥ�Ǳ߿�����ʲô���԰���ϵġ�" 
                            }, 
                            { missionId=6461, escortType = 15, npcGuid = 140554, name = "��Ա��",
                            	targetGuid = 139300, targetname = "������ʦ",   missionName = "��͢ʥ��", 
                            	finish = "\t������ô�����������ˡ�", 
                            	getmiss = "\t�⳵��װ�����Ҿ��׸���ɮ�ǵ�����Ǯ����Ҫ�������͵�������µ�@npc_139300���ǧ��Ҫ��©�˷�������˽�Բ𿪲鿴����֪������Щ����ʵ���ǲ������ԡ�", 
                            	intro = "\t�󶼵ĸ���@npc_140554������������µĸ�ɮ����һ�����¡���ȥ�����￴���ɡ�" 
                            }, 
}                                                                                                   

-- ��ʾ�����Ϣ
function x300519_OnCanCompleteMission( sceneId, selfId, targetId, MissionId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
        
        AddQuestText( sceneId, "\t��������¶������ˣ�" )
    EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId)
end

-- ��ʾ����δ���ʱNPC�ĶԻ���Ϣ
function x300519_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId)

    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
    if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
		return
    end
    -- ������NPC��GUID
    local npcGuid = x300519_g_EscortTable[id].npcGuid
    -- ����Ŀ��NPC��GUID
    local destGuid = x300519_g_EscortTable[id].targetGuid
    -- ���NPC��GUID
    local targetGuid = GetMonsterGUID( sceneId, targetId)
    local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )

    if npcGuid == targetGuid then
	--��ȡ���͵�NPC
	--print("busid"..GetBusId(sceneId, selfId))
	if (phase ~= 0) then
		return
	end
	
	BeginQuestEvent( sceneId)
		-- ��������
		AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
		-- ��������
		AddQuestText( sceneId, "#Y����������" )
		AddQuestText( sceneId, x300519_g_EscortTable[id].getmiss)
		AddQuestText( sceneId, " " )
		-- ����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺" )
		AddQuestText( sceneId, format( x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid) )

		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300519_GetExpAward ( sceneId, selfId, curlevel );
		local money,shengw = x300519_GetMoneyAward ( sceneId, selfId, curlevel );

		if(exp > 0) then
			AddQuestExpBonus(sceneId, exp)
		end
		if(money > 0) then
			AddQuestMoneyBonus2(sceneId, money)
		end

		if(shengw > 0) then
			AddQuestMoneyBonus5(sceneId, shengw)
		end

	EndQuestEvent()
	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId )

    elseif targetGuid == destGuid then -- ����Ŀ��NPC
	--print("busid"..GetBusId(sceneId, selfId))
        -- ��ʾ��ɻ�����Ϣ
	if (phase ~= 1) then
		return
	end
	
	if GetBusId(sceneId, selfId) <= 0 or IsValidMyselfBus(sceneId, selfId, MissionId) == 0 then	--����bus���������
		QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId)
	else
	        BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
			AddQuestText( sceneId, x300519_g_EscortTable[id].finish)
		EndQuestEvent()
		DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId)
	end
    elseif targetGuid == submitguid then
        BeginQuestEvent( sceneId)
            -- ��������
            AddQuestText( sceneId, "#Y"..x300519_g_MissionName)

		if (phase == 1) then
			AddQuestText(sceneId, format(x300519_g_MissionContinue, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid))
		elseif (phase == 0) then
	            AddQuestText( sceneId, "\t��������°����ˣ�" )		--Ҫ��
		end
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
    end
end

-- ����Ҫ���͵�Bus������������ʹ�����Զ��������
function x300519_OnIntoBusEvent( sceneId, selfId, targetId)
    --print( "x300519_OnIntoBusEvent" )
	local IsOwner = IsTheBusOwner( sceneId, selfId, targetId)
	if IsOwner == 1 then
		-- �������ұ������ø���
		AddBusMember( sceneId, selfId, targetId)
	end
end

function x300519_OnIntoBusAfter( sceneId, selfId, BusID)
    --print( "*****x300519_OnIntoBusAfter*****" )
end

function x300519_OnLeaveBusEvent( sceneId, selfId, BusId)
    --print( "�뿪Bus" )
end

function x300519_OnDie( sceneId, BusId, idKiller)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)	
	if (selfId == -1) then
		return
	end
	local MissionId = x300519_GetRandMissionId(sceneId, selfId);
	-- ������������
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	-- ��ɱ��
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 0)
	-- ��ǰ����׶α�ǣ�ÿ���׶��µ�����Ŀ�궼��һ����0��Ѱ��������NPC��1����ʼ���Ͳ���������Ŀ��NPC����2��������ɣ��ص��������񷢲��˴�������
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- ����Q���
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
	Msg2Player(sceneId, selfId, "����Ŀ���Ѿ������������½�ȡ����", 8, 3)
end

-- �ύ���񣬷���0��ʾʧ�ܣ�����1�ɹ�
function x300519_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId, farScriptId, constMD_Rand, retMissionId)
    return 1
end

-- ��ʾ������Ϣ
function x300519_ShowMissionInfo( sceneId, selfId, targetId, MissionId)
    
	local rand = 1
	-- �õ��������Ӧ�Ļ���Ŀ��
	for i, oneitem in x300519_g_EscortTable do
		if oneitem.missionId == MissionId then
			rand = i
			break;
		end
	end
	-- ���滤������Ŀ������
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_SubMission, rand)
    
    BeginQuestEvent( sceneId)
        -- ��������
        AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
 
        -- ��������
        AddQuestText( sceneId, "#Y����������" )
        AddQuestText( sceneId, x300519_g_EscortTable[rand].intro)
        AddQuestText( sceneId, " " )
        -- ����Ŀ��
        AddQuestText( sceneId, "#Y����Ŀ�꣺" )
        AddQuestText( sceneId, format( x300519_g_EscortTarget0, x300519_g_EscortTable[rand].npcGuid) )

    EndQuestEvent()
    DispatchQuestInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId, 1)
end

function x300519_CheckIfCanSubmit( sceneId, selfId, targetId, MissionId, misIndex)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
	if phase == 2 then
		return 1
	else
		return 0
	end
end

--�����м价�ڵ��ύ���򷵻�1������󻷽ڵ��ύ�������ű�����
function x300519_ProcQuestSubmitOrContinue( sceneId, selfId, targetId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)

	if phase == 0 then
		if IsBusMember(sceneId, selfId) == 1 then
			local strTip = "���Ѵ��ڻ���״̬���޷���ȡ�µĻ�������"
			Msg2Player(sceneId, selfId, strTip, 8, 3)				
			Msg2Player(sceneId, selfId, strTip, 8, 2)
			return 0
		end

		local PosX,PosZ = GetWorldPos( sceneId, selfId)
		-- ����Ҫ���͵�Bus
		local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
		if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
			return 0
		end
		local ObjID = CreateBus( sceneId, x300519_g_EscortTable[id].escortType, PosX, PosZ, 3, 3, 300519, selfId, 1210,MissionId,targetId)
		return 0

	elseif phase == 1 then
		-- ��û��Ͷ����Guid
		-- ɾ�����Ͷ���
		local busGuid = GetBusId(sceneId, selfId)
		if (busGuid < 0) or (IsObjValid (sceneId,busGuid) ~= 1) then						--���û��bus
			return	0			
		end
		if (MissionId ~= GetBusQuestID(sceneId, busGuid)) then	--�����ҵ�ǰbus������������Ҫ��bus,�������
			return	0			
		end
		DeleteBus( sceneId, busGuid, 1)
		-- update phase
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 2)
		-- set mission finish
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 1)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
		QuestCom( sceneId, selfId, MissionId)
		-- update Q panel
		x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
		return 0
	elseif phase == 2 then
		return 1
	else
		return 0
	end
end

function x300519_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)	

		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId, camp)
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusQuestID(sceneId, busId, MissionId)
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
		
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 1)		
		-- update Q panel
		x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)	
end

--��300501����
function x300519_AfterAccept( sceneId, selfId, targetId, MissionId, misIndex)
	-- ��ǰ����׶α�ǣ�ÿ���׶��µ�����Ŀ�궼��һ����0��Ѱ��������NPC��1����ʼ���Ͳ���������Ŀ��NPC����2��������ɣ��ص��������񷢲��˴�������
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- ����Q���
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
end

function x300519_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)

	MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--����������ύ�ˣ���ʾѡ��
	if submitguid ~= -1 and submitguid == npcGuid then	
		local state = GetQuestStateNM(sceneId, selfId, npcGuid, MissionId);
		AddQuestTextNM(sceneId, selfId, npcGuid, MissionId, state, -1);
		return 1
	end

	local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
	if (id == nil or id < 1 or id > getn(x300519_g_EscortTable) ) then
		return 0
	end
	-- ���ݱ���Ļ�������ŵõ�Դ��Ŀ��NPC��GUID
	local srcNpc = x300519_g_EscortTable[id].npcGuid
	local dstNpc = x300519_g_EscortTable[id].targetGuid
	if npcGuid == srcNpc then -- ������NPC
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if phase == 0 then
			AddQuestNumText( sceneId, MissionId, x300519_g_MissionName, 13)
		end
	elseif npcGuid == dstNpc then -- ����Ŀ��NPC
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if phase == 1 then
			AddQuestNumText( sceneId, MissionId, x300519_g_MissionName, 13)
		end
	end
    return 1
end

function x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

    
    
    if MissionId== nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 0
    end
        
    local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
    if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
		return 0
    end
    local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)

	local strName;
	strName = x300519_g_MissionName;
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	if (circle >= x300519_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end
	strName = strName.."("..circle;
	strName = strName.."/"..x300519_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex );
	local strReplyNPC = "@npc_"..reply_npcid
	BeginQuestEvent(sceneId)
	    if phase == 0 then -- �ҵ��ṩ����Ŀ���NPC
		--MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip
		AddQuestLogCustomText( sceneId,
					"",                             -- ����
					strName,          -- ��������
					format( "  "..x300519_g_EscortTarget0, x300519_g_EscortTable[id].npcGuid),
					strReplyNPC,             --����NPC
					format( x300519_g_EscortTarget0, x300519_g_EscortTable[id].npcGuid),
					x300519_g_EscortTable[id].intro,
					"" )
	    elseif phase == 1 then
		AddQuestLogCustomText( sceneId,
					"",                             -- ����
					strName,          -- ��������
					format( "  "..x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid),
					strReplyNPC,             --����NPC
					format( x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid),
					x300519_g_EscortTable[id].getmiss,
					"ע��;�в�Ҫ�뻤��Ŀ��̫Զ" )
	    elseif phase == 2 then
		AddQuestLogCustomText( sceneId,
					"",                             -- ����
					strName,          -- ��������
					"  ������ɣ��ظ�"..strReplyNPC,
					strReplyNPC,             --����NPC
					"������ɣ��ظ�"..strReplyNPC,
					x300519_g_EscortTable[id].finish,
					"" )
	    end
		
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if (phase ~= 0) then
			--������
			local curlevel = GetLevel(sceneId, selfId)
			local exp = x300519_GetExpAward ( sceneId, selfId, curlevel );
			local money,shengw = x300519_GetMoneyAward ( sceneId, selfId, curlevel );
			if(exp > 0) then
				AddQuestExpBonus(sceneId, exp)
			end
			if(money > 0) then
				AddQuestMoneyBonus2(sceneId, money)
			end
			if(shengw > 0) then
				AddQuestMoneyBonus5(sceneId, shengw)
			end
		end

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ����������
function x300519_ProcQuestAbandon(sceneId, selfId, MissionId)
	MissionId = x300519_GetRandMissionId(sceneId, selfId)

	local busGuid = GetBusId(sceneId, selfId)
	if (busGuid > 0) and (IsObjValid (sceneId,busGuid) == 1)then
		if (MissionId == GetBusQuestID(sceneId, busGuid)) then	--�����ҵ�ǰbus������������Ҫ��bus,�������
			DeleteBus( sceneId, busGuid, 1)
		end
	end

	CallScriptFunction( 300501, "ProcQuestAbandon", sceneId, selfId, MissionId)
end

function x300519_GetRandMissionId(sceneId, selfId)
	return x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
end

function x300519_OnBusStopWhenOwnerFarAway(sceneId, selfId)

	local strText = "���뻤��Ŀ��̫Զ������Ŀ��ֹͣ"

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,strText,8,2)
end

function x300519_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300519_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

function x300519_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)	
	if (selfId == -1) then
		--��Ҳ�����
		if (IsObjValid (sceneId,BusId) == 1) then
		    DeleteBus(sceneId, BusId,1)
		end
		return
	end

	local MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if (MissionId ~= GetBusQuestID(sceneId, BusId)) then	--�����ҵ�ǰbus������������Ҫ��bus,������
		return
	end

	DeleteBus(sceneId, BusId,1)
	x300519_RollbackBusMission (sceneId, selfId, MissionId)

end

function x300519_RollbackBusMission(sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)

	--ֻ�д��ڽ׶�1���ܻع�
	if (1 ~= GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)) then
		return
	end

	-- ��ɱ��
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 0)
	-- ��ǰ����׶α�ǣ�ÿ���׶��µ�����Ŀ�궼��һ����0��Ѱ��������NPC��1����ʼ���Ͳ���������Ŀ��NPC����2��������ɣ��ص��������񷢲��˴�������
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- ����Q���
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local strText = "�������뿪����Ŀ��ʱ����ã���Ļ���Ŀ����ʧ�ˣ������½�ȡ����"
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,strText,8,2)

end
function x300519_ClearBusMission(sceneId, selfId)
	local MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if MissionId >= x300519_g_EscortMissionID and MissionId <= x300519_g_EscortMissionID_End then	--����
		x300519_RollbackBusMission (sceneId, selfId, MissionId)
	end
end

function x300519_ProcEventEntry( sceneId, selfId, targetId, MissionId)
	return 1
end

--���������û�б仯�������ø߽��������������µ�����
function x300519_CheckDayChanged(sceneId, selfId)

	local lastDay = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--���ڱ仯
		x300519_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)	
		x300519_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

--���齱��
function x300519_GetExpAward(sceneId, selfId, startlevel)

	x300519_CheckDayChanged(sceneId, selfId)
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300519_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300519_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- �������룬���Ծ��鷭��
    BonusExp = BonusExp * 2
	return BonusExp;

end

--��Ǯ����
function x300519_GetMoneyAward(sceneId, selfId, startlevel)

	x300519_CheckDayChanged(sceneId, selfId)
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300519_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300519_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney, shengw;
end


function x300519_CheckSubmitNPC( sceneId,idMission,npcGUID )

	for i,item in x300519_g_EscortTable do
		if item.missionId == idMission then
			if item.npcGuid == npcGUID or item.targetGuid == npcGUID then
				return 1
			else
				return 0
			end
		end
	end
	
	return 0
end