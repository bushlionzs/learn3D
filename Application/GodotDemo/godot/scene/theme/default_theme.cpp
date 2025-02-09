/**************************************************************************/
/*  default_theme.cpp                                                     */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "default_theme.h"

#include "core/os/os.h"
#include "default_font.gen.h"
#include "scene/resources/gradient_texture.h"
#include "scene/resources/image_texture.h"
#include "scene/resources/style_box_flat.h"
#include "scene/resources/style_box_line.h"
#include "scene/resources/theme.h"
#include "scene/scene_string_names.h"
#include "scene/theme/theme_db.h"
#ifdef MODULE_SVG_ENABLED
#include "modules/svg/image_loader_svg.h"
#endif

static const int default_font_size = 16;

static float scale = 1.0;

static const int default_margin = 4;
static const int default_corner_radius = 3;

static Ref<StyleBoxFlat> make_flat_stylebox(Color p_color, float p_margin_left = default_margin, float p_margin_top = default_margin, float p_margin_right = default_margin, float p_margin_bottom = default_margin, int p_corner_radius = default_corner_radius, bool p_draw_center = true, int p_border_width = 0) {
	Ref<StyleBoxFlat> style(memnew(StyleBoxFlat));
	style->set_bg_color(p_color);
	style->set_content_margin_individual(Math::round(p_margin_left * scale), Math::round(p_margin_top * scale), Math::round(p_margin_right * scale), Math::round(p_margin_bottom * scale));

	style->set_corner_radius_all(Math::round(p_corner_radius * scale));
	style->set_anti_aliased(true);
	// Adjust level of detail based on the corners' effective sizes.
	style->set_corner_detail(MIN(Math::ceil(1.5 * p_corner_radius), 6) * scale);

	style->set_draw_center(p_draw_center);
	style->set_border_width_all(Math::round(p_border_width * scale));

	return style;
}

static Ref<StyleBoxFlat> sb_expand(Ref<StyleBoxFlat> p_sbox, float p_left, float p_top, float p_right, float p_bottom) {
	p_sbox->set_expand_margin(SIDE_LEFT, Math::round(p_left * scale));
	p_sbox->set_expand_margin(SIDE_TOP, Math::round(p_top * scale));
	p_sbox->set_expand_margin(SIDE_RIGHT, Math::round(p_right * scale));
	p_sbox->set_expand_margin(SIDE_BOTTOM, Math::round(p_bottom * scale));
	return p_sbox;
}

// See also `editor_generate_icon()` in `editor/themes/editor_icons.cpp`.
static Ref<ImageTexture> generate_icon(int p_index) {
	Ref<Image> img = memnew(Image);

#ifdef MODULE_SVG_ENABLED
	// Upsample icon generation only if the scale isn't an integer multiplier.
	// Generating upsampled icons is slower, and the benefit is hardly visible
	// with integer scales.
	const bool upsample = !Math::is_equal_approx(Math::round(scale), scale);

	Error err = ImageLoaderSVG::create_image_from_string(img, default_theme_icons_sources[p_index], scale, upsample, HashMap<Color, Color>());
	ERR_FAIL_COND_V_MSG(err != OK, Ref<ImageTexture>(), "Failed generating icon, unsupported or invalid SVG data in default theme.");
#else
	// If the SVG module is disabled, we can't really display the UI well, but at least we won't crash.
	// 16 pixels is used as it's the most common base size for Godot icons.
	img = Image::create_empty(Math::round(16 * scale), Math::round(16 * scale), false, Image::FORMAT_RGBA8);
#endif

	return ImageTexture::create_from_image(img);
}

static Ref<StyleBox> make_empty_stylebox(float p_margin_left = -1, float p_margin_top = -1, float p_margin_right = -1, float p_margin_bottom = -1) {
	Ref<StyleBox> style(memnew(StyleBoxEmpty));
	style->set_content_margin_individual(Math::round(p_margin_left * scale), Math::round(p_margin_top * scale), Math::round(p_margin_right * scale), Math::round(p_margin_bottom * scale));
	return style;
}


