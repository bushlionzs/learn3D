--MisDescBegin

x300612_g_ScriptId 	  = 300612
x300612_g_MissionKind 				= 	1                       --��������
x300612_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300612_MissionName = "���ڽ�����"

--MisDescEnd	  
						
--������																	   
x300612_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080017,ReturnMoney=2500 }, 
										  {	MissionId=7557,BaoDanId=13080018,ReturnMoney=5000 },
										  {	MissionId=7558,BaoDanId=13080019,ReturnMoney=7500 },
										  {	MissionId=7546,BaoDanId=13080020,ReturnMoney=15000 },
										  { MissionId=7547,BaoDanId=13080021,ReturnMoney=20000 },
										  { MissionId=7548,BaoDanId=13080022,ReturnMoney=25000 },
										}

function x300612_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x300612_g_ScriptId,x300612_MissionName,3);

end



--�������ť������������ִ�д˽ű�
function x300612_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	local Readme_1 ="\t���ѣ�����������֮�£������б��ձȽϿɿ��ɣ���Ȼ�������ȫ����ʧ�����ܱ�Ѫ���޹�Ҫǿ�ܶ࣬��˵�ǰɣ�#r"
	local Readme_2="\t�ðɣ����ڰ�#G���ⵥ#W�������������϶��������⸶��"
	local Readme = Readme_1..Readme_2
	AddQuestText(sceneId,Readme)
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300612_g_ScriptId, -1);

end

--**********************************
--����
--**********************************
function x300612_ProcAcceptCheck( sceneId, selfId, targetId )
	
	local IsHaveBaoDan = 0

	for i,itm in x300612_g_SubMissionID do
		local ItemCount = GetItemCountInBag(sceneId, selfId,itm.BaoDanId)
		if ItemCount > 0 then
			IsHaveBaoDan = 1
			--ɾ�����ⵥ
			DelItem(sceneId, selfId,itm.BaoDanId,ItemCount)	
			AddMoney(sceneId,selfId,0,ItemCount * itm.ReturnMoney) 	
			local Readme = "����ɹ�����������#R#{_MONEY"..ItemCount * itm.ReturnMoney.."}"

			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,Readme)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)		
			Msg2Player(sceneId,selfId,Readme,8,2)
		end
	end

	if IsHaveBaoDan == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ����û�����ⵥ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û�����ⵥ",8,2)
	end
	
end

--**********************************
--����
--**********************************
function x300612_ProcAccept( sceneId, selfId )
end

--�������
--����1����ɹ���0��������ʧ��
function x300612_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300612_ProcQuestAbandon( sceneId, selfId,MissionId )
end

