/* See LICENSE file for copyright and license details. */

/* Enable special function keys */
#include <X11/XF86keysym.h>

/* Default programs */
#define TERMINAL "st"
#define BROWSER "librewolf"
#define STATUSBAR "dwmblocks"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappih    = 8;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;        /* vert inner gap between windows */
static const unsigned int gappoh    = 8;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;        /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only 1 window */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
    "Noto Sans Mono:size=13",
    "Iosevka Nerd Font:size=13",
    "Noto Color Emoji:pixelsize=15:antialias=true:autohint=true",
};
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_sel[]         = "#770000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_sel  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,           0,         1,          0,          0,         -1 },
	{ "LibreWolf", NULL,      NULL,           1 << 8,    0,          0,          0,         -1 },
	{ "st-256color", NULL,    NULL,           0,         0,          1,          0,         -1 },
	{ NULL,       NULL,       "Event Tester", 0,         0,          0,          1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char scratchpadname2[] = "calculator";
static const char *scratchpadcmd2[] = { "st", "-t", scratchpadname2, "-g", "50x15", "-e", "bc", "-ql", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "bluetui", NULL } } },
	{ MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,                       XK_u,      spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,             		      XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_dead_acute,      togglescratch, {.ui = 0} },
	{ MODKEY|ShiftMask,             XK_dead_acute,      togglescratch, {.ui = 1} },
  { MODKEY,			                  XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "wlctl", NULL } } },
	{ MODKEY,                       XK_e,      spawn,          {.v = (const char*[]){ "thunderbird", NULL } } },
	{ MODKEY|ShiftMask,		          XK_e,      spawn,          SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
  { MODKEY,		                    XK_r,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
  { MODKEY|ShiftMask,		          XK_r,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "newsboat", NULL } } },
 	{ MODKEY,			                  XK_m,      spawn,           {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },

	{ MODKEY,                       XK_c,      spawn,          SHCMD("~/.local/bin/horizon-client") },
	{ MODKEY,                       XK_space,  spawn,          SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_BackSpace, spawn,       SHCMD("sysact") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("maimpick") },
	{ MODKEY,             		      XK_o,      spawn,          SHCMD("~/.local/bin/passmenu") },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = (const char*[]){ "keepassxc", NULL } } },
	{ MODKEY,                       XK_a,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "abpl", NULL } } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,	     zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_a,      togglegaps,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                      XK_q,      killclient,     {0} },

  { MODKEY,			XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY,			XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },

	{ MODKEY,     XK_F3,         spawn,                  SHCMD("displayselect") },
 	{ MODKEY,			XK_F4,         spawn,                  SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
 	{ MODKEY,			XK_F8,         spawn,                  {.v = (const char*[]){ "mailsync", NULL } } },
	{ MODKEY,			XK_F9,         spawn,                  {.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
	{ MODKEY,			XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,        spawn,                  SHCMD("remaps") },

  { 0,				XK_Print,      spawn,                  SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", NULL } } },

	/*{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },*/
	/*{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },*/
	/*{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },*/
	/*{ MODKEY,                       XK_space,  setlayout,      {0} },*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },

 	{ MODKEY,             		      XK_p,      spawn,          SHCMD("player-toggle") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "podsync", NULL } } },

	{ MODKEY,                      	XK_plus,   spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,            	XK_plus,   spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                      	XK_minus,  spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,            	XK_minus,  spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,            	XK_m,  	   spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,  	spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,  	spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMute,         	spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPlay,         	spawn,     SHCMD("player-toggle") },
	{ 0, XF86XK_AudioPause,        	spawn,     SHCMD("player-toggle") },
	{ 0, XF86XK_MonBrightnessDown, 	spawn,     SHCMD("brightnessctl set 10-") },
	{ 0, XF86XK_MonBrightnessUp,   	spawn,     SHCMD("brightnessctl set 10+") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        0,              6,              sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        0,              7,              sigstatusbar,   {.i = 7} },
	{ ClkStatusText,        0,              8,              sigstatusbar,   {.i = 8} },
	{ ClkStatusText,        0,              9,              sigstatusbar,   {.i = 9} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
