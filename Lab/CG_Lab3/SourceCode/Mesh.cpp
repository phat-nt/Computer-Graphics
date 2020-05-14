#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};



void Mesh::CreateCuboid(float fWidth, float fHeight , float fLength)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fWidth, fHeight, fLength);
	pt[1].set( fWidth, fHeight, fLength);
	pt[2].set( fWidth, fHeight, -fLength);
	pt[3].set(-fWidth, fHeight, -fLength);
	pt[4].set(-fWidth, 0 , fLength);
	pt[5].set( fWidth, 0, fLength);
	pt[6].set( fWidth, 0, -fLength);
	pt[7].set(-fWidth, 0, -fLength);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateCylinder(int nSegment, float fTopHeight, float fRadius){
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fTopHeight, 0);
	for(i = 0; i<nSegment; i++){
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fTopHeight;
		pt[i+1].set(x, y, z);

		y = 0;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, 0, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}



void Mesh::CreateHinhHopCoRanh(float lenght, float width , float height , float depth, float thickness)
{
	numVerts = 16;
	pt = new Point3[numVerts];
	//bottom
	pt[0].set(lenght/2, -height/2, width/2);
	pt[1].set(-lenght/2, -height/2, width/2);
	pt[2].set(-lenght/2, -height/2, -width/2);
	pt[3].set(lenght/2, -height/2, -width/2);
	//midle
	pt[4].set(lenght/2,height/2 - depth ,width/2);
	pt[5].set(-lenght/2,height/2 - depth ,width/2);
	pt[6].set(-lenght/2,height/2 - depth,-width/2);
	pt[7].set(lenght/2,height/2 - depth,-width/2);
	//topnear
	pt[8].set(lenght/2,height/2 ,width/2);
	pt[9].set(-lenght/2,height/2 ,width/2);
	pt[10].set(-lenght/2,height/2 ,width/2 - thickness);
	pt[11].set(lenght/2,height/2,width/2 - thickness );
	//topfar
	pt[12].set(lenght/2,height/2 ,-width/2);
	pt[13].set(-lenght/2,height/2 ,-width/2);
	pt[14].set(-lenght/2,height/2 ,-width/2 + thickness);
	pt[15].set(lenght/2,height/2,-width/2 + thickness );

	numFaces = 14;
	face = new Face[numFaces];
	// bottom and middle face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	for(int i = 0 ; i < 4 ; i ++)
	{		
		face[0].vert[i].vertIndex = i;
		face[1].vert[i].vertIndex = i + 4;
	}

	//front and rear face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;

	//near and far face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 8;
	face[4].vert[2].vertIndex = 9;
	face[4].vert[3].vertIndex = 1;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 12;
	face[5].vert[2].vertIndex = 13;
	face[5].vert[3].vertIndex = 2;

	//near and far top faces

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 8;
	face[6].vert[1].vertIndex = 9;
	face[6].vert[2].vertIndex = 10;
	face[6].vert[3].vertIndex = 11;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 12;
	face[7].vert[1].vertIndex = 13;
	face[7].vert[2].vertIndex = 14;
	face[7].vert[3].vertIndex = 15;

	// two behind faces

	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 4;
	face[8].vert[1].vertIndex = 5;
	face[8].vert[2].vertIndex = 10;
	face[8].vert[3].vertIndex = 11;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[8].nVerts];
	face[9].vert[0].vertIndex = 6;
	face[9].vert[1].vertIndex = 7;
	face[9].vert[2].vertIndex = 12;
	face[9].vert[3].vertIndex = 13;

	//four front and rear faces

	face[10].nVerts = 3;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 4;
	face[10].vert[1].vertIndex = 8;
	face[10].vert[2].vertIndex = 11;

	face[11].nVerts = 3;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 7;
	face[11].vert[1].vertIndex = 12;
	face[11].vert[2].vertIndex = 15;
	
	face[12].nVerts = 3;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 5;
	face[12].vert[1].vertIndex = 9;
	face[12].vert[2].vertIndex = 10;
	
	face[13].nVerts = 3;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 6;
	face[13].vert[1].vertIndex = 13;
	face[13].vert[2].vertIndex = 14;

}


void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

//Lab3
void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}
