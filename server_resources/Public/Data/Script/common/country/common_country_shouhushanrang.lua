-- �ű�ID
x300305_g_ScriptId              = 300305
-- Name
x300305_g_MissionName           = "�����ҡ��ػ�����"


function x300305_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    local isQingLong = IsQinglongZhuque( sceneId, selfId, 0)
    local isZhuQue = IsQinglongZhuque( sceneId, selfId, 1)
	if isQingLong ~= 1 and isZhuQue ~= 1 then
		return
	end

	AddQuestNumText( sceneId, x300305_g_ScriptId, x300305_g_MissionName, 3, 1)
end

function x300305_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)	--����������ִ�д˽ű�
    if idExt == 1 then
        local Readme_1 = "#Y�����ҡ��ػ�����#W#r #r"
        local Readme_2 = "\t�����Ը�⽫�����ڵ��ػ�λ�����ø����ĸ�������#r"
        local Readme_3 = "\t�������Ϊһʱ���첻���뵣���ػ��ˣ���ô�ҽ������侲��������������������Ѿ�������#G��˼����#W����ô�ҿ��԰�����������ػ���������#r"
        local Readme_4 = "\tÿ��#G����������#W���κ�ʱ�䣬����������������������ã�����#Gÿ��#Wֻ������#Gһ��#W������Ҫ�������ػ�λ�úʹ�Ȩ#G����#W����#G������#W��#r"
        local Readme = Readme_1..Readme_2..Readme_3..Readme_4
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, Readme)
        EndQuestEvent( sceneId)
        DispatchQuestEventList( sceneId, selfId, NPCId)
        DispatchQuestInfo( sceneId, selfId, NPCId, x300305_g_ScriptId, -1)
    end
end

function x300305_ProcAcceptCheck( sceneId, selfId, NPCId)
    -- print( "=====>>>>>", "x300305_ProcAcceptCheck" )
    local isQingLong = IsQinglongZhuque( sceneId, selfId, 0)
    local isZhuQue = IsQinglongZhuque( sceneId, selfId, 1)
	if isQingLong ~= 1 and isZhuQue ~= 1 then
        Msg2Player( sceneId, selfId, "�㲻����������ȸ�ػ�", 8, 3)
		return 0
	end

    local day, week = GetWeek()
    if day == 0 then
        Msg2Player( sceneId, selfId, "�ػ����ղ�������", 8, 3)
		return 0
    end

	return 1
end

function x300305_ProcAccept( sceneId, selfId)
    -- print( "=====>>>>>", "x300305_ProcAccept" )
    CountryGuildDemise( sceneId, selfId)
end


