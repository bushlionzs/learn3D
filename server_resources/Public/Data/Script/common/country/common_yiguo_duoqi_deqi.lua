
x300779_g_ScriptId = 300779
x300779_g_MissionName = "夺取军旗"

function x300779_ProcEnumEvent( sceneId, selfId, targetId, index )
--敦煌接取
	local missionId1 = 7686
	local missionId2 = 7687
	local missionId3 = 7688
	local missionId4 = 7689	
--昆仑接取
	local missionId5 = 7690
	local missionId6 = 7691
	local missionId7 = 7692
	local missionId8 = 7693
--楼兰接取
	local missionId9 = 7596
	local missionId10 = 7597
	local missionId11 = 7598
	local missionId12 = 7599	
--天山接取
	local missionId13 = 7694
	local missionId14 = 7695
	local missionId15 = 7696
	local missionId16 = 7697

	local scene1 = 51
	local scene2 = 151
	local scene3 = 251
	local scene4 = 351

	local MissionId =-1	

	if sceneId == scene1 then
		if IsHaveQuestNM( sceneId, selfId, missionId1 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId5 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId9 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId13 ) == 0 then
			return
		else 
			AddQuestNumText(sceneId,x300779_g_ScriptId, x300779_g_MissionName, 5)
		end
	elseif sceneId == scene2 then
		if IsHaveQuestNM( sceneId, selfId, missionId2 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId6 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId10 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId14 ) == 0 then
			return
		else 
			AddQuestNumText(sceneId,x300779_g_ScriptId, x300779_g_MissionName, 5)
		end
	elseif sceneId == scene3 then
		if IsHaveQuestNM( sceneId, selfId, missionId3 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId7 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId11 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId15 ) == 0 then
			return
		else 
			AddQuestNumText(sceneId,x300779_g_ScriptId, x300779_g_MissionName, 5)
		end
	elseif sceneId == scene4 then
		if IsHaveQuestNM( sceneId, selfId, missionId4 )	==0 and IsHaveQuestNM( sceneId, selfId, missionId8 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId12 ) ==0 and IsHaveQuestNM( sceneId, selfId, missionId16 ) == 0 then
			return
		else 
			AddQuestNumText(sceneId,x300779_g_ScriptId, x300779_g_MissionName, 5)
		end
	end
end


function x300779_ProcEventEntry( sceneId , selfId , targetId , state , index )
--敦煌接取	
	local missionId1 = 7686
	local missionId2 = 7687
	local missionId3 = 7688
	local missionId4 = 7689	
--昆仑接取
	local missionId5 = 7690
	local missionId6 = 7691
	local missionId7 = 7692
	local missionId8 = 7693
--楼兰接取
	local missionId9 = 7596
	local missionId10 = 7597
	local missionId11 = 7598
	local missionId12 = 7599	
--天山接取
	local missionId13 = 7694
	local missionId14 = 7695
	local missionId15 = 7696
	local missionId16 = 7697

	local scene1 = 51
	local scene2 = 151
	local scene3 = 251
	local scene4 = 351

	local MissionId =-1	

	if sceneId == scene1 then
		
		if 		IsHaveQuestNM( sceneId, selfId, missionId1 ) == 1 then
				MissionId = missionId1
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId5 ) == 1 then
				MissionId = missionId5
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId9 ) == 1 then
				MissionId = missionId9
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId13 ) == 1 then
				MissionId = missionId13	    
		end
		
	elseif sceneId == scene2 then
		
		if 		IsHaveQuestNM( sceneId, selfId, missionId2 ) == 1 then
				MissionId = missionId2
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId6 ) == 1 then
				MissionId = missionId6
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId10 ) == 1 then
				MissionId = missionId10
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId14 ) == 1 then
				MissionId = missionId14	    
		end
		
	elseif sceneId == scene3 then
		
		if 		IsHaveQuestNM( sceneId, selfId, missionId3 ) == 1 then
				MissionId = missionId3
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId7 ) == 1 then
				MissionId = missionId7
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId11 ) == 1 then
				MissionId = missionId11
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId15 ) == 1 then
				MissionId = missionId15    
		end
		
	elseif sceneId == scene4 then
		
		if 		IsHaveQuestNM( sceneId, selfId, missionId4 ) == 1 then
				MissionId = missionId4
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId8 ) == 1 then
				MissionId = missionId8
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId12 ) == 1 then
				MissionId = missionId12
		elseif 	IsHaveQuestNM( sceneId, selfId, missionId16 ) == 1 then
				MissionId = missionId16    
		end
	end

	if MissionId == -1 then
	
		return
	end


	if IsHaveSpecificImpact( sceneId, selfId, 7702 ) == 0 then
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 7702, 0);

			SetQuestParam(sceneId, selfId, MissionId, 0, 1)
			SetQuestParam(sceneId, selfId, MissionId, 7, 1)

	end
		

end
