-------------------------------------------------------------------------
--��·
-------------------------------------------------------------------------
function x888894_AskTheWay( sceneId, selfId, sceneNum, x, y, tip )
	Msg2Player( sceneId, selfId, "@*;flagNPC;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
	Msg2Player( sceneId, selfId, "@*;flashNPC;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
end

-------------------------------------------------------------------------
--��·
-------------------------------------------------------------------------
function x888894_AskTheWayPos( sceneId, selfId, sceneNum, x, y, tip )
	Msg2Player( sceneId, selfId, "@*;flagPOS;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
	Msg2Player( sceneId, selfId, "@*;flashPOS;" .. sceneNum .. ";" .. x .. ";" .. y .. ";" .. tip, MSG2PLAYER_PARA )
end

-------------------------------------------------------------------------
--�ÿͻ��˲��ű���������UICommandID = 11
-------------------------------------------------------------------------
function x888894_PlaySound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId, 11)
end

-------------------------------------------------------------------------
--�ÿͻ���ֹͣ���ű�������
-------------------------------------------------------------------------
function x888894_StopSound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId, 12)
end

-------------------------------------------------------------------------
--�ÿͻ��˲��ŵƹ⣬UICommandID = 13
-------------------------------------------------------------------------
function x888894_PlayLight( sceneId, selfId, lightId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, lightId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,13)
end

-------------------------------------------------------------------------
--�ÿͻ���ֹͣ���ŵƹ�
-------------------------------------------------------------------------
function x888894_StopLight( sceneId, selfId, lightId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, lightId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,14)
end

-------------------------------------------------------------------------
--�ÿͻ��˲�����Ч��UICommandID = 15
-------------------------------------------------------------------------
function x888894_PlayEffect( sceneId, selfId, effectId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, GetSceneInfo(sceneId,"CLIENTRES"))
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,15)
end

-------------------------------------------------------------------------
--ֹͣ��Ч
-------------------------------------------------------------------------
function x888894_StopEffect( sceneId, selfId, effectId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, GetSceneInfo(sceneId,"CLIENTRES"))
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,16)
end

-------------------------------------------------------------------------
--�ÿͻ��˲���snd_info.tab���е����֣���Ϊ�������֣�
-------------------------------------------------------------------------
function x888894_PlayBkgSound( sceneId, selfId, soundId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, soundId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,17)
end

-------------------------------------------------------------------------
--�ÿͻ���ֹͣ���ű�������
-------------------------------------------------------------------------
function x888894_StopBkgSound( sceneId, selfId )
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,18)
end

-------------------------------------------------------------------------
--�ͻ������ְ�����ʾ�¼�
-------------------------------------------------------------------------
function x888894_ShowNewHelp( sceneId, selfId, tableId )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, tableId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,19)
end

-------------------------------------------------------------------------
--�ͻ������ֽ���������ʾ��Ϣ
-------------------------------------------------------------------------
function x888894_ShowNewUITips( sceneId, selfId, UITipId,nToggle )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, UITipId)
	UICommand_AddInt(sceneId, nToggle)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,20)
end

-------------------------------------------------------------------------
--֪ͨ�ͻ��˲��ž�ͷ��Ч
-------------------------------------------------------------------------
function x888894_PlayClientCameraEffect( sceneId, selfId, effectId,nToggle )
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, nToggle)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,21)
end

-------------------------------------------------------------------------
--����õ�廨��Ч,���߼���ϵͳ
-------------------------------------------------------------------------
function x888894_PlayClientRiseEffect( sceneId, selfId)
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,22)
end


-------------------------------------------------------------------------
--���ſͻ��˶�����Ч
-------------------------------------------------------------------------
function x888894_PlayClientAnimEffect( sceneId, selfI,effectId)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, 1)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,23)
end

-------------------------------------------------------------------------
--ֹͣ�ͻ��˶�����Ч
-------------------------------------------------------------------------
function x888894_StopClientAnimEffect( sceneId, selfId,effectId)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, effectId)
	UICommand_AddInt(sceneId, 0)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,23)
end

-------------------------------------------------------------------------
--���ſͻ��˳�����ɫ
-------------------------------------------------------------------------
function x888894_PlayClientMapColor( sceneId, selfId, colorId, nTime)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, colorId)
	UICommand_AddInt(sceneId, 1)
	UICommand_AddInt(sceneId, nTime)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,24)
end

-------------------------------------------------------------------------
--ֹͣ�ͻ��˳�����ɫ
-------------------------------------------------------------------------
function x888894_StopClientMapColor( sceneId, selfId, nTime)
	BeginUICommand(sceneId)
	UICommand_AddInt(sceneId, -1)
	UICommand_AddInt(sceneId, 0)
	UICommand_AddInt(sceneId, nTime)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,24)
end


-------------------------------------------------------------------------
--�򿪽���ָ��
-------------------------------------------------------------------------
function x888894_OpenWorldDirectory( sceneId, selfId)
	BeginUICommand(sceneId)
	EndUICommand(sceneId)
	DispatchUICommand(sceneId,selfId,25)
end

-------------------------------------------------------------------------
--ȡ�ù�������
-------------------------------------------------------------------------
function x888894_GetCountryName(sceneId,nCountryId)
	
	if nCountryId == 0 then
		return "¥������"
	elseif nCountryId == 1 then
		return "��ɽ����"
	elseif nCountryId == 2 then
		return "��������"
	elseif nCountryId == 3 then
		return "�ػ�����"
	end
	
	return ""
	
end

-------------------------------------------------------------------------
--�:���MD
-------------------------------------------------------------------------
function x888894_Feast_ClearMD(sceneId,selfId)

	local nFrom = MD_FEAST_BEGIN[1]
	local nTo   = MD_FEAST_END[1]

	SetQuestData(sceneId,selfId,nFrom,16,16,0)
	nFrom = nFrom + 1
	
	for i = nFrom,nTo do
		SetQuestData(sceneId,selfId, i, 0, 32, 0)
	end
end


-------------------------------------------------------------------------
--�:ȡ�õ�ǰID
-------------------------------------------------------------------------
function x888894_Feast_GetCurrentId(sceneId,selfId)
	return GetQuestData(sceneId,selfId,MD_FEAST_INDEX[1],MD_FEAST_INDEX[2],MD_FEAST_INDEX[3])
end

-------------------------------------------------------------------------
--�:���õ�ǰID
-------------------------------------------------------------------------
function x888894_Feast_SetCurrentId( sceneId,selfId,nFeastId)
	
	--����Ƿ���Ҫ���
	if nFeastId ~=  x888894_Feast_GetCurrentId(sceneId,selfId) then
		x888894_Feast_ClearMD(sceneId,selfId)
	end
	
	--���õ�ǰ�ID
	SetQuestData(sceneId,selfId,MD_FEAST_INDEX[1],MD_FEAST_INDEX[2],MD_FEAST_INDEX[3],nFeastId)
end


