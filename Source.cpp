#include <windows.h>
#include "resource.h"   //Librerias, hehe.
#include <CommCtrl.h>

HWND ghDlg = 0;

HBITMAP BACKGROUND; //Instancia de la imagen
HWND Imagen; //Identificador de la imagen
HWND h_Us; //Identificador del edit con el usuario
HINSTANCE hInstance; //Instancia de la ventana de registro
HMENU h_Menu; //Identificador de la ventana de registro
HINSTANCE hInstGlobal; //Instancia global


struct usuario {
    usuario* ant;
   
    char nomUsu[30];
    char nomCompleto[50];
    char contra[30];
    char foto[300];
    int piso;
    usuario* sig;
};

usuario* aux, * inicio, * miUsu = nullptr;
char zFile[MAX_PATH];

int x = 0;
int y = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_Registro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_Menu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_AltaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_BajaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ActuaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ListaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_AltaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_BajaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ActuaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ListaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_AltaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_BajaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ActuaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ListaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_AltaConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Ventana_ListaConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    ghDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)WindowProc);
    ShowWindow(ghDlg, nCmdShow);
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG)); //Limpiar variable 
    while (GetMessage(&msg, 0, 0, 0))
    {
        if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:

    case WM_INITDIALOG:
        BACKGROUND = (HBITMAP)LoadImage(NULL, "SignUpBG.bmp", IMAGE_BITMAP, 177, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, 1001, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BACKGROUND);

 

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_RegistrarNewUser:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_Register), NULL, Ventana_Registro);
            break;

            case IDOK:
                char nomUsu[30];
                char contra[30];
                GetDlgItemText(hwnd, ID_eNomUser, nomUsu, sizeof(nomUsu));
                GetDlgItemText(hwnd, ID_ePassUser, contra, sizeof(contra));
                aux = inicio;

                DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG3), NULL, Ventana_Menu);

                break;

                if (inicio == nullptr) {
                    MessageBox(hwnd, "No hay usuario registrados.", "ERROR", MB_OK | MB_ICONERROR);
                }
                else {
                    while (aux != nullptr && strcmp(aux->nomUsu, nomUsu) != 0) {
                        aux = aux->sig;
                    }
                    if (aux == nullptr) {
                        MessageBox(hwnd, "Usuario no encontrado", "ADVERTENCIA", MB_OK | MB_ICONWARNING);
                    }
                    else {
                        if (strcmp(aux->contra, contra) == 0) {
                            miUsu = aux;
                            EndDialog(hwnd, 0);
                             
                        }
                        else {
                            MessageBox(hwnd, "Contraseña incorrecta", "ADVERTENCIA", MB_OK | MB_ICONWARNING);
                        }
                    }
                }

        break;

                MessageBox(NULL, "", (LPCSTR)"Advertencia", MB_ICONWARNING);

               
               break;

        case Salir_Bot:
    
            if (MessageBox(hwnd, "¿Seguro que desea salir?", "ADVERTENCIA", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            }
         
        break;
        }

      break;

       /* case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;*/

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        }

        return FALSE;
    }
   
LRESULT CALLBACK Ventana_Registro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:

    case WM_INITDIALOG:
        h_Menu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
        SetMenu(hwnd, h_Menu);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDc_BackRegister:
            DestroyWindow(hwnd);
            break;
        case IDC_AceptarRegistro:
            int opc = MessageBox(hwnd, "Datos registrados correctamente ¿Desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
            if (opc == IDYES)
                DestroyWindow(hwnd);
            break;
        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_Menu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:HMENU hmenu;
    case WM_INITDIALOG:
        hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
        SetMenu(hwnd, hmenu);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_AltaAdmin), NULL, Ventana_AltaAdmin);
            break;
        case IDC_BUTTON2:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG5), NULL, Ventana_BajaAdmin);
            break;
        case IDC_BUTTON3:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG6), NULL, Ventana_ActuaAdmin);
            break;
        case IDC_BUTTON4:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG7), NULL, Ventana_ListaAdmin);
            break;
        case IDC_BUTTON5:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG8), NULL, Ventana_AltaCliente);
            break;
        case IDC_BUTTON6:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG9), NULL, Ventana_BajaCliente);
            break;
        case IDC_BUTTON7:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG10), NULL, Ventana_ActuaCliente);
            break;
        case IDC_BUTTON8:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG11), NULL, Ventana_ListaCliente);
            break;
        case IDC_BUTTON9:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG12), NULL, Ventana_AltaPromo);
            break;
        case IDC_BUTTON10:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG13), NULL, Ventana_BajaPromo);
            break;
        case IDC_BUTTON11:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG14), NULL, Ventana_ActuaPromo);
            break;
        case IDC_BUTTON12:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG15), NULL, Ventana_ListaPromo);
            break;
        case IDC_BUTTON13:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG16), NULL, Ventana_AltaConsumo);
            break;
        case IDC_BUTTON14:
            DialogBox(hInstGlobal, MAKEINTRESOURCE(IDD_DIALOG17), NULL, Ventana_ListaConsumo);
            break;
        case ID_Exit:
            int opc = MessageBox(hwnd, "¿Desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
            if (opc == IDYES)
                DestroyWindow(hwnd);
            break;
        }
        break;
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);
        break;
    }
    return 0;
}

LRESULT CALLBACK Ventana_AltaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_SalirAltaAd:
            DestroyWindow(hwnd);
            break;

        case ID_RegistrarAdmin:
            MessageBox(hwnd, "Alta realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;
        }
        break;

    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_BajaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_OkDeleteAdmin:
            MessageBox(hwnd, "Baja realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);

            break;

        }
      /*  break;*/
    case 1038:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);
      

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ActuaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_Update:
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ListaAdmin(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ExitAdList:
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_AltaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_RegCliente:MessageBox(hwnd, "Alta realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;
            case ID_ExitRegCliente:
                DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_BajaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_AceptarDCliente:
            DestroyWindow(hwnd);
            break;
        case ID_ExitD_Cliente:
            MessageBox(hwnd, "Baja realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;
        }
        break;


    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ActuaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ActCliente:
            DestroyWindow(hwnd);
            break;
        case ID_ExitActCliente: MessageBox(hwnd, "Actulizacion realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;
          

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ListaCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ExitListClient:
            DestroyWindow(hwnd);
            break;

        }
        break;


    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_AltaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_RegPromo: DestroyWindow(hwnd);
            break;
        case ID_ExitAltaProm:MessageBox(hwnd, "Alta realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_BajaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BajaProm:
            DestroyWindow(hwnd);
            break;
        case ID_ExitBajaPromo:
            MessageBox(hwnd, "Baja realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ActuaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ActPromo:  DestroyWindow(hwnd);
            break;
        case ID_ExitActPromo: MessageBox(hwnd, "Actualizacion realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ListaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_PromoList:  DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_AltaConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_SiAltaConsum:DestroyWindow(hwnd);
            break;
        case ID_ExitConsum:MessageBox(hwnd, "Alta realizada", "AVISO", MB_ICONQUESTION);
            DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}

LRESULT CALLBACK Ventana_ListaConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ExitListCon:DestroyWindow(hwnd);
            break;

        }
        break;
    case WM_CLOSE:
        int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
        if (opc == IDYES)
            DestroyWindow(hwnd);

        break;

    }
    return 0;
}