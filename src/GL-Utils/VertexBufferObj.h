#define INCLUDE_VERTEXBUFFOBJ

class VertexBufferObj
{
	unsigned int m_id;
	int m_vertSize; //How many floats are in a single vertex
public:
	//Binds the vertex buffer
	virtual void Bind();
	
	//Enable the vertex buffer
	virtual void Enable();
	
	//Returns the id of the vertex buffer
	virtual unsigned int GetId();
	//Returns the size of a vertex
	virtual int GetVertSize();

	//Sends data to the buffer
	virtual void Data(const float *dat, int size, int vSize);

	//Generate the buffer
	virtual void GenBuffer();
};
