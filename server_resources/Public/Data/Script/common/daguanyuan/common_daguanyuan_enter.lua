--���Ͻ��������˼䡤���Ľű�

x310368_g_ScriptId = 310368
x310368_g_ask ={"���������˼䡤����(85��)","ȷ��"}
x310368_g_answer ={"\t�����������˼䡤����ô�����������������ֺ���������淨����Ƥ��ٻŮ�Ļ�Ҳ�����С�\n\t�����˼䡤������ÿ�������������ʽ���ţ�ÿ�������յ�һ�ν��������˼䡤������Ҫ#R����10������������#W��\n\t�������ڽ�ȥ����ô��"}

x310368_g_Item = 12035005 -- �޵�������

function x310368_IsEnterFirst(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3])
	if today ~= lastDay then
		return 1
	end
	
	
	return 0
end

function x310368_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�

		local level =GetLevel(sceneId, selfId)
		if which == 0 then
				BeginQuestEvent(sceneId)
				AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[1],0,1)
		  	EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x310368_g_answer[1])
			AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[2],0,2)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
            if level>= 85 then
            	local subsillertype=1
            	if GetWeek() ~= 0 and GetWeek() ~= 6 then
            		BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�����˼䡤����ֻ�����������ղŻῪ������ʱ�������ɡ�")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
										
			    local curTime = GetMinOfDay()
				if curTime < 540 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�����˼䡤���Ļ�δ���ţ�������9��00�Ժ�������")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end			
				if curTime >= 1380 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�����˼䡤�����Ѿ��رգ��´ο���ʱ�������ɡ�")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,NPCId)
					return
				end
									
				local res =  GetSillerMode(sceneId, selfId) 
				print("ss",res)
				local ret = x310368_IsEnterFirst(sceneId ,selfId)
				
   				if ret == 1 then  --��һ��Ҫ��Ǯ  		
   					if GetBagSpace(sceneId, selfId) <= 0 then
							Msg2Player(sceneId, selfId, "�����������޷���������˼䡤������͸��Ʊ", 0, 2)
							Msg2Player(sceneId, selfId, "�����������޷���������˼䡤������͸��Ʊ", 0, 3)
							return
						end		
					if GetSillerMode(sceneId, selfId) == 1 then
						if CostMoney(sceneId, selfId, 0, 10000) == -1 then				--������0   ������1	
							if CostMoney(sceneId, selfId, 1, 10000) == -1 then
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, "�ܱ�Ǹ�������һ�ν��������˼䡤����Ҫ����10������������");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������һ�ν��������˼䡤����Ҫ����10������������",8,2)				
								return
							else
								subsillertype	=	0
							end
						else
							subsillertype	=	1
						end
					else
						if CostMoney(sceneId, selfId,1, 10000) == -1 then
							if CostMoney(sceneId, selfId, 0, 10000) == -1 then	
								BeginQuestEvent(sceneId)
								AddQuestText(sceneId, "�ܱ�Ǹ�������һ�ν��������˼䡤����Ҫ����10������������");
								EndQuestEvent(sceneId)
								DispatchQuestTips(sceneId,selfId)	
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������һ�ν��������˼䡤����Ҫ����10������������",8,2)				
								return
							else
								subsillertype	=	1
							end
						else
							subsillertype =	0
						end
					end
				end
				if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,0) == 0 then
					--print("CheckCountryBattleLiteSceneTrans")
					return
				end

				if IsHaveSpecificImpact( sceneId, selfId, 7718) == 1 then
					CancelSpecificImpact( sceneId, selfId, 7718)	
				end
				SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 7718, 0)
				
				NewWorld( sceneId, selfId, 40, 127 + random( -2,2 ), 140 + random( -2, 2), 310368)
				if ret == 1 then  
           		if subsillertype	==	1 then
           			Msg2Player(sceneId,selfId,"��������10�����������������˼䡤���ġ�",8,2)	
           		else
           			Msg2Player(sceneId,selfId,"��������10�����������������˼䡤���ġ�",8,2)		
	           		end
	           	CallScriptFunction(310362,"GiveItem",sceneId,selfId)	
           		end
           		local today = GetDayOfYear()
           		SetQuestData(sceneId, selfId, MD_DAGUANYUAN_DATE[1], MD_DAGUANYUAN_DATE[2], MD_DAGUANYUAN_DATE[3], today)
           		
           		
            else 
            	BeginQuestEvent(sceneId)
            	AddQuestText(sceneId,"\t�ܱ�Ǹ��ֻ�в�����85������Ҳ��ܽ��������˼䡤���ġ�")
            	EndQuestEvent()
            	DispatchQuestEventList(sceneId, selfId, NPCId)
            end
        end
	

	
	
end


--**********************************

--�о��¼�

--**********************************

function x310368_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local minlevel = GetTopListInfo_MinLevel(GetWorldID(sceneId, selfId))
		-- if minlevel >=65 then
			AddQuestNumText(sceneId, x310368_g_ScriptId, x310368_g_ask[1],3,1)
		--end
end








