/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10", "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetBrains Mono:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "firefox",          NULL,       NULL,            1 << 8,    0,          0,          -1,        -1 },
	{ "St",               NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ "xst-256color",     NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ NULL,               NULL,       "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* Default: tile (Master on left, slaves on right) */
	{ "[M]",      monocle }, /* one window in "fullscreen" (fakefullscreen) */
	{ "><>",      NULL },    /* no layout function means floating behavior */

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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont }; /* no colors b/c i use dmenu-xresources patch */
static const char *emacscmd[] = { "emacsclient", "-c", "-a", "", NULL };
#define TERMINAL_ENVVAR "TERMINAL"

static const Key keys[] = {
	/* modifier                     key                function        argument */
	/* spawn programs */
	{ MODKEY,                       XK_b,              togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_c,              killclient,     {0} },
	{ MODKEY,                       XK_d,              spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,              spawn,          {.v = emacscmd } },
	{ MODKEY,                       XK_Return,         spawn,          {.v = termcmd } },
	/* layouts */
	{ MODKEY,                       XK_t,              setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_o,              setlayout,      {.v = &layouts[1]} }, /* monocle */
	{ MODKEY,                       XK_f,              setlayout,      {.v = &layouts[2]} }, /* float */
	{ MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
	/* move focus */
	{ MODKEY,                       XK_j,              focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,              focusstack,     {.i = -1 } },
	/* handle slave-master dynamics */
	{ MODKEY,                       XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_m,              incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_m,              incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_space,          zoom,           {0} }, /* set new master */
        /* (multi monitor setup) move focus between screens */
	{ MODKEY,                       XK_comma,          focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,         focusmon,       {.i = +1 } },
	/* (multi monitor setup) move active window to different screen */ 
	{ MODKEY|ShiftMask,             XK_comma,          tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,         tagmon,         {.i = +1 } },
	/* tags */ 
	TAGKEYS(                        XK_1,                              0)
	TAGKEYS(                        XK_2,                              1)
	TAGKEYS(                        XK_3,                              2)
	TAGKEYS(                        XK_4,                              3)
	TAGKEYS(                        XK_5,                              4)
	TAGKEYS(                        XK_6,                              5)
	TAGKEYS(                        XK_7,                              6)
	TAGKEYS(                        XK_8,                              7)
	TAGKEYS(                        XK_9,                              8)
	{ MODKEY,                       XK_0,              view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,              tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_p,              view,           {0} }, /* go back to previous tag */
	/* f-keys (mpc) */
	{ MODKEY,                       XK_F1,             spawn,          {.v = { "mpc", "clear", NULL } } },
	{ MODKEY,                       XK_F2,             spawn,          {.v = { "mpc", "volume", "-2", NULL } } },
	{ MODKEY,                       XK_F3,             spawn,          {.v = { "mpc", "volume", "+2", NULL } } },
	                             /* XK_F4 */
	{ MODKEY,                       XK_F5,             spawn,          {.v = { "mpc", "prev", NULL } } },
	{ MODKEY,                       XK_F6,             spawn,          {.v = { "mpc", "toggle", NULL } } },
	{ MODKEY,                       XK_F7,             spawn,          {.v = { "mpc", "next", NULL } } },
	{ MODKEY,                       XK_F8,             spawn,          {.v = { "mpc", "single", NULL } } },
	{ MODKEY,                       XK_F9,             spawn,          {.v = { "mpc", "shuffle", NULL } } },
	{ MODKEY,                       XK_F10,            spawn,          {.v = { "mpc", "repeat", NULL } } },
	{ MODKEY,                       XK_F11,            spawn,          {.v = { "mpc", "seek", "-5", NULL } } },
	{ MODKEY,                       XK_F12,            spawn,          {.v = { "mpc", "seek", "+5", NULL } } },
	/* misc */
	{ MODKEY|ShiftMask,             XK_q,              quit,           {0} },
	{ MODKEY|ShiftMask,             XK_F5,             xrdb,           {.v = NULL } }, /* reload xrdb */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

