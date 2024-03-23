
--MisDescBegin
--�ű���
x550525_g_ScriptId = 550525


--�����ı�����
x550525_g_MissionName="ɽկ��Ԯ������"
--x550525_g_CountryID = 3
--MisDescEnd

x550525_g_ChuanSong_X = 226.975891
x550525_g_ChuanSong_Z = 24.956709

function x550525_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --ս��δ����
    if GetGuildBattleStatus(sceneId) ~= 3 then
        return
    end

    --����A��Ӫ������Ч
	--�õ������������A��B��
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
     local nFlag = 0
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag == 0 then
	    AddQuestNumText(sceneId,x550525_g_ScriptId,"��Ԯ����",13,1)
    end
end


function x550525_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

	if GetGuildBattleStatus(sceneId) ~= 3 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "ս��δ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

    --����A��Ӫ������Ч
	local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
    local nFlag = 0
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag ~= 0 then
        return
    end

    SetPos(sceneId,selfId,x550525_g_ChuanSong_X,x550525_g_ChuanSong_Z)


end

--********************
--����������
--**********************************
function x550525_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x550525_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x550525_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x550525_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550525_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x550525_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

