; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLjz153View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ljz153.h"
LastPage=0

ClassCount=6
Class1=CLjz153App
Class2=CLjz153Doc
Class3=CLjz153View
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_DIALOG_GREY_STATICS
Class6=Dialog_Grey
Resource3=IDR_MAINFRAME
Resource4=IDD_DIALOG1

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
LastObject=CLjz153Doc

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
LastObject=IDT_PIC1
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
Command18=IDM_MOVE
CommandCount=18

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
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

