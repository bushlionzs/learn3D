x300932_g_ScriptId = 300932
x300932_g_MissionName = "�����ҡ��������"

function x300932_ProcEnumEvent( sceneId, selfId, targetId, index )
	if GetGuildID( sceneId, selfId ) == -1 then
		--���ڰ����
		return
	end
	
	--if GetGameOpenById(x300932_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300932_g_ScriptId, x300932_g_MissionName, 3)
	--end
end

function x300932_ProcEventEntry( sceneId , selfId , targetId , state , index )
	BeginQuestEvent(sceneId)
	local Readme_1 = "#Y�����ҡ��������#r#W"
	local Readme_2 = "\t���ã��𾴵����ռ���ߣ��������������������ǰ����ؽ��д��ã������ѡ�������أ������������κ����棬������Ҫ��������ص�����Ȩ��"
	local Readme = Readme_1..Readme_2
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300932_g_ScriptId, -1 );
end

function x300932_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

function x300932_ProcAccept( sceneId, selfId)
	
	
	
	--�����
	local nGuildId = GetGuildID(sceneId,selfId)
	if nGuildId < 0 then
		return
	end
	
	--�Ƿ��ǰ���
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= 5 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û��Ȩ��",8,3)
		Msg2Player(sceneId,selfId,"ֻ�а����ſ��Է�������ص�ӵ��Ȩ��",8,2)
        return
    end
	
	--����Ƿ��Ǿݵ��ػ����
	local nMapId0,nMapId1,nMapId2 = GetGuildLairdSceneId(nGuildId)
	if nMapId0 <= 0 then
		Msg2Player(sceneId,selfId,"�㲻����ص�����",8,3)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����İ��Ŀǰû���������Ȩ",8,2)
		return
	end
	
	--����Ƿ����ܱ�״̬
	if IsPasswordProtect(sceneId,selfId ) == 1 then
		return
	end
	
	--ִ�з�������
	GameBattleCancleLaird(sceneId,selfId)
	Msg2Player(sceneId,selfId,"�ɹ��������",8,3)
	Msg2Player(sceneId,selfId,"���ź������������������Ȩ��",8,2)
	Msg2Player(sceneId,selfId,"���ź��������������������Ȩ��",6,1)
	--������ʾ
end