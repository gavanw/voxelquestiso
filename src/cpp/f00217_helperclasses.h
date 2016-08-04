

class UniformBuffer {
public:

	

	

	// GLchar* names[] =
	// {
	// 	"SurfaceColor",
	// 	"WarmColor",
	// 	"CoolColor",
	// 	"DiffuseWarm",
	// 	"DiffuseCool"
	// };

	int uniPosition;

	GLuint bufferId, uniformBlockIndex, index, progId;
	GLsizei uniformBlockSize;
	GLint singleSize, offset;
	GLfloat* uniData;

	// GLfloat colors[] = 
	// {
	// 	0.45,0.45,1,1,
	// 	0.45,0.45,1,1,
	// 	0.75,0.75,0.75,1,
	// 	0.0,0.0,1.0,1,
	// 	0.0,1.0,0.0,1
	// };


	bool wasUpdated;
	bool wasInit;
	
	UniformBuffer() {
		wasInit = false;
		uniData = NULL;
	}

	void init(GLuint _progId, int bufNameInd)
	{

		wasInit = true;
		uniPosition = 0;
		wasUpdated = false;
		progId = _progId;
		uniData = NULL;


		//Update the uniforms using ARB_uniform_buffer_object
		glGenBuffers(1, &bufferId);


		
		//There's only one uniform block here, the 'colors0' uniform block. 
		//It contains the color info for the gooch shader.
		uniformBlockIndex = glGetUniformBlockIndex(
			progId,
			BUF_NAMES[bufNameInd]//bufName.c_str()//"colors0"
		);

		
		//We need to get the uniform block's size in order to back it with the
		//appropriate buffer
		glGetActiveUniformBlockiv(
			progId,
			uniformBlockIndex,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&uniformBlockSize
		);

		doTraceND("uniformBlockSize: ", i__s(uniformBlockSize));


		if (uniData != NULL) {
			delete[] uniData;
			uniData = NULL;
		}

		uniData = new GLfloat[uniformBlockSize/4];


		
		//Create UBO.
		glBindBuffer(
			GL_UNIFORM_BUFFER,
			bufferId
		);
		glBufferData(
			GL_UNIFORM_BUFFER,
			uniformBlockSize,
			NULL,
			GL_STATIC_DRAW//GL_DYNAMIC_DRAW
		);

		//Now we attach the buffer to UBO binding point 0...
		glBindBufferBase(
			GL_UNIFORM_BUFFER,
			0,
			bufferId
		);
		//And associate the uniform block to this binding point.
		glUniformBlockBinding(
			progId,
			uniformBlockIndex,
			0
		);


		//To update a single uniform in a uniform block, we need to get its
		//offset into the buffer.
		
		//glGetUniformIndices(progId, 1, &names[2], &index);
		//glGetActiveUniformsiv(progId, 1, &index, GL_UNIFORM_OFFSET, &offset);
		//glGetActiveUniformsiv(progId, 1, &index, GL_UNIFORM_SIZE, &singleSize);

	    
	}

	void updateUniformBlock(int numFloats) {

		int datSize = uniformBlockSize;

		if (numFloats < 0) {

		}
		else {
			datSize = numFloats*4;
		}



		if (wasUpdated) {

		}
		else {
			glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
			//We can use BufferData to upload our data to the shader,
			//since we know it's in the std140 layout
			//each float is 4 bytes
			glBufferData(GL_UNIFORM_BUFFER, datSize, uniData, GL_DYNAMIC_DRAW);
			//With a non-standard layout, we'd use BufferSubData for each uniform.
			//glBufferSubData(GL_UNIFORM_BUFFER, offset, singleSize, &uniData[8]);
			
			wasUpdated = true;
		}

		

	}

	void beginUniformBlock() {
		uniPosition = 0;
	}

	void invalidateUniformBlock() {
		wasUpdated = false;
	}
	bool wasUpdatedUniformBlock() {
		return wasUpdated;
	}

	~UniformBuffer() {

		if (wasInit) {
			if (uniData) {
				delete[] uniData;
				uniData = NULL;
			}
			glDeleteBuffers(1,&bufferId);
		}
		

	}


};








