#ifndef ENTRY_H
#define ENTRY_H

#include <pango/pangocairo.h>
#include "color.h"
#include "image.h"
#include "surface.h"
#include "string_vec.h"

#define MAX_INPUT_LENGTH 64

struct entry {
	struct surface surface;
	struct wl_subsurface *wl_subsurface;
	struct image image;
	struct {
		PangoContext *context;
		PangoLayout *entry_layout;
		PangoLayout *result_layouts[5];
	} pango;
	struct {
		cairo_surface_t *surface;
		cairo_t *cr;
	} cairo;
	PangoRectangle text_bounds;

	wchar_t input[MAX_INPUT_LENGTH];
	/* Assume maximum of 4 bytes per wchar_t (for UTF-8) */
	char input_mb[4*MAX_INPUT_LENGTH];
	uint32_t input_length;
	uint32_t input_mb_length;

	struct string_vec results;
	struct string_vec commands;

	/* Options */
	uint32_t font_size;
	const char *font_name;
	uint32_t padding;
	uint32_t num_characters;
	uint32_t num_lines;
	struct color foreground_color;
	struct color background_color;
	struct {
		struct color color;
		struct color outline_color;
		int32_t width;
		int32_t outline_width;
	} border;
};

void entry_preload(void);
void entry_init(struct entry *entry, uint32_t scale);
void entry_destroy(struct entry *entry);
void entry_update(struct entry *entry);
void entry_set_scale(struct entry *entry, uint32_t scale);

#endif /* ENTRY_H */
