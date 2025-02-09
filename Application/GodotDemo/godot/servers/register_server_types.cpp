/**************************************************************************/
/*  register_server_types.cpp                                             */
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

#include "register_server_types.h"

#include "core/config/engine.h"
#include "core/config/project_settings.h"

#include "audio/audio_effect.h"
#include "audio/audio_stream.h"
#include "audio/effects/audio_effect_amplify.h"
#include "audio/effects/audio_effect_capture.h"
#include "audio/effects/audio_effect_chorus.h"
#include "audio/effects/audio_effect_compressor.h"
#include "audio/effects/audio_effect_delay.h"
#include "audio/effects/audio_effect_distortion.h"
#include "audio/effects/audio_effect_eq.h"
#include "audio/effects/audio_effect_filter.h"
#include "audio/effects/audio_effect_hard_limiter.h"
#include "audio/effects/audio_effect_limiter.h"
#include "audio/effects/audio_effect_panner.h"
#include "audio/effects/audio_effect_phaser.h"
#include "audio/effects/audio_effect_pitch_shift.h"
#include "audio/effects/audio_effect_record.h"
#include "audio/effects/audio_effect_reverb.h"
#include "audio/effects/audio_effect_spectrum_analyzer.h"
#include "audio/effects/audio_effect_stereo_enhance.h"
#include "audio/effects/audio_stream_generator.h"
#include "audio_server.h"
#include "camera/camera_feed.h"
#include "camera_server.h"
#include "debugger/servers_debugger.h"
#include "movie_writer/movie_writer.h"
#include "movie_writer/movie_writer_mjpeg.h"
#include "movie_writer/movie_writer_pngwav.h"
#include "rendering_server.h"



// 2D physics and navigation.
#include "navigation_server_2d.h"
#include "physics_server_2d.h"
#include "physics_server_2d_dummy.h"
#include "physics_server_2d_wrap_mt.h"
#include "servers/extensions/physics_server_2d_extension.h"

// 3D physics and navigation (3D navigation is needed for 2D).
#include "navigation_server_3d.h"
#ifndef _3D_DISABLED
#include "physics_server_3d.h"
#include "physics_server_3d_dummy.h"
#include "physics_server_3d_wrap_mt.h"
#include "servers/extensions/physics_server_3d_extension.h"

#endif // _3D_DISABLED


#ifndef _3D_DISABLED
static PhysicsServer3D *_create_dummy_physics_server_3d() {
	return memnew(PhysicsServer3DDummy);
}
#endif // _3D_DISABLED

static PhysicsServer2D *_create_dummy_physics_server_2d() {
	return memnew(PhysicsServer2DDummy);
}

static bool has_server_feature_callback(const String &p_feature) {
	if (RenderingServer::get_singleton()) {
		if (RenderingServer::get_singleton()->has_os_feature(p_feature)) {
			return true;
		}
	}

	return false;
}

static MovieWriterMJPEG *writer_mjpeg = nullptr;
static MovieWriterPNGWAV *writer_pngwav = nullptr;

void register_server_types() {
	OS::get_singleton()->benchmark_begin_measure("Servers", "Register Extensions");




	

	OS::get_singleton()->benchmark_end_measure("Servers", "Register Extensions");
}

void unregister_server_types() {
	OS::get_singleton()->benchmark_begin_measure("Servers", "Unregister Extensions");



	OS::get_singleton()->benchmark_end_measure("Servers", "Unregister Extensions");
}

void register_server_singletons() {
	OS::get_singleton()->benchmark_begin_measure("Servers", "Register Singletons");

	

	OS::get_singleton()->benchmark_end_measure("Servers", "Register Singletons");
}
