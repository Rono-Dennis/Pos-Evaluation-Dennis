#include <sdk_tplus.h>

#include "DateScreen.h"
#include "Menu.h"
#include "util_sq.h"
#include <string.h>
#include <stdio.h>
#include <sdk_tplus.h>
#include "Goal.h"

//1.	Select bill payment
//2.	Enter bill number (bill number should be numeric, its length should between 5-8 characters). Perform validation of input and display appropriate error message where necessary.
//3.	Enter bill amount
//4.	Print receipt showing bill number entered, amount and date/time

int billpayment(){

//	    	//Declarations

	    	ulong ret;
	    	char maskEntry[]="/d/d/d/d/d/d/d/D";
	    	int i,len, f=0, length=8;

//	    	bill data
	    	char billNumber[100];
	    	char billmessage[256];
	    	char message[256];
	    	ulong message1 = 0;
	    	ulong amountResult = 0;
	    	char confirmBilling[100];
	    	char saleAmount[256];
	    	memset(saleAmount, 0, sizeof saleAmount);
	    	memset(billNumber, 0, sizeof billNumber);

//	    	amount data
			char amountNumber[100];
			char amountmessage[256];
			char messageAmt[256];

	    	//	    	return value
	    	lblCorrect:
	    	  GL_Dialog_Amount(gGoalGraphicLibInstance,"bill number: ","Enter bill :", maskEntry, billNumber,sizeof(billNumber)-1, "", GL_ALIGN_BOTTOM_RIGHT, 10*10000);



//	    	validate
	    	if (strlen(billNumber) > 9 || strlen(billNumber) < 5) {

	    		lblback:
					  GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please enter number less than 8 or more than 5", GL_ICON_NONE, GL_BUTTON_ALL, 2*1000);

//					if(ret == GL_KEY_CANCEL){
//					goto lblback;
//					}
					goto lblCorrect;
				}
	    	else {


			////	    	return value
			labelAmount:
			   GL_Dialog_Amount(gGoalGraphicLibInstance,"Enter Amount: ","Amount", maskEntry, amountNumber,sizeof(amountNumber)-1, "", GL_ALIGN_BOTTOM_RIGHT, 10*10000);


				}

//	    	get billnumber data
			memset(billmessage, 0, sizeof billmessage);
			strcat(billmessage, billNumber);
//	    	get amount data
			memset(amountmessage, 0, sizeof amountmessage);
			strcat(amountmessage, amountNumber);








//			strcat(billmessage,"Your Bill number is: ");

//			ret = GL_Dialog_Message(gGoalGraphicLibInstance, NULL, billmessage, GL_ICON_INFORMATION, GL_BUTTON_ALL, 10*10000);
	    	//Printer declarations
	    	static const ST_PRN_LINE xPrinter =
	    	{
	    	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
	    	};
	    	T_GL_HWIDGET xDocument = NULL;
	    	T_GL_HWIDGET xLayout;
	    	T_GL_HWIDGET xPrint;
	    	byte xline = 7;
	    	char tcDate[32+1];
	    	Telium_Date_t xDate;
	    	Telium_Read_date (&xDate);

	    	// Format date Date&Time
	    	Telium_Sprintf (tcDate, "DATE: %2.2s/%2.2s/20%2.2s", xDate.day, xDate.month, xDate.year);

	    	// Display Preparing printing data
	    		// ********************
	    	GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please Wait""\n""Preparing printing data", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);


	    	//TODO Print receipt
	    	xDocument = GoalCreateDocument(gGoalGraphicLibInstance, GL_ENCODING_UTF8);
	    	xLayout = GL_Layout_Create(xDocument);


	    	//sales information
	    	xPrint = GL_Print_Create    (xLayout);
	    	GL_Widget_SetText      (xPrint, "Bill Information");
	    	GL_Widget_SetItem      (xPrint, 0, xline++);
	    	GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
	    	GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
	    	GL_Widget_SetWrap      (xPrint, TRUE);
	    	GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);

	    	xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "-------------------------------------------------------------------------");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetMargins   (xPrint, 1, 1, 1, 1, GL_UNIT_PIXEL);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_SMALL);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);

			xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "Bill Number");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
			GL_Widget_SetWrap      (xPrint, TRUE);
			GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);


	    	xPrint = GL_Print_Create    (xLayout);
	    	GL_Widget_SetText      (xPrint, billmessage);
	    	GL_Widget_SetItem      (xPrint, 0, xline++);
	    	GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
	    	GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
	    	GL_Widget_SetWrap      (xPrint, TRUE);
	    	GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);


	    	xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "-------------------------------------------------------------------------");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetMargins   (xPrint, 1, 1, 1, 1, GL_UNIT_PIXEL);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_SMALL);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);

			xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "Entered Amount");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
			GL_Widget_SetWrap      (xPrint, TRUE);
			GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);


			xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, amountmessage);
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
			GL_Widget_SetWrap      (xPrint, TRUE);
			GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);

	    	xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "-------------------------------------------------------------------------");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetMargins   (xPrint, 1, 1, 1, 1, GL_UNIT_PIXEL);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_SMALL);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);

			xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, "Current Date");
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
			GL_Widget_SetWrap      (xPrint, TRUE);
			GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);

			xPrint = GL_Print_Create    (xLayout);
			GL_Widget_SetText      (xPrint, tcDate);
			GL_Widget_SetItem      (xPrint, 0, xline++);
			GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
			GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
			GL_Widget_SetMargins   (xPrint, 10, 10, 10, 100, GL_UNIT_PIXEL);
			GL_Widget_SetWrap      (xPrint, TRUE);
			GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);
			GoalPrnDocument(xDocument);

	    	//End printing

			lblEnd:
			return ret;
//            ret = GL_Dialog_Message(gGoalGraphicLibInstance, "You've entered full information", confirmBilling , GL_ICON_QUESTION, GL_BUTTON_VALID_CANCEL, 5*1000);


//			return sizeof amountResult;
//			 return 1;

}
