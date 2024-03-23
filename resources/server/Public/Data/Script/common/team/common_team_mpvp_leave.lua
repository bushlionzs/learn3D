--##############################################
--##������������뿪�����ű� by rj 2010-10-29 ##
--##############################################

x303103_g_ScriptId          		= 303103
x303103_g_MissionName       		= "�ص���"
x303100_g_LeaveToSceneIdAry		    = {0, 0, 0, 0}								--�Ĺ��ӱ��������뿪ʱ�˻س��� id
x303100_g_LeaveToPosAry		     	= {{168, 68}, {168, 68}, {168, 68}, {168, 68}}		--�Ĺ��ӱ��������뿪ʱ�˻س�������

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303103_ProcEnumEvent(sceneId, selfId, targetId, missionId)

    AddQuestNumText(sceneId, x303103_g_ScriptId, x303103_g_MissionName, 3)
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303103_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--�������ݿ⿪��
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end

   	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "\t������ѱ������뿪��������������޷��յ�����ս��֪ͨ���Ƿ��뿪�������������")
 	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x303103_g_ScriptId, -1)
    return
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303103_ProcAcceptCheck(sceneId, selfId, npcId)

	--���ݲ�ͬ���ҵ��򵽲�ͬ���������ͼ
	local nCountry = GetCurCountry(sceneId, selfId)
	NewWorld
		(
		sceneId, 
		selfId, 
		x303100_g_LeaveToSceneIdAry[nCountry + 1], 
		x303100_g_LeaveToPosAry[nCountry + 1][1],
		x303100_g_LeaveToPosAry[nCountry + 1][2], 
 		x303103_g_ScriptId
 		)
end
