/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 * Copyright (c) 2010 BYVoid <byvoid1@gmail.com>
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
#ifndef __PY_PUNCT_EDITOR_
#define __PY_PUNCT_EDITOR_

#include <vector>

#include "PYLookupTable.h"
#include "PYEditor.h"

namespace PY {

class PunctEditor : public Editor {
public:
    PunctEditor (PinyinProperties &props, Config & config);

    virtual gboolean processKeyEvent (guint keyval, guint keycode, guint modifiers);
    virtual void pageUp (void);
    virtual void pageDown (void);
    virtual void cursorUp (void);
    virtual void cursorDown (void);
    virtual void update (void);
    virtual void reset (void);
    virtual void candidateClicked (guint index, guint button, guint state);

    virtual gboolean processPunct (guint keyval, guint keycode, guint modifiers);
    virtual gboolean processSpace (guint keyval, guint keycode, guint modifiers);
    virtual gboolean insert (gchar ch);
    virtual void updateLookupTable (void);
    virtual void updateAuxiliaryText (void);
    virtual void updatePreeditText (void);
    virtual gboolean selectCandidate (guint i);
    virtual gboolean selectCandidateInPage (guint i);
    virtual void commit (const gchar *str);
    virtual void commit (void);
    virtual gboolean removeCharBefore (void);
    virtual gboolean removeCharAfter (void);
    virtual gboolean moveCursorLeft (void);
    virtual gboolean moveCursorRight (void);
    virtual gboolean moveCursorToBegin (void);
    virtual gboolean moveCursorToEnd (void);

    void fillLookupTable (void);
    void updatePunctCandidates (gchar ch);
protected:
    enum {
        MODE_DISABLE,
        MODE_INIT,
        MODE_NORMAL,
    } m_punct_mode;
    LookupTable m_lookup_table;
    String m_buffer;
    std::vector<const gchar *> m_selected_puncts;
    std::vector<const gchar *> m_punct_candidates;

};

};
#endif
