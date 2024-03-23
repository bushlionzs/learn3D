--���ʦ������

--�ű���
x800011_g_ScriptId	= 800011

x800011_g_MissionName	= "��ʦͽ������ͽ��"

--����ͽ�ܣ��۳���Ǯ
x800011_g_Gold			= 5000
x800011_g_CostMoneyType  		= 2
x800011_g_Item = 11990111
x800011_g_PrenticeCount = 5
--**********************************
--������ں���
--**********************************
function x800011_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x800011_g_ScriptId, x800011_g_MissionName,3,0);
end

function x800011_ProcEventEntry(sceneId, selfId, targetId, eventId, index)
	local	key	= index
	local guid
	local PrenticeName
	local	isHavePrentice	= 0
	local	str
	if key == 0 then
		BeginQuestEvent( sceneId )
		for i=0, x800011_g_PrenticeCount - 1 do
			guid = GetPrenticeGUID( sceneId, selfId, i )
			if guid ~= -1 then
				isHavePrentice	= 1
				PrenticeName	= GetFriendName( sceneId, selfId, guid )
				AddQuestText( sceneId, "#Y"..x800011_g_MissionName.."#W")
				AddQuestText( sceneId, "\t����ͽ�ܺ󣬲����ٴӴ��˼���ͽ���������������档�����ؿ��Ǻ�ѡ������λͽ�ܽ��ʦͽ��ϵ��")
				AddQuestNumText( sceneId, x800011_g_ScriptId, "��"..PrenticeName.."���ʦͽ��ϵ", -1, (i+1)*100 )
			end
		end
		if isHavePrentice == 0 then
			AddQuestText( sceneId, "�ܱ�Ǹ����������ʦ�����޷�����ͽ�ܡ�" )
		end
		EndQuestEvent( sceneId )
		DispatchQuestEventList( sceneId, selfId, targetId )
	end
	
	if key >= 100 and key < 10000 then
		key = floor(key/100)-1
		guid	= GetPrenticeGUID( sceneId, selfId, key )
		if guid ~= -1 then
			PrenticeName	= GetFriendName( sceneId, selfId, guid )
		end
		str	= format( "�˴�˵����Ҫ�Ķ���" )
		BeginQuestEvent( sceneId )
			--AddQuestText( sceneId, str )
			AddQuestNumText( sceneId, x800011_g_ScriptId, "��", -1, (key+1)*10000 )
		EndQuestEvent( sceneId )
		DispatchQuestEventList( sceneId, selfId, targetId )
	end
	
	if key >= 10000 then
			key = floor(key/10000)-1
			x800011_ProcAccept( sceneId, selfId, key )
	end
		
	--local Readme_1 = "#Y��ʦͽ������ͽ��#r"
	--local Readme_2 = "\t#W�ҿ��԰����������ͽ�ܵĹ�ϵ��#r���Ƿ�Ҫ����ͽ�ܣ�"
	--local Readme = Readme_1..Readme_2
	--BeginQuestEvent(sceneId);
	--AddQuestText(sceneId, Readme);
	--EndQuestEvent();
	--DispatchQuestInfo(sceneId, selfId, targetId, x800011_g_ScriptId,-1);

end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800011_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

--**********************************
--�о��¼�
--**********************************


--**********************************
--����
--**********************************
function x800011_ProcAccept( sceneId, selfId, index )
	
	local PrenticeGUID = GetPrenticeGUID( sceneId, selfId, index )
	if PrenticeGUID == -1 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ʦ�����޷�����ͽ�ܡ�",8,2)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ʦ�����޷�����ͽ�ܡ�",8,3)
		return
	end
	
	--if GetMoney( sceneId, selfId, x800011_g_CostMoneyType ) < x800011_g_Gold then
	--	local str = format("�ܱ�Ǹ���������е��ֽ���%d�����޷�����ͽ�ܡ�", x800011_g_Gold/1000);
	--	Msg2Player(sceneId,selfId,str,8,2)
	--	return
	--end
	
	--if HaveItemInBag(sceneId, selfId, x800011_g_Item) ~= 1 then
	--	local str = format("�ܱ�Ǹ���������е�û��@item_%d���޷�����ͽ�ܡ�", x800011_g_Item);
	--	Msg2Player(sceneId,selfId,str,8,2)
	--	return
	--end
	
	local PrenticeName	= GetFriendName( sceneId, selfId, PrenticeGUID )
	local selfName	= GetName( sceneId, selfId )

	--�۳����Ͻ�Ǯ
	--if CostMoney(sceneId, selfId, x800011_g_CostMoneyType, x800011_g_Gold) == -1 then
	--	Msg2Player(sceneId,selfId,"�۽�Ǯʧ�ܣ�",8,2)
	--	return
	--end
	--if DelItem(sceneId, selfId, x800011_g_Item, 1) ~= 1 then
	--	Msg2Player(sceneId,selfId,"����Ʒʧ�ܣ�",8,2)
	--	return
	--end
	
	local Msg = format("���ź������������ͽ��%s��ʦͽ��ϵ", PrenticeName);
	Msg2Player(sceneId,selfId,Msg,8,2)
	Msg2Player(sceneId,selfId,Msg,8,3)
	--����ͨ�ʼ���ͽ��
	SendSystemMail( sceneId, PrenticeName, "���ź�������ʦ��" .. selfName .. "���������ʦͽ��ϵ��" )
	--����ִ���ʼ���ͽ��
	SendScriptMail( sceneId, PrenticeName, MAIL_EXPELPRENTICE, 1, GetGUID(sceneId, selfId), 0, selfId )
	--���������Ż�
	ExpelPrentice( sceneId, selfId, PrenticeGUID, 2 )
end
