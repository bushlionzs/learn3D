                                                                                                                --������


--�ű��� 301022




--��̬������ʼ������

x301022_g_MissionId 	= 6602
x301022_g_ItemId 		= 12030006
x301022_g_ScriptId 		= 700003


--���ɺ�����ʼ************************************************************************

function 		x301022_OnCreate(sceneId,growPointType,x,y)

	--����
	local ItemBoxId = ItemBoxEnterScene(x,y,30,sceneId,0,x301022_g_ItemId)


end






--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301022_OnOpen(sceneId,selfId,targetId)
 	if IsHaveQuest(sceneId,selfId, x301022_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x301022_g_ItemId) < 10 then
			return 0
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���޷�������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û���������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301022_OnRecycle(sceneId,selfId,targetId)
    return CallScriptFunction( x301022_g_ScriptId, "OnGetHuoPaoDan", sceneId, selfId )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301022_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301022_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
