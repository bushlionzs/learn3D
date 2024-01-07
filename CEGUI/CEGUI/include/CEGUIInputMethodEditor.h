
#ifndef _CEGUIInputMethodEditor_h_
#define _CEGUIInputMethodEditor_h_

#include "CEGUIBase.h"


namespace ImeModule
{


void CEGUIEXPORT InitializeImm(unsigned int hWnd);
void CEGUIEXPORT UninitializeImm(void);



bool CEGUIEXPORT ImeMsgProc(unsigned int uMsg, unsigned int wParam, unsigned int lParam );



void CEGUIEXPORT SetActiveIMEEditBox(CEGUI::Window* imeEditBox, bool set);
CEGUIEXPORT CEGUI::Window*	GetActiveIMEEditBox(void);
bool CEGUIEXPORT HasInputFocus(void);
bool CEGUIEXPORT HasForbidInput(void);
bool CEGUIEXPORT HasInCandidate(void);
void CEGUIEXPORT ClearImeStat(void);


unsigned int	CEGUIEXPORT GetCaretBlinkTime(void);


enum IMESTATE { IMEUI_STATE_OFF, IMEUI_STATE_ON, IMEUI_STATE_ENGLISH };

IMESTATE		CEGUIEXPORT GetState(void);
}

#endif