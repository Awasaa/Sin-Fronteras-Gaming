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
	//xmlUnlinkNode(Node);
	//xmlUnlinkNode(ReturnNode);
	//xmlFreeNode(ReturnNode);
	//xmlFreeNode(Node);
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

	vector<string> VertexPath = { "library_geometries","1","geometry","1","mesh","1","source","1","float_array" ,"1" };
	vector<string> VertexConfigPath = { "technique_common","1","accessor","1"};

	if (Node = SearchAdmin(VertexPath, Node))
	{
		VertexStr = (const char *)(Node->children->content);
		cout << "Vertex: \n" << VertexStr << endl;
		if (Node = SearchAdmin(VertexConfigPath, Node))
		{
			cout << "Vertex count: " << FindAttribute("count", Node) << endl;
			cout << "Vertex div: " << FindAttribute("stride", Node) << endl;
		}
	}
}

void
ColladaToBin::StoreNormals()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> NormalsPath = { "library_geometries","1","geometry","1","mesh","1","source","2","float_array" ,"1" };
	vector<string> NormalsConfigPath = { "technique_common","1","accessor","1" };

	if (Node = SearchAdmin(NormalsPath, Node))
	{
		NormalsStr = (const char *)(Node->children->content);
		cout << "Normals: \n" << NormalsStr << endl;
		if (Node = SearchAdmin(NormalsConfigPath, Node))
		{
			cout << "Normals count: " << FindAttribute("count", Node) << endl;
			cout << "Normals div: " << FindAttribute("stride", Node) << endl;
		}

	}

}

void
ColladaToBin::StoreUV()
{
	Node = xmlDocGetRootElement(File)->children; //Acces first COLLADA큦 child (asset Node)

	vector<string> UVPath = { "library_geometries","1","geometry","1","mesh","1","source","3","float_array" ,"1" };
	vector<string> UVConfigPath = { "technique_common","1","accessor","1" };

	if (Node = SearchAdmin(UVPath, Node))
	{
		UVstr = (const char *)(Node->children->content);
		cout << "UV: \n" << UVstr << endl;
		if (Node = SearchAdmin(UVConfigPath, Node))
		{
			cout << "UV points count: " << FindAttribute("count", Node) << endl;
			cout << "UV div: " << FindAttribute("stride", Node) << endl;
		}
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
		SceneName = FindAttribute(AtributteName, Node);
		
		if (!SceneName.empty())
		{
			cout << "Scene Name:" << SceneName << endl;
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
		ModelName = FindAttribute(AtributteName, Node);

		if (!SceneName.empty())
		{
			cout << "Model Name:" << ModelName << endl;
		}
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

	return Node->parent;
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


string
ColladaToBin::FindAttribute(string AttributeName, xmlNode* TreeNode)
{
	xmlChar * str = nullptr;
	string ReturnStr;

	str = xmlGetProp(TreeNode, (xmlChar*)AttributeName.c_str());
	

	if (str)
	{
		ReturnStr = (const char *)str;
	}
	else
	{
		statusStr = "Corrupted XML or invalid atributte";
		status = COLLADA_TO_BIN_STATE::FAILED;
	}

	xmlFree(str);

	return ReturnStr;
}




