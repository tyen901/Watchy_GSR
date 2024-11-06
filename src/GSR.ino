#include "Watchy_GSR.h"

#include "Starfield/WatchyStarfield.h"

// Place all of your data and variables here.

// Remember RTC_DATA_ATTR for your variables so they don't get wiped on deep sleep.
RTC_DATA_ATTR uint8_t StarfieldStyle;

class OverrideGSR : public WatchyGSR
{
  /*
   * Keep your functions inside the class, but at the bottom to avoid confusion.
   * Be sure to visit https://github.com/GuruSR/Watchy_GSR/blob/main/Override%20Information.md for full information on how to override
   * including functions that are available to your override to enhance functionality.
   */
public:
  OverrideGSR() : WatchyGSR() {}

  /*
      void InsertPost(){
      };
  */

  /*
      String InsertNTPServer() { return "<your favorite ntp server address>"; }
  */

  /*
      void InsertDefaults(){
      };
  */

  /*
      bool OverrideBitmap(){
        return false;
      };
  */

  /*
      void InsertOnMinute(){
      };
  */
 
  WatchyStarfield StarfieldWatchFace;
/* 
  void InsertWiFi()
  {
  };
*/
/* 
  void InsertWiFiEnding()
  {
  };
*/

  // The next 3 functions allow you to add your own WatchFaces, there are examples that do work below.
  void InsertAddWatchStyles()
  {
    StarfieldStyle = AddWatchStyle("Starfield");
  };

  /*
      void InsertInitWatchStyle(uint8_t StyleID){
        if (StyleID == MyStyle){
            Design.Menu.Top = 72;
            Design.Menu.Header = 25;
            Design.Menu.Data = 66;
            Design.Menu.Gutter = 3;
            Design.Menu.Font = &aAntiCorona12pt7b;
            Design.Menu.FontSmall = &aAntiCorona11pt7b;
            Design.Menu.FontSmaller = &aAntiCorona10pt7b;
            Design.Face.Bitmap = nullptr;
            Design.Face.SleepBitmap = nullptr;
            Design.Face.Gutter = 4;
            Design.Face.Time = 56;
            Design.Face.TimeHeight = 45;
            Design.Face.TimeColor = GxEPD_BLACK;
            Design.Face.TimeFont = &aAntiCorona36pt7b;
            Design.Face.TimeLeft = 0;
            Design.Face.TimeStyle = WatchyGSR::dCENTER;
            Design.Face.Day = 101;
            Design.Face.DayGutter = 4;
            Design.Face.DayColor = GxEPD_BLACK;
            Design.Face.DayFont = &aAntiCorona16pt7b;
            Design.Face.DayFontSmall = &aAntiCorona15pt7b;
            Design.Face.DayFontSmaller = &aAntiCorona14pt7b;
            Design.Face.DayLeft = 0;
            Design.Face.DayStyle = WatchyGSR::dCENTER;
            Design.Face.Date = 143;
            Design.Face.DateGutter = 4;
            Design.Face.DateColor = GxEPD_BLACK;
            Design.Face.DateFont = &aAntiCorona15pt7b;
            Design.Face.DateFontSmall = &aAntiCorona14pt7b;
            Design.Face.DateFontSmaller = &aAntiCorona13pt7b;
            Design.Face.DateLeft = 0;
            Design.Face.DateStyle = WatchyGSR::dCENTER;
            Design.Face.Year = 186;
            Design.Face.YearLeft = 99;
            Design.Face.YearColor = GxEPD_BLACK;
            Design.Face.YearFont = &aAntiCorona16pt7b;
            Design.Face.YearLeft = 0;
            Design.Face.YearStyle = WatchyGSR::dCENTER;
            Design.Status.WIFIx = 5;
            Design.Status.WIFIy = 193;
            Design.Status.BATTx = 155;
            Design.Status.BATTy = 178;
        }
      };
  */


  void InsertDrawWatchStyle(uint8_t StyleID)
  {
    if (StyleID == StarfieldStyle)
    {
      if (SafeToDraw())
      {
        StarfieldWatchFace.drawWatchFace();
      }
    }
  };

  bool InsertHandlePressed(uint8_t SwitchNumber, bool &Haptic, bool &Refresh)
  {
      if (CurrentStyleID() == StarfieldStyle)
      {
        StarfieldWatchFace.handleButtonPress(SwitchNumber);
        Haptic = true;  // Cause Hptic feedback if set to true.
        Refresh = true; // Cause the screen to be refreshed (redrawn).
        return true;    // Respond with "I used a button", so the WatchyGSR knows you actually did something with a button.
      }

      return false;
  };

  /*
      bool OverrideSleepBitmap(){
        return false;
      };
  */
};

// Do not edit anything below this, leave all of your code above.
OverrideGSR watchy;

void setup(){
  watchy.init();
}

void loop() {}
