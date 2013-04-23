// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NOXEVENT_H_
#define NOXEVENT_H_
#include <linux/input.h>        // keyboard & mouse

typedef unsigned long stTime;
//===========mouse & keyboard=============
#if 0
typedef struct {
  int type;
  struct input_event inputEvent;
} DeviceEvent;
typedef DeviceEvent stMouseEvent;                     // package as a specific event
typedef DeviceEvent stKbdEvent;

typedef struct input_event MouseStruct;
typedef struct input_event KbdStruct;           //original to input.h
#endif

typedef struct {
        int type;               /* of event */
        stTime time;              /* Microseconds */
        unsigned int state;     /* key or button mask */
        unsigned int keycode;   /* detail */
} NOXKeyEvent;
typedef NOXKeyEvent NOXKeyPressedEvent;
typedef NOXKeyEvent NOXKeyReleasedEvent;

typedef struct {
        int type;               /* of event */
        stTime time;              /* Microseconds */
        int x, y;               /* pointer x, y coordinates in event window */
//        int x_root, y_root;     /* coordinates relative to root */
        unsigned int state;     /* key or button mask */
        unsigned int button;    /* detail */                  //wheel.. 1.left,2.middle,3.right,4.up scroll(+)5.down scroll(-)
} NOXButtonEvent;
typedef NOXButtonEvent NOXButtonPressedEvent;
typedef NOXButtonEvent NOXButtonReleasedEvent;

typedef struct {
        int type;               /* of event */
        stTime time;              /* Microseconds */
        int x, y;               /* pointer x, y coordinates in event window */
//        int x_root, y_root;     /* coordinates relative to root */
        unsigned int state;     /* key or button mask */
        char is_hint;           /* detail */
} NOXMotionEvent;
typedef NOXMotionEvent NOXPointerMovedEvent;

//===========end(mouse & keyboard)========



typedef union _NoxEvents {
        int type;               /* must not be changed; first element */
        NOXKeyEvent noxkey;
        NOXButtonEvent noxbutton;
        NOXMotionEvent noxmotion;
} NoxEvents;
#if 0

typedef enum _NoxEventType {
  MOUSE_EVENT_TYPE,
  KEYBOARD_EVENT_TYPE
}NoxEventType;

#endif

/* Event names.  Used in "type" field in NoxEvents structures.  Not to be
confused with event masks above.  They start from 2 because 0 and 1
are reserved in the protocol for errors and replies. */
// refered from X.h
#define KeyPress                2
#define KeyRelease              3
#define ButtonPress             4
#define ButtonRelease           5
#define MotionNotify            6
#define EnterNotify             7
#define LeaveNotify             8
#define FocusIn                 9
#define FocusOut                10
#define KeymapNotify            11
#define Expose                  12
#define GraphicsExpose          13
#define NoExpose                14
#define VisibilityNotify        15
#define CreateNotify            16
#define DestroyNotify           17
#define UnmapNotify             18
#define MapNotify               19
#define MapRequest              20
#define ReparentNotify          21
#define ConfigureNotify         22
#define ConfigureRequest        23
#define GravityNotify           24
#define ResizeRequest           25
#define CirculateNotify         26
#define CirculateRequest        27
#define PropertyNotify          28
#define SelectionClear          29
#define SelectionRequest        30
#define SelectionNotify         31
#define ColormapNotify          32
#define ClientMessage           33
#define MappingNotify           34
#define GenericEvent            35
#define LASTEvent               36      /* must be bigger than any event # */


/* Key masks. Used as modifiers to GrabButton and GrabKey, results of QueryPointer,
   state in various key-, mouse-, and button-related events. */

#define ShiftMask               (1<<0)
#define LockMask                (1<<1)
#define ControlMask             (1<<2)
#define Mod1Mask                (1<<3)          //alt down
#define Mod2Mask                (1<<4)
#define Mod3Mask                (1<<5)
#define Mod4Mask                (1<<6)
#define Mod5Mask                (1<<7)

/* button masks.  Used in same manner as Key masks above. Not to be confused
   with button names below. */

#define Button1Mask             (1<<8)          //left mouse
#define Button2Mask             (1<<9)          //middle mouse
#define Button3Mask             (1<<10)         //right mouse
#define Button4Mask             (1<<11)
#define Button5Mask             (1<<12)
#endif /* NOXEVENT_H_ */
