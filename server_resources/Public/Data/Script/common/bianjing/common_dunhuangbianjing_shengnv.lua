--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300581_g_MissionId 				= 	9501                     --����ID
x300581_g_ScriptId 					= 	300581                  --�ű�ID
x300581_g_MissionKind 				= 	1                       --��������
x300581_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300581_g_MissionName				= 	"�����ˡ�������ѡ��"
x300581_g_MissionTarget				= 	"�ҵ�@npc_139406"
x300581_g_MissionTarget1				= 	"ѯ����λ��������"
x300581_g_MissionInfo				= 	""
x300581_g_ContinueInfo				= 	""
x300581_g_MissionCompleted			= 	""
x300581_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300581_g_ExtTarget					=	{ {type=20,n=1,target="������ѡ��"}}

--����

x300581_g_ExpBonus					= 	0;--x300581_AddExpAward               	--����������


x300581_g_BonusMoney1               = 	0
x300581_g_BonusMoney2               =   0
x300581_g_BonusMoney3               =   0
x300581_g_BonusMoney5				=	0

x300581_g_BonusChoiceItem           =   {}
x300581_g_BonusItem					=   {{item=11050004,n=8}}	--��������Ʒ


--MisDescEnd

x300581_g_NpcList = {139405,141533,141534,141535}
x300581_g_ReplyNpcId = 139406


-- Mission Text list

x300581_g_GameId			= 1024

x300581_g_QuestionCount		= 8
x300581_g_QuestionTextList	= {
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ�������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�����#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��",
									text4="\t�ҸҶ϶����·�����#G��ɫ#W���ˣ��ز��ǻ�����һ���ˡ�",
									answer="\t������֪��˭�ǻ�����һ������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴��λ��������˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
								  gonglue1="#G�·����л�ɫ#W",
									gonglue2="#G�·����к�ɫ����ɫ#W",
									gonglue3="#G�·����а�ɫ#W",
									gonglue4="#G�·���û�к�ɫ#W",
									
									result = 1  -- ��

								},
							  {	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�����#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#Wû��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���������·���#G��ɫ#W��#G��ɫ#W��",
									text4="\t�ҸҶ϶���������һ���˵��·�����#G��ɫ#W��",
									answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
									gonglue1="#G�·�������ɫ#W",
									gonglue2="#G�·����л�ɫû�з�ɫ#W",
									gonglue3="#G�·����к�ɫ����ɫ#W",
									gonglue4="#G�·����а�ɫ#W",
									
									result = 1  -- ��

								},
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·��������#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ������������#G��ɫ#W��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ������������#G��ɫ#W��#G��ɫ#W��",
									text4="\t�ҸҶ϶���������һ���˵��·�����#G��ɫ#W��",
								  answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
								  gonglue1="#G�·���û�з�ɫ#W",
									gonglue2="#G�·����к�ɫ�ͻ�ɫ#W",
									gonglue3="#G�·�������ɫ����ɫ#W",
									gonglue4="#G�·�������ɫ#W",
									
									result = 2  -- ��

								},
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�����#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��",
									text4="\t�ҸҶ϶����·�����#G��ɫ#W���ˣ��ز��ǻ�����һ���ˡ�",
									 answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
									gonglue1="#G�·�������ɫ#W",
									gonglue2="#G�·����к�ɫ�ͻ�ɫ#W",
									gonglue3="#G�·�������ɫ#W",
									gonglue4="#G�·���û�а�ɫ#W",
									
									result = 2  -- ��

								},
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�����#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��",
									text4="\t�ҸҶ϶����·�����#G��ɫ#W���ˣ��ز��ǻ�����һ���ˡ�",
									 answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
									gonglue1="#G�·�������ɫ#W",
									gonglue2="#G�·����к�ɫ�ͻ�ɫ#W",
									gonglue3="#G�·����а�ɫ#W",
									gonglue4="#G�·���û����ɫ#W",
									
									result = 3  -- ��

								},
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�����#G��ɫ#W��#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��",
									text4="\t�ҸҶ϶���������һ�����·���û��#G��ɫ#W��",
									 answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
								  gonglue1="#G�·����а�ɫ�ͻ�ɫ#W",
									gonglue2="#G�·����к�ɫ����ɫ#W",
									gonglue3="#G�·����к�ɫ#W",
									gonglue4="#G�·���û����ɫ#W",
									
									result = 3  -- ��

								},
								{	title="�����ˡ�������ѡ��",  --��������
									info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
									task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
								  task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
									task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
									task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
									text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·�û��#G��ɫ#W��",
									text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��",
									text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��#G��ɫ#W��",
									text4="\t�ҸҶ϶���������һ���˵��·�����#G��ɫ#W��",
								 answer="\t������֪��˭�ǻ�����һ������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
									
									gonglue1="#G�·���û�г�ɫ#W",
									gonglue2="#G�·����к�ɫ#W",
									gonglue3="#G�·�������ɫ�Ͱ�ɫ#W",
									gonglue4="#G�·�������ɫ#W",
									
									result = 4  -- ��

								},
						    {	title="�����ˡ�������ѡ��",  --��������
								  info="\t������֮�е���λ��������ʶ�㣬ǰȥ���һ������֪��˭�����ɫ�Ļ������ˡ�", --����
							    task1="ѯ��@npc_"..x300581_g_NpcList[1].."",
						      task2="ѯ��@npc_"..x300581_g_NpcList[2].."",
								  task3="ѯ��@npc_"..x300581_g_NpcList[3].."",
								  task4="ѯ��@npc_"..x300581_g_NpcList[4].."",
							    text1="\t������������������֮�£��ҿ��Ը����㣺������һ���������·���#G��ɫ#Wû��#G��ɫ#W��",
							    text2="\t������λ���������Ҽ����ˣ�������һ���������·���#G��ɫ#W��#G��ɫ#W��",
								  text3="\t������һ���ˣ��ҿ��Ժܿ϶���˵��������һ���˽��������·���#G��ɫ#W��",
								  text4="\t�ҸҶ϶����·�����#G��ɫ#W���ˣ��ز��ǻ�����һ���ˡ�",
								 answer="\t������֪��˭�ǻ�����һ��������\n\t��#Gҩ�޸���#W��#G��������#W��#G�������#W������#G��Ӣ����#W��\n\t#Y(���������������в鿴֪����˵���Ļ����Ա������)",
									answer1="��ҩ�޸���",
									answer2="�ǹ�������",
									answer3="���������",
									answer4="�Ƕ�Ӣ����",
								
								  gonglue1="#G�·�������ɫû����ɫ#W",
								  gonglue2="#G�·����к�ɫ����ɫ#W",
								  gonglue3="#G�·����а�ɫ#W",
								  gonglue4="#G�·���û�л�ɫ#W",
							
							  	result = 4  -- ��
          
							  }
							   }	
				
-- ��������Ʒ�б�
x300581_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300581_GetMissionId( sceneId, selfId )
	return x300581_g_MissionId
end

function x300581_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300581_g_LevelLess then
       return
    end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300581_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x300581_g_MissionName)
				AddQuestText(sceneId,"\t����ҲĽ�������ˣ����Ǿ���˭�ǻ�����һ�����أ�")
				AddQuestNumText(sceneId, myMissionId, "�����Ұ�",2,31);
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
			return
		elseif nExt ==31 then
			x300581_GiveQuestion(sceneId, selfId, targetId, MissionId,1)
			return
		end
	end
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

		if bCompleted>0 then
			local bAnswerQuestion = GetQuestParam( sceneId, selfId, misIndex, 5 )

			if bAnswerQuestion>1 then
				x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "��֪��˭�ǻ�����һ���ˣ�",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer4,2,24);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300581_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300581_ShowTips(sceneId, selfId, "���Ȼ�ϻۣ����ϲ���")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
						
					
					else
						x300581_ShowTips(sceneId, selfId, "���Ȼ�´��ˣ���ȥ�����������ʰɣ�")
						x300581_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
					end
				end
			end
			return
		end
	end
	
	
	if nExt>10 then --��npc�Ի�ʱ
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300581_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300581_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- �������
				--x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300581_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300581_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300581_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300581_g_LevelLess then
		x300581_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300581_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    local day = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2],MD_SNZX_DATE[3] ) == day then
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ", 8, 3)
        return 0
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == day then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300581_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	
	if x300581_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300581_ShowTips(sceneId, selfId, "�����������޷���������")
		return 0
	end
	---------------------------- add end -------------------------------
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,myMissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300581_g_ScriptId, 0, 0, 0,1)-- ������������		
		
	if ret > 0 then
		local str = "������������"..x300581_g_MissionName;
		x300581_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300581_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		GamePlayScriptLog(sceneId, selfId, 1541)
		return 1
	else
		
		x300581_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300581_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300581_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --��û�д���
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300581_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300581_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300581_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300581_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������"..x300581_g_MissionName;
	    x300581_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2], MD_SNZX_DATE[3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end
	else
		x300581_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300581_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	


	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	
	if x300581_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

		if x300581_GiveReward(sceneId,selfId,selectId)>0 then
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300581_g_MissionId)

			local str = "�����������"..x300581_g_MissionName;
			x300581_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2], MD_SNZX_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 1542)
			
		else
			x300581_ShowTips(sceneId, selfId, "������ʧ��")
		end
		end
		
	end
end

function x300581_GiveReward( sceneId, selfId, selectRadioId)
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300581_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- ����������������ѡ����Ʒ��������Խ���¸�������ʱ�Ĵ���
    if count == 0 then
        for i, item in x300581_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("���������Ʒ��@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ռ䲻�㣬�޷������������Ʒ��������ʧ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
end



function x300581_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local bAnswered = GetQuestParam( sceneId, selfId, misIndex, 6 )

	if (bCompleted*bAnswered)<=0 then
		return 0
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300581_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300581_g_MissionName)
	AddQuestText(sceneId,"\tǰЩ���ӣ����������������������ͣ���������λ��ɫ�Ļ������ˡ���������λ���ˣ�ȴ��������ܼҴ��������鷳����")
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
			
	AddQuestText( sceneId,x300581_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300581_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t�㻹û�ҳ�˭�ǻ�����һ���ˣ�")
		AddQuestText(sceneId,"\n#GС��ʾ#W��")
		AddQuestText(sceneId,"\t����ѯ��һ���������䣬��������������")

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300581_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )

	
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\n\t�����˹�Ȼ��������������⻹�������¡�")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, myMissionId);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300581_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300581_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t���Բ��ԣ��ͱ������ж���ȫ��һ����\n\t����ȥ��ϸ���ʰɡ�\n\t#G�����ش���ˣ�����ֻ�û�ȥ����ѯ�ʡ���")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,1);
	


end


function x300581_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	SetQuestByIndex( sceneId, selfId, misIndex, iIndex-1, 1 )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	if value1*value2*value3*value4>0 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		
	end
	
	x300581_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text4)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300581_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300581_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300581_GetMissionName(sceneId,selfId),        -- ��������
							x300581_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300581_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300581_GetMissionMethod(sceneId,selfId),               --������
							x300581_GetMissionText(sceneId,selfId),	--��������
							x300581_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300581_GetMissionName(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		return ""..x300581_g_MissionName;
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300581_g_QuestionTextList[nQuestionId].title

	return str
end

function x300581_GetMissionTask(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y����ظ�:#G@npc_"..x300581_g_ReplyNpcId;
	end
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local strTable = "  ";
	local str1 = strTable..(x300581_g_QuestionTextList[nQuestionId].task1)..format("(%d/1)",value1)
	local str2 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task2)..format("(%d/1)",value2)
	local str3 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task3)..format("(%d/1)",value3)
	local str4 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task4)..format("(%d/1)",value4)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end
	if value2>=1 then
		str2 = "#G"..str2
	else
		str2 = "#W"..str2
	end
	if value3>=1 then
		str3 = "#G"..str3
	else
		str3 = "#W"..str3
	end
	if value4>=1 then
		str4 = "#G"..str4
	else
		str4 = "#W"..str4
	end

	return str1..str2..str3..str4
end

function x300581_GetReplyNpcId(sceneId,selfId)
	return x300581_g_ReplyNpcId;
end

function x300581_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local str=""

	if nMissionStep>0 then
		
		str = x300581_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  ������˵��"..x300581_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  �ֱ���˵��"..x300581_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  ������˵��"..x300581_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  ֻ����˵��"..x300581_g_QuestionTextList[nQuestionId].gonglue4;
		end
		
		
	else
		str = x300581_g_MissionTarget
	end

	return str
end

function x300581_GetMissionText(sceneId,selfId)
	return "\t����λ���ˣ����Ǹ���ǧ�ﰡ�����վ��ǻ��ϴ��٣���׼��ѡ������õ�һ���׸����£��������⸮����˵��硣�ʼ���޷�����������ѡ�����ɫ��Ů�ӣ����ǳ��˰���\n\tĪ���磬��ȥ�����Ҹ��ڵ���λ�����ǣ����������Ǻο�����"
end

function x300581_GetMissionHelp(sceneId,selfId)
	return "\t���Ѱ�һ�����һ���ˡ���Ҫ��ס����������#R���е���ʾ#G�������ܽᣬȻ��������ʾ#R�۲�������˵�����#G����ô��ͻ��ҵ��𰸡�"
end



function x300581_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300581_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300581_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	if npcGuid == x300581_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		
		if nStep==0 then
			AddQuestNumText(sceneId, x300581_g_MissionId, x300581_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300581_g_NpcList do
			iIndex = iIndex+1;
			if npcGuid==item then
				bFind=1;
				break;
			end
		end

		

		if bFind==0 then
			return
		end

		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep~=1 then
			return
		end



		
		local value = GetQuestParam( sceneId, selfId, misIndex, iIndex-1)

		if value==0 then


			AddQuestNumText(sceneId, x300581_g_MissionId, x300581_g_QuestionTextList[nQuestionId].title,2,iIndex+10);
		end
	end
	

	
end

function x300581_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




