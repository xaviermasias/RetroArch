/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2014-2015 - Jay McCarthy
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

#include "menu.h"
#include "menu_display.h"
#include "menu_entry.h"
#include "menu_navigation.h"
#include "menu_setting.h"
#include "menu_input.h"

#include "../general.h"

/* Returns the starting index of the menu entry list. */
size_t menu_entries_get_start(void)
{
   menu_handle_t *menu       = menu_driver_get_ptr();
   
   if (!menu)
     return 0;

   return menu->begin;
}

/* Returns the last index (+1) of the menu entry list. */
size_t menu_entries_get_end(void)
{
   menu_list_t *menu_list    = menu_list_get_ptr();
   return menu_list_get_size(menu_list);
}


/* Sets title to what the name of the current menu should be. */
int menu_entries_get_title(char *s, size_t len)
{
   const char *path          = NULL;
   const char *label         = NULL;
   unsigned menu_type        = 0;
   menu_file_list_cbs_t *cbs = NULL;
   menu_list_t *menu_list    = menu_list_get_ptr();
   
   if (!menu_list)
      return -1;

   cbs = (menu_file_list_cbs_t*)menu_list_get_last_stack_actiondata(menu_list);

   menu_list_get_last_stack(menu_list, &path, &label, &menu_type, NULL);

   if (cbs && cbs->action_get_title)
      return cbs->action_get_title(path, label, menu_type, s, len);
   return 0;
}

/* Returns true if a Back button should be shown (i.e. we are at least
 * one level deep in the menu hierarchy). */
bool menu_entries_show_back(void)
{
   menu_list_t *menu_list    = menu_list_get_ptr();

   if (!menu_list)
      return false;

   return (menu_list_get_stack_size(menu_list) > 1);
}

/* Sets 's' to the name of the current core 
 * (shown at the top of the UI). */
void menu_entries_get_core_title(char *s, size_t len)
{
   global_t *global          = global_get_ptr();
   const char *core_name     = global ? global->menu.info.library_name    : NULL;
   const char *core_version  = global ? global->menu.info.library_version : NULL;

   if (!core_name)
      core_name = global->system.info.library_name;
   if (!core_name)
      core_name = "No Core";

   if (!core_version)
      core_version = global->system.info.library_version;
   if (!core_version)
      core_version = "";

   snprintf(s, len, "%s - %s %s", PACKAGE_VERSION,
         core_name, core_version);
}
