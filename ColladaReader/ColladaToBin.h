#ifndef COLLADATOBIN_H
#define COLLADATOBIN_H

extern "C"
{
	#include "parser.h"
	#include "tree.h"
}

#include <iostream>
#include <string>
#include <vector>

enum class COLLADA_TO_BIN_STATE { INICIALIZATED , OPEN, FAILED};

using namespace std;

class ColladaToBin
{

public:
	//Constructors
	ColladaToBin(const char* FileName);
	ColladaToBin(string& FileName);

	//Destructor
	~ColladaToBin();

	//Getters
	string& getStatus(void) { return statusStr; }
	string& getModelName(void) { return ModelName; }
	string& getSceneName(void) { return SceneName; }
	string& getVertexStr(void) { return VertexStr; }
	string& getNormalsStr(void) { return NormalsStr; }
	string& getUVstr(void) { return UVstr; }

	//Method
	bool isOpened(void);

private:

	//Private methods
	void AdminFile(const char *FileName);
	void StoreVertexPos();
	void StoreNormals();
	void StoreUV();
	void StoreSceneName();
	void StoreModelName();
	xmlNode* SearchAdmin(vector<string> DataPath, xmlNode* FirstNode);
	xmlNode* FindNode(string NodeName, int NodeNamedValid, xmlNode* TreeNode);
	string FindAttribute(string AttributeName, xmlNode* TreeNode);

	//Data
	xmlDoc* File;		//XML file
	xmlNode* Node;		//Multiprupose Node
	xmlNode* ReturnNode;	//Use to return Node pointer
		
	string SceneName;
	string ModelName;
	string VertexStr;
	string NormalsStr;
	string UVstr;


	string statusStr;
	COLLADA_TO_BIN_STATE status;

};

#endif

