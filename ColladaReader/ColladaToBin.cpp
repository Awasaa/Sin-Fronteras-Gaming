#include "ColladaToBin.h"

ColladaToBin::ColladaToBin(const char *FileName)
{
	File = nullptr;
	statusStr = "Model initialized";
	status = COLLADA_TO_BIN_STATE::INICIALIZATED;
	AdminFile(FileName);
}

ColladaToBin::ColladaToBin(string &FileName)
{
	File = nullptr;
	statusStr = "Model initialized";
	status = COLLADA_TO_BIN_STATE::INICIALIZATED;
	AdminFile(FileName.c_str());
}

ColladaToBin::~ColladaToBin()
{
	xmlFreeDoc(File);
	xmlCleanupParser();
}

bool
ColladaToBin::isOpened(void)
{
	bool ReturnValue;


	if (status != COLLADA_TO_BIN_STATE::FAILED)
	{
		ReturnValue = true;
	}
	else
	{
		ReturnValue = false;
	}

	return ReturnValue;
}

void
ColladaToBin::AdminFile(const char *FileName)
{
	File = xmlReadFile(FileName, nullptr, 0);

	if (File != nullptr)
	{
		statusStr = "Model has been opened succesfully";
		status = COLLADA_TO_BIN_STATE::OPEN;

		StoreVertexPos();
		StoreNormals();
		StoreUV();
		StoreSceneName();
		StoreModelName();
	}
	else
	{
		statusStr = "Model opening failed";
		status = COLLADA_TO_BIN_STATE::FAILED;
	}


}

void
ColladaToBin::StoreVertexPos()
{
	xmlNode* Node = nullptr;
	Node = xmlDocGetRootElement(File)->children;
	string str = "library_geometries";

	//while (((const char *)(Node->name)) != str)
	//{
	//	cout << Node->name << endl;
	//	Node = Node->next;
	//}

	for ( ; Node && (((const char *)(Node->name)) != str); Node = Node->next) {}

	if (Node)
	{
		xmlNode* Node1 = Node->children;
		string str1 = "geometry";
		for (; Node1 && (((const char *)(Node1->name)) != str1); Node1 = Node1->next) {}

		if (Node1)
			cout << Node1->name;
	}
	else
		cout << "Corrupted XML" << endl;

}

void
ColladaToBin::StoreNormals()
{

}

void
ColladaToBin::StoreUV()
{

}

void
ColladaToBin::StoreSceneName()
{

}

void
ColladaToBin::StoreModelName()
{

}




