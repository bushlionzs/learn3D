--MisDescBegin

x300330_g_ScriptId 					= 	300330                  --�ű�ID
x300330_g_MissionId 				= 	8050                    --����ID

x300330_g_MissionKind 				= 	1                       --��������
x300330_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������

x300330_g_MissionName				= 	"�����ˡ��ر�ͼ������"                                        --��������(512)
x300330_g_MissionTarget				= 	"  ȥ#aB#h00CCFF{goto_%d,%d,%d}%s(%d,%d)#aE��ʹ�������ھ򱦲�"      --����Ŀ��
x300330_g_MissionInfo				= 	"ͨ���Ķ����������ر�ͼ���������˱��ص����ڡ�ȥ#aB#h00CCFF{goto_%d,%d,%d}%s(%d,%d)#aE��ȥ�ھ򱦲ذɡ�\n\tע�⣺������#G�������#W״̬ʱ���п��ܻ��ڵ���������������ֻ���ڵ�����������"            --������Ϣ
x300330_g_ContinueInfo				= 	""  --���������Ϣ
x300330_g_MissionCompleted			= 	"\t�������Ѿ��õ�@item_12030107,�������˽�ر�ͼ�������˰ɣ������Ҹ���һ����������˵������������׷����ȥ�п��ܵõ������ı��أ������Ļ����п�����Ϣ�ڵ������֣���������������������������������ʱ��õ������������Щ�������п��ܵõ�@item_12030108��"  --���������Ϣ
x300330_g_MissionHelp				=	"ȥ�ӻ����˴���һ��������Ȼ��ȥ�������ڵ�ʹ��"          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300330_g_strMissionAbandon         = "�����������񣺡����ˡ��ر�ͼ������"

--Ŀ��
x300330_g_ExtTarget					=	{ {type=20,n=1,target="ȥ�ӻ����˴���һ��������Ȼ��ȥ�������ڵ�ʹ�á�"} }


--����
x300330_g_ExpBonus					= 	0                    	--���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300330_g_BonusItem					=	{}	--��������Ʒ

x300330_g_BonusMoney1               = 	0  --������������
x300330_g_BonusMoney2               =   0  --�������ǰ�����
x300330_g_BonusMoney3               =   0  --�������󶨽��
x300330_g_BonusMoney4               =   0  --��������͢����
x300330_g_BonusMoney5               =   0  --��������������
x300330_g_BonusMoney6               =   0  --����������

x300330_g_BonusChoiceItem           =   {}


--MisDescEnd

--����Ŀ��˳��
x300330_MP_TARGET1					= 1
x300330_MP_TARGET2					= 2
x300330_MP_TARGET3					= 3
x300330_MP_TARGET4					= 4 -- �ھ�Ŀ�곡��
x300330_MP_ISCOMPLETE				= 7	--������� 0δ��ɣ� 1���

x300330_PREVIOUS_QUESTID			= -1		--ǰһ������ID
x300330_NEXT_QUESTID				= 7552		--��һ������ID
x300330_NEXT_QUESTSCRIPTID			= 300754	--��һ������ID
x300330_QUEST_HUANSHU				= 0			--��ǰ����Ļ���

-- �ڱ����б�ʹ�òر�ͼʱ���������ȡһ��
x300330_g_MissionTargetTable0        = {
                                        { mapId = 0, mapName = "����", posX = 162, posZ = 238 }, 
                                        { mapId = 0, mapName = "����", posX = 161, posZ = 221 }, 
                                        { mapId = 0, mapName = "����", posX = 163, posZ = 224 },  
                                        { mapId = 0, mapName = "����", posX = 92, posZ = 238 }, 
                                        { mapId = 0, mapName = "����", posX = 96, posZ = 223 }, 
                                        { mapId = 0, mapName = "����", posX = 159, posZ = 193 }, 
                                        { mapId = 0, mapName = "����", posX = 209, posZ = 166 }, 
                                        { mapId = 0, mapName = "����", posX = 208, posZ = 199 }, 
                                        { mapId = 0, mapName = "����", posX = 170, posZ = 114 }, 
                                        { mapId = 0, mapName = "����", posX = 167, posZ = 162 }, 
                                        { mapId = 0, mapName = "����", posX = 170, posZ = 112 }, 
                                        { mapId = 0, mapName = "����", posX = 167, posZ = 198 }, 
                                        { mapId = 0, mapName = "����", posX = 210, posZ = 72 }, 
                                        { mapId = 0, mapName = "����", posX = 202, posZ = 77 }, 
                                        { mapId = 0, mapName = "����", posX = 210, posZ = 61 }, 
                                        { mapId = 0, mapName = "����", posX = 171, posZ = 69  }, 
                                        { mapId = 0, mapName = "����", posX = 171, posZ = 78 }, 
                                        { mapId = 0, mapName = "����", posX = 87 , posZ = 76 }, 
                                        { mapId = 0, mapName = "����", posX = 91, posZ = 59 }, 
                                        { mapId = 0, mapName = "����", posX = 77, posZ = 71 }, 
                                        { mapId = 0, mapName = "����", posX = 8, posZ = 149 }, 
                                        { mapId = 0, mapName = "����", posX = 31, posZ = 145 }, 
                                        { mapId = 0, mapName = "����", posX = 57 , posZ = 90 }, 
                                        { mapId = 0, mapName = "����", posX = 249 , posZ = 87 }, 
                                        { mapId = 0, mapName = "����", posX = 224 , posZ = 146 }, 
                                        { mapId = 0, mapName = "����", posX = 224 , posZ = 137 }, 
                                        { mapId = 0, mapName = "����", posX = 250 , posZ = 149 }, 
                                        { mapId = 0, mapName = "����", posX = 208 , posZ = 191 }, 
                                        { mapId = 0, mapName = "����", posX = 168 , posZ = 198 }, 
                                        { mapId = 0, mapName = "����", posX = 90 , posZ = 194 }, 
                                        { mapId = 0, mapName = "����", posX = 80 , posZ = 203 }, 
                                        { mapId = 0, mapName = "����", posX = 50 , posZ = 167 }, 
                                        { mapId = 0, mapName = "����", posX = 20 , posZ = 150 }, 
                                        { mapId = 0, mapName = "����", posX = 30 , posZ = 99 }, 
                                        { mapId = 0, mapName = "����", posX = 31 , posZ = 89 }, 
                                        { mapId = 0, mapName = "����", posX = 8 , posZ = 131 }, 
                                        { mapId = 0, mapName = "����", posX = 31 , posZ = 137 }, 
                                        { mapId = 0, mapName = "����", posX = 6 , posZ = 104 }, 
                                        { mapId = 0, mapName = "����", posX = 113 , posZ = 92 }, 
                                        { mapId = 0, mapName = "����", posX = 141 , posZ = 92 }, 
                                        { mapId = 0, mapName = "����", posX = 163 , posZ = 91 }, 
                                        { mapId = 0, mapName = "����", posX = 178 , posZ = 56 }, 
                                        { mapId = 0, mapName = "����", posX = 192 , posZ = 54 }, 
                                        { mapId = 0, mapName = "����", posX = 206 , posZ = 46 }, 
                                        { mapId = 0, mapName = "����", posX = 207 , posZ = 41 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 47 }, 
                                        { mapId = 0, mapName = "����", posX = 205 , posZ = 24 }, 
                                        { mapId = 0, mapName = "����", posX = 197 , posZ = 23 }, 
                                        { mapId = 0, mapName = "����", posX = 206 , posZ = 27 }, 
                                        { mapId = 0, mapName = "����", posX = 203 , posZ = 32 }, 
                                        { mapId = 1, mapName = "����", posX = 25, posZ = 80 }, 
                                        { mapId = 1, mapName = "����", posX = 33, posZ = 60 }, 
                                        { mapId = 1, mapName = "����", posX = 37, posZ = 66 },  
                                        { mapId = 1, mapName = "����", posX = 70, posZ = 78 }, 
                                        { mapId = 1, mapName = "����", posX = 75, posZ = 76 }, 
                                        { mapId = 1, mapName = "����", posX = 21, posZ = 30 }, 
                                        { mapId = 1, mapName = "����", posX = 140, posZ = 23 }, 
                                        { mapId = 1, mapName = "����", posX = 163, posZ = 16 }, 
                                        { mapId = 1, mapName = "����", posX = 171, posZ = 24 }, 
                                        { mapId = 1, mapName = "����", posX = 211, posZ = 47 }, 
                                        { mapId = 1, mapName = "����", posX = 212, posZ = 71 }, 
                                        { mapId = 1, mapName = "����", posX = 199, posZ = 95 }, 
                                        { mapId = 1, mapName = "����", posX = 160, posZ = 113 }, 
                                        { mapId = 1, mapName = "����", posX = 188, posZ = 92 }, 
                                        { mapId = 1, mapName = "����", posX = 163, posZ = 78 }, 
                                        { mapId = 1, mapName = "����", posX = 170, posZ = 70  }, 
                                        { mapId = 1, mapName = "����", posX = 166, posZ = 88 }, 
                                        { mapId = 1, mapName = "����", posX = 169 , posZ = 101 }, 
                                        { mapId = 1, mapName = "����", posX = 177, posZ = 157 }, 
                                        { mapId = 1, mapName = "����", posX = 178, posZ = 143 }, 
                                        { mapId = 1, mapName = "����", posX = 216, posZ = 127 }, 
                                        { mapId = 1, mapName = "����", posX = 227, posZ = 136 }, 
                                        { mapId = 1, mapName = "����", posX = 222 , posZ = 149 }, 
                                        { mapId = 1, mapName = "����", posX = 211 , posZ = 144 }, 
                                        { mapId = 1, mapName = "����", posX = 186 , posZ = 164 }, 
                                        { mapId = 1, mapName = "����", posX = 204 , posZ = 214 }, 
                                        { mapId = 1, mapName = "����", posX = 217 , posZ = 204 }, 
                                        { mapId = 1, mapName = "����", posX = 223 , posZ = 233 }, 
                                        { mapId = 1, mapName = "����", posX = 218 , posZ = 222 }, 
                                        { mapId = 1, mapName = "����", posX = 130 , posZ = 220 }, 
                                        { mapId = 1, mapName = "����", posX = 98 , posZ = 218 }, 
                                        { mapId = 1, mapName = "����", posX = 56 , posZ = 228 }, 
                                        { mapId = 1, mapName = "����", posX = 44 , posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 39 , posZ = 217 }, 
                                        { mapId = 1, mapName = "����", posX = 51 , posZ = 189 }, 
                                        { mapId = 1, mapName = "����", posX = 62 , posZ = 188 }, 
                                        { mapId = 1, mapName = "����", posX = 86 , posZ = 168 }, 
                                        { mapId = 1, mapName = "����", posX = 90 , posZ = 90 }, 
                                        { mapId = 1, mapName = "����", posX = 75 , posZ = 90 }, 
                                        { mapId = 1, mapName = "����", posX = 45 , posZ = 58 }, 
                                        { mapId = 1, mapName = "����", posX = 38 , posZ = 46 }, 
                                        { mapId = 1, mapName = "����", posX = 100 , posZ = 40 }, 
                                        { mapId = 1, mapName = "����", posX = 121 , posZ = 27 }, 
                                        { mapId = 1, mapName = "����", posX = 143 , posZ = 25 }, 
                                        { mapId = 1, mapName = "����", posX = 149 , posZ = 29 }, 
                                        { mapId = 1, mapName = "����", posX = 162 , posZ = 19 }, 
                                        { mapId = 1, mapName = "����", posX = 238 , posZ = 36 }, 
                                        { mapId = 1, mapName = "����", posX = 221 , posZ = 47 }, 
                                        { mapId = 1, mapName = "����", posX = 189 , posZ = 55 }, 
                                        { mapId = 1, mapName = "����", posX = 175 , posZ = 74 },
                                        { mapId = 2, mapName = "��", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "��", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "��", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "��", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "��", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "��", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "��", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "��", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "��", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "��", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "��", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "��", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "��", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "��", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "��", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "��", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "������", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "������", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "������", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "������", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "������", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "������", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "������", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "������", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "������", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "������", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "������", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "������", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "������", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "������", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "������", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "������", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "����", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "����", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "����", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "����", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "����", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "����", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "����", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "����", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "����", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "����", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "����", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "����", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "����", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "����", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "����", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "����", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "����", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "����", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "����", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "����", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "�󶼶�", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "�󶼶�", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "����", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "����", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "����", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "����", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "����", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "����", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "����", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "����", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "����", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "����", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "����", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "����", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "����", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "����", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "����", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "����", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "����", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "����", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 107  },
                                                                                
}                                                                                        

x300330_g_MissionTargetTable1        = {
                                        { mapId = 0, mapName = "����", posX = 51, posZ = 83 }, 
                                        { mapId = 0, mapName = "����", posX = 50, posZ = 107 }, 
                                        { mapId = 0, mapName = "����", posX = 25, posZ = 92 },  
                                        { mapId = 0, mapName = "����", posX = 6, posZ = 105 }, 
                                        { mapId = 0, mapName = "����", posX = 7, posZ = 149 }, 
                                        { mapId = 0, mapName = "����", posX = 28, posZ = 142 }, 
                                        { mapId = 0, mapName = "����", posX = 31, posZ = 137 }, 
                                        { mapId = 0, mapName = "����", posX = 47, posZ = 141 }, 
                                        { mapId = 0, mapName = "����", posX = 87, posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 101, posZ = 165 }, 
                                        { mapId = 0, mapName = "����", posX = 101, posZ = 185 }, 
                                        { mapId = 0, mapName = "����", posX = 62, posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 51, posZ = 68 }, 
                                        { mapId = 0, mapName = "����", posX = 78, posZ = 71 }, 
                                        { mapId = 0, mapName = "����", posX = 100, posZ = 71 }, 
                                        { mapId = 0, mapName = "����", posX = 135, posZ = 75  }, 
                                        { mapId = 0, mapName = "����", posX = 168, posZ = 70 }, 
                                        { mapId = 0, mapName = "����", posX = 196 , posZ = 74 }, 
                                        { mapId = 0, mapName = "����", posX = 171, posZ = 44 }, 
                                        { mapId = 0, mapName = "����", posX = 203, posZ = 26 }, 
                                        { mapId = 0, mapName = "����", posX = 202, posZ = 32 }, 
                                        { mapId = 0, mapName = "����", posX = 228, posZ = 105 }, 
                                        { mapId = 0, mapName = "����", posX = 235 , posZ = 87 }, 
                                        { mapId = 0, mapName = "����", posX = 247 , posZ = 103 }, 
                                        { mapId = 0, mapName = "����", posX = 248 , posZ = 134 }, 
                                        { mapId = 0, mapName = "����", posX = 247 , posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 243 , posZ = 160 }, 
                                        { mapId = 0, mapName = "����", posX = 225 , posZ = 161 }, 
                                        { mapId = 0, mapName = "����", posX = 227 , posZ = 145 }, 
                                        { mapId = 0, mapName = "����", posX = 227 , posZ = 137 }, 
                                        { mapId = 0, mapName = "����", posX = 203 , posZ = 136 }, 
                                        { mapId = 0, mapName = "����", posX = 153 , posZ = 191 }, 
                                        { mapId = 0, mapName = "����", posX = 146 , posZ = 208 }, 
                                        { mapId = 0, mapName = "����", posX = 162 , posZ = 226 }, 
                                        { mapId = 0, mapName = "����", posX = 162 , posZ = 239 }, 
                                        { mapId = 0, mapName = "����", posX = 144 , posZ = 241 }, 
                                        { mapId = 0, mapName = "����", posX = 111 , posZ = 238 }, 
                                        { mapId = 0, mapName = "����", posX = 96 , posZ = 235 }, 
                                        { mapId = 0, mapName = "����", posX = 93 , posZ = 226 }, 
                                        { mapId = 0, mapName = "����", posX = 99 , posZ = 221 }, 
                                        { mapId = 0, mapName = "����", posX = 110 , posZ = 207 }, 
                                        { mapId = 0, mapName = "����", posX = 114 , posZ = 187 }, 
                                        { mapId = 0, mapName = "����", posX = 90 , posZ = 196 }, 
                                        { mapId = 0, mapName = "����", posX = 82 , posZ = 202 }, 
                                        { mapId = 0, mapName = "����", posX = 77 , posZ = 198 }, 
                                        { mapId = 0, mapName = "����", posX = 51 , posZ = 185 }, 
                                        { mapId = 0, mapName = "����", posX = 50 , posZ = 173 }, 
                                        { mapId = 0, mapName = "����", posX = 51 , posZ = 98 }, 
                                        { mapId = 0, mapName = "����", posX = 14 , posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 29 , posZ = 137 }, 
                                        { mapId = 1, mapName = "����", posX = 25, posZ = 43 }, 
                                        { mapId = 1, mapName = "����", posX = 24, posZ = 35 }, 
                                        { mapId = 1, mapName = "����", posX = 51, posZ = 31 },  
                                        { mapId = 1, mapName = "����", posX = 70, posZ = 30 }, 
                                        { mapId = 1, mapName = "����", posX = 81, posZ = 45 }, 
                                        { mapId = 1, mapName = "����", posX = 111, posZ = 28 }, 
                                        { mapId = 1, mapName = "����", posX = 131, posZ = 23 }, 
                                        { mapId = 1, mapName = "����", posX = 137, posZ = 24 }, 
                                        { mapId = 1, mapName = "����", posX = 172, posZ = 38 }, 
                                        { mapId = 1, mapName = "����", posX = 183, posZ = 30 }, 
                                        { mapId = 1, mapName = "����", posX = 231, posZ = 32 }, 
                                        { mapId = 1, mapName = "����", posX = 181, posZ = 72 }, 
                                        { mapId = 1, mapName = "����", posX = 228, posZ = 60 }, 
                                        { mapId = 1, mapName = "����", posX = 233, posZ = 70 }, 
                                        { mapId = 1, mapName = "����", posX = 197, posZ = 157 }, 
                                        { mapId = 1, mapName = "����", posX = 195, posZ = 139 }, 
                                        { mapId = 1, mapName = "����", posX = 183, posZ = 131 }, 
                                        { mapId = 1, mapName = "����", posX = 168 , posZ = 153 }, 
                                        { mapId = 1, mapName = "����", posX = 150, posZ = 156 }, 
                                        { mapId = 1, mapName = "����", posX = 194, posZ = 172 }, 
                                        { mapId = 1, mapName = "����", posX = 200, posZ = 173 }, 
                                        { mapId = 1, mapName = "����", posX = 192, posZ = 176 }, 
                                        { mapId = 1, mapName = "����", posX = 204 , posZ = 186 }, 
                                        { mapId = 1, mapName = "����", posX = 228 , posZ = 202 }, 
                                        { mapId = 1, mapName = "����", posX = 198 , posZ = 203 }, 
                                        { mapId = 1, mapName = "����", posX = 168 , posZ = 195 }, 
                                        { mapId = 1, mapName = "����", posX = 169 , posZ = 216 }, 
                                        { mapId = 1, mapName = "����", posX = 173 , posZ = 225 }, 
                                        { mapId = 1, mapName = "����", posX = 156 , posZ = 220 }, 
                                        { mapId = 1, mapName = "����", posX = 126 , posZ = 223 }, 
                                        { mapId = 1, mapName = "����", posX = 109 , posZ = 231 }, 
                                        { mapId = 1, mapName = "����", posX = 91 , posZ = 225 }, 
                                        { mapId = 1, mapName = "����", posX = 53 , posZ = 224 }, 
                                        { mapId = 1, mapName = "����", posX = 45 , posZ = 225 }, 
                                        { mapId = 1, mapName = "����", posX = 26 , posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 30 , posZ = 202 }, 
                                        { mapId = 1, mapName = "����", posX = 30 , posZ = 181 }, 
                                        { mapId = 1, mapName = "����", posX = 44 , posZ = 166 }, 
                                        { mapId = 1, mapName = "����", posX = 24 , posZ = 154 }, 
                                        { mapId = 1, mapName = "����", posX = 31 , posZ = 152 }, 
                                        { mapId = 1, mapName = "����", posX = 60 , posZ = 137 }, 
                                        { mapId = 1, mapName = "����", posX = 88 , posZ = 135 }, 
                                        { mapId = 1, mapName = "����", posX = 77 , posZ = 162 }, 
                                        { mapId = 1, mapName = "����", posX = 105 , posZ = 145 }, 
                                        { mapId = 1, mapName = "����", posX = 104 , posZ = 106 }, 
                                        { mapId = 1, mapName = "����", posX = 79 , posZ = 37 }, 
                                        { mapId = 1, mapName = "����", posX = 51 , posZ = 31 }, 
                                        { mapId = 1, mapName = "����", posX = 48 , posZ = 104 }, 
                                        { mapId = 1, mapName = "����", posX = 31 , posZ = 86 }, 
                                        { mapId = 1, mapName = "����", posX = 38 , posZ = 75 },
                                        { mapId = 2, mapName = "��", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "��", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "��", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "��", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "��", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "��", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "��", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "��", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "��", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "��", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "��", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "��", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "��", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "��", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "��", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "��", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "������", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "������", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "������", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "������", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "������", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "������", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "������", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "������", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "������", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "������", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "������", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "������", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "������", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "������", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "������", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "������", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "����", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "����", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "����", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "����", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "����", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "����", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "����", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "����", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "����", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "����", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "����", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "����", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "����", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "����", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "����", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "����", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "����", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "����", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "����", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "����", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "�󶼶�", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "�󶼶�", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "����", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "����", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "����", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "����", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "����", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "����", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "����", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "����", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "����", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "����", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "����", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "����", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "����", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "����", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "����", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "����", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "����", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "����", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 107  },
}

x300330_g_MissionTargetTable2        = {
                                        { mapId = 0, mapName = "����", posX = 89, posZ = 109 }, 
                                        { mapId = 0, mapName = "����", posX = 98, posZ = 99 }, 
                                        { mapId = 0, mapName = "����", posX = 76, posZ = 105 },  
                                        { mapId = 0, mapName = "����", posX = 77, posZ = 93 }, 
                                        { mapId = 0, mapName = "����", posX = 87, posZ = 95 }, 
                                        { mapId = 0, mapName = "����", posX = 92, posZ = 84 }, 
                                        { mapId = 0, mapName = "����", posX = 92, posZ = 68 }, 
                                        { mapId = 0, mapName = "����", posX = 88, posZ = 58 }, 
                                        { mapId = 0, mapName = "����", posX = 82, posZ = 54 }, 
                                        { mapId = 0, mapName = "����", posX = 49, posZ = 57 }, 
                                        { mapId = 0, mapName = "����", posX = 53, posZ = 93 }, 
                                        { mapId = 0, mapName = "����", posX = 49, posZ = 91 }, 
                                        { mapId = 0, mapName = "����", posX = 59, posZ = 93 }, 
                                        { mapId = 0, mapName = "����", posX = 49, posZ = 120 }, 
                                        { mapId = 0, mapName = "����", posX = 50, posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 85, posZ = 156  }, 
                                        { mapId = 0, mapName = "����", posX = 111, posZ = 163 }, 
                                        { mapId = 0, mapName = "����", posX = 164 , posZ = 186 }, 
                                        { mapId = 0, mapName = "����", posX = 93, posZ = 204 }, 
                                        { mapId = 0, mapName = "����", posX = 150, posZ = 234 }, 
                                        { mapId = 0, mapName = "����", posX = 101, posZ = 229 }, 
                                        { mapId = 0, mapName = "����", posX = 96, posZ = 215 }, 
                                        { mapId = 0, mapName = "����", posX = 76 , posZ = 226 }, 
                                        { mapId = 0, mapName = "����", posX = 52 , posZ = 223 }, 
                                        { mapId = 0, mapName = "����", posX = 49 , posZ = 220 }, 
                                        { mapId = 0, mapName = "����", posX = 56 , posZ = 202 }, 
                                        { mapId = 0, mapName = "����", posX = 67 , posZ = 201 }, 
                                        { mapId = 0, mapName = "����", posX = 92 , posZ = 206 }, 
                                        { mapId = 0, mapName = "����", posX = 90 , posZ = 190 }, 
                                        { mapId = 0, mapName = "����", posX = 112 , posZ = 186 }, 
                                        { mapId = 0, mapName = "����", posX = 156 , posZ = 167 }, 
                                        { mapId = 0, mapName = "����", posX = 164 , posZ = 186 }, 
                                        { mapId = 0, mapName = "����", posX = 171 , posZ = 170 }, 
                                        { mapId = 0, mapName = "����", posX = 203 , posZ = 194 }, 
                                        { mapId = 0, mapName = "����", posX = 202 , posZ = 210 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 233 }, 
                                        { mapId = 0, mapName = "����", posX = 183 , posZ = 240 }, 
                                        { mapId = 0, mapName = "����", posX = 179 , posZ = 229 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 165 }, 
                                        { mapId = 0, mapName = "����", posX = 205 , posZ = 148 }, 
                                        { mapId = 0, mapName = "����", posX = 210 , posZ = 117 }, 
                                        { mapId = 0, mapName = "����", posX = 226 , posZ = 119 }, 
                                        { mapId = 0, mapName = "����", posX = 226 , posZ = 110 }, 
                                        { mapId = 0, mapName = "����", posX = 240 , posZ = 107 }, 
                                        { mapId = 0, mapName = "����", posX = 246 , posZ = 109 }, 
                                        { mapId = 0, mapName = "����", posX = 225 , posZ = 167 }, 
                                        { mapId = 0, mapName = "����", posX = 226 , posZ = 155 }, 
                                        { mapId = 0, mapName = "����", posX = 205 , posZ = 146 }, 
                                        { mapId = 0, mapName = "����", posX = 165 , posZ = 108 }, 
                                        { mapId = 0, mapName = "����", posX = 153 , posZ = 92 }, 
                                        { mapId = 1, mapName = "����", posX = 46, posZ = 59 }, 
                                        { mapId = 1, mapName = "����", posX = 56, posZ = 57 }, 
                                        { mapId = 1, mapName = "����", posX = 50, posZ = 76 },  
                                        { mapId = 1, mapName = "����", posX = 81, posZ = 76 }, 
                                        { mapId = 1, mapName = "����", posX = 102, posZ = 88 }, 
                                        { mapId = 1, mapName = "����", posX = 80, posZ = 87 }, 
                                        { mapId = 1, mapName = "����", posX = 35, posZ = 95 }, 
                                        { mapId = 1, mapName = "����", posX = 33, posZ = 142 }, 
                                        { mapId = 1, mapName = "����", posX = 40, posZ = 169 }, 
                                        { mapId = 1, mapName = "����", posX = 40, posZ = 175 }, 
                                        { mapId = 1, mapName = "����", posX = 46, posZ = 189 }, 
                                        { mapId = 1, mapName = "����", posX = 81, posZ = 220 }, 
                                        { mapId = 1, mapName = "����", posX = 111, posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 130, posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 153, posZ = 213 }, 
                                        { mapId = 1, mapName = "����", posX = 166, posZ = 230  }, 
                                        { mapId = 1, mapName = "����", posX = 171, posZ = 231 }, 
                                        { mapId = 1, mapName = "����", posX = 184, posZ = 221 }, 
                                        { mapId = 1, mapName = "����", posX = 199, posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 216, posZ = 210 }, 
                                        { mapId = 1, mapName = "����", posX = 218, posZ = 193 }, 
                                        { mapId = 1, mapName = "����", posX = 210, posZ = 198 }, 
                                        { mapId = 1, mapName = "����", posX = 210 , posZ = 187 }, 
                                        { mapId = 1, mapName = "����", posX = 209 , posZ = 182 }, 
                                        { mapId = 1, mapName = "����", posX = 210 , posZ = 155 }, 
                                        { mapId = 1, mapName = "����", posX = 212 , posZ = 143 }, 
                                        { mapId = 1, mapName = "����", posX = 204 , posZ = 134 }, 
                                        { mapId = 1, mapName = "����", posX = 199 , posZ = 135 }, 
                                        { mapId = 1, mapName = "����", posX = 171 , posZ = 170 }, 
                                        { mapId = 1, mapName = "����", posX = 158 , posZ = 172 }, 
                                        { mapId = 1, mapName = "����", posX = 155 , posZ = 155 }, 
                                        { mapId = 1, mapName = "����", posX = 169 , posZ = 116 }, 
                                        { mapId = 1, mapName = "����", posX = 203 , posZ = 109 }, 
                                        { mapId = 1, mapName = "����", posX = 208 , posZ = 95 }, 
                                        { mapId = 1, mapName = "����", posX = 203 , posZ = 93 }, 
                                        { mapId = 1, mapName = "����", posX = 149 , posZ = 77 }, 
                                        { mapId = 1, mapName = "����", posX = 157 , posZ = 88 }, 
                                        { mapId = 1, mapName = "����", posX = 164 , posZ = 230 }, 
                                        { mapId = 1, mapName = "����", posX = 155 , posZ = 209 }, 
                                        { mapId = 1, mapName = "����", posX = 132 , posZ = 227 }, 
                                        { mapId = 1, mapName = "����", posX = 118 , posZ = 226 }, 
                                        { mapId = 1, mapName = "����", posX = 50 , posZ = 184 }, 
                                        { mapId = 1, mapName = "����", posX = 45 , posZ = 165 }, 
                                        { mapId = 1, mapName = "����", posX = 36 , posZ = 96 }, 
                                        { mapId = 1, mapName = "����", posX = 75 , posZ = 93 }, 
                                        { mapId = 1, mapName = "����", posX = 77 , posZ = 110 }, 
                                        { mapId = 1, mapName = "����", posX = 89 , posZ = 88 }, 
                                        { mapId = 1, mapName = "����", posX = 102 , posZ = 88 }, 
                                        { mapId = 1, mapName = "����", posX = 88 , posZ = 76 }, 
                                        { mapId = 1, mapName = "����", posX = 71 , posZ = 63 },
                                        { mapId = 2, mapName = "��", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "��", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "��", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "��", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "��", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "��", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "��", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "��", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "��", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "��", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "��", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "��", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "��", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "��", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "��", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "��", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "������", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "������", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "������", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "������", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "������", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "������", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "������", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "������", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "������", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "������", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "������", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "������", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "������", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "������", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "������", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "������", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "����", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "����", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "����", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "����", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "����", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "����", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "����", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "����", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "����", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "����", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "����", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "����", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "����", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "����", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "����", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "����", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "����", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "����", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "����", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "����", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "�󶼶�", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "�󶼶�", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "����", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "����", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "����", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "����", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "����", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "����", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "����", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "����", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "����", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "����", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "����", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "����", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "����", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "����", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "����", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "����", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "����", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "����", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 107  },
}

x300330_g_MissionTargetTable3        = {
                                        { mapId = 0, mapName = "����", posX = 93, posZ = 103 }, 
                                        { mapId = 0, mapName = "����", posX = 78, posZ = 123 }, 
                                        { mapId = 0, mapName = "����", posX = 46, posZ = 103 },  
                                        { mapId = 0, mapName = "����", posX = 78, posZ = 94 }, 
                                        { mapId = 0, mapName = "����", posX = 57, posZ = 94 }, 
                                        { mapId = 0, mapName = "����", posX = 88, posZ = 93 }, 
                                        { mapId = 0, mapName = "����", posX = 92, posZ = 82 }, 
                                        { mapId = 0, mapName = "����", posX = 102, posZ = 86 }, 
                                        { mapId = 0, mapName = "����", posX = 85, posZ = 163 }, 
                                        { mapId = 0, mapName = "����", posX = 96, posZ = 162 }, 
                                        { mapId = 0, mapName = "����", posX = 109, posZ = 163 }, 
                                        { mapId = 0, mapName = "����", posX = 108, posZ = 180 }, 
                                        { mapId = 0, mapName = "����", posX = 104, posZ = 188 }, 
                                        { mapId = 0, mapName = "����", posX = 101, posZ = 218 }, 
                                        { mapId = 0, mapName = "����", posX = 99, posZ = 227 }, 
                                        { mapId = 0, mapName = "����", posX = 106, posZ = 233  }, 
                                        { mapId = 0, mapName = "����", posX = 113, posZ = 240 }, 
                                        { mapId = 0, mapName = "����", posX = 143 , posZ = 239 }, 
                                        { mapId = 0, mapName = "����", posX = 149, posZ = 232 }, 
                                        { mapId = 0, mapName = "����", posX = 155, posZ = 224 }, 
                                        { mapId = 0, mapName = "����", posX = 155, posZ = 218 }, 
                                        { mapId = 0, mapName = "����", posX = 104, posZ = 189 }, 
                                        { mapId = 0, mapName = "����", posX = 144 , posZ = 177 }, 
                                        { mapId = 0, mapName = "����", posX = 183 , posZ = 194 }, 
                                        { mapId = 0, mapName = "����", posX = 182 , posZ = 188 }, 
                                        { mapId = 0, mapName = "����", posX = 174 , posZ = 209 }, 
                                        { mapId = 0, mapName = "����", posX = 170 , posZ = 215 }, 
                                        { mapId = 0, mapName = "����", posX = 183 , posZ = 233 }, 
                                        { mapId = 0, mapName = "����", posX = 176 , posZ = 228 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 229 }, 
                                        { mapId = 0, mapName = "����", posX = 202 , posZ = 224 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 211 }, 
                                        { mapId = 0, mapName = "����", posX = 194 , posZ = 195 }, 
                                        { mapId = 0, mapName = "����", posX = 200 , posZ = 193 }, 
                                        { mapId = 0, mapName = "����", posX = 192 , posZ = 181 }, 
                                        { mapId = 0, mapName = "����", posX = 190 , posZ = 176 }, 
                                        { mapId = 0, mapName = "����", posX = 198 , posZ = 164 }, 
                                        { mapId = 0, mapName = "����", posX = 211 , posZ = 150 }, 
                                        { mapId = 0, mapName = "����", posX = 211 , posZ = 145 }, 
                                        { mapId = 0, mapName = "����", posX = 228 , posZ = 154 }, 
                                        { mapId = 0, mapName = "����", posX = 225 , posZ = 166 }, 
                                        { mapId = 0, mapName = "����", posX = 250 , posZ = 149 }, 
                                        { mapId = 0, mapName = "����", posX = 244 , posZ = 166 }, 
                                        { mapId = 0, mapName = "����", posX = 250 , posZ = 161 }, 
                                        { mapId = 0, mapName = "����", posX = 248 , posZ = 108 }, 
                                        { mapId = 0, mapName = "����", posX = 226 , posZ = 110 }, 
                                        { mapId = 0, mapName = "����", posX = 226 , posZ = 119 }, 
                                        { mapId = 0, mapName = "����", posX = 211 , posZ = 128 }, 
                                        { mapId = 0, mapName = "����", posX = 211 , posZ = 120 }, 
                                        { mapId = 0, mapName = "����", posX = 162 , posZ = 71 }, 
                                        { mapId = 1, mapName = "����", posX = 80, posZ = 26 }, 
                                        { mapId = 1, mapName = "����", posX = 100, posZ = 31 }, 
                                        { mapId = 1, mapName = "����", posX = 104, posZ = 24 },  
                                        { mapId = 1, mapName = "����", posX = 111, posZ = 27 }, 
                                        { mapId = 1, mapName = "����", posX = 117, posZ = 28 }, 
                                        { mapId = 1, mapName = "����", posX = 173, posZ = 36 }, 
                                        { mapId = 1, mapName = "����", posX = 179, posZ = 42 }, 
                                        { mapId = 1, mapName = "����", posX = 202, posZ = 47 }, 
                                        { mapId = 1, mapName = "����", posX = 204, posZ = 23 }, 
                                        { mapId = 1, mapName = "����", posX = 212, posZ = 23 }, 
                                        { mapId = 1, mapName = "����", posX = 219, posZ = 49 }, 
                                        { mapId = 1, mapName = "����", posX = 216, posZ = 60 }, 
                                        { mapId = 1, mapName = "����", posX = 210, posZ = 57 }, 
                                        { mapId = 1, mapName = "����", posX = 198, posZ = 57 }, 
                                        { mapId = 1, mapName = "����", posX = 217, posZ = 74 }, 
                                        { mapId = 1, mapName = "����", posX = 208, posZ = 75  }, 
                                        { mapId = 1, mapName = "����", posX = 190, posZ = 76 }, 
                                        { mapId = 1, mapName = "����", posX = 184 , posZ = 76 }, 
                                        { mapId = 1, mapName = "����", posX = 157, posZ = 73 }, 
                                        { mapId = 1, mapName = "����", posX = 176, posZ = 97 }, 
                                        { mapId = 1, mapName = "����", posX = 212, posZ = 87 }, 
                                        { mapId = 1, mapName = "����", posX = 228, posZ = 95 }, 
                                        { mapId = 1, mapName = "����", posX = 234 , posZ = 109 }, 
                                        { mapId = 1, mapName = "����", posX = 229 , posZ = 197 }, 
                                        { mapId = 1, mapName = "����", posX = 230 , posZ = 204 }, 
                                        { mapId = 1, mapName = "����", posX = 188 , posZ = 230 }, 
                                        { mapId = 1, mapName = "����", posX = 169 , posZ = 229 }, 
                                        { mapId = 1, mapName = "����", posX = 160 , posZ = 223 }, 
                                        { mapId = 1, mapName = "����", posX = 145 , posZ = 217 }, 
                                        { mapId = 1, mapName = "����", posX = 139 , posZ = 205 }, 
                                        { mapId = 1, mapName = "����", posX = 122 , posZ = 227 }, 
                                        { mapId = 1, mapName = "����", posX = 110 , posZ = 216 }, 
                                        { mapId = 1, mapName = "����", posX = 87 , posZ = 217 }, 
                                        { mapId = 1, mapName = "����", posX = 71 , posZ = 227 }, 
                                        { mapId = 1, mapName = "����", posX = 36 , posZ = 202 }, 
                                        { mapId = 1, mapName = "����", posX = 34 , posZ = 196 }, 
                                        { mapId = 1, mapName = "����", posX = 44 , posZ = 164 }, 
                                        { mapId = 1, mapName = "����", posX = 34 , posZ = 147 }, 
                                        { mapId = 1, mapName = "����", posX = 44 , posZ = 141 }, 
                                        { mapId = 1, mapName = "����", posX = 54 , posZ = 138 }, 
                                        { mapId = 1, mapName = "����", posX = 65 , posZ = 146 }, 
                                        { mapId = 1, mapName = "����", posX = 70 , posZ = 165 }, 
                                        { mapId = 1, mapName = "����", posX = 129 , posZ = 26 }, 
                                        { mapId = 1, mapName = "����", posX = 96 , posZ = 30 }, 
                                        { mapId = 1, mapName = "����", posX = 71 , posZ = 46 }, 
                                        { mapId = 1, mapName = "����", posX = 82 , posZ = 46 }, 
                                        { mapId = 1, mapName = "����", posX = 60 , posZ = 102 }, 
                                        { mapId = 1, mapName = "����", posX = 67 , posZ = 81 }, 
                                        { mapId = 1, mapName = "����", posX = 58 , posZ = 78 }, 
                                        { mapId = 1, mapName = "����", posX = 45 , posZ = 89 },
                                        { mapId = 2, mapName = "��", posX = 76, posZ = 22 }, 
                                        { mapId = 2, mapName = "��", posX = 55, posZ = 183 }, 
                                        { mapId = 2, mapName = "��", posX = 217, posZ = 217 }, 
                                        { mapId = 2, mapName = "��", posX = 173, posZ = 39 }, 
                                        { mapId = 2, mapName = "��", posX = 64, posZ = 219 }, 
                                        { mapId = 2, mapName = "��", posX = 226, posZ = 85  }, 
                                        { mapId = 2, mapName = "��", posX = 185, posZ = 224 }, 
                                        { mapId = 2, mapName = "��", posX = 182, posZ = 23 }, 
                                        { mapId = 2, mapName = "��", posX = 191, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 188, posZ = 85 }, 
                                        { mapId = 2, mapName = "��", posX = 26, posZ = 178 }, 
                                        { mapId = 2, mapName = "��", posX = 70, posZ = 48 }, 
                                        { mapId = 2, mapName = "��", posX = 28, posZ = 69 }, 
                                        { mapId = 2, mapName = "��", posX = 63, posZ = 110 }, 
                                        { mapId = 2, mapName = "��", posX = 25, posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 57 , posZ = 206 }, 
                                        { mapId = 2, mapName = "��", posX = 53 , posZ = 177  }, 
                                        { mapId = 2, mapName = "��", posX = 73 , posZ = 84  }, 
                                        { mapId = 2, mapName = "��", posX = 177, posZ = 25  }, 
                                        { mapId = 2, mapName = "��", posX = 224, posZ = 61  },                                         
                                        { mapId = 3, mapName = "������", posX = 141, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 106, posZ = 185  }, 
                                        { mapId = 3, mapName = "������", posX = 67,  posZ = 148  }, 
                                        { mapId = 3, mapName = "������", posX = 129, posZ = 65  }, 
                                        { mapId = 3, mapName = "������", posX = 119, posZ = 90  }, 
                                        { mapId = 3, mapName = "������", posX = 130,  posZ = 91 }, 
                                        { mapId = 3, mapName = "������", posX = 89, posZ = 135  }, 
                                        { mapId = 3, mapName = "������", posX = 121, posZ = 134  }, 
                                        { mapId = 3, mapName = "������", posX = 195, posZ = 79 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 102 }, 
                                        { mapId = 3, mapName = "������", posX = 111,  posZ = 124 },
                                        { mapId = 3, mapName = "������", posX = 89,  posZ = 156 },
                                        { mapId = 3, mapName = "������", posX = 92,  posZ = 166 },
                                        { mapId = 3, mapName = "������", posX = 110,  posZ = 148 },
                                        { mapId = 3, mapName = "������", posX = 103,  posZ = 162 },
                                        { mapId = 3, mapName = "������", posX = 87,  posZ = 168 },
                                        { mapId = 3, mapName = "������", posX = 33,  posZ = 102 },
                                        { mapId = 3, mapName = "������", posX = 43,  posZ = 119 },
                                        { mapId = 3, mapName = "������", posX = 62,  posZ = 140 },
                                        { mapId = 3, mapName = "������", posX = 64,  posZ = 176 },
                                       	{ mapId = 36, mapName = "����", posX = 24, posZ = 102 }, 
                                        { mapId = 36, mapName = "����", posX = 24, posZ = 101 }, 
                                        { mapId = 36, mapName = "����", posX = 32, posZ = 115 }, 
                                        { mapId = 36, mapName = "����", posX = 22, posZ = 108 }, 
                                        { mapId = 36, mapName = "����", posX = 20, posZ = 132 }, 
                                        { mapId = 36, mapName = "����", posX = 31, posZ = 157  }, 
                                        { mapId = 36, mapName = "����", posX = 59 , posZ = 158 }, 
                                        { mapId = 36, mapName = "����", posX = 72, posZ = 159 }, 
                                        { mapId = 36, mapName = "����", posX = 54, posZ = 140 }, 
                                        { mapId = 36, mapName = "����", posX = 100, posZ = 151  }, 
                                        { mapId = 36, mapName = "����", posX = 140, posZ = 165 }, 
                                        { mapId = 36, mapName = "����", posX = 158, posZ = 160 }, 
                                        { mapId = 36, mapName = "����", posX = 174, posZ = 168 }, 
                                        { mapId = 36, mapName = "����", posX = 209, posZ = 156 }, 
                                        { mapId = 36, mapName = "����", posX = 234, posZ = 161 }, 
                                        { mapId = 36, mapName = "����", posX = 238 , posZ = 213 }, 
                                        { mapId = 36, mapName = "����", posX = 158 , posZ = 235  }, 
                                        { mapId = 36, mapName = "����", posX = 202 , posZ = 225  }, 
                                        { mapId = 36, mapName = "����", posX = 150, posZ = 235  },       
                                        { mapId = 36, mapName = "����", posX = 121, posZ = 230  },                                                                                
                                        { mapId = 37, mapName = "�󶼶�", posX = 64, posZ = 49  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 86, posZ = 118  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 87, posZ = 168  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 120, posZ = 158  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 161, posZ = 198  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 139, posZ = 240 },
                                        { mapId = 37, mapName = "�󶼶�", posX = 116, posZ = 241  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 106, posZ = 212  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 90, posZ = 210  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 92, posZ = 244  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 108, posZ = 242  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 104, posZ = 231  }, 
                                        { mapId = 37, mapName = "�󶼶�", posX = 155, posZ = 165  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 215, posZ = 224  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 221, posZ = 124  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 190, posZ = 81  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 169, posZ = 135  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 149, posZ = 95  },
                                        { mapId = 37, mapName = "�󶼶�", posX = 130, posZ = 90  },       
                                        { mapId = 37, mapName = "�󶼶�", posX = 121, posZ = 158  },                                        
                                        { mapId = 38, mapName = "����", posX = 137, posZ = 86  },       
                                        { mapId = 38, mapName = "����", posX = 135, posZ = 97  }, 
                                        { mapId = 38, mapName = "����", posX = 133, posZ = 108  },       
                                        { mapId = 38, mapName = "����", posX = 166, posZ = 111  },
                                        { mapId = 38, mapName = "����", posX = 182, posZ = 130  },       
                                        { mapId = 38, mapName = "����", posX = 234, posZ = 103  },
                                        { mapId = 38, mapName = "����", posX = 213, posZ = 179  },       
                                        { mapId = 38, mapName = "����", posX = 185, posZ = 167  },
                                        { mapId = 38, mapName = "����", posX = 147, posZ = 195  },       
                                        { mapId = 38, mapName = "����", posX = 160, posZ = 223  },
                                        { mapId = 38, mapName = "����", posX = 131, posZ = 222  },       
                                        { mapId = 38, mapName = "����", posX = 72, posZ = 161  }, 
                                        { mapId = 38, mapName = "����", posX = 33, posZ = 192  },       
                                        { mapId = 38, mapName = "����", posX = 89, posZ = 232  },
                                        { mapId = 38, mapName = "����", posX = 67, posZ = 135  },       
                                        { mapId = 38, mapName = "����", posX = 43, posZ = 86  },
                                        { mapId = 38, mapName = "����", posX = 87, posZ = 37  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 41  },
                                        { mapId = 38, mapName = "����", posX = 161, posZ = 74  },       
                                        { mapId = 38, mapName = "����", posX = 134, posZ = 107  },
}


x300330_g_MonsterTable              = {
                                        { level = 20, bossId = 3050, strName = "�޽���"    },
                                        { level = 25, bossId = 3051, strName = "��ͷ�"    },
                                        { level = 30, bossId = 3052, strName = "���ǽ�ʬ"  },
                                        { level = 35, bossId = 3053, strName = "��צ��"    },
                                        { level = 40, bossId = 3054, strName = "��β��"    },
                                        { level = 45, bossId = 3055, strName = "��βЫ"    },
                                        { level = 50, bossId = 3056, strName = "ŭ��ţ"    },
                                        { level = 55, bossId = 3057, strName = "������"    },
                                        { level = 60, bossId = 3058, strName = "����ѩ��"  },
                                        { level = 65, bossId = 3062, strName = "��Ӱ��"    },
                                        { level = 70, bossId = 3063, strName = "������"    },
                                        { level = 75, bossId = 3064, strName = "��βʨ"    },
}
-- �������Ǳ�
x300330_g_MonsterLive               = {
                                        { live = 0, sceneId = 50,  mapName = "¥������"   }, 
                                        { live = 0, sceneId = 51,  mapName = "¥������"   }, 
                                        { live = 0, sceneId = 150, mapName = "��ɽ����"   }, 
                                        { live = 0, sceneId = 151, mapName = "��ɽ����"   }, 
                                        { live = 0, sceneId = 250, mapName = "��������"   }, 
                                        { live = 0, sceneId = 251, mapName = "���ر���"   }, 
                                        { live = 0, sceneId = 350, mapName = "�ػ�����"   }, 
                                        { live = 0, sceneId = 351, mapName = "�ػͱ���"   }, 
                                        { live = 0, sceneId = 0,   mapName = "��"       }, 
                                        { live = 0, sceneId = 15,  mapName = "������"     }, 
}

-- �ٹ���Id
x300330_g_CallerId      = 0
x300330_g_CountryID     = 0
x300330_g_CallerName    = ""
-- �ھ�Χ�����ھ����Χ�����Χ���ھ���Ч
x300330_g_DigRange      = 2
-- Ǯ����Ч
x300330_g_MoneyBuff     = 7046
-- ��ʯ��Ч
x300330_g_GemBuff       = 7047
-- ҩƿ��Ч
x300330_g_MedicineBuff  = 7048
-- ��ħ��Ч
x300330_g_MonsterBuff   = 7049	

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300330_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )
    --print( "*****" )
end

---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300330_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--����������ִ�д˽ű�

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if(bHaveMission > 0) then
		local bDone = x300330_CheckSubmit(sceneId, selfId, NPCId);
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x300330_DispatchCompletedInfo( sceneId, selfId, NPCId ) --���������ʾ
			end
		else
			if nExtIdx ~= -1 then
				x300330_DispatchContinueInfo( sceneId, selfId, NPCId ) --δ���������ʾ
			end
		end
	else
		x300330_DispatchMissionInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300330_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAccept( sceneId, selfId, targetId, missionId)
	return 0
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAbandon(sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if(bHaveMission > 0) then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId); 
		DelQuest(sceneId, selfId, x300330_g_MissionId)

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, x300330_g_strMissionAbandon)
		EndQuestEvent( sceneId)
		DispatchQuestTips( sceneId, selfId)
		Msg2Player( sceneId, selfId, x300330_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300330_CheckSubmit(sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE);

end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300330_GetBonus( sceneId, selfId,NpcID, SelectId )

	--������Ǯ1
	if x300330_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300330_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300330_g_BonusMoney1),4,2)
	end

	--������Ǯ2
	if x300330_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300330_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300330_g_BonusMoney2),4,2)
	end

	--������Ǯ1
	if x300330_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300330_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x300330_g_BonusMoney3),4,2)
	end

	--��������
	if x300330_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300330_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("��ý�������%d�Ľ�����", x300330_g_BonusMoney4),4,2)
	end

	--��͢����
	if x300330_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300330_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("��ó�͢����%d�Ľ�����", x300330_g_BonusMoney5),4,2)
	end

	--��͢����
	if x300330_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300330_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x300330_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
	for i, item in x300330_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--������ѡ��Ʒ
	for i, item in x300330_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--��ȡ��أ��뷵�أ���ֹ�ظ����
			return
		end
    end

end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

	--�ж��Ƿ�������
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300330_g_MissionId);
	if bHaveMission > 0 then

		local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x300330_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
		    	x300330_GetBonus( sceneId,selfId,NPCId,selectRadioId )
		    	DelQuest(sceneId, selfId, x300330_g_MissionId)
		    	
					local scriptId = -1;
					local missionId = -1;
					local randnum = random(1, 5);
					if(randnum == 1) then
						scriptId = 300761;
						missionId = 7553;
					elseif(randnum == 2) then
						scriptId = 300762;
						missionId = 7554;
					elseif(randnum == 3) then
						scriptId = 300330;
						missionId = 7581;
					elseif(randnum == 4) then
						scriptId = 300764;
						missionId = 7582;
					elseif(randnum == 5) then
						scriptId = 300765;
						missionId = 7583;
					end
					CallScriptFunction( scriptId, "OnForceAddMission", sceneId, selfId, NPCId, missionId );
			   	--end
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����������")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����û����ɣ�")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else

		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"���񲻴��ڣ���ȡ������Ϣʧ�ܣ�")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);

		return
	end

end

---------------------------------------------------------------------------------------------------
--�����Ұ�������
---------------------------------------------------------------------------------------------------
function x300330_CheckPlayerBagFull( sceneId ,selfId )


	local result = 1

	local j = 0

	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������

	--��ͨ�Ľ������
	BeginAddItem(sceneId)
	for j, item in x300330_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

	local ret = EndAddItem(sceneId,selfId)
	if ret <= 0 then
		result = 0
		bAdd = 1
	end

    --������ѡ��Ʒ
	if bAdd == 0 then

		for j, item in x300330_g_BonusChoiceItem do
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret <= 0 then
				if result == 1 then
					result = 0
				end
			end
	    end
	end

	return result
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300330_DispatchMissionInfo( sceneId, selfId, NPCId )
--print( "***********" )
	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x300330_g_MissionName)
		AddQuestText(sceneId,x300330_g_MissionInfo)
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y����Ŀ�꣺")
		AddQuestText( sceneId,x300330_g_MissionTarget)
		AddQuestText( sceneId," ")

		--��ʾ��Ϣ
		if x300330_g_MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y������ʾ��")
			AddQuestText(sceneId,x300330_g_MissionHelp )
			AddQuestText(sceneId," ")
		end

		--��������Ϣ

		--1������
		if x300330_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x300330_g_ExpBonus )
		end

		--2����Ǯ1
		if x300330_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300330_g_BonusMoney1 )
		end

		--3����Ǯ2
		if x300330_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300330_g_BonusMoney2 )
		end
		--4����Ǯ3
		if x300330_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300330_g_BonusMoney3 )
		end

		--��������
		if x300330_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300330_g_BonusMoney4 )
		end

		--��͢����
		if x300330_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300330_g_BonusMoney5 )
		end

		--����ֵ
		if x300330_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300330_g_BonusMoney6 )
		end


		--5���̶���Ʒ
		for i, item in x300330_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x300330_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end


	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300330_g_ScriptId, x300330_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--ʹ�������ھ�ͨ�������Ľű����ô˺���
---------------------------------------------------------------------------------------------------
function x300330_OnDigbyShovel( sceneId, selfId)
    --print( "ʹ������" )
    if IsHaveQuestNM( sceneId, selfId, x300330_g_MissionId) == 0 then
		-- BeginQuestEvent( sceneId)
		-- AddQuestText( sceneId, "�����Ե��ھ���һ�󣬿�ϧһ�����á�" )
		-- EndQuestEvent( sceneId)
		-- DispatchQuestTips( sceneId, selfId)
        -- Msg2Player( sceneId, selfId, "�����Ե��ھ���һ�󣬿�ϧһ�����á�", 8, 2)
        return 0
    else
        -- ����ھ��
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300330_g_MissionId)
        local ts = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET4)
        if ts ~= sceneId then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "�ھ򳡾����ԣ�����æ��һ��" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "�ھ򳡾����ԣ�����æ��һ��", 8, 2)
            return 0
        end
        local x = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET2)
        local z = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET3)
        local curX, curZ = GetWorldPos( sceneId, selfId)
        curX = abs( x - curX)
        curZ = abs( z - curZ)
        if curX > x300330_g_DigRange or curZ > x300330_g_DigRange then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "�����Ե��ھ���һ�󣬿�ϧһ������" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "�����Ե��ھ���һ�󣬿�ϧһ������", 8, 2)
            return 0
        end
        local control = 1
        local brk = 0

        while control == 1 do 
            local irand = random( 1, 100)
            brk = 0
            local buff 	=	9011
						local buff1 =	9013
						local buff2 =	9012
            if irand <= 20 then -- �������3��(20%)

            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 0, 3000)
                else
                	BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 1, 3000)
	            end
                -- Ǯ����Ч
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
            elseif irand > 20 and irand <= 23 then -- ��һ������10��(3%)
            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����10��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����10��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 0, 10000)
	                local strName = GetName( sceneId, selfId)
               		Msg2Player( sceneId, selfId, "#cffcf00��ϲ��ϲ�����"..strName.."ʹ�òر�ͼѰ��ʱ�����#R10������#cffcf00�����Ǻ���������", 2, 1)-- ���½�
                	Msg2Player( sceneId, selfId, "#cffcf00��ϲ��ϲ�����"..strName.."ʹ�òر�ͼѰ��ʱ�����#R10������#cffcf00�����Ǻ���������", 2, 4)-- ˮƽ����
	            else
	            	BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����10��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����10��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 1, 10000)
	            end
                -- Ǯ����Ч
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
                -- �㲥
                
            elseif irand > 23 and irand <= 33 then -- �������3��
            	if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
	        		BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 0, 3000)
                else 
	                BeginQuestEvent( sceneId)
	        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��" )
	        		EndQuestEvent( sceneId)
	        		DispatchQuestTips( sceneId, selfId)
	                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R����3��#cffcf00����ϲ��ϲ��", 8, 2)
	                AddMoney( sceneId, selfId, 1, 3000)
                end
                -- Ǯ����Ч
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MoneyBuff, 0)
            elseif irand > 33 and irand <= 43 then -- ���1����Ͼ
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000201, 1)-- ����ǳ�
                else
                	AddBindItem( sceneId, 11000201, 1)-- ����ǳ�
                end
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            -- elseif irand > 23 and irand <= 43 then -- ���5��΢�(20%)
                -- BeginAddItem( sceneId)
                -- AddItem( sceneId, 11000200, 5)-- ΢��ǳ�
                -- local result = EndAddItem( sceneId, selfId)
                -- if result == 0 then
            		-- BeginQuestEvent( sceneId)
            		-- AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		-- EndQuestEvent( sceneId)
            		-- DispatchQuestTips( sceneId, selfId)
                    -- DelQuest( sceneId, selfId, x300330_g_MissionId)
                    -- return 1
                -- end
        		-- BeginQuestEvent( sceneId)
        		-- AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#R5��#{_ITEM11000200}#cffcf00����ϲ��ϲ��" )
                -- AddItemListToPlayer( sceneId, selfId)
        		-- EndQuestEvent( sceneId)
        		-- DispatchQuestTips( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#R5��#{_ITEM11000200}#cffcf00����ϲ��ϲ��", 8, 2)
                -- SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 43 and irand <= 48 then -- ���1����Ͼ(5%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000201, 1)-- ����ǳ�
                else
                	AddBindItem( sceneId, 11000201, 1)-- ����ǳ�
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 48 and irand <= 58 then -- ���1�������Ʊ�ʯ��1�����ݻƱ�ʯ��1�������Ʊ�ʯ��1����������ʯ�е�3�������ظ���(20%)
                local gemArray = { 14030001, 14030006, 14030011, 14040001 }
                local gemName = { "1��������", "1�����ݻ�", "1��������", "1��������" }
                local index = random( 1, 4)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, gemArray[ index], 3)
                else
                	AddBindItem( sceneId, gemArray[ index], 3)
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
                local strTemp = format( "�ڲر�ͼ��ָ���£����õ���#R3��#{_ITEM%d}#cffcf00����ϲ��ϲ��", gemArray[ index] )
                AddItemListToPlayer( sceneId, selfId)
                Msg2Player( sceneId, selfId, strTemp, 8, 2)
                Msg2Player( sceneId, selfId, strTemp, 8, 3)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 58 and irand <= 68 then -- �����ˮ����10%��
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 11000202, 1)
                else
                	AddBindItem( sceneId, 11000202, 1)
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
                local strTemp = format( "�ڲر�ͼ��ָ���£����õ���#R1��#{_ITEM%d}#cffcf00����ϲ��ϲ��", 11000202)
                AddItemListToPlayer( sceneId, selfId)
                Msg2Player( sceneId, selfId, strTemp, 8, 2)
                Msg2Player( sceneId, selfId, strTemp, 8, 3)
            -- elseif irand > 68 and irand <= 73 then -- ���Ǳ�ܵ���(5%)
                -- BeginAddItem( sceneId)
                -- AddItem( sceneId, 12055000, 1)-- Ǳ�ܵ���
                -- local result = EndAddItem( sceneId, selfId)
                -- if result == 0 then
            		-- BeginQuestEvent( sceneId)
            		-- AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		-- EndQuestEvent( sceneId)
            		-- DispatchQuestTips( sceneId, selfId)
                    -- DelQuest( sceneId, selfId, x300330_g_MissionId)
                    -- return 1
                -- end
        		-- BeginQuestEvent( sceneId)
        		-- AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���һ��Ǳ�ܵ��飬��ϲ��ϲ��" )
                -- AddItemListToPlayer( sceneId, selfId)
        		-- EndQuestEvent( sceneId)
        		-- DispatchQuestTips( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���һ��Ǳ�ܵ��飬��ϲ��ϲ��", 8, 2)
            elseif irand > 68 and irand <= 69 then -- �����˻�ͯҩ(1%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, 12054300, 1)-- ��˻�ͯ��
                else
                	AddBindItem( sceneId, 12054300, 1)-- ��˻�ͯ��
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#Rһ����˻�ͯ��#cffcf00����ϲ��ϲ��" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#Rһ����˻�ͯ��#cffcf00����ϲ��ϲ��", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MedicineBuff, 0)
            elseif irand > 69 and irand <= 90 then -- �ٻ�BOSS(21%)
                if x300330_CallBoss( sceneId, selfId) == 0 then
                    brk = 1
                else
                    --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MonsterBuff, 0)
                end
            elseif irand > 90 and irand <= 95 then -- ���1����Ͼ(5%)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
               	 AddItem( sceneId, 11000201, 1)-- ����ǳ�
               	else
               		AddBindItem( sceneId, 11000201, 1)-- ����ǳ�	 
               	end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���#Rһ��#{_ITEM11000201}#cffcf00����ϲ��ϲ��", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_GemBuff, 0)
            elseif irand > 95 and irand <= 100 then -- �ڳ����ײк�������к�����צ�к�����β�к��е�һ��(10%)
                local gemArray = { 12030022, 12030023, 12030024, 12030025 }
                local gemName = { "���ײк�", "����к�", "��צ�к�", "��β�к�" }
                local index = random( 1, 4)
                BeginAddItem( sceneId)
                if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
                	AddItem( sceneId, gemArray[ index], 1)
                else
                	AddBindItem( sceneId, gemArray[ index], 1)	
                end	
                local result = EndAddItem( sceneId, selfId)
                if result == 0 then
            		BeginQuestEvent( sceneId)
            		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            		EndQuestEvent( sceneId)
            		DispatchQuestTips( sceneId, selfId)
                    DelQuest( sceneId, selfId, x300330_g_MissionId)
                    return 1
                end
        		BeginQuestEvent( sceneId)
        		AddQuestText( sceneId, "�ڲر�ͼ��ָ���£����õ���һ��#R"..gemName[ index].."#cffcf00����ϲ��ϲ��" )
                AddItemListToPlayer( sceneId, selfId)
        		EndQuestEvent( sceneId)
        		DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, "�ڲر�ͼ��ָ���£����õ���һ��#R"..gemName[ index].."#cffcf00����ϲ��ϲ��", 8, 2)
                --SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300330_g_MedicineBuff, 0)
            end

            control = brk
        end

        -- ɾ������
        DelQuest( sceneId, selfId, x300330_g_MissionId)
        -- ��ʾ�������
        Msg2Player( sceneId, selfId, "������ˣ�"..x300330_g_MissionName, 8, 2)
        Msg2Player( sceneId, selfId, "������ˣ�"..x300330_g_MissionName, 8, 3)
        -- д��־
        GamePlayScriptLog( sceneId, selfId, 622)
        -- �����������ô���
        CallScriptFunction( 300331, "LogicDeplete", sceneId, selfId)
    end

    return 1
end

---------------------------------------------------------------------------------------------------
-- �ھ���ٻ�Boss
---------------------------------------------------------------------------------------------------
function x300330_CallBoss( sceneId, selfId)
    local monsters = {}
    local count = 1

    -- ���ݵ�ǰ�����޶�ѡ�ַ�Χ
    local maxLevel = 100
    if sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
        -- ���ǳ��ֵ�Boss���40��
        maxLevel = 40
    elseif sceneId == 51 or sceneId == 151 or sceneId == 251 or sceneId == 351 then
        -- �������ֵ�Boss���60��
        maxLevel = 60
    elseif sceneId == 36 or sceneId == 37 or sceneId == 38 or sceneId == 15 then
        maxLevel = 80
    end

    for i, item in x300330_g_MonsterTable do
        if item.level <= maxLevel then
            monsters[ count] = item
            count = count + 1
        end
    end

    -- ���ѡȡһֻ��
    local i = random( 1, getn( monsters) )
    -- ����������Ѿ�������ٻ���Boss
    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId and item.live == 1 then
            return 0
        end
    end

    -- �����ҵ�ǰλ��
    local x, z = GetWorldPos( sceneId, selfId)
    local mapName = ""
    CreateMonster( sceneId, monsters[ i].bossId, x + random( 1, 3), z + random( 1, 3), 1, -1, x300330_g_ScriptId, -1, 21, 30*60*1000)
    -- ����Boss�����
    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId then
            x300330_g_MonsterLive[ i].live = 1
            mapName = item.mapName
        end
    end

    Msg2Player( sceneId, selfId, "��һ���ھ�ȴ����һ���ڹ�ӵ���ð�����������������ߡ�", 8, 2)
    Msg2Player( sceneId, selfId, "��һ���ھ�ȴ����һ���ڹ�ӵ���ð�����������������ߡ�", 8, 3)
    -- �㲥
    local name = GetName( sceneId, selfId)
    local broadcast = "#e010101#cFF7903���#G"..name.."#e010101#cFF7903��ʹ�òر�ͼѰ���Ĺ����в�С�İ����޸����˳���������������#S"..mapName.."#e010101#cFF7903�����ε������ҿ��ǰ������"
    LuaAllScenceM2Country( sceneId, broadcast, GetCurCountry( sceneId, selfId), 0, 1)
    LuaAllScenceM2Country( sceneId, broadcast, GetCurCountry( sceneId, selfId), 4, 1)

    return 1
end

---------------------------------------------------------------------------------------------------
-- �ھ����������Ĺֱ�ɱ����ô˺���
---------------------------------------------------------------------------------------------------
function x300330_OnDie( sceneId, selfId, killerId)

    
--    GetCountryQuestDataNM(sceneId,x300330_g_CallerId,x300330_g_CountryID,CD_INDEX_MISSION_CAOBAOTU,x300330_g_ScriptId,-1,"OnCreaterGetBonus")

    --�㲥�����Ϣ
    --ThisScenceM2Country( sceneId, x300330_g_CountryID, "��ϲ��ϲ�����"..x300330_g_CallerName.."ʹ�òر�ͼѰ��ʱ�����#R10������#cffcf00�����Ǻ���������", 2, 1)-- ���½�
    --ThisScenceM2Country( sceneId, x300330_g_CountryID, "��ϲ��ϲ�����"..x300330_g_CallerName.."ʹ�òر�ͼѰ��ʱ�����#R10������#cffcf00�����Ǻ���������", 3, 1)-- ˮƽ����

    for i, item in x300330_g_MonsterLive do
        if item.sceneId == sceneId then
            x300330_g_MonsterLive[ i].live = 0
        end
    end

    x300330_g_CountryID = 0
    x300330_g_CallerId = 0    
    x300330_g_CallerName = ""

end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300330_DispatchContinueInfo( sceneId, selfId, NPCId )
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300330_DispatchCompletedInfo( sceneId, selfId, NPCId )
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestObjectKilled(sceneId, selfId, objdataId ,objId, MissionId )
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300330_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300330_g_MissionId)
    local mapId = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET1)
    local targetId = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET4)
    local x = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET2)
    local z = GetQuestParam( sceneId, selfId, misIndex, x300330_MP_TARGET3)
    local strMapName = ""

    if mapId == 0 then
        strMapName = "����"
    elseif mapId == 1 then
        strMapName = "����"
    elseif mapId == 2 then
        strMapName = "��"
    elseif mapId == 3 then
        strMapName = "������"
    elseif mapId == 36 then
        strMapName = "����"        
    elseif mapId == 37 then
        strMapName = "�󶼶�"        
    elseif mapId == 38 then
        strMapName = "����"        
    end

    

	BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x300330_g_MissionName,             -- ��������
                                format( x300330_g_MissionTarget, targetId, x, z,strMapName,x,z),
                                "��",                             --����NPC
                                x300330_g_MissionHelp,
                                format( x300330_g_MissionInfo, targetId, x, z,strMapName,x,z),
                                "" )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

---------------------------------------------------------------------------------------------------
--ǿ�м���������Ҽ�����ر�ͼ����ô˺���
---------------------------------------------------------------------------------------------------
function x300330_OnForceAddMission( sceneId, selfId, npcId, MissionId)
	if( MissionId ~= x300330_g_MissionId) then
		return 0;
	end

	-- print( "*********" )
	if(x300330_ProcAcceptCheck( sceneId, selfId, -1 ) ~= 1) then
		return 0;
	end
	local ret = AddQuest( sceneId, selfId, x300330_g_MissionId, x300330_g_ScriptId, 0, 0, 0, 0)
	if(ret == 0) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������������ʧ�ܣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
    else
        -- ��ʾ���������Ϣ
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "����������񣺡����ˡ��ر�ͼ������" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "����������񣺡����ˡ��ر�ͼ������", 8, 2)
	end

		local guo = GetCurCountry(sceneId,selfId)
		if guo ==0 then
	    -- ���ѡȡ�ھ��
	    local size = getn( x300330_g_MissionTargetTable0)
	    local i = random( 1, size)
	    -- �����ҵȼ�С��40������ֻ����ȡ�������ھ��
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable0[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable0[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable0[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable0[ i].mapId + 50
	    if x300330_g_MissionTargetTable0[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable0[ i].mapId == 38 then
	        mapId = 38       
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- д��־
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==1 then
	    -- ���ѡȡ�ھ��
	    local size = getn( x300330_g_MissionTargetTable1)
	    local i = random( 1, size)
	    -- �����ҵȼ�С��40������ֻ����ȡ�������ھ��
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable1[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable1[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable1[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable1[ i].mapId + 50
	    if x300330_g_MissionTargetTable1[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable1[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- д��־
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==2 then
	    -- ���ѡȡ�ھ��
	    local size = getn( x300330_g_MissionTargetTable2)
	    local i = random( 1, size)
	    -- �����ҵȼ�С��40������ֻ����ȡ�������ھ��
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable2[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable2[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable2[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable2[ i].mapId + 50
	    if x300330_g_MissionTargetTable2[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable2[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- д��־
	    GamePlayScriptLog( sceneId, selfId, 621)
	    return 1
	    
	    
	    elseif guo ==3 then
	    -- ���ѡȡ�ھ��
	    local size = getn( x300330_g_MissionTargetTable3)
	    local i = random( 1, size)
	    -- �����ҵȼ�С��40������ֻ����ȡ�������ھ��
	    if GetLevel( sceneId, selfId) < 40 then
	        i = random( 1, 100)
	    end
	
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300330_g_MissionId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET1, x300330_g_MissionTargetTable3[ i].mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET2, x300330_g_MissionTargetTable3[ i].posX)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET3, x300330_g_MissionTargetTable3[ i].posZ)
	    local mapId = GetCurCountry( sceneId, selfId) * 100 + x300330_g_MissionTargetTable3[ i].mapId + 50
	    if x300330_g_MissionTargetTable3[ i].mapId == 2 then
	        mapId = 0
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 3 then
	        mapId = 15
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 36 then
	        mapId = 36	        
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 37 then
	        mapId = 37	                
	    elseif x300330_g_MissionTargetTable3[ i].mapId == 38 then
	        mapId = 38 	        
	    end
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_TARGET4, mapId)
	    SetQuestByIndex( sceneId, selfId, misIndex, x300330_MP_ISCOMPLETE, 0)
	    -- д��־
	    GamePlayScriptLog( sceneId, selfId, 621)
	
	    return 1
	  end
	    
end

-----------------------------------------------------------------------------
--�������������ҽ���
-----------------------------------------------------------------------------
function x300330_OnCreaterGetBonus(sceneId,guid,missiondata)

    local nCastGuid = NumberCastIntToUInt(guid)
    
    --���ҵ����
    local selfId = -1
    local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local objGUID = GetPlayerGUID(sceneId, objId )
            if objGUID == nCastGuid then
                selfId = objId
                break
            end
        end
    end

    if selfId == -1 then
        return
    end

    --�������������������ʾ
    local xp = GetLevel( sceneId, selfId) * 500
    AddExp( sceneId, selfId, xp)

    local strMsg = format("���ų��Ĺ��Ѿ���������������%d�㾭��", xp)

    local name = GetName(sceneId,selfId)
    LuaScenceM2Player(sceneId,selfId,strMsg,name,2,1)
    LuaScenceM2Player(sceneId,selfId,strMsg,name,3,1)

end
