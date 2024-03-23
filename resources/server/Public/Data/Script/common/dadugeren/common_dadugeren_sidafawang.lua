--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300564_g_MissionId 				= 	9300                     --����ID
x300564_g_ScriptId 					= 	300564                  --�ű�ID
x300564_g_MissionKind 				= 	1                       --��������
x300564_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������


x300564_g_MissionName				= 	"�����ˡ��Ĵ���"
x300564_g_MissionTarget				= 	"�ҵ�@npc_141500"
x300564_g_MissionTarget1				= 	"ѯ�������Ĵ���"
x300564_g_MissionInfo				= 	""
x300564_g_ContinueInfo				= 	""
x300564_g_MissionCompleted			= 	""
x300564_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300564_g_ExtTarget					=	{ {type=20,n=1,target="���̷���"}}

--����

x300564_g_ExpBonus					= 	0;--x300564_AddExpAward               	--����������
x300564_g_BonusItem					=	{}	--��������Ʒ

x300564_g_BonusMoney1               = 	0
x300564_g_BonusMoney2               =   0
x300564_g_BonusMoney3               =   0
x300564_g_BonusMoney5				=	1000

x300564_g_BonusChoiceItem           =   {}


--MisDescEnd

x300564_g_NpcList = {139829,139828,139827,139834}
x300564_g_ReplyNpcId = 141500


-- Mission Text list

x300564_g_GameId			= 1001

x300564_g_QuestionCount		= 7	
x300564_g_QuestionTextList	= {
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#Gӥ��˵�滰#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#Gʨ��˵�ٻ�#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G��������ͽ#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G�����Ǻ���#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ��#W��#G��������#W��#G��üӥ��#W������#G��������#W��\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
								  gonglue1="#Gӥ��˵�滰#W��",
									gonglue2="#Gʨ��˵�ٻ�#W��",
									gonglue3="#G��������ͽ#W��",
									gonglue4="#G�����Ǻ���#W��",
									
									result = 3  -- ��

								},
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#G�Ҳ�����ͽ#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#G�Ҳ�����ͽ#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G����˵�滰#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G����˵�滰#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ��#W����������#W����üӥ��#W��������������#W��\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#G�Ҳ�����ͽ#W��",
									gonglue2="#G�Ҳ�����ͽ#W��",
									gonglue3="#G����˵�滰#W��",
									gonglue4="#G����˵�滰#W��",
									
									result = 4  -- ��

								},
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#Gӥ������ͽ#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#G�Ҳ�����ͽ#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#Gʨ��˵�滰#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G��������ͽ#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ����������������üӥ������������������\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#Gӥ������ͽ#W��",
									gonglue2="#G�Ҳ�����ͽ#W��",
									gonglue3="#Gʨ��˵�滰#W��",
									gonglue4="#G��������ͽ#W��",
									
									result = 2  -- ��

								},
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#G��˵�滰#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#G��������ͽ#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G��˵�滰#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G����˵�ٻ�#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ����������������üӥ������������������\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#G��˵�滰#W��",
									gonglue2="#G��������ͽ#W��",
									gonglue3="#G��˵�滰#W��",
									gonglue4="#G����˵�ٻ�#W��",
									
									result = 2  -- ��

								},
									{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#G�����Ǻ���#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#G�����Ǻ���#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G˵�ٻ�������ͽ#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G��������ͽ#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ����������������üӥ������������������\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#G�����Ǻ���#W��",
									gonglue2="#G�����Ǻ���#W��",
									gonglue3="#G˵�ٻ�������ͽ#W��",
									gonglue4="#G��������ͽ#W��",
									
									result = 1  -- ��

								},
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#G����˵�ٻ�#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#Gʨ������ͽ#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G��ͽ˵�˼ٻ�#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G����˵�ٻ�#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ����������������üӥ������������������\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#G����˵�ٻ�#W��",
									gonglue2="#Gʨ������ͽ#W��",
									gonglue3="#G��ͽ˵�˼ٻ�#W��",
									gonglue4="#G����˵�ٻ�#W��",
									
									result = 1  -- ��

								},
								{	title="�����ˡ��Ĵ���",  --��������
									info="\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ���˻�����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��", --����
									task1="ѯ����������@npc_"..x300564_g_NpcList[1].."",
									task2="ѯ�ʰ�üӥ��@npc_"..x300564_g_NpcList[2].."",
									task3="ѯ����������@npc_"..x300564_g_NpcList[3].."",
									task4="ѯ�ʽ�ëʨ��@npc_"..x300564_g_NpcList[4].."",
									text1="\t��ô�����������������ᱻ���ɣ��ߣ���ֻ�ܸ����㣺#G���Ǻ���#W��",
									text2="\t�Ұ�üӥ���������������ǵȱ������̵���С֮ͽ���������ҵ���֪����#G��������ͽ#W��",
									text3="\t�벻�����˾�Ȼ�ỳ�ɵ�������������������ҵ��Ʋ⣺#G��˵�滰#W��",
									text4="\tлѷһ�����ܣ������������������Ҳ�����������ܿ϶���#G��������ͽ#W��",
									answer="\t���Ѿ�֪��˭����ͽ�ˣ���֪����\n\t�ǽ�ëʨ����������������üӥ������������������\n\t#Y(���������������в鿴�Ĵ���˵���Ļ����Ա������)",
									answer1="�ǽ�ëʨ��",
									answer2="����������",
									answer3="����������",
									answer4="�ǰ�üӥ��",
									
									gonglue1="#G���Ǻ���#W��",
									gonglue2="#G��������ͽ#W��",
									gonglue3="#G��˵�滰#W��",
									gonglue4="#G��������ͽ#W��",
									
									result = 2  -- ��

								}
							   }	
				

-- ��������Ʒ�б�
x300564_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300564_GetMissionId( sceneId, selfId )
	return x300564_g_MissionId
end

function x300564_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300564_g_LevelLess then
       return
    end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300564_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
		return
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x300564_g_MissionName)
				AddQuestText(sceneId,"\t���֤�ݱ������������Ĵ����е�һλ�Ͳ�˹����͵Ϯһ������Ī���ϵ����������һ�ƣ����Ը��һ�ԣ�")
				AddQuestNumText(sceneId, myMissionId, "�õģ������Ұ�",2,31);
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
			return
		elseif nExt ==31 then
			x300564_GiveQuestion(sceneId, selfId, targetId, MissionId,1)
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
				x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "��֪��˭����ͽ�ˣ�",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer4,2,24);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300564_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300564_ShowTips(sceneId, selfId, "��������˵���ˣ�")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
					else
						x300564_ShowTips(sceneId, selfId, "��˵���ˣ�����û�ã���ȥ��ϸ���ʣ�")
						x300564_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
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

		x300564_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300564_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- �������
				--x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300564_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300564_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300564_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300564_g_LevelLess then
		x300564_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300564_ShowTips(sceneId, selfId, "���Ѿ������������������������")
		return 0;
	end

    local day = GetDayOfYear()
    if GetQuestData( sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2],MD_MJFY_DATE[3] ) == day then
        x300564_ShowTips(sceneId, selfId, "�ܱ�Ǹ���������Ѿ����������񣬲����ٴ���ȡ" )
        return 0;
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

function x300564_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0
	end
	
	if x300564_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300564_ShowTips(sceneId, selfId, "�����������޷���������")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300564_g_ScriptId, 0, 0, 0,1)-- ������������		
		
	if ret > 0 then
		local str = "������������"..x300564_g_MissionName;
		x300564_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300564_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		GamePlayScriptLog(sceneId, selfId, 901)
		return 1
	else
		
		x300564_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300564_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300564_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --��û�д���
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300564_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300564_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300564_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300564_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������"..x300564_g_MissionName;
	    x300564_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2], MD_MJFY_DATE[3], today)
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
		x300564_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300564_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	
	if x300564_CheckSubmit(sceneId, selfId )>0 then
		
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
            return 0
        end

        if x300564_GiveReward(sceneId,selfId,selectId) == 0 then
            return
        end

		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300564_g_MissionId)

			local str = "�����������"..x300564_g_MissionName;
			x300564_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData(sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2], MD_MJFY_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 902)
			
		else
			x300564_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300564_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300564_g_RewardTable do
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
        for i, item in x300564_g_RewardTable do
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



function x300564_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "�˻���첻����")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
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
function x300564_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300564_g_MissionName)
	AddQuestText(sceneId,"\n\t���գ�������������̳��Ȼ����˹����͵Ϯ����ʧ��һЩ������Ҫ�����¡���������̳�����ر�ɭ�ϣ���û����Ӧ����˹�˾�������������ɵ��֡�\n\t�ֽ������̹�����ԭ����ͬ������Ҫ�����ڼ������㲻��ǰȥ��������ִ��ʹ��ǫһ��")
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
			
	AddQuestText( sceneId,x300564_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
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

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300564_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t���ʹ��Ĵ�������")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300564_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\n\t�ܺã����ҵ��ж�һģһ�����������ˣ�������Ľ�����")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
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

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId);
	CallScriptFunction( 256225, "Finishfawang", sceneId, selfId)	

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�����Ŀ
---------------------------------------------------------------------------------------------------
function x300564_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300564_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t��������˵�Ļ��������Ѿ��������ˣ����Ȼ��û�жϳ�˭����ͽ��\n\t����û�ã��ٻ�ȥ��ϸ���ʣ�\n\t#G�����ش���ˣ�����ֻ�û�ȥ����ѯ�ʡ���")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,1);
	


end


function x300564_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
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
	
	x300564_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text4)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300564_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300564_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x300564_GetMissionName(sceneId,selfId),        -- ��������
							x300564_GetMissionTask(sceneId,selfId),		--����Ŀ��
							"@npc_"..x300564_GetReplyNpcId(sceneId,selfId),			--����NPC
							x300564_GetMissionMethod(sceneId,selfId),               --������
							x300564_GetMissionText(sceneId,selfId),	--��������
							x300564_GetMissionHelp(sceneId,selfId)					--����С��ʾ
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
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

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300564_GetMissionName(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		return ""..x300564_g_MissionName;
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300564_g_QuestionTextList[nQuestionId].title

	return str
end

function x300564_GetMissionTask(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y����ظ�:#G@npc_"..x300564_g_ReplyNpcId;
	end
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local strTable = "  ";
	local str1 = strTable..(x300564_g_QuestionTextList[nQuestionId].task1)..format("(%d/1)",value1)
	local str2 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task2)..format("(%d/1)",value2)
	local str3 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task3)..format("(%d/1)",value3)
	local str4 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task4)..format("(%d/1)",value4)

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

function x300564_GetReplyNpcId(sceneId,selfId)
	return x300564_g_ReplyNpcId;
end

function x300564_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local str=""

	if nMissionStep>0 then
		
		str = x300564_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  ��������˵��"..x300564_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  ��üӥ��˵��"..x300564_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  ��������˵��"..x300564_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  ��ëʨ��˵��"..x300564_g_QuestionTextList[nQuestionId].gonglue4;
		end
		
		
	else
		str = x300564_g_MissionTarget
	end

	return str
end

function x300564_GetMissionText(sceneId,selfId)
	return "\t���������Ĵ����г���һ����ͽ����ȥѯ��һ���Ĵ�������������#G������#W�������#G�滰#W��#Gһ����#W��#G����#W��\n\t��ס��#G���ѵ��˲�һ������ͽ����ͽ��һ������#W��"
end

function x300564_GetMissionHelp(sceneId,selfId)
	return "\t���ʶ����ͽ���ĸ���������#R������#G�������#R�滰#G��#Rһ���˻�����#G�����ҳ���#R����������ì��#G�ģ���ô����#R����һ���Ǽٻ�#G����ô������������˵��һ�����滰���������ǵ��滰�����������۳�˭����ͽ��\n\t��ס��#R���ѵ��˲�һ������ͽ����ͽ��һ������#G��"
end



function x300564_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300564_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300564_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		
		return
	end
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	if npcGuid == x300564_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		
		if nStep==0 then
			AddQuestNumText(sceneId, x300564_g_MissionId, x300564_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300564_g_NpcList do
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


			AddQuestNumText(sceneId, x300564_g_MissionId, x300564_g_QuestionTextList[nQuestionId].title,2,iIndex+10);
		end
	end
	

	
end

function x300564_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




