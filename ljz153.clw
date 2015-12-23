; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLjz153View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ljz153.h"
LastPage=0

ClassCount=9
Class1=CLjz153App
Class2=CLjz153Doc
Class3=CLjz153View
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=Dialog_Grey
Resource3=IDD_DIALOG_LOW
Class7=MoveDlg
Resource4=IDD_DIALOG1
Class8=Dlg_Low
Resource5=IDD_DIALOG_GREY_STATICS
Class9=Dlg_High
Resource6=IDD_DIALOG_HIGH

[CLS:CLjz153App]
Type=0
HeaderFile=ljz153.h
ImplementationFile=ljz153.cpp
Filter=N

[CLS:CLjz153Doc]
Type=0
HeaderFile=ljz153Doc.h
ImplementationFile=ljz153Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=IDT_PIC2

[CLS:CLjz153View]
Type=0
HeaderFile=ljz153View.h
ImplementationFile=ljz153View.cpp
Filter=C
LastObject=CLjz153View
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_EQUAL
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ljz153.cpp
ImplementationFile=ljz153.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_GREY_STATIS
Command18=IDM_LINE
Command19=IDM_EQUAL
Command20=IDM_MOVE
Command21=IDM_FT
Command22=IDM_IFT
Command23=IDM_FFT
Command24=IDM_IFFT
Command25=ID_AVERAGE_FILTER
Command26=ID_MEDIAN_FILTER
Command27=ID_GRAD_SHARP
Command28=ID_RAPLAS_SHARP
Command29=IDM_LOW
Command30=IDM_HIGH
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_GREY
Command10=IDT_PIC1
Command11=IDT_PIC2
CommandCount=11

[DLG:IDD_DIALOG_GREY_STATICS]
Type=1
Class=Dialog_Grey
ControlCount=0

[CLS:Dialog_Grey]
Type=0
HeaderFile=Dialog_Grey.h
ImplementationFile=Dialog_Grey.cpp
BaseClass=CDialog
Filter=D
LastObject=Dialog_Grey
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=MoveDlg
ControlCount=7
Control1=IDOKMOVE,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_MOVE_X,edit,1350631552
Control4=IDC_EDIT_MOVE_Y,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:MoveDlg]
Type=0
HeaderFile=MoveDlg.h
ImplementationFile=MoveDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_DIALOG_LOW]
Type=1
Class=Dlg_Low
ControlCount=3
Control1=IDOK2,button,1342242817
Control2=IDC_STATIC_LOW,static,1342308352
Control3=IDC_EDIT_LOW,edit,1350631552

[CLS:Dlg_Low]
Type=0
HeaderFile=Dlg_Low.h
ImplementationFile=Dlg_Low.cpp
BaseClass=CDialog
Filter=D
LastObject=Dlg_Low
VirtualFilter=dWC

[DLG:IDD_DIALOG_HIGH]
Type=1
Class=Dlg_High
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_HIGH,static,1342308352
Control3=IDC_EDIT_HIGH,edit,1350631552

[CLS:Dlg_High]
Type=0
HeaderFile=Dlg_High.h
ImplementationFile=Dlg_High.cpp
BaseClass=CDialog
Filter=D
LastObject=Dlg_High
VirtualFilter=dWC

