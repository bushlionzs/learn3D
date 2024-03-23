
--MisDescBegin
--脚本号
x310036_g_ScriptId = 310036


--任务文本描述
x310036_g_MissionName="圣山地宫传传出"
--x310036_g_CountryID = 3
--MisDescEnd

x310036_g_SceneId = { 58, 158, 258, 358 }

	--MATTRIBUTE_UNKNOW			=-1,//非法数值
	--MATTRIBUTE_WUSHI			=0,	//武士
	--MATTRIBUTE_JIANXIA			=1,	//剑侠
	--MATTRIBUTE_QISHE			=2,	//骑射手
	--MATTRIBUTE_HUOQIANG			=3,	//火枪手
	--MATTRIBUTE_XIANZHI			=4,	//先知
	--MATTRIBUTE_SAMAN			=5,	//萨满

x310036_g_BuffId = 7040

function x310036_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    AddQuestNumText(sceneId,x310036_g_ScriptId,"离开圣山地宫",14,-1)
     
end


function x310036_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )
	
	  BeginQuestEvent(sceneId)
	  local Readme_1 = "#Y【地宫传送】#r"
	  local Readme_2 = "#W\t你要离开这里吗？那你今天无法再次进来了，真是浪费了这强大的五耀之力啊！"
	  local Readme = Readme_1..Readme_2
		AddQuestText(sceneId,Readme)
		EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId,selfId,targetId,x310036_g_ScriptId,-1)
	return 

end

--********************
--检测接受条件
--**********************************
function x310036_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
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
--放弃
--**********************************
function x310036_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x310036_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x310036_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x310036_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

