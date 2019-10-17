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

	//Data
	xmlDoc* File;
	string statusStr;
	string SceneName;
	string ModelName;
	COLLADA_TO_BIN_STATE status;

};

#endif

