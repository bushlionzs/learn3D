 --��̽
x270354_g_ScriptId	= 270354
x270354_g_MissionId	=	{1390 , 1391, 1392, 1393}
x270354_g_MissionScriptId	=	{270350 , 270351, 270352, 270353}

--**********************************
--�¼��������
--**********************************
function x270354_ProcEventEntry( sceneId, selfId,targetId )            
	BeginQuestEvent(sceneId)                                             
	AddQuestText(sceneId,"\t�������������������ð���������ڲ��ü������ǰ������յĵط������ˡ�")     
	EndQuestEvent(sceneId)
	local misIndex = -1                                               
	if IsHaveQuest(sceneId,selfId, 1390) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1390) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[1], "�㲢���������",0, 1)
		end                  
	end                                               
	if IsHaveQuest(sceneId,selfId, 1391) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1391) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[2], "�㲢���������",0, 1)
		end                  
	end                                             
	if IsHaveQuest(sceneId,selfId, 1392) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1392) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[3], "�㲢���������",0, 1)
		end                  
	end                                              
	if IsHaveQuest(sceneId,selfId, 1393) > 0 then
		misIndex = GetQuestIndexByID(sceneId,selfId,1393) 
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x270354_g_MissionId[4], "�㲢���������",0, 1)
		end                  
	end	                                                                  
	DispatchQuestEventList(sceneId,selfId,targetId)                      
	ShowNpcQuestEventList(sceneId,selfId,targetId)                       
end                                                                    

x270354_g_MonsterTable              = {
                                        { minLevel = 20, maxLevel = 29, monList = { { id = 3840, objid = 400040, mapid = 58,  name = "��ľ����",   Place = "������" , posName = "@npc_59670"  }, { id = 3841, objid = 400041, mapid = 58,  name = "��ľ����", 	Place = "������" , posName = "@npc_59670"  }, { id = 3842, objid = 400042, mapid = 58,  name = "��������", 	 Place = "���Ϸ�" , posName = "@npc_59670"  }, { id = 3843, objid = 400043, mapid = 58,  name = "�������",    		Place = "���Ϸ�" , posName = "@npc_59670"  }, { id = 3844, objid = 400044,mapid = 58, name = "θ������", Place = "�Ϸ�" ,posName = "@npc_59670"  }, { id = 3845, objid = 400045,mapid = 58, name = "Ů������", Place = "�Ϸ�" ,posName = "@npc_59670" } }},  
                                        { minLevel = 30, maxLevel = 34, monList = { { id = 3846, objid = 400046, mapid = 104, name = "�������",   Place = "������" , posName = "@npc_59671"  }, { id = 3847, objid = 400047, mapid = 104, name = "β����", 	Place = "������" , posName = "@npc_59671"  }, { id = 3849, objid = 400049, mapid = 104, name = "��������", 	 Place = "���Ϸ�" ,	posName = "@npc_59671"  }, { id = 3850, objid = 400050, mapid = 104, name = "���", 			 		Place = "���Ϸ�" , posName = "@npc_59671"  } }},
                                        { minLevel = 35, maxLevel = 39, monList = { { id = 3849, objid = 400049, mapid = 104, name = "��������",   Place = "���Ϸ�" , posName = "@npc_59671"  }, { id = 3850, objid = 400050, mapid = 104, name = "���", 			Place = "���Ϸ�" , posName = "@npc_59671"  }, { id = 3852, objid = 400052, mapid = 105, name = "��צ����", 	 Place = "���Ϸ�" , posName = "@npc_59672"  }, { id = 3853, objid = 400053, mapid = 105, name = "�������", 	 		Place = "�в�" ,	 posName = "@npc_59672"  } }}, 
                                        { minLevel = 40, maxLevel = 44, monList = { { id = 3852, objid = 400052, mapid = 105, name = "��צ����",   Place = "���Ϸ�" , posName = "@npc_59672"  }, { id = 3853, objid = 400053, mapid = 105, name = "�������", 	Place = "�в�" ,	 posName = "@npc_59672"  }, { id = 3854, objid = 400054, mapid = 105, name = "̽����", 	 Place = "������" ,	posName = "@npc_59672"  }, { id = 3856, objid = 400056, mapid = 105, name = "��Ѩ��ħ",    		Place = "����" ,	 posName = "@npc_59672"  } }}, 
                                        { minLevel = 45, maxLevel = 49, monList = { { id = 3854, objid = 400054, mapid = 105, name = "̽����",   Place = "������" , posName = "@npc_59672"  }, { id = 3856, objid = 400056, mapid = 105, name = "��Ѩ��ħ", 	Place = "����" ,	 posName = "@npc_59672"  }, { id = 3858, objid = 400058, mapid = 106, name = "��������",	 Place = "����" ,   posName = "@npc_59673"  }, { id = 3859, objid = 400059, mapid = 106, name = "���˲�³˹",  		Place = "������" , posName = "@npc_59673"  } }}, 
                                        { minLevel = 50, maxLevel = 54, monList = { { id = 3858, objid = 400058, mapid = 106, name = "��������",   Place = "����" ,   posName = "@npc_59673"  }, { id = 3859, objid = 400059, mapid = 106, name = "���˲�³˹", Place = "������" , posName = "@npc_59673"  }, { id = 3862, objid = 400062, mapid = 106, name = "Ѫ����",		 Place = "�в�" ,		posName = "@npc_59673"  }, { id = 3863, objid = 400063, mapid = 106, name = "������ʿ",    		Place = "���Ϸ�" , posName = "@npc_59673"  } }}, 
                                        { minLevel = 55, maxLevel = 59, monList = { { id = 3862, objid = 400062, mapid = 106, name = "Ѫ����",     Place = "�в�" ,   posName = "@npc_59673"  }, { id = 3863, objid = 400063, mapid = 106, name = "������ʿ", 	Place = "���Ϸ�" , posName = "@npc_59673"  }, { id = 3864, objid = 400064, mapid = 107, name = "�綾����",   Place = "�в�" ,   posName = "@npc_59674"  }, { id = 3866, objid = 400066, mapid = 107, name = "��ǯ��Ы",    		Place = "������" , posName = "@npc_59674"  } }}, 
                                        { minLevel = 60, maxLevel = 64, monList = { { id = 3864, objid = 400064, mapid = 107, name = "�綾����",   Place = "�в�" ,   posName = "@npc_59674"  }, { id = 3866, objid = 400066, mapid = 107, name = "��ǯ��Ы", 	Place = "������" , posName = "@npc_59674"  }, { id = 3868, objid = 400068, mapid = 107, name = "ף��ׯ��Ժ", Place = "�в�" ,		posName = "@npc_59674"  }, { id = 3869, objid = 400069, mapid = 107, name = "ף��ׯ����",  		Place = "������" , posName = "@npc_59674"  } }}, 
 										{ minLevel = 65, maxLevel = 69, monList = { { id = 3868, objid = 400068, mapid = 107, name = "ף��ׯ��Ժ", Place = "�в�" ,		posName = "@npc_59674"	}, { id = 3869, objid = 400069, mapid = 107, name = "ף��ׯ����", Place = "������" , posName = "@npc_59674"  }, { id = 3870, objid = 400070, mapid = 108, name = "��֮��", 		 Place = "�в�" ,		posName = "@npc_59701"  }, { id = 3871, objid = 400071, mapid = 108, name = "��֮��", 		 		Place = "������" , posName = "@npc_59701"  } }}, 
                                        { minLevel = 70, maxLevel = 74, monList = { { id = 3870, objid = 400070, mapid = 108, name = "��֮��",     Place = "�в�" ,		posName = "@npc_59701"  }, { id = 3871, objid = 400071, mapid = 108, name = "��֮��", 		Place = "������" , posName = "@npc_59701"  }, { id = 3872, objid = 400072, mapid = 108, name = "��֮��", 		 Place = "����" ,		posName = "@npc_59701"  }, { id = 3873, objid = 400073, mapid = 108, name = "ͻ������",    		Place = "������" , posName = "@npc_59701"  } }}, 
                                        { minLevel = 75, maxLevel = 79, monList = { { id = 3872, objid = 400072, mapid = 108, name = "��֮��",     Place = "����" ,		posName = "@npc_59701"  }, { id = 3873, objid = 400073, mapid = 108, name = "ͻ������", 	Place = "������" , posName = "@npc_59701"  }, { id = 3874, objid = 400074, mapid = 109, name = "��֮��", 		 Place = "�в�" ,   posName = "@npc_59702"  }, { id = 3875, objid = 400075, mapid = 109, name = "ͻ�ʽ���", 	 		Place = "������" , posName = "@npc_59702"  } }}, 
                                        { minLevel = 80, maxLevel = 84, monList = { { id = 3874, objid = 400074, mapid = 109, name = "��֮��",     Place = "�в�" ,   posName = "@npc_59702"  }, { id = 3875, objid = 400075, mapid = 109, name = "ͻ�ʽ���", 	Place = "������" , posName = "@npc_59702"  }, { id = 3876, objid = 400076, mapid = 109, name = "���ׯׯ��", Place = "����" ,		posName = "@npc_59702"  }, { id = 3877, objid = 400077, mapid = 109, name = "ף��ׯׯ��",  		Place = "����" ,	 posName = "@npc_59702"  } }}, 
                                        { minLevel = 85, maxLevel = 89, monList = { { id = 3876, objid = 400076, mapid = 109, name = "���ׯׯ��", Place = "����" ,		posName = "@npc_59702"  }, { id = 3877, objid = 400077, mapid = 109, name = "ף��ׯׯ��", Place = "����" ,	 posName = "@npc_59702"  }, { id = 3878, objid = 400078, mapid = 110, name = "���ùٱ�",   Place = "�в�" ,		posName = "@npc_59703"  }, { id = 3879, objid = 400079, mapid = 110, name = "ͻ������",    		Place = "����" ,	 posName = "@npc_59703"  } }}, 
                                        { minLevel = 90, maxLevel = 94, monList = { { id = 3878, objid = 400078, mapid = 110, name = "���ùٱ�",   Place = "�в�" ,		posName = "@npc_59703"  }, { id = 3879, objid = 400079, mapid = 110, name = "ͻ������", 	Place = "����" ,	 posName = "@npc_59703"  }, { id = 3880, objid = 400080, mapid = 110, name = "�ҿ�з", 		 Place = "������" ,	posName = "@npc_59703"  }, { id = 3881, objid = 400081, mapid = 110, name = "�����Ѧ��",  		Place = "������" , posName = "@npc_59703"  } }}, 
                                        { minLevel = 95, maxLevel = 99, monList = { { id = 3880, objid = 400080, mapid = 110, name = "�ҿ�з",     Place = "������" ,	posName = "@npc_59703"  }, { id = 3881, objid = 400081, mapid = 110, name = "�����Ѧ��", Place = "������" , posName = "@npc_59703"  },	{ id = 3882, objid = 400082, mapid = 111, name = "������Ӿ�", Place = "���Ϸ�" , posName = "@npc_59704"},   { id = 3883, objid = 400083, mapid = 111, name = "�����ʦ",    		Place = "����" ,   posName = "@npc_59704"  } }}, 
                                        { minLevel = 100,maxLevel =160, monList = { { id = 3882, objid = 400082, mapid = 111, name = "������Ӿ�", Place = "���Ϸ�" , posName = "@npc_59704"  }, { id = 3883, objid = 400083, mapid = 111, name = "�����ʦ", 	Place = "����" ,   posName = "@npc_59704"  }, { id = 3884, objid = 400084, mapid = 111, name = "���Ӫ����", Place = "����" ,		posName = "@npc_59704"  }, { id = 3885, objid = 400085, mapid = 111, name = "�������Ӫ���", Place = "����" ,   posName = "@npc_59704"  } }}, 
}
function x270354_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
	local MissionId = 0
	local Index = 0
	local guid = GetMonsterGUID(sceneId, selfId)
	local x,z = GetWorldPos(sceneId,selfId)
	local Num =  GetNearPlayerCount(sceneId, killerId,x,z,30)  
	for i = 0, Num-1 do
		local humanObjId = GetNearPlayerMember(sceneId, killerId,i);

		if humanObjId >= 0 then
			if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
				if IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[1]) == 1 then
					MissionId = x270354_g_MissionId[1]
					Index = 1
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[2]) == 1 then
					MissionId = x270354_g_MissionId[2]
					Index = 2
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[3]) == 1 then
					MissionId = x270354_g_MissionId[3]
					Index = 3
				elseif IsHaveQuestNM(sceneId, humanObjId, x270354_g_MissionId[4]) == 1 then
					MissionId = x270354_g_MissionId[4]
					Index = 4
				end
				if MissionId ~= 0 then
					
	            local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
	            local monidx = GetQuestParam( sceneId, humanObjId, misIndex, 1)
	            local index = GetQuestParam( sceneId, humanObjId, misIndex, 2)
		            if monidx == nil or monidx == 0 or index == nil or index == 0 then
		            	return
		            end
	            local name = x270354_g_MonsterTable[index].monList[monidx].name
	            if guid == x270354_g_MonsterTable[ index].monList[ monidx].objid then
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 6, 1)
				        Msg2Player( sceneId, humanObjId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 3)
				        Msg2Player( sceneId, humanObjId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 2)
				        
				        CallScriptFunction( x270354_g_MissionScriptId[Index], "ProcQuestLogRefresh", sceneId, humanObjId, MissionId)
			    		end
			    end
	        	
			end
		end
	end
end