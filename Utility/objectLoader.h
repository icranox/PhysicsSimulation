//Basic object loader

#include<iostream>
#include<fstream>

typedef struct vertexPoint_s {
	float x;
	float y;
	float z;
} vertexPoint_t;

typedef struct vertexUV_s {
	float u;
	float v;
} vertexUV_t;


class ObjectLoader {
public:
	ObjectLoader();
	~ObjectLoader();
	void Init();
	void Load(char *filename);
	//GLdouble * GetVertexArray();
	//GLdouble * GetNormalVertexArray();
	//GLdouble * GetTextureVertexArray();
	//GLdouble * GetTriangeArray();
	
	float *triangleArray;
	float *textureTriangleArray;
	float *normalTriangleArray;
private:
	vertexPoint_t *vertexArray;
	vertexPoint_t *normalVertexArray;
	vertexUV_t *textureVertexArray;

	long nTriangle;
	long nNormalTriangle;
	long nTextureTriangle;
	long nVertex;
	long nNormalVertex;
	long nTextureVertex;
};


ObjectLoader::ObjectLoader()
{
	Init();
}

ObjectLoader::~ObjectLoader()
{
	delete[]vertexArray;
	delete[]normalVertexArray;
	delete[]textureVertexArray;
	delete[]triangleArray;
	delete[]normalTriangleArray;
	delete[]textureTriangleArray;
}

void ObjectLoader::Init()
{
	nTriangle=0;
	nNormalTriangle=0;
	nTextureTriangle=0;
	nVertex=0;
	nNormalVertex=0;
	nTextureVertex=0;
}

void ObjectLoader::Load(char *filename)
{
	Init();
	std::ifstream inputFile;
	std::ifstream inputFile1;


	inputFile.open(filename, std::ios::in);
	char type[128];
	
	vertexPoint_t vertex;
	vertexUV_t textureVertex;
	textureVertex.u=0;
	textureVertex.v=0;
	vertex.x=0;
	vertex.y=0;
	vertex.z=0;
	float v1=0;
	float v2=0;
	float v3=0;
	//vertexPoint_t normalVertex;
	//vertexPoint_t textureVertex;
	while (!inputFile.eof())
	{
		char data[128];
		type[0]=' ';
	//	if ()
	//	{
	//		break;
	//	}
		inputFile.getline(data, 128);
		sscanf(data, "%s", &type);
		if (strcmp(type, "v")==0)
		{
			nVertex++;
		}
		else if (strcmp(type, "vn")==0)
		{
			nNormalVertex++;
		}
		else if (strcmp(type, "vt")==0)
		{
			nTextureVertex++;
		}
		else if (strcmp(type, "f\0")==0)
		{
			nTriangle++;
		}
	}

	inputFile.close();

	inputFile.open(filename, std::ios::in);
	vertexArray=new vertexPoint_t[nVertex+1];
	normalVertexArray=new vertexPoint_t[nNormalVertex+1];
	textureVertexArray=new vertexUV_t[nTextureVertex+1];
	triangleArray=new float[nTriangle*3*3]; //number of triangles, 3 verticies per triangle, 3 coordinates per vertex
	normalTriangleArray=new float[nTriangle*3*3]; //number of triangles, 3 verticies per triangle, 3 coordinates per vertex
	textureTriangleArray=new float[nTriangle*3*2]; //number of triangles, 3 verticies per triangle, 2 coordinates per vertex

	Init();

	int nVertex1=0;
	int nVertex2=0;
	int nVertex3=0;

	int nNormalVertex1=0;
	int nNormalVertex2=0;
	int nNormalVertex3=0;

	int nTextureVertex1=0;
	int nTextureVertex2=0;
	int nTextureVertex3=0;

	while (!inputFile.eof())
	{
		char data[128];
		
	//	if (inputFile.eof())
	//	{
	//		break;
	//	}
		inputFile.getline(data, 128);
		if (sscanf(data, "%s %f %f %f/n", &type, &vertex.x, &vertex.y, &vertex.z)==4)
//		if (sscanf(data, "%s %f %f %f/n", &type, &v1, &v2, &v3)==4)
		{
			if (strcmp(type, "v")==0)
			{
				vertexArray[nVertex].x=vertex.x;
				vertexArray[nVertex].y=vertex.y;
				vertexArray[nVertex].z=vertex.z;
				nVertex++;
			}
			else if (strcmp(type, "vn")==0)
			{
				normalVertexArray[nNormalVertex].x=vertex.x;
				normalVertexArray[nNormalVertex].y=vertex.y;
				normalVertexArray[nNormalVertex].z=vertex.z;
				nNormalVertex++;
			}
		}
		else if (sscanf(data, "%s %f %f/n", &type, &textureVertex.u, &textureVertex.v)==3)
		{
			if (strcmp(type, "vt")==0)
			{
				textureVertexArray[nTextureVertex].u=textureVertex.u;
				textureVertexArray[nTextureVertex].v=textureVertex.v;
				nTextureVertex++;
			}
		}
		else if(sscanf(data, "%s %d//%d %d//%d %d//%d/n", &type, &nVertex1, &nNormalVertex1, &nVertex2, &nNormalVertex2, &nVertex3, &nNormalVertex3)==7)
		{
			
			if (strcmp(type, "f")==0)
			{
				triangleArray[nTriangle*9+0]=vertexArray[nVertex1-1].x;
				triangleArray[nTriangle*9+1]=vertexArray[nVertex1-1].y;
				triangleArray[nTriangle*9+2]=vertexArray[nVertex1-1].z;

				triangleArray[nTriangle*9+3]=vertexArray[nVertex2-1].x;
				triangleArray[nTriangle*9+4]=vertexArray[nVertex2-1].y;
				triangleArray[nTriangle*9+5]=vertexArray[nVertex2-1].z;

				triangleArray[nTriangle*9+6]=vertexArray[nVertex3-1].x;
				triangleArray[nTriangle*9+7]=vertexArray[nVertex3-1].y;
				triangleArray[nTriangle*9+8]=vertexArray[nVertex3-1].z;
				

				normalTriangleArray[nTriangle*9+0]=vertexArray[nNormalVertex1-1].x;
				normalTriangleArray[nTriangle*9+1]=vertexArray[nNormalVertex1-1].y;
				normalTriangleArray[nTriangle*9+2]=vertexArray[nNormalVertex1-1].z;

				normalTriangleArray[nTriangle*9+3]=vertexArray[nNormalVertex2-1].x;
				normalTriangleArray[nTriangle*9+4]=vertexArray[nNormalVertex2-1].y;
				normalTriangleArray[nTriangle*9+5]=vertexArray[nNormalVertex2-1].z;

				normalTriangleArray[nTriangle*9+6]=vertexArray[nNormalVertex3-1].x;
				normalTriangleArray[nTriangle*9+7]=vertexArray[nNormalVertex3-1].y;
				normalTriangleArray[nTriangle*9+8]=vertexArray[nNormalVertex3-1].z;
				
				nTriangle++;
				
			}
		}
		else if(sscanf(data, "%s %d/%d/%d %d/%d/%d %d/%d/%d/n", &type, &nVertex1, &nTextureVertex1, &nNormalVertex1, &nVertex2, &nTextureVertex2, &nNormalVertex2, &nVertex3, &nTextureVertex3, &nNormalVertex3)==10)
		{
			if (strcmp(type, "f")==0)
			{
				triangleArray[nTriangle*9+0]=vertexArray[nVertex1-1].x;
				triangleArray[nTriangle*9+1]=vertexArray[nVertex1-1].y;
				triangleArray[nTriangle*9+2]=vertexArray[nVertex1-1].z;

				triangleArray[nTriangle*9+3]=vertexArray[nVertex2-1].x;
				triangleArray[nTriangle*9+4]=vertexArray[nVertex2-1].y;
				triangleArray[nTriangle*9+5]=vertexArray[nVertex2-1].z;

				triangleArray[nTriangle*9+6]=vertexArray[nVertex3-1].x;
				triangleArray[nTriangle*9+7]=vertexArray[nVertex3-1].y;
				triangleArray[nTriangle*9+8]=vertexArray[nVertex3-1].z;


				textureTriangleArray[nTriangle*6+0]=textureVertexArray[nTextureVertex1-1].u;
				textureTriangleArray[nTriangle*6+1]=textureVertexArray[nTextureVertex1-1].v;

				textureTriangleArray[nTriangle*6+2]=textureVertexArray[nTextureVertex2-1].u;
				textureTriangleArray[nTriangle*6+3]=textureVertexArray[nTextureVertex2-1].v;

				textureTriangleArray[nTriangle*6+4]=textureVertexArray[nTextureVertex3-1].u;
				textureTriangleArray[nTriangle*6+5]=textureVertexArray[nTextureVertex3-1].v;


				normalTriangleArray[nTriangle*9+0]=normalVertexArray[nNormalVertex1-1].x;
				normalTriangleArray[nTriangle*9+1]=normalVertexArray[nNormalVertex1-1].y;
				normalTriangleArray[nTriangle*9+2]=normalVertexArray[nNormalVertex1-1].z;

				normalTriangleArray[nTriangle*9+3]=normalVertexArray[nNormalVertex2-1].x;
				normalTriangleArray[nTriangle*9+4]=normalVertexArray[nNormalVertex2-1].y;
				normalTriangleArray[nTriangle*9+5]=normalVertexArray[nNormalVertex2-1].z;

				normalTriangleArray[nTriangle*9+6]=normalVertexArray[nNormalVertex3-1].x;
				normalTriangleArray[nTriangle*9+7]=normalVertexArray[nNormalVertex3-1].y;
				normalTriangleArray[nTriangle*9+8]=normalVertexArray[nNormalVertex3-1].z;
				
				nTriangle++;
			}
		}
		


	}
	inputFile.close();

}
