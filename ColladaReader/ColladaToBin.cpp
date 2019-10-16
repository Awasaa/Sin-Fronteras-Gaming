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

		StoreVertexPos(File);
		StoreNormals(File);
		StoreUV(File);
		StoreSceneName(File);
		StoreModelName(File);
	}
	else
	{
		statusStr = "Model opening failed";
		status = COLLADA_TO_BIN_STATE::FAILED;
	}
		

}

void
ColladaToBin::StoreVertexPos(xmlDoc* File)
{

}

void
ColladaToBin::StoreNormals(xmlDoc* File)
{

}

void
ColladaToBin::StoreUV(xmlDoc* File)
{

}

void
ColladaToBin::StoreSceneName(xmlDoc* File)
{

}

void
ColladaToBin::StoreModelName(xmlDoc* File)
{

}




