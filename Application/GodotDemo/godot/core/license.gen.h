/* THIS FILE IS GENERATED DO NOT EDIT */
#ifndef LICENSE_GEN_H
#define LICENSE_GEN_H
const char *const GODOT_LICENSE_TEXT =
		"Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md).\n"
		"Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.\n"
		"\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
		"of this software and associated documentation files (the \042Software\042), to deal\n"
		"in the Software without restriction, including without limitation the rights\n"
		"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
		"copies of the Software, and to permit persons to whom the Software is\n"
		"furnished to do so, subject to the following conditions:\n"
		"\n"
		"The above copyright notice and this permission notice shall be included in all\n"
		"copies or substantial portions of the Software.\n"
		"\n"
		"THE SOFTWARE IS PROVIDED \042AS IS\042, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
		"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
		"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
		"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
		"SOFTWARE.\n";

struct ComponentCopyrightPart {
	const char *license;
	const char *const *files;
	const char *const *copyright_statements;
	int file_count;
	int copyright_count;
};

struct ComponentCopyright {
	const char *name;
	const ComponentCopyrightPart *parts;
	int part_count;
};

const char *const COPYRIGHT_INFO_DATA[] = {
	"*",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./icon.png",
	"./icon.svg",
	"./logo.png",
	"./logo.svg",
	"2017, Andrea Calabr\303\263",
	"./core/math/convex_hull.cpp",
	"./core/math/convex_hull.h",
	"2011, Ole Kniemeyer, MAXON, www.maxon.net",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./modules/godot_physics_3d/gjk_epa.cpp",
	"./modules/godot_physics_3d/joints/godot_generic_6dof_joint_3d.cpp",
	"./modules/godot_physics_3d/joints/godot_generic_6dof_joint_3d.h",
	"./modules/godot_physics_3d/joints/godot_hinge_joint_3d.cpp",
	"./modules/godot_physics_3d/joints/godot_hinge_joint_3d_sw.h",
	"./modules/godot_physics_3d/joints/godot_jacobian_entry_3d_sw.h",
	"./modules/godot_physics_3d/joints/godot_pin_joint_3d.cpp",
	"./modules/godot_physics_3d/joints/godot_pin_joint_3d.h",
	"./modules/godot_physics_3d/joints/godot_slider_joint_3d.cpp",
	"./modules/godot_physics_3d/joints/godot_slider_joint_3d.h",
	"./modules/godot_physics_3d/godot_soft_body_3d.cpp",
	"./modules/godot_physics_3d/godot_soft_body_3d.h",
	"./modules/godot_physics_3d/godot_shape_3d.cpp",
	"./modules/godot_physics_3d/godot_shape_3d.h",
	"2003-2008, Erwin Coumans",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./modules/godot_physics_3d/joints/godot_cone_twist_joint_3d.cpp",
	"./modules/godot_physics_3d/joints/godot_cone_twist_joint_3d.h",
	"2007, Starbreeze Studios",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./modules/godot_physics_2d/godot_joints_2d.cpp",
	"2007, Scott Lembcke",
	"./modules/godot_physics_3d/godot_collision_solver_3d_sat.cpp",
	"2001-2003, Russell L. Smith, Alen Ladavac, Nguyen Binh",
	"./modules/lightmapper_rd/lm_compute.glsl",
	"2020, Manuel Prandini",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./platform/android/java/editor/src/main/java/com/android/*",
	"./platform/android/java/lib/aidl/com/android/*",
	"./platform/android/java/lib/res/layout/status_bar_ongoing_event_progress_bar.xml",
	"./platform/android/java/lib/src/com/google/android/*",
	"./platform/android/java/lib/src/org/godotengine/godot/input/InputManagerCompat.java",
	"./platform/android/java/lib/src/org/godotengine/godot/input/InputManagerV16.java",
	"2008-2016, The Android Open Source Project",
	"2002, Google, Inc.",
	"./platform/android/java/lib/src/org/godotengine/godot/utils/ProcessPhoenix.java",
	"2015, Jake Wharton",
	"./scene/animation/easing_equations.h",
	"2001, Robert Penner",
	"2014-present, Godot Engine contributors",
	"2007-2014, Juan Linietsky, Ariel Manzur",
	"./servers/rendering/renderer_rd/shaders/ss_effects_downsample.glsl",
	"./servers/rendering/renderer_rd/shaders/ssao_blur.glsl",
	"./servers/rendering/renderer_rd/shaders/ssao_importance_map.glsl",
	"./servers/rendering/renderer_rd/shaders/ssao_interleave.glsl",
	"./servers/rendering/renderer_rd/shaders/ssao.glsl",
	"./servers/rendering/renderer_rd/shaders/ssil_blur.glsl",
	"./servers/rendering/renderer_rd/shaders/ssil_importance_map.glsl",
	"./servers/rendering/renderer_rd/shaders/ssil_interleave.glsl",
	"./servers/rendering/renderer_rd/shaders/ssil.glsl",
	"2016, Intel Corporation",
	"./servers/rendering/renderer_rd/shaders/taa_resolve.glsl",
	"2016, Panos Karabelas",
	"./thirdparty/amd-fsr/",
	"2021, Advanced Micro Devices, Inc.",
	"./thirdparty/amd-fsr2/",
	"2022-2023, Advanced Micro Devices, Inc.",
	"./thirdparty/angle/",
	"2018, The ANGLE Project Authors.",
	"./thirdparty/astcenc/",
	"2011-2024, Arm Limited",
	"./thirdparty/basis_universal/",
	"2022, Binomial LLC.",
	"./thirdparty/brotli/",
	"2009, 2010, 2013-2016 by the Brotli Authors.",
	"./thirdparty/certs/ca-certificates.crt",
	"Mozilla Contributors",
	"./thirdparty/clipper2/",
	"2010-2023, Angus Johnson",
	"./thirdparty/cvtt/",
	"2018, Eric Lasota",
	"2018, Microsoft Corp.",
	"./thirdparty/d3d12ma/",
	"2019-2022 Advanced Micro Devices, Inc.",
	"./thirdparty/directx_headers/",
	"Microsoft Corporation",
	"./thirdparty/doctest/",
	"2016-2023, Viktor Kirilov",
	"./thirdparty/embree/",
	"2009-2021 Intel Corporation",
	"./thirdparty/enet/",
	"2002-2024, Lee Salzman",
	"./thirdparty/etcpak/",
	"2013-2022, Bartosz Taudul",
	"./thirdparty/fonts/DroidSans*.woff2",
	"2008, The Android Open Source Project",
	"./thirdparty/fonts/JetBrainsMono_Regular.woff2",
	"2020, JetBrains s.r.o.",
	"./thirdparty/fonts/NotoSans*.woff2",
	"2012, Google Inc.",
	"./thirdparty/freetype/",
	"1996-2023, David Turner, Robert Wilhelm, and Werner Lemberg.",
	"./thirdparty/glad/",
	"2013-2022, David Herberth",
	"2013-2020, The Khronos Group Inc.",
	"./thirdparty/glslang/",
	"2015-2020, Google, Inc.",
	"2014-2020, The Khronos Group Inc",
	"2002, NVIDIA Corporation.",
	"./thirdparty/graphite/",
	"2010, SIL International",
	"./thirdparty/harfbuzz/",
	"2010-2022, Google, Inc.",
	"2015-2020, Ebrahim Byagowi",
	"2019,2020, Facebook, Inc.",
	"2012, 2015, Mozilla Foundation",
	"2011, Codethink Limited",
	"2008, 2010, Nokia Corporation and/or its subsidiary(-ies)",
	"2009, Keith Stribley",
	"2011, Martin Hosken and SIL International",
	"2007, Chris Wilson",
	"2005-2006, 2020-2023, Behdad Esfahbod",
	"2004, 2007-2010, 2013, 2021-2023, Red Hat, Inc.",
	"1998-2005, David Turner and Werner Lemberg",
	"2016, Igalia, S.L.",
	"2022, Matthias Clasen",
	"2018, 2021, Khaled Hosny",
	"2018-2020, Adobe, Inc.",
	"2013-2015, Alexei Podtelezhnikov",
	"./thirdparty/icu4c/",
	"2016-2024, Unicode, Inc.",
	"./thirdparty/jpeg-compressor/",
	"2012, Rich Geldreich",
	"./thirdparty/libbacktrace/",
	"2012-2021, Free Software Foundation, Inc.",
	"./thirdparty/libktx/",
	"2013-2020, Mark Callow",
	"2010-2020 The Khronos Group, Inc.",
	"./thirdparty/libogg/",
	"2002, Xiph.org Foundation",
	"./thirdparty/libvorbis/",
	"2002-2015, Xiph.org Foundation",
	"./thirdparty/libpng/",
	"1995-2024, The PNG Reference Library Authors.",
	"2018-2024, Cosmin Truta.",
	"2000-2002, 2004, 2006-2018 Glenn Randers-Pehrson.",
	"1996-1997, Andreas Dilger.",
	"1995-1996, Guy Eric Schalnat, Group 42, Inc.",
	"./thirdparty/libtheora/",
	"2002-2009, Xiph.org Foundation",
	"./thirdparty/libwebp/",
	"2010, Google Inc.",
	"./thirdparty/mbedtls/",
	"The Mbed TLS Contributors",
	"./thirdparty/meshoptimizer/",
	"2016-2023, Arseny Kapoulkine",
	"./thirdparty/mingw-std-threads/",
	"2016, Mega Limited",
	"./thirdparty/minimp3/",
	"lieff",
	"./thirdparty/miniupnpc/",
	"2005-2024, Thomas Bernard",
	"./thirdparty/minizip/",
	"1998-2010, Gilles Vollant",
	"2007-2008, Even Rouault",
	"2009-2010, Mathias Svensson",
	"./thirdparty/misc/cubemap_coeffs.h",
	"2016, Activision Publishing, Inc.",
	"./thirdparty/misc/fastlz.c",
	"./thirdparty/misc/fastlz.h",
	"2005-2020, Ariya Hidayat",
	"./thirdparty/misc/ifaddrs-android.cc",
	"./thirdparty/misc/ifaddrs-android.h",
	"2012-2013, Google Inc.",
	"./thirdparty/misc/mikktspace.c",
	"./thirdparty/misc/mikktspace.h",
	"2011, Morten S. Mikkelsen",
	"./thirdparty/misc/ok_color.h",
	"./thirdparty/misc/ok_color_shader.h",
	"2021, Bj\303\266rn Ottosson",
	"./thirdparty/noise/FastNoiseLite.h",
	"2023, Jordan Peck and contributors",
	"./thirdparty/misc/pcg.cpp",
	"./thirdparty/misc/pcg.h",
	"2014, M.E. O'Neill",
	"./thirdparty/misc/polypartition.cpp",
	"./thirdparty/misc/polypartition.h",
	"2011-2021, Ivan Fratric and contributors",
	"./thirdparty/misc/qoa.h",
	"2023, Dominic Szablewski",
	"./thirdparty/misc/r128.c",
	"./thirdparty/misc/r128.h",
	"Alan Hickman",
	"./thirdparty/misc/smaz.c",
	"./thirdparty/misc/smaz.h",
	"2006-2009, Salvatore Sanfilippo",
	"./thirdparty/misc/smolv.cpp",
	"./thirdparty/misc/smolv.h",
	"2016-2020, Aras Pranckevicius",
	"./thirdparty/misc/stb_rect_pack.h",
	"Sean Barrett",
	"./thirdparty/misc/yuv2rgb.h",
	"2008-2011, Robin Watts",
	"./thirdparty/msdfgen/",
	"2016-2022, Viktor Chlumsky",
	"./thirdparty/nvapi/nvapi_minimal.h",
	"2019-2022, NVIDIA Corporation",
	"./thirdparty/openxr/",
	"2020-2023, The Khronos Group Inc.",
	"./thirdparty/pcre2/",
	"1997-2024, University of Cambridge",
	"2009-2024, Zoltan Herczeg",
	"./thirdparty/recastnavigation/",
	"2009, Mikko Mononen",
	"./thirdparty/rvo2/",
	"2016, University of North Carolina at Chapel Hill",
	"./thirdparty/spirv-cross/",
	"2015-2021, Arm Limited",
	"./thirdparty/spirv-reflect/",
	"2017-2022, Google Inc.",
	"./thirdparty/squish/",
	"2006, Simon Brown",
	"./thirdparty/thorvg/",
	"2020-2024, The ThorVG Project",
	"./thirdparty/tinyexr/",
	"2014-2021, Syoyo Fujita",
	"2002, Industrial Light & Magic, a division of Lucas Digital Ltd. LLC",
	"./thirdparty/ufbx/",
	"2020, Samuli Raivio",
	"./thirdparty/vhacd/",
	"2011, Khaled Mamou",
	"2003-2009, Erwin Coumans",
	"./thirdparty/volk/",
	"2018-2024, Arseny Kapoulkine",
	"./thirdparty/vulkan/",
	"2014-2024, The Khronos Group Inc.",
	"2014-2024, Valve Corporation",
	"2014-2024, LunarG, Inc.",
	"./thirdparty/vulkan/vk_mem_alloc.h",
	"2017-2024, Advanced Micro Devices, Inc.",
	"./thirdparty/wayland/",
	"2008-2012, Kristian H\303\270gsberg",
	"2010-2012, Intel Corporation",
	"2011, Benjamin Franzke",
	"2012, Collabora, Ltd.",
	"./thirdparty/wayland-protocols/",
	"2008-2013, Kristian H\303\270gsberg",
	"2010-2013, Intel Corporation",
	"2013,      Rafael Antognolli",
	"2013,      Jasper St. Pierre",
	"2014,      Jonas \303\205dahl",
	"2014,      Jason Ekstrand",
	"2014-2015, Collabora, Ltd.",
	"2015,      Red Hat Inc.",
	"./thirdparty/wslay/",
	"2011, 2012, 2015, Tatsuhiro Tsujikawa",
	"./thirdparty/xatlas/",
	"2018-2020, Jonathan Young",
	"2013, Thekla, Inc",
	"2006, NVIDIA Corporation, Ignacio Castano",
	"./thirdparty/zlib/",
	"1995-2024, Jean-loup Gailly and Mark Adler",
	"./thirdparty/zstd/",
	"Meta Platforms, Inc. and affiliates.",
};

const ComponentCopyrightPart COPYRIGHT_PROJECT_PARTS[] = {
	{ "Expat", &COPYRIGHT_INFO_DATA[0], &COPYRIGHT_INFO_DATA[1], 1, 2 },
	{ "CC-BY-4.0", &COPYRIGHT_INFO_DATA[3], &COPYRIGHT_INFO_DATA[7], 4, 1 },
	{ "Expat and Zlib", &COPYRIGHT_INFO_DATA[8], &COPYRIGHT_INFO_DATA[10], 2, 3 },
	{ "Expat and Zlib", &COPYRIGHT_INFO_DATA[13], &COPYRIGHT_INFO_DATA[27], 14, 3 },
	{ "Expat and Zlib", &COPYRIGHT_INFO_DATA[30], &COPYRIGHT_INFO_DATA[32], 2, 3 },
	{ "Expat", &COPYRIGHT_INFO_DATA[35], &COPYRIGHT_INFO_DATA[36], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[37], &COPYRIGHT_INFO_DATA[38], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[39], &COPYRIGHT_INFO_DATA[40], 1, 3 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[43], &COPYRIGHT_INFO_DATA[49], 6, 2 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[51], &COPYRIGHT_INFO_DATA[52], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[53], &COPYRIGHT_INFO_DATA[54], 1, 3 },
	{ "Expat", &COPYRIGHT_INFO_DATA[57], &COPYRIGHT_INFO_DATA[66], 9, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[67], &COPYRIGHT_INFO_DATA[68], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[69], &COPYRIGHT_INFO_DATA[70], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[71], &COPYRIGHT_INFO_DATA[72], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[73], &COPYRIGHT_INFO_DATA[74], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[75], &COPYRIGHT_INFO_DATA[76], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[77], &COPYRIGHT_INFO_DATA[78], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[79], &COPYRIGHT_INFO_DATA[80], 1, 1 },
	{ "MPL-2.0", &COPYRIGHT_INFO_DATA[81], &COPYRIGHT_INFO_DATA[82], 1, 1 },
	{ "BSL-1.0", &COPYRIGHT_INFO_DATA[83], &COPYRIGHT_INFO_DATA[84], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[85], &COPYRIGHT_INFO_DATA[86], 1, 2 },
	{ "Expat", &COPYRIGHT_INFO_DATA[88], &COPYRIGHT_INFO_DATA[89], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[90], &COPYRIGHT_INFO_DATA[91], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[92], &COPYRIGHT_INFO_DATA[93], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[94], &COPYRIGHT_INFO_DATA[95], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[96], &COPYRIGHT_INFO_DATA[97], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[98], &COPYRIGHT_INFO_DATA[99], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[100], &COPYRIGHT_INFO_DATA[101], 1, 1 },
	{ "OFL-1.1", &COPYRIGHT_INFO_DATA[102], &COPYRIGHT_INFO_DATA[103], 1, 1 },
	{ "OFL-1.1", &COPYRIGHT_INFO_DATA[104], &COPYRIGHT_INFO_DATA[105], 1, 1 },
	{ "FTL", &COPYRIGHT_INFO_DATA[106], &COPYRIGHT_INFO_DATA[107], 1, 1 },
	{ "CC0-1.0 and Apache-2.0", &COPYRIGHT_INFO_DATA[108], &COPYRIGHT_INFO_DATA[109], 1, 2 },
	{ "glslang", &COPYRIGHT_INFO_DATA[111], &COPYRIGHT_INFO_DATA[112], 1, 3 },
	{ "Expat", &COPYRIGHT_INFO_DATA[115], &COPYRIGHT_INFO_DATA[116], 1, 1 },
	{ "HarfBuzz", &COPYRIGHT_INFO_DATA[117], &COPYRIGHT_INFO_DATA[118], 1, 17 },
	{ "Unicode", &COPYRIGHT_INFO_DATA[135], &COPYRIGHT_INFO_DATA[136], 1, 1 },
	{ "public-domain or Apache-2.0", &COPYRIGHT_INFO_DATA[137], &COPYRIGHT_INFO_DATA[138], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[139], &COPYRIGHT_INFO_DATA[140], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[141], &COPYRIGHT_INFO_DATA[142], 1, 2 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[144], &COPYRIGHT_INFO_DATA[145], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[146], &COPYRIGHT_INFO_DATA[147], 1, 1 },
	{ "Zlib", &COPYRIGHT_INFO_DATA[148], &COPYRIGHT_INFO_DATA[149], 1, 5 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[154], &COPYRIGHT_INFO_DATA[155], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[156], &COPYRIGHT_INFO_DATA[157], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[158], &COPYRIGHT_INFO_DATA[159], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[160], &COPYRIGHT_INFO_DATA[161], 1, 1 },
	{ "BSD-2-clause", &COPYRIGHT_INFO_DATA[162], &COPYRIGHT_INFO_DATA[163], 1, 1 },
	{ "CC0-1.0", &COPYRIGHT_INFO_DATA[164], &COPYRIGHT_INFO_DATA[165], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[166], &COPYRIGHT_INFO_DATA[167], 1, 1 },
	{ "Zlib", &COPYRIGHT_INFO_DATA[168], &COPYRIGHT_INFO_DATA[169], 1, 3 },
	{ "Expat", &COPYRIGHT_INFO_DATA[172], &COPYRIGHT_INFO_DATA[173], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[174], &COPYRIGHT_INFO_DATA[176], 2, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[177], &COPYRIGHT_INFO_DATA[179], 2, 1 },
	{ "Zlib", &COPYRIGHT_INFO_DATA[180], &COPYRIGHT_INFO_DATA[182], 2, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[183], &COPYRIGHT_INFO_DATA[185], 2, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[186], &COPYRIGHT_INFO_DATA[187], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[188], &COPYRIGHT_INFO_DATA[190], 2, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[191], &COPYRIGHT_INFO_DATA[193], 2, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[194], &COPYRIGHT_INFO_DATA[195], 1, 1 },
	{ "public-domain or Unlicense", &COPYRIGHT_INFO_DATA[196], &COPYRIGHT_INFO_DATA[198], 2, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[199], &COPYRIGHT_INFO_DATA[201], 2, 1 },
	{ "public-domain or Unlicense or Expat", &COPYRIGHT_INFO_DATA[202], &COPYRIGHT_INFO_DATA[204], 2, 1 },
	{ "public-domain or Unlicense or Expat", &COPYRIGHT_INFO_DATA[205], &COPYRIGHT_INFO_DATA[206], 1, 1 },
	{ "BSD-2-clause", &COPYRIGHT_INFO_DATA[207], &COPYRIGHT_INFO_DATA[208], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[209], &COPYRIGHT_INFO_DATA[210], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[211], &COPYRIGHT_INFO_DATA[212], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[213], &COPYRIGHT_INFO_DATA[214], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[215], &COPYRIGHT_INFO_DATA[216], 1, 2 },
	{ "Zlib", &COPYRIGHT_INFO_DATA[218], &COPYRIGHT_INFO_DATA[219], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[220], &COPYRIGHT_INFO_DATA[221], 1, 1 },
	{ "Apache-2.0 or Expat", &COPYRIGHT_INFO_DATA[222], &COPYRIGHT_INFO_DATA[223], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[224], &COPYRIGHT_INFO_DATA[225], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[226], &COPYRIGHT_INFO_DATA[227], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[228], &COPYRIGHT_INFO_DATA[229], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[230], &COPYRIGHT_INFO_DATA[231], 1, 2 },
	{ "Expat", &COPYRIGHT_INFO_DATA[233], &COPYRIGHT_INFO_DATA[234], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[235], &COPYRIGHT_INFO_DATA[236], 1, 2 },
	{ "Expat", &COPYRIGHT_INFO_DATA[238], &COPYRIGHT_INFO_DATA[239], 1, 1 },
	{ "Apache-2.0", &COPYRIGHT_INFO_DATA[240], &COPYRIGHT_INFO_DATA[241], 1, 3 },
	{ "Expat", &COPYRIGHT_INFO_DATA[244], &COPYRIGHT_INFO_DATA[245], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[246], &COPYRIGHT_INFO_DATA[247], 1, 4 },
	{ "Expat", &COPYRIGHT_INFO_DATA[251], &COPYRIGHT_INFO_DATA[252], 1, 8 },
	{ "Expat", &COPYRIGHT_INFO_DATA[260], &COPYRIGHT_INFO_DATA[261], 1, 1 },
	{ "Expat", &COPYRIGHT_INFO_DATA[262], &COPYRIGHT_INFO_DATA[263], 1, 3 },
	{ "Zlib", &COPYRIGHT_INFO_DATA[266], &COPYRIGHT_INFO_DATA[267], 1, 1 },
	{ "BSD-3-clause", &COPYRIGHT_INFO_DATA[268], &COPYRIGHT_INFO_DATA[269], 1, 1 },
};

const int COPYRIGHT_INFO_COUNT = 84;
const ComponentCopyright COPYRIGHT_INFO[] = {
	{ "Godot Engine", &COPYRIGHT_PROJECT_PARTS[0], 1 },
	{ "Godot Engine logo", &COPYRIGHT_PROJECT_PARTS[1], 1 },
	{ "Bullet Continuous Collision Detection and Physics Library", &COPYRIGHT_PROJECT_PARTS[2], 3 },
	{ "Chipmunk2D Joint Constraints", &COPYRIGHT_PROJECT_PARTS[5], 1 },
	{ "Open Dynamics Engine", &COPYRIGHT_PROJECT_PARTS[6], 1 },
	{ "Joint Non-Local Means (JNLM) denoiser", &COPYRIGHT_PROJECT_PARTS[7], 1 },
	{ "The Android Open Source Project", &COPYRIGHT_PROJECT_PARTS[8], 1 },
	{ "ProcessPhoenix", &COPYRIGHT_PROJECT_PARTS[9], 1 },
	{ "Robert Penner's Easing Functions", &COPYRIGHT_PROJECT_PARTS[10], 1 },
	{ "Intel ASSAO and related files", &COPYRIGHT_PROJECT_PARTS[11], 1 },
	{ "Temporal Anti-Aliasing resolve implementation", &COPYRIGHT_PROJECT_PARTS[12], 1 },
	{ "AMD FidelityFX Super Resolution", &COPYRIGHT_PROJECT_PARTS[13], 1 },
	{ "AMD FidelityFX Super Resolution 2", &COPYRIGHT_PROJECT_PARTS[14], 1 },
	{ "ANGLE", &COPYRIGHT_PROJECT_PARTS[15], 1 },
	{ "Arm ASTC Encoder", &COPYRIGHT_PROJECT_PARTS[16], 1 },
	{ "Basis Universal", &COPYRIGHT_PROJECT_PARTS[17], 1 },
	{ "Brotli", &COPYRIGHT_PROJECT_PARTS[18], 1 },
	{ "CA certificates", &COPYRIGHT_PROJECT_PARTS[19], 1 },
	{ "Clipper2", &COPYRIGHT_PROJECT_PARTS[20], 1 },
	{ "Convection Texture Tools Stand-Alone Kernels", &COPYRIGHT_PROJECT_PARTS[21], 1 },
	{ "D3D12 Memory Allocator", &COPYRIGHT_PROJECT_PARTS[22], 1 },
	{ "DirectX Headers", &COPYRIGHT_PROJECT_PARTS[23], 1 },
	{ "doctest", &COPYRIGHT_PROJECT_PARTS[24], 1 },
	{ "Embree", &COPYRIGHT_PROJECT_PARTS[25], 1 },
	{ "ENet", &COPYRIGHT_PROJECT_PARTS[26], 1 },
	{ "etcpak", &COPYRIGHT_PROJECT_PARTS[27], 1 },
	{ "DroidSans font", &COPYRIGHT_PROJECT_PARTS[28], 1 },
	{ "JetBrains Mono font", &COPYRIGHT_PROJECT_PARTS[29], 1 },
	{ "Noto Sans font", &COPYRIGHT_PROJECT_PARTS[30], 1 },
	{ "The FreeType Project", &COPYRIGHT_PROJECT_PARTS[31], 1 },
	{ "glad", &COPYRIGHT_PROJECT_PARTS[32], 1 },
	{ "glslang", &COPYRIGHT_PROJECT_PARTS[33], 1 },
	{ "Graphite engine", &COPYRIGHT_PROJECT_PARTS[34], 1 },
	{ "HarfBuzz text shaping library", &COPYRIGHT_PROJECT_PARTS[35], 1 },
	{ "International Components for Unicode", &COPYRIGHT_PROJECT_PARTS[36], 1 },
	{ "jpeg-compressor", &COPYRIGHT_PROJECT_PARTS[37], 1 },
	{ "libbacktrace", &COPYRIGHT_PROJECT_PARTS[38], 1 },
	{ "KTX", &COPYRIGHT_PROJECT_PARTS[39], 1 },
	{ "OggVorbis", &COPYRIGHT_PROJECT_PARTS[40], 2 },
	{ "libpng", &COPYRIGHT_PROJECT_PARTS[42], 1 },
	{ "OggTheora", &COPYRIGHT_PROJECT_PARTS[43], 1 },
	{ "WebP codec", &COPYRIGHT_PROJECT_PARTS[44], 1 },
	{ "Mbed TLS", &COPYRIGHT_PROJECT_PARTS[45], 1 },
	{ "meshoptimizer", &COPYRIGHT_PROJECT_PARTS[46], 1 },
	{ "mingw-std-threads", &COPYRIGHT_PROJECT_PARTS[47], 1 },
	{ "MiniMP3", &COPYRIGHT_PROJECT_PARTS[48], 1 },
	{ "MiniUPnP Project", &COPYRIGHT_PROJECT_PARTS[49], 1 },
	{ "MiniZip", &COPYRIGHT_PROJECT_PARTS[50], 1 },
	{ "Fast Filtering of Reflection Probes", &COPYRIGHT_PROJECT_PARTS[51], 1 },
	{ "FastLZ", &COPYRIGHT_PROJECT_PARTS[52], 1 },
	{ "libjingle", &COPYRIGHT_PROJECT_PARTS[53], 1 },
	{ "Tangent Space Normal Maps implementation", &COPYRIGHT_PROJECT_PARTS[54], 1 },
	{ "OK Lab color space", &COPYRIGHT_PROJECT_PARTS[55], 1 },
	{ "FastNoise Lite", &COPYRIGHT_PROJECT_PARTS[56], 1 },
	{ "Minimal PCG32 implementation", &COPYRIGHT_PROJECT_PARTS[57], 1 },
	{ "PolyPartition / Triangulator", &COPYRIGHT_PROJECT_PARTS[58], 1 },
	{ "Quite OK Audio Format", &COPYRIGHT_PROJECT_PARTS[59], 1 },
	{ "r128 library", &COPYRIGHT_PROJECT_PARTS[60], 1 },
	{ "SMAZ", &COPYRIGHT_PROJECT_PARTS[61], 1 },
	{ "SMOL-V", &COPYRIGHT_PROJECT_PARTS[62], 1 },
	{ "stb libraries", &COPYRIGHT_PROJECT_PARTS[63], 1 },
	{ "YUV2RGB", &COPYRIGHT_PROJECT_PARTS[64], 1 },
	{ "Multi-channel signed distance field generator", &COPYRIGHT_PROJECT_PARTS[65], 1 },
	{ "Stripped down version of \042nvapi.h\042 from the NVIDIA NVAPI SDK", &COPYRIGHT_PROJECT_PARTS[66], 1 },
	{ "OpenXR Loader", &COPYRIGHT_PROJECT_PARTS[67], 1 },
	{ "PCRE2", &COPYRIGHT_PROJECT_PARTS[68], 1 },
	{ "Recast", &COPYRIGHT_PROJECT_PARTS[69], 1 },
	{ "RVO2", &COPYRIGHT_PROJECT_PARTS[70], 1 },
	{ "SPIRV-Cross", &COPYRIGHT_PROJECT_PARTS[71], 1 },
	{ "SPIRV-Reflect", &COPYRIGHT_PROJECT_PARTS[72], 1 },
	{ "libSquish", &COPYRIGHT_PROJECT_PARTS[73], 1 },
	{ "ThorVG", &COPYRIGHT_PROJECT_PARTS[74], 1 },
	{ "TinyEXR", &COPYRIGHT_PROJECT_PARTS[75], 1 },
	{ "ufbx", &COPYRIGHT_PROJECT_PARTS[76], 1 },
	{ "V-HACD", &COPYRIGHT_PROJECT_PARTS[77], 1 },
	{ "volk", &COPYRIGHT_PROJECT_PARTS[78], 1 },
	{ "Vulkan Headers", &COPYRIGHT_PROJECT_PARTS[79], 1 },
	{ "Vulkan Memory Allocator", &COPYRIGHT_PROJECT_PARTS[80], 1 },
	{ "Wayland core protocol", &COPYRIGHT_PROJECT_PARTS[81], 1 },
	{ "Wayland protocols that add functionality not available in the core protocol", &COPYRIGHT_PROJECT_PARTS[82], 1 },
	{ "Wslay", &COPYRIGHT_PROJECT_PARTS[83], 1 },
	{ "xatlas", &COPYRIGHT_PROJECT_PARTS[84], 1 },
	{ "zlib", &COPYRIGHT_PROJECT_PARTS[85], 1 },
	{ "Zstandard", &COPYRIGHT_PROJECT_PARTS[86], 1 },
};

const int LICENSE_COUNT = 15;
const char *const LICENSE_NAMES[] = {
	"Apache-2.0",
	"BSD-2-clause",
	"BSD-3-clause",
	"BSL-1.0",
	"CC0-1.0",
	"CC-BY-4.0",
	"Expat",
	"glslang",
	"FTL",
	"HarfBuzz",
	"MPL-2.0",
	"OFL-1.1",
	"Unicode",
	"Unlicense",
	"Zlib",
};

const char *const LICENSE_BODIES[] = {

	"Licensed under the Apache License, Version 2.0 (the \042License\042);\n"
	"you may not use this file except in compliance with the License.\n"
	"You may obtain a copy of the License at\n"
	"\n"
	"http://www.apache.org/licenses/LICENSE-2.0\n"
	"\n"
	"Unless required by applicable law or agreed to in writing, software\n"
	"distributed under the License is distributed on an \042AS IS\042 BASIS,\n"
	"WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
	"See the License for the specific language governing permissions and\n"
	"limitations under the License.\n"
	"",

	"Redistribution and use in source and binary forms, with or without\n"
	"modification, are permitted provided that the following conditions are met:\n"
	"\n"
	"* Redistributions of source code must retain the above copyright notice, this\n"
	"list of conditions and the following disclaimer.\n"
	"\n"
	"* Redistributions in binary form must reproduce the above copyright notice,\n"
	"this list of conditions and the following disclaimer in the documentation\n"
	"and/or other materials provided with the distribution.\n"
	"\n"
	"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \042AS IS\042 AND\n"
	"ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
	"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n"
	"DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE\n"
	"FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	"DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR\n"
	"SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER\n"
	"CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,\n"
	"OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n"
	"OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
	"",

	"Redistribution and use in source and binary forms, with or without\n"
	"modification, are permitted provided that the following conditions\n"
	"are met:\n"
	"\n"
	"1. Redistributions of source code must retain the above copyright\n"
	"notice, this list of conditions and the following disclaimer.\n"
	"\n"
	"2. Redistributions in binary form must reproduce the above copyright\n"
	"notice, this list of conditions and the following disclaimer in the\n"
	"documentation and/or other materials provided with the distribution.\n"
	"\n"
	"3. Neither the name of the copyright holder nor the names of its\n"
	"contributors may be used to endorse or promote products derived from\n"
	"this software without specific prior written permission.\n"
	"\n"
	"THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND\n"
	"ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	"IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n"
	"ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE\n"
	"FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	"DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n"
	"OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	"HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
	"LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n"
	"OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n"
	"SUCH DAMAGE.\n"
	"",

	"Boost Software License - Version 1.0 - August 17th, 2003\n"
	"\n"
	"Permission is hereby granted, free of charge, to any person or organization\n"
	"obtaining a copy of the software and accompanying documentation covered by\n"
	"this license (the \042Software\042) to use, reproduce, display, distribute,\n"
	"execute, and transmit the Software, and to prepare derivative works of the\n"
	"Software, and to permit third-parties to whom the Software is furnished to\n"
	"do so, all subject to the following:\n"
	"\n"
	"The copyright notices in the Software and this entire statement, including\n"
	"the above license grant, this restriction and the following disclaimer,\n"
	"must be included in all copies of the Software, in whole or in part, and\n"
	"all derivative works of the Software, unless such copies or derivative\n"
	"works are solely in the form of machine-executable object code generated by\n"
	"a source language processor.\n"
	"\n"
	"THE SOFTWARE IS PROVIDED \042AS IS\042, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
	"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
	"FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT\n"
	"SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE\n"
	"FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,\n"
	"ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER\n"
	"DEALINGS IN THE SOFTWARE.\n"
	"",

	"CC0 1.0 Universal\n"
	"\n"
	"Statement of Purpose\n"
	"\n"
	"The laws of most jurisdictions throughout the world automatically confer\n"
	"exclusive Copyright and Related Rights (defined below) upon the creator and\n"
	"subsequent owner(s) (each and all, an \042owner\042) of an original work of\n"
	"authorship and/or a database (each, a \042Work\042).\n"
	"\n"
	"Certain owners wish to permanently relinquish those rights to a Work for the\n"
	"purpose of contributing to a commons of creative, cultural and scientific\n"
	"works (\042Commons\042) that the public can reliably and without fear of later\n"
	"claims of infringement build upon, modify, incorporate in other works, reuse\n"
	"and redistribute as freely as possible in any form whatsoever and for any\n"
	"purposes, including without limitation commercial purposes. These owners may\n"
	"contribute to the Commons to promote the ideal of a free culture and the\n"
	"further production of creative, cultural and scientific works, or to gain\n"
	"reputation or greater distribution for their Work in part through the use and\n"
	"efforts of others.\n"
	"\n"
	"For these and/or other purposes and motivations, and without any expectation\n"
	"of additional consideration or compensation, the person associating CC0 with a\n"
	"Work (the \042Affirmer\042), to the extent that he or she is an owner of Copyright\n"
	"and Related Rights in the Work, voluntarily elects to apply CC0 to the Work\n"
	"and publicly distribute the Work under its terms, with knowledge of his or her\n"
	"Copyright and Related Rights in the Work and the meaning and intended legal\n"
	"effect of CC0 on those rights.\n"
	"\n"
	"1. Copyright and Related Rights. A Work made available under CC0 may be\n"
	"protected by copyright and related or neighboring rights (\042Copyright and\n"
	"Related Rights\042). Copyright and Related Rights include, but are not limited\n"
	"to, the following:\n"
	"\n"
	"i. the right to reproduce, adapt, distribute, perform, display, communicate,\n"
	"and translate a Work;\n"
	"\n"
	"ii. moral rights retained by the original author(s) and/or performer(s);\n"
	"\n"
	"iii. publicity and privacy rights pertaining to a person's image or likeness\n"
	"depicted in a Work;\n"
	"\n"
	"iv. rights protecting against unfair competition in regards to a Work,\n"
	"subject to the limitations in paragraph 4(a), below;\n"
	"\n"
	"v. rights protecting the extraction, dissemination, use and reuse of data in\n"
	"a Work;\n"
	"\n"
	"vi. database rights (such as those arising under Directive 96/9/EC of the\n"
	"European Parliament and of the Council of 11 March 1996 on the legal\n"
	"protection of databases, and under any national implementation thereof,\n"
	"including any amended or successor version of such directive); and\n"
	"\n"
	"vii. other similar, equivalent or corresponding rights throughout the world\n"
	"based on applicable law or treaty, and any national implementations thereof.\n"
	"\n"
	"2. Waiver. To the greatest extent permitted by, but not in contravention of,\n"
	"applicable law, Affirmer hereby overtly, fully, permanently, irrevocably and\n"
	"unconditionally waives, abandons, and surrenders all of Affirmer's Copyright\n"
	"and Related Rights and associated claims and causes of action, whether now\n"
	"known or unknown (including existing as well as future claims and causes of\n"
	"action), in the Work (i) in all territories worldwide, (ii) for the maximum\n"
	"duration provided by applicable law or treaty (including future time\n"
	"extensions), (iii) in any current or future medium and for any number of\n"
	"copies, and (iv) for any purpose whatsoever, including without limitation\n"
	"commercial, advertising or promotional purposes (the \042Waiver\042). Affirmer makes\n"
	"the Waiver for the benefit of each member of the public at large and to the\n"
	"detriment of Affirmer's heirs and successors, fully intending that such Waiver\n"
	"shall not be subject to revocation, rescission, cancellation, termination, or\n"
	"any other legal or equitable action to disrupt the quiet enjoyment of the Work\n"
	"by the public as contemplated by Affirmer's express Statement of Purpose.\n"
	"\n"
	"3. Public License Fallback. Should any part of the Waiver for any reason be\n"
	"judged legally invalid or ineffective under applicable law, then the Waiver\n"
	"shall be preserved to the maximum extent permitted taking into account\n"
	"Affirmer's express Statement of Purpose. In addition, to the extent the Waiver\n"
	"is so judged Affirmer hereby grants to each affected person a royalty-free,\n"
	"non transferable, non sublicensable, non exclusive, irrevocable and\n"
	"unconditional license to exercise Affirmer's Copyright and Related Rights in\n"
	"the Work (i) in all territories worldwide, (ii) for the maximum duration\n"
	"provided by applicable law or treaty (including future time extensions), (iii)\n"
	"in any current or future medium and for any number of copies, and (iv) for any\n"
	"purpose whatsoever, including without limitation commercial, advertising or\n"
	"promotional purposes (the \042License\042). The License shall be deemed effective as\n"
	"of the date CC0 was applied by Affirmer to the Work. Should any part of the\n"
	"License for any reason be judged legally invalid or ineffective under\n"
	"applicable law, such partial invalidity or ineffectiveness shall not\n"
	"invalidate the remainder of the License, and in such case Affirmer hereby\n"
	"affirms that he or she will not (i) exercise any of his or her remaining\n"
	"Copyright and Related Rights in the Work or (ii) assert any associated claims\n"
	"and causes of action with respect to the Work, in either case contrary to\n"
	"Affirmer's express Statement of Purpose.\n"
	"\n"
	"4. Limitations and Disclaimers.\n"
	"\n"
	"a. No trademark or patent rights held by Affirmer are waived, abandoned,\n"
	"surrendered, licensed or otherwise affected by this document.\n"
	"\n"
	"b. Affirmer offers the Work as-is and makes no representations or warranties\n"
	"of any kind concerning the Work, express, implied, statutory or otherwise,\n"
	"including without limitation warranties of title, merchantability, fitness\n"
	"for a particular purpose, non infringement, or the absence of latent or\n"
	"other defects, accuracy, or the present or absence of errors, whether or not\n"
	"discoverable, all to the greatest extent permissible under applicable law.\n"
	"\n"
	"c. Affirmer disclaims responsibility for clearing rights of other persons\n"
	"that may apply to the Work or any use thereof, including without limitation\n"
	"any person's Copyright and Related Rights in the Work. Further, Affirmer\n"
	"disclaims responsibility for obtaining any necessary consents, permissions\n"
	"or other rights required for any use of the Work.\n"
	"\n"
	"d. Affirmer understands and acknowledges that Creative Commons is not a\n"
	"party to this document and has no duty or obligation with respect to this\n"
	"CC0 or use of the Work.\n"
	"",

	"Creative Commons Attribution 4.0 International Public License\n"
	"\n"
	"By exercising the Licensed Rights (defined below), You accept and agree\n"
	"to be bound by the terms and conditions of this Creative Commons\n"
	"Attribution 4.0 International Public License (\042Public\n"
	"License\042). To the extent this Public License may be interpreted as a\n"
	"contract, You are granted the Licensed Rights in consideration of Your\n"
	"acceptance of these terms and conditions, and the Licensor grants You\n"
	"such rights in consideration of benefits the Licensor receives from\n"
	"making the Licensed Material available under these terms and\n"
	"conditions.\n"
	"\n"
	"Section 1 -- Definitions.\n"
	"\n"
	"a. Adapted Material means material subject to Copyright and Similar\n"
	"Rights that is derived from or based upon the Licensed Material\n"
	"and in which the Licensed Material is translated, altered,\n"
	"arranged, transformed, or otherwise modified in a manner requiring\n"
	"permission under the Copyright and Similar Rights held by the\n"
	"Licensor. For purposes of this Public License, where the Licensed\n"
	"Material is a musical work, performance, or sound recording,\n"
	"Adapted Material is always produced where the Licensed Material is\n"
	"synched in timed relation with a moving image.\n"
	"\n"
	"b. Adapter's License means the license You apply to Your Copyright\n"
	"and Similar Rights in Your contributions to Adapted Material in\n"
	"accordance with the terms and conditions of this Public License.\n"
	"\n"
	"c. Copyright and Similar Rights means copyright and/or similar rights\n"
	"closely related to copyright including, without limitation,\n"
	"performance, broadcast, sound recording, and Sui Generis Database\n"
	"Rights, without regard to how the rights are labeled or\n"
	"categorized. For purposes of this Public License, the rights\n"
	"specified in Section 2(b)(1)-(2) are not Copyright and Similar\n"
	"Rights.\n"
	"\n"
	"d. Effective Technological Measures means those measures that, in the\n"
	"absence of proper authority, may not be circumvented under laws\n"
	"fulfilling obligations under Article 11 of the WIPO Copyright\n"
	"Treaty adopted on December 20, 1996, and/or similar international\n"
	"agreements.\n"
	"\n"
	"e. Exceptions and Limitations means fair use, fair dealing, and/or\n"
	"any other exception or limitation to Copyright and Similar Rights\n"
	"that applies to Your use of the Licensed Material.\n"
	"\n"
	"f. Licensed Material means the artistic or literary work, database,\n"
	"or other material to which the Licensor applied this Public\n"
	"License.\n"
	"\n"
	"g. Licensed Rights means the rights granted to You subject to the\n"
	"terms and conditions of this Public License, which are limited to\n"
	"all Copyright and Similar Rights that apply to Your use of the\n"
	"Licensed Material and that the Licensor has authority to license.\n"
	"\n"
	"h. Licensor means the individual(s) or entity(ies) granting rights\n"
	"under this Public License.\n"
	"\n"
	"i. Share means to provide material to the public by any means or\n"
	"process that requires permission under the Licensed Rights, such\n"
	"as reproduction, public display, public performance, distribution,\n"
	"dissemination, communication, or importation, and to make material\n"
	"available to the public including in ways that members of the\n"
	"public may access the material from a place and at a time\n"
	"individually chosen by them.\n"
	"\n"
	"j. Sui Generis Database Rights means rights other than copyright\n"
	"resulting from Directive 96/9/EC of the European Parliament and of\n"
	"the Council of 11 March 1996 on the legal protection of databases,\n"
	"as amended and/or succeeded, as well as other essentially\n"
	"equivalent rights anywhere in the world.\n"
	"\n"
	"k. You means the individual or entity exercising the Licensed Rights\n"
	"under this Public License. Your has a corresponding meaning.\n"
	"\n"
	"Section 2 -- Scope.\n"
	"\n"
	"a. License grant.\n"
	"\n"
	"1. Subject to the terms and conditions of this Public License,\n"
	"the Licensor hereby grants You a worldwide, royalty-free,\n"
	"non-sublicensable, non-exclusive, irrevocable license to\n"
	"exercise the Licensed Rights in the Licensed Material to:\n"
	"\n"
	"a. reproduce and Share the Licensed Material, in whole or\n"
	"in part; and\n"
	"\n"
	"b. produce, reproduce, and Share Adapted Material.\n"
	"\n"
	"2. Exceptions and Limitations. For the avoidance of doubt, where\n"
	"Exceptions and Limitations apply to Your use, this Public\n"
	"License does not apply, and You do not need to comply with\n"
	"its terms and conditions.\n"
	"\n"
	"3. Term. The term of this Public License is specified in Section\n"
	"6(a).\n"
	"\n"
	"4. Media and formats; technical modifications allowed. The\n"
	"Licensor authorizes You to exercise the Licensed Rights in\n"
	"all media and formats whether now known or hereafter created,\n"
	"and to make technical modifications necessary to do so. The\n"
	"Licensor waives and/or agrees not to assert any right or\n"
	"authority to forbid You from making technical modifications\n"
	"necessary to exercise the Licensed Rights, including\n"
	"technical modifications necessary to circumvent Effective\n"
	"Technological Measures. For purposes of this Public License,\n"
	"simply making modifications authorized by this Section 2(a)\n"
	"(4) never produces Adapted Material.\n"
	"\n"
	"5. Downstream recipients.\n"
	"\n"
	"a. Offer from the Licensor -- Licensed Material. Every\n"
	"recipient of the Licensed Material automatically\n"
	"receives an offer from the Licensor to exercise the\n"
	"Licensed Rights under the terms and conditions of this\n"
	"Public License.\n"
	"\n"
	"b. No downstream restrictions. You may not offer or impose\n"
	"any additional or different terms or conditions on, or\n"
	"apply any Effective Technological Measures to, the\n"
	"Licensed Material if doing so restricts exercise of the\n"
	"Licensed Rights by any recipient of the Licensed\n"
	"Material.\n"
	"\n"
	"6. No endorsement. Nothing in this Public License constitutes or\n"
	"may be construed as permission to assert or imply that You\n"
	"are, or that Your use of the Licensed Material is, connected\n"
	"with, or sponsored, endorsed, or granted official status by,\n"
	"the Licensor or others designated to receive attribution as\n"
	"provided in Section 3(a)(1)(A)(i).\n"
	"\n"
	"b. Other rights.\n"
	"\n"
	"1. Moral rights, such as the right of integrity, are not\n"
	"licensed under this Public License, nor are publicity,\n"
	"privacy, and/or other similar personality rights; however, to\n"
	"the extent possible, the Licensor waives and/or agrees not to\n"
	"assert any such rights held by the Licensor to the limited\n"
	"extent necessary to allow You to exercise the Licensed\n"
	"Rights, but not otherwise.\n"
	"\n"
	"2. Patent and trademark rights are not licensed under this\n"
	"Public License.\n"
	"\n"
	"3. To the extent possible, the Licensor waives any right to\n"
	"collect royalties from You for the exercise of the Licensed\n"
	"Rights, whether directly or through a collecting society\n"
	"under any voluntary or waivable statutory or compulsory\n"
	"licensing scheme. In all other cases the Licensor expressly\n"
	"reserves any right to collect such royalties.\n"
	"\n"
	"Section 3 -- License Conditions.\n"
	"\n"
	"Your exercise of the Licensed Rights is expressly made subject to the\n"
	"following conditions.\n"
	"\n"
	"a. Attribution.\n"
	"\n"
	"1. If You Share the Licensed Material (including in modified\n"
	"form), You must:\n"
	"\n"
	"a. retain the following if it is supplied by the Licensor\n"
	"with the Licensed Material:\n"
	"\n"
	"i. identification of the creator(s) of the Licensed\n"
	"Material and any others designated to receive\n"
	"attribution, in any reasonable manner requested by\n"
	"the Licensor (including by pseudonym if\n"
	"designated);\n"
	"\n"
	"ii. a copyright notice;\n"
	"\n"
	"iii. a notice that refers to this Public License;\n"
	"\n"
	"iv. a notice that refers to the disclaimer of\n"
	"warranties;\n"
	"\n"
	"v. a URI or hyperlink to the Licensed Material to the\n"
	"extent reasonably practicable;\n"
	"\n"
	"b. indicate if You modified the Licensed Material and\n"
	"retain an indication of any previous modifications; and\n"
	"\n"
	"c. indicate the Licensed Material is licensed under this\n"
	"Public License, and include the text of, or the URI or\n"
	"hyperlink to, this Public License.\n"
	"\n"
	"2. You may satisfy the conditions in Section 3(a)(1) in any\n"
	"reasonable manner based on the medium, means, and context in\n"
	"which You Share the Licensed Material. For example, it may be\n"
	"reasonable to satisfy the conditions by providing a URI or\n"
	"hyperlink to a resource that includes the required\n"
	"information.\n"
	"\n"
	"3. If requested by the Licensor, You must remove any of the\n"
	"information required by Section 3(a)(1)(A) to the extent\n"
	"reasonably practicable.\n"
	"\n"
	"4. If You Share Adapted Material You produce, the Adapter's\n"
	"License You apply must not prevent recipients of the Adapted\n"
	"Material from complying with this Public License.\n"
	"\n"
	"Section 4 -- Sui Generis Database Rights.\n"
	"\n"
	"Where the Licensed Rights include Sui Generis Database Rights that\n"
	"apply to Your use of the Licensed Material:\n"
	"\n"
	"a. for the avoidance of doubt, Section 2(a)(1) grants You the right\n"
	"to extract, reuse, reproduce, and Share all or a substantial\n"
	"portion of the contents of the database;\n"
	"\n"
	"b. if You include all or a substantial portion of the database\n"
	"contents in a database in which You have Sui Generis Database\n"
	"Rights, then the database in which You have Sui Generis Database\n"
	"Rights (but not its individual contents) is Adapted Material; and\n"
	"\n"
	"c. You must comply with the conditions in Section 3(a) if You Share\n"
	"all or a substantial portion of the contents of the database.\n"
	"\n"
	"For the avoidance of doubt, this Section 4 supplements and does not\n"
	"replace Your obligations under this Public License where the Licensed\n"
	"Rights include other Copyright and Similar Rights.\n"
	"\n"
	"Section 5 -- Disclaimer of Warranties and Limitation of Liability.\n"
	"\n"
	"a. UNLESS OTHERWISE SEPARATELY UNDERTAKEN BY THE LICENSOR, TO THE\n"
	"EXTENT POSSIBLE, THE LICENSOR OFFERS THE LICENSED MATERIAL AS-IS\n"
	"AND AS-AVAILABLE, AND MAKES NO REPRESENTATIONS OR WARRANTIES OF\n"
	"ANY KIND CONCERNING THE LICENSED MATERIAL, WHETHER EXPRESS,\n"
	"IMPLIED, STATUTORY, OR OTHER. THIS INCLUDES, WITHOUT LIMITATION,\n"
	"WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR\n"
	"PURPOSE, NON-INFRINGEMENT, ABSENCE OF LATENT OR OTHER DEFECTS,\n"
	"ACCURACY, OR THE PRESENCE OR ABSENCE OF ERRORS, WHETHER OR NOT\n"
	"KNOWN OR DISCOVERABLE. WHERE DISCLAIMERS OF WARRANTIES ARE NOT\n"
	"ALLOWED IN FULL OR IN PART, THIS DISCLAIMER MAY NOT APPLY TO YOU.\n"
	"\n"
	"b. TO THE EXTENT POSSIBLE, IN NO EVENT WILL THE LICENSOR BE LIABLE\n"
	"TO YOU ON ANY LEGAL THEORY (INCLUDING, WITHOUT LIMITATION,\n"
	"NEGLIGENCE) OR OTHERWISE FOR ANY DIRECT, SPECIAL, INDIRECT,\n"
	"INCIDENTAL, CONSEQUENTIAL, PUNITIVE, EXEMPLARY, OR OTHER LOSSES,\n"
	"COSTS, EXPENSES, OR DAMAGES ARISING OUT OF THIS PUBLIC LICENSE OR\n"
	"USE OF THE LICENSED MATERIAL, EVEN IF THE LICENSOR HAS BEEN\n"
	"ADVISED OF THE POSSIBILITY OF SUCH LOSSES, COSTS, EXPENSES, OR\n"
	"DAMAGES. WHERE A LIMITATION OF LIABILITY IS NOT ALLOWED IN FULL OR\n"
	"IN PART, THIS LIMITATION MAY NOT APPLY TO YOU.\n"
	"\n"
	"c. The disclaimer of warranties and limitation of liability provided\n"
	"above shall be interpreted in a manner that, to the extent\n"
	"possible, most closely approximates an absolute disclaimer and\n"
	"waiver of all liability.\n"
	"\n"
	"Section 6 -- Term and Termination.\n"
	"\n"
	"a. This Public License applies for the term of the Copyright and\n"
	"Similar Rights licensed here. However, if You fail to comply with\n"
	"this Public License, then Your rights under this Public License\n"
	"terminate automatically.\n"
	"\n"
	"b. Where Your right to use the Licensed Material has terminated under\n"
	"Section 6(a), it reinstates:\n"
	"\n"
	"1. automatically as of the date the violation is cured, provided\n"
	"it is cured within 30 days of Your discovery of the\n"
	"violation; or\n"
	"\n"
	"2. upon express reinstatement by the Licensor.\n"
	"\n"
	"For the avoidance of doubt, this Section 6(b) does not affect any\n"
	"right the Licensor may have to seek remedies for Your violations\n"
	"of this Public License.\n"
	"\n"
	"c. For the avoidance of doubt, the Licensor may also offer the\n"
	"Licensed Material under separate terms or conditions or stop\n"
	"distributing the Licensed Material at any time; however, doing so\n"
	"will not terminate this Public License.\n"
	"\n"
	"d. Sections 1, 5, 6, 7, and 8 survive termination of this Public\n"
	"License.\n"
	"\n"
	"Section 7 -- Other Terms and Conditions.\n"
	"\n"
	"a. The Licensor shall not be bound by any additional or different\n"
	"terms or conditions communicated by You unless expressly agreed.\n"
	"\n"
	"b. Any arrangements, understandings, or agreements regarding the\n"
	"Licensed Material not stated herein are separate from and\n"
	"independent of the terms and conditions of this Public License.\n"
	"\n"
	"Section 8 -- Interpretation.\n"
	"\n"
	"a. For the avoidance of doubt, this Public License does not, and\n"
	"shall not be interpreted to, reduce, limit, restrict, or impose\n"
	"conditions on any use of the Licensed Material that could lawfully\n"
	"be made without permission under this Public License.\n"
	"\n"
	"b. To the extent possible, if any provision of this Public License is\n"
	"deemed unenforceable, it shall be automatically reformed to the\n"
	"minimum extent necessary to make it enforceable. If the provision\n"
	"cannot be reformed, it shall be severed from this Public License\n"
	"without affecting the enforceability of the remaining terms and\n"
	"conditions.\n"
	"\n"
	"c. No term or condition of this Public License will be waived and no\n"
	"failure to comply consented to unless expressly agreed to by the\n"
	"Licensor.\n"
	"\n"
	"d. Nothing in this Public License constitutes or may be interpreted\n"
	"as a limitation upon, or waiver of, any privileges and immunities\n"
	"that apply to the Licensor or You, including from the legal\n"
	"processes of any jurisdiction or authority.\n"
	"",

	"Permission is hereby granted, free of charge, to any person obtaining\n"
	"a copy of this software and associated documentation files (the\n"
	"\042Software\042), to deal in the Software without restriction, including\n"
	"without limitation the rights to use, copy, modify, merge, publish,\n"
	"distribute, sublicense, and/or sell copies of the Software, and to\n"
	"permit persons to whom the Software is furnished to do so, subject to\n"
	"the following conditions:\n"
	"\n"
	"The above copyright notice and this permission notice shall be\n"
	"included in all copies or substantial portions of the Software.\n"
	"\n"
	"THE SOFTWARE IS PROVIDED \042AS IS\042, WITHOUT WARRANTY OF ANY KIND,\n"
	"EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
	"MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
	"IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY\n"
	"CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,\n"
	"TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE\n"
	"SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n"
	"",

	"Here, glslang proper means core GLSL parsing, HLSL parsing, and SPIR-V code\n"
	"generation. Glslang proper requires use of a number of licenses, one that covers\n"
	"preprocessing and others that covers non-preprocessing.\n"
	"\n"
	"Bison was removed long ago. You can build glslang from the source grammar,\n"
	"using tools of your choice, without using bison or any bison files.\n"
	"\n"
	"Other parts, outside of glslang proper, include:\n"
	"\n"
	"- gl_types.h, only needed for OpenGL-like reflection, and can be left out of\n"
	"a parse and codegen project.  See it for its license.\n"
	"\n"
	"- update_glslang_sources.py, which is not part of the project proper and does\n"
	"not need to be used.\n"
	"\n"
	"- the SPIR-V \042remapper\042, which is optional, but has the same license as\n"
	"glslang proper\n"
	"\n"
	"- Google tests and SPIR-V tools, and anything in the external subdirectory\n"
	"are external and optional; see them for their respective licenses.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"The core of glslang-proper, minus the preprocessor is licenced as follows:\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"3-Clause BSD License\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"Copyright (C) 2015-2018 Google, Inc.\n"
	"Copyright (C) <various other dates and companies>\n"
	"\n"
	"All rights reserved.\n"
	"\n"
	"See: <License: BSD-3-clause>.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"2-Clause BSD License\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"Copyright 2020 The Khronos Group Inc\n"
	"\n"
	"See: <License: BSD-2-clause>.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"The MIT License\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"Copyright 2020 The Khronos Group Inc\n"
	"\n"
	"See: <License: Expat>.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"APACHE LICENSE, VERSION 2.0\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"See: <License: Apache-2.0>.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"GPL 3 with special bison exception\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"Bison implementation for Yacc-like parsers in C\n"
	"\n"
	"Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.\n"
	"\n"
	"This program is free software: you can redistribute it and/or modify\n"
	"it under the terms of the GNU General Public License as published by\n"
	"the Free Software Foundation, either version 3 of the License, or\n"
	"(at your option) any later version.\n"
	"\n"
	"This program is distributed in the hope that it will be useful,\n"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	"GNU General Public License for more details.\n"
	"\n"
	"You should have received a copy of the GNU General Public License\n"
	"along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"
	"\n"
	"As a special exception, you may create a larger work that contains\n"
	"part or all of the Bison parser skeleton and distribute that work\n"
	"under terms of your choice, so long as that work isn't itself a\n"
	"parser generator using the skeleton or a modified version thereof\n"
	"as a parser skeleton.  Alternatively, if you modify or redistribute\n"
	"the parser skeleton itself, you may (at your option) remove this\n"
	"special exception, which will cause the skeleton and the resulting\n"
	"Bison output files to be licensed under the GNU General Public\n"
	"License without this special exception.\n"
	"\n"
	"This special exception was added by the Free Software Foundation in\n"
	"version 2.2 of Bison.\n"
	"\n"
	"--------------------------------------------------------------------------------\n"
	"================================================================================\n"
	"--------------------------------------------------------------------------------\n"
	"\n"
	"The preprocessor has the core licenses stated above, plus an additional licence:\n"
	"\n"
	"Copyright (c) 2002, NVIDIA Corporation.\n"
	"\n"
	"NVIDIA Corporation(\042NVIDIA\042) supplies this software to you in\n"
	"consideration of your agreement to the following terms, and your use,\n"
	"installation, modification or redistribution of this NVIDIA software\n"
	"constitutes acceptance of these terms.  If you do not agree with these\n"
	"terms, please do not use, install, modify or redistribute this NVIDIA\n"
	"software.\n"
	"\n"
	"In consideration of your agreement to abide by the following terms, and\n"
	"subject to these terms, NVIDIA grants you a personal, non-exclusive\n"
	"license, under NVIDIA's copyrights in this original NVIDIA software (the\n"
	"\042NVIDIA Software\042), to use, reproduce, modify and redistribute the\n"
	"NVIDIA Software, with or without modifications, in source and/or binary\n"
	"forms; provided that if you redistribute the NVIDIA Software, you must\n"
	"retain the copyright notice of NVIDIA, this notice and the following\n"
	"text and disclaimers in all such redistributions of the NVIDIA Software.\n"
	"Neither the name, trademarks, service marks nor logos of NVIDIA\n"
	"Corporation may be used to endorse or promote products derived from the\n"
	"NVIDIA Software without specific prior written permission from NVIDIA.\n"
	"Except as expressly stated in this notice, no other rights or licenses\n"
	"express or implied, are granted by NVIDIA herein, including but not\n"
	"limited to any patent rights that may be infringed by your derivative\n"
	"works or by other works in which the NVIDIA Software may be\n"
	"incorporated. No hardware is licensed hereunder.\n"
	"\n"
	"THE NVIDIA SOFTWARE IS BEING PROVIDED ON AN \042AS IS\042 BASIS, WITHOUT\n"
	"WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED,\n"
	"INCLUDING WITHOUT LIMITATION, WARRANTIES OR CONDITIONS OF TITLE,\n"
	"NON-INFRINGEMENT, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR\n"
	"ITS USE AND OPERATION EITHER ALONE OR IN COMBINATION WITH OTHER\n"
	"PRODUCTS.\n"
	"\n"
	"IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT,\n"
	"INCIDENTAL, EXEMPLARY, CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED\n"
	"TO, LOST PROFITS; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF\n"
	"USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) OR ARISING IN ANY WAY\n"
	"OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE\n"
	"NVIDIA SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT,\n"
	"TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF\n"
	"NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
	"",

	"The FreeType Project LICENSE\n"
	"----------------------------\n"
	"\n"
	"2000-Feb-08\n"
	"\n"
	"Copyright 1996-2000 by\n"
	"David Turner, Robert Wilhelm, and Werner Lemberg\n"
	"\n"
	"\n"
	"\n"
	"Introduction\n"
	"============\n"
	"\n"
	"The FreeType  Project is distributed in  several archive packages;\n"
	"some of them may contain, in addition to the FreeType font engine,\n"
	"various tools and  contributions which rely on, or  relate to, the\n"
	"FreeType Project.\n"
	"\n"
	"This  license applies  to all  files found  in such  packages, and\n"
	"which do not  fall under their own explicit  license.  The license\n"
	"affects  thus  the  FreeType   font  engine,  the  test  programs,\n"
	"documentation and makefiles, at the very least.\n"
	"\n"
	"This  license   was  inspired  by  the  BSD,   Artistic,  and  IJG\n"
	"(Independent JPEG  Group) licenses, which  all encourage inclusion\n"
	"and  use of  free  software in  commercial  and freeware  products\n"
	"alike.  As a consequence, its main points are that:\n"
	"\n"
	"o We don't promise that this software works. However, we will be\n"
	"interested in any kind of bug reports. (`as is' distribution)\n"
	"\n"
	"o You can  use this software for whatever you  want, in parts or\n"
	"full form, without having to pay us. (`royalty-free' usage)\n"
	"\n"
	"o You may not pretend that  you wrote this software.  If you use\n"
	"it, or  only parts of it,  in a program,  you must acknowledge\n"
	"somewhere  in  your  documentation  that  you  have  used  the\n"
	"FreeType code. (`credits')\n"
	"\n"
	"We  specifically  permit  and  encourage  the  inclusion  of  this\n"
	"software, with  or without modifications,  in commercial products.\n"
	"We  disclaim  all warranties  covering  The  FreeType Project  and\n"
	"assume no liability related to The FreeType Project.\n"
	"\n"
	"\n"
	"Legal Terms\n"
	"===========\n"
	"\n"
	"0. Definitions\n"
	"--------------\n"
	"\n"
	"Throughout this license,  the terms `package', `FreeType Project',\n"
	"and  `FreeType  archive' refer  to  the  set  of files  originally\n"
	"distributed  by the  authors  (David Turner,  Robert Wilhelm,  and\n"
	"Werner Lemberg) as the `FreeType Project', be they named as alpha,\n"
	"beta or final release.\n"
	"\n"
	"`You' refers to  the licensee, or person using  the project, where\n"
	"`using' is a generic term including compiling the project's source\n"
	"code as  well as linking it  to form a  `program' or `executable'.\n"
	"This  program is  referred to  as  `a program  using the  FreeType\n"
	"engine'.\n"
	"\n"
	"This  license applies  to all  files distributed  in  the original\n"
	"FreeType  Project,   including  all  source   code,  binaries  and\n"
	"documentation,  unless  otherwise  stated   in  the  file  in  its\n"
	"original, unmodified form as  distributed in the original archive.\n"
	"If you are  unsure whether or not a particular  file is covered by\n"
	"this license, you must contact us to verify this.\n"
	"\n"
	"The FreeType  Project is copyright (C) 1996-2000  by David Turner,\n"
	"Robert Wilhelm, and Werner Lemberg.  All rights reserved except as\n"
	"specified below.\n"
	"\n"
	"1. No Warranty\n"
	"--------------\n"
	"\n"
	"THE FREETYPE PROJECT  IS PROVIDED `AS IS' WITHOUT  WARRANTY OF ANY\n"
	"KIND, EITHER  EXPRESS OR IMPLIED,  INCLUDING, BUT NOT  LIMITED TO,\n"
	"WARRANTIES  OF  MERCHANTABILITY   AND  FITNESS  FOR  A  PARTICULAR\n"
	"PURPOSE.  IN NO EVENT WILL ANY OF THE AUTHORS OR COPYRIGHT HOLDERS\n"
	"BE LIABLE  FOR ANY DAMAGES CAUSED  BY THE USE OR  THE INABILITY TO\n"
	"USE, OF THE FREETYPE PROJECT.\n"
	"\n"
	"2. Redistribution\n"
	"-----------------\n"
	"\n"
	"This  license  grants  a  worldwide, royalty-free,  perpetual  and\n"
	"irrevocable right  and license to use,  execute, perform, compile,\n"
	"display,  copy,   create  derivative  works   of,  distribute  and\n"
	"sublicense the  FreeType Project (in  both source and  object code\n"
	"forms)  and  derivative works  thereof  for  any  purpose; and  to\n"
	"authorize others  to exercise  some or all  of the  rights granted\n"
	"herein, subject to the following conditions:\n"
	"\n"
	"o Redistribution  of source code  must retain this  license file\n"
	"(`LICENSE.TXT') unaltered; any additions, deletions or changes\n"
	"to   the  original   files  must   be  clearly   indicated  in\n"
	"accompanying  documentation.   The  copyright notices  of  the\n"
	"unaltered, original  files must be preserved in  all copies of\n"
	"source files.\n"
	"\n"
	"o Redistribution in binary form must provide a  disclaimer  that\n"
	"states  that  the software is based in part of the work of the\n"
	"FreeType Team,  in  the  distribution  documentation.  We also\n"
	"encourage you to put an URL to the FreeType web page  in  your\n"
	"documentation, though this isn't mandatory.\n"
	"\n"
	"These conditions  apply to any  software derived from or  based on\n"
	"the FreeType Project,  not just the unmodified files.   If you use\n"
	"our work, you  must acknowledge us.  However, no  fee need be paid\n"
	"to us.\n"
	"\n"
	"3. Advertising\n"
	"--------------\n"
	"\n"
	"Neither the  FreeType authors and  contributors nor you  shall use\n"
	"the name of the  other for commercial, advertising, or promotional\n"
	"purposes without specific prior written permission.\n"
	"\n"
	"We suggest,  but do not require, that  you use one or  more of the\n"
	"following phrases to refer  to this software in your documentation\n"
	"or advertising  materials: `FreeType Project',  `FreeType Engine',\n"
	"`FreeType library', or `FreeType Distribution'.\n"
	"\n"
	"As  you have  not signed  this license,  you are  not  required to\n"
	"accept  it.   However,  as  the FreeType  Project  is  copyrighted\n"
	"material, only  this license, or  another one contracted  with the\n"
	"authors, grants you  the right to use, distribute,  and modify it.\n"
	"Therefore,  by  using,  distributing,  or modifying  the  FreeType\n"
	"Project, you indicate that you understand and accept all the terms\n"
	"of this license.\n"
	"\n"
	"4. Contacts\n"
	"-----------\n"
	"\n"
	"There are two mailing lists related to FreeType:\n"
	"\n"
	"o freetype@freetype.org\n"
	"\n"
	"Discusses general use and applications of FreeType, as well as\n"
	"future and  wanted additions to the  library and distribution.\n"
	"If  you are looking  for support,  start in  this list  if you\n"
	"haven't found anything to help you in the documentation.\n"
	"\n"
	"o devel@freetype.org\n"
	"\n"
	"Discusses bugs,  as well  as engine internals,  design issues,\n"
	"specific licenses, porting, etc.\n"
	"\n"
	"o http://www.freetype.org\n"
	"\n"
	"Holds the current  FreeType web page, which will  allow you to\n"
	"download  our  latest  development  version  and  read  online\n"
	"documentation.\n"
	"\n"
	"You can also contact us individually at:\n"
	"\n"
	"David Turner      <david.turner@freetype.org>\n"
	"Robert Wilhelm    <robert.wilhelm@freetype.org>\n"
	"Werner Lemberg    <werner.lemberg@freetype.org>\n"
	"",

	"HarfBuzz is licensed under the so-called \042Old MIT\042 license.  Details follow.\n"
	"For parts of HarfBuzz that are licensed under different licenses see individual\n"
	"files names COPYING in subdirectories where applicable.\n"
	"\n"
	"Copyright (C) 2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020  Google, Inc.\n"
	"Copyright (C) 2018,2019,2020  Ebrahim Byagowi\n"
	"Copyright (C) 2019,2020  Facebook, Inc.\n"
	"Copyright (C) 2012  Mozilla Foundation\n"
	"Copyright (C) 2011  Codethink Limited\n"
	"Copyright (C) 2008,2010  Nokia Corporation and/or its subsidiary(-ies)\n"
	"Copyright (C) 2009  Keith Stribley\n"
	"Copyright (C) 2009  Martin Hosken and SIL International\n"
	"Copyright (C) 2007  Chris Wilson\n"
	"Copyright (C) 2005,2006,2020,2021  Behdad Esfahbod\n"
	"Copyright (C) 2005  David Turner\n"
	"Copyright (C) 2004,2007,2008,2009,2010  Red Hat, Inc.\n"
	"Copyright (C) 1998-2004  David Turner and Werner Lemberg\n"
	"\n"
	"For full copyright notices consult the individual files in the package.\n"
	"\n"
	"\n"
	"Permission is hereby granted, without written agreement and without\n"
	"license or royalty fees, to use, copy, modify, and distribute this\n"
	"software and its documentation for any purpose, provided that the\n"
	"above copyright notice and the following two paragraphs appear in\n"
	"all copies of this software.\n"
	"\n"
	"IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR\n"
	"DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES\n"
	"ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN\n"
	"IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH\n"
	"DAMAGE.\n"
	"\n"
	"THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,\n"
	"BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND\n"
	"FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS\n"
	"ON AN \042AS IS\042 BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO\n"
	"PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.\n"
	"",

	"Mozilla Public License Version 2.0\n"
	"==================================\n"
	"\n"
	"1. Definitions\n"
	"--------------\n"
	"\n"
	"1.1. \042Contributor\042\n"
	"means each individual or legal entity that creates, contributes to\n"
	"the creation of, or owns Covered Software.\n"
	"\n"
	"1.2. \042Contributor Version\042\n"
	"means the combination of the Contributions of others (if any) used\n"
	"by a Contributor and that particular Contributor's Contribution.\n"
	"\n"
	"1.3. \042Contribution\042\n"
	"means Covered Software of a particular Contributor.\n"
	"\n"
	"1.4. \042Covered Software\042\n"
	"means Source Code Form to which the initial Contributor has attached\n"
	"the notice in Exhibit A, the Executable Form of such Source Code\n"
	"Form, and Modifications of such Source Code Form, in each case\n"
	"including portions thereof.\n"
	"\n"
	"1.5. \042Incompatible With Secondary Licenses\042\n"
	"means\n"
	"\n"
	"(a) that the initial Contributor has attached the notice described\n"
	"in Exhibit B to the Covered Software; or\n"
	"\n"
	"(b) that the Covered Software was made available under the terms of\n"
	"version 1.1 or earlier of the License, but not also under the\n"
	"terms of a Secondary License.\n"
	"\n"
	"1.6. \042Executable Form\042\n"
	"means any form of the work other than Source Code Form.\n"
	"\n"
	"1.7. \042Larger Work\042\n"
	"means a work that combines Covered Software with other material, in\n"
	"a separate file or files, that is not Covered Software.\n"
	"\n"
	"1.8. \042License\042\n"
	"means this document.\n"
	"\n"
	"1.9. \042Licensable\042\n"
	"means having the right to grant, to the maximum extent possible,\n"
	"whether at the time of the initial grant or subsequently, any and\n"
	"all of the rights conveyed by this License.\n"
	"\n"
	"1.10. \042Modifications\042\n"
	"means any of the following:\n"
	"\n"
	"(a) any file in Source Code Form that results from an addition to,\n"
	"deletion from, or modification of the contents of Covered\n"
	"Software; or\n"
	"\n"
	"(b) any new file in Source Code Form that contains any Covered\n"
	"Software.\n"
	"\n"
	"1.11. \042Patent Claims\042 of a Contributor\n"
	"means any patent claim(s), including without limitation, method,\n"
	"process, and apparatus claims, in any patent Licensable by such\n"
	"Contributor that would be infringed, but for the grant of the\n"
	"License, by the making, using, selling, offering for sale, having\n"
	"made, import, or transfer of either its Contributions or its\n"
	"Contributor Version.\n"
	"\n"
	"1.12. \042Secondary License\042\n"
	"means either the GNU General Public License, Version 2.0, the GNU\n"
	"Lesser General Public License, Version 2.1, the GNU Affero General\n"
	"Public License, Version 3.0, or any later versions of those\n"
	"licenses.\n"
	"\n"
	"1.13. \042Source Code Form\042\n"
	"means the form of the work preferred for making modifications.\n"
	"\n"
	"1.14. \042You\042 (or \042Your\042)\n"
	"means an individual or a legal entity exercising rights under this\n"
	"License. For legal entities, \042You\042 includes any entity that\n"
	"controls, is controlled by, or is under common control with You. For\n"
	"purposes of this definition, \042control\042 means (a) the power, direct\n"
	"or indirect, to cause the direction or management of such entity,\n"
	"whether by contract or otherwise, or (b) ownership of more than\n"
	"fifty percent (50%) of the outstanding shares or beneficial\n"
	"ownership of such entity.\n"
	"\n"
	"2. License Grants and Conditions\n"
	"--------------------------------\n"
	"\n"
	"2.1. Grants\n"
	"\n"
	"Each Contributor hereby grants You a world-wide, royalty-free,\n"
	"non-exclusive license:\n"
	"\n"
	"(a) under intellectual property rights (other than patent or trademark)\n"
	"Licensable by such Contributor to use, reproduce, make available,\n"
	"modify, display, perform, distribute, and otherwise exploit its\n"
	"Contributions, either on an unmodified basis, with Modifications, or\n"
	"as part of a Larger Work; and\n"
	"\n"
	"(b) under Patent Claims of such Contributor to make, use, sell, offer\n"
	"for sale, have made, import, and otherwise transfer either its\n"
	"Contributions or its Contributor Version.\n"
	"\n"
	"2.2. Effective Date\n"
	"\n"
	"The licenses granted in Section 2.1 with respect to any Contribution\n"
	"become effective for each Contribution on the date the Contributor first\n"
	"distributes such Contribution.\n"
	"\n"
	"2.3. Limitations on Grant Scope\n"
	"\n"
	"The licenses granted in this Section 2 are the only rights granted under\n"
	"this License. No additional rights or licenses will be implied from the\n"
	"distribution or licensing of Covered Software under this License.\n"
	"Notwithstanding Section 2.1(b) above, no patent license is granted by a\n"
	"Contributor:\n"
	"\n"
	"(a) for any code that a Contributor has removed from Covered Software;\n"
	"or\n"
	"\n"
	"(b) for infringements caused by: (i) Your and any other third party's\n"
	"modifications of Covered Software, or (ii) the combination of its\n"
	"Contributions with other software (except as part of its Contributor\n"
	"Version); or\n"
	"\n"
	"(c) under Patent Claims infringed by Covered Software in the absence of\n"
	"its Contributions.\n"
	"\n"
	"This License does not grant any rights in the trademarks, service marks,\n"
	"or logos of any Contributor (except as may be necessary to comply with\n"
	"the notice requirements in Section 3.4).\n"
	"\n"
	"2.4. Subsequent Licenses\n"
	"\n"
	"No Contributor makes additional grants as a result of Your choice to\n"
	"distribute the Covered Software under a subsequent version of this\n"
	"License (see Section 10.2) or under the terms of a Secondary License (if\n"
	"permitted under the terms of Section 3.3).\n"
	"\n"
	"2.5. Representation\n"
	"\n"
	"Each Contributor represents that the Contributor believes its\n"
	"Contributions are its original creation(s) or it has sufficient rights\n"
	"to grant the rights to its Contributions conveyed by this License.\n"
	"\n"
	"2.6. Fair Use\n"
	"\n"
	"This License is not intended to limit any rights You have under\n"
	"applicable copyright doctrines of fair use, fair dealing, or other\n"
	"equivalents.\n"
	"\n"
	"2.7. Conditions\n"
	"\n"
	"Sections 3.1, 3.2, 3.3, and 3.4 are conditions of the licenses granted\n"
	"in Section 2.1.\n"
	"\n"
	"3. Responsibilities\n"
	"-------------------\n"
	"\n"
	"3.1. Distribution of Source Form\n"
	"\n"
	"All distribution of Covered Software in Source Code Form, including any\n"
	"Modifications that You create or to which You contribute, must be under\n"
	"the terms of this License. You must inform recipients that the Source\n"
	"Code Form of the Covered Software is governed by the terms of this\n"
	"License, and how they can obtain a copy of this License. You may not\n"
	"attempt to alter or restrict the recipients' rights in the Source Code\n"
	"Form.\n"
	"\n"
	"3.2. Distribution of Executable Form\n"
	"\n"
	"If You distribute Covered Software in Executable Form then:\n"
	"\n"
	"(a) such Covered Software must also be made available in Source Code\n"
	"Form, as described in Section 3.1, and You must inform recipients of\n"
	"the Executable Form how they can obtain a copy of such Source Code\n"
	"Form by reasonable means in a timely manner, at a charge no more\n"
	"than the cost of distribution to the recipient; and\n"
	"\n"
	"(b) You may distribute such Executable Form under the terms of this\n"
	"License, or sublicense it under different terms, provided that the\n"
	"license for the Executable Form does not attempt to limit or alter\n"
	"the recipients' rights in the Source Code Form under this License.\n"
	"\n"
	"3.3. Distribution of a Larger Work\n"
	"\n"
	"You may create and distribute a Larger Work under terms of Your choice,\n"
	"provided that You also comply with the requirements of this License for\n"
	"the Covered Software. If the Larger Work is a combination of Covered\n"
	"Software with a work governed by one or more Secondary Licenses, and the\n"
	"Covered Software is not Incompatible With Secondary Licenses, this\n"
	"License permits You to additionally distribute such Covered Software\n"
	"under the terms of such Secondary License(s), so that the recipient of\n"
	"the Larger Work may, at their option, further distribute the Covered\n"
	"Software under the terms of either this License or such Secondary\n"
	"License(s).\n"
	"\n"
	"3.4. Notices\n"
	"\n"
	"You may not remove or alter the substance of any license notices\n"
	"(including copyright notices, patent notices, disclaimers of warranty,\n"
	"or limitations of liability) contained within the Source Code Form of\n"
	"the Covered Software, except that You may alter any license notices to\n"
	"the extent required to remedy known factual inaccuracies.\n"
	"\n"
	"3.5. Application of Additional Terms\n"
	"\n"
	"You may choose to offer, and to charge a fee for, warranty, support,\n"
	"indemnity or liability obligations to one or more recipients of Covered\n"
	"Software. However, You may do so only on Your own behalf, and not on\n"
	"behalf of any Contributor. You must make it absolutely clear that any\n"
	"such warranty, support, indemnity, or liability obligation is offered by\n"
	"You alone, and You hereby agree to indemnify every Contributor for any\n"
	"liability incurred by such Contributor as a result of warranty, support,\n"
	"indemnity or liability terms You offer. You may include additional\n"
	"disclaimers of warranty and limitations of liability specific to any\n"
	"jurisdiction.\n"
	"\n"
	"4. Inability to Comply Due to Statute or Regulation\n"
	"---------------------------------------------------\n"
	"\n"
	"If it is impossible for You to comply with any of the terms of this\n"
	"License with respect to some or all of the Covered Software due to\n"
	"statute, judicial order, or regulation then You must: (a) comply with\n"
	"the terms of this License to the maximum extent possible; and (b)\n"
	"describe the limitations and the code they affect. Such description must\n"
	"be placed in a text file included with all distributions of the Covered\n"
	"Software under this License. Except to the extent prohibited by statute\n"
	"or regulation, such description must be sufficiently detailed for a\n"
	"recipient of ordinary skill to be able to understand it.\n"
	"\n"
	"5. Termination\n"
	"--------------\n"
	"\n"
	"5.1. The rights granted under this License will terminate automatically\n"
	"if You fail to comply with any of its terms. However, if You become\n"
	"compliant, then the rights granted under this License from a particular\n"
	"Contributor are reinstated (a) provisionally, unless and until such\n"
	"Contributor explicitly and finally terminates Your grants, and (b) on an\n"
	"ongoing basis, if such Contributor fails to notify You of the\n"
	"non-compliance by some reasonable means prior to 60 days after You have\n"
	"come back into compliance. Moreover, Your grants from a particular\n"
	"Contributor are reinstated on an ongoing basis if such Contributor\n"
	"notifies You of the non-compliance by some reasonable means, this is the\n"
	"first time You have received notice of non-compliance with this License\n"
	"from such Contributor, and You become compliant prior to 30 days after\n"
	"Your receipt of the notice.\n"
	"\n"
	"5.2. If You initiate litigation against any entity by asserting a patent\n"
	"infringement claim (excluding declaratory judgment actions,\n"
	"counter-claims, and cross-claims) alleging that a Contributor Version\n"
	"directly or indirectly infringes any patent, then the rights granted to\n"
	"You by any and all Contributors for the Covered Software under Section\n"
	"2.1 of this License shall terminate.\n"
	"\n"
	"5.3. In the event of termination under Sections 5.1 or 5.2 above, all\n"
	"end user license agreements (excluding distributors and resellers) which\n"
	"have been validly granted by You or Your distributors under this License\n"
	"prior to termination shall survive termination.\n"
	"\n"
	"************************************************************************\n"
	"*                                                                      *\n"
	"*  6. Disclaimer of Warranty                                           *\n"
	"*  -------------------------                                           *\n"
	"*                                                                      *\n"
	"*  Covered Software is provided under this License on an \042as is\042       *\n"
	"*  basis, without warranty of any kind, either expressed, implied, or  *\n"
	"*  statutory, including, without limitation, warranties that the       *\n"
	"*  Covered Software is free of defects, merchantable, fit for a        *\n"
	"*  particular purpose or non-infringing. The entire risk as to the     *\n"
	"*  quality and performance of the Covered Software is with You.        *\n"
	"*  Should any Covered Software prove defective in any respect, You     *\n"
	"*  (not any Contributor) assume the cost of any necessary servicing,   *\n"
	"*  repair, or correction. This disclaimer of warranty constitutes an   *\n"
	"*  essential part of this License. No use of any Covered Software is   *\n"
	"*  authorized under this License except under this disclaimer.         *\n"
	"*                                                                      *\n"
	"************************************************************************\n"
	"\n"
	"************************************************************************\n"
	"*                                                                      *\n"
	"*  7. Limitation of Liability                                          *\n"
	"*  --------------------------                                          *\n"
	"*                                                                      *\n"
	"*  Under no circumstances and under no legal theory, whether tort      *\n"
	"*  (including negligence), contract, or otherwise, shall any           *\n"
	"*  Contributor, or anyone who distributes Covered Software as          *\n"
	"*  permitted above, be liable to You for any direct, indirect,         *\n"
	"*  special, incidental, or consequential damages of any character      *\n"
	"*  including, without limitation, damages for lost profits, loss of    *\n"
	"*  goodwill, work stoppage, computer failure or malfunction, or any    *\n"
	"*  and all other commercial damages or losses, even if such party      *\n"
	"*  shall have been informed of the possibility of such damages. This   *\n"
	"*  limitation of liability shall not apply to liability for death or   *\n"
	"*  personal injury resulting from such party's negligence to the       *\n"
	"*  extent applicable law prohibits such limitation. Some               *\n"
	"*  jurisdictions do not allow the exclusion or limitation of           *\n"
	"*  incidental or consequential damages, so this exclusion and          *\n"
	"*  limitation may not apply to You.                                    *\n"
	"*                                                                      *\n"
	"************************************************************************\n"
	"\n"
	"8. Litigation\n"
	"-------------\n"
	"\n"
	"Any litigation relating to this License may be brought only in the\n"
	"courts of a jurisdiction where the defendant maintains its principal\n"
	"place of business and such litigation shall be governed by laws of that\n"
	"jurisdiction, without reference to its conflict-of-law provisions.\n"
	"Nothing in this Section shall prevent a party's ability to bring\n"
	"cross-claims or counter-claims.\n"
	"\n"
	"9. Miscellaneous\n"
	"----------------\n"
	"\n"
	"This License represents the complete agreement concerning the subject\n"
	"matter hereof. If any provision of this License is held to be\n"
	"unenforceable, such provision shall be reformed only to the extent\n"
	"necessary to make it enforceable. Any law or regulation which provides\n"
	"that the language of a contract shall be construed against the drafter\n"
	"shall not be used to construe this License against a Contributor.\n"
	"\n"
	"10. Versions of the License\n"
	"---------------------------\n"
	"\n"
	"10.1. New Versions\n"
	"\n"
	"Mozilla Foundation is the license steward. Except as provided in Section\n"
	"10.3, no one other than the license steward has the right to modify or\n"
	"publish new versions of this License. Each version will be given a\n"
	"distinguishing version number.\n"
	"\n"
	"10.2. Effect of New Versions\n"
	"\n"
	"You may distribute the Covered Software under the terms of the version\n"
	"of the License under which You originally received the Covered Software,\n"
	"or under the terms of any subsequent version published by the license\n"
	"steward.\n"
	"\n"
	"10.3. Modified Versions\n"
	"\n"
	"If you create software not governed by this License, and you want to\n"
	"create a new license for such software, you may create and use a\n"
	"modified version of this License if you rename the license and remove\n"
	"any references to the name of the license steward (except to note that\n"
	"such modified license differs from this License).\n"
	"\n"
	"10.4. Distributing Source Code Form that is Incompatible With Secondary\n"
	"Licenses\n"
	"\n"
	"If You choose to distribute Source Code Form that is Incompatible With\n"
	"Secondary Licenses under the terms of this version of the License, the\n"
	"notice described in Exhibit B of this License must be attached.\n"
	"\n"
	"Exhibit A - Source Code Form License Notice\n"
	"-------------------------------------------\n"
	"\n"
	"This Source Code Form is subject to the terms of the Mozilla Public\n"
	"License, v. 2.0. If a copy of the MPL was not distributed with this\n"
	"file, You can obtain one at https://mozilla.org/MPL/2.0/.\n"
	"\n"
	"If it is not possible or desirable to put the notice in a particular\n"
	"file, then You may include the notice in a location (such as a LICENSE\n"
	"file in a relevant directory) where a recipient would be likely to look\n"
	"for such a notice.\n"
	"\n"
	"You may add additional accurate notices of copyright ownership.\n"
	"\n"
	"Exhibit B - \042Incompatible With Secondary Licenses\042 Notice\n"
	"---------------------------------------------------------\n"
	"\n"
	"This Source Code Form is \042Incompatible With Secondary Licenses\042, as\n"
	"defined by the Mozilla Public License, v. 2.0.\n"
	"",

	"PREAMBLE\n"
	"The goals of the Open Font License (OFL) are to stimulate worldwide\n"
	"development of collaborative font projects, to support the font creation\n"
	"efforts of academic and linguistic communities, and to provide a free and\n"
	"open framework in which fonts may be shared and improved in partnership\n"
	"with others.\n"
	"\n"
	"The OFL allows the licensed fonts to be used, studied, modified and\n"
	"redistributed freely as long as they are not sold by themselves. The\n"
	"fonts, including any derivative works, can be bundled, embedded,\n"
	"redistributed and/or sold with any software provided that any reserved\n"
	"names are not used by derivative works. The fonts and derivatives,\n"
	"however, cannot be released under any other type of license. The\n"
	"requirement for fonts to remain under this license does not apply\n"
	"to any document created using the fonts or their derivatives.\n"
	"\n"
	"DEFINITIONS\n"
	"\042Font Software\042 refers to the set of files released by the Copyright\n"
	"Holder(s) under this license and clearly marked as such. This may\n"
	"include source files, build scripts and documentation.\n"
	"\n"
	"\042Reserved Font Name\042 refers to any names specified as such after the\n"
	"copyright statement(s).\n"
	"\n"
	"\042Original Version\042 refers to the collection of Font Software components as\n"
	"distributed by the Copyright Holder(s).\n"
	"\n"
	"\042Modified Version\042 refers to any derivative made by adding to, deleting,\n"
	"or substituting -- in part or in whole -- any of the components of the\n"
	"Original Version, by changing formats or by porting the Font Software to a\n"
	"new environment.\n"
	"\n"
	"\042Author\042 refers to any designer, engineer, programmer, technical\n"
	"writer or other person who contributed to the Font Software.\n"
	"\n"
	"PERMISSION & CONDITIONS\n"
	"Permission is hereby granted, free of charge, to any person obtaining\n"
	"a copy of the Font Software, to use, study, copy, merge, embed, modify,\n"
	"redistribute, and sell modified and unmodified copies of the Font\n"
	"Software, subject to the following conditions:\n"
	"\n"
	"1) Neither the Font Software nor any of its individual components,\n"
	"in Original or Modified Versions, may be sold by itself.\n"
	"\n"
	"2) Original or Modified Versions of the Font Software may be bundled,\n"
	"redistributed and/or sold with any software, provided that each copy\n"
	"contains the above copyright notice and this license. These can be\n"
	"included either as stand-alone text files, human-readable headers or\n"
	"in the appropriate machine-readable metadata fields within text or\n"
	"binary files as long as those fields can be easily viewed by the user.\n"
	"\n"
	"3) No Modified Version of the Font Software may use the Reserved Font\n"
	"Name(s) unless explicit written permission is granted by the corresponding\n"
	"Copyright Holder. This restriction only applies to the primary font name as\n"
	"presented to the users.\n"
	"\n"
	"4) The name(s) of the Copyright Holder(s) or the Author(s) of the Font\n"
	"Software shall not be used to promote, endorse or advertise any\n"
	"Modified Version, except to acknowledge the contribution(s) of the\n"
	"Copyright Holder(s) and the Author(s) or with their explicit written\n"
	"permission.\n"
	"\n"
	"5) The Font Software, modified or unmodified, in part or in whole,\n"
	"must be distributed entirely under this license, and must not be\n"
	"distributed under any other license. The requirement for fonts to\n"
	"remain under this license does not apply to any document created\n"
	"using the Font Software.\n"
	"\n"
	"TERMINATION\n"
	"This license becomes null and void if any of the above conditions are\n"
	"not met.\n"
	"\n"
	"DISCLAIMER\n"
	"THE FONT SOFTWARE IS PROVIDED \042AS IS\042, WITHOUT WARRANTY OF ANY KIND,\n"
	"EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OF\n"
	"MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT\n"
	"OF COPYRIGHT, PATENT, TRADEMARK, OR OTHER RIGHT. IN NO EVENT SHALL THE\n"
	"COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\n"
	"INCLUDING ANY GENERAL, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL\n"
	"DAMAGES, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING\n"
	"FROM, OUT OF THE USE OR INABILITY TO USE THE FONT SOFTWARE.\n"
	"",

	"COPYRIGHT AND PERMISSION NOTICE (ICU 58 and later)\n"
	"\n"
	"Copyright (C) 1991-2020 Unicode, Inc. All rights reserved.\n"
	"Distributed under the Terms of Use in https://www.unicode.org/copyright.html.\n"
	"\n"
	"Permission is hereby granted, free of charge, to any person obtaining\n"
	"a copy of the Unicode data files and any associated documentation\n"
	"(the \042Data Files\042) or Unicode software and any associated documentation\n"
	"(the \042Software\042) to deal in the Data Files or Software\n"
	"without restriction, including without limitation the rights to use,\n"
	"copy, modify, merge, publish, distribute, and/or sell copies of\n"
	"the Data Files or Software, and to permit persons to whom the Data Files\n"
	"or Software are furnished to do so, provided that either\n"
	"(a) this copyright and permission notice appear with all copies\n"
	"of the Data Files or Software, or\n"
	"(b) this copyright and permission notice appear in associated\n"
	"Documentation.\n"
	"\n"
	"THE DATA FILES AND SOFTWARE ARE PROVIDED \042AS IS\042, WITHOUT WARRANTY OF\n"
	"ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE\n"
	"WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
	"NONINFRINGEMENT OF THIRD PARTY RIGHTS.\n"
	"IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS\n"
	"NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL\n"
	"DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,\n"
	"DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER\n"
	"TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR\n"
	"PERFORMANCE OF THE DATA FILES OR SOFTWARE.\n"
	"\n"
	"Except as contained in this notice, the name of a copyright holder\n"
	"shall not be used in advertising or otherwise to promote the sale,\n"
	"use or other dealings in these Data Files or Software without prior\n"
	"written authorization of the copyright holder.\n"
	"",

	"This is free and unencumbered software released into the public domain.\n"
	"\n"
	"Anyone is free to copy, modify, publish, use, compile, sell, or\n"
	"distribute this software, either in source code form or as a compiled\n"
	"binary, for any purpose, commercial or non-commercial, and by any\n"
	"means.\n"
	"\n"
	"In jurisdictions that recognize copyright laws, the author or authors\n"
	"of this software dedicate any and all copyright interest in the\n"
	"software to the public domain. We make this dedication for the benefit\n"
	"of the public at large and to the detriment of our heirs and\n"
	"successors. We intend this dedication to be an overt act of\n"
	"relinquishment in perpetuity of all present and future rights to this\n"
	"software under copyright law.\n"
	"\n"
	"THE SOFTWARE IS PROVIDED \042AS IS\042, WITHOUT WARRANTY OF ANY KIND,\n"
	"EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
	"MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
	"IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n"
	"OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n"
	"ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
	"OTHER DEALINGS IN THE SOFTWARE.\n"
	"\n"
	"For more information, please refer to <https://unlicense.org/>\n"
	"",

	"This software is provided 'as-is', without any express or implied\n"
	"warranty.  In no event will the authors be held liable for any damages\n"
	"arising from the use of this software.\n"
	"\n"
	"Permission is granted to anyone to use this software for any purpose,\n"
	"including commercial applications, and to alter it and redistribute it\n"
	"freely, subject to the following restrictions:\n"
	"\n"
	"1. The origin of this software must not be misrepresented; you must not\n"
	"claim that you wrote the original software. If you use this software\n"
	"in a product, an acknowledgment in the product documentation would be\n"
	"appreciated but is not required.\n"
	"2. Altered source versions must be plainly marked as such, and must not be\n"
	"misrepresented as being the original software.\n"
	"3. This notice may not be removed or altered from any source distribution.\n"
	"",

};

#endif // LICENSE_GEN_H
