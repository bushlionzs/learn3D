                                                                                                                --������


--�ű��� 301030




--��̬������ʼ������

x301030_g_MissionId 	= 6603
x301030_g_ItemId 		= 13010083
x301030_g_ScriptId 		= 700004


--���ɺ�����ʼ************************************************************************

function 		x301030_OnCreate(sceneId,growPointType,x,y)

	--����
	local ItemBoxId = ItemBoxEnterScene(x,y,100,sceneId,0,x301030_g_ItemId)


end






--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301030_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x301030_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x301030_g_ItemId) == 0 then
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
function	 x301030_OnRecycle(sceneId,selfId,targetId)
     return CallScriptFunction( x301030_g_ScriptId, "OnGetHeShiBi", sceneId, selfId )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301030_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301030_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
