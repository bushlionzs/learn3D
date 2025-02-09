/**************************************************************************/
/*  theme_owner.cpp                                                       */
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

#include "theme_owner.h"


#include "scene/main/window.h"
#include "scene/theme/theme_db.h"

// Theme owner node.

void ThemeOwner::set_owner_node(Node *p_node) {
	owner_control = nullptr;
	owner_window = nullptr;

	

	Window *w = Object::cast_to<Window>(p_node);
	if (w) {
		owner_window = w;
		return;
	}
}

Node *ThemeOwner::get_owner_node() const {

	
	return nullptr;
}

bool ThemeOwner::has_owner_node() const {
	return bool(owner_control || owner_window);
}

void ThemeOwner::set_owner_context(ThemeContext *p_context, bool p_propagate) {
	ThemeContext *default_context = ThemeDB::get_singleton()->get_default_theme_context();

	if (owner_context && owner_context->is_connected(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed))) {
		owner_context->disconnect(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed));
	} else if (default_context->is_connected(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed))) {
		default_context->disconnect(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed));
	}

	owner_context = p_context;

	if (owner_context) {
		owner_context->connect(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed));
	} else {
		default_context->connect(CoreStringName(changed), callable_mp(this, &ThemeOwner::_owner_context_changed));
	}

	if (p_propagate) {
		_owner_context_changed();
	}
}

void ThemeOwner::_owner_context_changed() {
	if (!holder->is_inside_tree()) {
		// We ignore theme changes outside of tree, because NOTIFICATION_ENTER_TREE covers everything.
		return;
	}


}

ThemeContext *ThemeOwner::_get_active_owner_context() const {
	if (owner_context) {
		return owner_context;
	}

	return ThemeDB::get_singleton()->get_default_theme_context();
}

// Theme propagation.

void ThemeOwner::assign_theme_on_parented(Node *p_for_node) {
	// We check if there are any themes affecting the parent. If that's the case
	// its children also need to be affected.
	// We don't notify here because `NOTIFICATION_THEME_CHANGED` will be handled
	// a bit later by `NOTIFICATION_ENTER_TREE`.

	Node *parent = p_for_node->get_parent();

	
}

void ThemeOwner::clear_theme_on_unparented(Node *p_for_node) {
	// We check if there were any themes affecting the parent. If that's the case
	// its children need were also affected and need to be updated.
	// We don't notify because we're exiting the tree, and it's not important.

	Node *parent = p_for_node->get_parent();

	
}

void ThemeOwner::propagate_theme_changed(Node *p_to_node, Node *p_owner_node, bool p_notify, bool p_assign) {
	
}

// Theme lookup.

void ThemeOwner::get_theme_type_dependencies(const Node *p_for_node, const StringName &p_theme_type, Vector<StringName> &r_result) const {
	
}

Variant ThemeOwner::get_theme_item_in_types(Theme::DataType p_data_type, const StringName &p_name, const Vector<StringName> &p_theme_types) {
	ERR_FAIL_COND_V_MSG(p_theme_types.is_empty(), Variant(), "At least one theme type must be specified.");

	// First, look through each control or window node in the branch, until no valid parent can be found.
	// Only nodes with a theme resource attached are considered.
	Node *owner_node = get_owner_node();

	while (owner_node) {
		// For each theme resource check the theme types provided and see if p_name exists with any of them.
		for (const StringName &E : p_theme_types) {
			Ref<Theme> owner_theme = _get_owner_node_theme(owner_node);

			if (owner_theme.is_valid() && owner_theme->has_theme_item(p_data_type, p_name, E)) {
				return owner_theme->get_theme_item(p_data_type, p_name, E);
			}
		}

		owner_node = _get_next_owner_node(owner_node);
	}

	// Second, check global themes from the appropriate context.
	ThemeContext *global_context = _get_active_owner_context();
	for (const Ref<Theme> &theme : global_context->get_themes()) {
		if (theme.is_valid()) {
			for (const StringName &E : p_theme_types) {
				if (theme->has_theme_item(p_data_type, p_name, E)) {
					return theme->get_theme_item(p_data_type, p_name, E);
				}
			}
		}
	}

	// Finally, if no match exists, use any type to return the default/empty value.
	return global_context->get_fallback_theme()->get_theme_item(p_data_type, p_name, StringName());
}

bool ThemeOwner::has_theme_item_in_types(Theme::DataType p_data_type, const StringName &p_name, const Vector<StringName> &p_theme_types) {
	ERR_FAIL_COND_V_MSG(p_theme_types.is_empty(), false, "At least one theme type must be specified.");

	// First, look through each control or window node in the branch, until no valid parent can be found.
	// Only nodes with a theme resource attached are considered.
	Node *owner_node = get_owner_node();

	while (owner_node) {
		// For each theme resource check the theme types provided and see if p_name exists with any of them.
		for (const StringName &E : p_theme_types) {
			Ref<Theme> owner_theme = _get_owner_node_theme(owner_node);

			if (owner_theme.is_valid() && owner_theme->has_theme_item(p_data_type, p_name, E)) {
				return true;
			}
		}

		owner_node = _get_next_owner_node(owner_node);
	}

	// Second, check global themes from the appropriate context.
	ThemeContext *global_context = _get_active_owner_context();
	for (const Ref<Theme> &theme : global_context->get_themes()) {
		if (theme.is_valid()) {
			for (const StringName &E : p_theme_types) {
				if (theme->has_theme_item(p_data_type, p_name, E)) {
					return true;
				}
			}
		}
	}

	// Finally, if no match exists, return false.
	return false;
}

float ThemeOwner::get_theme_default_base_scale() {
	// First, look through each control or window node in the branch, until no valid parent can be found.
	// Only nodes with a theme resource attached are considered.
	// For each theme resource see if their assigned theme has the default value defined and valid.
	Node *owner_node = get_owner_node();

	while (owner_node) {
		Ref<Theme> owner_theme = _get_owner_node_theme(owner_node);

		if (owner_theme.is_valid() && owner_theme->has_default_base_scale()) {
			return owner_theme->get_default_base_scale();
		}

		owner_node = _get_next_owner_node(owner_node);
	}

	// Second, check global themes from the appropriate context.
	ThemeContext *global_context = _get_active_owner_context();
	for (const Ref<Theme> &theme : global_context->get_themes()) {
		if (theme.is_valid()) {
			if (theme->has_default_base_scale()) {
				return theme->get_default_base_scale();
			}
		}
	}

	// Finally, if no match exists, return the universal default.
	return ThemeDB::get_singleton()->get_fallback_base_scale();
}



int ThemeOwner::get_theme_default_font_size() {
	// First, look through each control or window node in the branch, until no valid parent can be found.
	// Only nodes with a theme resource attached are considered.
	// For each theme resource see if their assigned theme has the default value defined and valid.
	Node *owner_node = get_owner_node();

	

	

	// Finally, if no match exists, return the universal default.
	return ThemeDB::get_singleton()->get_fallback_font_size();
}

Ref<Theme> ThemeOwner::_get_owner_node_theme(Node *p_owner_node) const {
	

	return Ref<Theme>();
}

Node *ThemeOwner::_get_next_owner_node(Node *p_from_node) const {
	

	return nullptr;
}
