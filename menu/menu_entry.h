/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2011-2015 - Daniel De Matteis
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MENU_ENTRY_H__
#define MENU_ENTRY_H__

#include <stdint.h>
#include <boolean.h>

#include "menu_input.h"

#ifdef __cplusplus
extern "C" {
#endif

enum menu_entry_type
{
   MENU_ENTRY_ACTION = 0,
   MENU_ENTRY_BOOL,
   MENU_ENTRY_INT,
   MENU_ENTRY_UINT,
   MENU_ENTRY_FLOAT,
   MENU_ENTRY_PATH,
   MENU_ENTRY_DIR,
   MENU_ENTRY_STRING,
   MENU_ENTRY_HEX,
   MENU_ENTRY_BIND,
   MENU_ENTRY_ENUM,
};

typedef struct menu_entry
{
   char  path[PATH_MAX_LENGTH];
   char label[PATH_MAX_LENGTH];
   char value[PATH_MAX_LENGTH];
   size_t entry_idx;
   unsigned idx;
   unsigned type;
   unsigned spacing;
} menu_entry_t;


int menu_entry_go_back(void);

enum menu_entry_type menu_entry_get_type(uint32_t i);

void menu_entry_get_path(uint32_t i, char  *s, size_t len);

void menu_entry_get_label(uint32_t i, char *s, size_t len);

unsigned menu_entry_get_spacing(uint32_t i);

unsigned menu_entry_get_type_new(uint32_t i);

uint32_t menu_entry_get_bool_value(uint32_t i);

void menu_entry_set_bool_value(uint32_t i, bool new_val);

struct string_list *menu_entry_enum_values(uint32_t i);

void menu_entry_enum_set_value_with_string(uint32_t i, const char *s);

int32_t menu_entry_bind_index(uint32_t i);

void menu_entry_bind_key_set(uint32_t i, int32_t value);

void menu_entry_bind_joykey_set(uint32_t i, int32_t value);

void menu_entry_bind_joyaxis_set(uint32_t i, int32_t value);

void menu_entry_pathdir_selected(uint32_t i);

bool menu_entry_pathdir_allow_empty(uint32_t i);

uint32_t menu_entry_pathdir_for_directory(uint32_t i);

void menu_entry_pathdir_get_value(uint32_t i, char *s, size_t len);

int menu_entry_pathdir_set_value(uint32_t i, const char *s);

void menu_entry_pathdir_extensions(uint32_t i, char *s, size_t len);

void menu_entry_reset(uint32_t i);

void menu_entry_get_value(uint32_t i, char *s, size_t len);

void menu_entry_set_value(uint32_t i, const char *s);

uint32_t menu_entry_num_has_range(uint32_t i);

float menu_entry_num_min(uint32_t i);

float menu_entry_num_max(uint32_t i);

int menu_entry_get_current_id(bool use_representation);

bool menu_entry_is_currently_selected(unsigned id);

void menu_entry_get(menu_entry_t *entry, size_t i,
      void *userdata, bool use_representation);

int menu_entry_iterate(unsigned action);

int menu_entry_select(uint32_t i);

int menu_entry_action(menu_entry_t *entry,
                      unsigned i, enum menu_action action);

size_t menu_entries_get_start(void);

size_t menu_entries_get_end(void);

int menu_entries_get_title(char *title, size_t title_len);

bool menu_entries_show_back(void);

void menu_entries_get_core_title(char *title_msg, size_t title_msg_len);

#ifdef __cplusplus
}
#endif

#endif
