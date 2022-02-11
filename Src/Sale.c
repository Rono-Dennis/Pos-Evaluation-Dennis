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

#define E_TSCREEN      27										/*!< event number for TSCREEN */
#define TSCREEN       (1 << E_TSCREEN)


// Printer
#define E_PRINTER		  1										/*!< event number for PRINTER */
#define PRINTER			 (1 << E_PRINTER)			/*!< event mask used as parameter for ttestall */

// keyboard
#define E_KEYBOARD		0										/*!< event number for KEYBOARD */
#define KEYBOARD		 (1 << E_KEYBOARD)		/*!< event mask used as parameter for ttestall */
#define _receive_id        1			/*!< parameter for reset_buf : reset in FIFO */
#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}
#define NUMBER_OF_LINES(a) (sizeof(a)/sizeof((a)[0]))
#define PIXEL_BOTTOM   40


static const ST_DSP_LINE txMagnetic[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};

// Properties of the Track screen (Goal)
// =====================================
static const ST_DSP_LINE txTrack[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_RED,   100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_GREEN, 100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line5
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

void IsoError(int iSta, char *pcTrk)
{
	switch (iSta)
	{
		case DEF_SEP: strcpy(pcTrk, "Separator fault");  break;
		case DEF_PAR: strcpy(pcTrk, "Parity fault");     break;
		case DEF_LRC: strcpy(pcTrk, "LRC fault");        break;
		case DEF_LUH: strcpy(pcTrk, "Luhn fault");       break;
		case DEF_NUM: strcpy(pcTrk, "Numerical fault");  break;
		case NO_DATA: strcpy(pcTrk, "No readable data"); break;
		default:      strcpy(pcTrk, "Unknown error");    break;
	}
}



 int Smart()
{
	// Local variables
    // ***************
	T_GL_HWIDGET hScreen=NULL;
	ST_PRN_LINE xLine;
    Telium_File_t *hMag31=NULL, *hMag2=NULL, *hMag3=NULL;
	byte ucLen=0;
    int iSta;
    char tcTmp[128];
    char *pcSrc, *pcDst;
    char tcTrk1[128], tcTrk2[128], tcTrk3[128];
    byte p; // Printer line index
	int iKey, iTimeout=0, iRet;
	char saleMasc[] = "/d/d/d,/d/d/d,/d/d/D";
	char pinMask[] = "/d/d/d/d";
	char currency[10] = "Ksh";
	char pinValue[4 + 1];
	char pinEntry = 0;
	ulong amountResult = 0;

	// Swipe card in progress
	// **********************
	strcpy(tcTrk1, "No readable data");               // By default
	strcpy(tcTrk2, "No readable data");
	strcpy(tcTrk3, "No readable data");


	// Open peripherals
		// ================
		if (IsISO1() == 1)
		{
			hMag31 = Telium_Fopen("SWIPE31", "r*");       // Open mag1 peripheral
			CHECK(hMag31, lblKO);
		}
	    if (IsISO2() == 1)
	    {
	    	hMag2 = Telium_Fopen("SWIPE2", "r*");         // Open mag2 peripheral
	    	CHECK(hMag2, lblKO);
	    }
	    if (IsISO3() == 1)
	    {
	    	hMag3 = Telium_Fopen("SWIPE3", "r*");         // Open mag3 peripheral
	    	CHECK(hMag3, lblKO);
	    }

	    char saleAmount[100];
	    char amountmessage[256];
	    ulong message = 0;
	    int amount = 0;
	    int amount1 = 0;
	    int upamount = 0;
	    int up = 0;
	    int belowAmount = 1;
	    int upAmount = 5001;
	    memset(saleAmount, 0, sizeof saleAmount);
	    memset(pinValue, 0, sizeof pinValue);
	    labelAmount:
	    amountResult = GL_Dialog_Amount(gGoalGraphicLibInstance, "Sale", "Enter Amount", saleMasc, saleAmount, sizeof(saleAmount),currency, GL_ALIGN_BOTTOM_RIGHT, 6* 1000);

	    // Type cast amount to enable validation
	    int Amount = atoi(saleAmount);

	           if(Amount >= 5000 || Amount < 1){
	           message = GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please enter amount less than 5000 or more than 1", GL_ICON_NONE, GL_BUTTON_ALL, 2*1000);
	           if(message == GL_KEY_CANCEL){
	                  goto labelEnd;
	                  }
	                  goto labelAmount;
	                  }


		memset(amountmessage, 0, sizeof amountmessage);
		strcat(amountmessage, saleAmount);
	    GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Please Insert or Swipe Card", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);


	    	// Wait for magnetic card
	    		// ======================
	    	    iRet = TimerStart(0, 30*1000);                                   // Timer0 starts to 30s
	    	    CHECK(iRet>=0, lblKO);
	    		do
	    		{
	    			iSta = Telium_Ttestall(SWIPE31 | SWIPE2 | SWIPE3, 10);       // Wait for the first event SWIPE31
	    			if (iSta != 0)
	    				break;                                                   // Swipe detected
	    			iKey = GoalGetKey(hScreen, gGoalGraphicLibInstance, true, 100, false);         // Get key pressed/touched (shortcut)
	    			CHECK(iKey!=GL_KEY_CANCEL, lblEnd);                          // Exit on cancel key
	    			iTimeout = TimerGet(0);                                      // Retrieve timer value
	    		}while(iTimeout>0);

	    		CHECK(iTimeout!=0, lblEnd);                                      // Exit on timeout

	    		iSta |= Telium_Ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10); // Wait for the second event SWIPE2
	    		iSta |= Telium_Ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10); // Wait for the third event SWIPE3



	    		// Retrieve and analyze ISO1
	    		// =========================
	    		if(iSta & SWIPE31)
	    		{
	    			memset(tcTmp, 0, sizeof(tcTmp));
	    		    memset(tcTrk1, 0, sizeof(tcTrk1));
	    			iRet = Telium_Is_iso1(hMag31, &ucLen, (byte*)tcTmp); // *** Read ISO1 to ascii format ***
	    			if (iRet != ISO_OK)
	    				IsoError (iRet, tcTrk1);
	    			else
	    			{
	    				CHECK(strlen(tcTmp)<128, lblKO);
	    				pcSrc = tcTmp;
	    				pcDst = tcTrk1;
	    				while(*pcSrc) {                                  // Find start sentinel
	    					if(*pcSrc++ == '%')
	    						break;
	    				}
	    				while(*pcSrc) {                                  // Copy all data between start and end sentinels
	    					if(*pcSrc == '?')
	    						break;
	    					*pcDst++ = *pcSrc++;
	    				}
	    			}

	    		}



	    		// Retrieve and analyze ISO2
	    			// =========================
	    			if(iSta & SWIPE2)
	    			{
	    				memset(tcTmp, 0, sizeof(tcTmp));
	    			    memset(tcTrk2, 0, sizeof(tcTrk2));
	    				iRet = Telium_Is_iso2(hMag2, &ucLen, (byte*)tcTmp);  // *** Read ISO2 to ascii format ***
	    				if (iRet != ISO_OK)
	    					IsoError (iRet, tcTrk2);
	    				else
	    				{
	    					CHECK(strlen(tcTmp)<128, lblKO);
	    					pcSrc = tcTmp;
	    					pcDst = tcTrk2;
	    					while(*pcSrc) {                                  // Find start sentinel
	    						if(*pcSrc++ == 'B')
	    							break;
	    					}
	    					while(*pcSrc) {                                  // Copy all data between start and end sentinels
	    						if(*pcSrc == 'F')
	    							break;
	    						if(*pcSrc == 'D')
									//Truncate Data to return Card Number only
									//*pcSrc = '=';
									break;

									*pcDst++ = *pcSrc++;
	    					}
	    				}

	    			}



	    			// Retrieve and analyze ISO3
	    			// =========================
	    			if(iSta & SWIPE3)
	    			{
	    				memset(tcTmp, 0, sizeof(tcTmp));
	    			    memset(tcTrk3, 0, sizeof(tcTrk3));
	    				iRet = Telium_Is_iso3(hMag3, &ucLen, (byte*)tcTmp);  // *** Read ISO3 to ascii format ***
	    				if (iRet != ISO_OK)
	    					IsoError (iRet, tcTrk3);
	    				else
	    				{
	    					CHECK(strlen(tcTmp)<128, lblKO);
	    					pcSrc = tcTmp;
	    					pcDst = tcTrk3;
	    					while(*pcSrc) {                                  // Find start sentinel
	    						if(*pcSrc++ == 'B')
	    							break;
	    					}
	    					while(*pcSrc) {                                  // Copy all data between start and end sentinels
	    						if(*pcSrc == 'F')
	    							break;
	    						if(*pcSrc == 'D')
	    							*pcSrc = '=';
	    						*pcDst++ = *pcSrc++;
	    					}
	    				}
	    			}


	    			if (tcTrk1[0]==0) strcpy(tcTrk1, "Empty");               // Check if track empty
	    			if (tcTrk2[0]==0) strcpy(tcTrk2, "Empty");
	    			if (tcTrk3[0]==0) strcpy(tcTrk3, "Empty");

	    			GoalDestroyScreen(&hScreen);                             // Destroy screen

	    			pinEntry = GL_Dialog_Password(gGoalGraphicLibInstance, NULL, "Enter PIN", pinMask, pinValue, sizeof pinValue, 10 * 1000);


	    			// Display tracks
	    			// ==============
	    			hScreen = GoalCreateScreen(gGoalGraphicLibInstance, txTrack, NUMBER_OF_LINES(txTrack), GL_ENCODING_UTF8);
	    			CHECK(hScreen!=NULL, lblKO);
	    			iRet = GoalClrScreen(hScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	    			CHECK(iRet>=0, lblKO);                                   // Create new screen and clear it

	    			iRet = GoalDspLine(hScreen, 0, "Track 1 :", &txTrack[0], 0, false); // Show part of track1
	    			CHECK(iRet>=0, lblKO);
	    			iRet = GoalDspLine(hScreen, 1, tcTrk1, &txTrack[1], 0, false);
	    			CHECK(iRet>=0, lblKO);
	    			iRet = GoalDspLine(hScreen, 2, "Track 2 :", &txTrack[2], 0, false); // Show part of track2
	    			CHECK(iRet>=0, lblKO);
	    			iRet = GoalDspLine(hScreen, 3, tcTrk2, &txTrack[3], 0, false);
	    			CHECK(iRet>=0, lblKO);
	    			iRet = GoalDspLine(hScreen, 4, "Track 3 :", &txTrack[4], 0, false); // Show part of track3
	    			CHECK(iRet>=0, lblKO);
	    			iRet = GoalDspLine(hScreen, 5, tcTrk3, &txTrack[5], 0, true);
	    			CHECK(iRet>=0, lblKO);



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
					Telium_Sprintf (tcDate, "DATE: %2.2s/%2.2s/20%2.2s   TIME: %2.2s:%2.2s ", xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);


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
					GL_Widget_SetText      (xPrint, tcTrk2);
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
					GL_Widget_SetText      (xPrint, "Sale Amount");
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



	    // Errors treatment
	        // ****************
	    lblKO:                                                       // None-classified low level error

		GL_Dialog_Message(gGoalGraphicLibInstance, NULL, "Processing Complete", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);
 	goto lblEnd;
	    lblEnd:
	    	TimerStop(0);                                            // Stop Timer0
	        if(hMag2)
	    		Telium_Fclose(hMag2);                                // Close mag2 peripheral
	    	if(hMag3)
	    		Telium_Fclose(hMag3);                                // Close mag3 peripheral
	    	if(hMag31)
	    		Telium_Fclose(hMag31);                               // Close mag31 peripheral



	    	labelEnd:
	    	       return 1;
}
