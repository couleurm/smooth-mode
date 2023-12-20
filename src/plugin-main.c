// These headers are mandatory for the module to even exist.
#include <obs-module.h>
#include "plugin-support.h"

// These headers import symbols which the module uses.
#include <obs-properties.h>
#include <obs-source.h>
#include <obs.h>
#include <util/bmem.h>
#include <util/c99defs.h>

#define DEBUG_MODE 1
#define TEXT_NAME "Smooth mode"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

// smooth_mode_state
typedef struct {
	obs_source_t *context;
} smooth_mode_state;

// smooth_mode_frame
// typedef struct {
// } smooth_mode_frame;

// smooth_mode_get_name returns the filter's name.
static const char *smooth_mode_get_name(void *input)
{
	UNUSED_PARAMETER(input);
	return TEXT_NAME;
}

// smooth_mode_create is the constructor for a new instance of
// 'smooth_mode_state'. This instance is then treated as the filter's
// global state.
static void *smooth_mode_create(obs_data_t *settings, obs_source_t *context)
{
	smooth_mode_state *state =
		(smooth_mode_state *)bzalloc(sizeof(smooth_mode_state));
	state->context = context;

	obs_source_update(context, settings);
	return state;
}

// smooth_mode_destroy is the deconstructor for the existing instance
// of 'smooth_mode_state'. It is implicitly called by OBS whenever the
// module is unloaded.
static void smooth_mode_destroy(void *_state)
{
	smooth_mode_state *state = _state;
	bfree(state);
}

// smooth_mode_tick
static void smooth_mode_tick(void *_state, float t)
{
	UNUSED_PARAMETER(t);

	smooth_mode_state *state = _state;
	obs_source_t *target = obs_filter_get_target(state->context);

	if (!!target) {
#if DEBUG_MODE
		obs_log(LOG_INFO, "smooth_mode_tick: target valid");
#endif
	}
}

// obs_module_load is called when the module is loaded. It registers
// the filter.
bool obs_module_load(void)
{
	obs_log(LOG_INFO, "plugin loaded successfully (version %s)",
		PLUGIN_VERSION);

	// This is where we set all callbacks for the filter's interface.
	struct obs_source_info smooth_mode_filter = {
		.id = "smooth_mode",
		.type = OBS_SOURCE_TYPE_FILTER,
		.output_flags = OBS_SOURCE_VIDEO,
		.get_name = smooth_mode_get_name,
		.create = smooth_mode_create,
		.destroy = smooth_mode_destroy,
		.video_tick = smooth_mode_tick,
	};

	// Register the filter and display a log message. If the
	// registration causes OBS to crash, we'll never see the success
	// message, which is the desired behaviour.
	obs_register_source(&smooth_mode_filter);
	obs_log(LOG_INFO, "filter source successfully registered");

	return true;
}

// obs_module_unload is called when the module is unloaded. It unloads
// the filter and frees all allocated resources.
void obs_module_unload(void)
{
	obs_log(LOG_INFO, "plugin unloaded");
}
