--Const
--***********************
-------------------------

--�������а�ƺ�


x310601_g_ScriptId 			= 310601                  --�ű�ID
x310601_g_Name              ="���а���"
x310601_g_NotEnouth         ="���ź�������������ս����û�л�����Σ�"
x310601_g_RepeatAward       ="���Ѿ���ȡ�������а�Ľ�����!"
x310601_g_SuccessAward      ="���ɹ���ȡ�˸����а�Ľ���!"


--
--�������а�	��������а�	С�������а�	��Ѫ�����а�
--ɱ�����а�	ף��ׯ���а�	ս���ȼ����а�	����Ĺ���а�
--���̻����а�	ӡ�Ⱥ����а�	�����������а�	�ֻ�̨���а�
--õ�����а�	���������а�	�����������а�	���������а�


x310601_g_ToplistInfo       =   {
{ClassName = "ף��ׯ", ClassIndex = 1,TitleClassID = 57, Desc = "ף��ׯ���а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",    --ף��ׯ���а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 71},
                   {LevelStart=2,LevelEnd=3,TitleID = 72},
                   {LevelStart=4,LevelEnd=20,TitleID = 73},
                   {LevelStart=21,LevelEnd=50,TitleID = 74},
                   {LevelStart=51,LevelEnd=100,TitleID = 75}
            }
       	} ,
       {ClassName = "ս���ȼ�", ClassIndex = 2,TitleClassID = 17, Desc = "ս���ȼ����а��¼��������PKǿ�ߡ���ҳ�ʼս���ȼ�Ϊ500��ս���ȼ�����500����Ҳ����ʸ���������а��ϡ�����������ս��ÿʤ��һ��+1��ÿʧ��һ��-1��ս���ȼ���ߵ�ǰ100����ҿ��Ե������а�",   --ս���ȼ����а�
       TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 51},
                    {LevelStart=2,LevelEnd=3,TitleID = 52},
                    {LevelStart=4,LevelEnd=20,TitleID = 53},
                    {LevelStart=21,LevelEnd=50,TitleID = 54},
                    {LevelStart=51,LevelEnd=100,TitleID = 55}
             }
        } ,
        {ClassName = "����Ĺ", ClassIndex = 3,TitleClassID = 63, Desc = "����Ĺ���а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",   --����Ĺ���а�
       TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 92},
                    {LevelStart=2,LevelEnd=3,TitleID = 93},
                    {LevelStart=4,LevelEnd=20,TitleID = 94},
                    {LevelStart=21,LevelEnd=50,TitleID = 95},
                    {LevelStart=51,LevelEnd=100,TitleID = 96}
             }
        } ,
        {ClassName = "���̻�", ClassIndex = 4,TitleClassID = 49, Desc = "ȼ���κ�������̻��������������̻����а��ڵķ����������̻�������ߵ�ǰ100����ҿ��Ե������а�",   --���̻����а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 46},
                   {LevelStart=2,LevelEnd=3,TitleID = 47},
                   {LevelStart=4,LevelEnd=20,TitleID = 48},
                   {LevelStart=21,LevelEnd=50,TitleID = 49},
                   {LevelStart=51,LevelEnd=100,TitleID = 50}
            }
       } ,
        {ClassName = "ӡ�Ⱥ�", ClassIndex = 5,TitleClassID = 65, Desc = "ӡ�Ⱥ����а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",   --ӡ�Ⱥ����а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 97},
                   {LevelStart=2,LevelEnd=3,TitleID = 98},
                   {LevelStart=4,LevelEnd=20,TitleID = 99},
                   {LevelStart=21,LevelEnd=50,TitleID = 100},
                   {LevelStart=51,LevelEnd=100,TitleID = 101}
            }
       } ,
        {ClassName = "��������", ClassIndex = 6,TitleClassID = 37, Desc = "�����������а��ۼ�һ��ÿ�������������ܷ������ܷ���ߵ�ǰ100����ҿ��Ե������а�",   --��������
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 31},
                        {LevelStart=2,LevelEnd=3,TitleID = 32},
                        {LevelStart=4,LevelEnd=20,TitleID = 33},
                        {LevelStart=21,LevelEnd=50,TitleID = 34},
                        {LevelStart=51,LevelEnd=100,TitleID = 35}
                 }
            } ,
        {ClassName = "�ֻ�̨", ClassIndex = 7,TitleClassID = 59, Desc = "�ֻ�̨���а��¼�����������ֻ�̨����ʿ�������ɸ���ʱʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",  --�ֻ�̨
            TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 76},
                    {LevelStart=2,LevelEnd=3,TitleID = 77},
                    {LevelStart=4,LevelEnd=20,TitleID = 78},
                    {LevelStart=21,LevelEnd=50,TitleID = 79},
                    {LevelStart=51,LevelEnd=100,TitleID = 80}
             }
        } ,
		{ClassName = "õ��", ClassIndex = 8,TitleClassID = 31, Desc = "�յ���õ�廨����Ů��ҽ���פõ�����а��κ�õ�廨��������1������ָ��������ָ����ߵ�ǰ100����ҿ��Ե������а�",    --	õ�����а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 26},
                   {LevelStart=2,LevelEnd=3,TitleID = 27},
                   {LevelStart=4,LevelEnd=20,TitleID = 28},
                   {LevelStart=21,LevelEnd=50,TitleID = 29},
                   {LevelStart=51,LevelEnd=100,TitleID = 30}
            }
		} ,
		{ClassName = "�����", ClassIndex = 9,TitleClassID = 61, Desc = "��������а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",    --	���������а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 111},
                   {LevelStart=2,LevelEnd=3,TitleID = 112},
                   {LevelStart=4,LevelEnd=20,TitleID = 113},
                   {LevelStart=21,LevelEnd=50,TitleID = 114},
                   {LevelStart=51,LevelEnd=100,TitleID = 91}
            }
		} ,
        {ClassName = "��������", ClassIndex = 10,TitleClassID = 43, Desc = "�����������а���¼��Ѱ����������̽���ң�ÿʹ��һ�������ر�ͼ�ھ򱦲ض�������¼���ڱ�������ߵ�ǰ100����ҿ��Ե������а�",  		--�����������а� 

           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 36},
                   {LevelStart=2,LevelEnd=3,TitleID = 37},
                   {LevelStart=4,LevelEnd=20,TitleID = 38},
                   {LevelStart=21,LevelEnd=50,TitleID = 39},
                   {LevelStart=51,LevelEnd=100,TitleID = 40}
            }
       } ,
       
	    {ClassName = "������", ClassIndex = 11,TitleClassID = 51, Desc = "���������а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�", --���������а�
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 56},
                        {LevelStart=2,LevelEnd=3,TitleID = 57},
                        {LevelStart=4,LevelEnd=20,TitleID = 58},
                        {LevelStart=21,LevelEnd=50,TitleID = 59},
                        {LevelStart=51,LevelEnd=100,TitleID = 60}
                 }
            } ,
	    
		{ClassName = "����", ClassIndex = 12,TitleClassID = 45, Desc = "�������а���¼��������������ʿ��ÿɱ��һֻ����֮�궼�������������������������ߵ�ǰ100����ҿ��Ե������а�",   --�������а�
		
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 41},
                   {LevelStart=2,LevelEnd=3,TitleID = 42},
                   {LevelStart=4,LevelEnd=20,TitleID = 43},
                   {LevelStart=21,LevelEnd=50,TitleID = 44},
                   {LevelStart=51,LevelEnd=100,TitleID = 45}
            }
       } ,     
       {ClassName = "�����", ClassIndex = 13,TitleClassID = 53, Desc = "��������а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100����ҿ��Ե������а�",   --��������а�
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 61},
                   {LevelStart=2,LevelEnd=3,TitleID = 62},
                   {LevelStart=4,LevelEnd=20,TitleID = 63},
                   {LevelStart=21,LevelEnd=50,TitleID = 64},
                   {LevelStart=51,LevelEnd=100,TitleID = 65}
            }
       } ,
       {ClassName = "С����", ClassIndex = 14,TitleClassID = 47,  --"��С���Ⱦ���ı�����ĸ�̸���۰ɣ����������������������磡ʹ��С���ȹ㲥��������ǰ100����ҿ��Ե������а�",
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 102},
                        {LevelStart=2,LevelEnd=3,TitleID = 103},
                        {LevelStart=4,LevelEnd=20,TitleID = 104},
                        {LevelStart=21,LevelEnd=50,TitleID = 105},
                        {LevelStart=51,LevelEnd=100,TitleID = 106}
                 }
            } ,
       {ClassName = "��Ѫ��", ClassIndex = 15,TitleClassID = 55, Desc = "��Ѫ�����а�ֻ������ģʽ�²��������ע�⣬���������ÿ��ʣ����������࣬��ɼ������ᱻ�������а���ɴ˸���ʱ����̵�ǰ100������ҿ��Ե������а�",   --��Ѫ�����а�

           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 66},
                   {LevelStart=2,LevelEnd=3,TitleID = 67},
                   {LevelStart=4,LevelEnd=20,TitleID = 68},
                   {LevelStart=21,LevelEnd=50,TitleID = 69},
                   {LevelStart=51,LevelEnd=100,TitleID = 70}
            }
       } ,
        {ClassName = "ɱ��", ClassIndex = 16,TitleClassID = 15, Desc = "ɱ�����а��¼�������Чɱ����������ʿ�ǡ�ɱ���������Լ��ȼ�20�����ϵ������Ҳ�������ɱ���������2Сʱ��ɱ��ͬһ�������ҳ���10�Σ����ٴ�ɱ������ҽ���������ɱ��������Чɱ��������ǰ100����ҿ��Ե������а�",  --ɱ��
            TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 21},
                    {LevelStart=2,LevelEnd=3,TitleID = 22},
                    {LevelStart=4,LevelEnd=20,TitleID = 23},
                    {LevelStart=21,LevelEnd=50,TitleID = 24},
                    {LevelStart=51,LevelEnd=100,TitleID = 25}
             }
        },
	 }
    

                
function x310601_ProcEnumEvent(sceneId, selfId, NPCId)

    local WeekDay = GetWeek()
    local Min = GetMinOfDay()
    if(WeekDay < 1 or WeekDay > 6) then
        return
    end
    if(WeekDay == 1 and Min < 60 ) then
        return
    end
    if(WeekDay == 6 and Min > 60*23 ) then
        return
    end

	if GetUpdateDBBeforeToggle()==1 or GetUpdateDBAfterToggle()==1 then
		return
	end	
    --local dayTime = GetDayTime()
    --if(dayTime < 10031) then
		--return
   	--end	
   
    local nTitleIndex = x310601_GetTitleIndex()
        
	AddQuestNumText(sceneId,x310601_g_ScriptId,"��ȡ������ս������\r",3,100)
end

--���������а�  ��������а� ��Ѫ�����а� ף��ׯ���а� ս���ȼ����а�  �ֻ�̨
--  1               5             7             9            10          11
--  GetToplistRankEx

function x310601_IsMultiChampion(nTitleIndex)
	--local MultiChampionTab = {1,5,7,9,10,11}
	if(nTitleIndex == 1 or nTitleIndex == 3 or nTitleIndex == 5 or nTitleIndex == 7 or nTitleIndex == 9 or nTitleIndex == 11 or nTitleIndex == 13 or nTitleIndex == 15) then
		return 1
	end
	return 0
end

function x310601_GetTitleID(sceneId, selfId)	--
	local nTitleIndex = x310601_GetTitleIndex()
    local nTitleType = x310601_g_ToplistInfo[nTitleIndex].TitleClassID
    --local nTitleRank = GetToplistRank(sceneId,selfId,nTitleType)
	local nTitleRank = 1
	if x310601_IsMultiChampion(nTitleIndex) == 1 then
		nTitleRank = GetToplistRankEx(sceneId,selfId,nTitleType) + 1
	else	
		nTitleRank = GetToplistRank(sceneId,selfId,nTitleType) + 1
	end
    local TitleInfo = x310601_g_ToplistInfo[nTitleIndex].TitleInfo
    for i, s in TitleInfo do
        if nTitleRank >= s.LevelStart and nTitleRank <= s.LevelEnd then
            return s.TitleID
        end
    end
    return -1
end

function x310601_GetTitleIndex()	--
	local nWeekIndex = GetWeekIndex() --since 2010-01-25
	local nTitleIndex = mod(nWeekIndex,16)
    if nTitleIndex == 0 then
        nTitleIndex = 16
    end
	nTitleIndex = nTitleIndex -1	--���ܵ�
	if nTitleIndex == 0 then
		nTitleIndex = 16
	end

    return nTitleIndex
end

function x310601_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--����������ִ�д˽ű�
	local titleIndex = x310601_GetTitleIndex()
	--x310601_g_ToplistInfo[nTitleIndex].TitleClassID
    local titleID = x310601_GetTitleID(sceneId, selfId, NPCId)

    BeginQuestEvent(sceneId)
    
    local TitleDesc;
	local nLevel = GetLevel(sceneId, selfId)
	local nExp = nLevel * 240000
    local sex = GetSex(sceneId,selfId)
    local nTitleClassID = x310601_g_ToplistInfo[titleIndex].TitleClassID
	local TitleInfo = x310601_g_ToplistInfo[titleIndex].TitleInfo
	local TitleID = TitleInfo[1].TitleID
    local TitleBuffName = GetImpactNameByTitleID(TitleID)
	local TitleName = GetTitleNameByTitleID(TitleID, sex)
	local nTitleIndex = x310601_GetTitleIndex()
    local nTitleType = x310601_g_ToplistInfo[nTitleIndex].TitleClassID

	local nTitleRank = 1
	if x310601_IsMultiChampion(nTitleIndex) == 1 then
		nTitleRank = GetToplistRankEx(sceneId,selfId,nTitleType) + 1
	else	
		nTitleRank = GetToplistRank(sceneId,selfId,nTitleType) + 1
	end

   if nTitleRank <= 100 and nTitleRank > 0 then
    TitleDesc = "#Y��ȡ�������½���\r\n\r\n#W���ܽ��е���#G"..x310601_g_ToplistInfo[titleIndex].ClassName.."��ս��#W��Ŀǰ���ڰ佱��\r\n#W�������ܵı����л���˵�#G"..nTitleRank.."#W����\n��������#G"..nExp.."#W�㾭�齱���������¶��⽱����\n\r\n"
   else
    TitleDesc = "#Y��ȡ�������½���\r\n\r\n#W���ܽ��е���#G"..x310601_g_ToplistInfo[titleIndex].ClassName.."��ս��#W��Ŀǰ���ڰ佱��\r\n#W�������ܵı�����#Gû�л������#W��\n����������ܱ�����ȡ�����ν�����#G"..nExp.."#W�㾭�齱���������¶��⽱����\n\r\n"
   end
    TitleDesc = TitleDesc.."#Y".."����    ".."�ƺż�����".."\n"
    TitleDesc = TitleDesc.."#W".."1       #G"..TitleName.."#W��"..TitleBuffName.."\r\n"

	TitleID = TitleInfo[2].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."2~3     #G"..TitleName.."#W��"..TitleBuffName.."\r\n"

	TitleID = TitleInfo[3].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."4~20    #G"..TitleName.."#W��"..TitleBuffName.."\r\n"

    TitleID = TitleInfo[4].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."21~50   #G"..TitleName.."#W��"..TitleBuffName.."\r\n"
    
    TitleID = TitleInfo[5].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."51~100  #G"..TitleName.."#W��"..TitleBuffName
    
    AddQuestText(sceneId,"#Y"..TitleDesc)
     ---AddQuestText(sceneId,"#Y"..TitleBuffName)
    EndQuestEvent()
    DispatchQuestInfo(sceneId, selfId, NPCId, x310601_g_ScriptId,-1);
end


function x310601_ProcAccept( sceneId, selfId, targetId, MissionId, index )
    local titleIndex = x310601_GetTitleIndex()
    local titleID = x310601_GetTitleID(sceneId, selfId)
    --print(titleID)
    --titleID = 57
    --print(titleID)

    
    
    if titleID < 0 then
        --print("2")
		Msg2Player(sceneId,selfId,x310601_g_NotEnouth,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_NotEnouth);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
    elseif IsTitleActive(sceneId, selfId, titleID) > 0 then
        --print("1")
        Msg2Player(sceneId,selfId,x310601_g_RepeatAward,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_RepeatAward);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	else
         --print("3")
        AwardTitle(sceneId, selfId, titleID)
        local level = GetLevel(sceneId, selfId)
        local exp = level * 240000
        AddExp(sceneId, selfId, exp)  
        
		Msg2Player(sceneId,selfId,x310601_g_SuccessAward,8,2)

		local sex = GetSex(sceneId,selfId)
		local TitleName = GetTitleNameByTitleID(titleID, sex)
		local msg = "�������"..TitleName.."�ƺš�"
		Msg2Player(sceneId,selfId,msg,8,2)
		msg = "�������"..exp.."�㾭�顣"
		Msg2Player(sceneId,selfId,msg,8,2)
		   
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_SuccessAward);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
    end

    return 1
end
function x310601_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end
function x310601_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	