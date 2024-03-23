
--MisDescBegin
--�ű���
x310401_g_ScriptId = 310401


--�����ı�����
x310401_g_MissionName="��̲��孵�����"

x310401_g_BuffId = 7061

x310401_g_TransportTable        = {
                                    { x = 150.44, z = 180 }, 
                                    { x = 150.44, z = 180 }, 
                                    { x = 150.44, z = 180 }, 
                                    { x = 155.44, z = 179 }, 
                                    { x = 154.44, z = 182 }, 
                                    { x = 147.44, z = 180 }, 
                                    { x = 147.44, z = 180 }, 
                                    { x = 158.44, z = 185 }, 
                                    { x = 164.44, z = 182 }, 
}

function x310401_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    AddQuestNumText(sceneId,x310401_g_ScriptId,"�뿪��孵�",14,-1)
     
end


function x310401_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )
	
	  BeginQuestEvent(sceneId)
	  local Readme_1 = "#Y���߾����͡�#r"
	  local Readme_2 = "#W\t��Ҫ�뿪��������������޷��ٴν����ˣ������˷�����ǿ�������֮������"
	  local Readme = Readme_1..Readme_2
		AddQuestText(sceneId,Readme)
		EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId,selfId,targetId,x310401_g_ScriptId,-1)
	return 

end

--********************
--����������
--**********************************
function x310401_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x310401_ProcAccept( sceneId, selfId )

	--LuaFnCancelSpecificImpact(sceneId, selfId, x310401_g_BuffId)
	
	--local countryId = GetCurCountry(sceneId, selfId)

	--local NewSceneId = x310401_g_SceneId[countryId+1]
    local rand = random( 1, getn( x310401_g_TransportTable) )
	local PosX = x310401_g_TransportTable[ rand].x
	local PosZ = x310401_g_TransportTable[ rand].z

	GamePlayScriptLog(sceneId, selfId, 532)
	
	NewWorld(sceneId, selfId, 15, PosX + random( 0, 3), PosZ + random( 0, 3), 310401 )

end

--**********************************
--����
--**********************************
function x310401_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x310401_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310401_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x310401_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

