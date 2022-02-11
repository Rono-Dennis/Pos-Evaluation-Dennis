/// 1. Select sale
/// 2. Enter amount (application should only accept amount > 1 and < 5,000).
/// 3. Prompt user to insert/swipe card
/// 4. Prompt user to enter card's PIN
/// 5. Print receipt showing the card number, amount entered and date/time
            #include <stdio.h>
	    	#include <sdk_tplus.h>
	    	#include "Menu.h"
	    	#include "Goal.h"
            #include "GTL_Assert.h"
	    	static Telium_File_t *hMag13 = NULL;
	    	static Telium_File_t *hMag2 = NULL;
	    	static Telium_File_t *hMag3 = NULL;
	    	#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
	    	int returnVal = 0;
	    	char trk1[128 + 1],trk2[128 + 1],trk3[128 + 1];
	    	num = 0;
	    	byte * buf;

	    	// Function to Enter Amount
	    	int sale(){
	    	//Declarations
	    		int ret = 0;
	    	char saleAmount[100];
	    	char confirmSale[100];
	    	char saleMasc[] = "/d,/d/d/D";
	    	char pinMask[] = "/d/d/d/d";
	    	char currency[10] = "Ksh";
	    	char pinValue[4 + 1];
	    	ulong amountResult = 0;
	    	ulong message = 0;
	    	char pinEntry = 0;
	    	int amount = 0;


	    	//Magstripe definitions

	    	int magCardPresent = FALSE;
	    	unsigned int sta = 0;
	    	char *src = 0;
	    	char *dst = 0;
	    	Telium_File_t *hMag31=NULL, *hMag2=NULL, *hMag3=NULL;
	    	char tcTmp[128];
	    	byte ucLen=0;
	    	char tcTrk1[128], tcTrk2[128], tcTrk3[128];
	    	int iRet = ISO_OK - 1;
	    	int cardNumber[256];

	    	//Card inserted variables
	    	Telium_File_t* hCam;
	    	unsigned char ucStatus;
	    	unsigned char   cardapplinum;
	    	hCam = NULL;

	    	//Clean memory before use
	    	memset(saleAmount, 0, sizeof saleAmount);
	    	memset(confirmSale, 0, sizeof confirmSale);
	    	memset(pinValue, 0, sizeof pinValue);
	    	memset(tcTmp, 0, sizeof tcTmp);
	    	memset(tcTrk1, 0, sizeof tcTrk1);
	    	memset(tcTrk2, 0, sizeof tcTrk2);
	    	memset(tcTrk3, 0, sizeof tcTrk3);

	    	//Dialog for input Amount

	    	char amountmessage[256];
	    	labelAmount:
	    	memset(saleAmount, 0, sizeof saleAmount);
	    	amount = 0.00;
	    	amountResult = GL_Dialog_Amount(gGoalGraphicLibInstance, "Sale", "Enter Amount", saleMasc, saleAmount, sizeof(saleAmount),currency, GL_ALIGN_BOTTOM_RIGHT, 6* 1000);

//	    	get amount data
		memset(amountmessage, 0, sizeof amountmessage);
		strcat(amountmessage, saleAmount);
        if(amountResult == GL_KEY_CANCEL){
        goto labelEnd;
         }

    // Type cast amount to enable validation
       sscanf(saleAmount, "%d", &amount);
       amount = amount/100;

       if( amount < 1 || amount >= 5000){
       message = GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please enter amount less than 5000 or more than 1", GL_ICON_NONE, GL_BUTTON_ALL, 5*1000);

       if(message == GL_KEY_CANCEL){
       goto labelEnd;
       }
       goto labelAmount;
       }
       //Prompt for Card insert or swipe



       while(!magCardPresent){

    	   const char*  Smart(char *amountmessage);
       }
	    	//PIN Input
//       int confirm(){
    	   lblKO:
    		pinEntry = GL_Dialog_Password(gGoalGraphicLibInstance, NULL, "Enter PIN", pinMask, pinValue, sizeof pinValue, 10 * 1000);

    	//	    	while(!magCardPresent)
    	//
    	//	    	{ Smart();}

    		    	static const ST_PRN_LINE xPrinter =
    		    	{
    		    	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
    		    	};
    		    	T_GL_HWIDGET xDocument = NULL;
    		    	T_GL_HWIDGET xLayout;
    		    	T_GL_HWIDGET xPrint;
    		    	byte xline = 7;


    		    	// Display Preparing printing data
    		    		// ********************
    		    	lblprnt:
    		    	GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please Wait""\n""Preparing printing data", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);

    		    	char tcDate[32+1];
    				Telium_Date_t xDate;
    				Telium_Read_date (&xDate);
    				Telium_Sprintf (tcDate, "DATE: %2.2s/%2.2s/20%2.2s", xDate.day, xDate.month, xDate.year);


    		    	//TODO Print receipt
    		    	xDocument = GoalCreateDocument(gGoalGraphicLibInstance, GL_ENCODING_UTF8);
    		    	xLayout = GL_Layout_Create(xDocument);


    		    	//sales information
    		    	xPrint = GL_Print_Create    (xLayout);
    		    	GL_Widget_SetText      (xPrint, "Sale Information");
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
    				GL_Widget_SetText      (xPrint, "card number");
    				GL_Widget_SetItem      (xPrint, 0, xline++);
    				GL_Widget_SetFontScale (xPrint, GL_SCALE_LARGE);
    				GL_Widget_SetBackAlign (xPrint, GL_ALIGN_CENTER);
    				GL_Widget_SetWrap      (xPrint, TRUE);
    				GL_Widget_SetFontStyle (xPrint, GL_FONT_STYLE_BOLD);


    		    	xPrint = GL_Print_Create    (xLayout);
    		    	GL_Widget_SetText      (xPrint, cardNumber);
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
//       }

       labelEnd:
       return ret;
       }





// TODO: Confirm transaction
//strcat(confirmSale, "Confirm sale of amount:\n");
//sprintf(saleAmount, "%f", amount);
//strcat(confirmSale, saleAmount);
//strcat(confirmSale, "\nBy account: ");
//message = GL_Dialog_Message(gGoalGraphicLibInstance, "Confirm Transaction", confirmSale , GL_ICON_QUESTION, GL_BUTTON_VALID_CANCEL, 0);
//if(message == GL_KEY_CANCEL){
//goto labelEnd;
//}



//labelEnd:
//GL_Dialog_Message(gGoalGraphicLibInstance, "End of Transaction", confirmSale , GL_ICON_QUESTION, GL_BUTTON_VALID_CANCEL, 5*1000);

