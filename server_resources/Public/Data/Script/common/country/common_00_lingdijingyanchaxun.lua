x302506_g_ScriptId 		= 302506
x302506_g_MissionKind 	= 	1                       --��������
x302506_g_MissionName	= "�����ҡ�ͼ�ھ����ѯ"

-- �淨����id
x302506_g_IsEnableId    = 1050
x302506_g_LimitLevel	= 40			--��ͼ���

-- ͼ�����ڵĵ�ͼ
x302506_g_LairdMap		= { 6, 9, 13, 18, 21, 24, 27, 31, 34 }
-- ͼ��NPC id
x302506_g_LairdNpcId	= { 400600, 400601, 400602, 400603, 400604, 400605, 400606, 400607, 400608 }
-- ÿ���ȼ���ͼ�ھ������ֵ
x302506_g_LairdExpMax	= { 10500, 11667, 12834, 14001 }


-- ʹ�øú�����ʾ
function x302506_CallbackEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById( x302506_g_IsEnableId) <= 0 then
        return
    end
    
    local index = -1
    local npcGuid = GetMonsterGUID(sceneId,targetId)
    for i, item in x302506_g_LairdNpcId do
    	if npcGuid == item then
    		index = i
    		break
    	end
    end
	if index == -1 then
		return
	end
    
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x302506_g_LairdMap[index])
    if nLairdCountry ~= country then
		return
	end
    
	AddQuestNumText(sceneId,x302506_g_ScriptId, x302506_g_MissionName, 3, -1)
end

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x302506_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x302506_ProcEventEntry( sceneId ,selfId, targetId, idScript, idExt )

	if GetGameOpenById( x302506_g_IsEnableId) <= 0 then
        return
    end
    
    local index = -1
    local npcGuid = GetMonsterGUID(sceneId,targetId)
    for i, item in x302506_g_LairdNpcId do
    	if npcGuid == item then
    		index = i
    		break
    	end
    end
	if index == -1 then
		return
	end
    
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x302506_g_LairdMap[index])
    if nLairdCountry ~= country then
		return
	end
	
	local nGuildID = GetSceneLairdGuildId(x302506_g_LairdMap[index])
	if nGuildID < 0 then
		--�����Ч
		return
	end
	
	local nLairdLevel = GetSceneLairdLevel(x302506_g_LairdMap[index])
	local nCurLairdExp = GetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP)
	
	BeginQuestEvent(sceneId)          
	AddQuestText(sceneId, "#Y"..x302506_g_MissionName.."#W")
	
	if nLairdLevel == 5 then
		AddQuestText(sceneId, "#Y".."��ǰ��صȼ��Ѵﵽ����".."#W")
	else
	local percent = nCurLairdExp*100/x302506_g_LairdExpMax[nLairdLevel]-0.05
	if percent < 0 then
		percent = 0
	end
	AddQuestText(sceneId, format("\n\t���ͼ�ڵľ�����Դ��#Y�����ҡ�ͼ�ڽ���#W���񡣵�ͼ�ڵľ��鵽��100%%ʱ��ͼ�ڽ������������ͼ�����������Ϊ#Gռ����صİ��#W������ؽ�������ؾ��飬ͬʱҲ������#Gȫ�����#W��������Ľ�����\n \n��ǰ���飺#R%.1f%%", percent))
	end
	
	EndQuestEvent()
	DispatchQuestInfo(sceneId ,selfId, targetId, x302506_g_ScriptId, -1, 1)
end

function x302506_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x302506_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x302506_ProcQuestAbandon( sceneId, selfId, MissionId )

end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x302506_OnContinue( sceneId, selfId, targetId )

end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x302506_CheckSubmit( sceneId, selfId )

end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x302506_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x302506_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x302506_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x302506_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
