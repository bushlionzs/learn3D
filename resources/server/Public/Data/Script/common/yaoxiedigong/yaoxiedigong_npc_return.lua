
--MisDescBegin
--�ű���
x310036_g_ScriptId = 310036


--�����ı�����
x310036_g_MissionName="ʥɽ�ع�������"
--x310036_g_CountryID = 3
--MisDescEnd

x310036_g_SceneId = { 58, 158, 258, 358 }

	--MATTRIBUTE_UNKNOW			=-1,//�Ƿ���ֵ
	--MATTRIBUTE_WUSHI			=0,	//��ʿ
	--MATTRIBUTE_JIANXIA			=1,	//����
	--MATTRIBUTE_QISHE			=2,	//������
	--MATTRIBUTE_HUOQIANG			=3,	//��ǹ��
	--MATTRIBUTE_XIANZHI			=4,	//��֪
	--MATTRIBUTE_SAMAN			=5,	//����

x310036_g_BuffId = 7040

function x310036_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    AddQuestNumText(sceneId,x310036_g_ScriptId,"�뿪ʥɽ�ع�",14,-1)
     
end


function x310036_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )
	
	  BeginQuestEvent(sceneId)
	  local Readme_1 = "#Y���ع����͡�#r"
	  local Readme_2 = "#W\t��Ҫ�뿪��������������޷��ٴν����ˣ������˷�����ǿ�����ҫ֮������"
	  local Readme = Readme_1..Readme_2
		AddQuestText(sceneId,Readme)
		EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId,selfId,targetId,x310036_g_ScriptId,-1)
	return 

end

--********************
--����������
--**********************************
function x310036_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x310036_ProcAccept( sceneId, selfId )

	--CancelSpecificImpact(sceneId, selfId, x310036_g_BuffId)
	
	local countryId = GetCurCountry(sceneId, selfId)

	local NewSceneId = x310036_g_SceneId[countryId+1]
    --local PosX, PosZ;
--if  sceneId == YX_LOULAN_SCENE_ID1 or sceneId == YX_LAIYIN_SCENE_ID1 or sceneId == YX_KUNLUN_SCENE_ID1 or sceneId == YX_DUNHUANG_SCENE_ID1 then
--	PosX =128
--	PosZ = 70
--elseif sceneId == YX_LOULAN_SCENE_ID2 or sceneId ==YX_LAIYIN_SCENE_ID2 or sceneId ==YX_KUNLUN_SCENE_ID2 or sceneId ==YX_DUNHUANG_SCENE_ID2 then
--	PosX =129
--	PosZ = 56
--elseif sceneId ==YX_LOULAN_SCENE_ID3 or sceneId ==YX_LAIYIN_SCENE_ID3 or sceneId ==YX_KUNLUN_SCENE_ID3 or sceneId ==YX_DUNHUANG_SCENE_ID3 then
--	PosX =126
--	PosZ = 45
--elseif sceneId ==YX_LOULAN_SCENE_ID4 or sceneId ==YX_LAIYIN_SCENE_ID4 or sceneId ==YX_KUNLUN_SCENE_ID4 or sceneId ==YX_DUNHUANG_SCENE_ID4 then
--	PosX =111
--	PosZ = 53
--elseif sceneId ==YX_LOULAN_SCENE_ID5 or sceneId ==YX_LAIYIN_SCENE_ID5 or sceneId ==YX_KUNLUN_SCENE_ID5 or sceneId ==YX_DUNHUANG_SCENE_ID5 then
--	PosX =128
--	PosZ = 70
--elseif sceneId ==YX_LOULAN_SCENE_ID6 or sceneId ==YX_LAIYIN_SCENE_ID6 or sceneId ==YX_KUNLUN_SCENE_ID6 or sceneId ==YX_DUNHUANG_SCENE_ID6 then
--	PosX =128
--	PosZ = 70
--else
--	return
--end
	local	PosX={ 128, 128, 128, 128} 
  local PosZ={ 66, 66, 190, 190}

	GamePlayScriptLog(sceneId, selfId, 532)
	
	local Posx = PosX[countryId+1]
	local Posz = PosZ[countryId+1]
	NewWorld(sceneId, selfId, NewSceneId, Posx + random( 0, 3), Posz + random( 0, 3), 310036 )

end

--**********************************
--����
--**********************************
function x310036_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x310036_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310036_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x310036_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

