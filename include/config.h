#ifndef _SWAY_CONFIG_H
#define _SWAY_CONFIG_H

#include <stdint.h>
#include <wlc/wlc.h>
#include <xkbcommon/xkbcommon.h>
#include "list.h"
#include "layout.h"
#include "container.h"

/**
 * Describes a variable created via the `set` command.
 */
struct sway_variable {
	char *name;
	char *value;
};

/**
 * A key binding and an associated command.
 */
struct sway_binding {
	list_t *keys;
	uint32_t modifiers;
	char *command;
};

/**
 * A "mode" of keybindings created via the `mode` command.
 */
struct sway_mode {
	char *name;
	list_t *bindings;
};

/**
 * Size and position configuration for a particular output.
 *
 * This is set via the `output` command.
 */
struct output_config {
	char *name;
	bool enabled;
	int width, height;
	int x, y;
};

/**
 * Maps a workspace name to an output name.
 *
 * Set via `workspace <x> output <y>`
 */
struct workspace_output {
	char *output;
	char *workspace;
};

/**
 * The configuration struct. The result of loading a config file.
 */
struct sway_config {
	list_t *symbols;
	list_t *modes;
	list_t *cmd_queue;
	list_t *workspace_outputs;
	list_t *output_configs;
	struct sway_mode *current_mode;
	uint32_t floating_mod;
	enum swayc_layouts default_orientation;
	enum swayc_layouts default_layout;

	// Flags
	bool focus_follows_mouse;
	bool mouse_warping;
	bool active;
	bool failed;
	bool reloading;
	bool reading;
	bool auto_back_and_forth;
	bool seamless_mouse;

	bool edge_gaps;
	int gaps_inner;
	int gaps_outer;
};

/**
 * Loads the config from the given path.
 */
bool load_config(const char *file);
/** Reads the config from the given FILE.
 */
bool read_config(FILE *file, bool is_active);
/**
 * Does variable replacement for a string based on the config's currently loaded variables.
 */
char *do_var_replacement(char *str);
/** Sets up a WLC output handle based on a given output_config.
 */
void apply_output_config(struct output_config *oc, swayc_t *output);

/**
 * Global config singleton.
 */
extern struct sway_config *config;

#endif
