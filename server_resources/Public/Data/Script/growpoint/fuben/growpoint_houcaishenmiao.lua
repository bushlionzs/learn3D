                                                                                                                --������


--�ű��� 301021




--��̬������ʼ������

x301021_g_MissionId 	= 6602 
x301021_g_ItemId 		= 12030006
x301021_g_ScriptId 		= 700003


--���ɺ�����ʼ************************************************************************

function 		x301021_OnCreate(sceneId,growPointType,x,y)

	--���� 
	local ItemBoxId = ItemBoxEnterScene(x,y,29,sceneId,0,x301021_g_ItemId)


end






--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301021_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x301021_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,targetId) == 0 then
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
function	 x301021_OnRecycle(sceneId,selfId,targetId)
     CallScriptFunction( x301021_g_ScriptId, "OnDestroyHouPaoDan", sceneId, selfId )
     return 0
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301021_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301021_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
