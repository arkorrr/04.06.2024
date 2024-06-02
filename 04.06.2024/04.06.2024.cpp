#include<windows.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class IDocument
{
public:
	virtual void DocumentOpen(ifstream& infile) abstract;
	virtual void DocumentClose(ofstream& outfile) abstract;
};

class RealDocument : public IDocument
{
	RealDocument()
	{
		cout << "Create object Math. Wait...\n";
		Sleep(3000);
	}

	void DocumentOpen(ifstream& infile) override
	{
		if (infile.is_open())
			cout << "Document is open" << endl;
	}
	void DocumentClose(ofstream& outfile) override
	{
		if (!outfile.is_open())
			cout << "Document is close" << endl;
	}
};

class DocumentProxy : public IDocument
{
	RealDocument* realDocument;
public:
	DocumentProxy()
	{
		realDocument = nullptr;
	}
	~DocumentProxy()
	{
		delete realDocument;
	}
	void DocumentOpen(ifstream& infile) override
	{
		if (infile.is_open())
			cout << "Document is open" << endl;
	}
	void DocumentClose(ofstream& outfile) override
	{
		if (!outfile.is_open())
			cout << "Document is close" << endl;
	}
};

void client(IDocument* p, ofstream& outfile, ifstream& infile)  // сюда "приходит" либо заместитель, либо сам субъект
{
	p->DocumentOpen(infile);
	p->DocumentClose(outfile);

}

int main()
{
	IDocument* p = new DocumentProxy();
	ifstream file("Text.txt");     
	ofstream file1("Text.txt");
	client(p,file1,file);

}
