#include "ColladaToBin.h"

ColladaToBin::ColladaToBin(const char *FileName)
{
	File = nullptr;
	Node = nullptr;
	ReturnNode = nullptr;
	statusStr = "Model initialized";
	status = COLLADA_TO_BIN_STATE::INICIALIZATED;
	AdminFile(FileName);
}

ColladaToBin::ColladaToBin(string &FileName)
{
	File = nullptr;
	Node = nullptr;
	ReturnNode = nullptr;
	statusStr = "Model initialized";
	status = COLLADA_TO_BIN_STATE::INICIALIZATED;
	AdminFile(FileName.c_str());
}

ColladaToBin::~ColladaToBin()
{
	xmlUnlinkNode(Node);
	xmlFreeNode(Node);
	xmlUnlinkNode(ReturnNode);
	xmlFreeNode(ReturnNode);
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
	 Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> DataPath = { "library_geometries","1","geometry","1","mesh","1","source","1","float_array" ,"1" };

	if (Node = SearchAdmin(DataPath, Node))
	{
		cout << "Vertex: \n" << Node->content << endl;
	}

}

void
ColladaToBin::StoreNormals()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> DataPath = { "library_geometries","1","geometry","1","mesh","1","source","2","float_array" ,"1" };

	if (Node = SearchAdmin(DataPath, Node))
	{
		cout << "Normals: \n" << Node->content << endl;
	}

}

void
ColladaToBin::StoreUV()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> DataPath = { "library_geometries","1","geometry","1","mesh","1","source","3","float_array" ,"1" };

	if (Node = SearchAdmin(DataPath, Node))
	{
		cout << "UV: \n" << Node->content << endl;
	}

}

void
ColladaToBin::StoreSceneName()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> DataPath = { "library_visual_scenes","1","visual_scene","1" };
	string AtributteName = "name";

	if (Node = SearchAdmin(DataPath, Node))
	{
		xmlChar * str = xmlGetProp(Node->parent, (xmlChar*)"name");

		if (str)
		{
			cout << "Scene Name: " << str << endl;;
			xmlFree(str);
		}

	}

}

void
ColladaToBin::StoreModelName()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> DataPath = { "library_visual_scenes","1","visual_scene","1","node","1"};
	string AtributteName = "name";

	if (Node = SearchAdmin(DataPath, Node))
	{
		xmlChar * str = xmlGetProp(Node->parent, (xmlChar*)"name");

		if (str)
		{
			cout << "Model Name: " << str << endl;
		}
		else
		{
			statusStr = "Corrupted XML or invalid atributte";
			status = COLLADA_TO_BIN_STATE::FAILED;
		}

		xmlFree(str);
	}

}

xmlNode*
ColladaToBin::SearchAdmin(vector<string> DataPath, xmlNode* Node)
{
	size_t i = 0;

	do
	{
		Node = FindNode(DataPath[i],atoi(DataPath[i+1].c_str()),Node);
		if (Node)
		{
			Node = Node->children;
		}
		i += 2;
	} while (Node && i < DataPath.size());

	return Node;
}

xmlNode*
ColladaToBin::FindNode(string NodeName, int NodeNamedValid, xmlNode* TreeNode)
{
	ReturnNode = nullptr;
	bool Continue = true;
	int i = 1;

	while (TreeNode && Continue)
	{
		if ((const char *)(TreeNode->name) == NodeName)
		{
			if (NodeNamedValid == i)
			{
				Continue = false;
			}
			else
			{
				i++;
			}
		}

		if (Continue)
		{
			TreeNode = TreeNode->next;
		}
	}

	if (TreeNode)
	{
		ReturnNode = TreeNode;
	}
	else
	{
		statusStr = "Corrupted XML or invalid element";
		status = COLLADA_TO_BIN_STATE::FAILED;
	}

	return ReturnNode;
}

/*
string
ColladaToBin::FindAttribute(string AttributeName, xmlNode* TreeNode)
{
	xmlAttr* attribute = TreeNode->properties;
	string ReturnStr;
	bool AtributteFinded = false;

	while (attribute)
	{
		if ((const char *)attribute->name == AttributeName)
		{
			ReturnStr = (const char *)attribute->doc;
			bool AtributteFinded = true;
		}
		
		attribute = attribute->next;
	}

	if (!AtributteFinded)
	{
		statusStr = "Corrupted XML or invalid atributte";
		status = COLLADA_TO_BIN_STATE::FAILED;
	}

	return ReturnStr;
}

*/


