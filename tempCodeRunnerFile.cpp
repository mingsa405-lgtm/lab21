#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* This is where all the input to the window goes to */
HWND textfield;
HWND button;
char ssclassName[]="WindowClass";
HWND textbox1;
HWND textbox2;
HBRUSH hBrush= NULL;// White background

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: 
		hBrush = CreateSolidBrush(RGB(144, 238, 144)); // 
		textbox1=CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,
			20,50,200,25,hwnd,(HMENU)101,NULL,NULL);
		textbox2=CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,
			20,80,200,25,hwnd,(HMENU)102,NULL,NULL);
		textfield=CreateWindow("STATIC","Please input two numbers",WS_CHILD|WS_VISIBLE,
			20,20,200,25,hwnd,NULL,NULL,NULL);
		button =CreateWindow("BUTTON","+",WS_CHILD|WS_VISIBLE|WS_BORDER,
			70,120,25,25,hwnd,(HMENU)1,NULL,NULL);
			button =CreateWindow("BUTTON","-",WS_CHILD|WS_VISIBLE|WS_BORDER,
			100,120,25,25,hwnd,(HMENU)2,NULL,NULL);
			button =CreateWindow("BUTTON","*",WS_CHILD|WS_VISIBLE|WS_BORDER,
			130,120,25,25,hwnd,(HMENU)3,NULL,NULL);
			button =CreateWindow("BUTTON","/",WS_CHILD|WS_VISIBLE|WS_BORDER,
			160,120,25,25,hwnd,(HMENU)4,NULL,NULL);

		break;
		


		case WM_ERASEBKGND:
{
    RECT rc;
    GetClientRect(hwnd, &rc);
    FillRect((HDC)wParam, &rc, hBrush);
    return 1;   // บอกระบบว่าเราวาดเองแล้ว
}
{
   case WM_CTLCOLORSTATIC:
{
    HDC hdc = (HDC)wParam;
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkColor(hdc, RGB(240, 240, 255));
    return (LRESULT)hBrush; 
}
}
		case WM_COMMAND:
		  char str1[100], str2[100], res[100];
    double num1, num2, result;

    GetWindowText(textbox1, str1, 100);
    GetWindowText(textbox2, str2, 100);

    num1 = atof(str1);
    num2 = atof(str2);
		   switch(LOWORD(wParam)){
		       case 1:
						result=num1+num2;
					sprintf(res, "%lf", result);
					MessageBox(hwnd,res,"result",MB_OK);
		           break;
		       case 2:
		          result=num1-num2;
					sprintf(res, "%lf", result);
					MessageBox(hwnd,res,"result",MB_OK);
		           break;
		       case 3:
		          result=num1*num2;
					sprintf(res, "%lf", result);
					MessageBox(hwnd,res,"result",MB_OK);
		           break;
		       case 4:
		          if(num2 == 0) {
		             MessageBox(hwnd,"Error: Division by zero","Error",MB_OK);
		          } else {
		             result=num1/num2;
						sprintf(res, "%lf", result);
						MessageBox(hwnd,res,"result",MB_OK);
		          }
		           break;
		   }

		break;
			/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			DeleteObject(hBrush); // Clean up the brush resource
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = NULL;
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator", WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
		
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
