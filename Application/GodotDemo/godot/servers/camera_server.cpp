/**************************************************************************/
/*  camera_server.cpp                                                     */
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

#include "camera_server.h"
#include "core/variant/typed_array.h"
#include "rendering_server.h"
#include "servers/camera/camera_feed.h"

////////////////////////////////////////////////////////
// CameraServer

CameraServer::CreateFunc CameraServer::create_func = nullptr;

void CameraServer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_feed", "index"), &CameraServer::get_feed);
	ClassDB::bind_method(D_METHOD("get_feed_count"), &CameraServer::get_feed_count);
	ClassDB::bind_method(D_METHOD("feeds"), &CameraServer::get_feeds);

	ClassDB::bind_method(D_METHOD("add_feed", "feed"), &CameraServer::add_feed);
	ClassDB::bind_method(D_METHOD("remove_feed", "feed"), &CameraServer::remove_feed);

	ADD_SIGNAL(MethodInfo("camera_feed_added", PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("camera_feed_removed", PropertyInfo(Variant::INT, "id")));

	BIND_ENUM_CONSTANT(FEED_RGBA_IMAGE);
	BIND_ENUM_CONSTANT(FEED_YCBCR_IMAGE);
	BIND_ENUM_CONSTANT(FEED_Y_IMAGE);
	BIND_ENUM_CONSTANT(FEED_CBCR_IMAGE);
};

CameraServer *CameraServer::singleton = nullptr;

CameraServer *CameraServer::get_singleton() {
	return singleton;
};

int CameraServer::get_free_id() {
	bool id_exists = true;
	int newid = 0;

	

	return newid;
};

int CameraServer::get_feed_index(int p_id) {
	

	return -1;
};

Ref<CameraFeed> CameraServer::get_feed_by_id(int p_id) {
	return nullptr;
};

void CameraServer::add_feed(const Ref<CameraFeed> &p_feed) {
	
};

void CameraServer::remove_feed(const Ref<CameraFeed> &p_feed) {
	
};

Ref<CameraFeed> CameraServer::get_feed(int p_index) {
	return nullptr;
};

int CameraServer::get_feed_count() {
	return feeds.size();
};

TypedArray<CameraFeed> CameraServer::get_feeds() {
	TypedArray<CameraFeed> return_feeds;
	

	return return_feeds;
};

RID CameraServer::feed_texture(int p_id, CameraServer::FeedImage p_texture) {
	return RID();
};

CameraServer::CameraServer() {
	singleton = this;
};

CameraServer::~CameraServer() {
	singleton = nullptr;
};
