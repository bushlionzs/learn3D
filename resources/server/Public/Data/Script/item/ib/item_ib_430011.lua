
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x430011_g_scriptId 		= 430011 



x430011_g_itemlist = { 
						  {id=12230001,  levelmin = 71, skillname ="冲锋斩 ",	skillid =121, skilllevel =8},
						  {id=12230002,  levelmin = 76, skillname ="杀无赦",	skillid =123, skilllevel =8},
						  {id=12230003,  levelmin = 72, skillname ="扬威破阵",	skillid =124, skilllevel =8},
						  {id=12230004,  levelmin = 74, skillname ="战八方",	skillid =125, skilllevel =8},
						  {id=12230005,  levelmin = 71, skillname ="笑骂千军",	skillid =126, skilllevel =8},
						  {id=12230006,  levelmin = 77, skillname ="怒发冲冠",	skillid =127, skilllevel =8},
						  {id=12230007,  levelmin = 78, skillname ="热血沸腾",	skillid =128, skilllevel =8},
						  {id=12230008,  levelmin = 75, skillname ="锐不可挡",	skillid =129, skilllevel =8},
						  {id=12230009,  levelmin = 79, skillname ="虽远必诛",	skillid =130, skilllevel =8},
						  {id=12230010,  levelmin = 73, skillname ="勇冠三军",	skillid =132, skilllevel =8},
						  {id=12230011,  levelmin = 76, skillname ="血量增强",	skillid =134, skilllevel =8},
						  {id=12230012,  levelmin = 77, skillname ="免疫增强",	skillid =135, skilllevel =8},
						  {id=12230013,  levelmin = 78, skillname ="近攻增强",	skillid =136, skilllevel =8},
						  {id=12230014,  levelmin = 79, skillname ="韧性增强",	skillid =137, skilllevel =8},
						  {id=12230101,  levelmin = 77, skillname ="凌波微步",	skillid =201, skilllevel =8},
						  {id=12230102,  levelmin = 79, skillname ="穴打风池",	skillid =202, skilllevel =8},
						  {id=12230103,  levelmin = 76, skillname ="起剑诀",	skillid =203, skilllevel =8},
						  {id=12230104,  levelmin = 75, skillname ="御剑诀",	skillid =204, skilllevel =8},
						  {id=12230105,  levelmin = 72, skillname ="一剑乾坤",	skillid =205, skilllevel =8},
						  {id=12230106,  levelmin = 76, skillname ="剑走偏锋",	skillid =206, skilllevel =8},
						  {id=12230107,  levelmin = 71, skillname ="七伤剑阵",	skillid =207, skilllevel =8},
						  {id=12230108,  levelmin = 73, skillname ="七星剑阵",	skillid =208, skilllevel =8},
						  {id=12230109,  levelmin = 71, skillname ="金蝉脱壳",	skillid =209, skilllevel =8},
						  {id=12230110,  levelmin = 74, skillname ="逍遥游",	skillid =210, skilllevel =8},
						  {id=12230111,  levelmin = 78, skillname ="梯云纵",	skillid =211, skilllevel =8},
						  {id=12230112,  levelmin = 79, skillname ="暴击增强",	skillid =212, skilllevel =8},
						  {id=12230113,  levelmin = 77, skillname ="近攻增强",	skillid =213, skilllevel =8},
						  {id=12230114,  levelmin = 78, skillname ="命中增强",	skillid =214, skilllevel =8},
						  {id=12230201,  levelmin = 78, skillname ="锋芒之歌",	skillid =301, skilllevel =8},
						  {id=12230202,  levelmin = 77, skillname ="天鹰之歌",	skillid =302, skilllevel =8},
						  {id=12230203,  levelmin = 71, skillname ="血羽箭",	skillid =303, skilllevel =8},
						  {id=12230204,  levelmin = 79, skillname ="淬毒箭",	skillid =305, skilllevel =8},
						  {id=12230205,  levelmin = 72, skillname ="百步穿杨",	skillid =306, skilllevel =8},
						  {id=12230206,  levelmin = 76, skillname ="万箭齐发",	skillid =307, skilllevel =8},
						  {id=12230207,  levelmin = 73, skillname ="自由之歌",	skillid =309, skilllevel =8},
						  {id=12230208,  levelmin = 74, skillname ="战神之歌",	skillid =311, skilllevel =8},
						  {id=12230209,  levelmin = 76, skillname ="敏捷增强",	skillid =313, skilllevel =8},
						  {id=12230210,  levelmin = 71, skillname ="远攻增强",	skillid =314, skilllevel =8},
						  {id=12230211,  levelmin = 77, skillname ="韧性增强",	skillid =315, skilllevel =8},
						  {id=12230212,  levelmin = 75, skillname ="迷魂索",	skillid =316, skilllevel =8},
						  {id=12230213,  levelmin = 78, skillname ="夺命索",	skillid =317, skilllevel =8},
						  {id=12230214,  levelmin = 79, skillname ="绊马索",	skillid =318, skilllevel =8},
						  {id=12230301,  levelmin = 71, skillname ="狙击",		skillid =404, skilllevel =8},
						  {id=12230302,  levelmin = 77, skillname ="毁灭",		skillid =406, skilllevel =8},
						  {id=12230303,  levelmin = 74, skillname ="快速填弹",	skillid =408, skilllevel =8},
						  {id=12230304,  levelmin = 73, skillname ="散兵队形",	skillid =409, skilllevel =8},
						  {id=12230305,  levelmin = 79, skillname ="火线救护",	skillid =410, skilllevel =8},
						  {id=12230306,  levelmin = 77, skillname ="震荡雷",	skillid =411, skilllevel =8},
						  {id=12230307,  levelmin = 79, skillname ="暴击增强",	skillid =412, skilllevel =8},
						  {id=12230308,  levelmin = 71, skillname ="远攻增强",	skillid =413, skilllevel =8},
						  {id=12230309,  levelmin = 76, skillname ="命中增强",	skillid =414, skilllevel =8},
						  {id=12230310,  levelmin = 75, skillname ="霰光雷",	skillid =417, skilllevel =8},
						  {id=12230311,  levelmin = 78, skillname ="排子炮",	skillid =418, skilllevel =8},
						  {id=12230312,  levelmin = 78, skillname ="地网雷",	skillid =421, skilllevel =8},
						  {id=12230313,  levelmin = 72, skillname ="连珠炮",	skillid =422, skilllevel =8},
						  {id=12230314,  levelmin = 76, skillname ="一闪",		skillid =423, skilllevel =8},
						  {id=12230401,  levelmin = 77, skillname ="天之惩戒",	skillid =501, skilllevel =8},
						  {id=12230402,  levelmin = 78, skillname ="风之惩戒",	skillid =502, skilllevel =8},
						  {id=12230403,  levelmin = 77, skillname ="火之惩戒",	skillid =503, skilllevel =8},
						  {id=12230404,  levelmin = 72, skillname ="末日审判",	skillid =505, skilllevel =8},
						  {id=12230405,  levelmin = 76, skillname ="沉默箴言",	skillid =506, skilllevel =8},
						  {id=12230406,  levelmin = 71, skillname ="禁锢箴言",	skillid =507, skilllevel =8},
						  {id=12230407,  levelmin = 73, skillname ="神灯之光",	skillid =508, skilllevel =8},
						  {id=12230408,  levelmin = 78, skillname ="玄石之盾",	skillid =509, skilllevel =8},
						  {id=12230409,  levelmin = 75, skillname ="气定神闲",	skillid =510, skilllevel =8},
						  {id=12230410,  levelmin = 74, skillname ="祷告之歌",	skillid =511, skilllevel =8},
						  {id=12230411,  levelmin = 79, skillname ="幻影箴言",	skillid =512, skilllevel =8},
						  {id=12230412,  levelmin = 79, skillname ="暴击增强",	skillid =513, skilllevel =8},
						  {id=12230413,  levelmin = 71, skillname ="魔攻增强",	skillid =514, skilllevel =8},
						  {id=12230414,  levelmin = 76, skillname ="闪避增强",	skillid =515, skilllevel =8},
						  {id=12230501,  levelmin = 75, skillname ="烈犬之舞",	skillid =601, skilllevel =8},
						  {id=12230502,  levelmin = 77, skillname ="黑鸦蛊惑",	skillid =602, skilllevel =8},
						  {id=12230503,  levelmin = 71, skillname ="小巫医术",	skillid =604, skilllevel =8},
						  {id=12230504,  levelmin = 72, skillname ="火凤之舞",	skillid =605, skilllevel =8},
						  {id=12230505,  levelmin = 78, skillname ="回春之光",	skillid =606, skilllevel =8},
						  {id=12230506,  levelmin = 79, skillname ="白蟒蛊惑",	skillid =609, skilllevel =8},
						  {id=12230507,  levelmin = 73, skillname ="冥神附体",	skillid =610, skilllevel =8},
						  {id=12230508,  levelmin = 74, skillname ="大巫医术",	skillid =611, skilllevel =8},
						  {id=12230509,  levelmin = 78, skillname ="巫神之舞",	skillid =612, skilllevel =8},
						  {id=12230510,  levelmin = 76, skillname ="智力增强",	skillid =613, skilllevel =8},
						  {id=12230511,  levelmin = 71, skillname ="魔攻增强",	skillid =614, skilllevel =8},
						  {id=12230512,  levelmin = 79, skillname ="韧性增强",	skillid =615, skilllevel =8},
						  {id=12230513,  levelmin = 76, skillname ="石神附体",	skillid =616, skilllevel =8},
						  {id=12230514,  levelmin = 77, skillname ="雪神附体",	skillid =617, skilllevel =8},
              {id=12230015,  levelmin = 91, skillname ="冲锋斩" ,	  skillid =121, skilllevel =9},
              {id=12230016,  levelmin = 96, skillname ="杀无赦" ,	  skillid =123, skilllevel =9},
              {id=12230017,  levelmin = 92, skillname ="扬威破阵" ,	skillid =124, skilllevel =9},
              {id=12230018,  levelmin = 94, skillname ="战八方" ,	  skillid =125, skilllevel =9},
              {id=12230019,  levelmin = 91, skillname ="笑骂千军" ,	skillid =126, skilllevel =9},
              {id=12230020,  levelmin = 97, skillname ="怒发冲冠" ,	skillid =127, skilllevel =9},
              {id=12230021,  levelmin = 98, skillname ="热血沸腾" ,	skillid =128, skilllevel =9},      
              {id=12230022,  levelmin = 95, skillname ="锐不可挡" ,	skillid =129, skilllevel =9},
              {id=12230023,  levelmin = 99, skillname ="虽远必诛" ,	skillid =130, skilllevel =9},
              {id=12230024,  levelmin = 93, skillname ="勇冠三军" ,	skillid =132, skilllevel =9},
              {id=12230025,  levelmin = 96, skillname ="血量增强" ,	skillid =134, skilllevel =9},
              {id=12230026,  levelmin = 97, skillname ="免疫增强" ,	skillid =135, skilllevel =9},
              {id=12230027,  levelmin = 98, skillname ="近攻增强" ,	skillid =136, skilllevel =9},
              {id=12230028,  levelmin = 99, skillname ="韧性增强" ,	skillid =137, skilllevel =9},
              {id=12230115,  levelmin = 97, skillname ="凌波微步" ,	skillid =201, skilllevel =9},
              {id=12230116,  levelmin = 99, skillname ="穴打风池" ,	skillid =202, skilllevel =9},
              {id=12230117,  levelmin = 96, skillname ="起剑诀" ,	  skillid =203, skilllevel =9},
              {id=12230118,  levelmin = 95, skillname ="御剑诀" ,	  skillid =204, skilllevel =9},
              {id=12230119,  levelmin = 92, skillname ="一剑乾坤" ,	skillid =205, skilllevel =9},
              {id=12230120,  levelmin = 96, skillname ="剑走偏锋" ,	skillid =206, skilllevel =9},
              {id=12230121,  levelmin = 91, skillname ="七伤剑阵",	skillid =207, skilllevel =9},
              {id=12230122,  levelmin = 93, skillname ="七星剑阵" ,	skillid =208, skilllevel =9},
              {id=12230123,  levelmin = 91, skillname ="金蝉脱壳" ,	skillid =209, skilllevel =9},
              {id=12230124,  levelmin = 94, skillname ="逍遥游" ,	  skillid =210, skilllevel =9},
              {id=12230125,  levelmin = 98, skillname ="梯云纵" ,	  skillid =211, skilllevel =9},
              {id=12230126,  levelmin = 99, skillname ="暴击增强" ,	skillid =212, skilllevel =9},
              {id=12230127,  levelmin = 97, skillname ="近攻增强" ,	skillid =213, skilllevel =9},
              {id=12230128,  levelmin = 98, skillname ="命中增强" ,	skillid =214, skilllevel =9},
              {id=12230215,  levelmin = 98, skillname ="锋芒之歌" ,	skillid =301, skilllevel =9},
              {id=12230216,  levelmin = 97, skillname ="天鹰之歌" ,	skillid =302, skilllevel =9},
              {id=12230217,  levelmin = 91, skillname ="血羽箭" ,	  skillid =303, skilllevel =9},
              {id=12230218,  levelmin = 99, skillname ="淬毒箭" ,	  skillid =305, skilllevel =9},
              {id=12230219,  levelmin = 92, skillname ="百步穿杨" ,	skillid =306, skilllevel =9},
              {id=12230220,  levelmin = 96, skillname ="万箭齐发" ,	skillid =307, skilllevel =9},
              {id=12230221,  levelmin = 93, skillname ="自由之歌" ,	skillid =309, skilllevel =9},
              {id=12230222,  levelmin = 94, skillname ="战神之歌" ,	skillid =311, skilllevel =9},
              {id=12230223,  levelmin = 96, skillname ="敏捷增强" ,	skillid =313, skilllevel =9},
              {id=12230224,  levelmin = 91, skillname ="远攻增强" ,	skillid =314, skilllevel =9},
              {id=12230225,  levelmin = 97, skillname ="韧性增强" ,	skillid =315, skilllevel =9},
              {id=12230226,  levelmin = 95, skillname ="迷魂索" ,	  skillid =316, skilllevel =9},
              {id=12230227,  levelmin = 98, skillname ="夺命索" ,	  skillid =317, skilllevel =9},
              {id=12230228,  levelmin = 99, skillname ="绊马索" ,	  skillid =318, skilllevel =9},
              {id=12230315,  levelmin = 91, skillname ="狙击" ,	    skillid =404, skilllevel =9},
              {id=12230316,  levelmin = 97, skillname ="毁灭" ,	    skillid =406, skilllevel =9},
              {id=12230317,  levelmin = 94, skillname ="快速填弹" ,	skillid =408, skilllevel =9},
              {id=12230318,  levelmin = 93, skillname ="散兵队形" ,	skillid =409, skilllevel =9},
              {id=12230319,  levelmin = 99, skillname ="火线救护" ,	skillid =410, skilllevel =9},
              {id=12230320,  levelmin = 97, skillname ="震荡雷" ,	  skillid =411, skilllevel =9},
              {id=12230321,  levelmin = 99, skillname ="暴击增强" ,	skillid =412, skilllevel =9},
              {id=12230322,  levelmin = 91, skillname ="远攻增强" ,	skillid =413, skilllevel =9},
              {id=12230323,  levelmin = 96, skillname ="命中增强" ,	skillid =414, skilllevel =9},
              {id=12230324,  levelmin = 95, skillname ="霰光雷" ,	  skillid =417, skilllevel =9},
              {id=12230325,  levelmin = 98, skillname ="排子炮" ,	  skillid =418, skilllevel =9},
              {id=12230326,  levelmin = 98, skillname ="地网雷" ,	  skillid =421, skilllevel =9},
              {id=12230327,  levelmin = 92, skillname ="连珠炮" ,	  skillid =422, skilllevel =9},
              {id=12230328,  levelmin = 96, skillname ="一闪" ,	    skillid =423, skilllevel =9},
              {id=12230415,  levelmin = 97, skillname ="天之惩戒" ,	skillid =501, skilllevel =9},
              {id=12230416,  levelmin = 98, skillname ="风之惩戒" ,	skillid =502, skilllevel =9},
              {id=12230417,  levelmin = 97, skillname ="火之惩戒" ,	skillid =503, skilllevel =9},
              {id=12230418,  levelmin = 92, skillname ="末日审判" ,	skillid =505, skilllevel =9},
              {id=12230419,  levelmin = 96, skillname ="沉默箴言" ,	skillid =506, skilllevel =9},
              {id=12230420,  levelmin = 91, skillname ="禁锢箴言" ,	skillid =507, skilllevel =9},
              {id=12230421,  levelmin = 93, skillname ="神灯之光" ,	skillid =508, skilllevel =9},
              {id=12230422,  levelmin = 98, skillname ="玄石之盾" ,	skillid =509, skilllevel =9},
              {id=12230423,  levelmin = 95, skillname ="气定神闲" ,	skillid =510, skilllevel =9},
              {id=12230424,  levelmin = 94, skillname ="祷告之歌" ,	skillid =511, skilllevel =9},
              {id=12230425,  levelmin = 99, skillname ="幻影箴言" ,	skillid =512, skilllevel =9},
              {id=12230426,  levelmin = 99, skillname ="暴击增强" ,	skillid =513, skilllevel =9},
              {id=12230427,  levelmin = 91, skillname ="魔攻增强" ,	skillid =514, skilllevel =9},
              {id=12230428,  levelmin = 96, skillname ="闪避增强" ,	skillid =515, skilllevel =9},
              {id=12230515,  levelmin = 95, skillname ="烈犬之舞" ,	skillid =601, skilllevel =9},
              {id=12230516,  levelmin = 97, skillname ="黑鸦蛊惑" ,	skillid =602, skilllevel =9},
              {id=12230517,  levelmin = 91, skillname ="小巫医术" ,	skillid =604, skilllevel =9},
              {id=12230518,  levelmin = 92, skillname ="火凤之舞" ,	skillid =605, skilllevel =9},
              {id=12230519,  levelmin = 98, skillname ="回春之光" ,	skillid =606, skilllevel =9},
              {id=12230520,  levelmin = 99, skillname ="白蟒蛊惑" ,	skillid =609, skilllevel =9},
              {id=12230521,  levelmin = 93, skillname ="冥神附体" ,	skillid =610, skilllevel =9},
              {id=12230522,  levelmin = 94, skillname ="大巫医术" ,	skillid =611, skilllevel =9},
              {id=12230523,  levelmin = 98, skillname ="巫神之舞" ,	skillid =612, skilllevel =9},
              {id=12230524,  levelmin = 96, skillname ="智力增强" ,	skillid =613, skilllevel =9},
              {id=12230525,  levelmin = 91, skillname ="魔攻增强" ,	skillid =614, skilllevel =9},
              {id=12230526,  levelmin = 99, skillname ="韧性增强" ,	skillid =615, skilllevel =9},
              {id=12230527,  levelmin = 96, skillname ="石神附体" ,	skillid =616, skilllevel =9},
              {id=12230528,  levelmin = 97, skillname ="雪神附体" ,	skillid =617, skilllevel =9},
              {id=12230601,  levelmin = 71, skillname ="十字军冲杀", skillid =1107, skilllevel =8},
              {id=12230602,  levelmin = 76, skillname ="审判", skillid =1104, skilllevel =8},
              {id=12230603,  levelmin = 72, skillname ="十字军威慑", skillid =1106, skilllevel =8},
              {id=12230604,  levelmin = 74, skillname ="十字军穿刺", skillid =1108, skilllevel =8},
              {id=12230605,  levelmin = 71, skillname ="十字军之怒", skillid =1109, skilllevel =8},
              {id=12230606,  levelmin = 77, skillname ="裁决", skillid =1105, skilllevel =8},
              {id=12230607,  levelmin = 78, skillname ="光明祝福", skillid =1100, skilllevel =8},
              {id=12230608,  levelmin = 75, skillname ="光明圣盾", skillid =1101, skilllevel =8},
              {id=12230609,  levelmin = 79, skillname ="狂热", skillid =1103, skilllevel =8},
              {id=12230610,  levelmin = 73, skillname ="光明圣战", skillid =1102, skilllevel =8},
              {id=12230611,  levelmin = 76, skillname ="血量增强", skillid =1112, skilllevel =8},
              {id=12230612,  levelmin = 77, skillname ="力量增强", skillid =1113, skilllevel =8},
              {id=12230613,  levelmin = 78, skillname ="近攻增强", skillid =1111, skilllevel =8},
              {id=12230614,  levelmin = 79, skillname ="韧性增强", skillid =1110, skilllevel =8},
              {id=12230615,  levelmin = 91, skillname ="十字军冲杀", skillid =1107, skilllevel =9},
              {id=12230616,  levelmin = 96, skillname ="审判", skillid =1104, skilllevel =9},
              {id=12230617,  levelmin = 92, skillname ="十字军威慑", skillid =1106, skilllevel =9},
              {id=12230618,  levelmin = 94, skillname ="十字军穿刺", skillid =1108, skilllevel =9},
              {id=12230619,  levelmin = 91, skillname ="十字军之怒", skillid =1109, skilllevel =9},
              {id=12230620,  levelmin = 97, skillname ="裁决", skillid =1105, skilllevel =9},
              {id=12230621,  levelmin = 98, skillname ="光明祝福", skillid =1100, skilllevel =9},
              {id=12230622,  levelmin = 95, skillname ="光明圣盾", skillid =1101, skilllevel =9},
              {id=12230623,  levelmin = 99, skillname ="狂热", skillid =1103, skilllevel =9},
              {id=12230624,  levelmin = 93, skillname ="光明圣战", skillid =1102, skilllevel =9},
              {id=12230625,  levelmin = 96, skillname ="血量增强", skillid =1112, skilllevel =9},
              {id=12230626,  levelmin = 97, skillname ="力量增强", skillid =1113, skilllevel =9},
              {id=12230627,  levelmin = 98, skillname ="近攻增强", skillid =1111, skilllevel =9},
              {id=12230628,  levelmin = 99, skillname ="韧性增强", skillid =1110, skilllevel =9},
              {id=12230701,  levelmin = 77, skillname ="嗜血如命", skillid =1201, skilllevel =8},
              {id=12230702,  levelmin = 79, skillname ="乾坤大挪移", skillid =1202, skilllevel =8},
              {id=12230703,  levelmin = 76, skillname ="火光遍野", skillid =1211, skilllevel =8},
              {id=12230704,  levelmin = 75, skillname ="烈焰冲天", skillid =1207, skilllevel =8},
              {id=12230705,  levelmin = 72, skillname ="烽火连城", skillid =1208, skilllevel =8},
              {id=12230706,  levelmin = 76, skillname ="圣火熊熊", skillid =1205, skilllevel =8},
              {id=12230707,  levelmin = 71, skillname ="怒火燎原", skillid =1209, skilllevel =8},
              {id=12230708,  levelmin = 73, skillname ="无名业火", skillid =1206, skilllevel =8},
              {id=12230709,  levelmin = 71, skillname ="圣火盾", skillid =1200, skilllevel =8},
              {id=12230710,  levelmin = 74, skillname ="如火如荼", skillid =1204, skilllevel =8},
              {id=12230711,  levelmin = 78, skillname ="烟雾缭绕", skillid =1203, skilllevel =8},
              {id=12230712,  levelmin = 79, skillname ="暴击增强", skillid =1213, skilllevel =8},
              {id=12230713,  levelmin = 77, skillname ="力量增强", skillid =1214, skilllevel =8},
              {id=12230714,  levelmin = 78, skillname ="命中增强", skillid =1212, skilllevel =8},
              {id=12230715,  levelmin = 97, skillname ="嗜血如命", skillid =1201, skilllevel =9},
              {id=12230716,  levelmin = 99, skillname ="乾坤大挪移", skillid =1202, skilllevel =9},
              {id=12230717,  levelmin = 96, skillname ="火光遍野", skillid =1211, skilllevel =9},
              {id=12230718,  levelmin = 95, skillname ="烈焰冲天", skillid =1207, skilllevel =9},
              {id=12230719,  levelmin = 92, skillname ="烽火连城", skillid =1208, skilllevel =9},
              {id=12230720,  levelmin = 96, skillname ="圣火熊熊", skillid =1205, skilllevel =9},
              {id=12230721,  levelmin = 91, skillname ="怒火燎原", skillid =1209, skilllevel =9},
              {id=12230722,  levelmin = 93, skillname ="无名业火", skillid =1206, skilllevel =9},
              {id=12230723,  levelmin = 91, skillname ="圣火盾", skillid =1200, skilllevel =9},
              {id=12230724,  levelmin = 94, skillname ="如火如荼", skillid =1204, skilllevel =9},
              {id=12230725,  levelmin = 98, skillname ="烟雾缭绕", skillid =1203, skilllevel =9},
              {id=12230726,  levelmin = 99, skillname ="暴击增强", skillid =1213, skilllevel =9},
              {id=12230727,  levelmin = 97, skillname ="力量增强", skillid =1214, skilllevel =9},
              {id=12230728,  levelmin = 98, skillname ="命中增强", skillid =1212, skilllevel =9},
              {id=12230801,  levelmin = 78, skillname ="孤注一掷", skillid =1303, skilllevel =8},
              {id=12230802,  levelmin = 77, skillname ="趁虚而入", skillid =1304, skilllevel =8},
              {id=12230803,  levelmin = 71, skillname ="破魔箭", skillid =1310, skilllevel =8},
              {id=12230804,  levelmin = 77, skillname ="烈火夺命箭", skillid =1309, skilllevel =8},
              {id=12230805,  levelmin = 72, skillname ="瞬杀箭", skillid =1307, skilllevel =8},
              {id=12230806,  levelmin = 76, skillname ="八方箭雨", skillid =1308, skilllevel =8},
              {id=12230807,  levelmin = 73, skillname ="疾风烈火", skillid =1306, skilllevel =8},
              {id=12230808,  levelmin = 74, skillname ="身形如魅", skillid =1305, skilllevel =8},
              {id=12230809,  levelmin = 76, skillname ="敏捷增强", skillid =1313, skilllevel =8},
              {id=12230810,  levelmin = 71, skillname ="命中增强", skillid =1311, skilllevel =8},
              {id=12230811,  levelmin = 79, skillname ="闪避增强", skillid =1312, skilllevel =8},
              {id=12230812,  levelmin = 75, skillname ="无技可施", skillid =1300, skilllevel =8},
              {id=12230813,  levelmin = 78, skillname ="销声匿迹", skillid =1301, skilllevel =8},
              {id=12230814,  levelmin = 79, skillname ="寸步难行", skillid =1302, skilllevel =8},
              {id=12230815,  levelmin = 98, skillname ="孤注一掷", skillid =1303, skilllevel =9},
              {id=12230816,  levelmin = 97, skillname ="趁虚而入", skillid =1304, skilllevel =9},
              {id=12230817,  levelmin = 91, skillname ="破魔箭", skillid =1310, skilllevel =9},
              {id=12230818,  levelmin = 97, skillname ="烈火夺命箭", skillid =1309, skilllevel =9},
              {id=12230819,  levelmin = 92, skillname ="瞬杀箭", skillid =1307, skilllevel =9},
              {id=12230820,  levelmin = 96, skillname ="八方箭雨", skillid =1308, skilllevel =9},
              {id=12230821,  levelmin = 93, skillname ="疾风烈火", skillid =1306, skilllevel =9},
              {id=12230822,  levelmin = 94, skillname ="身形如魅", skillid =1305, skilllevel =9},
              {id=12230823,  levelmin = 96, skillname ="敏捷增强", skillid =1313, skilllevel =9},
              {id=12230824,  levelmin = 91, skillname ="命中增强", skillid =1311, skilllevel =9},
              {id=12230825,  levelmin = 99, skillname ="闪避增强", skillid =1312, skilllevel =9},
              {id=12230826,  levelmin = 95, skillname ="无技可施", skillid =1300, skilllevel =9},
              {id=12230827,  levelmin = 98, skillname ="销声匿迹", skillid =1301, skilllevel =9},
              {id=12230828,  levelmin = 99, skillname ="寸步难行", skillid =1302, skilllevel =9},
              {id=12230901,  levelmin = 77, skillname ="惊雷火", skillid =1407, skilllevel =8},
              {id=12230902,  levelmin = 71, skillname ="破甲", skillid =1400, skilllevel =8},
              {id=12230903,  levelmin = 74, skillname ="极速装填", skillid =1403, skilllevel =8},
              {id=12230904,  levelmin = 73, skillname ="临兵列阵", skillid =1406, skilllevel =8},
              {id=12230905,  levelmin = 79, skillname ="镇定自若", skillid =1404, skilllevel =8},
              {id=12230906,  levelmin = 77, skillname ="瞄准", skillid =1405, skilllevel =8},
              {id=12230907,  levelmin = 79, skillname ="闪避增强", skillid =1413, skilllevel =8},
              {id=12230908,  levelmin = 71, skillname ="远攻增强", skillid =1415, skilllevel =8},
              {id=12230909,  levelmin = 76, skillname ="敏捷增强", skillid =1414, skilllevel =8},
              {id=12230910,  levelmin = 75, skillname ="暗渡陈仓", skillid =1409, skilllevel =8},
              {id=12230911,  levelmin = 78, skillname ="轰天火", skillid =1410, skilllevel =8},
              {id=12230912,  levelmin = 78, skillname ="迷魂火", skillid =1401, skilllevel =8},
              {id=12230913,  levelmin = 72, skillname ="霹雳火", skillid =1408, skilllevel =8},
              {id=12230914,  levelmin = 76, skillname ="架射", skillid =1402, skilllevel =8},
              {id=12230915,  levelmin = 97, skillname ="惊雷火", skillid =1407, skilllevel =9},
              {id=12230916,  levelmin = 91, skillname ="破甲", skillid =1400, skilllevel =9},
              {id=12230917,  levelmin = 94, skillname ="极速装填", skillid =1403, skilllevel =9},
              {id=12230918,  levelmin = 93, skillname ="临兵列阵", skillid =1406, skilllevel =9},
              {id=12230919,  levelmin = 99, skillname ="镇定自若", skillid =1404, skilllevel =9},
              {id=12230920,  levelmin = 97, skillname ="瞄准", skillid =1405, skilllevel =9},
              {id=12230921,  levelmin = 99, skillname ="闪避增强", skillid =1413, skilllevel =9},
              {id=12230922,  levelmin = 91, skillname ="远攻增强", skillid =1415, skilllevel =9},
              {id=12230923,  levelmin = 96, skillname ="敏捷增强", skillid =1414, skilllevel =9},
              {id=12230924,  levelmin = 95, skillname ="暗渡陈仓", skillid =1409, skilllevel =9},
              {id=12230925,  levelmin = 98, skillname ="轰天火", skillid =1410, skilllevel =9},
              {id=12230926,  levelmin = 98, skillname ="迷魂火", skillid =1401, skilllevel =9},
              {id=12230927,  levelmin = 92, skillname ="霹雳火", skillid =1408, skilllevel =9},
              {id=12230928,  levelmin = 96, skillname ="架射", skillid =1402, skilllevel =9},
              {id=12231001,  levelmin = 77, skillname ="驱魔箴言", skillid =1508, skilllevel =8},
              {id=12231002,  levelmin = 78, skillname ="除魔诀", skillid =1507, skilllevel =8},
              {id=12231003,  levelmin = 77, skillname ="灭魔诀", skillid =1509, skilllevel =8},
              {id=12231004,  levelmin = 72, skillname ="天罚箴言", skillid =1510, skilllevel =8},
              {id=12231005,  levelmin = 76, skillname ="神恩祷言", skillid =1500, skilllevel =8},
              {id=12231006,  levelmin = 71, skillname ="冰封诅咒", skillid =1501, skilllevel =8},
              {id=12231007,  levelmin = 73, skillname ="苦修祷言", skillid =1506, skilllevel =8},
              {id=12231008,  levelmin = 78, skillname ="神佑", skillid =1503, skilllevel =8},
              {id=12231009,  levelmin = 75, skillname ="青蛙诅咒", skillid =1502, skilllevel =8},
              {id=12231010,  levelmin = 74, skillname ="圣音祷言", skillid =1504, skilllevel =8},
              {id=12231011,  levelmin = 76, skillname ="惩击箴言", skillid =1505, skilllevel =8},
              {id=12231012,  levelmin = 79, skillname ="命中增强", skillid =1513, skilllevel =8},
              {id=12231013,  levelmin = 71, skillname ="魔攻增强", skillid =1511, skilllevel =8},
              {id=12231014,  levelmin = 79, skillname ="全属增强", skillid =1512, skilllevel =8},
              {id=12231015,  levelmin = 97, skillname ="驱魔箴言", skillid =1508, skilllevel =9},
              {id=12231016,  levelmin = 98, skillname ="除魔诀", skillid =1507, skilllevel =9},
              {id=12231017,  levelmin = 97, skillname ="灭魔诀", skillid =1509, skilllevel =9},
              {id=12231018,  levelmin = 92, skillname ="天罚箴言", skillid =1510, skilllevel =9},
              {id=12231019,  levelmin = 96, skillname ="神恩祷言", skillid =1500, skilllevel =9},
              {id=12231020,  levelmin = 91, skillname ="冰封诅咒", skillid =1501, skilllevel =9},
              {id=12231021,  levelmin = 93, skillname ="苦修祷言", skillid =1506, skilllevel =9},
              {id=12231022,  levelmin = 98, skillname ="神佑", skillid =1503, skilllevel =9},
              {id=12231023,  levelmin = 95, skillname ="青蛙诅咒", skillid =1502, skilllevel =9},
              {id=12231024,  levelmin = 94, skillname ="圣音祷言", skillid =1504, skilllevel =9},
              {id=12231025,  levelmin = 96, skillname ="惩击箴言", skillid =1505, skilllevel =9},
              {id=12231026,  levelmin = 99, skillname ="命中增强", skillid =1513, skilllevel =9},
              {id=12231027,  levelmin = 91, skillname ="魔攻增强", skillid =1511, skilllevel =9},
              {id=12231028,  levelmin = 99, skillname ="全属增强", skillid =1512, skilllevel =9},
              {id=12231101,  levelmin = 75, skillname ="巨熊护法", skillid =1600, skilllevel =8},
              {id=12231102,  levelmin = 71, skillname ="断灭咒", skillid =1602, skilllevel =8},
              {id=12231103,  levelmin = 76, skillname ="梵音咒", skillid =1608, skilllevel =8},
              {id=12231104,  levelmin = 76, skillname ="神獒护法", skillid =1601, skilllevel =8},
              {id=12231105,  levelmin = 77, skillname ="大悲咒", skillid =1604, skilllevel =8},
              {id=12231106,  levelmin = 78, skillname ="还生咒", skillid =1607, skilllevel =8},
              {id=12231107,  levelmin = 73, skillname ="浮屠咒", skillid =1605, skilllevel =8},
              {id=12231108,  levelmin = 74, skillname ="移魂咒", skillid =1603, skilllevel =8},
              {id=12231109,  levelmin = 77, skillname ="伏魔咒", skillid =1609, skilllevel =8},
              {id=12231110,  levelmin = 78, skillname ="智力增强", skillid =1612, skilllevel =8},
              {id=12231111,  levelmin = 76, skillname ="体质增强", skillid =1611, skilllevel =8},
              {id=12231112,  levelmin = 76, skillname ="免疫增强", skillid =1613, skilllevel =8},
              {id=12231113,  levelmin = 76, skillname ="金刚咒", skillid =1606, skilllevel =8},
              {id=12231114,  levelmin = 74, skillname ="急兵咒", skillid =1610, skilllevel =8},
              {id=12231115,  levelmin = 95, skillname ="巨熊护法", skillid =1600, skilllevel =9},
              {id=12231116,  levelmin = 91, skillname ="断灭咒", skillid =1602, skilllevel =9},
              {id=12231117,  levelmin = 96, skillname ="梵音咒", skillid =1608, skilllevel =9},
              {id=12231118,  levelmin = 96, skillname ="神獒护法", skillid =1601, skilllevel =9},
              {id=12231119,  levelmin = 97, skillname ="大悲咒", skillid =1604, skilllevel =9},
              {id=12231120,  levelmin = 98, skillname ="还生咒", skillid =1607, skilllevel =9},
              {id=12231121,  levelmin = 93, skillname ="浮屠咒", skillid =1605, skilllevel =9},
              {id=12231122,  levelmin = 94, skillname ="移魂咒", skillid =1603, skilllevel =9},
              {id=12231123,  levelmin = 97, skillname ="伏魔咒", skillid =1609, skilllevel =9},
              {id=12231124,  levelmin = 98, skillname ="智力增强", skillid =1612, skilllevel =9},
              {id=12231125,  levelmin = 96, skillname ="体质增强", skillid =1611, skilllevel =9},
              {id=12231126,  levelmin = 96, skillname ="免疫增强", skillid =1613, skilllevel =9},
              {id=12231127,  levelmin = 96, skillname ="金刚咒", skillid =1606, skilllevel =9},
              {id=12231128,  levelmin = 94, skillname ="急兵咒", skillid =1610, skilllevel =9},

						
					}



--需要的等级


--**********************************
--事件交互入口
--**********************************
function x430011_ProcEventEntry( sceneId, selfId, bagIndex )
-- 不需要这个接口，但要保留空函数
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x430011_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end

--**********************************
--直接取消效果：
--系统会直接调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：已经取消对应效果，不再执行后续操作；返回0：没有检测到相关效果，继续执行。
--**********************************
function x430011_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

--**********************************
--条件检测入口：
--系统会在技能检测的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：条件检测通过，可以继续执行；返回0：条件检测失败，中断后续执行。
--**********************************
function x430011_OnConditionCheck( sceneId, selfId )
	
	--校验使用的物品
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x430011_OnDeplete( sceneId, selfId )
	
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--只会执行一次入口：
--聚气和瞬发技能会在消耗完成后调用这个接口（聚气结束并且各种条件都满足的时候），而引导
--技能也会在消耗完成后调用这个接口（技能的一开始，消耗成功执行之后）。
--返回1：处理成功；返回0：处理失败。
--注：这里是技能生效一次的入口
--**********************************
function x430011_OnActivateOnce( sceneId, selfId, impactId )

	local bagIndex = GetBagIndexOfUsedItem(sceneId, selfId)

	local itemid = GetItemIDByIndexInBag(sceneId, selfId, bagIndex)

	
	local nIndex =0

	local bFind = 0

	for i,item in x430011_g_itemlist do
		nIndex = nIndex+1
		if item.id == itemid then
			bFind =1
			break
		end
	end

	if bFind<=0 then
		return
	end

	local level_min = x430011_g_itemlist[nIndex].levelmin
	local skill_name = x430011_g_itemlist[nIndex].skillname
	local skill_id = x430011_g_itemlist[nIndex].skillid
	local skill_level = x430011_g_itemlist[nIndex].skilllevel
	
	
	
	local nLevel = GetLevel(sceneId, selfId)

	if nLevel<level_min then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("你的等级不足%d,不能学习技能",level_min))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	

	

	if HaveSkill(sceneId, selfId,skill_id)<=0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"你没有学习"..skill_name.."技能，无法使用该技能书")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local nCurrentSkillLevel = GetHumanSkillLevel(sceneId, selfId,skill_id)


	if nCurrentSkillLevel<skill_level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("你没有学习%d级"..skill_name.."技能，无法使用该技能书",skill_level))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	elseif nCurrentSkillLevel>skill_level then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("你已经学习过%d级"..skill_name.."技能",skill_level+1))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local nLogResult =0;

	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		
		local nRet = HumanSkillLevelUp(sceneId, selfId,skill_id,skill_level+1)

		if nRet > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("已学习%d级"..skill_name.."技能",skill_level+1))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			nLogResult = 1
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("学习%d级"..skill_name.."技能失败",skill_level+1))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)

			nLogResult = 2
			
		end

		--写日志
		local msg=format("skill book:%d,%s,%d,%d,%d",itemid,GetName(sceneId,selfId), GetPlayerGUID( sceneId,selfId ), nLogResult,nCurrentSkillLevel)
		WriteLog(1,msg)

		

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"使用物品异常！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		
	end

	


	

end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x430011_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

