// Common types shared between the graphics server and the graphic library
#ifndef GL_Types_h_INCLUDED
#define GL_Types_h_INCLUDED

#ifndef GL_EXCEPTION
	#define GL_EXCEPTION
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** Graphic library context handle */
typedef struct T_GL_GRAPHIC_LIB *T_GL_HGRAPHIC_LIB;

/** Widget context handle */
typedef struct T_GL_WIDGET *T_GL_HWIDGET;

/** StringList file handle */
typedef struct T_TL_STRINGLIST *T_GL_HSTRINGLIST;

/** Viewer handle definition */
typedef struct T_GL_VIEWER *T_GL_HVIEWER;

/** Message handle definition (Stylus button, key, timer, ...) */
typedef struct T_GL_MESSAGE *T_GL_HMESSAGE;

/** Define a dir handle used in dir module function,
	a value of 0 / NULL indicates a bad handle */
typedef struct T_TL_DIR *T_GL_HDIR;

/** Disk mount handle */
typedef struct T_TL_MOUNT *T_GL_HMOUNT;

/** File handle */
typedef struct T_TL_FILE *T_GL_HFILE;

/** Scheme interface */
struct T_GL_SCHEME_INTERFACE;

/** Scheme interface */
typedef struct T_GL_SCHEME_INTERFACE
{
	/** Open the scheme
	@param interfac point on the current interface schema
	@return
		- GL_RESULT_SUCCESS : no error
		- GL_ERROR_FAILED   : if the scheme cannot be opened */
	unsigned long (*open) (struct T_GL_SCHEME_INTERFACE *  interfac);

	/** Close the scheme
	@param interfac point on the current interface schema  */
	void (*close)(struct T_GL_SCHEME_INTERFACE * interfac);

	/** Refresh the scheme content
	@param interfac point on the current interface schema
	@param label label handle to refresh
	@return To exit the dialog box you must return a value other than GL_RESULT_SUCCESS.
		The value you put in return is equivalent to the value returned by the function @ref GL_Dialog_Scheme.
		Below are some examples of reporting that you can use :
		- GL_KEY_VALID         : key valid pressed
		- GL_KEY_CANCEL        : key cancel pressed
		- GL_RESULT_INACTIVITY : the scheme ends with a timeout
		- GL_RESULT_SUCCESS    : Stay in the execution of the function @ref GL_Dialog_Scheme */
	unsigned long (*refresh)(struct T_GL_SCHEME_INTERFACE * interfac, T_GL_HWIDGET label);

	/** Private data pointer */
	void * privateData;
} T_GL_SCHEME_INTERFACE;


/** Scheme interface handle */
typedef struct T_GL_SCHEME_INTERFACE * T_GL_HSCHEME_INTERFACE;

/** Signature file handle */
typedef struct T_TL_SIGNATURE *T_GL_HSIGNATURE;

/** Widget context handle */
typedef struct T_TL_BUFFER *T_GL_HLIST_ID;

#include "GL_CommonTypes.h"

/**
@addtogroup GL_Types
@{
@addtogroup GL_TypesStruct Structures
@{
*/

/** Undefined dimension. A dimension defined disables the automatic placement in a layout.
This value set in size or position enables the automatic placement.
All sizes and position are initialized by default with this value */
#define GL_DIM_UNDEFINED ((T_GL_DIM)((((1<<GL_RESOLUTION)-1)>>1)))

/** Minimal dimension */
#define GL_DIM_MIN ((T_GL_DIM)(0))

/** Maximal dimension */
#define GL_DIM_MAX ((T_GL_DIM)(GL_DIM_UNDEFINED-1))

/*<ALL>
	Enum("UNIT",                                 "Unit supported by the graphical library.",
		Define("pixel",            "0",          "Dimensions or position are expressed in pixels"),
		Define("percent",          "1",          "Dimensions or position are expressed in percentage of parent"),
		Define("perthousand",      "2",          "Dimensions or position are expressed in per thousand of parent"),
		Define("px",               "0",          "Dimensions or position are expressed in pixels"),
		Define("%",               "1",          "Dimensions or position are expressed in percentage of parent"),
		Define("%%",             "2",          "Dimensions or position are expressed in per thousand of parent"),
		),
</ALL>*/
/** Unit supported by the graphical library.
When you select the unit GL_UNIT_PERCENT, the position and dimension on the screen are expressed in
ten thousandth of the width or height of the screen. */
typedef enum T_GL_UNIT
{
	GL_UNIT_PIXEL,      ///< all dimensions and position are expressed in pixels
	GL_UNIT_PERCENT,    ///< all dimensions and position are expressed in percentage of parent
	GL_UNIT_PERTHOUSAND ///< all dimensions and position are expressed in per thousand of parent
} T_GL_UNIT;

#define GL_VALUE_PERCENT 100      ///< Percent value
#define GL_VALUE_PERTHOUSAND 1000 ///< Perthousand value

/** local(TERMINAL) choice for Graphic Library target viewer **/
#define GL_VIEWER_LOCAL  (T_GL_HVIEWER)0

/** remote(PINPAD) choice for Graphic Library target viewer **/
#define GL_VIEWER_PINPAD (T_GL_HVIEWER)1

/** Low resolution of dimension */
#define GL_LOW_RESOLUTION 15

/** High resolution of dimension */
#define GL_HIGH_RESOLUTION 24

#if defined(__TELIUM2__) || defined(WIN32)
	/** Size and position precision */
	#define GL_RESOLUTION GL_LOW_RESOLUTION

	/** Defines a coordinates type. (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
	typedef short T_GL_COORD;

	/** Defines a dimension type (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
	typedef unsigned short T_GL_DIM;
#else
	/** Size and position precision */
	#define GL_RESOLUTION GL_HIGH_RESOLUTION

	/** Defines a coordinates type. (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
	typedef long T_GL_COORD;

	/** Defines a dimension type (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
	typedef unsigned long T_GL_DIM;
#endif

/** Location of prompt in the edit field */
typedef unsigned long T_GL_LOCATION;

/*<ALL>
	Struct("SIZE",                               "Defines a size",
		Integer("width",                         "Width coded according to the chosen unit"),
		Integer("height",                        "Height coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defining a Dimension */
typedef struct T_GL_SIZE
{
#ifdef WIN32
	/** @cond DOXYGEN_IGNORE */
	/** Width coded according to the chosen unit */
	T_GL_DIM width;

	/** Height coded according to the chosen unit */
	T_GL_DIM height;

	/** Unit of size */
	T_GL_UNIT unit;
	/** @endcond */
#else
	/** Width coded according to the chosen unit */
	unsigned int width /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :8; // fill to 32 bits (24 + 8)
	#endif
	/** @endcond */

	/** Height coded according to the chosen unit */
	unsigned int height /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** Unit of size */
	unsigned int unit /** @cond DOXYGEN_IGNORE */ :2 /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :6; // fill to 32 bits (24 + 2 + 6)
	#endif
	/** @endcond */
#endif
} T_GL_SIZE;

/** Handle on size */
typedef T_GL_SIZE * T_GL_HSIZE;

/*<ALL>
	Struct("POSITION",                           "Defines a position",
		Integer("x",                             "x coordinates coded according to the chosen unit"),
		Integer("y",                             "y coordinates coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines a position */
typedef struct T_GL_POSITION
{
#ifdef WIN32
	/** @cond DOXYGEN_IGNORE */
	/** X coded according to the chosen unit */
	T_GL_COORD x;

	/** Y coded according to the chosen unit */
	T_GL_COORD y;

	/** Unit of position */
	T_GL_UNIT unit;
	/** @endcond */
#else
	/** X coded according to the chosen unit */
	int x /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

		/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :8; // fill to 32 bits (24 + 8)
	#endif
	/** @endcond */

	/** Y coded according to the chosen unit */
	int y /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** Unit of position */
	unsigned int unit /** @cond DOXYGEN_IGNORE */ :2 /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :6; // fill to 32 bits (24 + 2 + 6)
	#endif
	/** @endcond */
#endif
} T_GL_POSITION;

/** Handle on position */
typedef T_GL_POSITION * T_GL_HPOSITION;


/** Move */
typedef T_GL_POSITION T_GL_MOVE;

/** Handle on move */
typedef T_GL_MOVE * T_GL_HMOVE;

/*<ALL>
	Struct("MARGINS",                            "Defines all margins",
		Integer("left",                          "Left margin coded according to the chosen unit"),
		Integer("top",                           "Top margin coded according to the chosen unit"),
		Integer("right",                         "Right margin coded according to the chosen unit"),
		Integer("bottom",                        "Bottom margin coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines a margins */
typedef struct T_GL_MARGINS
{
#ifdef WIN32
	/** @cond DOXYGEN_IGNORE */
	/** Left margin coded according to the chosen unit */
	T_GL_DIM left;

	/** Top margin coded according to the chosen unit */
	T_GL_DIM top;

	/** Right margin coded according to the chosen unit */
	T_GL_DIM right;

	/** Bottom margin coded according to the chosen unit */
	T_GL_DIM bottom;

	/** Unit of margin */
	T_GL_UNIT unit;
	/** @endcond */
#else
	/** Left margin coded according to the chosen unit */
	unsigned int left /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :8; // fill to 32 bits (24 + 8)
	#endif
	/** @endcond */

	/** Top margin coded according to the chosen unit */
	unsigned int top /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :8; // fill to 32 bits (24 + 8)
	#endif
	/** @endcond */

	/** Right margin coded according to the chosen unit */
	unsigned int right /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :8; // fill to 32 bits (24 + 8)
	#endif
	/** @endcond */

	/** Bottom margin coded according to the chosen unit */
	unsigned int bottom /** @cond DOXYGEN_IGNORE */ :GL_RESOLUTION /** @endcond */;

	/** Unit of margin */
	unsigned int unit /** @cond DOXYGEN_IGNORE */ :2 /** @endcond */;

	/** @cond DOXYGEN_IGNORE */
	#if GL_RESOLUTION == GL_HIGH_RESOLUTION
		unsigned int 	    :6; // fill to 32 bits (24 + 2 + 6)
	#endif
	/** @endcond */
#endif
} T_GL_MARGINS;

/** Margins handle */
typedef T_GL_MARGINS * T_GL_HMARGINS;

/*<ALL>
	Struct("PADDINGS",                           "Defines a paddings",
		Integer("left",                          "Left padding coded according to the chosen unit"),
		Integer("top",                           "Top padding coded according to the chosen unit"),
		Integer("right",                         "Right padding coded according to the chosen unit"),
		Integer("bottom",                        "Bottom padding coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines paddings */
typedef T_GL_MARGINS T_GL_PADDINGS;

/** Paddings handle */
typedef T_GL_PADDINGS * T_GL_HPADDINGS;


/*<ALL>
	Struct("BORDERS",                            "Defines a borders",
		Integer("left",                          "Left border coded according to the chosen unit"),
		Integer("top",                           "Top border coded according to the chosen unit"),
		Integer("right",                         "Right border coded according to the chosen unit"),
		Integer("bottom",                        "Bottom border coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		RefOne("color",            "COLOR",      "border color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)"),
		),
</ALL>*/

/** Defines a borders */
typedef struct T_GL_BORDERS
{
	/** Border size */
	T_GL_MARGINS size;

	/** Border colors */
	T_GL_COLOR color;
} T_GL_BORDERS;

/** Borders handle */
typedef T_GL_BORDERS * T_GL_HBORDERS;


/** Rectangle */
typedef struct T_GL_RECT
{
	/** Defines a position */
	T_GL_POSITION position;

	/** Defining a Dimension */
	T_GL_SIZE     size;
} T_GL_RECT;

/** Handle on rectangle */
typedef T_GL_RECT * T_GL_HRECT;

/*<ALL>
	Struct("RANGE","Range",
		Integer("min",                           "The minimum limit of the scroll bar"),
		Integer("max",                           "The maximum limit of the scroll bar"),
		Integer("value",                         "The value of the scroll bar"),
		Integer("page",                          "The page size of the scroll bar (scales the size of slider in the scrollbar)"),
		Integer("step",                          "The step increment"),
		),
</ALL>*/
/** Range */
typedef struct T_GL_RANGE
{
	/** lower bound */
	T_GL_COORD min;

	/** upper bound */
	T_GL_COORD max;

	/** current value */
	T_GL_COORD value;

	/** page */
	T_GL_DIM page;

	/** step */
	T_GL_DIM step;
} T_GL_RANGE;

/** Handle on range */
typedef T_GL_RANGE * T_GL_HRANGE;


/** Date */
typedef struct T_GL_DATE
{
	/** Year (1900..2100) */
	ushort year;

	/** Month (1..12) */
	byte month;

	/** Day (1..31) */
	byte day;

	/** Hour (0..23) */
	byte hour;

	/** Minute (0..59) */
	byte minute;

	/** Second (0..59) */
	byte second;
}T_GL_DATE;

/** Date handle */
typedef T_GL_DATE * T_GL_HDATE;


/** Ip V4 address string */
typedef struct T_GL_IP_STR
{
#define GL_IP_MAX 16 ///< Maximal size of ip address string

	/** Ip address string */
	char address[GL_IP_MAX];
} T_GL_IP_STR;

/** Ip V4 address handle */
typedef T_GL_IP_STR * T_GL_HIP_STR;

/** Ip V4 address integer value  (0x01020304 -> 001.002.003.004) */
typedef unsigned long T_GL_IP;

/** Ip V4 address integer handle */
typedef T_GL_IP * T_GL_HIP;

/** Converts ip string address into ip integer address
@param ip ip integer address
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp}
@return ip string address */
T_GL_IP_STR GL_Ip_ToString(T_GL_IP ip);

/** Converts ip integer address into ip string address
@param ipStr ip string address
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp}
@return return ip address or 0 if failed*/
T_GL_IP GL_Ip_ToInt(const char * ipStr);


/*<ALL>
	Struct("ITEM",                               "Unit used by the coordinates or sizes",
		Integer("column",                        "Column number in the layout (first row = 0) "),
		Integer("row",                           "Row number in the layout (first column = 0)"),
		),
</ALL>*/
/** Item in layout */
typedef struct T_GL_ITEM
{
	/** Row number in layout (first row = 0) */
	T_GL_DIM row;

	/** Column number in layout (first column = 0) */
	T_GL_DIM column;
}T_GL_ITEM;

/** Version and revision of DLL */
typedef struct T_GL_VERSION
{
	/** Version value */
	ulong version;

	/** Revision value */
	ulong revision;
} T_GL_VERSION;


/**
@}
*/


/**
@}
@addtogroup GL_TypesOther Other definitions
@{
*/

/* ************************************************************************************************************** */
/*                                                 WIDGET TYPE                                                    */
/* ************************************************************************************************************** */

/** Type of widget */
typedef enum T_GL_TYPE
{
	GL_TYPE_UNDEFINED = 0,
	GL_TYPE_WIDGET_START = 0x123,
	GL_TYPE_GRAPHIC_LIB,           ///< @see GL_GraphicLib
	GL_TYPE_WINDOW,                ///< @see GL_Window
	GL_TYPE_DIALOG,                ///< @see GL_Dialog
	GL_TYPE_LIST,                  ///< @see GL_List
	GL_TYPE_SKIN,                  ///< @see GL_Skin
	GL_TYPE_TIMER,                 ///< @see GL_Timer
	GL_TYPE_DRAWING,               ///< @see GL_Drawing
	GL_TYPE_VSCROLLBAR,            ///< @see GL_VScrollBar
	GL_TYPE_HSCROLLBAR,            ///< @see GL_HScrollBar
	GL_TYPE_SCROLLVIEW,            ///< @see GL_ScrollView
	GL_TYPE_KEY,                   ///< @see GL_Button
	GL_TYPE_MEDIA,                 ///< @see GL_Media
	GL_TYPE_HSLIDER,               ///< @see GL_HSlider
	GL_TYPE_PLUGIN,                ///< @see GL_Plugin
	GL_TYPE_DOCUMENT,              ///< @see GL_Document
	GL_TYPE_PRINT,                 ///< @see GL_Print
	GL_TYPE_SIGNATURE,             ///< @see GL_Sign
	GL_TYPE_USERCONTROL,           ///< @see GL_UserControl
	/* __NEWTYPE__ */

	// Widget types that can be inserted into a list
	GL_TYPE_ITEM_START = 0x234,

		GL_TYPE_BUTTON,            ///< @see GL_Button
		GL_TYPE_CHECKBUTTON,       ///< @see GL_CheckButton
		GL_TYPE_RADIOBUTTON,       ///< @see GL_RadioButton
		GL_TYPE_LABEL,             ///< @see GL_Label
		GL_TYPE_EDIT,              ///< @see GL_Edit
		GL_TYPE_PROGRESSBAR,       ///< @see GL_ProgressBar
		GL_TYPE_ICON,              ///< @see GL_Icon
		GL_TYPE_LAYOUT,            ///< @see GL_Layout
		GL_TYPE_PALETTE,           ///< @see GL_Palette
		GL_TYPE_PICTURE,           ///< @see GL_Picture
		GL_TYPE_VIRTUALKEYBOARD,   ///< @see GL_VirtualKeyboard
		GL_TYPE_ICONBUTTON,        ///< @see GL_IconButton
		GL_TYPE_BARCODE,           ///< @see GL_Barcode
		GL_TYPE_ARROWBUTTON,       ///< @see GL_Button
		GL_TYPE_CHECK,             ///< @see GL_CheckButton
		GL_TYPE_RADIO,             ///< @see GL_RadioButton

	GL_TYPE_ITEM_STOP,


	// INSERT NEW TYPE BEFORE
	GL_TYPE_FIRST_RFU       = GL_TYPE_WIDGET_START + 0x800,
	GL_TYPE_WIDGET_END = 0xFFF

} T_GL_TYPE;


/** Defines the icons supported by the message box */
typedef enum T_GL_DIALOG_ICON
{
	GL_ICON_NONE,         ///< The message box does not have any icon.
	GL_ICON_QUESTION,     ///< An icon indicating that the message is asking a question.
	GL_ICON_INFORMATION,  ///< An icon indicating that the message is nothing out of the ordinary.
	GL_ICON_WARNING,      ///< An icon indicating that the message is a warning, but can be dealt with.
	GL_ICON_ERROR      ///< An icon indicating that the message represents a critical problem.
} T_GL_DIALOG_ICON;


/** Defines the buttons managed in the dialogs */
typedef enum T_GL_BUTTONS
{
	GL_BUTTON_NONE                = 0x0000, ///< No button managed
	GL_BUTTON_VALID               = 0x0001, ///< Green button validation managed
	GL_BUTTON_CANCEL              = 0x0002, ///< Red button cancellation managed
	GL_BUTTON_CORRECTION          = 0x0004, ///< Yellow button correction managed
	GL_BUTTON_SHORTCUT            = 0x0008, ///< Shortcut present (reserved for the manager application)

	GL_BUTTON_VALID_CANCEL        = (GL_BUTTON_VALID|GL_BUTTON_CANCEL),
	GL_BUTTON_CORRECTION_CANCEL   = (GL_BUTTON_CORRECTION|GL_BUTTON_CANCEL),
	GL_BUTTON_VALID_CORRECTION    = (GL_BUTTON_VALID|GL_BUTTON_CORRECTION),
	GL_BUTTON_ALL                 = (GL_BUTTON_VALID|GL_BUTTON_CANCEL|GL_BUTTON_CORRECTION),
	GL_BUTTON_DEFAULT             = 0xFFFF ///< To use the default shortcuts
} T_GL_BUTTONS;


/* ************************************************************************************************************** */
/*                                                 ALIGN                                                          */
/* ************************************************************************************************************** */

/*<ALL>
	Enum("ALIGN",                                "Item alignement",
		Define("center",           "0",          "The item is placed in the center"),
		Define("top",              "4",          "The item is placed in vertical on the top"),
		Define("bottom",           "8",          "The item is placed in vertical on the bottom"),
		Define("left",             "1",          "The item is placed in horizontal on the left"),
		Define("right",            "2",          "The item is placed in horizontal on the right"),
		Define("top,left",         "5",          "The item is placed in the top left corner"),
		Define("top,right",        "6",          "The item is placed in the top right corner"),
		Define("bottom,left",      "9",          "The item is placed in the bottom left corner"),
		Define("bottom,right",     "10",         "The item is placed in the bottom right corner"),
		),
</ALL>*/

/** Alignement */
typedef enum T_GL_ALIGN
{
	GL_ALIGN_CENTER        = 0x00, ///< the item is placed in the center
	GL_ALIGN_LEFT          = 0x01, ///< the item is placed in horizontal on the left
	GL_ALIGN_RIGHT         = 0x02, ///< the item is placed in horizontal on the right
	GL_ALIGN_TOP           = 0x04, ///< the item is placed in vertical on the top
	GL_ALIGN_BOTTOM        = 0x08, ///< the item is placed in vertical on the bottom

	GL_ALIGN_TOP_LEFT      = GL_ALIGN_TOP    | GL_ALIGN_LEFT,   ///< the item is placed on the top left corner
	GL_ALIGN_TOP_RIGHT     = GL_ALIGN_TOP    | GL_ALIGN_RIGHT,  ///< the item is placed on the top right corner

	GL_ALIGN_BOTTOM_LEFT   = GL_ALIGN_BOTTOM | GL_ALIGN_LEFT,   ///< the item is placed on the bottom left corner
	GL_ALIGN_BOTTOM_RIGHT  = GL_ALIGN_BOTTOM | GL_ALIGN_RIGHT,  ///< the item is placed on the bottom right corner

	GL_ALIGN_HORIZONTAL    = GL_ALIGN_LEFT   | GL_ALIGN_RIGHT,  ///< Horizontal alignement mask
	GL_ALIGN_VERTICAL      = GL_ALIGN_TOP    | GL_ALIGN_BOTTOM  ///< Vertical alignement mask
} T_GL_ALIGN;


/*<ALL>
	Enum("DIRECTION",                            "Direction of the change in size",
		Define("width",            "1",          "Authorizes a change in size in width"),
		Define("height",           "2",          "Authorizes a change in size in height"),
		Define("all",              "3",          "Authorizes a change in size all direction"),
		Define("none",             "0",          "Prohibits any change in size"),
		),
</ALL>*/
/** Direction of grow or crop */
typedef enum T_GL_DIRECTION
{
	GL_DIRECTION_NONE   = 0, ///< No modification
	GL_DIRECTION_WIDTH  = 1, ///< Width adaptation direction
	GL_DIRECTION_HEIGHT = 2, ///< Height adaptation direction
	GL_DIRECTION_ALL    = (GL_DIRECTION_WIDTH | GL_DIRECTION_HEIGHT) ///< All adaptation direction
} T_GL_DIRECTION;

/*<ALL>
	Enum("STATE",                                  "State to consider whether to display the widget",
		Define("focused",            "1",          "The widget is displayed when it has focus"),
		Define("unfocused",          "2",          "The widget is displayed when it has not focus"),
		Define("checked",            "4",          "The widget is displayed when it is checked"),
		Define("unchecked",          "8",          "The widget is displayed when it is not checked"),
		Define("pressed",           "16",          "The widget is displayed when it is pressed"),
		Define("unchecked",         "32",          "The widget is displayed when it is not pressed"),
		Define("pushed",            "64",          "The widget is displayed when it is pressed (prioritary than the other bits)"),
		Define("unpushed",         "128",          "The widget is displayed when it is not pressed (prioritary than the other bits)"),
		Define("focused,checked",    "5",          "The widget is displayed when it has focus and is checked"),
		Define("focused,unchecked",  "9",          "The widget is displayed when it has focus and is not checked"),
		Define("unfocused,checked",  "6",          "The widget is displayed when it has not focus and is checked"),
		Define("unfocused,unchecked","10",         "The widget is displayed when it has not focus and is not checked"),

		Define("all",                "63",         "The widget is always displayed"),
		),
</ALL>*/

/** State to consider whether to display the widget @ref GL_Widget_StateMaskProperties */
typedef enum T_GL_STATE
{
	GL_STATE_FOCUSED = 0x01, ///< The widget has focus
	GL_STATE_CHECKED = 0x02, ///< The widget is checked
	GL_STATE_PRESSED = 0x04, ///< The widget is pressed

	GL_STATE_PUSHED   = 0x08, ///< The widget is pressed, This bit does not work like the previous, if set it priority over other.
	GL_STATE_DISABLED = 0x10, ///< The widget is disabled

	GL_STATE_ALL = (GL_STATE_FOCUSED | GL_STATE_CHECKED | GL_STATE_PRESSED | GL_STATE_DISABLED),

	GL_STATE_EMPTY = 0
} T_GL_STATE;


/** Arrow direction */
typedef enum T_GL_ARROW_DIRECTION
{
	GL_ARROW_DIRECTION_NONE,          ///< No arrow on the button
	GL_ARROW_DIRECTION_LEFT,          ///< The arrow is displayed at left
	GL_ARROW_DIRECTION_RIGHT,         ///< The arrow is displayed at right
	GL_ARROW_DIRECTION_LEFT_AND_RIGHT ///< The arrow is displayed left and right
} T_GL_ARROW_DIRECTION;


/*<ALL>
	Enum("TRANSFORMATION",             "Image transformation",
		Define("none",                "0",  "No treatment of the image : if the image is too large it will be truncated, if it is too small it will be displayed as it is"),
		Define("repeatx",             "1",  "The image is repeated on the x-axis"),
		Define("repeaty",             "2",  "The image is repeated on the y-axis"),
		Define("repeatall",           "3",  "The image is repeated on all directions"),
		Define("stretchx",            "4",  "The image is stretched along the x-axis only"),
		Define("stretchy",            "5",  "The image is stretched along the y-axis only"),
		Define("stretchall",          "6",  "The image is stretched along the all directions"),
		Define("fitx",                "7",  "The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated"),
		Define("fity",                "8",  "The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated"),
		Define("fitall",              "9",  "The image size will be adapted to fit exactly to the space without distortion"),
		Define("repeatxstretchy",     "10", "The image is repeated on the x-axis and stretched along the y-axis"),
		Define("repeatystretchx",     "11", "The image is repeated on the y-axis and stretched along the x-axis"),
		),
</ALL>*/

/** Image transformation */
typedef enum T_GL_TRANSFORMATION
{
	GL_TRANSFORMATION_NONE,               ///< No treatment of the image : if the image is too large it will be truncated, if it is too small it will be displayed as it is
	GL_TRANSFORMATION_REPEAT_X,           ///< The image is repeated on the x-axis
	GL_TRANSFORMATION_REPEAT_Y,           ///< The image is repeated on the y-axis
	GL_TRANSFORMATION_REPEAT_ALL,         ///< The image is repeated on all directions
	GL_TRANSFORMATION_STRETCH_X,          ///< The image is stretched along the x-axis only
	GL_TRANSFORMATION_STRETCH_Y,          ///< The image is stretched along the y-axis only
	GL_TRANSFORMATION_STRETCH_ALL,        ///< The image is stretched along the all directions
	GL_TRANSFORMATION_FIT_X,              ///< The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated
	GL_TRANSFORMATION_FIT_Y,              ///< The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated
	GL_TRANSFORMATION_FIT_ALL,            ///< The image size will be adapted to fit exactly to the space without distortion
	GL_TRANSFORMATION_REPEAT_X_STRETCH_Y, ///< The image is repeated on the x-axis and stretched along the y-axis
	GL_TRANSFORMATION_REPEAT_Y_STRETCH_X, ///< The image is repeated on the y-axis and stretched along the x-axis

	GL_TRANSFORMATION_LAST
} T_GL_TRANSFORMATION;

/*<ALL>
	Struct("INPUTMODE",                           "Configure the input mode",
		Bool("blank",                             "false:hide the blank part of input, true:show the blank part of input"),
		Bool("password",                          "false:The characters entered are displayed, true:The characters entered are replaced by the '*' (used to enter password)"),
		Bool("prompt",                            "false:hide the prompt, true:show the prompt"),
		Bool("replace",                           "false:The characters entered are inserted into the input field, true:The characters entered replace existing characters in the input field"),
		Bool("zeroSignificant",                   "false:The zeros are not displayed in the early numbers, true:The zeros are displayed in the early numbers (eg 000123)"),
	),
</ALL>*/
/** Input mode mask */
typedef enum T_GL_MODE
{
	// Input behavior
	GL_MODE_INSERT            = 0x00, ///< The characters entered are inserted into the input field
	GL_MODE_REPLACE           = 0x01, ///< The characters entered replace existing characters in the input field

	// Password
	GL_MODE_NORMAL            = 0x00, ///< The characters entered are displayed
	GL_MODE_PASSWORD          = 0x02, ///< The characters entered are replaced by the '*' (used to enter password)

	// 0 not significant
	GL_MODE_0_SIGNIFICANT     = 0x00, ///< The zeros are displayed in the early numbers (eg 000123)
	GL_MODE_0_NOT_SIGNIFICANT = 0x08, ///< The zeros are not displayed in the early numbers

	// Hide or show prompt
	GL_MODE_SHOW_PROMPT       = 0x00, ///< Show the prompt
	GL_MODE_HIDE_PROMPT       = 0x10, ///< Hide the prompt

	// Hide or show blank part
	GL_MODE_SHOW_BLANK        = 0x00, ///< Show the blank part of input (example : with the following pattern "/d/d,/d/d/D./D/D" it shows the comma unnecessary : "  ,  0.00")
	GL_MODE_HIDE_BLANK        = 0x20  ///< Hide the blank part of input (example : with the following pattern "/d/d,/d/d/D./D/D" it hides the comma unnecessary : "0.00")
} T_GL_MODE;


/** Undefined position in layout */
#define GL_ITEM_UNDEFINED ((T_GL_DIM)(-1))

/** Relative size to the size of the screen */
typedef enum T_GL_SCALE
{
	GL_SCALE_XXSMALL = 0x3FF0, ///< Extra extra small font size (Optimized to display an average of 24 characters on the screen width)
	GL_SCALE_XSMALL  = 0x3FF1, ///< Extra small font size  (Optimized to display an average of 24 characters on the screen width)
	GL_SCALE_SMALL   = 0x3FF2, ///< Small font size (Optimized to display an average of 22 characters on the screen width)
	GL_SCALE_MEDIUM  = 0x3FF3, ///< Medium font size (Optimized to display an average of 20 characters on the screen width)
	GL_SCALE_LARGE   = 0x3FF4, ///< Large font size (Optimized to display an average of 16 characters on the screen width)
	GL_SCALE_XLARGE  = 0x3FF5, ///< Extra large font size (Optimized to display an average of 12 characters on the screen width)
	GL_SCALE_XXLARGE = 0x3FF6  ///< Extra extra large font size (Optimized to display an average of 10 characters on the screen width)
} T_GL_SCALE;

/** Definition pointer callback message processing
@param message message handle
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp}
@return Returns false to skip the processing of this message. Returns true to consider the message*/
typedef bool (*T_GL_MESSAGE_CALLBACK)(T_GL_HMESSAGE message);

/** C plus plus base class used to bind a method to a widget event */
typedef struct T_GL_CLASS_BINDABLE * T_GL_HCLASS_BINDABLE;

/** Callback function called periodically to update the progress bar */
typedef T_GL_COORD (*T_GL_DIALOG_PROGRESS_UPDATE)(T_GL_COORD value);

/** Defines the class binder manager */
typedef struct T_GL_CLASS_BINDER * T_GL_HCLASS_BINDER;

/** Callback for filtering the display of files or directories
@param path Path full file name (with the filesystem)
@param isFile true indicates a file, false indicates a directory
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp}
@return must return true if the file is displayed, otherwise returns false */
typedef bool (*T_GL_DIALOG_FILE_FILTER)(const char * path, bool isFile);

/** This callback function is to initialize the user control
@param userControl user control handle
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp} */
typedef void (*T_GL_USERCONTROL_CALLBACK)(T_GL_HWIDGET userControl);

/** This callback function instanciate the C++ context object when the user control widget is created
@param userControl user control handle
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp}
@return the instanciated object */
typedef void * (*T_GL_USERCONTROL_CONSTRUCTOR)(T_GL_HWIDGET userControl);

/** This callback function destroy the C++ object instanciated
@param object C++ object instanciated with @ref T_GL_USERCONTROL_CONSTRUCTOR function
@ing_framework {fwt2,fwtplus,fwt3}
@ing_hardware {hwt1,hwt2,hwtetra}
@ing_language {lang_c,lang_cpp} */
typedef void (*T_GL_USERCONTROL_DESTRUCTOR)(void * object);

/** Callback function called when the slider change */
typedef void (*T_GL_DIALOG_SLIDER_UPDATE)(T_GL_RANGE range) GL_EXCEPTION;

/**
@}
*/

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif // GL_Types_h_INCLUDED
