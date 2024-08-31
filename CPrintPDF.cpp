#include <afxwin.h>
#include <afxext.h>
#include <fpdfview.h> // Include PDFium header

class CPrintPDFApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

class CPrintPDFDlg : public CDialogEx
{
public:
    CPrintPDFDlg() : CDialogEx(IDD_PRINTPDF_DIALOG) {}

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedPrint();
};

BEGIN_MESSAGE_MAP(CPrintPDFDlg, CDialogEx)
    ON_BN_CLICKED(IDC_PRINT_BUTTON, &CPrintPDFDlg::OnBnClickedPrint)
END_MESSAGE_MAP()

BOOL CPrintPDFApp::InitInstance()
{
    CWinApp::InitInstance();

    // Initialize PDFium
    FPDF_InitLibrary();

    CPrintPDFDlg dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();

    // Cleanup PDFium
    FPDF_DestroyLibrary();

    return FALSE;
}

void CPrintPDFDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CPrintPDFDlg::OnBnClickedPrint()
{
    CFileDialog fileDlg(TRUE, _T("pdf"), NULL, OFN_FILEMUSTEXIST, _T("PDF Files (*.pdf)|*.pdf||"));
    if (fileDlg.DoModal() == IDOK)
    {
        CString filePath = fileDlg.GetPathName();

        // Load the PDF document
        FPDF_DOCUMENT document = FPDF_LoadDocument((LPCTSTR)filePath, nullptr);
        if (document)
        {
            // For simplicity, we're not implementing actual printing here
            AfxMessageBox(_T("Loaded PDF file: ") + filePath);

            // Clean up
            FPDF_CloseDocument(document);
        }
        else
        {
            AfxMessageBox(_T("Failed to load PDF file."));
        }
    }
}

CPrintPDFApp theApp;
