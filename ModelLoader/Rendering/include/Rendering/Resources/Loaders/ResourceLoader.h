#pragma once
#include <thread>
#include <Rendering/Resources/Model.h>
#include <mutex>

class ResourceLoader
{
public:
	ResourceLoader() = delete;
	~ResourceLoader() = delete;

	/*template<typename T, typename... args>
	static std::vector<Rendering::Resources::Model> LoadModels(T first, args... args)
	{
		std::vector<Rendering::Resources::Model> models;
		//std::thread t{ &ThreadLoadModel,  models, first};
		LoadModels(args...);
		//t.join();
		return models;
	}*/
	
	/*static void ThreadLoadModel(std::vector<Rendering::Resources::Model>& p_models, const char* p_path)
	{
		p_models.push_back(Rendering::Resources::Model::StaticLoadModel(p_path));
	}*/

	bool isQuad;
	std::vector<Geometry::Vertex> vertices;
	std::vector<GLuint> faceIndex, textureIndex, normalIndex;
	std::vector<glm::vec3> tmp_vertex;
	std::vector<glm::vec2> tmp_uv;
	std::vector<glm::vec3> tmp_normal;

	std::ifstream in(filename);

	if (!in)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);

	}
	std::string line;
	while (std::getline(in, line))
	{
		//check v for vertices
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			vert = glm::vec3(x, y, z);
			tmp_vertex.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{

			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			GLfloat U, V;
			v >> U; v >> V;
			tex = glm::vec2(U, V);
			tmp_uv.push_back(tex);

		}
		else if (line.substr(0, 2) == "vn")
		{

			std::istringstream v(line.substr(3));
			glm::vec3 norm;
			GLfloat x, y, z;
			v >> x; v >> y; v >> z;
			norm = glm::vec3(x, y, z);
			tmp_normal.push_back(norm);

		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			GLuint x, y, z, a; //to store mesh index
			GLuint u, v, w, i; //to store texture index
			GLuint X, Y, Z, A; //to store normal index
			//std::istringstream v;
		  //v.str(line.substr(2));
			const char* chh = line.c_str();
			int count = sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", &x, &u, &X, &y, &v, &Y, &z, &w, &Z, &a, &i, &A); //here it read the line start with f and store the corresponding values in the variables

			faceIndex.push_back(x - 1); textureIndex.push_back(u - 1); normalIndex.push_back(X - 1);
			faceIndex.push_back(y - 1); textureIndex.push_back(v - 1); normalIndex.push_back(Y - 1);
			faceIndex.push_back(z - 1); textureIndex.push_back(w - 1); normalIndex.push_back(Z - 1);
			if (count == 12)
			{
				//faceIndex.push_back(a - 1); textureIndex.push_back(i - 1); normalIndex.push_back(A - 1);
				isQuad = true;
			}
			else
				isQuad = false;
		}

};
