x310056_g_scriptId = 310056 


x310056_g_DestSceneName1 = "����"
x310056_g_DestSceneName2 = "��ɳĮ"
x310056_g_DestSceneName3 = "��˹��ԭ"
x310056_g_DestSceneName4 = "��������"
x310056_g_DestSceneName5 = "��ռͥ�۹�"
x310056_g_DestSceneName6 = "���ΰ뵺"
x310056_g_DestSceneName7 = "���ݵ�"
x310056_g_DestSceneName8 = "ӡ�Ⱥ�"
x310056_g_DestSceneName9 = "���Ŵ���"
x310056_g_DestSceneId = {7,10,16,19,22,25,29,32,35}


function x310056_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--��������
	if sceneId == 7 then
	local Positionx1 = 111
	local Positionz1 = 169
	local distanceRet = 5 * 5 - (Positionx1 - PlayerPosX) * (Positionx1 - PlayerPosX) - (Positionz1 - PlayerPosZ) * (Positionz1 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx1, Positionz1 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�������ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--��ɳĮ����
	elseif sceneId == 10 then
	local Positionx2 = 211
	local Positionz2 = 109
	local distanceRet = 5 * 5 - (Positionx2 - PlayerPosX) * (Positionx2 - PlayerPosX) - (Positionz2 - PlayerPosZ) * (Positionz2 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx2, Positionz2 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�ں�ɳĮ�ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
		--��˹��ԭ����
	elseif sceneId == 16 then
	local Positionx3 = 90
	local Positionz3 = 198
	local distanceRet = 5 * 5 - (Positionx3 - PlayerPosX) * (Positionx3 - PlayerPosX) - (Positionz3 - PlayerPosZ) * (Positionz3 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx3, Positionz3 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�ڲ�˹��ԭ�ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
			--������������
	elseif sceneId == 19 then
	local Positionx4 = 128
	local Positionz4 = 47
	local distanceRet = 5 * 5 - (Positionx4 - PlayerPosX) * (Positionx4 - PlayerPosX) - (Positionz4 - PlayerPosZ) * (Positionz4 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx4, Positionz4 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�ڲ��������ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
		--��ռͥ�۹�����
	elseif sceneId == 22 then
	local Positionx5 = 160
	local Positionz5 = 176
	local distanceRet = 5 * 5 - (Positionx5 - PlayerPosX) * (Positionx5 - PlayerPosX) - (Positionz5- PlayerPosZ) * (Positionz5 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx5, Positionz5 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�ڰ�ռͥ�۹��ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--���ΰ뵺����
	elseif sceneId == 25 then
	local Positionx6 = 181
	local Positionz6 = 64
	local distanceRet = 5 * 5 - (Positionx6 - PlayerPosX) * (Positionx6 - PlayerPosX) - (Positionz6- PlayerPosZ) * (Positionz6 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx6, Positionz6 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�����ΰ뵺�ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--���ݵ�����
	elseif sceneId == 29 then
	local Positionx7 = 100
	local Positionz7 = 100
	local distanceRet = 5 * 5 - (Positionx7 - PlayerPosX) * (Positionx7 - PlayerPosX) - (Positionz7- PlayerPosZ) * (Positionz7 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx7, Positionz7 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�ھ��ݵ��ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--ӡ�Ⱥ�����
	elseif sceneId == 32 then
	local Positionx8 = 100
	local Positionz8 = 100
	local distanceRet = 5 * 5 - (Positionx8 - PlayerPosX) * (Positionx8 - PlayerPosX) - (Positionz8- PlayerPosZ) * (Positionz8 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx8, Positionz8 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."��ӡ�Ⱥ��ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--���Ŵ�������
	elseif sceneId == 35 then
	local Positionx9 = 100
	local Positionz9 = 100
	local distanceRet = 5 * 5 - (Positionx9 - PlayerPosX) * (Positionx9 - PlayerPosX) - (Positionz9- PlayerPosZ) * (Positionz9 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("��Ӧ����[%d,%d]ʹ�ô���Ʒ��", Positionx9, Positionz9 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --ɾ����Ʒ
		local message = GetName(sceneId, selfId)
		message = message.."�����Ŵ����ٳ��˻����Ǿ�"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	else
		local strText = format("��������������޷��ٻ��������Ǿ���" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310056_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310056_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x310056_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310056_OnDeplete( sceneId, selfId )

	return 0
end

function x310056_OnActivateOnce( sceneId, selfId )
end

function x310056_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310056_OnDie(sceneId, selfId, killerId)--�����������־
	
	x310056_UpdateTopList(sceneId, killerId)
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

function x310056_UpdateTopList(sceneId,selfId)

	local lastday = GetQuestData( sceneId, selfId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3] )
	local curCount = GetQuestData( sceneId, selfId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3] )
	local curday = GetWeekFirstDay()
	if lastday ~= curday then
		curCount = 0
	end
	curCount = curCount + 1
	SetQuestData( sceneId, selfId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3], curCount )
	SetQuestData( sceneId, selfId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3], curday )
	
	SendToplistKeyValue2GL(sceneId, selfId, TULONG_TOPLIST, curCount)
	
end