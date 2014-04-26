/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2010 Peng Wu <alexepico@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#ifndef LUA_PLUGIN_H
#define LUA_PLUGIN_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <glib-object.h>

#define LUA_IMELIBNAME   "ime"
LUALIB_API int (luaopen_ime) (lua_State * L);
LUALIB_API int (luaopen_myos) (lua_State * L);

#define LUA_IMELIB_CONTEXT "__context"

typedef struct _lua_command_t{
  const char * command_name;
  const char * lua_function_name;
  const char * description;
  const char * leading; /* optional, default "digit". */
  const char * help; /* optional. */
} lua_command_t;

typedef struct _lua_command_candidate_t{
  const char * suggest;
  const char * help;
  const char * content;
} lua_command_candidate_t;

typedef struct _lua_trigger_t{
  const char * lua_function_name;
  const char * description;
  /*< private, skip it, and register it into Special Table directly with * wildcard. >*/
  /*
   * list of input_trigger_strings;
   * list of candidate_trigger_strings;
   */
} lua_trigger_t;

/*
 * Type macros.
 */

#define IBUS_TYPE_ENGINE_PLUGIN                 (ibus_engine_plugin_get_type ())
#define IBUS_ENGINE_PLUGIN(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), IBUS_TYPE_ENGINE_PLUGIN, IBusEnginePlugin))
#define IBUS_IS_ENGINE_PLUGIN(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IBUS_TYPE_ENGINE_PLUGIN))
#define IBUS_ENGINE_PLUGIN_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), IBUS_TYPE_ENGINE_PLUGIN, IBusEnginePluginClass))
#define IBUS_IS_ENGINE_PLUGIN_CLASS(klass)      (G_TYPE_CHECK_CLASS ((klass), IBUS_TYPE_ENGINE_PLUGIN))
#define IBUS_ENGINE_PLUGIN_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), IBUS_TYPE_ENGINE_PLUGIN, IBusEnginePluginClass))

typedef struct _IBusEnginePlugin IBusEnginePlugin;
typedef struct _IBusEnginePluginClass IBusEnginePluginClass;
typedef struct _IBusEnginePluginPrivate IBusEnginePluginPrivate;

void lua_plugin_openlibs (lua_State *L);
void lua_plugin_store_plugin(lua_State * L, IBusEnginePlugin * plugin);

struct _IBusEnginePlugin
{
  GObject parent_instance;

  /*< private >*/
  IBusEnginePluginPrivate *priv;  
};

struct _IBusEnginePluginClass
{
  GObjectClass parent_class;
};

GType ibus_engine_plugin_get_type(void);

/**
 * create a new ibus engine plugin.
 */
IBusEnginePlugin * ibus_engine_plugin_new();

/**
 * load a new lua script for ibus engine plugin.
 */
int ibus_engine_plugin_load_lua_script(IBusEnginePlugin * plugin, const char * filename);

/**
 * add a lua_command_t to plugin.
 */
gboolean ibus_engine_plugin_add_command(IBusEnginePlugin * plugin, lua_command_t * command);

/**
 * retrieve all available lua plugin commands.
 * return array of command informations of type lua_command_t without copies.
 */
const GArray * ibus_engine_plugin_get_available_commands(IBusEnginePlugin * plugin);

/**
 * Lookup a special command in ime lua extension.
 * command must be an 2-char long string.
 * return the matched command.
 */
const lua_command_t * ibus_engine_plugin_lookup_command(IBusEnginePlugin * plugin, const char * command_name);

/**
 * retval int: returns the number of results,
 *              only support string or string array.
 * the consequence call of ibus_engine_plugin_get_retval* must follow this call immediately.
 */
int ibus_engine_plugin_call(IBusEnginePlugin * plugin, const char * lua_function_name, const char * argument /*optional, maybe NULL.*/);

/**
 * retrieve the retval string value. (value has been copied.)
 */
const lua_command_candidate_t * ibus_engine_plugin_get_retval(IBusEnginePlugin * plugin);

/**
 * retrieve the array of lua_command_candidate_t values. (string values have been copied.)
 */
GArray * ibus_engine_plugin_get_retvals(IBusEnginePlugin * plugin);

void ibus_engine_plugin_free_candidate(lua_command_candidate_t * candidate);
#endif
