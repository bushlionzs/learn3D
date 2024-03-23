--############################################
--##��� 2v2 ս���ɼ���ű� by rj 2010-11-3 ##
--############################################

--��ǰ�ɼ��������������飬ϣ���������ͼ�ϳ��ֵĲɼ������ͼ���Ӧ��buf
x303104_g_GrowPonitTypeAry 			= 
{
{type = 840, bufid = 30070}, 
{type = 841, bufid = 30071},
{type = 842, bufid = 30072}, 
{type = 843, bufid = 30073},
{type = 844, bufid = 30074}, 
{type = 845, bufid = 30075},
{type = 846, bufid = 30070}, 
{type = 847, bufid = 30071},
{type = 848, bufid = 30072}, 
{type = 849, bufid = 30073},
{type = 850, bufid = 30074}, 
{type = 851, bufid = 30075},
{type = 852, bufid = 30070}, 
{type = 853, bufid = 30071},
{type = 854, bufid = 30072}, 
{type = 855, bufid = 30073},
{type = 856, bufid = 30074}, 
{type = 857, bufid = 30075},
}											
--�ɼ������������
x303104_g_curGrowPonitInfoTbl 		= {}
--��ǰ�ɼ����ϣ��ʹ��objid��key
x303104_g_curExistAllGrowPonitTbl 	= {}	
--��ǰ�����Ƿ��Ѿ���ʼ������־��													
x303104_g_curSceneInit	 			= {}		
--�ɼ�����buf��Ӧ���֣�key��bufid
x303104_g_GrowPonitBufName			= {}

-------------------------------------------------------------------------
--����ս���߼����õĳ�ʼ���ɼ��㺯��
-------------------------------------------------------------------------
function x303104_OnInit(sceneId)
	
	--ÿ�ν���ս���ɼ���ȫ�����գ�-1 ���������ڳ����ڲ���ǿת�����ֵ��ʹ�������ӳٲ���ˢ����Դ
	for i, item in x303104_g_GrowPonitTypeAry do
		RecycleGrowPointByType(sceneId, item.type, -1)
	end

	--��ʼ���ɼ�buf���֣�key��bufid
	x303104_g_GrowPonitBufName[30070] = "����"
	x303104_g_GrowPonitBufName[30071] = "�ظ�"
	x303104_g_GrowPonitBufName[30072] = "�����˺�����"
	x303104_g_GrowPonitBufName[30073] = "����"
	x303104_g_GrowPonitBufName[30074] = "�˺�����"
	x303104_g_GrowPonitBufName[30075] = "���Ӽ���"	
	--��ʼ������������������
	x303104_g_curGrowPonitInfoTbl[sceneId] =
	 {
		 {type = 0, exist = 0, tmp = 0, x = 90,y = 	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	86,y = 	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	88,y = 	141	}, 
		 {type = 0, exist = 0, tmp = 0, x =	87,y = 	113	}, 
		 {type = 0, exist = 0, tmp = 0, x =	84,y = 	111	}, 
		 {type = 0, exist = 0, tmp = 0, x =	79,y = 	112	}, 
		 {type = 0, exist = 0, tmp = 0, x =	167,y =	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	170,y =	136	}, 
		 {type = 0, exist = 0, tmp = 0, x =	174,y =	140	}, 
		 {type = 0, exist = 0, tmp = 0, x =	167,y =	116	}, 
		 {type = 0, exist = 0, tmp = 0, x =171,y =	112	}, 
		 {type = 0, exist = 0, tmp = 0, x =174,y =	114	}, 
		 {type = 0, exist = 0, tmp = 0, x =127,y =	142	}, 
		 {type = 0, exist = 0, tmp = 0, x =125,y =	151	}, 
		 {type = 0, exist = 0, tmp = 0, x =130,y =	151	}, 
		 {type = 0, exist = 0, tmp = 0, x =125,y =	105	}, 
		 {type = 0, exist = 0, tmp = 0, x =128,y =	113	}, 
		 {type = 0, exist = 0, tmp = 0, x =130,y =	105	}, 

	 }
	 
	 --ɾ����������ͼ�ʹ����Ĳɼ���Դ��
	 x303104_g_curSceneInit[sceneId] = 1
end

-------------------------------------------------------------------------
--����������ս�����õ��Ĳɼ��� buf
-------------------------------------------------------------------------
function x303104_RecyclePlayerAllBuf(sceneId, selfId)

	for i, item in x303104_g_GrowPonitTypeAry do
        DispelSpecificImpact(sceneId, selfId, item.bufid, 1)
    end
end


-------------------------------------------------------------------------
--����ս���߼���ʱ���õĲ����ɼ��㺯��
-------------------------------------------------------------------------
function x303104_OnTimeMakeGrowPoint(sceneId)

	--��¼����������OnInit֮�󽫿ռ������ܽ��У�����������
	if x303104_g_curSceneInit[sceneId] == nil then
		return
	end
	
	--���Դ����ȡ��������
	local nTypeNum = getn(x303104_g_GrowPonitTypeAry)
	if nTypeNum == 0 then
		return
	end

	local tblOkPoint = {}
	local tblOkType = {}
	local nOkPointIdx = 0
	local nOkTypeIdx = 0
	local nExistNum = 0
	local nPosNum = getn(x303104_g_curGrowPonitInfoTbl[sceneId])

	--�ҳ����л�û��ӵ���ͼ�ϵ����ͼ��������ʱ����
	for i, item1 in x303104_g_GrowPonitTypeAry do
		
		local nExist = 0
		for j, item2 in x303104_g_curGrowPonitInfoTbl[sceneId] do
			if item1.type == item2.type then
				nExist = 1
				break
			end
		end
		
		if nExist == 0 then
			nOkTypeIdx = nOkTypeIdx + 1
			tblOkType[nOkTypeIdx] = item1.type
		end
	end

	--�������Ͳɼ��㶼�ڵ�ͼ���ˣ������������
	if getn(tblOkType) == 0 then
		return
	end

	--�ҳ����л�û�б�ռ�õ�λ�õ������ʱ����
	for i = 1, nPosNum do
		if x303104_g_curGrowPonitInfoTbl[sceneId][i].exist == 0 then
			nOkPointIdx = nOkPointIdx + 1
			tblOkPoint[nOkPointIdx] = x303104_g_curGrowPonitInfoTbl[sceneId][i]
		
			--��¼x303104_g_curGrowPonitTypeTbl������
			tblOkPoint[nOkPointIdx].tmp = i
		else
			nExistNum = nExistNum + 1
		end
	end
	
	--�Ѿ�����ˢ��λ�õ�����ޣ����Ѿ����������ֵһ�����ˣ�
	if nExistNum >= nTypeNum then
		return
	end
	
	--�����������ҳ�һ��λ�����������Դ
	if nOkPointIdx > 0 then
		local nIndex1 = random(1, nOkPointIdx)
		local nIndex2 = random(1, nOkTypeIdx)

		--ˢ�������Դ, 0 ��ʾ����ˢ����û���ӳ٣����� OnCreate ���� obj
		RecycleGrowPointByType(sceneId, tblOkType[nIndex2], 0)
		SetGrowPointPos(sceneId, tblOkType[nIndex2], tblOkPoint[nIndex1].x, tblOkPoint[nIndex1].y)

		--�������λ�õ���Ϣ
		x303104_g_curGrowPonitInfoTbl[sceneId][tblOkPoint[nIndex1].tmp].type = tblOkType[nIndex2]	
		x303104_g_curGrowPonitInfoTbl[sceneId][tblOkPoint[nIndex1].tmp].exist = 1	
	end		
end

-------------------------------------------------------------------------
--�ɼ��㴴��
-------------------------------------------------------------------------
function x303104_OnCreate(sceneId, growPointType, x, y)

	--ʵ�ʴ����ɼ���Դ��Ĭ�ϲ���ʾ
	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)
	SetGrowPointObjID(sceneId, growPointType, x, y, ItemBoxId)
	
	--ʹ��ǰ�����ʼ�����������
	if x303104_g_curExistAllGrowPonitTbl[sceneId] == nil then
		x303104_g_curExistAllGrowPonitTbl[sceneId] = {}
	end
	
	x303104_g_curExistAllGrowPonitTbl[sceneId][ItemBoxId] = growPointType
end

-------------------------------------------------------------------------
--�ɼ����
-------------------------------------------------------------------------
function x303104_OnOpen(sceneId, selfId, targetId)

	--��¼����������OnInit֮�󽫿ռ������ܽ��У�����������
	if x303104_g_curSceneInit[sceneId] == nil then
		return 1
	end
	
	if getn(x303104_g_GrowPonitTypeAry) == 0 then
		return 1
	end

	if x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] == nil then
		return 1
	end
	
	--��������ɼ��㣬���ᴥ�� OnRecycle���ӵ�ͼ��ɾ�� obj������������
	RecycleGrowPointByType(sceneId, x303104_g_curExistAllGrowPonitTbl[sceneId][targetId], -1)

	--�����λ���������
	local nPosNum = getn(x303104_g_curGrowPonitInfoTbl[sceneId])

	for i = 1, nPosNum do
		if x303104_g_curGrowPonitInfoTbl[sceneId][i].type == x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] then
			x303104_g_curGrowPonitInfoTbl[sceneId][i].type = 0
			x303104_g_curGrowPonitInfoTbl[sceneId][i].exist = 0
			break
		end
	end
	
	--��� buf
	for i, item in x303104_g_GrowPonitTypeAry do
		if item.type == x303104_g_curExistAllGrowPonitTbl[sceneId][targetId] then
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, item.bufid, 0)
			if x303104_g_GrowPonitBufName[item.bufid] ~= nil then
				Msg2Player(sceneId, selfId, format("���ɼ����ˡ�%s��Ч��", x303104_g_GrowPonitBufName[item.bufid]), 8, 2)
				Msg2Player(sceneId, selfId, format("���ɼ����ˡ�%s��Ч��", x303104_g_GrowPonitBufName[item.bufid]), 8, 3)	
				WriteLog(1, format("MP2BL:x303104_OnOpen 1 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), item.bufid))			
			end
			break
		end
	end
	
	--���� 1 ʹ�������ܽ��У��޽���ʱ OnRecycle �ص�
    return 1
end

-------------------------------------------------------------------------
--�ɼ������
-------------------------------------------------------------------------
function x303104_OnRecycle(sceneId, selfId, targetId)
	return 1
end

-------------------------------------------------------------------------
--�ɼ������
-------------------------------------------------------------------------
function x303104_OnProcOver(sceneId,selfId,targetId)
end

-------------------------------------------------------------------------
--�ɼ�����
-------------------------------------------------------------------------
function x303104_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end

-------------------------------------------------------------------------
--�ɼ�����
-------------------------------------------------------------------------
function x303104_OnOpenItemBox(sceneId, selfId, targetId, gpType, needItemID)
	return 0
end
