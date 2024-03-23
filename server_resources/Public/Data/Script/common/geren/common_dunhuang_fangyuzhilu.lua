--MisDescBegin


x300983_g_ScriptId = 300983

x300983_g_MissionId_List = {
							7800,	--¥���Ķ�Ӧ�����
							7801,	--��ɽ�Ķ�Ӧ�����
							7802,	--���صĶ�Ӧ�����
							7803,	--�ػ͵Ķ�Ӧ�����
							}
x300983_g_MissionId = 7803


x300983_g_Title = "����֮·"

x300983_g_Profession_Enum = {	--12��ְҵ
								0,	--��ʿ  
								1,	--����  
								2, 	--����  
								3, 	--��ǹ  
								4, 	--��֪  
								5,	--����  
								6, 	--ʮ�־�
								7, 	--ʥ��ʹ
								8, 	--�̿�  
								9, 	--������
								10,	--����ʿ
								11,	--ɮ��  
								0,	--��ʿ  
								2, 	--����  
								3, 	--��ǹ  
								4, 	--��֪  
								5,	--���� 
								6, 	--ʮ�־�
								8, 	--�̿�  
								10,	--����ʿ
								2, 	--����  
								3, 	--��ǹ  
								4, 	--��֪   
								8, 	--�̿�  
							}
							
x300983_g_Profession_Desc = {	--12��ְҵ
								"��ʿ",
								"����",  
								"����",  
								"��ǹ",  
								"��֪",  
								"����",  
								"ʮ�־�",
								"ʥ��ʹ",
								"�̿�",  
								"������",
								"����ʿ",
								"ɮ��",
								"��ʿ", 
								"����",  
								"��ǹ",  
								"��֪",  
								"����",  
								"ʮ�־�",
								"�̿�",  
								"����ʿ",
								"����",  
								"��ǹ",  
								"��֪",   
								"�̿�",  
							}							

--x300983_g_Profession  = 0   --ȫ�ֱ�����ÿ�ε������npc��ʱ������һ��
--x300983_g_Profession_Desc = "" --ȫ�ֱ�����ÿ�ε������npc��ʱ�����һ��
--x300983_g_Kill_Count  = 0   --ȫ�ֱ�������¼����ĳ��ְҵ����ҵĸ���  
--x300983_g_Completed   = 0   --ȫ�ֱ���������Ƿ��������
x300983_g_Quest_Max_Count = 1	--ȫ�ֱ�����������ֻ�޽�1��,ʹ��ר��֮�顤�������Զ��1��


x300983_g_MissionName = "�����ˡ�����֮·"
x300983_g_MissionInfo				= 	"\t�����빥���Ĺ�ϵ��΢���Ҫ׷�����ߵķ�����û��һ���Ĺ���Ҳ��û������ġ�������Ҫ����һ�����顪������ĳһ��ְҵ��6���й����֡�ͨ�����������֮���һ����ӽ������ߵķ�����#G�����ܵ���Ҳ������Լ�20������Ч����" 
x300983_g_Mission_Kill_Cnt = 6				   

x300983_g_CommitNPC     = "@npc_141103"

--print(".........................................")					   
--��Ҫ�ĵȼ�
function x300983_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	if GetCurCountry(sceneId,selfId) ~=3 or GetLevel(sceneId, selfId) < 80 then
		return -1
	end	

	--PrintStr("x300983_ProcEnumEvent")
	local state = GetQuestStateNM(sceneId,selfId,NPCId,x300983_g_MissionId)
	AddQuestTextNM( sceneId, selfId, NPCId, x300983_g_MissionId, state, -1 )

end


--D:\workspace\khan2_run\Public\Data\Script\common\cangbaotu\common_gujitanyi.lua
--���û�����񣻽�����
--�����������ʾ�Ƿ���������������
function x300983_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
	if GetGameOpenById(1060)<=0 then
		Msg2Player(sceneId, selfId, "�˻�ѹرգ������ĵȴ�������", 0, 3)
		return
	end
	
	--PrintStr("x300983_ProcEventEntry")

	--�ж��Ƿ���ר��֮�顤��������,yes ����Խӵڶ���;����ֻ�ܽ�һ��
	local nCntItem_tuozhanzhishu = GetItemCountInBag( sceneId, selfId, 11010125)
	--PrintNum(nCntItem_tuozhanzhishu)
	
	
	local nCnt = x300983_GetDayCount(sceneId, selfId) + 1
	print("-----------------nCntItem_tuozhanzhishu",nCntItem_tuozhanzhishu,"nCnt",nCnt)
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- ���û��������� 
				
				if nCnt == 1 then --��һ�ν�����
							x300983_DistachMission_Info(sceneId,selfId,NPCId,1)
				elseif  nCnt == 2 then
							if nCntItem_tuozhanzhishu > 0  then 
															--�Ѿ�����һ������,��ר��֮�顤����
															--����һ��ר��֮�顤��������
															--DelItemByIDInBag( sceneId, selfId, 11010125, 1)
															--ʹ��ר��֮�顤�������߿��Զ��һ������,��ProcQuestAccept�������
															x300983_DistachMission_Info(sceneId,selfId,NPCId,2)
															--Msg2Player( sceneId, selfId, "���ܷ�����������ר��֮�顤��������һ��", 8, 3)
							else
															BeginQuestEvent(sceneId)
															AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
															AddQuestText(sceneId,"\t�������Ѿ����һ�α������ˣ������#Gר��֮�顤����#W��������ȡһ�α�����\n\t#Gר��֮�顤����#W�������������#Gר���츳����̵�#W����")															
															EndQuestEvent(sceneId)
															DispatchQuestEventList(sceneId, selfId, NPCId)
															return -1  
							end
				else --����2����					
							BeginQuestEvent(sceneId)
							AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
							AddQuestText(sceneId,"\t�����Ѿ��ﵽ����������ޣ������������\n")
							EndQuestEvent(sceneId)
							DispatchQuestEventList(sceneId, selfId, NPCId)
							return -1  
				end
					
					
					
    else--����ǲ��ǿ����ύ    
				local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
		        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		        
				if isFinish > 0 then -- �������������
							    --x300340_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- ��ʾ�����Ϣ
							  	BeginQuestEvent( sceneId)
								AddQuestText( sceneId, "#Y"..x300983_g_MissionName.."#W\n\t���������������ǵ�Լ�����һ������ķ�������һ��¥��" )
								AddQuestText( sceneId, "\n#Y�������� ")
								AddQuestText( sceneId, "ר��ѵ��������13�� ")	
								EndQuestEvent( sceneId)
								DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId)
								--SetQuestByIndex( sceneId, selfId, misIndex, 7,0) --��������־��0
								
				else
								--PrintNum(isFinish)			        
								--x300340_MissionContinue( sceneId, selfId, targetId, x300983_g_MissionId) -- ��ʾ����δ�����Ϣ
								
								local nRemain = 0
								local today = GetDayOfYear()
								local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
								if lastday ~= today then --����ǵ�һ��ɱ��
									nRemain = x300983_g_Mission_Kill_Cnt
								else										
									local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
									nRemain = x300983_g_Mission_Kill_Cnt - nKillCnt
								end
								--local nIdx     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_OTHER)
								local nIdx		 = GetQuestParam( sceneId, selfId, misIndex , 3)          --��ȡ������±�
								print("------------------------------->",nIdx)
								if nIdx <=0 or nIdx > getn(x300983_g_Profession_Desc) then
									return -1
								end
								local strPro   = x300983_g_Profession_Desc[nIdx]								
								BeginQuestEvent( sceneId)
								AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
							    AddQuestText( sceneId, "\t����������𣿼������Ͱɣ�ֻ�и������лر���\n\t�㻹��Ҫ����"..nRemain.."��#R"..strPro.."#Wְҵ�ĵй���һ���#R������ż")
								EndQuestEvent()
							    DispatchQuestEventList( sceneId, selfId, NPCId)
							    --PrintNum(GetQuestParam( sceneId, selfId, misIndex, 0))
				end
    end
end

function x300983_DistachMission_Info(sceneId,selfId,NPCId,nFlag)
							--local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId ) 
							local nIndex  = random(1,24)           
							--SetQuestParam( sceneId, selfId, misIndex , 3 ,nIndex)
							SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_OTHER,nIndex)	--����ȫ�ֱ���            
							--PrintStr("nIndex")
							--PrintNum(nIndex)                        
							---local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId ) 
							---SetQuestByIndex(sceneId, selfId, misIndex,1,nIndex)
							---PrintNum(GetQuestParam(sceneId, selfId, misIndex,1))
							---assert(GetQuestParam(sceneId, selfId, misIndex,1) == nIndex)
							
								
							
							if nFlag == 2 then		
												BeginQuestEvent( sceneId)
												AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
												AddQuestText( sceneId, x300983_g_MissionInfo)
												--����Ŀ��
												AddQuestText( sceneId, "#Y����Ŀ�꣺")
												AddQuestText( sceneId, format( "����ĳ��ְҵ�ĵй���һ���������ż#R6��#W��") )
												AddQuestText( sceneId, "\n#GС��ʾ��\n\t�ӱ���������Ҫ����һ��ר��֮�顤��������ȷ��Ҫ���ܴ�������?")
												AddQuestText( sceneId, "\n#Y�������� ")
												AddQuestText( sceneId, "ר��ѵ��������13�� ")	
												EndQuestEvent()
					
												DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId);
							else
												BeginQuestEvent( sceneId)
												AddQuestText( sceneId, "#Y"..x300983_g_MissionName)
												AddQuestText( sceneId, x300983_g_MissionInfo)
												--����Ŀ��
												AddQuestText( sceneId, "#Y����Ŀ�꣺")
												AddQuestText( sceneId, format( "����ĳ��ְҵ�ĵй���һ���������ż#R6��#W��") )
												AddQuestText( sceneId, "\n#Y�������� ")
												AddQuestText( sceneId, "ר��ѵ��������13�� ")	
													
												EndQuestEvent()
					
												DispatchQuestInfoNM( sceneId, selfId, NPCId, x300983_g_ScriptId, x300983_g_MissionId);
							end
											

end


function x300983_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	--PrintStr("x300983_ProcQuestAccept")
		if GetInherenceLevel(sceneId, selfId) < 50  then
			Msg2Player(sceneId, selfId, "�츳�ȼ�����50����������ȡ������", 0, 2)
			Msg2Player(sceneId, selfId, "�츳�ȼ�����50����������ȡ������", 0, 3)
			return -1
		end
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId) == 0 then   -- û���������
				        -- ��鵱���Ƿ��Ѿ������������,����ӹ�һ�ζ�����ר��֮�顤�������ߵĻ��������ٽ�һ������

				        ---------------------------------if x300983_GetDayCount(sceneId, selfId) ~= 0 then
						---------------------------------					local str = "������Ѿ���ɹ������������������"
						---------------------------------					BeginQuestEvent( sceneId)
						---------------------------------					AddQuestText( sceneId, str )
						---------------------------------					EndQuestEvent()
						---------------------------------					DispatchQuestTips( sceneId, selfId)
						---------------------------------					Msg2Player(sceneId, selfId, str, 8, 2)
						---------------------------------					return
				        ---------------------------------end
						--������Ǳ����ĳ�Ա�����޷�������
						if GetCurCountry(sceneId, selfId) ~= 3 then
							--print("00000000000000000000000000")
							return -1
						end
						
						local nCnt = x300983_GetDayCount(sceneId, selfId)
						if nCnt == 1 then --�Ѿ�����һ������
								local nCntItem_tuozhanzhishu = GetItemCountInBag( sceneId, selfId, 11010125)
								if nCntItem_tuozhanzhishu > 0 then
										DelItemByIDInBag( sceneId, selfId, 11010125, 1)
										Msg2Player( sceneId, selfId, "����ר��֮�顤��������һ��", 8, 2)
										Msg2Player( sceneId, selfId, "����ר��֮�顤��������һ��", 8, 3)
								else
										Msg2Player( sceneId, selfId, "û������ר��֮�顤�������ߣ��޷��ӵڶ�������", 8, 2)
										Msg2Player( sceneId, selfId, "û������ר��֮�顤�������ߣ��޷��ӵڶ�������", 8, 3)
										return -1
								end
						end
							
						
						local ret	= AddQuest( sceneId, selfId, x300983_g_MissionId, x300983_g_ScriptId, 1, 0, 0) --ע������Ĳ���
						if ret == 0 then
											local str = "�����������������ʧ�ܣ�"
											BeginQuestEvent( sceneId)
											AddQuestText( sceneId, str )
											EndQuestEvent( sceneId)
											DispatchQuestTips( sceneId, selfId)
											Msg2Player(sceneId, selfId, str, 8, 2)
											return 0
						else
											local nIndex = GetPlayerRuntimeData(sceneId, selfId,RD_GUILDCONTEND_KILL_OTHER)
											local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
											--local nIndex =   GetQuestParam(sceneId, selfId, misIndex, 3)
											--PrintNum(nIndex)
											SetQuestByIndex(sceneId, selfId,misIndex,3,nIndex)
											-- ���½�����ʱ��
											x300983_SetDayCount(sceneId, selfId)   								
											BeginQuestEvent( sceneId)
											AddQuestText( sceneId, "�������ˡ����ˡ�����֮·������");
											EndQuestEvent( sceneId);
											DispatchQuestTips( sceneId, selfId);
											Msg2Player( sceneId, selfId, "�������ˡ����ˡ�����֮·������", 8, 2)
											Msg2Player( sceneId, selfId, "�������ˡ����ˡ�����֮·������", 8, 3)
								
			
					    end
    else
						DelQuest(sceneId, selfId , x300983_g_MissionId) --��������ɾ������  
						--x300983_SetDayCount(sceneId, selfId)
			        
						
						--to be fixed!!!
						--shangyu�ṩ�ӿ�,����13��ר���츳��ְҵר���ܼ��ܵ���
						local nExp = 13
						SetInherenceZhuanFangExp(sceneId, selfId, nExp)
						--PrintNum(13)
						
						Msg2Player( sceneId, selfId, "�������13��ר�����ܵ���", 8, 2)
						Msg2Player( sceneId, selfId, "�������13��ר�����ܵ���", 8, 3)
						
			        
    end
end















--core.lua���ñ��ű��Ľӿ�
--ˢ�»��ܵ���Ҹ���
--�ж�dieId��ְҵ�Ƿ��ǽ������ָ���Ļ��ܵ�ְҵ
--������������1
function x300983_UpdateKillCountProfession(sceneId,selfId,dieId)
	if selfId == dieId then --������ɱ�����
		return -1
	end
	if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- ���û���������
							return
	else	

						    local teamSize = GetNearTeamCount( sceneId, selfId)
						    if teamSize <= 1 then -- ����ӣ�����������
						    
											local misIndex 		=  GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
											local nIndex 		=  GetQuestParam(sceneId, selfId, misIndex,3)
											local nProfession   =  x300983_g_Profession_Enum[nIndex]
											
											--�жϵ�ǰɱ�˵���Ŀ,������������˼�������������MD������
											local today = GetDayOfYear()
											local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
											if lastday ~= today then --����ǵ�һ��ɱ��
														if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3  then 
																local nKillCnt = 1
																SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt)
																SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																x300983_QuestLogRefresh( sceneId, selfId, x300983_g_MissionId)
														end
											else	
														if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3 then          --��������ܵ���ҵ�ְҵ�ͽ��������������ְҵ����
																local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
																nKillCnt       = nKillCnt + 1
																SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt) --ʹ�õ�3λ���汾��������ܵ�ĳ��ְҵ����ҵ����� 
																if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																	SetQuestByIndex(sceneId, selfId, misIndex,7, 1 ) --����������ɱ�־
																	SetQuestByIndex(sceneId, selfId, misIndex,0, 1 ) --����������ɱ�־
																end
																x300983_QuestLogRefresh( sceneId, selfId, x300983_g_MissionId)
														end	
											 end
						    
						    else
								        for i = 0, teamSize - 1 do
								            local memberId = GetNearTeamMember( sceneId, selfId, i)
								            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
													if IsHaveQuestNM( sceneId, memberId, x300983_g_MissionId) ~= 0 then -- ����ó�Ա�����˷���֮·			
																				local misIndex = GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId)
															                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
																								local misIndex 		=  GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId )
																								local nIndex 		=  GetQuestParam(sceneId, memberId, misIndex,3)
																								local nProfession   =  x300983_g_Profession_Enum[nIndex]
																								
																								--�жϵ�ǰɱ�˵���Ŀ,������������˼�������������MD������
																								local today = GetDayOfYear()
																								local lastday = GetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
																								if lastday ~= today then --����ǵ�һ��ɱ��
																											if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3  then 
																													local nKillCnt = 1
																													SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt)
																													SetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																													x300983_QuestLogRefresh( sceneId, memberId, x300983_g_MissionId)
																											end
																								else	
																											if nProfession      == GetZhiye(sceneId, dieId) and GetCurCountry(sceneId,dieId) ~=3 then          --��������ܵ���ҵ�ְҵ�ͽ��������������ְҵ����
																													local nKillCnt = GetQuestParam( sceneId, memberId, misIndex , 2 )
																													nKillCnt       = nKillCnt + 1
																													SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt) --ʹ�õ�3λ���汾��������ܵ�ĳ��ְҵ����ҵ����� 
																													if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																														SetQuestByIndex(sceneId, memberId, misIndex,7, 1 ) --����������ɱ�־
																														SetQuestByIndex(sceneId, memberId, misIndex,0, 1 ) --����������ɱ�־
																													end
																													x300983_QuestLogRefresh( sceneId, memberId, x300983_g_MissionId)
																											end	
																								 end
																				end
													end
										  end
									end
							end


	end
end


--�ύ����
--from common_cangbaotu.lua
function x300983_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	--�ж��Ƿ�������
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300983_g_MissionId);
	local misIndex 		=  GetQuestIndexByID( sceneId, selfId, MissionId )
	local nKillCnt 		=  GetQuestParam(sceneId, selfId, misIndex,2)
	if bHaveMission > 0 then
				if nKillCnt >= x300983_g_Mission_Kill_Cnt then
						local str = "�������"
						Msg2Player(sceneId,selfId,str,8,2)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, str);
						EndQuestEvent();
						DispatchQuestTips(sceneId, selfId)						
						
						--���½��������
						x300983_SetDayCount(sceneId, selfId)
						
						--�������֮��Ѵ���������Ϊ1
						--x300983_g_Quest_Max_Count = 1
						return
				end
	end
end



--�����ܵĽ�����Ĵ�����Ĭ����1�Σ�
--ʹ��ר��֮�顤�������ߵ�ʱ���޸�Ϊ2��
--�˺�������ר��֮�顤�������߽ű�����
--function x300983_Update_Quest_Max_Count(sceneID,selfId)
--	--x300983_g_Quest_Max_Count = 2
--	local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
--	local nQuest_Max_Count = GetQuestParam( sceneId, selfId, misIndex , 1 )
--	nQuest_Max_Count = 2
--	SetQuestByIndex(sceneId, selfId, misIndex,1,nQuest_Max_Count)					  --ʹ�õ�2λ����ÿ�������������� 
--end


--��������Ҳ�Ǵ�
--********************************************************************
--����
--********************************************************************
function x300983_ProcQuestAbandon( sceneId, selfId, MissionId )
	--��������ͬ������
	--PrintStr("x300983_ProcQuestAbandon")
	DelQuest( sceneId, selfId, x300983_g_MissionId )
	--x300983_SetDayCount(sceneId, selfId)   
	Msg2Player(sceneId, selfId, "�����������񡾸��ˡ�����֮·��", 0, 2)
end


---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x300983_GetDayCount(sceneId, selfId)
	--PrintStr("x300983_GetDayCount")
	if x300983_g_Quest_Max_Count > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3])
		return daycount

	end
	return 0
end



-------------------------------------`--------------------------------------------------------------
--���µ�����������
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x300983_SetDayCount(sceneId, selfId)
	--PrintStr("x300983_SetDayCount")
    local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
	if lastday ~= today then
			
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3], 1)		
	else
				
		local daycount = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DAYCOUNT[1], MD_FANGYUZHILU_DAYCOUNT[2], MD_FANGYUZHILU_DAYCOUNT[3], daycount+1)		
	end
end


--**********************************

--���ܹ�������

--**********************************

function x300983_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId) 
	--print("----------------->","x300983_ProcQuestObjectKilled")
	--��Ҫ�������ж��Ƿ���ܵ�������ż�Ĺ��
	--to be fixed!!!
	if objdataId ~= 9526 and objdataId ~= 9527 then --������żֻ�Է���������Ч
		return -1
	end
	
    local teamSize = GetNearTeamCount( sceneId, selfId)
    if teamSize <= 1 then -- ����ӣ�����������
    
				local misIndex 		=  GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId )
				local nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
				--print("-------------->",nKillCnt)
				
				--�жϵ�ǰɱ�˵���Ŀ,������������˼�������������MD������
				local today = GetDayOfYear()
				local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
				if lastday ~= today then --����ǵ�һ��ɱ��
					nKillCnt = 1
					SetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
					SetQuestByIndex(sceneId, selfId, misIndex,7, 0 )
				else
					nKillCnt       = nKillCnt + 1
				end
				
				SetQuestByIndex(sceneId, selfId, misIndex,2,nKillCnt) --ʹ�õ�3λ���汾��������ܵ�ĳ��ְҵ����ҵ����� 
				if nKillCnt >= x300983_g_Mission_Kill_Cnt then
					print("...........................................................")
					SetQuestByIndex(sceneId, selfId, misIndex,7, 1 ) --����������ɱ�־
					SetQuestByIndex(sceneId, selfId, misIndex,0, 1 ) --����������ɱ�־
				end
				
				x300983_QuestLogRefresh( sceneId, selfId, MissionId)
    
    else
		        for i = 0, teamSize - 1 do
		            local memberId = GetNearTeamMember( sceneId, selfId, i)
		            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
							if IsHaveQuestNM( sceneId, memberId, x300983_g_MissionId) ~= 0 then -- ����ó�Ա�����˷���֮·			
														local misIndex = GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId)
									                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
																		local misIndex 		=  GetQuestIndexByID( sceneId, memberId, x300983_g_MissionId )
																		local nKillCnt = GetQuestParam( sceneId, memberId, misIndex , 2 )
																		--print("-------------->",nKillCnt)
																		
																		--�жϵ�ǰɱ�˵���Ŀ,������������˼�������������MD������
																		local today = GetDayOfYear()
																		local lastday = GetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
																		if lastday ~= today then --����ǵ�һ��ɱ��
																			nKillCnt = 1
																			SetQuestData(sceneId, memberId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3], today)
																			SetQuestByIndex(sceneId, memberId, misIndex,7, 0 )
																		else
																			nKillCnt       = nKillCnt + 1
																		end
																		
																		SetQuestByIndex(sceneId, memberId, misIndex,2,nKillCnt) --ʹ�õ�3λ���汾��������ܵ�ĳ��ְҵ����ҵ����� 
																		if nKillCnt >= x300983_g_Mission_Kill_Cnt then
																			print("...........................................................")
																			SetQuestByIndex(sceneId, memberId, misIndex,7, 1 ) --����������ɱ�־
																			SetQuestByIndex(sceneId, memberId, misIndex,0, 1 ) --����������ɱ�־
																		end
																		
																		x300983_QuestLogRefresh( sceneId, memberId, MissionId)
														end
							end
				  end
			end
end
	

	
end

function x300983_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300983_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300983_QuestLogRefresh( sceneId, selfId, MissionId)
	--print("----------------------x300983_QuestLogRefresh")
    if IsHaveQuestNM( sceneId, selfId, x300983_g_MissionId ) == 0 then	-- ���û��������� 
    		return
    end
    
	local mission = "  ����#G"
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300983_g_MissionId)
	local nIdx		 = GetQuestParam( sceneId, selfId, misIndex , 3)          --��ȡ������±�
	if nIdx <=0 or nIdx > getn(x300983_g_Profession_Desc) then
		return
	end
	local strPro   = x300983_g_Profession_Desc[nIdx]	
	mission = mission..strPro.."#Wְҵ�ĵй���һ���#G������ż#W"							
	
	local nRemain = 0
	local nKillCnt = 0;
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_FANGYUZHILU_DATE[1], MD_FANGYUZHILU_DATE[2], MD_FANGYUZHILU_DATE[3])
	if lastday ~= today then --����ǵ�һ��ɱ��
		nRemain = x300983_g_Mission_Kill_Cnt
	else										
		nKillCnt = GetQuestParam( sceneId, selfId, misIndex , 2 )
		nRemain = x300983_g_Mission_Kill_Cnt - nKillCnt
	end
		
	local strTarget  = format("%d",nKillCnt) 				
	BeginQuestEvent(sceneId)
	if nKillCnt < x300983_g_Mission_Kill_Cnt then
				AddQuestLogCustomText( sceneId,
										x300983_g_MissionName,		-- ����
										x300983_g_MissionName,      -- ��������
										mission.."("..strTarget.."/6)",					--����Ŀ��
										x300983_g_CommitNPC,		--����NPC
										mission,               		--������
										x300983_g_MissionInfo.."\n \n#Y��������#W\nר��ѵ��������13�� ",				--��������
										"ʹ��ר��֮�顤��������ÿ����Զ��һ������"			--����С��ʾ
										)
	else
				AddQuestLogCustomText( sceneId,
										x300983_g_MissionName,		-- ����
										x300983_g_MissionName,      -- ��������
										mission.."(6/6)",		--����Ŀ��
										x300983_g_CommitNPC,		--����NPC
										mission,               		--������
										x300983_g_MissionInfo.."\n \n#Y��������#W\nר��ѵ��������13�� ",				--��������
										"ʹ��ר��֮�顤��������ÿ����Զ��һ������"			--����С��ʾ
										)
	end
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, x300983_g_MissionId);
end
