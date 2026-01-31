#include <bits/stdc++.h>
using namespace std;

class ReportData {
public:
    vector<string> getHeaders() {
      vector<string> headers = {"ID", "Name", "Value"};
      return headers;
    }
    
    vector<map<string, string>> getRows() {
      vector<map<string, string>> rows;
      
      map<string, string> row1;
      row1["ID"] = "1";
      row1["Name"] = "Item A";
      row1["Value"] = "100.0";
      rows.push_back(row1);
      
      map<string, string> row2;
      row2["ID"] = "2";
      row2["Name"] = "Item B";
      row2["Value"] = "150.5";
      rows.push_back(row2);
      
      map<string, string> row3;
      row3["ID"] = "3";
      row3["Name"] = "Item C";
      row3["Value"] = "75.25";
      rows.push_back(row3);
      
      return rows;
    }
};

class AbstractReportExporter {
public:
    virtual ~AbstractReportExporter() = default;

    void exportReport(ReportData* data, string filePath) {
      prepareData(data);
      openFile(filePath);
      writeHeader(data);
      writeDataRows(data);
      writeFooter(data);
      closeFile(filePath);
      cout << "Export complete: " << filePath << endl;
    }

protected:
    virtual void prepareData(ReportData* data) {
      cout << "Preparing report data (common step)..." << endl;
    }
    
    virtual void openFile(string filePath) {
      cout << "Opening file '" << filePath << endl;
    }
    
    virtual void writeHeader(ReportData* data) = 0;
    
    virtual void writeDataRows(ReportData* data) = 0;
    
    virtual void writeFooter(ReportData* data) {
      cout << "Writing footer (default: no footer)." << endl;
    }
    
    virtual void closeFile(string filePath) {
      cout << "Closing file '" << filePath << endl;
    }
};  

class CsvReportExporter : public AbstractReportExporter {
protected:
    // prepareData() not overridden - default will be used
    // OpenFile() not overridden - default will be used

    void writeHeader(ReportData* data) override {
      vector<string> headers = data->getHeaders();
      string headerLine = "CSV: Writing header: ";
      for (int i = 0; i < headers.size(); i++) {
          headerLine += headers[i];
          if (i < headers.size() - 1) {
              headerLine += ",";
          }
      }
      cout << headerLine << endl;
    }
    
    void writeDataRows(ReportData* data) override {
      cout << "CSV: Writing data rows..." << endl;
      vector<map<string, string>> rows = data->getRows();
      for (const auto& row : rows) {
          cout << "CSV: ";
          for (const auto& pair : row) {
              cout << pair.second << " ";
          }
          cout << endl;
      }
    }

    // writeFooter() not overridden - default will be used
    // closeFile() not overridden - default will be used    
};

class PdfReportExporter : public AbstractReportExporter {
protected:
    // prepareData() not overridden - default will be used
    // penFile() not overridden - default will be used

    void writeHeader(ReportData* data) override {
      vector<string> headers = data->getHeaders();
      string headerLine = "PDF: Writing header: ";
      for (int i = 0; i < headers.size(); i++) {
          headerLine += headers[i];
          if (i < headers.size() - 1) {
              headerLine += ",";
          }
      }
      cout << headerLine << endl;
    }
    
    void writeDataRows(ReportData* data) override {
      cout << "PDF: Writing data rows..." << endl;
      vector<map<string, string>> rows = data->getRows();
      for (const auto& row : rows) {
          cout << "PDF: ";
          for (const auto& pair : row) {
              cout << pair.second << " ";
          }
          cout << endl;
      }      
    }

    // writeFooter() not overridden - default will be used
    // closeFile() not overridden - default will be used    
};


int main() {
    ReportData* data = new ReportData();

    AbstractReportExporter* csvExporter = new CsvReportExporter();
    csvExporter->exportReport(data, "sales_report");

    cout << endl;

    AbstractReportExporter* pdfExporter = new PdfReportExporter();
    pdfExporter->exportReport(data, "financial_summary");

    delete data;
    delete csvExporter;
    delete pdfExporter;

    return 0;
}