-------------------------
--***********************
--Const
--***********************
-------------------------

x800012_g_ScriptId 					= 800012
x800012_g_MissionName				= "��ʦͽ���뿪ʦ��"
x800012_g_CostMoneyPanShi		= 5000
x800012_g_CostMoneyType			=	2
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x800012_g_ScriptId, x800012_g_MissionName,3,0);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800012_ProcEventEntry(sceneId, selfId, targetId)
	local Readme_1 = "#Y��ʦͽ���뿪ʦ��#r"
	local Readme_2 = "\t#W�ҿ��԰��������ʦ���Ĺ�ϵ��#r���Ƿ�Ҫ��ʦ�����ʦͽ��ϵ��"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x800012_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800012_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800012_ProcAccept(sceneId, selfId)

	
	if IsHaveMaster(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ͽ�ܣ��޷����ʦͽ��",8,2)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ͽ�ܣ��޷����ʦͽ��",8,3)
		return
	end
	
	--����ͨ�ʼ���ʦ��
	--�õ�ʦ��GUID
	local targetGUID = GetMasterGUID(sceneId, selfId);
	if targetGUID == -1 then
		return
	end
	local MasterName = GetFriendName( sceneId, selfId, targetGUID )
	
	local mail = format("���ź�������ͽ��%s���������ʦͽ��ϵ��", GetName(sceneId, selfId));
	SendSystemMail(sceneId, MasterName, mail);
	
	--����ִ���ʼ���ʦ��
	local MyGUID = GetGUID( sceneId, selfId )
	SendScriptMail( sceneId, MasterName, MAIL_BETRAYMASTER, MyGUID, 1, 0, selfId )
		--��ʦ
	BetrayMaster(sceneId, selfId);
	--��ͽ�ܵ���ʾ��Ϣ
	local Msg = format("���ź������������ʦ��%s��ʦͽ��ϵ", MasterName);
	Msg2Player(sceneId,selfId,Msg,8,2)
	Msg2Player(sceneId,selfId,Msg,8,3)
end