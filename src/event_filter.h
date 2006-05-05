/*      $Id$
 
        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2, or (at your option)
        any later version.
 
        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.
 
        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 
        xfwm4    - (c) 2002-2006 Olivier Fourdan
 
 */
 
#ifndef __EVENT_FILTER_H__
#define __EVENT_FILTER_H__

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <X11/Xlib.h>

/* this formatting is needed by glib-mkenums */
typedef enum {
    EVENT_FILTER_STOP = TRUE,
    EVENT_FILTER_CONTINUE = FALSE
}
eventFilterStatus;

typedef eventFilterStatus (*XfwmFilter) (XEvent * xevent, gpointer data);

typedef struct eventFilterStack
{
    XfwmFilter filter;
    gpointer data;
    struct eventFilterStack *next;
}
eventFilterStack;

typedef struct eventFilterSetup
{
    eventFilterStack *filterstack;
}
eventFilterSetup;

eventFilterStack * eventFilterPush  (eventFilterSetup *setup,
                                     XfwmFilter filter,
                                     gpointer data);
eventFilterStack * eventFilterPop   (eventFilterSetup *setup);
eventFilterSetup * eventFilterInit  (gpointer data);
void               eventFilterClose (eventFilterSetup *setup);

#endif /* __EVENT_FILTER_H__ */