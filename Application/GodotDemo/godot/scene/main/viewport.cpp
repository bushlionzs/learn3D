/**************************************************************************/
/*  viewport.cpp                                                          */
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

#include "viewport.h"

#include "core/config/project_settings.h"
#include "core/debugger/engine_debugger.h"
#include "core/string/translation.h"
#include "core/templates/pair.h"
#include "core/templates/sort_array.h"
#include "scene/2d/audio_listener_2d.h"
#include "scene/2d/camera_2d.h"
#include "scene/2d/physics/collision_object_2d.h"
#ifndef _3D_DISABLED
#include "scene/3d/audio_listener_3d.h"
#include "scene/3d/camera_3d.h"
#include "scene/3d/physics/collision_object_3d.h"
#include "scene/3d/world_environment.h"
#endif // _3D_DISABLED
#include "scene/main/canvas_layer.h"
#include "scene/main/window.h"
#include "scene/resources/mesh.h"
#include "scene/resources/world_2d.h"
#include "servers/audio_server.h"

void ViewportTexture::setup_local_to_scene() {
	// For the same target viewport, setup is only allowed once to prevent multiple free or multiple creations.
	if (!vp_changed) {
		return;
	}

	if (vp_pending) {
		return;
	}

	Node *loc_scene = get_local_scene();
	if (!loc_scene) {
		return;
	}

	if (vp) {
		vp->viewport_textures.erase(this);
		vp = nullptr;
	}

	if (loc_scene->is_ready()) {
		_setup_local_to_scene(loc_scene);
	} else {
		loc_scene->connect(SceneStringName(ready), callable_mp(this, &ViewportTexture::_setup_local_to_scene).bind(loc_scene), CONNECT_ONE_SHOT);
		vp_pending = true;
	}
}

void ViewportTexture::reset_local_to_scene() {
	vp_changed = true;

	if (vp) {
		vp->viewport_textures.erase(this);
		vp = nullptr;
	}

	if (proxy.is_valid() && proxy_ph.is_null()) {
		proxy_ph = RS::get_singleton()->texture_2d_placeholder_create();
		RS::get_singleton()->texture_proxy_update(proxy, proxy_ph);
	}
}

void ViewportTexture::set_viewport_path_in_scene(const NodePath &p_path) {
	if (path == p_path) {
		return;
	}

	path = p_path;

	reset_local_to_scene();

	if (get_local_scene() && !path.is_empty()) {
		setup_local_to_scene();
	} else {
		if (path.is_empty()) {
			vp_changed = false;
		}
		emit_changed();
	}
}

NodePath ViewportTexture::get_viewport_path_in_scene() const {
	return path;
}

int ViewportTexture::get_width() const {
	if (!vp) {
		_err_print_viewport_not_set();
		return 0;
	}
	return vp->size.width;
}

int ViewportTexture::get_height() const {
	if (!vp) {
		_err_print_viewport_not_set();
		return 0;
	}
	return vp->size.height;
}

Size2 ViewportTexture::get_size() const {
	if (!vp) {
		_err_print_viewport_not_set();
		return Size2();
	}
	return vp->size;
}

RID ViewportTexture::get_rid() const {
	if (proxy.is_null()) {
		proxy_ph = RS::get_singleton()->texture_2d_placeholder_create();
		proxy = RS::get_singleton()->texture_proxy_create(proxy_ph);
	}
	return proxy;
}

bool ViewportTexture::has_alpha() const {
	return false;
}

Ref<Image> ViewportTexture::get_image() const {
	if (!vp) {
		_err_print_viewport_not_set();
		return Ref<Image>();
	}
	return RS::get_singleton()->texture_2d_get(vp->texture_rid);
}

void ViewportTexture::_err_print_viewport_not_set() const {
	if (!vp_pending && !vp_changed) {
		ERR_PRINT("Viewport Texture must be set to use it.");
	}
}

void ViewportTexture::_setup_local_to_scene(const Node *p_loc_scene) {
	// Always reset this, even if this call fails with an error.
	vp_pending = false;

	Node *vpn = p_loc_scene->get_node_or_null(path);
	ERR_FAIL_NULL_MSG(vpn, "Path to node is invalid: '" + path + "'.");
	vp = Object::cast_to<Viewport>(vpn);
	ERR_FAIL_NULL_MSG(vp, "Path to node does not point to a viewport: '" + path + "'.");

	vp->viewport_textures.insert(this);

	ERR_FAIL_NULL(RenderingServer::get_singleton());
	if (proxy_ph.is_valid()) {
		RS::get_singleton()->texture_proxy_update(proxy, vp->texture_rid);
		RS::get_singleton()->free(proxy_ph);
		proxy_ph = RID();
	} else {
		ERR_FAIL_COND(proxy.is_valid()); // Should be invalid.
		proxy = RS::get_singleton()->texture_proxy_create(vp->texture_rid);
	}
	vp_changed = false;

	emit_changed();
}

void ViewportTexture::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_viewport_path_in_scene", "path"), &ViewportTexture::set_viewport_path_in_scene);
	ClassDB::bind_method(D_METHOD("get_viewport_path_in_scene"), &ViewportTexture::get_viewport_path_in_scene);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "viewport_path", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Viewport", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NODE_PATH_FROM_SCENE_ROOT), "set_viewport_path_in_scene", "get_viewport_path_in_scene");
}

ViewportTexture::ViewportTexture() {
	set_local_to_scene(true);
}

ViewportTexture::~ViewportTexture() {
	if (vp) {
		vp->viewport_textures.erase(this);
	}

	ERR_FAIL_NULL(RenderingServer::get_singleton());

	if (proxy_ph.is_valid()) {
		RS::get_singleton()->free(proxy_ph);
	}
	if (proxy.is_valid()) {
		RS::get_singleton()->free(proxy);
	}
}

void Viewport::_process_dirty_canvas_parent_orders() {
	
}

void Viewport::_sub_window_update_order() {
	
}

void Viewport::_sub_window_register(Window *p_window) {
	}

void Viewport::_sub_window_update(Window *p_window) {
	}

void Viewport::_sub_window_grab_focus(Window *p_window) {
	
}

void Viewport::_sub_window_remove(Window *p_window) {
	}

int Viewport::_sub_window_find(Window *p_window) const {
	

	return -1;
}

void Viewport::_update_viewport_path() {
	if (viewport_textures.is_empty()) {
		return;
	}

	Node *scene_root = get_scene_file_path().is_empty() ? get_owner() : this;
	if (!scene_root && is_inside_tree()) {
		scene_root = get_tree()->get_edited_scene_root();
	}
	if (scene_root && (scene_root == this || scene_root->is_ancestor_of(this))) {
		NodePath path_in_scene = scene_root->get_path_to(this);
		for (ViewportTexture *E : viewport_textures) {
			E->path = path_in_scene;
		}
	}
}


void Viewport::_process_picking() {
	
}

RID Viewport::get_viewport_rid() const {
	ERR_READ_THREAD_GUARD_V(RID());
	return viewport;
}

void Viewport::update_canvas_items() {
	
}

bool Viewport::_set_size(const Size2i &p_size, const Size2i &p_size_2d_override, bool p_allocated) {
	
	return true;
}

Size2i Viewport::_get_size() const {


	return size;
}

Size2i Viewport::_get_size_2d_override() const {
	return size_2d_override;
}

bool Viewport::_is_size_allocated() const {
	return size_allocated;
}

Rect2 Viewport::get_visible_rect() const {
	ERR_READ_THREAD_GUARD_V(Rect2());
	Rect2 r;

	

	return r;
}

void Viewport::canvas_parent_mark_dirty(Node *p_node) {
	
}

void Viewport::enable_canvas_transform_override(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	if (override_canvas_transform == p_enable) {
		return;
	}

	override_canvas_transform = p_enable;
	if (p_enable) {
		RenderingServer::get_singleton()->viewport_set_canvas_transform(viewport, find_world_2d()->get_canvas(), canvas_transform_override);
	} else {
		RenderingServer::get_singleton()->viewport_set_canvas_transform(viewport, find_world_2d()->get_canvas(), canvas_transform);
	}
}

bool Viewport::is_canvas_transform_override_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return override_canvas_transform;
}

void Viewport::set_canvas_transform_override(const Transform2D &p_transform) {
	ERR_MAIN_THREAD_GUARD;
	if (canvas_transform_override == p_transform) {
		return;
	}

	canvas_transform_override = p_transform;
	if (override_canvas_transform) {
		RenderingServer::get_singleton()->viewport_set_canvas_transform(viewport, find_world_2d()->get_canvas(), canvas_transform_override);
	}
}

Transform2D Viewport::get_canvas_transform_override() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return canvas_transform_override;
}

void Viewport::set_canvas_transform(const Transform2D &p_transform) {
	ERR_MAIN_THREAD_GUARD;
	canvas_transform = p_transform;

	if (!override_canvas_transform) {
		RenderingServer::get_singleton()->viewport_set_canvas_transform(viewport, find_world_2d()->get_canvas(), canvas_transform);
	}
}

Transform2D Viewport::get_canvas_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return canvas_transform;
}

void Viewport::_update_global_transform() {
	Transform2D sxform = stretch_transform * global_canvas_transform;

	RenderingServer::get_singleton()->viewport_set_global_canvas_transform(viewport, sxform);
}

void Viewport::set_global_canvas_transform(const Transform2D &p_transform) {
	ERR_MAIN_THREAD_GUARD;
	global_canvas_transform = p_transform;

	_update_global_transform();
}

Transform2D Viewport::get_global_canvas_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return global_canvas_transform;
}

void Viewport::_canvas_layer_add(CanvasLayer *p_canvas_layer) {
	canvas_layers.insert(p_canvas_layer);
}

void Viewport::_canvas_layer_remove(CanvasLayer *p_canvas_layer) {
	canvas_layers.erase(p_canvas_layer);
}

void Viewport::set_transparent_background(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	transparent_bg = p_enable;
	RS::get_singleton()->viewport_set_transparent_background(viewport, p_enable);
}

bool Viewport::has_transparent_background() const {
	ERR_READ_THREAD_GUARD_V(false);
	return transparent_bg;
}

void Viewport::set_use_hdr_2d(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	use_hdr_2d = p_enable;
	RS::get_singleton()->viewport_set_use_hdr_2d(viewport, p_enable);
}

bool Viewport::is_using_hdr_2d() const {
	ERR_READ_THREAD_GUARD_V(false);
	return use_hdr_2d;
}

void Viewport::set_world_2d(const Ref<World2D> &p_world_2d) {
	ERR_MAIN_THREAD_GUARD;
	if (world_2d == p_world_2d) {
		return;
	}

	if (is_inside_tree()) {
		RenderingServer::get_singleton()->viewport_remove_canvas(viewport, current_canvas);
	}

	if (world_2d.is_valid()) {
		world_2d->remove_viewport(this);
	}

	if (p_world_2d.is_valid()) {
		bool do_propagate = world_2d.is_valid() && is_inside_tree();
		world_2d = p_world_2d;
		if (do_propagate) {
			_propagate_world_2d_changed(this);
		}
	} else {
		WARN_PRINT("Invalid world_2d");
		world_2d = Ref<World2D>(memnew(World2D));
	}

	world_2d->register_viewport(this);
	_update_audio_listener_2d();

	if (is_inside_tree()) {
		current_canvas = find_world_2d()->get_canvas();
		RenderingServer::get_singleton()->viewport_attach_canvas(viewport, current_canvas);
	}
}

Ref<World2D> Viewport::find_world_2d() const {
	ERR_READ_THREAD_GUARD_V(Ref<World2D>());
	if (world_2d.is_valid()) {
		return world_2d;
	} else if (parent) {
		return parent->find_world_2d();
	} else {
		return Ref<World2D>();
	}
}

void Viewport::_propagate_drag_notification(Node *p_node, int p_what) {
	
}

Ref<World2D> Viewport::get_world_2d() const {
	ERR_READ_THREAD_GUARD_V(Ref<World2D>());
	return world_2d;
}

Transform2D Viewport::get_final_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return stretch_transform * global_canvas_transform;
}

void Viewport::_update_canvas_items(Node *p_node) {
	if (p_node != this) {
		Window *w = Object::cast_to<Window>(p_node);
		if (w && (!w->is_inside_tree() || !w->is_embedded())) {
			return;
		}

		CanvasItem *ci = Object::cast_to<CanvasItem>(p_node);
		if (ci) {
			ci->queue_redraw();
		}
	}

	int cc = p_node->get_child_count();

	for (int i = 0; i < cc; i++) {
		_update_canvas_items(p_node->get_child(i));
	}
}

Ref<ViewportTexture> Viewport::get_texture() const {
	ERR_READ_THREAD_GUARD_V(Ref<ViewportTexture>());
	return default_texture;
}

void Viewport::set_positional_shadow_atlas_size(int p_size) {
	ERR_MAIN_THREAD_GUARD;
	positional_shadow_atlas_size = p_size;
	RS::get_singleton()->viewport_set_positional_shadow_atlas_size(viewport, p_size, positional_shadow_atlas_16_bits);
}

int Viewport::get_positional_shadow_atlas_size() const {
	ERR_READ_THREAD_GUARD_V(0);
	return positional_shadow_atlas_size;
}

void Viewport::set_positional_shadow_atlas_16_bits(bool p_16_bits) {
	ERR_MAIN_THREAD_GUARD;
	if (positional_shadow_atlas_16_bits == p_16_bits) {
		return;
	}

	positional_shadow_atlas_16_bits = p_16_bits;
	RS::get_singleton()->viewport_set_positional_shadow_atlas_size(viewport, positional_shadow_atlas_size, positional_shadow_atlas_16_bits);
}

bool Viewport::get_positional_shadow_atlas_16_bits() const {
	ERR_READ_THREAD_GUARD_V(false);
	return positional_shadow_atlas_16_bits;
}
void Viewport::set_positional_shadow_atlas_quadrant_subdiv(int p_quadrant, PositionalShadowAtlasQuadrantSubdiv p_subdiv) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_quadrant, 4);
	ERR_FAIL_INDEX(p_subdiv, SHADOW_ATLAS_QUADRANT_SUBDIV_MAX);

	if (positional_shadow_atlas_quadrant_subdiv[p_quadrant] == p_subdiv) {
		return;
	}

	positional_shadow_atlas_quadrant_subdiv[p_quadrant] = p_subdiv;
	static const int subdiv[SHADOW_ATLAS_QUADRANT_SUBDIV_MAX] = { 0, 1, 4, 16, 64, 256, 1024 };

	RS::get_singleton()->viewport_set_positional_shadow_atlas_quadrant_subdivision(viewport, p_quadrant, subdiv[p_subdiv]);
}

Viewport::PositionalShadowAtlasQuadrantSubdiv Viewport::get_positional_shadow_atlas_quadrant_subdiv(int p_quadrant) const {
	ERR_READ_THREAD_GUARD_V(SHADOW_ATLAS_QUADRANT_SUBDIV_DISABLED);
	ERR_FAIL_INDEX_V(p_quadrant, 4, SHADOW_ATLAS_QUADRANT_SUBDIV_DISABLED);
	return positional_shadow_atlas_quadrant_subdiv[p_quadrant];
}

Ref<InputEvent> Viewport::_make_input_local(const Ref<InputEvent> &ev) {
	if (ev.is_null()) {
		return ev; // No transformation defined for null event
	}

	Transform2D ai = get_final_transform().affine_inverse();
	Ref<InputEventMouse> me = ev;
	if (me.is_valid()) {
		me = me->xformed_by(ai);
		// For InputEventMouse, the global position is not adjusted by ev->xformed_by() and needs to be set separately.
		me->set_global_position(me->get_position());
		return me;
	}
	return ev->xformed_by(ai);
}

Vector2 Viewport::get_mouse_position() const {
	return Vector2();
}

void Viewport::warp_mouse(const Vector2 &p_position) {

}

void Viewport::_gui_sort_roots() {
	
}








void Viewport::_gui_input_event(Ref<InputEvent> p_event) {
	
}



void Viewport::_gui_cleanup_internal_state(Ref<InputEvent> p_event) {
	
}


void Viewport::gui_set_root_order_dirty() {
	
}




void Viewport::_gui_remove_root_control(List<Control *>::Element *RI) {
	
}



Window *Viewport::get_base_window() const {
	return nullptr;
}

void Viewport::_gui_remove_focus_for_window(Node *p_window) {
	if (get_base_window() == p_window) {
		gui_release_focus();
	}
}


void Viewport::_gui_accept_event() {
	if (is_inside_tree()) {
		set_input_as_handled();
	}
}

void Viewport::_drop_mouse_focus() {
	
}

void Viewport::_drop_physics_mouseover(bool p_paused_only) {
	
}


void Viewport::_post_gui_grab_click_focus() {
	
}

///////////////////////////////

void Viewport::push_text_input(const String &p_text) {
	
}

Viewport::SubWindowResize Viewport::_sub_window_get_resize_margin(Window *p_subwindow, const Point2 &p_point) {
	if (p_subwindow->get_flag(Window::FLAG_BORDERLESS) || p_subwindow->get_flag(Window::FLAG_RESIZE_DISABLED)) {
		return SUB_WINDOW_RESIZE_DISABLED;
	}

	Rect2i r = Rect2i(p_subwindow->get_position(), p_subwindow->get_size());

	int title_height = p_subwindow->theme_cache.title_height;

	r.position.y -= title_height;
	r.size.y += title_height;

	if (r.has_point(p_point)) {
		return SUB_WINDOW_RESIZE_DISABLED; // It's inside, so no resize.
	}

	int dist_x = p_point.x < r.position.x ? (p_point.x - r.position.x) : (p_point.x > (r.position.x + r.size.x) ? (p_point.x - (r.position.x + r.size.x)) : 0);
	int dist_y = p_point.y < r.position.y ? (p_point.y - r.position.y) : (p_point.y > (r.position.y + r.size.y) ? (p_point.y - (r.position.y + r.size.y)) : 0);

	int limit = p_subwindow->theme_cache.resize_margin;

	if (ABS(dist_x) > limit) {
		return SUB_WINDOW_RESIZE_DISABLED;
	}

	if (ABS(dist_y) > limit) {
		return SUB_WINDOW_RESIZE_DISABLED;
	}

	if (dist_x < 0 && dist_y < 0) {
		return SUB_WINDOW_RESIZE_TOP_LEFT;
	}

	if (dist_x == 0 && dist_y < 0) {
		return SUB_WINDOW_RESIZE_TOP;
	}

	if (dist_x > 0 && dist_y < 0) {
		return SUB_WINDOW_RESIZE_TOP_RIGHT;
	}

	if (dist_x < 0 && dist_y == 0) {
		return SUB_WINDOW_RESIZE_LEFT;
	}

	if (dist_x > 0 && dist_y == 0) {
		return SUB_WINDOW_RESIZE_RIGHT;
	}

	if (dist_x < 0 && dist_y > 0) {
		return SUB_WINDOW_RESIZE_BOTTOM_LEFT;
	}

	if (dist_x == 0 && dist_y > 0) {
		return SUB_WINDOW_RESIZE_BOTTOM;
	}

	if (dist_x > 0 && dist_y > 0) {
		return SUB_WINDOW_RESIZE_BOTTOM_RIGHT;
	}

	return SUB_WINDOW_RESIZE_DISABLED;
}

bool Viewport::_sub_windows_forward_input(const Ref<InputEvent> &p_event) {
	

	return true;
}

void Viewport::_update_mouse_over() {
	
}

void Viewport::_update_mouse_over(Vector2 p_pos) {
	
}

void Viewport::_mouse_leave_viewport() {
	
}

void Viewport::_drop_mouse_over(Control *p_until_control) {
	
}

void Viewport::push_input(const Ref<InputEvent> &p_event, bool p_local_coords) {
	
}

#ifndef DISABLE_DEPRECATED
void Viewport::push_unhandled_input(const Ref<InputEvent> &p_event, bool p_local_coords) {
	ERR_MAIN_THREAD_GUARD;
	WARN_DEPRECATED_MSG(R"*(The "push_unhandled_input()" method is deprecated, use "push_input()" instead.)*");
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(p_event.is_null());

	local_input_handled = false;

	if (disable_input || !_can_consume_input_events()) {
		return;
	}

	if (Engine::get_singleton()->is_editor_hint() && get_tree()->get_edited_scene_root() && get_tree()->get_edited_scene_root()->is_ancestor_of(this)) {
		return;
	}

	Ref<InputEvent> ev;
	if (!p_local_coords) {
		ev = _make_input_local(p_event);
	} else {
		ev = p_event;
	}

	_push_unhandled_input_internal(ev);
}
#endif // DISABLE_DEPRECATED

void Viewport::_push_unhandled_input_internal(const Ref<InputEvent> &p_event) {
	// Shortcut Input.
	if (Object::cast_to<InputEventKey>(*p_event) != nullptr || Object::cast_to<InputEventShortcut>(*p_event) != nullptr || Object::cast_to<InputEventJoypadButton>(*p_event) != nullptr) {
		ERR_FAIL_COND(!is_inside_tree());
		get_tree()->_call_input_pause(shortcut_input_group, SceneTree::CALL_INPUT_TYPE_SHORTCUT_INPUT, p_event, this);
	}

	// Unhandled key Input - Used for performance reasons - This is called a lot less than _unhandled_input since it ignores MouseMotion, and to handle Unicode input with Alt / Ctrl modifiers after handling shortcuts.
	if (!is_input_handled() && (Object::cast_to<InputEventKey>(*p_event) != nullptr)) {
		ERR_FAIL_COND(!is_inside_tree());
		get_tree()->_call_input_pause(unhandled_key_input_group, SceneTree::CALL_INPUT_TYPE_UNHANDLED_KEY_INPUT, p_event, this);
	}

	// Unhandled Input.
	if (!is_input_handled()) {
		ERR_FAIL_COND(!is_inside_tree());
		get_tree()->_call_input_pause(unhandled_input_group, SceneTree::CALL_INPUT_TYPE_UNHANDLED_INPUT, p_event, this);
	}

	if (physics_object_picking && !is_input_handled()) {
		if (Input::get_singleton()->get_mouse_mode() != Input::MOUSE_MODE_CAPTURED &&
				(Object::cast_to<InputEventMouse>(*p_event) ||
						Object::cast_to<InputEventScreenDrag>(*p_event) ||
						Object::cast_to<InputEventScreenTouch>(*p_event)

								)) {
			physics_picking_events.push_back(p_event);
			set_input_as_handled();
		}
	}
}

void Viewport::set_physics_object_picking(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	physics_object_picking = p_enable;
	if (physics_object_picking) {
		add_to_group("_picking_viewports");
	} else {
		physics_picking_events.clear();
		if (is_in_group("_picking_viewports")) {
			remove_from_group("_picking_viewports");
		}
	}
}

bool Viewport::get_physics_object_picking() {
	ERR_READ_THREAD_GUARD_V(false);
	return physics_object_picking;
}

void Viewport::set_physics_object_picking_sort(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	physics_object_picking_sort = p_enable;
}

bool Viewport::get_physics_object_picking_sort() {
	ERR_READ_THREAD_GUARD_V(false);
	return physics_object_picking_sort;
}

void Viewport::set_physics_object_picking_first_only(bool p_enable) {
	physics_object_picking_first_only = p_enable;
}

bool Viewport::get_physics_object_picking_first_only() {
	return physics_object_picking_first_only;
}

Vector2 Viewport::get_camera_coords(const Vector2 &p_viewport_coords) const {
	ERR_READ_THREAD_GUARD_V(Vector2());
	Transform2D xf = stretch_transform * global_canvas_transform;
	return xf.xform(p_viewport_coords);
}

Vector2 Viewport::get_camera_rect_size() const {
	ERR_READ_THREAD_GUARD_V(Vector2());
	return size;
}

void Viewport::set_disable_input(bool p_disable) {
	ERR_MAIN_THREAD_GUARD;
	if (p_disable == disable_input) {
		return;
	}
	if (p_disable) {
		_drop_mouse_focus();
		_mouse_leave_viewport();

	}
	disable_input = p_disable;
}

bool Viewport::is_input_disabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return disable_input;
}

Variant Viewport::gui_get_drag_data() const {
	return Variant();
}

PackedStringArray Viewport::get_configuration_warnings() const {
	ERR_MAIN_THREAD_GUARD_V(PackedStringArray());
	PackedStringArray warnings = Node::get_configuration_warnings();

	if (size.x <= 1 || size.y <= 1) {
		warnings.push_back(RTR("The Viewport size must be greater than or equal to 2 pixels on both dimensions to render anything."));
	}
	return warnings;
}

void Viewport::gui_reset_canvas_sort_index() {

}

int Viewport::gui_get_canvas_sort_index() {
	return 0;
}

void Viewport::gui_release_focus() {
	
}



void Viewport::set_msaa_2d(MSAA p_msaa) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_msaa, MSAA_MAX);
	if (msaa_2d == p_msaa) {
		return;
	}
	msaa_2d = p_msaa;
	RS::get_singleton()->viewport_set_msaa_2d(viewport, RS::ViewportMSAA(p_msaa));
}

Viewport::MSAA Viewport::get_msaa_2d() const {
	ERR_READ_THREAD_GUARD_V(MSAA_DISABLED);
	return msaa_2d;
}

void Viewport::set_msaa_3d(MSAA p_msaa) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_msaa, MSAA_MAX);
	if (msaa_3d == p_msaa) {
		return;
	}
	msaa_3d = p_msaa;
	RS::get_singleton()->viewport_set_msaa_3d(viewport, RS::ViewportMSAA(p_msaa));
}

Viewport::MSAA Viewport::get_msaa_3d() const {
	ERR_READ_THREAD_GUARD_V(MSAA_DISABLED);
	return msaa_3d;
}

void Viewport::set_screen_space_aa(ScreenSpaceAA p_screen_space_aa) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_screen_space_aa, SCREEN_SPACE_AA_MAX);
	if (screen_space_aa == p_screen_space_aa) {
		return;
	}
	screen_space_aa = p_screen_space_aa;
	RS::get_singleton()->viewport_set_screen_space_aa(viewport, RS::ViewportScreenSpaceAA(p_screen_space_aa));
}

Viewport::ScreenSpaceAA Viewport::get_screen_space_aa() const {
	ERR_READ_THREAD_GUARD_V(SCREEN_SPACE_AA_DISABLED);
	return screen_space_aa;
}

void Viewport::set_use_taa(bool p_use_taa) {
	ERR_MAIN_THREAD_GUARD;
	if (use_taa == p_use_taa) {
		return;
	}
	use_taa = p_use_taa;
	RS::get_singleton()->viewport_set_use_taa(viewport, p_use_taa);
}

bool Viewport::is_using_taa() const {
	ERR_READ_THREAD_GUARD_V(false);
	return use_taa;
}

void Viewport::set_use_debanding(bool p_use_debanding) {
	ERR_MAIN_THREAD_GUARD;
	if (use_debanding == p_use_debanding) {
		return;
	}
	use_debanding = p_use_debanding;
	RS::get_singleton()->viewport_set_use_debanding(viewport, p_use_debanding);
}

bool Viewport::is_using_debanding() const {
	ERR_READ_THREAD_GUARD_V(false);
	return use_debanding;
}

void Viewport::set_mesh_lod_threshold(float p_pixels) {
	ERR_MAIN_THREAD_GUARD;
	mesh_lod_threshold = p_pixels;
	RS::get_singleton()->viewport_set_mesh_lod_threshold(viewport, mesh_lod_threshold);
}

float Viewport::get_mesh_lod_threshold() const {
	ERR_READ_THREAD_GUARD_V(0);
	return mesh_lod_threshold;
}

void Viewport::set_use_occlusion_culling(bool p_use_occlusion_culling) {
	ERR_MAIN_THREAD_GUARD;
	if (use_occlusion_culling == p_use_occlusion_culling) {
		return;
	}

	use_occlusion_culling = p_use_occlusion_culling;
	RS::get_singleton()->viewport_set_use_occlusion_culling(viewport, p_use_occlusion_culling);

	notify_property_list_changed();
}

bool Viewport::is_using_occlusion_culling() const {
	ERR_READ_THREAD_GUARD_V(false);
	return use_occlusion_culling;
}

void Viewport::set_debug_draw(DebugDraw p_debug_draw) {
	ERR_MAIN_THREAD_GUARD;
	debug_draw = p_debug_draw;
	RS::get_singleton()->viewport_set_debug_draw(viewport, RS::ViewportDebugDraw(p_debug_draw));
}

Viewport::DebugDraw Viewport::get_debug_draw() const {
	ERR_READ_THREAD_GUARD_V(DEBUG_DRAW_DISABLED);
	return debug_draw;
}

int Viewport::get_render_info(RenderInfoType p_type, RenderInfo p_info) {
	ERR_READ_THREAD_GUARD_V(0);
	return RS::get_singleton()->viewport_get_render_info(viewport, RS::ViewportRenderInfoType(p_type), RS::ViewportRenderInfo(p_info));
}

void Viewport::set_snap_controls_to_pixels(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	snap_controls_to_pixels = p_enable;
}

bool Viewport::is_snap_controls_to_pixels_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return snap_controls_to_pixels;
}

void Viewport::set_snap_2d_transforms_to_pixel(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	snap_2d_transforms_to_pixel = p_enable;
	RS::get_singleton()->viewport_set_snap_2d_transforms_to_pixel(viewport, snap_2d_transforms_to_pixel);
}

bool Viewport::is_snap_2d_transforms_to_pixel_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return snap_2d_transforms_to_pixel;
}

void Viewport::set_snap_2d_vertices_to_pixel(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	snap_2d_vertices_to_pixel = p_enable;
	RS::get_singleton()->viewport_set_snap_2d_vertices_to_pixel(viewport, snap_2d_vertices_to_pixel);
}

bool Viewport::is_snap_2d_vertices_to_pixel_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return snap_2d_vertices_to_pixel;
}

bool Viewport::gui_is_dragging() const {
	return false;
}

bool Viewport::gui_is_drag_successful() const {
	return false;
}

void Viewport::gui_cancel_drag() {
	
}

void Viewport::set_input_as_handled() {
	ERR_MAIN_THREAD_GUARD;
	if (!handle_input_locally) {
		ERR_FAIL_COND(!is_inside_tree());
		Viewport *vp = this;
		while (true) {
			if (Object::cast_to<Window>(vp)) {
				break;
			}
			if (!vp->get_parent()) {
				break;
			}
			vp = vp->get_parent()->get_viewport();
		}
		if (vp != this) {
			vp->set_input_as_handled();
			return;
		}
	}

	local_input_handled = true;
}

bool Viewport::is_input_handled() const {
	ERR_READ_THREAD_GUARD_V(false);
	if (!handle_input_locally) {
		ERR_FAIL_COND_V(!is_inside_tree(), false);
		const Viewport *vp = this;
		while (true) {
			if (Object::cast_to<Window>(vp)) {
				break;
			}
			if (!vp->get_parent()) {
				break;
			}
			vp = vp->get_parent()->get_viewport();
		}
		if (vp != this) {
			return vp->is_input_handled();
		}
	}
	return local_input_handled;
}

void Viewport::set_handle_input_locally(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	handle_input_locally = p_enable;
}

bool Viewport::is_handling_input_locally() const {
	ERR_READ_THREAD_GUARD_V(false);
	return handle_input_locally;
}

void Viewport::set_default_canvas_item_texture_filter(DefaultCanvasItemTextureFilter p_filter) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_filter, DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_MAX);

	if (default_canvas_item_texture_filter == p_filter) {
		return;
	}
	default_canvas_item_texture_filter = p_filter;
	switch (default_canvas_item_texture_filter) {
		case DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_filter(viewport, RS::CANVAS_ITEM_TEXTURE_FILTER_NEAREST);
			break;
		case DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_LINEAR:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_filter(viewport, RS::CANVAS_ITEM_TEXTURE_FILTER_LINEAR);
			break;
		case DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_LINEAR_WITH_MIPMAPS:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_filter(viewport, RS::CANVAS_ITEM_TEXTURE_FILTER_LINEAR_WITH_MIPMAPS);
			break;
		case DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST_WITH_MIPMAPS:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_filter(viewport, RS::CANVAS_ITEM_TEXTURE_FILTER_NEAREST_WITH_MIPMAPS);
			break;
		default: {
		}
	}
}

Viewport::DefaultCanvasItemTextureFilter Viewport::get_default_canvas_item_texture_filter() const {
	ERR_READ_THREAD_GUARD_V(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST);
	return default_canvas_item_texture_filter;
}

void Viewport::set_default_canvas_item_texture_repeat(DefaultCanvasItemTextureRepeat p_repeat) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_repeat, DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_MAX);

	if (default_canvas_item_texture_repeat == p_repeat) {
		return;
	}

	default_canvas_item_texture_repeat = p_repeat;

	switch (default_canvas_item_texture_repeat) {
		case DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_DISABLED:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_repeat(viewport, RS::CANVAS_ITEM_TEXTURE_REPEAT_DISABLED);
			break;
		case DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_ENABLED:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_repeat(viewport, RS::CANVAS_ITEM_TEXTURE_REPEAT_ENABLED);
			break;
		case DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_MIRROR:
			RS::get_singleton()->viewport_set_default_canvas_item_texture_repeat(viewport, RS::CANVAS_ITEM_TEXTURE_REPEAT_MIRROR);
			break;
		default: {
		}
	}
}

Viewport::DefaultCanvasItemTextureRepeat Viewport::get_default_canvas_item_texture_repeat() const {
	ERR_READ_THREAD_GUARD_V(DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_DISABLED);
	return default_canvas_item_texture_repeat;
}

void Viewport::set_vrs_mode(Viewport::VRSMode p_vrs_mode) {
	
}


DisplayServer::WindowID Viewport::get_window_id() const {
	ERR_READ_THREAD_GUARD_V(DisplayServer::INVALID_WINDOW_ID);
	return DisplayServer::MAIN_WINDOW_ID;
}

Viewport *Viewport::get_parent_viewport() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	ERR_FAIL_COND_V(!is_inside_tree(), nullptr);
	if (!get_parent()) {
		return nullptr; //root viewport
	}

	return get_parent()->get_viewport();
}



bool Viewport::is_embedding_subwindows() const {
	return false;
}

TypedArray<Window> Viewport::get_embedded_subwindows() const {
	TypedArray<Window> windows;
	

	return windows;
}

void Viewport::subwindow_set_popup_safe_rect(Window *p_window, const Rect2i &p_rect) {
	
}

Rect2i Viewport::subwindow_get_popup_safe_rect(Window *p_window) const {
	
		return Rect2i();
	
}

void Viewport::set_sdf_oversize(SDFOversize p_sdf_oversize) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_sdf_oversize, SDF_OVERSIZE_MAX);
	sdf_oversize = p_sdf_oversize;
	RS::get_singleton()->viewport_set_sdf_oversize_and_scale(viewport, RS::ViewportSDFOversize(sdf_oversize), RS::ViewportSDFScale(sdf_scale));
}

Viewport::SDFOversize Viewport::get_sdf_oversize() const {
	ERR_READ_THREAD_GUARD_V(SDF_OVERSIZE_100_PERCENT);
	return sdf_oversize;
}

void Viewport::set_sdf_scale(SDFScale p_sdf_scale) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_INDEX(p_sdf_scale, SDF_SCALE_MAX);
	sdf_scale = p_sdf_scale;
	RS::get_singleton()->viewport_set_sdf_oversize_and_scale(viewport, RS::ViewportSDFOversize(sdf_oversize), RS::ViewportSDFScale(sdf_scale));
}

Viewport::SDFScale Viewport::get_sdf_scale() const {
	ERR_READ_THREAD_GUARD_V(SDF_SCALE_100_PERCENT);
	return sdf_scale;
}

Transform2D Viewport::get_screen_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return get_screen_transform_internal();
}

Transform2D Viewport::get_screen_transform_internal(bool p_absolute_position) const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	return get_final_transform();
}

void Viewport::update_mouse_cursor_state() {
	// Updates need to happen in Window, because SubViewportContainers might be hidden behind other Controls.
	Window *base_window = get_base_window();
	if (base_window) {
		base_window->update_mouse_cursor_state();
	}
}

void Viewport::set_canvas_cull_mask(uint32_t p_canvas_cull_mask) {
	ERR_MAIN_THREAD_GUARD;
	canvas_cull_mask = p_canvas_cull_mask;
	RenderingServer::get_singleton()->viewport_set_canvas_cull_mask(viewport, canvas_cull_mask);
}

uint32_t Viewport::get_canvas_cull_mask() const {
	ERR_READ_THREAD_GUARD_V(0);
	return canvas_cull_mask;
}

void Viewport::set_canvas_cull_mask_bit(uint32_t p_layer, bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	ERR_FAIL_UNSIGNED_INDEX(p_layer, 32);
	if (p_enable) {
		set_canvas_cull_mask(canvas_cull_mask | (1 << p_layer));
	} else {
		set_canvas_cull_mask(canvas_cull_mask & (~(1 << p_layer)));
	}
}

bool Viewport::get_canvas_cull_mask_bit(uint32_t p_layer) const {
	ERR_READ_THREAD_GUARD_V(false);
	ERR_FAIL_UNSIGNED_INDEX_V(p_layer, 32, false);
	return (canvas_cull_mask & (1 << p_layer));
}

void Viewport::_update_audio_listener_2d() {
	
}

void Viewport::_audio_listener_2d_set(AudioListener2D *p_audio_listener) {
	
}

void Viewport::_audio_listener_2d_remove(AudioListener2D *p_audio_listener) {
	if (audio_listener_2d == p_audio_listener) {
		audio_listener_2d = nullptr;
	}
}

void Viewport::_camera_2d_set(Camera2D *p_camera_2d) {
	camera_2d = p_camera_2d;
}

void Viewport::_cleanup_mouseover_colliders(bool p_clean_all_frames, bool p_paused_only, uint64_t p_frame_reference) {
	
}

AudioListener2D *Viewport::get_audio_listener_2d() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return audio_listener_2d;
}

void Viewport::set_as_audio_listener_2d(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	if (p_enable == is_audio_listener_2d_enabled) {
		return;
	}

	is_audio_listener_2d_enabled = p_enable;
	_update_audio_listener_2d();
}

bool Viewport::is_audio_listener_2d() const {
	ERR_READ_THREAD_GUARD_V(false);
	return is_audio_listener_2d_enabled;
}

Camera2D *Viewport::get_camera_2d() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return camera_2d;
}

void Viewport::assign_next_enabled_camera_2d(const StringName &p_camera_group) {
	ERR_MAIN_THREAD_GUARD;
	List<Node *> camera_list;
	get_tree()->get_nodes_in_group(p_camera_group, &camera_list);

	Camera2D *new_camera = nullptr;
	for (Node *E : camera_list) {
		Camera2D *cam = Object::cast_to<Camera2D>(E);
		if (!cam) {
			continue; // Non-camera node (e.g. ParallaxBackground).
		}

		
	}

	_camera_2d_set(new_camera);
	if (!camera_2d) {
		set_canvas_transform(Transform2D());
	}
}

#ifndef _3D_DISABLED
AudioListener3D *Viewport::get_audio_listener_3d() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return audio_listener_3d;
}

void Viewport::set_as_audio_listener_3d(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	if (p_enable == is_audio_listener_3d_enabled) {
		return;
	}

	is_audio_listener_3d_enabled = p_enable;
	_update_audio_listener_3d();
}

bool Viewport::is_audio_listener_3d() const {
	ERR_READ_THREAD_GUARD_V(false);
	return is_audio_listener_3d_enabled;
}

void Viewport::_update_audio_listener_3d() {
	
}

void Viewport::_listener_transform_3d_changed_notify() {
}

void Viewport::_audio_listener_3d_set(AudioListener3D *p_listener) {
	if (audio_listener_3d == p_listener) {
		return;
	}

	audio_listener_3d = p_listener;

	_update_audio_listener_3d();
	_listener_transform_3d_changed_notify();
}

bool Viewport::_audio_listener_3d_add(AudioListener3D *p_listener) {
	audio_listener_3d_set.insert(p_listener);
	return audio_listener_3d_set.size() == 1;
}

void Viewport::_audio_listener_3d_remove(AudioListener3D *p_listener) {
	audio_listener_3d_set.erase(p_listener);
	if (audio_listener_3d == p_listener) {
		audio_listener_3d = nullptr;
	}
}

void Viewport::_audio_listener_3d_make_next_current(AudioListener3D *p_exclude) {
	if (audio_listener_3d_set.size() > 0) {
		for (AudioListener3D *E : audio_listener_3d_set) {
			if (p_exclude == E) {
				continue;
			}
			if (!E->is_inside_tree()) {
				continue;
			}
			if (audio_listener_3d != nullptr) {
				return;
			}

		
		}
	} else {
		// Attempt to reset listener to the camera position.
		if (camera_3d != nullptr) {
			_update_audio_listener_3d();
			_camera_3d_transform_changed_notify();
		}
	}
}

void Viewport::_collision_object_3d_input_event(CollisionObject3D *p_object, Camera3D *p_camera, const Ref<InputEvent> &p_input_event, const Vector3 &p_pos, const Vector3 &p_normal, int p_shape) {
	Transform3D object_transform = p_object->get_global_transform();
	Transform3D camera_transform = p_camera->get_global_transform();
	ObjectID id = p_object->get_instance_id();

	// Avoid sending the fake event unnecessarily if nothing really changed in the context.
	if (object_transform == physics_last_object_transform && camera_transform == physics_last_camera_transform && physics_last_id == id) {
		Ref<InputEventMouseMotion> mm = p_input_event;
		if (mm.is_valid() && mm->get_device() == InputEvent::DEVICE_ID_INTERNAL) {
			return; // Discarded.
		}
	}
	p_object->_input_event_call(camera_3d, p_input_event, p_pos, p_normal, p_shape);
	physics_last_object_transform = object_transform;
	physics_last_camera_transform = camera_transform;
	physics_last_id = id;
}

Camera3D *Viewport::get_camera_3d() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return camera_3d;
}

void Viewport::_camera_3d_transform_changed_notify() {
}

void Viewport::_camera_3d_set(Camera3D *p_camera) {
	if (camera_3d == p_camera) {
		return;
	}

	if (camera_3d) {
		camera_3d->notification(Camera3D::NOTIFICATION_LOST_CURRENT);
	}

	camera_3d = p_camera;

	if (!camera_3d_override) {
		if (camera_3d) {
			RenderingServer::get_singleton()->viewport_attach_camera(viewport, camera_3d->get_camera());
		} else {
			RenderingServer::get_singleton()->viewport_attach_camera(viewport, RID());
		}
	}

	if (camera_3d) {
		camera_3d->notification(Camera3D::NOTIFICATION_BECAME_CURRENT);
	}

	_update_audio_listener_3d();
	_camera_3d_transform_changed_notify();
}

bool Viewport::_camera_3d_add(Camera3D *p_camera) {
	camera_3d_set.insert(p_camera);
	return camera_3d_set.size() == 1;
}

void Viewport::_camera_3d_remove(Camera3D *p_camera) {
	camera_3d_set.erase(p_camera);
	if (camera_3d == p_camera) {
		_camera_3d_set(nullptr);
	}
}

void Viewport::_camera_3d_make_next_current(Camera3D *p_exclude) {
	for (Camera3D *E : camera_3d_set) {
		if (p_exclude == E) {
			continue;
		}
		if (!E->is_inside_tree()) {
			continue;
		}
		if (camera_3d != nullptr) {
			return;
		}

		E->make_current();
	}
}

void Viewport::enable_camera_3d_override(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	if (p_enable == camera_3d_override) {
		return;
	}

	if (p_enable) {
		camera_3d_override.rid = RenderingServer::get_singleton()->camera_create();
	} else {
		RenderingServer::get_singleton()->free(camera_3d_override.rid);
		camera_3d_override.rid = RID();
	}

	if (p_enable) {
		RenderingServer::get_singleton()->viewport_attach_camera(viewport, camera_3d_override.rid);
	} else if (camera_3d) {
		RenderingServer::get_singleton()->viewport_attach_camera(viewport, camera_3d->get_camera());
	} else {
		RenderingServer::get_singleton()->viewport_attach_camera(viewport, RID());
	}
}

void Viewport::set_camera_3d_override_perspective(real_t p_fovy_degrees, real_t p_z_near, real_t p_z_far) {
	ERR_MAIN_THREAD_GUARD;
	if (camera_3d_override) {
		if (camera_3d_override.fov == p_fovy_degrees && camera_3d_override.z_near == p_z_near &&
				camera_3d_override.z_far == p_z_far && camera_3d_override.projection == Camera3DOverrideData::PROJECTION_PERSPECTIVE) {
			return;
		}

		camera_3d_override.fov = p_fovy_degrees;
		camera_3d_override.z_near = p_z_near;
		camera_3d_override.z_far = p_z_far;
		camera_3d_override.projection = Camera3DOverrideData::PROJECTION_PERSPECTIVE;

		RenderingServer::get_singleton()->camera_set_perspective(camera_3d_override.rid, camera_3d_override.fov, camera_3d_override.z_near, camera_3d_override.z_far);
	}
}

void Viewport::set_camera_3d_override_orthogonal(real_t p_size, real_t p_z_near, real_t p_z_far) {
	ERR_MAIN_THREAD_GUARD;
	if (camera_3d_override) {
		if (camera_3d_override.size == p_size && camera_3d_override.z_near == p_z_near &&
				camera_3d_override.z_far == p_z_far && camera_3d_override.projection == Camera3DOverrideData::PROJECTION_ORTHOGONAL) {
			return;
		}

		camera_3d_override.size = p_size;
		camera_3d_override.z_near = p_z_near;
		camera_3d_override.z_far = p_z_far;
		camera_3d_override.projection = Camera3DOverrideData::PROJECTION_ORTHOGONAL;

		RenderingServer::get_singleton()->camera_set_orthogonal(camera_3d_override.rid, camera_3d_override.size, camera_3d_override.z_near, camera_3d_override.z_far);
	}
}

void Viewport::set_disable_3d(bool p_disable) {
	ERR_MAIN_THREAD_GUARD;
	disable_3d = p_disable;
	RenderingServer::get_singleton()->viewport_set_disable_3d(viewport, disable_3d);
}

bool Viewport::is_3d_disabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return disable_3d;
}

bool Viewport::is_camera_3d_override_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return camera_3d_override;
}

void Viewport::set_camera_3d_override_transform(const Transform3D &p_transform) {
	ERR_MAIN_THREAD_GUARD;
	if (camera_3d_override) {
		camera_3d_override.transform = p_transform;
		RenderingServer::get_singleton()->camera_set_transform(camera_3d_override.rid, p_transform);
	}
}

Transform3D Viewport::get_camera_3d_override_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform3D());
	if (camera_3d_override) {
		return camera_3d_override.transform;
	}

	return Transform3D();
}

Ref<World3D> Viewport::get_world_3d() const {
	ERR_READ_THREAD_GUARD_V(Ref<World3D>());
	return world_3d;
}

Ref<World3D> Viewport::find_world_3d() const {
	ERR_READ_THREAD_GUARD_V(Ref<World3D>());
	if (own_world_3d.is_valid()) {
		return own_world_3d;
	} else if (world_3d.is_valid()) {
		return world_3d;
	} else if (parent) {
		return parent->find_world_3d();
	} else {
		return Ref<World3D>();
	}
}

void Viewport::set_world_3d(const Ref<World3D> &p_world_3d) {
	ERR_MAIN_THREAD_GUARD;
	if (world_3d == p_world_3d) {
		return;
	}

	if (is_inside_tree()) {
		_propagate_exit_world_3d(this);
	}

	if (own_world_3d.is_valid() && world_3d.is_valid()) {
		world_3d->disconnect_changed(callable_mp(this, &Viewport::_own_world_3d_changed));
	}

	world_3d = p_world_3d;

	if (own_world_3d.is_valid()) {
		if (world_3d.is_valid()) {
			own_world_3d = world_3d->duplicate();
			world_3d->connect_changed(callable_mp(this, &Viewport::_own_world_3d_changed));
		} else {
			own_world_3d = Ref<World3D>(memnew(World3D));
		}
	}

	if (is_inside_tree()) {
		_propagate_enter_world_3d(this);
	}

	if (is_inside_tree()) {
		RenderingServer::get_singleton()->viewport_set_scenario(viewport, find_world_3d()->get_scenario());
	}

	_update_audio_listener_3d();
}

void Viewport::_own_world_3d_changed() {
	ERR_FAIL_COND(world_3d.is_null());
	ERR_FAIL_COND(own_world_3d.is_null());

	if (is_inside_tree()) {
		_propagate_exit_world_3d(this);
	}

	own_world_3d = world_3d->duplicate();

	if (is_inside_tree()) {
		_propagate_enter_world_3d(this);
	}

	if (is_inside_tree()) {
		RenderingServer::get_singleton()->viewport_set_scenario(viewport, find_world_3d()->get_scenario());
	}

	_update_audio_listener_3d();
}

void Viewport::set_use_own_world_3d(bool p_use_own_world_3d) {
	ERR_MAIN_THREAD_GUARD;
	if (p_use_own_world_3d == own_world_3d.is_valid()) {
		return;
	}

	if (is_inside_tree()) {
		_propagate_exit_world_3d(this);
	}

	if (p_use_own_world_3d) {
		if (world_3d.is_valid()) {
			own_world_3d = world_3d->duplicate();
			world_3d->connect_changed(callable_mp(this, &Viewport::_own_world_3d_changed));
		} else {
			own_world_3d = Ref<World3D>(memnew(World3D));
		}
	} else {
		own_world_3d = Ref<World3D>();
		if (world_3d.is_valid()) {
			world_3d->disconnect_changed(callable_mp(this, &Viewport::_own_world_3d_changed));
		}
	}

	if (is_inside_tree()) {
		_propagate_enter_world_3d(this);
	}

	if (is_inside_tree()) {
		RenderingServer::get_singleton()->viewport_set_scenario(viewport, find_world_3d()->get_scenario());
	}

	_update_audio_listener_3d();
}

bool Viewport::is_using_own_world_3d() const {
	ERR_READ_THREAD_GUARD_V(false);
	return own_world_3d.is_valid();
}

void Viewport::_propagate_enter_world_3d(Node *p_node) {
	if (p_node != this) {
		if (!p_node->is_inside_tree()) { //may not have entered scene yet
			return;
		}

		if (Object::cast_to<Node3D>(p_node) || Object::cast_to<WorldEnvironment>(p_node)) {
			p_node->notification(Node3D::NOTIFICATION_ENTER_WORLD);
		} else {
			Viewport *v = Object::cast_to<Viewport>(p_node);
			if (v) {
				if (v->world_3d.is_valid() || v->own_world_3d.is_valid()) {
					return;
				}
			}
		}
	}

	for (int i = 0; i < p_node->get_child_count(); i++) {
		_propagate_enter_world_3d(p_node->get_child(i));
	}
}

void Viewport::_propagate_exit_world_3d(Node *p_node) {
	if (p_node != this) {
		if (!p_node->is_inside_tree()) { //may have exited scene already
			return;
		}

		if (Object::cast_to<Node3D>(p_node) || Object::cast_to<WorldEnvironment>(p_node)) {
			p_node->notification(Node3D::NOTIFICATION_EXIT_WORLD);
		} else {
			Viewport *v = Object::cast_to<Viewport>(p_node);
			if (v) {
				if (v->world_3d.is_valid() || v->own_world_3d.is_valid()) {
					return;
				}
			}
		}
	}

	for (int i = 0; i < p_node->get_child_count(); i++) {
		_propagate_exit_world_3d(p_node->get_child(i));
	}
}

void Viewport::set_use_xr(bool p_use_xr) {
	
}

bool Viewport::is_using_xr() {
	ERR_READ_THREAD_GUARD_V(false);
	return use_xr;
}

void Viewport::set_scaling_3d_mode(Scaling3DMode p_scaling_3d_mode) {
	ERR_MAIN_THREAD_GUARD;
	if (scaling_3d_mode == p_scaling_3d_mode) {
		return;
	}

	scaling_3d_mode = p_scaling_3d_mode;
	RS::get_singleton()->viewport_set_scaling_3d_mode(viewport, (RS::ViewportScaling3DMode)(int)p_scaling_3d_mode);
}

Viewport::Scaling3DMode Viewport::get_scaling_3d_mode() const {
	ERR_READ_THREAD_GUARD_V(SCALING_3D_MODE_BILINEAR);
	return scaling_3d_mode;
}

void Viewport::set_scaling_3d_scale(float p_scaling_3d_scale) {
	ERR_MAIN_THREAD_GUARD;
	// Clamp to reasonable values that are actually useful.
	// Values above 2.0 don't serve a practical purpose since the viewport
	// isn't displayed with mipmaps.
	scaling_3d_scale = CLAMP(p_scaling_3d_scale, 0.1, 2.0);

	RS::get_singleton()->viewport_set_scaling_3d_scale(viewport, scaling_3d_scale);
}

float Viewport::get_scaling_3d_scale() const {
	ERR_READ_THREAD_GUARD_V(0);
	return scaling_3d_scale;
}

void Viewport::set_fsr_sharpness(float p_fsr_sharpness) {
	ERR_MAIN_THREAD_GUARD;
	if (fsr_sharpness == p_fsr_sharpness) {
		return;
	}

	if (p_fsr_sharpness < 0.0f) {
		p_fsr_sharpness = 0.0f;
	}

	fsr_sharpness = p_fsr_sharpness;
	RS::get_singleton()->viewport_set_fsr_sharpness(viewport, p_fsr_sharpness);
}

float Viewport::get_fsr_sharpness() const {
	ERR_READ_THREAD_GUARD_V(0);
	return fsr_sharpness;
}

void Viewport::set_texture_mipmap_bias(float p_texture_mipmap_bias) {
	ERR_MAIN_THREAD_GUARD;
	if (texture_mipmap_bias == p_texture_mipmap_bias) {
		return;
	}

	texture_mipmap_bias = p_texture_mipmap_bias;
	RS::get_singleton()->viewport_set_texture_mipmap_bias(viewport, p_texture_mipmap_bias);
}

float Viewport::get_texture_mipmap_bias() const {
	ERR_READ_THREAD_GUARD_V(0);
	return texture_mipmap_bias;
}

#endif // _3D_DISABLED

void Viewport::_propagate_world_2d_changed(Node *p_node) {
	if (p_node != this) {
		if (Object::cast_to<CanvasItem>(p_node)) {
			p_node->notification(CanvasItem::NOTIFICATION_WORLD_2D_CHANGED);
		} else {
			Viewport *v = Object::cast_to<Viewport>(p_node);
			if (v) {
				if (v->world_2d.is_valid()) {
					return;
				}
			}
		}
	}

	for (int i = 0; i < p_node->get_child_count(); ++i) {
		_propagate_world_2d_changed(p_node->get_child(i));
	}
}

void Viewport::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_world_2d", "world_2d"), &Viewport::set_world_2d);
	ClassDB::bind_method(D_METHOD("get_world_2d"), &Viewport::get_world_2d);
	ClassDB::bind_method(D_METHOD("find_world_2d"), &Viewport::find_world_2d);

	ClassDB::bind_method(D_METHOD("set_canvas_transform", "xform"), &Viewport::set_canvas_transform);
	ClassDB::bind_method(D_METHOD("get_canvas_transform"), &Viewport::get_canvas_transform);

	ClassDB::bind_method(D_METHOD("set_global_canvas_transform", "xform"), &Viewport::set_global_canvas_transform);
	ClassDB::bind_method(D_METHOD("get_global_canvas_transform"), &Viewport::get_global_canvas_transform);
	ClassDB::bind_method(D_METHOD("get_final_transform"), &Viewport::get_final_transform);
	ClassDB::bind_method(D_METHOD("get_screen_transform"), &Viewport::get_screen_transform);

	ClassDB::bind_method(D_METHOD("get_visible_rect"), &Viewport::get_visible_rect);
	ClassDB::bind_method(D_METHOD("set_transparent_background", "enable"), &Viewport::set_transparent_background);
	ClassDB::bind_method(D_METHOD("has_transparent_background"), &Viewport::has_transparent_background);
	ClassDB::bind_method(D_METHOD("set_use_hdr_2d", "enable"), &Viewport::set_use_hdr_2d);
	ClassDB::bind_method(D_METHOD("is_using_hdr_2d"), &Viewport::is_using_hdr_2d);

	ClassDB::bind_method(D_METHOD("set_msaa_2d", "msaa"), &Viewport::set_msaa_2d);
	ClassDB::bind_method(D_METHOD("get_msaa_2d"), &Viewport::get_msaa_2d);

	ClassDB::bind_method(D_METHOD("set_msaa_3d", "msaa"), &Viewport::set_msaa_3d);
	ClassDB::bind_method(D_METHOD("get_msaa_3d"), &Viewport::get_msaa_3d);

	ClassDB::bind_method(D_METHOD("set_screen_space_aa", "screen_space_aa"), &Viewport::set_screen_space_aa);
	ClassDB::bind_method(D_METHOD("get_screen_space_aa"), &Viewport::get_screen_space_aa);

	ClassDB::bind_method(D_METHOD("set_use_taa", "enable"), &Viewport::set_use_taa);
	ClassDB::bind_method(D_METHOD("is_using_taa"), &Viewport::is_using_taa);

	ClassDB::bind_method(D_METHOD("set_use_debanding", "enable"), &Viewport::set_use_debanding);
	ClassDB::bind_method(D_METHOD("is_using_debanding"), &Viewport::is_using_debanding);

	ClassDB::bind_method(D_METHOD("set_use_occlusion_culling", "enable"), &Viewport::set_use_occlusion_culling);
	ClassDB::bind_method(D_METHOD("is_using_occlusion_culling"), &Viewport::is_using_occlusion_culling);

	ClassDB::bind_method(D_METHOD("set_debug_draw", "debug_draw"), &Viewport::set_debug_draw);
	ClassDB::bind_method(D_METHOD("get_debug_draw"), &Viewport::get_debug_draw);

	ClassDB::bind_method(D_METHOD("get_render_info", "type", "info"), &Viewport::get_render_info);

	ClassDB::bind_method(D_METHOD("get_texture"), &Viewport::get_texture);

	ClassDB::bind_method(D_METHOD("set_physics_object_picking", "enable"), &Viewport::set_physics_object_picking);
	ClassDB::bind_method(D_METHOD("get_physics_object_picking"), &Viewport::get_physics_object_picking);
	ClassDB::bind_method(D_METHOD("set_physics_object_picking_sort", "enable"), &Viewport::set_physics_object_picking_sort);
	ClassDB::bind_method(D_METHOD("get_physics_object_picking_sort"), &Viewport::get_physics_object_picking_sort);
	ClassDB::bind_method(D_METHOD("set_physics_object_picking_first_only", "enable"), &Viewport::set_physics_object_picking_first_only);
	ClassDB::bind_method(D_METHOD("get_physics_object_picking_first_only"), &Viewport::get_physics_object_picking_first_only);

	ClassDB::bind_method(D_METHOD("get_viewport_rid"), &Viewport::get_viewport_rid);
	ClassDB::bind_method(D_METHOD("push_text_input", "text"), &Viewport::push_text_input);
	ClassDB::bind_method(D_METHOD("push_input", "event", "in_local_coords"), &Viewport::push_input, DEFVAL(false));
#ifndef DISABLE_DEPRECATED
	ClassDB::bind_method(D_METHOD("push_unhandled_input", "event", "in_local_coords"), &Viewport::push_unhandled_input, DEFVAL(false));
#endif // DISABLE_DEPRECATED

	ClassDB::bind_method(D_METHOD("get_mouse_position"), &Viewport::get_mouse_position);
	ClassDB::bind_method(D_METHOD("warp_mouse", "position"), &Viewport::warp_mouse);
	ClassDB::bind_method(D_METHOD("update_mouse_cursor_state"), &Viewport::update_mouse_cursor_state);

	ClassDB::bind_method(D_METHOD("gui_cancel_drag"), &Viewport::gui_cancel_drag);
	ClassDB::bind_method(D_METHOD("gui_get_drag_data"), &Viewport::gui_get_drag_data);
	ClassDB::bind_method(D_METHOD("gui_is_dragging"), &Viewport::gui_is_dragging);
	ClassDB::bind_method(D_METHOD("gui_is_drag_successful"), &Viewport::gui_is_drag_successful);

	ClassDB::bind_method(D_METHOD("gui_release_focus"), &Viewport::gui_release_focus);

	ClassDB::bind_method(D_METHOD("set_disable_input", "disable"), &Viewport::set_disable_input);
	ClassDB::bind_method(D_METHOD("is_input_disabled"), &Viewport::is_input_disabled);

	ClassDB::bind_method(D_METHOD("_gui_remove_focus_for_window"), &Viewport::_gui_remove_focus_for_window);

	ClassDB::bind_method(D_METHOD("set_positional_shadow_atlas_size", "size"), &Viewport::set_positional_shadow_atlas_size);
	ClassDB::bind_method(D_METHOD("get_positional_shadow_atlas_size"), &Viewport::get_positional_shadow_atlas_size);

	ClassDB::bind_method(D_METHOD("set_positional_shadow_atlas_16_bits", "enable"), &Viewport::set_positional_shadow_atlas_16_bits);
	ClassDB::bind_method(D_METHOD("get_positional_shadow_atlas_16_bits"), &Viewport::get_positional_shadow_atlas_16_bits);

	ClassDB::bind_method(D_METHOD("set_snap_controls_to_pixels", "enabled"), &Viewport::set_snap_controls_to_pixels);
	ClassDB::bind_method(D_METHOD("is_snap_controls_to_pixels_enabled"), &Viewport::is_snap_controls_to_pixels_enabled);

	ClassDB::bind_method(D_METHOD("set_snap_2d_transforms_to_pixel", "enabled"), &Viewport::set_snap_2d_transforms_to_pixel);
	ClassDB::bind_method(D_METHOD("is_snap_2d_transforms_to_pixel_enabled"), &Viewport::is_snap_2d_transforms_to_pixel_enabled);

	ClassDB::bind_method(D_METHOD("set_snap_2d_vertices_to_pixel", "enabled"), &Viewport::set_snap_2d_vertices_to_pixel);
	ClassDB::bind_method(D_METHOD("is_snap_2d_vertices_to_pixel_enabled"), &Viewport::is_snap_2d_vertices_to_pixel_enabled);

	ClassDB::bind_method(D_METHOD("set_positional_shadow_atlas_quadrant_subdiv", "quadrant", "subdiv"), &Viewport::set_positional_shadow_atlas_quadrant_subdiv);
	ClassDB::bind_method(D_METHOD("get_positional_shadow_atlas_quadrant_subdiv", "quadrant"), &Viewport::get_positional_shadow_atlas_quadrant_subdiv);

	ClassDB::bind_method(D_METHOD("set_input_as_handled"), &Viewport::set_input_as_handled);
	ClassDB::bind_method(D_METHOD("is_input_handled"), &Viewport::is_input_handled);

	ClassDB::bind_method(D_METHOD("set_handle_input_locally", "enable"), &Viewport::set_handle_input_locally);
	ClassDB::bind_method(D_METHOD("is_handling_input_locally"), &Viewport::is_handling_input_locally);

	ClassDB::bind_method(D_METHOD("set_default_canvas_item_texture_filter", "mode"), &Viewport::set_default_canvas_item_texture_filter);
	ClassDB::bind_method(D_METHOD("get_default_canvas_item_texture_filter"), &Viewport::get_default_canvas_item_texture_filter);

	ClassDB::bind_method(D_METHOD("is_embedding_subwindows"), &Viewport::is_embedding_subwindows);
	ClassDB::bind_method(D_METHOD("get_embedded_subwindows"), &Viewport::get_embedded_subwindows);

	ClassDB::bind_method(D_METHOD("set_canvas_cull_mask", "mask"), &Viewport::set_canvas_cull_mask);
	ClassDB::bind_method(D_METHOD("get_canvas_cull_mask"), &Viewport::get_canvas_cull_mask);

	ClassDB::bind_method(D_METHOD("set_canvas_cull_mask_bit", "layer", "enable"), &Viewport::set_canvas_cull_mask_bit);
	ClassDB::bind_method(D_METHOD("get_canvas_cull_mask_bit", "layer"), &Viewport::get_canvas_cull_mask_bit);

	ClassDB::bind_method(D_METHOD("set_default_canvas_item_texture_repeat", "mode"), &Viewport::set_default_canvas_item_texture_repeat);
	ClassDB::bind_method(D_METHOD("get_default_canvas_item_texture_repeat"), &Viewport::get_default_canvas_item_texture_repeat);

	ClassDB::bind_method(D_METHOD("set_sdf_oversize", "oversize"), &Viewport::set_sdf_oversize);
	ClassDB::bind_method(D_METHOD("get_sdf_oversize"), &Viewport::get_sdf_oversize);

	ClassDB::bind_method(D_METHOD("set_sdf_scale", "scale"), &Viewport::set_sdf_scale);
	ClassDB::bind_method(D_METHOD("get_sdf_scale"), &Viewport::get_sdf_scale);

	ClassDB::bind_method(D_METHOD("set_mesh_lod_threshold", "pixels"), &Viewport::set_mesh_lod_threshold);
	ClassDB::bind_method(D_METHOD("get_mesh_lod_threshold"), &Viewport::get_mesh_lod_threshold);

	ClassDB::bind_method(D_METHOD("_process_picking"), &Viewport::_process_picking);

	ClassDB::bind_method(D_METHOD("set_as_audio_listener_2d", "enable"), &Viewport::set_as_audio_listener_2d);
	ClassDB::bind_method(D_METHOD("is_audio_listener_2d"), &Viewport::is_audio_listener_2d);
	ClassDB::bind_method(D_METHOD("get_audio_listener_2d"), &Viewport::get_audio_listener_2d);
	ClassDB::bind_method(D_METHOD("get_camera_2d"), &Viewport::get_camera_2d);

#ifndef _3D_DISABLED
	ClassDB::bind_method(D_METHOD("set_world_3d", "world_3d"), &Viewport::set_world_3d);
	ClassDB::bind_method(D_METHOD("get_world_3d"), &Viewport::get_world_3d);
	ClassDB::bind_method(D_METHOD("find_world_3d"), &Viewport::find_world_3d);

	ClassDB::bind_method(D_METHOD("set_use_own_world_3d", "enable"), &Viewport::set_use_own_world_3d);
	ClassDB::bind_method(D_METHOD("is_using_own_world_3d"), &Viewport::is_using_own_world_3d);

	ClassDB::bind_method(D_METHOD("get_audio_listener_3d"), &Viewport::get_audio_listener_3d);
	ClassDB::bind_method(D_METHOD("get_camera_3d"), &Viewport::get_camera_3d);
	ClassDB::bind_method(D_METHOD("set_as_audio_listener_3d", "enable"), &Viewport::set_as_audio_listener_3d);
	ClassDB::bind_method(D_METHOD("is_audio_listener_3d"), &Viewport::is_audio_listener_3d);

	ClassDB::bind_method(D_METHOD("set_disable_3d", "disable"), &Viewport::set_disable_3d);
	ClassDB::bind_method(D_METHOD("is_3d_disabled"), &Viewport::is_3d_disabled);

	ClassDB::bind_method(D_METHOD("set_use_xr", "use"), &Viewport::set_use_xr);
	ClassDB::bind_method(D_METHOD("is_using_xr"), &Viewport::is_using_xr);

	ClassDB::bind_method(D_METHOD("set_scaling_3d_mode", "scaling_3d_mode"), &Viewport::set_scaling_3d_mode);
	ClassDB::bind_method(D_METHOD("get_scaling_3d_mode"), &Viewport::get_scaling_3d_mode);

	ClassDB::bind_method(D_METHOD("set_scaling_3d_scale", "scale"), &Viewport::set_scaling_3d_scale);
	ClassDB::bind_method(D_METHOD("get_scaling_3d_scale"), &Viewport::get_scaling_3d_scale);

	ClassDB::bind_method(D_METHOD("set_fsr_sharpness", "fsr_sharpness"), &Viewport::set_fsr_sharpness);
	ClassDB::bind_method(D_METHOD("get_fsr_sharpness"), &Viewport::get_fsr_sharpness);

	ClassDB::bind_method(D_METHOD("set_texture_mipmap_bias", "texture_mipmap_bias"), &Viewport::set_texture_mipmap_bias);
	ClassDB::bind_method(D_METHOD("get_texture_mipmap_bias"), &Viewport::get_texture_mipmap_bias);

	ClassDB::bind_method(D_METHOD("set_vrs_mode", "mode"), &Viewport::set_vrs_mode);




	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "disable_3d"), "set_disable_3d", "is_3d_disabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_xr"), "set_use_xr", "is_using_xr");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "own_world_3d"), "set_use_own_world_3d", "is_using_own_world_3d");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world_3d", PROPERTY_HINT_RESOURCE_TYPE, "World3D"), "set_world_3d", "get_world_3d");
#endif // _3D_DISABLED
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world_2d", PROPERTY_HINT_RESOURCE_TYPE, "World2D", PROPERTY_USAGE_NONE), "set_world_2d", "get_world_2d");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "transparent_bg"), "set_transparent_background", "has_transparent_background");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "handle_input_locally"), "set_handle_input_locally", "is_handling_input_locally");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "snap_2d_transforms_to_pixel"), "set_snap_2d_transforms_to_pixel", "is_snap_2d_transforms_to_pixel_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "snap_2d_vertices_to_pixel"), "set_snap_2d_vertices_to_pixel", "is_snap_2d_vertices_to_pixel_enabled");
	ADD_GROUP("Rendering", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "msaa_2d", PROPERTY_HINT_ENUM, String::utf8("Disabled (Fastest),2× (Average),4× (Slow),8× (Slowest)")), "set_msaa_2d", "get_msaa_2d");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "msaa_3d", PROPERTY_HINT_ENUM, String::utf8("Disabled (Fastest),2× (Average),4× (Slow),8× (Slowest)")), "set_msaa_3d", "get_msaa_3d");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "screen_space_aa", PROPERTY_HINT_ENUM, "Disabled (Fastest),FXAA (Fast)"), "set_screen_space_aa", "get_screen_space_aa");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_taa"), "set_use_taa", "is_using_taa");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_debanding"), "set_use_debanding", "is_using_debanding");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_occlusion_culling"), "set_use_occlusion_culling", "is_using_occlusion_culling");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mesh_lod_threshold", PROPERTY_HINT_RANGE, "0,1024,0.1"), "set_mesh_lod_threshold", "get_mesh_lod_threshold");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "debug_draw", PROPERTY_HINT_ENUM, "Disabled,Unshaded,Lighting,Overdraw,Wireframe,Normal Buffer,VoxelGI Albedo,VoxelGI Lighting,VoxelGI Emission,Shadow Atlas,Directional Shadow Map,Scene Luminance,SSAO,SSIL,Directional Shadow Splits,Decal Atlas,SDFGI Cascades,SDFGI Probes,VoxelGI/SDFGI Buffer,Disable Mesh LOD,OmniLight3D Cluster,SpotLight3D Cluster,Decal Cluster,ReflectionProbe Cluster,Occlusion Culling Buffer,Motion Vectors,Internal Buffer"), "set_debug_draw", "get_debug_draw");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_hdr_2d"), "set_use_hdr_2d", "is_using_hdr_2d");

#ifndef _3D_DISABLED
	ADD_GROUP("Scaling 3D", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "scaling_3d_mode", PROPERTY_HINT_ENUM, "Bilinear (Fastest),FSR 1.0 (Fast),FSR 2.2 (Slow)"), "set_scaling_3d_mode", "get_scaling_3d_mode");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scaling_3d_scale", PROPERTY_HINT_RANGE, "0.25,2.0,0.01"), "set_scaling_3d_scale", "get_scaling_3d_scale");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "texture_mipmap_bias", PROPERTY_HINT_RANGE, "-2,2,0.001"), "set_texture_mipmap_bias", "get_texture_mipmap_bias");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fsr_sharpness", PROPERTY_HINT_RANGE, "0,2,0.1"), "set_fsr_sharpness", "get_fsr_sharpness");
	ADD_GROUP("Variable Rate Shading", "vrs_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "vrs_mode", PROPERTY_HINT_ENUM, "Disabled,Texture,Depth buffer,XR"), "set_vrs_mode", "get_vrs_mode");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "vrs_update_mode", PROPERTY_HINT_ENUM, "Disabled,Once,Always"), "set_vrs_update_mode", "get_vrs_update_mode");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "vrs_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_vrs_texture", "get_vrs_texture");
#endif
	ADD_GROUP("Canvas Items", "canvas_item_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "canvas_item_default_texture_filter", PROPERTY_HINT_ENUM, "Nearest,Linear,Linear Mipmap,Nearest Mipmap"), "set_default_canvas_item_texture_filter", "get_default_canvas_item_texture_filter");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "canvas_item_default_texture_repeat", PROPERTY_HINT_ENUM, "Disabled,Enabled,Mirror"), "set_default_canvas_item_texture_repeat", "get_default_canvas_item_texture_repeat");
	ADD_GROUP("Audio Listener", "audio_listener_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "audio_listener_enable_2d"), "set_as_audio_listener_2d", "is_audio_listener_2d");
#ifndef _3D_DISABLED
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "audio_listener_enable_3d"), "set_as_audio_listener_3d", "is_audio_listener_3d");
#endif // _3D_DISABLED
	ADD_GROUP("Physics", "physics_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "physics_object_picking"), "set_physics_object_picking", "get_physics_object_picking");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "physics_object_picking_sort"), "set_physics_object_picking_sort", "get_physics_object_picking_sort");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "physics_object_picking_first_only"), "set_physics_object_picking_first_only", "get_physics_object_picking_first_only");
	ADD_GROUP("GUI", "gui_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "gui_disable_input"), "set_disable_input", "is_input_disabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "gui_snap_controls_to_pixels"), "set_snap_controls_to_pixels", "is_snap_controls_to_pixels_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "gui_embed_subwindows"), "set_embedding_subwindows", "is_embedding_subwindows");
	ADD_GROUP("SDF", "sdf_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sdf_oversize", PROPERTY_HINT_ENUM, "100%,120%,150%,200%"), "set_sdf_oversize", "get_sdf_oversize");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sdf_scale", PROPERTY_HINT_ENUM, "100%,50%,25%"), "set_sdf_scale", "get_sdf_scale");
	ADD_GROUP("Positional Shadow Atlas", "positional_shadow_atlas_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "positional_shadow_atlas_size"), "set_positional_shadow_atlas_size", "get_positional_shadow_atlas_size");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "positional_shadow_atlas_16_bits"), "set_positional_shadow_atlas_16_bits", "get_positional_shadow_atlas_16_bits");
	ADD_PROPERTYI(PropertyInfo(Variant::INT, "positional_shadow_atlas_quad_0", PROPERTY_HINT_ENUM, "Disabled,1 Shadow,4 Shadows,16 Shadows,64 Shadows,256 Shadows,1024 Shadows"), "set_positional_shadow_atlas_quadrant_subdiv", "get_positional_shadow_atlas_quadrant_subdiv", 0);
	ADD_PROPERTYI(PropertyInfo(Variant::INT, "positional_shadow_atlas_quad_1", PROPERTY_HINT_ENUM, "Disabled,1 Shadow,4 Shadows,16 Shadows,64 Shadows,256 Shadows,1024 Shadows"), "set_positional_shadow_atlas_quadrant_subdiv", "get_positional_shadow_atlas_quadrant_subdiv", 1);
	ADD_PROPERTYI(PropertyInfo(Variant::INT, "positional_shadow_atlas_quad_2", PROPERTY_HINT_ENUM, "Disabled,1 Shadow,4 Shadows,16 Shadows,64 Shadows,256 Shadows,1024 Shadows"), "set_positional_shadow_atlas_quadrant_subdiv", "get_positional_shadow_atlas_quadrant_subdiv", 2);
	ADD_PROPERTYI(PropertyInfo(Variant::INT, "positional_shadow_atlas_quad_3", PROPERTY_HINT_ENUM, "Disabled,1 Shadow,4 Shadows,16 Shadows,64 Shadows,256 Shadows,1024 Shadows"), "set_positional_shadow_atlas_quadrant_subdiv", "get_positional_shadow_atlas_quadrant_subdiv", 3);
	ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM2D, "canvas_transform", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NONE), "set_canvas_transform", "get_canvas_transform");
	ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM2D, "global_canvas_transform", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NONE), "set_global_canvas_transform", "get_global_canvas_transform");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "canvas_cull_mask", PROPERTY_HINT_LAYERS_2D_RENDER), "set_canvas_cull_mask", "get_canvas_cull_mask");

	ADD_SIGNAL(MethodInfo("size_changed"));
	ADD_SIGNAL(MethodInfo("gui_focus_changed", PropertyInfo(Variant::OBJECT, "node", PROPERTY_HINT_RESOURCE_TYPE, "Control")));

	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_DISABLED);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_1);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_4);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_16);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_64);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_256);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_1024);
	BIND_ENUM_CONSTANT(SHADOW_ATLAS_QUADRANT_SUBDIV_MAX);

	BIND_ENUM_CONSTANT(SCALING_3D_MODE_BILINEAR);
	BIND_ENUM_CONSTANT(SCALING_3D_MODE_FSR);
	BIND_ENUM_CONSTANT(SCALING_3D_MODE_FSR2);
	BIND_ENUM_CONSTANT(SCALING_3D_MODE_MAX);

	BIND_ENUM_CONSTANT(MSAA_DISABLED);
	BIND_ENUM_CONSTANT(MSAA_2X);
	BIND_ENUM_CONSTANT(MSAA_4X);
	BIND_ENUM_CONSTANT(MSAA_8X);
	BIND_ENUM_CONSTANT(MSAA_MAX);

	BIND_ENUM_CONSTANT(SCREEN_SPACE_AA_DISABLED);
	BIND_ENUM_CONSTANT(SCREEN_SPACE_AA_FXAA);
	BIND_ENUM_CONSTANT(SCREEN_SPACE_AA_MAX);

	BIND_ENUM_CONSTANT(RENDER_INFO_OBJECTS_IN_FRAME);
	BIND_ENUM_CONSTANT(RENDER_INFO_PRIMITIVES_IN_FRAME);
	BIND_ENUM_CONSTANT(RENDER_INFO_DRAW_CALLS_IN_FRAME);
	BIND_ENUM_CONSTANT(RENDER_INFO_MAX);

	BIND_ENUM_CONSTANT(RENDER_INFO_TYPE_VISIBLE);
	BIND_ENUM_CONSTANT(RENDER_INFO_TYPE_SHADOW);
	BIND_ENUM_CONSTANT(RENDER_INFO_TYPE_CANVAS);
	BIND_ENUM_CONSTANT(RENDER_INFO_TYPE_MAX);

	BIND_ENUM_CONSTANT(DEBUG_DRAW_DISABLED);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_UNSHADED);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_LIGHTING);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_OVERDRAW);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_WIREFRAME);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_NORMAL_BUFFER);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_VOXEL_GI_ALBEDO);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_VOXEL_GI_LIGHTING);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_VOXEL_GI_EMISSION);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SHADOW_ATLAS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_DIRECTIONAL_SHADOW_ATLAS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SCENE_LUMINANCE);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SSAO);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SSIL);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_PSSM_SPLITS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_DECAL_ATLAS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SDFGI);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_SDFGI_PROBES);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_GI_BUFFER);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_DISABLE_LOD);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_CLUSTER_OMNI_LIGHTS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_CLUSTER_SPOT_LIGHTS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_CLUSTER_DECALS);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_CLUSTER_REFLECTION_PROBES);
	BIND_ENUM_CONSTANT(DEBUG_DRAW_OCCLUDERS)
	BIND_ENUM_CONSTANT(DEBUG_DRAW_MOTION_VECTORS)
	BIND_ENUM_CONSTANT(DEBUG_DRAW_INTERNAL_BUFFER);

	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_LINEAR);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_LINEAR_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_NEAREST_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_FILTER_MAX);

	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_DISABLED);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_ENABLED);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_MIRROR);
	BIND_ENUM_CONSTANT(DEFAULT_CANVAS_ITEM_TEXTURE_REPEAT_MAX);

	BIND_ENUM_CONSTANT(SDF_OVERSIZE_100_PERCENT);
	BIND_ENUM_CONSTANT(SDF_OVERSIZE_120_PERCENT);
	BIND_ENUM_CONSTANT(SDF_OVERSIZE_150_PERCENT);
	BIND_ENUM_CONSTANT(SDF_OVERSIZE_200_PERCENT);
	BIND_ENUM_CONSTANT(SDF_OVERSIZE_MAX);

	BIND_ENUM_CONSTANT(SDF_SCALE_100_PERCENT);
	BIND_ENUM_CONSTANT(SDF_SCALE_50_PERCENT);
	BIND_ENUM_CONSTANT(SDF_SCALE_25_PERCENT);
	BIND_ENUM_CONSTANT(SDF_SCALE_MAX);

	BIND_ENUM_CONSTANT(VRS_DISABLED);
	BIND_ENUM_CONSTANT(VRS_TEXTURE);
	BIND_ENUM_CONSTANT(VRS_XR);
	BIND_ENUM_CONSTANT(VRS_MAX);

	BIND_ENUM_CONSTANT(VRS_UPDATE_DISABLED);
	BIND_ENUM_CONSTANT(VRS_UPDATE_ONCE);
	BIND_ENUM_CONSTANT(VRS_UPDATE_ALWAYS);
	BIND_ENUM_CONSTANT(VRS_UPDATE_MAX);
}

void Viewport::_validate_property(PropertyInfo &p_property) const {
	
}

Viewport::Viewport() {
	world_2d = Ref<World2D>(memnew(World2D));
	world_2d->register_viewport(this);

	viewport = RenderingServer::get_singleton()->viewport_create();
	texture_rid = RenderingServer::get_singleton()->viewport_get_texture(viewport);

	default_texture.instantiate();
	default_texture->vp = const_cast<Viewport *>(this);
	viewport_textures.insert(default_texture.ptr());
	default_texture->proxy = RS::get_singleton()->texture_proxy_create(texture_rid);

	canvas_layers.insert(nullptr); // This eases picking code (interpreted as the canvas of the Viewport).

	set_positional_shadow_atlas_size(positional_shadow_atlas_size);

	for (int i = 0; i < 4; i++) {
		positional_shadow_atlas_quadrant_subdiv[i] = SHADOW_ATLAS_QUADRANT_SUBDIV_MAX;
	}
	set_positional_shadow_atlas_quadrant_subdiv(0, SHADOW_ATLAS_QUADRANT_SUBDIV_4);
	set_positional_shadow_atlas_quadrant_subdiv(1, SHADOW_ATLAS_QUADRANT_SUBDIV_4);
	set_positional_shadow_atlas_quadrant_subdiv(2, SHADOW_ATLAS_QUADRANT_SUBDIV_16);
	set_positional_shadow_atlas_quadrant_subdiv(3, SHADOW_ATLAS_QUADRANT_SUBDIV_64);

	set_mesh_lod_threshold(mesh_lod_threshold);

	String id = itos(get_instance_id());
	input_group = "_vp_input" + id;
	unhandled_input_group = "_vp_unhandled_input" + id;
	shortcut_input_group = "_vp_shortcut_input" + id;
	unhandled_key_input_group = "_vp_unhandled_key_input" + id;

#ifndef _3D_DISABLED
	set_scaling_3d_mode((Viewport::Scaling3DMode)(int)GLOBAL_GET("rendering/scaling_3d/mode"));
	set_scaling_3d_scale(GLOBAL_GET("rendering/scaling_3d/scale"));
	set_fsr_sharpness((float)GLOBAL_GET("rendering/scaling_3d/fsr_sharpness"));
	set_texture_mipmap_bias((float)GLOBAL_GET("rendering/textures/default_filters/texture_mipmap_bias"));
#endif // _3D_DISABLED

	set_sdf_oversize(sdf_oversize); // Set to server.

	// Physics interpolation mode for viewports is a special case.
	// Typically viewports will be housed within Controls,
	// and Controls default to PHYSICS_INTERPOLATION_MODE_OFF.
	// Viewports can thus inherit physics interpolation OFF, which is unexpected.
	// Setting to ON allows each viewport to have a fresh interpolation state.
	set_physics_interpolation_mode(Node::PHYSICS_INTERPOLATION_MODE_ON);
}

Viewport::~Viewport() {
	// Erase itself from viewport textures.
	for (ViewportTexture *E : viewport_textures) {
		E->vp = nullptr;
	}
	if (world_2d.is_valid()) {
		world_2d->remove_viewport(this);
	}
	ERR_FAIL_NULL(RenderingServer::get_singleton());
	RenderingServer::get_singleton()->free(viewport);
}

/////////////////////////////////

void SubViewport::set_size(const Size2i &p_size) {
	ERR_MAIN_THREAD_GUARD;
	_internal_set_size(p_size);
}

void SubViewport::set_size_force(const Size2i &p_size) {
	ERR_MAIN_THREAD_GUARD;
	// Use only for setting the size from the parent SubViewportContainer with enabled stretch mode.
	// Don't expose function to scripting.
	_internal_set_size(p_size, true);
}

void SubViewport::_internal_set_size(const Size2i &p_size, bool p_force) {
	
}

Size2i SubViewport::get_size() const {
	ERR_READ_THREAD_GUARD_V(Size2());
	return _get_size();
}

void SubViewport::set_size_2d_override(const Size2i &p_size) {
	ERR_MAIN_THREAD_GUARD;
	_set_size(_get_size(), p_size, true);
}

Size2i SubViewport::get_size_2d_override() const {
	ERR_READ_THREAD_GUARD_V(Size2i());
	return _get_size_2d_override();
}

void SubViewport::set_size_2d_override_stretch(bool p_enable) {
	ERR_MAIN_THREAD_GUARD;
	if (p_enable == size_2d_override_stretch) {
		return;
	}

	size_2d_override_stretch = p_enable;
	_set_size(_get_size(), _get_size_2d_override(), true);
}

bool SubViewport::is_size_2d_override_stretch_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return size_2d_override_stretch;
}

void SubViewport::set_update_mode(UpdateMode p_mode) {
	ERR_MAIN_THREAD_GUARD;
	update_mode = p_mode;
	RS::get_singleton()->viewport_set_update_mode(get_viewport_rid(), RS::ViewportUpdateMode(p_mode));
}

SubViewport::UpdateMode SubViewport::get_update_mode() const {
	ERR_READ_THREAD_GUARD_V(UPDATE_DISABLED);
	return update_mode;
}

void SubViewport::set_clear_mode(ClearMode p_mode) {
	ERR_MAIN_THREAD_GUARD;
	clear_mode = p_mode;
	RS::get_singleton()->viewport_set_clear_mode(get_viewport_rid(), RS::ViewportClearMode(p_mode));
}

SubViewport::ClearMode SubViewport::get_clear_mode() const {
	ERR_READ_THREAD_GUARD_V(CLEAR_MODE_ALWAYS);
	return clear_mode;
}

DisplayServer::WindowID SubViewport::get_window_id() const {
	ERR_READ_THREAD_GUARD_V(DisplayServer::INVALID_WINDOW_ID);
	return DisplayServer::INVALID_WINDOW_ID;
}

Transform2D SubViewport::get_screen_transform_internal(bool p_absolute_position) const {
	
	Transform2D container_transform;
	
	return container_transform * get_final_transform();
}

Transform2D SubViewport::get_popup_base_transform() const {

		return Transform2D();

	
}

Viewport *SubViewport::get_section_root_viewport() const {
	return nullptr;
}

bool SubViewport::is_attached_in_viewport() const {
	return false;
}

void SubViewport::_notification(int p_what) {
	
}

void SubViewport::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_size", "size"), &SubViewport::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &SubViewport::get_size);

	ClassDB::bind_method(D_METHOD("set_size_2d_override", "size"), &SubViewport::set_size_2d_override);
	ClassDB::bind_method(D_METHOD("get_size_2d_override"), &SubViewport::get_size_2d_override);

	ClassDB::bind_method(D_METHOD("set_size_2d_override_stretch", "enable"), &SubViewport::set_size_2d_override_stretch);
	ClassDB::bind_method(D_METHOD("is_size_2d_override_stretch_enabled"), &SubViewport::is_size_2d_override_stretch_enabled);

	ClassDB::bind_method(D_METHOD("set_update_mode", "mode"), &SubViewport::set_update_mode);
	ClassDB::bind_method(D_METHOD("get_update_mode"), &SubViewport::get_update_mode);

	ClassDB::bind_method(D_METHOD("set_clear_mode", "mode"), &SubViewport::set_clear_mode);
	ClassDB::bind_method(D_METHOD("get_clear_mode"), &SubViewport::get_clear_mode);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size", PROPERTY_HINT_NONE, "suffix:px"), "set_size", "get_size");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "size_2d_override", PROPERTY_HINT_NONE, "suffix:px"), "set_size_2d_override", "get_size_2d_override");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "size_2d_override_stretch"), "set_size_2d_override_stretch", "is_size_2d_override_stretch_enabled");
	ADD_GROUP("Render Target", "render_target_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "render_target_clear_mode", PROPERTY_HINT_ENUM, "Always,Never,Next Frame"), "set_clear_mode", "get_clear_mode");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "render_target_update_mode", PROPERTY_HINT_ENUM, "Disabled,Once,When Visible,When Parent Visible,Always"), "set_update_mode", "get_update_mode");

	BIND_ENUM_CONSTANT(CLEAR_MODE_ALWAYS);
	BIND_ENUM_CONSTANT(CLEAR_MODE_NEVER);
	BIND_ENUM_CONSTANT(CLEAR_MODE_ONCE);

	BIND_ENUM_CONSTANT(UPDATE_DISABLED);
	BIND_ENUM_CONSTANT(UPDATE_ONCE);
	BIND_ENUM_CONSTANT(UPDATE_WHEN_VISIBLE);
	BIND_ENUM_CONSTANT(UPDATE_WHEN_PARENT_VISIBLE);
	BIND_ENUM_CONSTANT(UPDATE_ALWAYS);
}

void SubViewport::_validate_property(PropertyInfo &p_property) const {
	
}

SubViewport::SubViewport() {
	RS::get_singleton()->viewport_set_size(get_viewport_rid(), get_size().width, get_size().height);
}

SubViewport::~SubViewport() {}
