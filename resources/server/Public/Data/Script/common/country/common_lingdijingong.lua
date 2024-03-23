--ͼ�ڽ���
x300959_g_ScriptId              			= 300959
x300959_g_MissionName          			="�����ҡ�ͼ�ڽ���"

x300959_g_MissionId						= {7760, 7761, 7762, 7763, 7764, 7765, 7766, 7767, 7768}
x300959_g_Laird							= {6, 9, 13, 18, 21, 24, 27, 31, 34}

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300959_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local state = 8
	for i, item in x300959_g_MissionId do
		local state = GetQuestStateNM(sceneId, selfId, targetId, item)
		if state == 7 then
			break
		end
	end
	if state == 8 then
		local ret = 1
		local country = GetCurCountry(sceneId, selfId)
		for i, item in x300959_g_Laird do
			local nLairdCountry = GetSceneLairdCountryId(item)
			if nLairdCountry == country then
				ret = 0
				break
			end
		end
		if ret == 1 then
			return
		end
	end
	AddQuestNumText(sceneId,x300959_g_ScriptId,x300959_g_MissionName,state,x300959_g_ScriptId)
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300959_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )
	
	BeginQuestEvent(sceneId)
	
		AddQuestText( sceneId, "\t���ͼ����ߵȼ�Ϊ#G5��#W���ﵽ#G40��#W����ң���Ϊ���ͼ�ڽ����Ӷ�����ͼ�ڵȼ���������ɻ��#G����#W��#G�츳ֵ#W��������ѡ��#G����ռ���ͼ��#W���н�������ע��ֻ����ÿ�յ�#R9��-23��#W�ſɽ��ܺ��������" )
		CallScriptFunction(300950,"CallbackEnumEvent", sceneId, selfId, targetId, 1)
		CallScriptFunction(300951,"CallbackEnumEvent", sceneId, selfId, targetId, 2)
		CallScriptFunction(300952,"CallbackEnumEvent", sceneId, selfId, targetId, 3)
		CallScriptFunction(300953,"CallbackEnumEvent", sceneId, selfId, targetId, 4)
		CallScriptFunction(300954,"CallbackEnumEvent", sceneId, selfId, targetId, 5)
		CallScriptFunction(300955,"CallbackEnumEvent", sceneId, selfId, targetId, 6)
		CallScriptFunction(300956,"CallbackEnumEvent", sceneId, selfId, targetId, 7)
		CallScriptFunction(300957,"CallbackEnumEvent", sceneId, selfId, targetId, 8)
		CallScriptFunction(300958,"CallbackEnumEvent", sceneId, selfId, targetId, 9)
    
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)	

    return 1

end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300959_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300959_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300959_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300959_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300959_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300959_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300959_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300959_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300959_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end