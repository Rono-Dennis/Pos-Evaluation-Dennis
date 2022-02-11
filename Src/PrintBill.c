//printing bill

#include <sdk_tplus.h>

#include "DateScreen.h"
#include "Menu.h"
#include "util_sq.h"
#include <string.h>

 int PrintBill(billmessage){
	 byte p;  // Printer line index

	 T_GL_HWIDGET xDocument = NULL;
	 T_GL_HWIDGET xLayout;
	 T_GL_HWIDGET xPrint;

	 char *Raw_Columns;
	 char *Columns_Array[40];
	 char PrintData[256 + 1];byte xline = 0;int ret = 0;
	 char Statement[512];int NumOfRecords = 0;int NumberOfColumns = 0;
 	 Telium_Date_t xDate;char famount[12 + 1];
 	 char tcDate[32+1];


 	    Telium_Read_date (&xDate);

 		// Format date Date&Time
 		Telium_Sprintf (tcDate, "DATE: %2.2s/%2.2s/20%2.2s", xDate.day, xDate.month, xDate.year);

 		GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please Wait""\n""Preparing printing data", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);

 		xDocument = GoalCreateDocument(gGoalGraphicLibInstance, GL_ENCODING_UTF8);

 		xLayout = GL_Layout_Create(xDocument); //set the document layout

 		xPrint = GL_Print_Create    (xLayout);
 		GL_Widget_SetText      (xPrint, " SUMMARY REPORT ");
 		GL_Widget_SetItem      (xPrint, 0, xline++);
 		GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
 		GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
 		GL_Widget_SetWrap      (xPrint, TRUE);
 		GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);

 		xPrint = GL_Print_Create    (xLayout);
 		GL_Widget_SetText      (xPrint, tcDate);
 		GL_Widget_SetItem      (xPrint, 0, xline++);
 		GL_Widget_SetFontScale (xPrint, GL_SCALE_MEDIUM);
 		GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
 		GL_Widget_SetWrap      (xPrint, TRUE);
 		GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);


 		xPrint = GL_Print_Create    (xLayout);
 		GL_Widget_SetText      (xPrint, "===========================");
 		GL_Widget_SetItem      (xPrint, 0, xline++);
 		GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
 		GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
 		GL_Widget_SetWrap      (xPrint, TRUE);

 		xPrint = GL_Print_Create    (xLayout);
 		GL_Widget_SetText      (xPrint, billmessage);
 		GL_Widget_SetItem      (xPrint, 0, xline++);
 		GL_Widget_SetMargins   (xPrint, 15, 0, 0, 0, GL_UNIT_PIXEL);
 		GL_Widget_SetFontScale (xPrint, GL_SCALE_SMALL);
 		GL_Widget_SetBackAlign (xPrint, GL_ALIGN_LEFT);
 		GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);
 		GL_Widget_SetWrap (xPrint, TRUE);

 		xPrint = GL_Print_Create    (xLayout);
 		GL_Widget_SetText      (xPrint, "--------------------------------------");
 		GL_Widget_SetItem      (xPrint, 0, xline++);
 		GL_Widget_SetMargins   (xPrint, 1, 1, 1, 1, GL_UNIT_PIXEL);
 		GL_Widget_SetFontScale (xPrint, GL_SCALE_XLARGE);
 		GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
 		GL_Widget_SetWrap (xPrint, TRUE);

 }
