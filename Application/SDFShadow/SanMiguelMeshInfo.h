#pragma once
#include "sdfUtil.h"
#include "SDF_Constant.h"

MeshInfo opaqueMeshInfos[] = {
    { "twosided_superthin_innerfloor_01", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "twosided_triplethin_hugewall_02", MATERIAL_FLAG_TWO_SIDED, 0.8f },
    { "twosided_triplethin_hugewall_01", MATERIAL_FLAG_TWO_SIDED, 0.8f },
    { "balcony_01", MATERIAL_FLAG_NONE, 0.0f },
    { "outerfloor_01", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_05", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_06", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_07", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_11", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_10", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_09", MATERIAL_FLAG_NONE, 0.0f },
    { "indoortable_03", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_01", MATERIAL_FLAG_NONE, 0.0f },
    { "outdoortable_03", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_02", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_04", MATERIAL_FLAG_NONE, 0.0f },
    { "outdoortable_07", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_02", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_15", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_14", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_13", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_12", MATERIAL_FLAG_NONE, 0.0f },
    { "outdoortable_08", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_10", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_06", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_05", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_09", MATERIAL_FLAG_NONE, 0.0f },
    { "outertable_11", MATERIAL_FLAG_NONE, 0.0f },
    { "uppertable_04", MATERIAL_FLAG_NONE, 0.0f },
    { "uppertable_03", MATERIAL_FLAG_NONE, 0.0f },
    { "uppertable_01", MATERIAL_FLAG_NONE, 0.0f },
    { "uppertable_02", MATERIAL_FLAG_NONE, 0.0f },
    { "opendoor_01", MATERIAL_FLAG_NONE, 0.0f },
    { "opendoor_02", MATERIAL_FLAG_NONE, 0.0f },
    { "indoortable_01", MATERIAL_FLAG_NONE, 0.0f },
    { "indoortable_05", MATERIAL_FLAG_NONE, 0.0f },
    { "indoortable_04", MATERIAL_FLAG_NONE, 0.0f },
    { "indoortable_02", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_01", MATERIAL_FLAG_NONE, 0.0f },
    { "waterpool_01", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_01", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_04", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_05", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_06", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_10", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_09", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_08", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_07", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_02", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_12", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_03", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_thin_leavesbasket_01", MATERIAL_FLAG_TWO_SIDED, 0.15f },
    { "twosided_kinda_double_combinedoutdoorchairs_01", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "gargoyle_04", MATERIAL_FLAG_NONE, 0.0f },
    { "gargoyle_05", MATERIAL_FLAG_NONE, 0.0f },
    { "gargoyle_02", MATERIAL_FLAG_NONE, 0.0f },
    { "gargoyle_06", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_kinda_double_outdoorchairs_02", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_indoorchairs_02", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_thin_double_indoorchairs_03", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.15f },
    { "twosided_thin_double_indoorchairs_04", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.15f },
    { "twosided_kinda_double_indoorchairs_05", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_indoorchairs_06", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "double_upperchairs_01", MATERIAL_FLAG_NONE, 0.0f },
    { "longpillar_11", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_thin_leavesbasket_02", MATERIAL_FLAG_TWO_SIDED, 0.15f },
    { "twosided_kinda_double_outdoorchairs_01", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_04", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "double_upperchairs_02", MATERIAL_FLAG_NONE, 0.0f },
    { "double_upperchairs_03", MATERIAL_FLAG_NONE, 0.0f },
    { "double_upperchairs_04", MATERIAL_FLAG_NONE, 0.0f },
    { "doorwall_01", MATERIAL_FLAG_NONE, 0.0f },
    { "doorwall_02", MATERIAL_FLAG_NONE, 0.0f },
    { "underledge_01", MATERIAL_FLAG_NONE, 0.0f },
    { "underceil_01", MATERIAL_FLAG_NONE, 0.0f },
    { "underceil_02", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_kinda_double_indoorchairs_07", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "hugewallfront_01", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_kinda_metalLedges_02", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_07", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_01", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_05", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_03", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_04", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_06", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_double_outdoorchairs_06", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_05", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_metalLedges_08", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_metalLedges_09", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_doorwall_03", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "twosided_kinda_doorwall_04", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "myinnerfloor_01", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_kinda_double_outdoorchairs_07", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_08", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "mywall_01", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_kinda_double_outdoorchairs_09", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_10", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_11", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_12", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_13", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_14", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_double_outdoorchairs_15", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.09f },
    { "twosided_kinda_metalLedges_10", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "curvepillar_12", MATERIAL_FLAG_NONE, 0.0f },
    { "curvepillar_08", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_superthin_innerhall_01", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "doorwall_06", MATERIAL_FLAG_NONE, 0.0f },
    { "doorwall_05", MATERIAL_FLAG_NONE, 0.0f },
    { "double_doorwall_07", MATERIAL_FLAG_DOUBLE_VOXEL_SIZE, 0.0f },
    { "twosided_kinda_basketonly_01", MATERIAL_FLAG_TWO_SIDED, 0.09f },
    { "backmuros_01", MATERIAL_FLAG_NONE, 0.0f },
    { "shortceil_01", MATERIAL_FLAG_NONE, 0.0f },
    { "shortceil_02", MATERIAL_FLAG_NONE, 0.0f },
    { "shortceil_03", MATERIAL_FLAG_NONE, 0.0f },
    { "cap03", MATERIAL_FLAG_NONE, 0.0f },
    { "cap01", MATERIAL_FLAG_NONE, 0.0f },
    { "cap02", MATERIAL_FLAG_NONE, 0.0f },
    { "cap04", MATERIAL_FLAG_NONE, 0.0f }
};

MeshInfo flagsMeshInfos[] = {
    { "gargoyle_08", MATERIAL_FLAG_NONE, 0.0f },
    { "twosided_superthin_forgeflags_01", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "twosided_superthin_forgeflags_02", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "twosided_superthin_forgeflags_04", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "twosided_superthin_forgeflags_03", MATERIAL_FLAG_TWO_SIDED, 0.5f },
    { "gargoyle_01", MATERIAL_FLAG_NONE, 0.0f },
    { "gargoyle_07", MATERIAL_FLAG_NONE, 0.0f },
    { "gargoyle_03", MATERIAL_FLAG_NONE, 0.0f },
};

MeshInfo alphaTestedMeshInfos[] = {
    // group 0
    { "twosided_thin_alphatested_smallLeaves04_beginstack0", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "flower0339_continuestack0", MATERIAL_FLAG_NONE, 0.0f },
    { "stem01_continuestack0", MATERIAL_FLAG_NONE, 0.0f },
    { "basket01_continuestack0", MATERIAL_FLAG_NONE, 0.0f },
    // group 1
    { "twosided_thin_alphatested_smallLeaves04_beginstack1", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "stem_continuestack1", MATERIAL_FLAG_NONE, 0.0f },
    { "smallLeaves019_alphatested_continuestack1", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "smallLeaves0377_alphatested_continuestack1", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack1", MATERIAL_FLAG_NONE, 0.0f },
    { "rose00_alphatested_continuestack1", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    // group 2
    { "twosided_thin_alphatested_smallLeaves00_beginstack2", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves023_continuestack2", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "stem02_continuestack2", MATERIAL_FLAG_NONE, 0.0f },
    { "alphatested_flower0304_continuestack2", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "stem03_continuestack2", MATERIAL_FLAG_NONE, 0.0f },
    { "basket02_continuestack2", MATERIAL_FLAG_NONE, 0.0f },
    // group 3
    { "twosided_thin_alphatested_smallLeaves04_beginstack3", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "twosided_thin_alphatested_smallLeaves09_continuestack3", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket_continuestack3", MATERIAL_FLAG_NONE, 0.0f },
    // group 4
    { "twosided_thin_alphatested_smallLeaves022_beginstack4", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket_continuestack4", MATERIAL_FLAG_NONE, 0.0f },
    // group 5
    { "twosided_thin_alphatested_smallLeaves013_beginstack5", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves012_continuestack5", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves020_continuestack5", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_twosided_thin_smallLeaves07_continuestack5", MATERIAL_FLAG_ALPHA_TESTED | MATERIAL_FLAG_TWO_SIDED, 0.15f },
    { "alphatested_twosided_thin_smallLeaves05_continuestack5", MATERIAL_FLAG_ALPHA_TESTED | MATERIAL_FLAG_TWO_SIDED, 0.15f },
    { "twosided_thin_alphatested_floor1_continuestack5", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack5", MATERIAL_FLAG_NONE, 0.0f },
    // group 6
    { "twosided_thin_alphatested_smallLeaves023_beginstack6", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves0300_continuestack6", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves016_continuestack6", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0341_continuestack6", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack6", MATERIAL_FLAG_NONE, 0.0f },
    // group 7
    { "twosided_thin_alphatested_smallLeaves014_beginstack7", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves015_continuestack7", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack7", MATERIAL_FLAG_NONE, 0.0f },
    // group 8
    { "twosided_thin_alphatested_smallLeaves027_beginstack8", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0343_continuestack8", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves018_continuestack8", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack8", MATERIAL_FLAG_NONE, 0.0f },
    // group 9
    { "twosided_thin_alphatested_smallLeaves0380_beginstack9", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0338_continuestack9", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "bakset01_continuestack9", MATERIAL_FLAG_NONE, 0.0f },
    // group 10
    { "twosided_thin_alphatested_smallLeaves00_beginstack10", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0304_continuestack10", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack10", MATERIAL_FLAG_NONE, 0.0f },
    // group 11
    { "twosided_thin_double_alphatested__group146_beginstack11", MATERIAL_FLAG_ALL, 0.15f },
    { "alphatested_group147_continuestack11", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "branch_group145_continuestack11", MATERIAL_FLAG_NONE, 0.0f },
    // group 12
    { "twosided_superthin_alphatested_double_treeLeaves04_beginstack12", MATERIAL_FLAG_ALL, 0.5f },
    { "alphatested_treeLeaves00_continuestack12", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_treeLeaves02_continuestack12", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_treeLeaves05_continuestack12", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    // group 13
    { "twosided_superthin_alphatested_double_treeLeaves08_beginstack13", MATERIAL_FLAG_ALL, 0.5f },
    { "alphatested_treeLeaves05_continuestack13", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_treeLeaves07_continuestack13", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    // group 14
    { "twosided_superthin_alphatested_double_treeLeaves03_beginstack14", MATERIAL_FLAG_ALL, 0.5f },
    { "alphatested_treeLeaves01_continuestack14", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_treeLeaves06_continuestack14", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    // group 15
    { "twosided_thin_alphatested_smallLeaves02_beginstack15", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves08_continuestack15", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack15", MATERIAL_FLAG_NONE, 0.0f },
    // group 16
    { "twosided_thin_double_alphatested_smallLeaves019_beginstack16", MATERIAL_FLAG_ALL, 0.15f },
    { "alphatested_flower0343_continuestack16", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves018_continuestack16", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves0377_continuestack16", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_rose00_continuestack16", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack16", MATERIAL_FLAG_NONE, 0.0f },
    // group 17
    { "twosided_thin_alphatested_smallLeaves0380_beginstack17", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0342_continuestack17", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves07_continuestack17", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves05_continuestack17", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_floor1_continuestack17", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0338_continuestack17", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack17", MATERIAL_FLAG_NONE, 0.0f },
    // group 18
    { "twosided_thin_alphatested_smallLeaves06_beginstack18", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves0378_continuestack18", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0344_continuestack18", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0340_continuestack18", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack18", MATERIAL_FLAG_NONE, 0.0f },
    // group 19
    { "twosided_thin_double_alphatested_smallLeaves00_beginstack19", MATERIAL_FLAG_ALL, 0.15f },
    { "alphatested_smallLeaves016_continuestack19", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0341_continuestack19", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves017_continuestack19", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves021_continuestack19", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0304_continuestack19", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack19", MATERIAL_FLAG_NONE, 0.0f },
    // group 20
    { "twosided_thin_alphatested_smallLeaves024_beginstack20", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack20", MATERIAL_FLAG_NONE, 0.0f },
    // group 21
    { "twosided_thin_alphatested_smallLeaves010_beginstack21", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack21", MATERIAL_FLAG_NONE, 0.0f },
    // group 22
    { "twosided_thin_alphatested_smallLeaves01_beginstack22", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack22", MATERIAL_FLAG_NONE, 0.0f },
    // group 23
    { "twosided_thin_alphatested_smallLeaves04_beginstack23", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack23", MATERIAL_FLAG_NONE, 0.0f },
    // group 24
    { "twosided_thin_alphatested_smallLeaves024_beginstack24", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack24", MATERIAL_FLAG_NONE, 0.0f },
    // group 25
    { "twosided_thin_alphatested_smallLeaves00_beginstack25", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0304_continuestack25", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack25", MATERIAL_FLAG_NONE, 0.0f },
    // group 26
    { "twosided_thin_alphatested_smallLeaves00_beginstack26", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves023_continuestack26", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0304_continuestack26", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack26", MATERIAL_FLAG_NONE, 0.0f },
    // group 27
    { "twosided_thin_double_alphatested_smallLeaves025_beginstack27", MATERIAL_FLAG_ALL, 0.15f },
    { "alphatested_smallLeaves011_continuestack27", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves021_continuestack27", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves017_continuestack27", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves08_continuestack27", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack27", MATERIAL_FLAG_NONE, 0.0f },
    // group 28
    { "twosided_thin_alphatested_smallLeaves0377_beginstack28", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_rose00_continuestack28", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack28", MATERIAL_FLAG_NONE, 0.0f },
    // group 29
    { "twosided_thin_double_alphatested_smallLeaves00_beginstack29", MATERIAL_FLAG_ALL, 0.15f },
    { "alphatested_smallLeaves026_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower01_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves09_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves013_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_smallLeaves023_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "alphatested_flower0304_continuestack29", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack29", MATERIAL_FLAG_NONE, 0.0f },
    // group 30
    { "twosided_thin_alphatested_smallLeaves027_beginstack30", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "flower00_continuestack30", MATERIAL_FLAG_NONE, 0.0f },
    { "basket01_continuestack30", MATERIAL_FLAG_NONE, 0.0f },
    // group 31
    { "twosided_thin_alphatested_smallLeaves013_beginstack31", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack31", MATERIAL_FLAG_NONE, 0.0f },
    // group 32
    { "twosided_thin_alphatested_smallLeaves04_beginstack32", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack32", MATERIAL_FLAG_NONE, 0.0f },
    // group 33
    { "twosided_thin_alphatested_smallLeaves00_beginstack33", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_flower0304_continuestack33", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack33", MATERIAL_FLAG_NONE, 0.0f },
    // group 34
    { "twosided_thin_alphatested_smallLeaves0381_beginstack34", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack34", MATERIAL_FLAG_NONE, 0.0f },
    // group 35
    { "twosided_thin_alphatested_smallLeaves0379_beginstack35", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "basket01_continuestack35", MATERIAL_FLAG_NONE, 0.0f },
    // group 36
    { "twosided_thin_alphatested_smallLeaves021_beginstack36", MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED, 0.15f },
    { "alphatested_smallLeaves017_continuestack36", MATERIAL_FLAG_ALPHA_TESTED, 0.0f },
    { "basket01_continuestack36", MATERIAL_FLAG_NONE, 0.0f }
};

uint32_t alphaTestedGroupSizes[] = { 
    4, 6, 6, 3, 2, 7, 5, 3, 4, 3, 3, 3, 4, 3, 3, 3, 6, 7, 5,
    7, 2, 2, 2, 2, 2, 3, 4, 6, 3, 8, 3, 2, 2, 3, 2, 2, 3 };

uint32_t alphaTestedMeshIndices[] = {
    30,  12,  31,  32,                      // group 0
    34,  35,  36,  37,  38,  39,            // group 1
    40,  41,  42,  43,  44,  45,            // group 2
    47,  50,  51,                           // group 3
    9,   52,                                // group 4
    53,  6,   25,  55,  57,  59,  60,       // group 5
    61,  14,  63,  65,  66,                 // group 6
    0,   7,   67,                           // group 7
    69,  71,  73,  75,                      // group 8
    77,  79,  80,                           // group 9
    81,  84,  86,                           // group 10
    2,   26,  28,                           // group 11
    33,  5,   16,  85,                      // group 12
    24,  20,  27,                           // group 13
    13,  17,  19,                           // group 14
    83,  82,  87,                           // group 15
    46,  70,  72,  88,  89,  90,            // group 16
    76,  1,   54,  56,  58,  78,  91,       // group 17
    11,  3,   18,  29,  92,                 // group 18
    95,  62,  64,  93,  94,  96,  97,       // group 19
    99,  100,                               // group 20
    23,  101,                               // group 21
    10,  102,                               // group 22
    104, 105,                               // group 23
    98,  106,                               // group 24
    107, 108, 109,                          // group 25
    111, 110, 112, 113,                     // group 26
    15,  21,  117, 118, 119, 120,           // group 27
    114, 115, 116,                          // group 28
    125, 4,   8,   49,  122, 123, 124, 126, // group 29
    68,  74,  127,                          // group 30
    121, 48,                                // group 31
    103, 129,                               // group 32
    128, 130, 131,                          // group 33
    22,  132,                               // group 34
    133, 134,                               // group 35
    135, 136, 137                           // group 36
};