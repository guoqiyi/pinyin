/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
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
#ifndef __PY_PINYIN_PROPERTIES_H_
#define __PY_PINYIN_PROPERTIES_H_

#include <PyZy/InputContext.h>

#include "PYSignal.h"
#include "PYProperty.h"

namespace PY {

class Config;

class PinyinProperties {
public:
    PinyinProperties (Config & config);

    void toggleModeChinese   (void);
    void toggleModeFull      (void);
    void toggleModeFullPunct (void);
    void toggleModeSimp      (void);

    void reset (void);

    gboolean modeChinese (void) const   { return m_mode_chinese; }
    gboolean modeFull (void) const      { return m_mode_full; }
    gboolean modeFullPunct (void) const { return m_mode_full_punct; }
    gboolean modeSimp (void) const      { return m_mode_simp; }

    PropList & properties (void)        { return m_props; }

    gboolean propertyActivate (const gchar *prop_name, guint prop_state);

    signal <void (Property &)> & signalUpdateProperty (void)
    {
        return m_signal_update_property;
    }

    void setContext (PyZy::InputContext *context);
    void clearContext ();

private:
    void updateProperty (Property & prop) const
    {
        m_signal_update_property (prop);
    }

    signal <void (Property &)> m_signal_update_property;

private:
    Config    & m_config;
    gboolean    m_mode_chinese;
    gboolean    m_mode_full;
    gboolean    m_mode_full_punct;
    gboolean    m_mode_simp;

    /* properties */
    Property    m_prop_chinese;
    Property    m_prop_full;
    Property    m_prop_full_punct;
    Property    m_prop_simp;
    Property    m_prop_setup;
    PropList    m_props;

    PyZy::InputContext * m_context;
};

};

#endif
