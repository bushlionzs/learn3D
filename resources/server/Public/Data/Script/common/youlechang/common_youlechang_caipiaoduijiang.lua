x310336_g_ScriptId 		= 310336
-- ����ȯ�һ�
x310336_g_ScriptName	= "��ȡ��͸�󽱣�"

x310336_g_SubmitItem	= 12035005 -- �޵�������

x310336_g_TitleInfo		= "#Y�����ˡ�������͸��\n\t#W������͸�󽱣��ǿ���һ�ʾ޶�ĲƸ������ĵ�������������˭�أ�\n\t������������˼䡤�����������˵�����\n\t��������û���н����ǵ����ܼ������������������Ҫ�������������˵ļһ��Ҫ�ǵ�ÿ�������￴���ң����ѣ�"
		
x310336_g_GameId = 1041
function x310336_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--����������ִ�д˽ű�
	if GetGameOpenById(x310336_g_GameId) <= 0 then
		Msg2Player(sceneId,selfId,"�˻�ѹر�",8,3)
		return
	end
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x310336_g_TitleInfo)
		
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x310336_g_ScriptId, x310336_g_ScriptId)
end

--�о��¼�
function x310336_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	--local state = GetQuestStateNM( sceneId, selfId, NPCId, x310336_g_MissionId)
    AddQuestNumText(sceneId,x310336_g_ScriptId,x310336_g_ScriptName,3,0)
end

function x310336_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--��ȷ����
function x310336_ProcAccept( sceneId, selfId )

	local bagIndex = FindFirstBagIndexOfItem( sceneId, selfId, x310336_g_SubmitItem)
	if bagIndex < 0 then
		local msg = format("û��#{_ITEM%d}��", x310336_g_SubmitItem)
		Msg2Player( sceneId, selfId, msg, 8, 3)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		return
	end
	local firstTime = GetItemParam( sceneId, selfId, bagIndex, 8, 2)
	local currtime = GetDayOfYear()
	if currtime ~= firstTime then
		Msg2Player( sceneId, selfId, "�Ѿ������˱����ڣ��޷��һ�����,�붪���˵��ߣ�", 8, 3)
		return
	end
	
	local index = GetItemParam( sceneId, selfId, bagIndex, 4, 2 )
	
	local caipiao1 = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1)
	local caipiao2 = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1)
	local caipiao3 = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1)
	local caipiao4 = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2)
	local caipiao5 = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2)
	local caipiao6 = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2)
	local caipiao7 = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2)
	
	if caipiao1 == -1 and caipiao2 == -1 and caipiao3 == -1 and caipiao4 == -1 and
		caipiao5 == -1 and caipiao6 == -1 and caipiao7 == -1 then
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ�����ڻ�û�п������˺���", 8, 3)
		return
	end
	
	local ret = 0
	if index == caipiao1 then
		ret = 1
	elseif index == caipiao2 then
		ret = 1
	elseif index == caipiao3 then
		ret = 1
	elseif index == caipiao4 then
		ret = 1
	elseif index == caipiao5 then
		ret = 1
	elseif index == caipiao6 then
		ret = 1
	elseif index == caipiao7 then
		ret = 1
	end
	
	if ret == 0 then
		Msg2Player( sceneId, selfId, "�ܱ�Ǹ�������еĺ��벻�ڽ����ѿ��������˺���֮��", 8, 3)
		return
	end
	
	DelItem( sceneId, selfId, x310336_g_SubmitItem, 1)
	
	GamePlayScriptLog(sceneId, selfId, 1612)
	
	local count = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)-1000
	AddMoney(sceneId,selfId,1,count*1000)
	
	Msg2Player( sceneId, selfId, format("��ϲ��������͸�󽱣�������#{_MONEY%d}�����Ľ�����", count*1000), 8, 3)
end