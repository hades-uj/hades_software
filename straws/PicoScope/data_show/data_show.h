 
#include <TQObject.h>
#include <RQ_OBJECT.h>
class TGWindow;
class TGMainFrame;
class TRootEmbeddedCanvas;
class MyMainFrame {
RQ_OBJECT("MyMainFrame")
private:
TGMainFrame *fMain;
TRootEmbeddedCanvas *fEcanvas;
unsigned short i_r1_min;
unsigned short i_c1_min;
unsigned short i_r2_min;
unsigned short i_c2_min;

unsigned short i_r1_max;
unsigned short i_c1_max;
unsigned short i_r2_max;
unsigned short i_c2_max;

unsigned short dic_number;

unsigned short operation_mode_flag;

	
public:
MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
virtual ~MyMainFrame();
void DoDraw();
};
