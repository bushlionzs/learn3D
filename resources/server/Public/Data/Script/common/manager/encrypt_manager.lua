
x800100_g_ScriptId = 800100
x800100_g_MissionName = "�����㷨����ģ��"



--�����NPC��
function x800100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )	
end



--�������ť������������ִ�д˽ű�
function x800100_ProcEventEntry( sceneId, selfId, targetId,state,index )	
end


--���ܹ���ģ�飺
--���ܣ�1�����ɲ������µļ����㷨		
function x800100_OnEncryptManager( sceneId, selfId, enctyptId )	
	
	local answer = x800100_CheckLoginAnswer( sceneId, selfId )	

	if answer == 0 then		--��½�𰸴���	
		
		local bValid,nErrorCount,nOPMode = GetCheatActTableInfo( sceneId, selfId,9 )
		
		if bValid == 0 then
			--���ܹر�
			return 1
		end
		
		if nOPMode == 2 then		--�ߵ�
			x800100_MakeKickTime( sceneId, selfId )				
		elseif nOPMode == 3 then	--����
			x800100_DoLoginAnswer( sceneId, selfId )	
		end

		SetLoginAnswer(sceneId, selfId,3)		--�����ظ�����
		return 1
	elseif answer == 1 or answer == 2 then
		--�����������ʱ
		local bValid,nErrorCount,nOPMode = GetCheatActTableInfo( sceneId, selfId,0 )
		
		if bValid == 0 then
			--���ܹر�
			return 1
		end
				
		if nOPMode == 2 then		--�ߵ�
			x800100_MakeKickTime( sceneId, selfId )				
		elseif nOPMode == 3 then	--����
			x800100_DoLoginAnswer( sceneId, selfId )	
		end
		return 1
	end

	local encryptCount = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT )

	if encryptCount == 0 then
		SetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX, -1 )
	end

	if encryptCount == 0 or encryptCount >= 5 then

		--ÿ5���Ӳ���һ��������
		SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT, 0 )
		local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
		SetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX, currIndex )
		SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX, enctyptId )
		encryptCount = 0

	end

	SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT, encryptCount+1 )
	
	--����ͻ���δ��Ӧʱ�䣬���δ��Ӧ����5���ӣ����ߵ������
	local unrespondCount = GetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME )
	if unrespondCount >= 5 then
		--��������
		return 0
	end

	SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, unrespondCount+1 )

	--����Id�õ���ǰ������Ϣ
	local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
	local scriptId,result,fnName = GetEncryptInfo( sceneId, selfId ,currIndex )

	--ÿ���ӷ���һ�μ����㷨
	CallScriptFunction( scriptId, fnName, sceneId, selfId ,currIndex )

	return 1
	
end


--����½ʱ����֤���
--����ֵ��	0����½�𰸴���	���������⣨��Ȼ�������ߵ���
--			1�������������ߵ�	
--			2�����볬ʱ������������ڷ����ԡ��ߵ�
--			3���ɹ�
function x800100_CheckLoginAnswer( sceneId, selfId )	
	
	local answer = GetLoginAnswer(sceneId, selfId)
	return answer

end


--��½ʱ������󣬽�����Ϸ���ٴδ���
function x800100_DoLoginAnswer( sceneId, selfId )	
	
	if GetGameOpenById(1020)>0 then

		if CallScriptFunction(300824, "StartDati", sceneId, selfId, 1020)>0 then
		end
		
	end

end

function x800100_OnDatiSuccess(sceneId,selfId)
end

function x800100_OnDatiFail(sceneId,selfId)
end


--���ͻ��˼��ܽ��
--�ȼ�鵱ǰ�����㷨�����ʧ�ܲ������ݴ�ʱ�����������ϴμ����㷨�Ƿ�ƥ��
function x800100_OnCheckEncrypt( sceneId, selfId, result )	
	
	local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
	local scriptId,tabResult,fnName = GetEncryptInfo( sceneId, selfId ,currIndex )

	if result == tabResult then

		--��֤ͨ�����ؼƿͻ�����Ӧʱ��
		SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, 0 )
		return 1

	else

		local lastIndex = GetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX )	
		if lastIndex ~= -1 then
			local scriptId2,tabResult2,fnName2 = GetEncryptInfo( sceneId, selfId ,lastIndex )
			if result == tabResult2 then
				--��֤ͨ�����ؼƿͻ�����Ӧʱ��
				SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, 0 )
				return 1
			end
		end

	end

	--������֤ʧ�ܣ�����
	return 0

end


--��������ʱ��
function x800100_MakeKickTime( sceneId, selfId )	
	
	local kickTime = GetEncryptKickTime(sceneId, selfId)

	if kickTime ~= NumberCastIntToUInt(-1) then
		--�Ѵ��ڱ���״̬
		return 
	end

	--����ʱΪ30--120��
	kickTime = mod(600,2400)
	SetEncryptKickTime(sceneId, selfId,kickTime)

end
